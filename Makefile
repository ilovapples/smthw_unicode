BINC := $(HOME)/Coding/include
BLIB := $(HOME)/Coding/lib

APLCORE_FLAGS := -L$(BLIB) -laplcore
CFLAGS := -Wall -Wextra -Wpedantic -Wno-gnu-zero-variadic-macro-arguments -g
OBJS_LIST := obj/getcodept.o obj/main.o

EXEC := test

all: $(EXEC)

.PHONY: clean

obj/getcodept.o: Makefile src/getcodept.c include/getcodept.h
	gcc src/getcodept.c -c -I$(BINC) -I$(BINC)/aplcore -Iinclude -o obj/getcodept.o $(CFLAGS)

obj/main.o: Makefile src/main.c include/getcodept.h
	gcc src/main.c -c -I$(BINC) -I$(BINC)/aplcore -Iinclude -o obj/main.o $(CFLAGS)

$(EXEC): $(OBJS_LIST) obj
	gcc $(OBJS_LIST) $(APLCORE_FLAGS) -o $(EXEC)

obj:
	mkdir obj

clean:
	rm -f obj/* $(EXEC)
