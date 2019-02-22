CC=clang++

VERSION=c++17
CFLAGS=-std=$(VERSION) -DNDEBUG
CFLAGS+= -O3 -march=native
CFLAGS+= -s -fno-stack-protector -fno-ident -fno-exceptions -fno-rtti -ffast-math
#CFLAGS+= -g
FILES=main.cpp

.PHONY: clean fclean re all

all: binary_search
	
binary_search: 
	$(CC) $(CFLAGS) $(FILES) -o binary_search 

fclean:
	rm -f binary_search

gen:
	cd ./generator;\
	echo "10000 1000 0.5"       | go run main.go > ../inp_low;\
	echo "1000000 100000 0.5"   | go run main.go > ../inp_mid;\
	echo "10000000 1000000 0.5" | go run main.go > ../inp_hi;\
	cd ..

re: fclean all