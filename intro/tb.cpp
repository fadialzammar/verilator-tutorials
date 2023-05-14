#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h> // Needed for trace output
#include "Vcounter.h"

#define MAX_TIME 20
int i = 0;

int main(int argc,char** argv, char** env){
    // Initialize verilated module
    Vcounter *dut = new Vcounter;

    // Trace setup
    Verilated::traceEverOn(true); // enables trace output
    VerilatedVcdC *m_trace = new VerilatedVcdC; // object to hold trace
    dut->trace(m_trace,5);
    m_trace->open("waveform.vcd");

    // Initialize inputs
    dut->clk = 0;

    // Run simulation
    while(i<MAX_TIME) {
        dut->clk ^= 1;
        dut->reset = 0;
        dut->eval();
        m_trace->dump(i);
        printf("Count: %i\n", dut->count);
        i++;
    }

    // Cleanup
    m_trace->close();
    dut->final();
    delete dut;
    exit(EXIT_SUCCESS);
}