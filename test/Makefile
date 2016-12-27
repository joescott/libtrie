
TEST=trie_test

INCLUDES= -I. -I../ 
CFLAGS= -MD -g -Wall -DDEBUG
LDFLAGS= -L. -L../ -ltrie

.PHONY: all clean 

OBJS_ALL=$(patsubst %.c,%.o,$(wildcard *.c))

all: $(TEST)

$(TEST): $(OBJS_ALL)
	@$(CC) $^ $(LDFLAGS) -o $@  

%.o: %.c
	@$(CC) $(INCLUDES) $(CFLAGS) -Wall -g -c $(DEFINE) $<

clean: 
	@/bin/rm -rf *.o *~ *.d $(TEST)
