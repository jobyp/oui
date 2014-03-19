PROGS=$(wildcard *.cc)
BINS=$(patsubst %.cc,%,$(PROGS))

.PHONY: all
all: $(BINS)

# On my Chromebook I have an older gcc
ifeq ($(strip $(shell uname -m)),armv7l)
CCFLAGS:= -std=c++0x -Wall
else
CCFLAGS:= -std=c++11 -Wall
endif

%: %.cc
	g++ $(CCFLAGS) -o $@ $<

.PHONY: ev
ev:
	@echo '// Local Variables:'
	@echo '// c-basic-offset: 8'
	@echo '// End:'

.PHONY: clean
clean:
	@rm -f $(BINS) *.o *~

fix_source=$(shell sed -i -e '1 s/^[AB]*//' $(src_file))

.PHONY: fix
fix:
	@echo -n $(foreach src_file,$(wildcard *.cc),$(fix_source))

