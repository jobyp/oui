PROGS=$(patsubst %.v,%.vo,$(wildcard *.v))

.PHONY: all
all: $(PROGS)
	@ :

%.vo: %.v
	coqc $<

# Add dependencies here
Induction.vo : Basics.vo
List.vo : Induction.vo

.PHONY: clean
clean:
	rm -f *~ *.glob *.vo

