MODULE = counter.sv
TESTBENCH = tb.cpp
VFLAGS = -Wall --trace --exe --build -cc
PDFDIR = ../pdfs
PFLAGS = -f markdown-implicit_figures -t pdf -V colorlinks --highlight-style $(HIGHLIGHT)
HIGHLIGHT ?= tango
MARKDOWN = $(wildcard *.md)
PDFS = $(patsubst %.md,$(PDFDIR)/%.pdf, $(MARKDOWN))

.PHONY: docs all clean clean-docs clean-all

obj_dir/V$(MODULE): $(TESTBENCH) $(MODULE)
	verilator $(VFLAGS) $(TESTBENCH) $(MODULE)

docs: $(PDFDIR) $(PDFS)

$(PDFDIR):
	mkdir $(PDFDIR)

$(PDFDIR)/%.pdf: %.md
	pandoc $(PFLAGS) $< -o $@ 

clean:
	rm -r ./obj_dir/

clean-docs:
	rm $(PDFS)
      
clean-all: clean clean-docs
