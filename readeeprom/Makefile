CC = g++ -std=c++11
CFLAGS := -fPIC -Wall -Wextra -O3 -g
CFLAGS += -D_DEBUG_
LDFLAGS := -lTestOfBoard -lcrypto_64 -lcrypto -lpthread

SAMPLE_EXC = readEEPROM
SAMPLE_SRC = main.cpp
LIB_PATH = lib/

all : $(SAMPLE_EXC)

$(SAMPLE_EXC):
	$(CC) $(SAMPLE_SRC) -L$(LIB_PATH) -o $(SAMPLE_EXC) $(LDFLAGS)

clean:
	rm -f $(SAMPLE_EXC)
