a.out: main.o func_select.o pstring.o
	gcc -m32 -g -o a.out main.o func_select.o pstring.o 

main.o: main.c pstring.h
	gcc -m32 -g -c -o main.o main.c

func_select.o: func_select.s pstring.h
	gcc -m32 -g -c -o func_select.o func_select.s

pstring.o: pstring.s
	gcc -m32 -g -c -o pstring.o pstring.s	

clean:
	rm -f *.o a.out