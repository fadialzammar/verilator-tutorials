#include <iostream>
#include <vector>
#include <png.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "obj_dir/Vvga_wrapper.h"
#include "obj_dir/Vvga_wrapper___024root.h"

using namespace std;

bool vcd_enabled() {
    // Return false only if VCD=0; defaults to true if not set
    static bool disabled = (getenv("VCD") != nullptr) && (strcmp(getenv("VCD"), "0") == 0);
    return !disabled;
}

int tick(Vvga_wrapper* dut, VerilatedVcdC* vcd, int time){
    dut->CLK = !dut->CLK;
    dut->eval();
    if (vcd_enabled()) {
        vcd->dump(time);
    }
    return time + 1;
}

void write_png(const char* filename, uint8_t* image_data, int width, int height) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        cerr << "File could not be opened for writing\n";
        exit(1);
    }

    // Initialize libpng structures
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        cerr << "png_create_write_struct failed\n";
        exit(1);
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        cerr << "png_create_info_struct failed\n";
        exit(1);
    }

    // Set error handling
    if (setjmp(png_jmpbuf(png))) {
        cerr << "Error during png creation\n";
        exit(1);
    }

    // Set the output file for libpng
    png_init_io(png, fp);

    // Write header information for the PNG
    png_set_IHDR(png, info, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    // Write image data
    png_write_info(png, info);
    for (int y = 0; y < height; y++) {
        // Prepare a row of pixels in 8-bit format (R3 G3 B2 -> R8 G8 B8)
        vector<uint8_t> row(width * 3);  // 3 bytes per pixel (RGB)

        for (int x = 0; x < width; x++) {
            int row_offset = y * width;

            // Convert the RRRGGGBB format to 8-bit RGB
            uint8_t pixel = image_data[row_offset + x];
            uint8_t r = (pixel & 0b11100000);
            uint8_t g = (pixel & 0b00011100) << 3;
            uint8_t b = (pixel & 0b00000011) << 6;

            // Fill the row with the expanded pixel data
            row[x * 3] = r;
            row[x * 3 + 1] = g;
            row[x * 3 + 2] = b;
        }

        png_write_row(png, row.data());
    }
    
    // End the write process
    png_write_end(png, nullptr);

    // Clean up
    fclose(fp);
    png_destroy_write_struct(&png, &info);
}

int main(int argc, char** argv, char** env){
    // Initialize verilated module
    Vvga_wrapper* dut = new Vvga_wrapper;

    // Trace setup
    VerilatedVcdC* vcd = nullptr;
    if (vcd_enabled()) {
        Verilated::traceEverOn(true); // enables trace output
        vcd = new VerilatedVcdC; // object to hold trace
        dut->trace(vcd,5);
        vcd->open("waveform.vcd");
    }
    int time = 0; // the timestep we are currently on

    // Initialize inputs
    dut->SWITCHES = 0;
    dut->CLK = 0;
    dut->BTNL = 0;

    // Reset
    dut->BTNC = 1; // BTNC is tied to OTTER_MCU's RESET in OTTER_Wrapper
    time = tick(dut, vcd, time);
    time = tick(dut, vcd, time);
    dut->BTNC = 0;

    for (int i = 0; i < 1e7; i++) {
        time = tick(dut, vcd, time);
    }
    
    // Write framebuffer to raw file
    FILE* image = fopen("vga_image.raw", "wb");
    int mem_size = 1 << 17;
    fwrite(&dut->rootp->vga_wrapper__DOT__VGA__DOT__ram128kx8__DOT__mem, 1, mem_size, image);  // Write 1 byte from mem, mem_size times, to image
    fclose(image);

    // Write framebuffer to PNG
    int width = 320;
    int height = 240;
    mem_size = width * height;
    uint8_t image_mem[mem_size];

    for (int i = 0; i < mem_size; i++) {
        // Copy data from Verilator object to contiguous array
        image_mem[i] = dut->rootp->vga_wrapper__DOT__VGA__DOT__ram128kx8__DOT__mem[i];
    }
    write_png("output_image.png", image_mem, width, height);

    dut->final();

    // Cleanup
    if (vcd_enabled()) {
        vcd->close();
    }
    delete dut;
    exit(EXIT_SUCCESS);
}
