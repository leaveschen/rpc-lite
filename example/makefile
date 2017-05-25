# rpc lite makefiel

# ------ mk file ------ #

include makefile.mk

# ------ build args ------ #

CC = clang-mp-4.0
CXX = clang++-mp-4.0
CFLAGS := -std=c++14 -g -Wall -pipe -fPIC -O2
CFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0 -fno-strict-aliasing

INCLUDE += $(RPC_INCLUDE)
SRC += $(RPC_SRC)

# ------ target ------ #

all:
	$(CXX) $(CFLAGS) $(INCLUDE) test.cc -o test

clean:
	rm -rf *.dSYM/
	rm -f test

