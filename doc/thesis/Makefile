# GNUmakefile template aatos.heikkinen@cern.ch
# For more info see manuals/stallman06aGnumake.pdf
# 080930 generalisig the scrip with parameters (tex, pdfviewer) 
# 080212 collected example code from Geant4

#d = ah09fortum
d = bthesis
#d = ah09bTalk
# extended report
#d = ah08hCodeReport
tex       = pdflatex
#tex       = latex
#pdfviewer = /home/gillis/Desktop/system/tools/acroread/opt/Adobe/Reader8/bin/./acroread
pdfviewer = evince
#pdfviewer = firefox
dviviewer = xdvi -allowshell -geometry 700x900+750+100 

all: 
	@echo :::document = $(d)
	@echo :::preparing latex ...
	@c; rm -f *.aux

	@makeindex $(d).tex; $(tex) $(d); bibtex $(d); $(tex) $(d); $(tex) $(d); asy $(d); $(tex) $(d)
ifdef AHSYSTEM
	$(dviviewer) $(d).dvi &
endif
	$(pdfviewer) $(d).pdf
ca:
	rm -f $(d).pdf $(d).ps *.out $(d)_*.eps $(d).asy

files:
	ls -latGg code/$(GI)  >  code/bertiniFiles.txt
	ls -latGg code/$(GI)  >> code/bertiniFiles.txt

gpin:   # grep pi-N scattering
	rm -f code/pin.grep;g
	grep -nisr tetnew code/ > code/pin.grep;
	grep -nisr phfun code/ >> code/pin.grep;

pdf:
	@echo :: prepare ps and pdf from dvi
	@dvips -R0 $(d).dvi -o $(d).ps
	@ps2pdf $(d).ps
ifdef AHSYSTEM
	$(pdfviewer) $(d).pdf &
endif
s:
	@echo :::launching browser... 
	@konqueror -geometry 650x1600+950+0 $(d).dvi &
	@echo :::done.

CODE = G4NucleiModel.cc
codetex: #prepare file to be included to latex
	echo " \begin{verbatim} "  > code/$(CODE).tex; \
        cat  code/$(CODE)         >> code/$(CODE).tex; \
        echo " \end{verbatim}   " >> code/$(CODE).tex; \
	ls -alt code

FIX  = FIX080213
codefix: #prepare file to be included to latex
	echo " \begin{verbatim} "       > code/$(FIX)$(CODE).tex; \
        grep -nisr $(FIX) code/$(CODE) >> code/$(FIX)$(CODE).tex; \
        echo " \end{verbatim}   "      >> code/$(FIX)$(CODE).tex; \
	ls -alt code

#-----------------SLIDE
slides:
	$(tex) $(d).tex; $(tex) $(d).tex; $(pdfviewer) $(d).pdf &

SOURCEFILE = d
show:
	$(pdfviewer) $(SOURCEFILE).pdf &

html: $(SOURCEFILE).pdf
	pdftohtml $(SOURCEFILE).pdf

pdfs: $(SOURCEFILE).tex 
	$(PDFGENERATOR) $(SOURCEFILE)
	$(PDFGENERATOR) $(SOURCEFILE)

dvi: $(SOURCEFILE).tex filter
	$(DVIGENERATOR) $(SOURCEFILE)
	$(DVIGENERATOR) $(SOURCEFILE)
	$(DVIGENERATOR) $(FILTEREDFISRC)
	$(DVIGENERATOR) $(FILTEREDFISRC)

ps: dvi
	$(PSGENERATOR) $(SOURCEFILE).dvi -o $(SOURCEFILE).ps
	$(PSGENERATOR) $(FILTEREDFISRC).dvi -o $(FILTEREDFISRC).ps

filter: $(FISOURCEFILE).tex
	cat $(FISOURCEFILE).tex |sed "s/ä/\\\\\"a/g" | sed "s/Ä/\\\\\"A/g" | sed "s/ö/\\\\\"o/g" | sed "s/Ö/\\\\\"O/g" > $(FILTEREDFISRC).tex


#END SLIDE -----------------------

