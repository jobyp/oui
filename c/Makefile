PROGS := hwserver hwclient
OBJDIR := _build

CFLAGS := -g -std=c99
LDFLAGS := -lzmq

.PHONY: all
all: $(PROGS)
	@:

% : %.c
% : %.o

.SECONDARY:

$(OBJDIR)/%.o : %.c | $(OBJDIR)
	gcc -Wall -c $(CFLAGS) -o $@  $< 

% : $(OBJDIR)/%.o
	gcc -Wall -o $@ $^ $(LDFLAGS) 

$(OBJDIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(PROGS) $(OBJDIR) *~ 

