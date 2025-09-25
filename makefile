#CFLAGS := --std=c99 -Wall -Wextra -Wpedantic
CFLAGS := -Wall -std=c99

ifdef DEBUG
	CFLAGS += -g
else
	CFLAGS += -O3
endif

SRC := main.c task_functions.c aux_functions.c file_open.c file_results.c
OBJ := ${SRC:%.c=build/%.o}

INC := header.h

OUT := tourists

build/%.o: %.c $(INC) | build
	$(CC) -o $@ -c $< $(CFLAGS)

$(OUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean build

build:
	mkdir -p $@

clean:
	rm -rf build/ $(OUT)
