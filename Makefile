all:
	clang -Wall -Werror -o thread_fill -lpthread thread_fill.c
	clang -Wall -Werror -o thread_increment -lpthread thread_increment.c

clean:
	rm thread_fill thread_increment