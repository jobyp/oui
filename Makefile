.PHONY: all
all: hw

hw: hw.cc
	g++ -std=c++11 -o $@ $<

.PHONY: clean
clean:
	rm -f hw hw.o *~
