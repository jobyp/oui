PROGS:=Basics Induction Lists

.PHONY: all
all: $(patsubst %,%.vo,$(PROGS))
	@ :

%.vo : %.v
	coqc $<

# Add dependencies here
Induction.vo : Basics.vo
Lists.vo : Induction.vo
Poly.vo : Lists.vo
MoreCoq.vo : Poly.vo
Logic.vo : MoreCoq.vo
Prop.vo : Logic.vo
MoreLogic.vo : Prop.vo

.PHONY: clean
clean:
	rm -f *~ *.glob *.vo

