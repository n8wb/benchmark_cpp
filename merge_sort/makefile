#CC=g++-8
CC=clang++-8
VERSION=c++17
CFLAGS=-std=$(VERSION) -DNDEBUG #-Wno-format -Wall 
CFLAGS+= -O3 -march=native

CFLAGS+= -s  -fno-stack-protector 
FILES=main.cpp

.PHONY: clean fclean re all

all: merge_sort
	
merge_sort: 
	$(CC) $(CFLAGS) $(FILES) -o merge_sort 

fclean:
	rm -f merge_sort

gen:
	cd ./generator;\
	echo "10000"       | go run main.go > ../inp_low;\
	echo "1000000"   | go run main.go > ../inp_mid;\
	echo "10000000" | go run main.go > ../inp_hi;\
	cd ..

re: fclean all