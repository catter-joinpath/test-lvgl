CFLAGS = -ggdb3
LDFLAGS = -llvgl -llvgl_examples -lm -pthread

SRC = $(shell find -type f -name *.c)
OBJ = $(patsubst %.c,%.o,$(SRC))
DEP = $(patsubst %.c,%.d,$(SRC))

TARGET = test_lvgl

all: $(OBJ)
	gcc -o $(TARGET) $(OBJ) $(LDFLAGS)

clean:
	rm -rf $(TARGET) $(OBJ) $(DEP)

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<