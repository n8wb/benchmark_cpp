CC=clang++-8

VERSION=c++17
CFLAGS=-std=$(VERSION) -DNDEBUG #-Wno-format -Wall 
CFLAGS+= -O3 -march=native
#CFLAGS+=-I/usr/local/include -I/usr/include
CFLAGS+= -s  -fno-stack-protector 

FILES=main.cpp

.PHONY: clean fclean re all

all: huffman_encoding
	
huffman_encoding: 
	$(CC) $(CFLAGS) $(FILES) -o huffman_encoding 

fclean:
	rm huffman_encoding

gen:
	cd ./generator;\
	echo 10000    | go run main.go > ../inp_low;\
	echo 1000000  | go run main.go > ../inp_mid;\
	echo 10000000 | go run main.go > ../inp_hi;\
	cd ..;

re: fclean all