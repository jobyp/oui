PROGS=students split frame rev palin urls analyse

EMACS_CC_MODE:='mode: c++'
.PHONY: all
all: $(PROGS)

CXX?=g++
# On my Chromebook I have an older gcc
ifeq ($(strip $(shell uname -m)),armv7l)
CCFLAGS:= -g -O0 -std=c++0x -Wall -pedantic
else
CCFLAGS:= -g -O0 -std=c++11 -Wall -pedantic
endif

%.o: %.cc
	$(CXX) -c $(CCFLAGS) -o $@ $<

%: %.o
	$(CXX) $(CCFLAGS) -o $@ $^

$(foreach src,$(wildcard *.cc),$(eval $(shell $(CXX) -MM $(src))))

students: median.o student_info.o grade.o
analyse: median.o student_info.o grade.o report.o

.PHONY: ev
ev:
	@echo '// Local Variables:'
	@echo '// c-basic-offset: 8'
	@echo '// $(EMACS_CC_MODE)'
	@echo '// End:'

.PHONY: clean
clean:
	@rm -f $(PROGS) *.o *~

fix_source=$(shell sed -i -e '1 s/^[AB]*//' $(src_file))

.PHONY: fix
fix:
	@echo -n $(foreach src_file,$(wildcard *.cc),$(fix_source))

