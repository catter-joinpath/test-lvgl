CFLAGS = -ggdb3 -DLV_CONF_INCLUDE_SIMPLE -DLV_CONF_SUPPRESS_DEFINE_CHECK
LDFLAGS = -llvgl -llvgl_examples -linput -lm -pthread

SRC = $(shell find . -type f -name "*.c")
CPP_SRC = $(shell find . -type f -name "*.cpp")
OBJ = $(patsubst %.c,%.o,$(SRC))
CPP_OBJ = $(patsubst %.cpp,%.o,$(CPP_SRC))
DEP = $(patsubst %.o,%.d,$(OBJ) $(CPP_OBJ))

TARGET = test_lvgl

all: $(OBJ) $(CPP_OBJ)
	g++ -o $(TARGET) $^ $(LDFLAGS)

clean:
	rm -rf $(TARGET) $(OBJ) $(CPP_OBJ) $(DEP)

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

%.o: %.cpp
	g++ $(CFLAGS) -c -o $@ $<

-include $(DEP)