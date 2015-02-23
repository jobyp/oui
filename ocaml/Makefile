PROGS := stats tac grml
OCAMLC ?= ocamlopt.opt

.PHONY: all
all: $(PROGS)
	@:

.PHONY: clean
clean:
	@rm -f $(PROGS) *~ *.cmi *.cmo *.o *.cmx

stats : textstat.mli textstat.ml stats.ml
	$(OCAMLC) $^ -o $@ 

% : %.ml
	$(OCAMLC) $^ -o $@
