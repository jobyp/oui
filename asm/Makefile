PROGS:=exit
OBJDIR=_build

AS=yasm
LD=gcc

.PHONY: all
all: $(PROGS)
	@:

.SECONDARY:

LST=$(patsubst %.asm,%.lst,$<)

$(OBJDIR)/%.o : %.asm | $(OBJDIR)
	$(AS) -f elf64 -g dwarf2 -l $(LST) -o $@ $<

% : $(OBJDIR)/%.o
	$(LD) -o $@ $^

$(OBJDIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(PROGS) $(OBJDIR) *.lst *~ 

