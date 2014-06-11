PROGS := hwserver hwclient version
OBJDIR := _build

CFLAGS := -g -std=c99
LDFLAGS := -lzmq

.PHONY: all
all: $(PROGS)
	@:

hwserver : $(addprefix $(OBJDIR)/,util.o)
hwclient : $(addprefix $(OBJDIR)/,util.o)

-include $(patsubst %.c,$(OBJDIR)/%.d,$(wildcard *.c))

% : %.c
% : %.o

.SECONDARY:

$(OBJDIR)/%.d : %.c | $(OBJDIR)
	@set -e ; rm -f $@; gcc $(CFLAGS) -MM $< > $@.$$$$; \
	sed -e 's,\($*\)\.o[ ]*:,$(OBJDIR)/\1.o $@ :,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(OBJDIR)/%.o : %.c | $(OBJDIR)
	gcc -Wall -c $(CFLAGS) -o $@  $< 

% : $(OBJDIR)/%.o
	gcc -Wall -o $@ $^ $(LDFLAGS) 

$(OBJDIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(PROGS) $(OBJDIR) *~ 

