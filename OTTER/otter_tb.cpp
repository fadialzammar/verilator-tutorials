#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "obj_dir/VOTTER_Wrapper.h"
#include "obj_dir/VOTTER_Wrapper___024root.h"

using namespace std;

int tick(VOTTER_Wrapper *dut, VerilatedVcdC *vcd, int time){
    dut->CLK = !dut->CLK;
    dut->eval();
    vcd->dump(time);
    return time + 1;
}

int main(int argc, char** argv, char** env){
    // Initialize verilated module
    VOTTER_Wrapper *dut = new VOTTER_Wrapper;

    // Trace setup
    Verilated::traceEverOn(true); // enables trace output
    // std::print(Verilated::time())
    VerilatedVcdC *vcd = new VerilatedVcdC; // object to hold trace
    dut->trace(vcd,5);
    vcd->open("waveform.vcd");
    int time = 0; // the timestep we are currently on

    // Initialize inputs
    dut->SWITCHES = 0;
    dut->CLK = 0;
    dut->BTNL = 0;

    // Reset
    dut->BTNC = 1; // BTNC tied to OTTER_MCU's RESET in OTTER_Wrapper
    time = tick(dut, vcd, time);
    time = tick(dut, vcd, time);
    dut->BTNC = 0;

    for (int i = 0; i < 10000; i++) {
        time = tick(dut, vcd, time);
    }
    
    cout << "Reg s0: " << dut->rootp->OTTER_Wrapper__DOT__MCU__DOT__RF__DOT__RF[8] << endl;
    dut->final();

    // Cleanup
    vcd->close();
    delete dut;
    exit(EXIT_SUCCESS);
}
