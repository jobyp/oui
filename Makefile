.PHONY: all
all: hw

# On my Chromebook I have an older gcc
ifeq ($(strip $(shell uname -m)),armv7l)
CCFLAGS:= -std=c++0x
else
CCFLAGS:= -std=c++11
endif

hw: hw.cc
	g++ $(CCFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f hw hw.o *~
