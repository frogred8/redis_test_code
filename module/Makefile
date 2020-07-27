# find the OS
uname_S = $(shell sh -c 'uname -s 2>/dev/null || echo not')

# Compile flags for linux / osx
ifeq ($(uname_S), Linux)
	SHOBJ_LDFLAGS ?= -shared
else
	SHOBJ_LDFLAGS ?= -bundle -undefined dynamic_lookup
endif

CFLAG = -g -fPIC -O2 -std=gnu99
CC = gcc

all: clean test_module.so

# test_module.so: src/setbigger.c
# 		$(CC) -Iinclude $(CFLAG) $(SHOBJ_LDFLAGS) -o $@ $< 

setbigger.o: src/setbigger.c
		$(CC) -Iinclude $(CFLAG) -c -o $@ $<

test_module.so: setbigger.o
		$(CC) $(SHOBJ_LDFLAGS) -o $@ $< 

clean: 
		rm -f *.o *.so
