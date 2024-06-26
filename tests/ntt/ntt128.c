#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define N 8

#include "vhd128/vhd128.h"

__attribute__((noinline)) void ntt8bigint(uint128_t  *Y, uint128_t  *X, uint128_t modulus, uint128_t  *twiddles, uint128_t mu) {
    uint128_t s73, s74, s75, s76, s77, s78, s79, s80, 
            s81, s82, s83, s84, t87, t88, t89, t90, 
            t91, t92, t93, t94;
    s73 = mulmod128(twiddles[1], X[4], modulus, mu);
    t87 = addmod128(X[0], s73, modulus); // c = a + b % m
    t88 = submod128(X[0], s73, modulus); // c = a - b % m
    s74 = mulmod128(twiddles[1], X[5], modulus, mu);
    t89 = addmod128(X[1], s74, modulus);
    t90 = submod128(X[1], s74, modulus);
    s75 = mulmod128(twiddles[1], X[6], modulus, mu);
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
    for (int i = 0; i < N; i++){
        if (obtained[i] != truth[i]) {
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

    uint64_t uptwd[2*N] = {1107468979794352ULL, 6124012274588012912ULL, 1794037998336679ULL, 18349672013992343267ULL, 597758336841380ULL, 12220332284926137603ULL, 626252333594259ULL, 9529838049678440770ULL, 2157721302853290ULL, 5789448867364500140ULL, 1076818653734551ULL, 16496738273973212157ULL, 791168531883964ULL, 10519764176491036486ULL, 1425660382861813ULL, 6368653271593428950ULL};
    uint64_t upx[2*N] = {2072619743648984ULL, 1174316001554398513ULL, 970669643717545ULL, 13792331081875866075ULL, 2011029543516884ULL, 12973929413704199390ULL, 1797333132607212ULL, 18325247463772350639ULL, 2057711242332268ULL, 18288287252645839511ULL, 1416838974927711ULL, 14790018937092230040ULL, 1010372367505218ULL, 8533883250531886584ULL, 1120774964508559ULL, 11200049924888057394ULL};
    uint64_t upy[2*N] = {2084257051095537ULL, 7029550207955506566ULL, 1792861369664923ULL, 366244537012160122ULL, 1498182373957841ULL, 10837998621593354740ULL, 1815177947853493ULL, 13523700647414230514ULL, 417087286019338ULL, 4242306121123920291ULL, 1837418803814827ULL, 17673280050360584326ULL, 2231530524133368ULL, 18244427004021248763ULL, 400842965282045ULL, 11263997117780068476ULL};

    uint128_t x[N], twd[N], y_t[N];

    for (int i=0; i < N; i++) {
        x[i] = INT128(upx[2*i], upx[2*i+1]);
        y_t[i] = INT128(upy[2*i], upy[2*i+1]);
        twd[i] = INT128(uptwd[2*i], uptwd[2*i+1]);
    }

    printf("Testing %d-point MP NTTs using %d-bit DBaseInt on CPU...\n", N, 128);

    // Executing kernel 
    ntt8bigint(y, x, modulus, twd, mu);

    // Verification
    verify(y_t, y);

}
