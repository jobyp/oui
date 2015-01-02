PROGS:=$(patsubst %.hs,%,$(wildcard *.hs)) 

.PHONY: all
all: $(PROGS)
	@ :

.PHONY: clean
clean:
	rm -f *~ $(PROGS) *.hi *.o


% : %.hs
	ghc $<

