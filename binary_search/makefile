CC=clang++

VERSION=c++17
CFLAGS=-std=$(VERSION) -DNDEBUG
CFLAGS+= -O2 -march=native
CFLAGS+= -s -fno-stack-protector -fno-ident -fno-exceptions -fno-rtti -ffast-math
#CFLAGS+= -g
FILES=main.cpp

.PHONY: clean fclean re all

all: binary_search
	
binary_search: 
	$(CC) $(CFLAGS) $(FILES) -o binary_search 

fclean:
	rm binary_search

re: fclean all