test: test_src/main.o src/rpc.o libdummy.a 
	gcc test_src/main.o src/rpc.o -I./include/ -L. -ldummy -o test -g

#compile main.c
test_src/main.o: test_src/main.c 
	gcc -c test_src/main.c -I./include/ -o test_src/main.o -g

#compile rpc.c
src/rpc.o: src/rpc.c 
	gcc -c src/rpc.c -I./include/ -o src/rpc.o  -g


libdummy.a: dummy_example.o 
	ar rcs libdummy.a dummy_example.o 

dummy_example.o: dummy_src/example.c
	gcc -c dummy_src/example.c -o dummy_example.o  -g


clean: 
	rm dummy_example.o libdummy.a output.o test_src/main.o src/rpc.o
