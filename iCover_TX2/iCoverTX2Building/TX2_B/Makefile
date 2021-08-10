Q               := @
CC		:= g++
#CC		:= $(CROSS_COMPILE)gcc	
SRCS            := $(wildcard *.cpp)
OBJS            := $(SRCS:.cpp=.o)
TARGET          := iCoverJS
LIBS			:= 
CFLAGS          += -Wall -Linclude
LDFLAGS         := -lTestOfBoard -lcrypto_64 -lcrypto -lpthread #$(LIBS) 
LIB_PATH 		:= lib/

.PHONY: all clean distclean	

all: .depend $(TARGET)

%.o: %.c Makefile
	$(Q)echo "  Compiling '$<' ..."
	$(Q)$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET): $(OBJS)
	$(Q)echo "  Building '$@' ..."
	$(Q)$(CC) -L $(LIB_PATH) -o $@ $(OBJS) $(LDFLAGS)

clean distclean: 
	$(Q)echo "  Cleaning '$(TARGET)' ..."
	$(Q)rm -f .depend *~ $(OBJS) $(TARGET) a.out*

.depend dep depend:
	$(Q)echo "  Generating '$@' ..."
	$(Q)$(CC) $(CFLAGS) -M *.cpp > $@

ifeq (.depend, $(wildcard .depend))
    include .depend
endif
