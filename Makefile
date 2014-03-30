PROGS?=$(wildcard *.cc)
BINS=$(patsubst %.cc,%,$(PROGS))
EMACS_CC_MODE:='mode: c++'
.PHONY: all
all: $(BINS)

# On my Chromebook I have an older gcc
ifeq ($(strip $(shell uname -m)),armv7l)
CCFLAGS:= -g -O0 -std=c++0x -Wall
else
CCFLAGS:= -g -O0 -std=c++11 -Wall
endif

%: %.cc
	g++ $(CCFLAGS) -o $@ $<

.PHONY: ev
ev:
	@echo '// Local Variables:'
	@echo '// c-basic-offset: 8'
	@echo '// $(EMACS_CC_MODE)'
	@echo '// End:'

.PHONY: clean
clean:
	@rm -f $(BINS) *.o *~

fix_source=$(shell sed -i -e '1 s/^[AB]*//' $(src_file))

.PHONY: fix
fix:
	@echo -n $(foreach src_file,$(wildcard *.cc),$(fix_source))

