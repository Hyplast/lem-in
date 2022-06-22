NAME = lem_in

flags = -Wall -Wextra -Werror -g



compile:
	gcc -o $(NAME) $(flags) $(NAME).c

all: $(NAME)



clean:
	rm -f *.o *.d *.out

rebuild: clean
	make

fclean:
	rm -f *.o *.d *.out
	rm -f Makefile
	rm -f *.c *.h

