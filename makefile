all:
	cd ./counter;make;mv libcounter.so ../libcounter.so
	cd ./sloppycounter;make;mv libsloppycounter.so ../libsloppycounter.so
	cd ./linklist;make;mv liblist.so ../liblist.so
	cd ./hash;make;mv libhash.so ../libhash.so
	gcc -o testfile ./test/test.c -lcounter -lsloppycounter -llist -lhash -lpthread -L. 
clean:
	cd ./counter;make clean
	cd ./sloppycounter;make clean
	cd ./linklist;make clean
	cd ./hash;make clean
	cd ./locks;rm chooselock.h.gch;
	rm libcounter.so;rm libhash.so;rm liblist.so;rm libsloppycounter.so;rm testfile
