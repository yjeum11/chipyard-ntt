#include <inttypes.h>
#include <stdlib.h>
#include "rocc.h"
#define USE_ROCC
#include "multi-word/vhd128/vhd128.h"

int main() {
    uint128_t m = MODULUS;
    // 41538374868278621028243970639921153
    // 0x8000000000000 00000000005E0001
    // N = 10; 122 bits -> modulus
    uint64_t a_arr [] = {455333662575606846ULL, 5153218546387004957ULL, 1131560547825840217ULL, 17924790538551007214ULL, 522020843238499809ULL, 2462990123288075990ULL, 1020272225028617497ULL, 5001273086703436857ULL, 904279509577326203ULL, 11869200803368529633ULL, 232646445786432630ULL, 9716052183658065440ULL, 709384929503838142ULL, 4313023943571838851ULL, 556347282068515533ULL, 12806531270151132396ULL, 510387787250276456ULL, 217137843093062593ULL, 584283483357701210ULL, 4729461141359015700ULL};
    uint64_t b_arr [] = {183891191845911447ULL, 17412682013082121417ULL, 353637215703872467ULL, 1703829506495596229ULL, 793866542400794990ULL, 6135517859464665404ULL, 619300502795586487ULL, 17312428213747592495ULL, 703793535409475593ULL, 2457056326862964716ULL, 996037676574286231ULL, 11957412452116541152ULL, 720729944750716007ULL, 17620907602431889878ULL, 847029808101559426ULL, 5419051434938528272ULL, 1072838403577485006ULL, 14734744131830234573ULL, 1090153119713012640ULL, 4481808947799215998ULL};

    uint64_t time1, time2;

    uint64_t ah, al, bh, bl;
    uint128_t a, b, c, d;

    for (int i = 0; i < 10; i++) {
        ah = a_arr[2*i];
        al = a_arr[2*i+1];
        bh = b_arr[2*i];
        bl = b_arr[2*i+1];

        a = INT128(ah, al) % m;
        b = INT128(bh, bl) % m;

        asm volatile ("" ::: "memory");
        asm volatile (
                "rdcycle %0\n\t"
                : "=r" (time1));
        asm volatile ("" ::: "memory");
        c = submod128(a, b, m);
        asm volatile ("" ::: "memory");
        asm volatile (
                "rdcycle %0\n\t"
                : "=r" (time2));
        asm volatile ("" ::: "memory");
        // d = (a-b)%m;
        d = submod128_baseline(a, b, m);
        printf("time diff for sub = %ld\n", time2-time1);

        if (c != d) {
            printf("bad. ch = %lx, %lx\n", HI64(c), LO64(c));
            printf("dh = %lx, %lx", HI64(d), LO64(d));
            printf("\n");
            if (c > m) {
                printf("c > m\n");
            }
            return 1;
        }
    }
}
