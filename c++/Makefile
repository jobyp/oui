PROGS_1:=students test_split frame rev palin test_urls concat map \
test_xref sentence f f2 f3 f4 vec str grad f5 handle str2 hw \
frame2 f6 hw2 insertion_sort merge_sort

PROGS_2:=bst

OBJDIR:=_build
BINDIR:=_bin

.PHONY: all
all: build_PROGS_1 algos

.PHONY: build_PROGS_1
build_PROGS_1 : $(addprefix $(BINDIR)/,$(PROGS_1))

.PHONY: algos
algos : LDFLAGS:=
algos : $(addprefix $(BINDIR)/,$(PROGS_2))

-include $(patsubst %.cc,$(OBJDIR)/%.d,$(wildcard *.cc))

CXX?=g++
CCFLAGS:=-g -O2 -std=c++11 -Wall -pedantic
LDFLAGS:= -pthread

$(OBJDIR)/%.d : %.cc | $(OBJDIR)
	@set -e ; rm -f $@; $(CXX) $(CCFLAGS) -MM $< > $@.$$$$; \
	sed -e 's,\($*\)\.o[ ]*:,$(OBJDIR)/\1.o $@ :,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(OBJDIR)/%.o: %.cc | $(OBJDIR)
	$(CXX) -c $(CCFLAGS) -o $@ $<

$(BINDIR)/%: $(OBJDIR)/%.o | $(BINDIR)
	$(CXX) $(CCFLAGS) $(LDFLAGS) -o $@ $^

$(OBJDIR) $(BINDIR):
	@mkdir -p $@


$(BINDIR)/students: $(addprefix $(OBJDIR)/,median.o student_info.o grade.o)
$(BINDIR)/analyse: $(addprefix $(OBJDIR)/,median.o student_info.o grade.o report.o)
$(BINDIR)/test_split: $(addprefix $(OBJDIR)/,split.o)
$(BINDIR)/test_urls: $(addprefix $(OBJDIR)/,urls.o)
$(BINDIR)/test_xref: $(addprefix $(OBJDIR)/,xref.o split.o)
$(BINDIR)/sentence: $(addprefix $(OBJDIR)/,split.o)
$(BINDIR)/f: $(addprefix $(OBJDIR)/,split.o)
$(BINDIR)/grad: $(addprefix $(OBJDIR)/,grade.o)

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
	@rm -rf $(PROGS_1) $(PROGS_2) $(OBJDIR) $(BINDIR) *~

fix_source=$(shell sed -i -e '1 s/^[AB]*//' $(src_file))

.PHONY: fix
fix:
	@echo -n $(foreach src_file,$(wildcard *.cc) Makefile,$(fix_source))

