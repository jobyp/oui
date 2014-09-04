PROGS:=$(patsubst %.v,%.vo,$(wildcard *.v))

.PHONY: all
all: $(PROGS)
	@ :

%.vo : %.v
	coqc $<

# Add dependencies here
Induction.vo : Basics.vo
Lists.vo : Induction.vo
Poly.vo : Lists.vo
MoreCoq.vo : Poly.vo

.PHONY: clean
clean:
	rm -f *~ *.glob *.vo

