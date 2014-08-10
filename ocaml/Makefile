PROGS:=$(patsubst %.ml,%.native,$(wildcard *.ml))

.PHONY: all
all : $(PROGS)
	@:

.PHONY: clean
clean:
	@rm -rf  _build *.cmx *.cmi *.o *~ $(PROGS)


%.native : %.ml
	corebuild $@
