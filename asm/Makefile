PROGS:=$(patsubst %.asm,%,$(wildcard *.asm))
OBJDIR=_build

AS=as
LD=gcc

.PHONY: all
all: $(PROGS)
	@:

.SECONDARY:

$(OBJDIR)/%.o : %.asm | $(OBJDIR)
	$(AS) -aln=$(OBJDIR)/$*.list -g -o $@ $<

% : $(OBJDIR)/%.o
	$(LD) -o $@ $^

$(OBJDIR):
	mkdir -p $@


.PHONY: clean
clean:
	rm -rf $(PROGS) $(OBJDIR) *~ hw.*


% : %.s
% : %.c

