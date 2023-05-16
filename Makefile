# HIGHLIGHT = tango
# PFLAGS = -f markdown-implicit_figures -t pdf -V colorlinks --highlight-style ${HIGHLIGHT}
# MARKDOWN=$(filter-out README.md, $(wildcard */*.md))
PDFDIR = pdfs/
LESSONS = $(filter-out $(PDFDIR), $(wildcard */))

.PHONY: docs clean-docs $(LESSONS)

docs: $(LESSONS)

$(LESSONS):
	$(MAKE) -C $@ docs

clean-docs:
	rm -r $(PDFDIR)
