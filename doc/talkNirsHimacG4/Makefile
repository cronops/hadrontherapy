# GNUmakefile template aatos.heikkinen@cern.ch
# For more info see manuals/stallman06aGnumake.pdf
# 080930 generalisig the scrip with parameters (tex, pdfviewer) 
# 080212 collected example code from Geant4

d         = talkNirsHimacG4
tex       = pdflatex
pdfviewer = xpdf
#pdfviewer = gv
#pdfviewer = firefox
#pdfviewer = evince
dviviewer = xdvi -allowshell -geometry 700x900+750+100 

all: 
	@echo :::document = $(d)
	@echo :::preparing latex ...
	@c; rm -f *.aux *.toc
	@makeindex $(d).tex; $(tex) $(d); bibtex $(d); $(tex) $(d); $(tex) $(d); asy $(d); $(tex) $(d)
	$(pdfviewer) $(d).pdf

talk: d =ah09cTalk
talk: all

doc: d =ah09bCommittee
doc: all

pdf:
	@echo :: prepare ps and pdf from dvi
	@dvips -R0 $(d).dvi -o $(d).ps
	@ps2pdf $(d).ps

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


