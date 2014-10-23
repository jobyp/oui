PROGS:=exit
OBJDIR=_build

AS=gcc -c -O2 -x assembler
LD=gcc

.PHONY: all
all: $(PROGS)
	@:

.SECONDARY:

$(OBJDIR)/%.o : %.asm | $(OBJDIR)
	$(AS) -o $@ $<

% : $(OBJDIR)/%.o
	$(LD) -o $@ $^

$(OBJDIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(PROGS) $(OBJDIR) *~ 


% : %.s
