PROGS := wc interact split_lines Main
GHCFLAGS := --make -Wall -O 

.PHONY: all
all: $(PROGS)
	@ :

Main : CommonWords.hs

% : %.hs
	ghc $(GHCFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f *~ $(PROGS) *.hi *.o
