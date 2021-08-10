CC = gcc
CFLAGS := -fPIC -Wall -Wextra -O3 -g
CFLAGS += -D_DEBUG_
LDFLAGS := -lpthread

OBJS = libATPlatform.o
LIB = libATPlatform.a
LIB_NAME = libATPlatform 
SAMPLE_EXC = UsingATPlatform
SAMPLE_SRC = main.c
LIB_PATH = ./
INCLUDE_PATH = include/
OUT_PATH = ./bin

all : $(LIB) $(SAMPLE_EXC)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c $< -o $(OUT_PATH)/$@ 

$(LIB) : $(OBJS)
	rm -f $(OUT_PATH)/$@
	ar cr $(OUT_PATH)/$@ $(OUT_PATH)/$(OBJS)
	rm -f $(OUT_PATH)/$(OBJS)

$(SAMPLE_EXC):
	$(CC) $(SAMPLE_SRC) $(OUT_PATH)/$(LIB) -o $(OUT_PATH)/$(SAMPLE_EXC) $(LDFLAGS)

clean:
	rm -f $(OUT_PATH)/$(OBJS) $(TARGET) $(OUT_PATH)/$(LIB) $(OUT_PATH)/$(SAMPLE_EXC)
