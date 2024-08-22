PDFDIR ?= pdfs/
LESSON_FOLDERS = $(filter-out $(PDFDIR), $(wildcard */))
LESSON_NAMES = $(subst /,,$(LESSON_FOLDERS))
LESSON_READMES = $(foreach f,$(LESSON_FOLDERS),$(f)README.md)
LESSON_PDFS = $(foreach f,$(LESSON_NAMES),$(PDFDIR)$(f).pdf)
PFLAGS = -f markdown-implicit_figures -t pdf -V colorlinks --highlight-style $(HIGHLIGHT)
HIGHLIGHT ?= tango

.PHONY: all clean $(LESSON_NAMES)

all: $(PDFDIR) $(LESSON_PDFS)

$(PDFDIR):
	mkdir -p $(PDFDIR)

$(PDFDIR)%.pdf: %/README.md | $(PDFDIR)
	pandoc $(PFLAGS) --resource-path=$* $< -o $@

$(LESSON_NAMES): %: $(PDFDIR)%.pdf

clean:
	-rm -r $(PDFDIR)
