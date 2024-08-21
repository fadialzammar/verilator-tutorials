PDFDIR = ../pdfs
PFLAGS = -f markdown-implicit_figures -t pdf -V colorlinks --highlight-style $(HIGHLIGHT)
HIGHLIGHT ?= tango
MARKDOWN = $(wildcard *.md)
PDFS = $(patsubst %.md,$(PDFDIR)/%.pdf, $(MARKDOWN))

.PHONY: pdf clean

pdf: $(PDFDIR) $(PDFS)

$(PDFDIR):
	mkdir $(PDFDIR)

$(PDFDIR)/%.pdf: %.md
	pandoc $(PFLAGS) $< -o $@ 

clean:
	rm $(PDFS)
