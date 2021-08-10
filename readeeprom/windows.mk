Q					:=@	
CC 					:=g++
SRCS_E    			:=encrypt_example.cpp
SRCS_D				:=decrypt_example.cpp
OBJECT_E			:=encrypt_example.o
OBJECT_D			:=decrypt_example.o
INCLUDE				:=include
LIB_PATH			:=../bin
LIB_INCLUDE			:=$(LIB_PATH)/$(INCLUDE)
OPENSSL_INCLUDE		:=../Build-OpenSSL-MinGW-64/$(INCLUDE)
OPENSSL_LIB			:=../Build-OpenSSL-MinGW-64/lib
CPPFLAGS 			:=-Wall -ggdb -I$(LIB_INCLUDE) -I$(OPENSSL_INCLUDE)
LIBS 				:=-lssl -lcrypto libcrypto.dll
LDFLAGS				:=-L$(OPENSSL_LIB) $(LIBS)
EXAMPLE_TARGET_E	:=encrypt_example 
EXAMPLE_TARGET_D	:=decrypt_example

ifeq ($(DEBUG), y)
	CFLAGS := $(CPPFLAGS) -DDEBUG
endif

.PHONY: all

all: clean $(EXAMPLE_TARGET_E) $(EXAMPLE_TARGET_D)

%.o: %.cpp
	$(Q)echo "  Compiling '$<' ..."
	$(Q)$(CC) -o $@ -c $< $(CPPFLAGS) 

$(EXAMPLE_TARGET_E):$(OBJECT_E)
	$(Q)$(CC) -o $@ $< $(LDFLAGS)

$(EXAMPLE_TARGET_D):$(OBJECT_D)
	$(Q)$(CC) -o $@ $< $(LDFLAGS)

clean:
	$(Q)$(RM) -f $(EXAMPLE_TARGET_E) $(EXAMPLE_TARGET_D)