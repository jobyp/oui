PROGS := wc interact split_lines
GHCFLAGS := --make -Wall

.PHONY: all
all: $(PROGS)
	@ :

.PHONY: clean
clean:
	rm -f *~ $(PROGS) *.hi *.o


% : %.hs
	ghc $(GHCFLAGS) $< -o $@

