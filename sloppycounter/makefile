libsloppycounter.so:sloppycounter.o
	gcc -shared -o libsloppycounter.so sloppycounter.o

sloppycounter.o:sloppycounter.h sloppycounter.c ../locks/mutex3.c ../locks/spinlock.c ../locks/chooselock.h ../locks/xchg.c ../locks/sys_futex.c
	gcc -c -fpic sloppycounter.h sloppycounter.c ../locks/mutex3.c ../locks/spinlock.c ../locks/chooselock.h ../locks/xchg.c ../locks/sys_futex.c -lpthread 

clean:
	rm sloppycounter.h.gch;rm sloppycounter.o;rm mutex2.o;rm mutex3.o;rm mutex4.o;rm spinlock.o;rm sys_futex.o;rm xchg.o
