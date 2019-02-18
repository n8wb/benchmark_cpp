CC=g++-8

INCLUDE=-Ilib/
VERSION=c++17

DFLAGS=-g
CFLAGS=$(DFLAGS) -std=$(VERSION) -Wall -Wextra -Werror $(EXTRA_ARGS)
CFLAGS+= -O3 -m64#Remove this flag for better cross machine compilation
CFLAGS+= -I/usr/local/include -I/usr/include

CMFLAGS = $(CFLAGS) -pthread -lboost_system -lboost_coroutine -lboost_thread

FILES=main.cpp

TEST_FILES=test/test.cpp

GENERIC_OBJ=$(foreach x, $(basename $(wildcard lib/generic/*.cpp)), $(x).o)

STATE_OBJ=$(foreach x, $(basename $(wildcard lib/state/*.cpp)), $(x).o)

LIB_OBJ=$(foreach x, $(basename $(wildcard lib/*.cpp)), $(x).o)

IMPL_OBJ=$(foreach x, $(basename $(wildcard lib/test/*.cpp)), $(x).o)

RPC_OBJ=$(foreach x, $(basename $(wildcard lib/rpc/*.cpp)), $(x).o)

RPC_HELPER_OBJ=$(foreach x, $(basename $(wildcard lib/rpc/*/*.cpp)), $(x).o)

STRUCT_OBJ=$(foreach x, $(basename $(wildcard lib/structs/*/*.cpp)), $(x).o)

TEST_OBJ=$(foreach x, $(basename $(wildcard test/src/*.cpp)), $(x).o)

INTERFACE_OBJ=$(foreach x, $(basename $(wildcard lib/interface/*.cpp)), $(x).o)
INTERFACE_OBJ+=$(foreach x, $(basename $(wildcard lib/interface/*/*.cpp)), $(x).o)

DATABASE_OBJ=$(foreach x, $(basename $(wildcard lib/database/*.cpp)), $(x).o)

RPC_OBJ+=$(RPC_HELPER_OBJ)

OBJECTS=$(LIB_OBJ) $(CLIB_OBJ) $(IMPL_OBJ) $(RPC_OBJ) $(STRUCT_OBJ) $(INTERFACE_OBJ) $(DATABASE_OBJ) $(STATE_OBJ) $(GENERIC_OBJ)

.PHONY: clean fclean re all

all: $(OBJECTS) rpc

objects: $(OBJECTS)
	
rpc: 
	$(CC) $(FILES) -o rpc  $(OBJECTS) $(CMFLAGS)

test: all $(TEST_OBJ) test-bin

test-bin:
	$(CC) $(TEST_FILES) -o rpc_test $(TEST_OBJ) $(OBJECTS) $(CMFLAGS)

clean: 
	rm -f $(OBJECTS)  $(TEST_OBJ)

fclean:
	rm -f rpc

rpc_clean:
	rm $(RPC_OBJ)

re: fclean all

$(LIB_OBJ): lib/%.o : lib/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(IMPL_OBJ): lib/test/%.o : lib/test/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(RPC_OBJ): lib/rpc/%.o : lib/rpc/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(STRUCT_OBJ): lib/structs/%.o : lib/structs/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(INTERFACE_OBJ): lib/interface/%.o : lib/interface/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ): test/src/%.o : test/src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(DATABASE_OBJ): lib/database/%.o : lib/database/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(STATE_OBJ): lib/state/%.o : lib/state/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(GENERIC_OBJ): lib/generic/%.o : lib/generic/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
