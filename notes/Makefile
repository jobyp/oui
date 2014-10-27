PROGS:=$(patsubst %.tex,%.pdf,$(wildcard *.tex))

.PHONY: all
all : $(PROGS)
	@ :

%.pdf : %.tex
	pdflatex $<

.PHONY:clean
clean:
	@rm -vf $(PROGS) *.aux *.log *~