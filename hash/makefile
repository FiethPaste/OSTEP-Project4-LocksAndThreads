libhash.so:hash.o
	gcc -shared -o libhash.so hash.o

hash.o:hash.h hash.c ../locks/mutex3.c ../locks/spinlock.c ../locks/chooselock.h ../locks/xchg.c ../locks/sys_futex.c
	gcc -c -fpic hash.h hash.c ../locks/mutex3.c ../locks/spinlock.c ../locks/chooselock.h ../locks/xchg.c ../locks/sys_futex.c -lpthread 

clean:
	rm hash.h.gch;rm hash.o;rm mutex2.o;rm mutex3.o;rm mutex4.o;rm spinlock.o;rm sys_futex.o;rm xchg.o
