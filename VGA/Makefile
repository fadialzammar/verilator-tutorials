MODULE = vga_wrapper
TESTBENCH = vga_tb.cpp
INCLUDES = -Isrc
PROGRAM ?= vga_color_shift
PARAMS = -GMEM_FILE='"mem/$(PROGRAM).mem"'
VFLAGS = -Wall --trace --exe --build -cc --Wno-fatal $(INCLUDES) $(PARAMS) --LDFLAGS -lpng
WAVEFORM = waveform.vcd
SRC_FILES = $(wildcard src/*)

.PHONY: all clean

all: obj_dir/V$(MODULE)
	./obj_dir/V$(MODULE)

obj_dir/V$(MODULE): $(TESTBENCH) $(SRC_FILES)
	verilator $(VFLAGS) $(MODULE).sv $(TESTBENCH) 

clean:
	rm -rf obj_dir waveform.vcd output_image.png
