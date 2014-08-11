PROGS=$(patsubst %.v,%.vo,$(wildcard *.v))

.PHONY: all
all: $(PROGS)
	@ :

%.vo: %.v
	coqc $^

# Add dependencies here


.PHONY: clean
clean:
	rm -f *~ *.glob *.vo

