all: run


main.o: main.c
	clang -c -o main.o main.c

resources.o: resources.c
	clang -c -o resources.o resources.c

lexer.o: lexer.c
	clang -c -o lexer.o lexer.c

vector.o: vector.c
	clang -c -o vector.o vector.c

compiler_error.o: compiler_error.c
	clang -c -o compiler_error.o compiler_error.c

clean:
	rm *.o


a.out: main.o resources.o lexer.o vector.o compiler_error.o
	clang -v -o a.out main.o resources.o lexer.o vector.o compiler_error.o
	

build: a.out


run: a.out
	./a.out

