CC = g++
CFLAGS := -fPIC -Wall -Wextra -O3 -g
CFLAGS += -D_DEBUG_
LDFLAGS := -lpthread -lcurl

OBJS = libSample.o
LIB = libSample.a
LIB_NAME = libSample
SAMPLE_EXC = sample
SAMPLE_SRC = main.cpp
LIB_PATH = ./
INCLUDE_PATH = include/

all : $(LIB) $(SAMPLE_EXC)

%.o : %.cpp
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c $< -o $@ 

$(LIB) : $(OBJS)
	rm -f $@
	ar cr $@ $(OBJS)
	rm -f $(OBJS)

$(SAMPLE_EXC):
	$(CC) $(SAMPLE_SRC) $(LIB) -o $(SAMPLE_EXC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET) $(LIB) $(SAMPLE_EXC)
