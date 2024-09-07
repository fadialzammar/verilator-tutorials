MODULE = OTTER_Wrapper
MODULE_VERILOG = src/OTTER_Wrapper.sv
TESTBENCH = otter_tb.cpp
# INCLUDES = -I./src -I./src/peripherals
INCLUDES = -I./src
VFLAGS = -Wall --trace --exe --build -cc --Wno-fatal $(INCLUDES)
WAVEFORM = waveform.vcd

.PHONY: all clean

all: $(WAVEFORM)
$(WAVEFORM): obj_dir/V$(MODULE)
	./obj_dir/V$(MODULE)

obj_dir/V$(MODULE): $(TESTBENCH) $(MODULE_VERILOG)
	verilator $(VFLAGS) $(TESTBENCH) $(MODULE).sv

clean:
	rm -rf obj_dir waveform.vcd
