MODULE = counter
TESTBENCH = tb.cpp
VFLAGS = -Wall --trace --exe --build -cc
WAVEFORM = waveform.vcd

.PHONY: all clean

all: $(WAVEFORM)
$(WAVEFORM): obj_dir/V$(MODULE)
	./obj_dir/V$(MODULE)

obj_dir/V$(MODULE): $(TESTBENCH) $(MODULE).sv
	verilator $(VFLAGS) $(TESTBENCH) $(MODULE).sv

clean:
	rm -rf obj_dir waveform.vcd
