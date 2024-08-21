# HIGHLIGHT = tango
# PFLAGS = -f markdown-implicit_figures -t pdf -V colorlinks --highlight-style ${HIGHLIGHT}
# MARKDOWN=$(filter-out README.md, $(wildcard */*.md))
PDFDIR = pdfs/
LESSONS = $(filter-out $(PDFDIR), $(wildcard */))

.PHONY: pdfs clean $(LESSONS)

pdfs: $(LESSONS)

$(LESSONS):
	$(MAKE) -C $@ -f pdf.mk

clean:
	rm -r $(PDFDIR)
