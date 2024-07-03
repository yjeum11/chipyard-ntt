#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define N 8
#define USE_ROCC

#include "multi-word/rocc.h"

// #define DEBUG

#include "multi-word/vhd128/vhd128.h"

#define CHECK_MOD(_a, _comment) { \
    if (_a > MODULUS) { \
        printf(TO_STRING(_a) " bigger than mod after " _comment "\n"); \
    } \
}

__attribute__((noinline)) void ntt8bigint(uint128_t  *Y, uint128_t  *X, uint128_t modulus, uint128_t  *twiddles, uint128_t mu) {
    uint128_t s73, s74, s75, s76, s77, s78, s79, s80, 
            s81, s82, s83, s84, t87, t88, t89, t90, 
            t91, t92, t93, t94;
    printf("twiddles[1] = ");
    print_u128_u(twiddles[1]);
    printf("\nX[4] = ");
    print_u128_u(X[4]);
    printf("\n");
    s73 = mulmod128(twiddles[1], X[4], modulus, mu);
    CHECK_MOD(s73, "mul");
    printf("s73 =     ");
    print_u128_u(s73);
    printf("\n");
    printf("should be ");
    printf("\n");
    t87 = addmod128(X[0], s73, modulus); // c = a + b % m
    CHECK_MOD(t87, "add");
    t88 = submod128(X[0], s73, modulus); // c = a - b % m
    CHECK_MOD(t88, "sub");
    s74 = mulmod128(twiddles[1], X[5], modulus, mu);
    CHECK_MOD(s74, "mul");
    t89 = addmod128(X[1], s74, modulus);
    CHECK_MOD(t89, "add");
    t90 = submod128(X[1], s74, modulus);
    CHECK_MOD(t90, "sub");
    s75 = mulmod128(twiddles[1], X[6], modulus, mu);
    CHECK_MOD(s75, "mul");
    s76 = mulmod128(twiddles[2], addmod128(X[2], s75, modulus), modulus, mu);
    s77 = mulmod128(twiddles[3], submod128(X[2], s75, modulus), modulus, mu);
    s78 = mulmod128(twiddles[1], X[7], modulus, mu);
    s79 = mulmod128(twiddles[2], addmod128(X[3], s78, modulus), modulus, mu);
    s80 = mulmod128(twiddles[3], submod128(X[3], s78, modulus), modulus, mu);
    t91 = addmod128(t87, s76, modulus);
    t92 = submod128(t87, s76, modulus);
    t93 = addmod128(t88, s77, modulus);
    t94 = submod128(t88, s77, modulus);
    s81 = mulmod128(twiddles[4], addmod128(t89, s79, modulus), modulus, mu);
    s82 = mulmod128(twiddles[5], submod128(t89, s79, modulus), modulus, mu);
    s83 = mulmod128(twiddles[6], addmod128(t90, s80, modulus), modulus, mu);
    s84 = mulmod128(twiddles[7], submod128(t90, s80, modulus), modulus, mu);
    Y[0] = addmod128(t91, s81, modulus);
    Y[1] = submod128(t91, s81, modulus);
    Y[2] = addmod128(t92, s82, modulus);
    Y[3] = submod128(t92, s82, modulus);
    Y[4] = addmod128(t93, s83, modulus);
    Y[5] = submod128(t93, s83, modulus);
    Y[6] = addmod128(t94, s84, modulus);
    Y[7] = submod128(t94, s84, modulus);
}

// ----------------- host code for verification -----------------

__attribute__((noinline)) void verify(uint128_t * truth, uint128_t * obtained){
    int verified = 1;
    printf("Modulus  ");
    print_u128_u(MODULUS);
    printf("\n");
    for (int i = 0; i < N; i++){
        if (obtained[i] > MODULUS) {
            printf("bigger than modulus at %d\n", i);
            printf("Obtained ");
            print_u128_u(obtained[i]);
            printf("\n");
            verified = 0;
        } else if (obtained[i] != truth[i]) {
            printf("Error at %d\n", i);
            printf("Obtained ");
            print_u128_u(obtained[i]);
            printf("\nTruth    ");
            print_u128_u(truth[i]);
            printf("\n");
            verified = 0;
            //return;
        } else {
            printf("Correct at %d\n", i);
        }
    }
    if (verified)
      printf("\nVerified!\n");
}


int main(){

    uint128_t y[N];

    uint128_t mu = MU;
    uint128_t modulus = MODULUS;

    uint128_t twd_s[16] = {1055898684314591564, 711025607762871027, 966570013936180415, 6929421080235479996, 591350567062346513, 2021159029935434152, 687826829272817159, 9464065837175590288, 867798882079456885, 11995606456538430431, 664363147658901805, 17288154367051196830, 814030176194976011, 129506888771778232, 1149733277491081101, 10407251625223102527};
    uint128_t x_s[16] = {832137077598977201, 5633217820568833289, 837470512948776706, 11898998185116459593, 837013546926632267, 11890325367662713918, 997848201131024976, 16150054879108010656, 996420824442851916, 6533705180688641587, 854367316177507938, 2685403168274441061, 810015006183690113, 10939532673115793298, 691420179962120975, 15709810520805426527};
    uint128_t ver_s[16] = {1051263660585169989, 8697381581013653036, 868476041825480758, 12837081054297167495, 1063738294739221800, 8297360164457009044, 1110238199977756696, 17069659981464964462, 43201063616783133, 13727644356483739819, 1115180270952211684, 17798492622729705333, 388251434454588774, 10267676123459330065, 1016747654640604771, 11710678901773751906};

    uint128_t twd[8]; 
    uint128_t x[8];
    uint128_t ver[8];

    for(int i = 0; i < 8; i ++){
        twd[i] = INT128(twd_s[2*i], twd_s[2*i+1]);
        x[i] = INT128(x_s[2*i], x_s[2*i+1]);
        ver[i] = INT128(ver_s[2*i], ver_s[2*i+1]);
    }

    printf("Testing %d-point MP NTTs using %d-bit DBaseInt on CPU...\n", N, 128);

    // Executing kernel 
    //
    uint64_t time1, time2;

        asm volatile ("" ::: "memory");
        asm volatile (
                "rdcycle %0\n\t"
                : "=r" (time1));
        asm volatile ("" ::: "memory");
    ntt8bigint(y, x, modulus, twd, mu);
        asm volatile ("" ::: "memory");
        asm volatile (
                "rdcycle %0\n\t"
                : "=r" (time2));
        asm volatile ("" ::: "memory");

        printf("time diff for ntt = %ld\n", time2-time1);
    // Verification
    verify(ver, y);

}
