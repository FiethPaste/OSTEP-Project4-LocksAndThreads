#ifndef CHOOSESTRUC_H_INCLUDED
#define CHOOSESTRUC_H_INCLUDED

#define COUNTER 1
#define SLOPPY_COUNTER 2
#define LINKLIST 3
#define HASH 4
#define CUR_STRUC 1
#define TIME 1000000
#define PNUM 20

#if CUR_STRUC == COUNTER
    #include "../counter/counter.h"
#elif CUR_STRUC == SLOPPY_COUNTER
    #include "../sloppycounter/sloppycounter.h"
#elif CUR_STRUC == LINKLIST
    #include "../linklist/linklist.h"
#else
    #include "../hash/hash.h"
#endif

#endif // CHOOSESTRUC_H_INCLUDED
