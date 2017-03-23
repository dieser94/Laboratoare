CC=gcc
FLAGS= -Wall

all : 1 2 3 bonus

1 : 1.c
	$(CC) $(FLAGS) 1.c -o 1

2 : 2.c
	$(CC) $(FLAGS) 2.c -o 2

bonus : bonus.c
	$(CC) $(FLAGS) bonus.c -o bonus

3 : 3.c
	$(CC) $(FLAGS) 3.c -o 3

.PHONY : clean
clean :
	rm -rf 1 2 3 bonus
