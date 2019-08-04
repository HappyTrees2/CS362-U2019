test: testme.c
	gcc -o testme testme.c -g -Wall -fprofile-arcs -ftest-coverage
	testme

clean: 
	rm -f testme *.gc*
