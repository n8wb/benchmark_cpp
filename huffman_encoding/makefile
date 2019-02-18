CC=g++-8

VERSION=c++17
CFLAGS=-std=$(VERSION) -DNDEBUG #-Wno-format -Wall 
CFLAGS+= -O3 -march=native
#CFLAGS+=-I/usr/local/include -I/usr/include

FILES=main.cpp

.PHONY: clean fclean re all

all: huffman_encoding
	
huffman_encoding: 
	$(CC) $(CFLAGS) $(FILES) -o huffman_encoding 

fclean:
	rm huffman_encoding

re: fclean all