all: dummy_example 
	gcc -c src/rpc.c -I./include/ -L. -ldummy -o output.o

dummy_example: 
	gcc dummy_src/example.c -o dummy_example.o 
	ar rcs libdummy.a dummy_example.o
clean: 
	rm dummy_example.o libdummy.a output.o
