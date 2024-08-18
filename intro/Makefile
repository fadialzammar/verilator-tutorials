MODULE = counter
TESTBENCH = tb.cpp
VFLAGS = -Wall --trace --exe --build -cc
WAVEFORM = waveform.vcd
PDFDIR = ../pdfs
PFLAGS = -f markdown-implicit_figures -t pdf -V colorlinks --highlight-style $(HIGHLIGHT)
HIGHLIGHT ?= tango
MARKDOWN = $(wildcard *.md)
PDFS = $(patsubst %.md,$(PDFDIR)/%.pdf, $(MARKDOWN))

.PHONY: docs all clean clean-docs clean-all

$(WAVEFORM): obj_dir/V$(MODULE)
	./obj_dir/V$(MODULE)

obj_dir/V$(MODULE): $(TESTBENCH) $(MODULE).sv
	verilator $(VFLAGS) $(TESTBENCH) $(MODULE).sv

docs: $(PDFDIR) $(PDFS)

$(PDFDIR):
	mkdir $(PDFDIR)

$(PDFDIR)/%.pdf: %.md
	pandoc $(PFLAGS) $< -o $@ 

clean:
	rm -rf obj_dir waveform.vcd

clean-docs:
	rm $(PDFS)
      
clean-all: clean clean-docs

all: $(WAVEFORM) docs
