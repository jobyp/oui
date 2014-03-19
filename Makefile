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

.PHONY: ev
ev:
	@echo '// Local Variables:'
	@echo '// c-basic-offset: 8'
	@echo '// End:'

.PHONY: clean
clean:
	rm -f hw hw.o *~

fix_source=$(shell sed -i -e '1 s/^[AB]*//' $(src_file))

.PHONY: fix
fix:
	@echo -n $(foreach src_file,$(wildcard *.cc),$(fix_source))

