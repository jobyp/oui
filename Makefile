PROGS=students test_split frame rev palin test_urls analyse concat map \
test_xref sentence

EMACS_CC_MODE:='mode: c++'
.PHONY: all
all: $(PROGS)

-include $(patsubst %.cc,%.d,$(wildcard *.cc))

CXX?=g++
# On my Chromebook I have an older gcc
ifeq ($(strip $(shell uname -m)),armv7l)
CCFLAGS:= -g -O0 -std=c++0x -Wall -pedantic
else
CCFLAGS:= -g -O0 -std=c++11 -Wall -pedantic
endif

%.d : %.cc
	@set -e ; rm -f $@; $(CXX) -MM $< > $@.$$$$; \
	sed -e 's,\($*\)\.o[ ]*:,\1.o $@ :,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.o: %.cc
	$(CXX) -c $(CCFLAGS) -o $@ $<

%: %.o
	$(CXX) $(CCFLAGS) -o $@ $^

students: median.o student_info.o grade.o
analyse: median.o student_info.o grade.o report.o
test_split: split.o
test_urls: urls.o
test_xref: xref.o split.o
sentence: split.o

.PHONY: ev
ev:
	@echo '// Local Variables:'
	@echo '// c-basic-offset: 8'
	@echo '// $(EMACS_CC_MODE)'
	@echo '// End:'

.PHONY: clean
clean:
	@rm -f $(PROGS) *.o *.d *~

fix_source=$(shell sed -i -e '1 s/^[AB]*//' $(src_file))

.PHONY: fix
fix:
	@echo -n $(foreach src_file,$(wildcard *.cc),$(fix_source))

