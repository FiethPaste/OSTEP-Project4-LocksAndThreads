liblist.so:linklist.o
	gcc -shared -o liblist.so linklist.o

linklist.o:linklist.h linklist.c ../locks/mutex3.c ../locks/spinlock.c ../locks/chooselock.h ../locks/xchg.c ../locks/sys_futex.c
	gcc -c -fpic linklist.h linklist.c ../locks/mutex3.c ../locks/spinlock.c ../locks/chooselock.h ../locks/xchg.c ../locks/sys_futex.c -lpthread 

clean:
	rm linklist.h.gch;rm linklist.o;rm mutex2.o;rm mutex3.o;rm mutex4.o;rm spinlock.o;rm sys_futex.o;rm xchg.o
