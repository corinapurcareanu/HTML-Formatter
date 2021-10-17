build: 
	gcc -Wall -g F_utils.c parsare.c F_aux.c  tema3.c -o tema3

clean: 
	rm -rf tema3
