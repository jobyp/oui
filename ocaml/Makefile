PROGS := hw
OCAMLC ?= ocamlopt.opt

.PHONY: all
all: $(PROGS)
	@:

.PHONY: clean
clean:
	@rm -f $(PROGS) *~ *.cmi *.cmo *.o *.cmx

% : %.ml
	$(OCAMLC) -o $@ $<

