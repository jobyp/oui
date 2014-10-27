PROGS:=exit
OBJDIR=_build

AS=as
LD=gcc

.PHONY: all
all: $(PROGS)
	@:

.SECONDARY:

$(OBJDIR)/%.o : %.asm | $(OBJDIR)
	$(AS) -aln=$*.list -g -o $@ $<

% : $(OBJDIR)/%.o
	$(LD) -o $@ $^

$(OBJDIR):
	mkdir -p $@


.PHONY: clean
clean:
	rm -rf $(PROGS) $(OBJDIR) $(PROGS:%=%.list)


% : %.s
