BINC := $(HOME)/Coding/include
BLIB := $(HOME)/Coding/lib

APLCORE_FLAGS := -L$(BLIB) -laplcore
CFLAGS := -Wall -Wextra -Wpedantic -g
OBJS_LIST := obj/getcodept.o obj/main.o

EXEC := test

all: $(EXEC)

.PHONY: clean

obj/getcodept.o: Makefile obj src/getcodept.c include/getcodept.h
	gcc src/getcodept.c -c -I$(BINC) -I$(BINC)/aplcore -Iinclude -o obj/getcodept.o $(CFLAGS)

obj/main.o: Makefile obj src/main.c include/getcodept.h
	gcc src/main.c -c -I$(BINC) -I$(BINC)/aplcore -Iinclude -o obj/main.o $(CFLAGS)

$(EXEC): Makefile $(OBJS_LIST)
	gcc $(APLCORE_FLAGS) $(OBJS_LIST) -o $(EXEC)

obj:
	mkdir obj

clean:
	rm obj/* $(EXEC)
