#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "vhd128/vhd128.h"
#define N 8

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
