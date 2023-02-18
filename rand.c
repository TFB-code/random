#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

// nanohop waits for the monotonic clock to update.  Use between calls to
// a random number generator to reduce the chance of duplicate readings at
// the cost of performance
void nanohop() {

    struct timespec time;
    __pthread_clock_gettime(CLOCK_MONOTONIC,&time);

    long time1 = time.tv_nsec,time2 = time.tv_nsec;

    while (time1==time2) {
        __pthread_clock_gettime(CLOCK_MONOTONIC, &time);
        time2=time.tv_nsec;
    }
}

// random returns a random number between 0 and 1
float random() {

    struct timespec time;
    __pthread_clock_gettime(CLOCK_MONOTONIC,&time);

    char srand[10];
    char fsrand[10];
    sprintf( srand, "%ld", time.tv_nsec);

    int len=strlen(srand);
    if (len>2) {
        if (srand[len - 2] == '0') {
            srand[len - 2] = '\0';
        } else {
            if (srand[len - 1] == '0') {
                srand[len - 1] = '\0';
            }
        }
    }
    strrev(srand);

    sprintf(fsrand,"0.%s",srand);

    return atof(fsrand);
}

// rnd_ returns a simple random integer between 0 and num inclusive
int rnd_(int num) {
    num++;
    return num*random();
}

// rnd returns a random integer between 0 and num inclusive
int rnd(int num) {
    nanohop();
    num++;
    float rand=num*random();
    int result=rand;
    if (rand-result>0.5&&result<num) {result ++;}
    return result;
}