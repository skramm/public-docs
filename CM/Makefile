# generic makefile for building multiple beamer pdf files from source .texb files

# .texg targets are declared as .PRECIOUS so they don't get erased in case of trouble somewhere
# note: .texg stands for "Generated TEX" files, to make sure they don't get confused with regular hand-written tex files
#.PRECIOUS: %.texg %.tex
.SECONDARY:

# Required ! Because the default shell used by Make is "sh" (?), and with this shell,
# the command "echo "\n xxx" does not print the linefeed
SHELL=bash

infiles   :=$(wildcard src/*.tex)
filenames :=$(notdir $(basename $(infiles)))
types     :=B H P

FILE_EXT=tex

# building the final list of pdf files to be generated
outfiles := $(foreach Y,$(filenames),\
	$(foreach X,$(types),\
		out/$(Y)_$(X).pdf ) ) 


all: $(infiles) $(outfiles) $(ditaa_out)
	@echo "done target $<"


show:
	@echo "infiles=$(infiles)"
	@echo "filenames=$(filenames)"
	@echo "outfiles=$(outfiles)"


# rules for building .tex file from single .texb file

build/%_B.texg: src/%.$(FILE_EXT) template/head_beamer.tex template/common_header.tex
#	@echo " - building file $@ from $<"
	@cat template/head_beamer.tex template/common_header.tex $< > $(basename $(@)).texg
	@echo "\end{document}" >> $(basename $(@)).texg

build/%_H.texg: src/%.$(FILE_EXT) template/head_handout1.tex template/common_header.tex
#	@echo " - building file $@ from $<"
	@cat template/head_handout1.tex template/common_header.tex $< > $(basename $(@)).texg
	@echo "\end{document}" >> $(basename $(@)).texg

build/%_P.texg: src/%.$(FILE_EXT) template/head_handout4.tex template/common_header.tex
#	@echo " - building file $@ from $<"
	@cat template/head_handout4.tex template/common_header.tex $< > $(basename $(@)).texg
	@echo "\end{document}" >> $(basename $(@)).texg


# rule for building .pdf file from .texg file
# need to call twice pdflatex to get refs right
build/%.pdf: build/%.texg
	@echo " - calling latex to build file $@ from $<"
	cd build && pdflatex --interaction=batchmode $(notdir $<) 1> $(notdir $(basename $<)).stdout  2> $(notdir $(basename $<)).stderr

# copy to output folder, that will contain only the final pdf files
out/%.pdf: build/%.pdf
	@mv $< $@ 


touch:
	touch $(infiles)

clean:
	@echo " - Clean up generated files"
	@-rm build/* 1>/dev/null 2>/dev/null


cleanall: clean
	@echo " - Clean all non-generated files"
	@-rm src/*.texg
	@-rm out/*.pdf 1>/dev/null 2>/dev/null
	
