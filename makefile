cFLAGS := --std=c99 -Wall -Wextra -Wpedantic

ifdef DEBUG
	CFLAGS += -g
else
	CFLAGS += -O3
endif

SRC := main.c
OBJ := ${SRC:%.c=build/%.o}

INC :=

OUT := tourIST

build/%.o: %.c $(INC) | build
	$(CC) -o $@ -c $< $(CFLAGS)

$(OUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean build

build:
	mkdir -p $@

clean:
	rm -rf build/
