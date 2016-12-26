
LIBNAME=libtrie

INCLUDES= -I.
CFLAGS= -MD -g -Wall -DNDEBUG
LDFLAGS= -L.

.PHONY: all clean

OBJS_ALL=$(patsubst %.c,%.o,$(wildcard *.c))
OBJS_LIBS:=$(filter-out main.o,$(OBJS_ALL))

all: $(LIBNAME).a test 

$(LIBNAME).a: $(OBJS_LIBS)
	@$(AR) rcs $@ $^

%.o: %.c
	@$(CC) $(INCLUDES) $(CFLAGS) -Wall -g -c $(DEFINE) $<

test:
	@$(MAKE) -s -C test

clean: 
	@$(MAKE) -s -C test clean
	@/bin/rm -rf *.o *~ *.d $(LIBNAME).a
