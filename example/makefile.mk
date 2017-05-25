# mk file

# header search path
RPC_INCLUDE := -I ../

# source file
RPC_SRC := $(wildcard ../rpc/*.cpp)
RPC_SRC += $(wildcard ../rpc/basic/*.cpp)
RPC_SRC += $(wildcard ../rpc/frame/*.cpp)
RPC_SRC += $(wildcard ../rpc/interface/*.cpp)
RPC_SRC += $(wildcard ../rpc/thread/*.cpp)

