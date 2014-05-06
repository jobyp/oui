PROGS=students test_split frame rev palin test_urls concat map \
test_xref sentence f f2 f3 f4 vec lst

OBJDIR=_build

.PHONY: all
all: $(PROGS)

-include $(patsubst %.cc,$(OBJDIR)/%.d,$(wildcard *.cc))

CXX?=g++
CCFLAGS:=-g -O2 -std=c++11 -Wall -pedantic

$(OBJDIR)/%.d : %.cc | $(OBJDIR)
	@set -e ; rm -f $@; $(CXX) -MM $< > $@.$$$$; \
	sed -e 's,\($*\)\.o[ ]*:,$(OBJDIR)/\1.o $@ :,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(OBJDIR)/%.o: %.cc | $(OBJDIR)
	$(CXX) -c $(CCFLAGS) -o $@ $<

%: $(OBJDIR)/%.o
	$(CXX) $(CCFLAGS) -o $@ $^

$(OBJDIR):
	@mkdir -p $(OBJDIR)

students: $(addprefix $(OBJDIR)/,median.o student_info.o grade.o)
analyse: $(addprefix $(OBJDIR)/,median.o student_info.o grade.o report.o)
test_split: $(addprefix $(OBJDIR)/,split.o)
test_urls: $(addprefix $(OBJDIR)/,urls.o)
test_xref: $(addprefix $(OBJDIR)/,xref.o split.o)
sentence: $(addprefix $(OBJDIR)/,split.o)
f: $(addprefix $(OBJDIR)/,split.o)

emacs_cxx_offset:='// c-basic-offset: 8'
emacs_cxx_end:='// End:'
emacs_cxx_begin:='// Local Variables:'
emacs_cxx_mode:='// mode: c++'

.PHONY: ev
ev:
	@echo $(emacs_cxx_begin)
	@echo $(emacs_cxx_offset)
	@echo $(emacs_cxx_mode)
	@echo $(emacs_cxx_end)

.PHONY: clean
clean:
	@rm -rf $(PROGS) $(OBJDIR) *~

fix_source=$(shell sed -i -e '1 s/^[AB]*//' $(src_file))

.PHONY: fix
fix:
	@echo -n $(foreach src_file,$(wildcard *.cc) Makefile,$(fix_source))

