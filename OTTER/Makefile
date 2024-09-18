MODULE = OTTER_Wrapper
TESTBENCH = otter_tb.cpp
# INCLUDES = -I./src -I./src/peripherals
INCLUDES = -I./src
PROGRAM ?= mul
PARAMS = -GMEM_FILE='"mem/$(PROGRAM).mem"'
VFLAGS = -Wall --trace --exe --build -cc --Wno-fatal $(INCLUDES) $(PARAMS)
WAVEFORM = waveform.vcd
SRC_FILES = $(wildcard src/*.sv mem/*.mem)

.PHONY: all clean

all: $(WAVEFORM)
$(WAVEFORM): obj_dir/V$(MODULE)
	./obj_dir/V$(MODULE)

obj_dir/V$(MODULE): $(TESTBENCH) $(SRC_FILES)
	verilator $(VFLAGS) $(TESTBENCH) $(MODULE).sv

clean:
	rm -rf obj_dir waveform.vcd
