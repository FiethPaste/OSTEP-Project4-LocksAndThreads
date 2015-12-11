libcounter.so:counter.o
	gcc -shared -o libcounter.so counter.o

counter.o:counter.h counter.c ../locks/mutex3.c ../locks/spinlock.c ../locks/chooselock.h ../locks/xchg.c ../locks/sys_futex.c
	gcc -c -fpic counter.h counter.c ../locks/mutex3.c ../locks/spinlock.c ../locks/chooselock.h ../locks/xchg.c ../locks/sys_futex.c -lpthread 

clean:
	rm counter.h.gch;rm counter.o;rm mutex2.o;rm mutex3.o;rm mutex4.o;rm spinlock.o;rm sys_futex.o;rm xchg.o
