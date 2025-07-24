test: build/main.o build/rpc.o build/libdummy.a 
	gcc build/main.o build/rpc.o -I./include/ -L./build -ldummy -o build/test -g

#compile main.c
build/main.o: test_src/main.c 
	gcc -c test_src/main.c -I./include/ -o build/main.o -g


build/librpc.a: build/rpc.o 
	ar rcs build/librpc.a build/rpc.o

#compile rpc.c
build/rpc.o: src/rpc.c 
	gcc -c src/rpc.c -I./include/ -o build/rpc.o  -g


build/libdummy.a: build/dummy_example.o 
	ar rcs build/libdummy.a build/dummy_example.o 

build/dummy_example.o: dummy_src/example.c
	gcc -c dummy_src/example.c -o build/dummy_example.o  -g


clean: 
	rm build/dummy_example.o build/libdummy.a build/output.o build//main.o build/rpc.o
