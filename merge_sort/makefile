#CC=g++-8
CC=clang++
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

re: fclean all