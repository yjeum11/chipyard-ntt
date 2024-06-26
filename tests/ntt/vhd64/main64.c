#include <stdio.h>
#include <stdint.h>

#include "vhd64.h"

#define SHIFT		4
#define CTRL		1
#define MBITS		60
#define MODULUS		1152921504606846577ULL
#define MU			9223372036854779000ULL


__uint64_t addmod(__uint64_t a, __uint64_t b, __uint64_t m) {
#ifdef _HAS_CFLAG
	_Bool cflag;
	__uint64_t c;
	_addqc(c, cflag, a, b);
	return _csubq(c, m, cflag);
#else
	return _csubq(_addq(a, b), m, _carry_addq(a, b));
#endif
}

__uint64_t submod(__uint64_t a, __uint64_t b, __uint64_t m) {
#ifdef _HAS_CFLAG
	_Bool cflag;
	__uint64_t c;
	_subqc(c, cflag, a, b);
	return _caddq(c, m, cflag);
#else
	return _caddq(_subq(a, b), m, _carry_subq(a, b));
#endif
}


__uint64_t mulmod(__uint64_t a, __uint64_t b, __uint64_t m, __uint64_t mu) {
	__uint64_t ql, qh, tmpl, qqml, qq, qmh, c;

#ifdef _HAS_MULDQQQ
	_muldqqq(qh, ql, a, b);
#else
	ql = _mulq(a, b);
	qh = _mulhiq(a, b);
#endif
	tmpl = ql;

	ql = _shrqdq(qh, ql, MBITS - 2);
	qh = _shrq(qh, MBITS - 2);

	qmh = _addq(_mulhiq(ql, mu), _mulq(qh, mu));
	qq = _shrq(qmh, 1);

	qqml = _mulq(qq, m);
	tmpl = _subq(tmpl, qqml);
	return _csubq(tmpl, m, _cmpgeq(tmpl, m));
}


int main() {
	__uint64_t a = 0x123456789ABCDEFULL,
		b = 0xFEDCBA0987654321ULL,
		m = MODULUS,
		mu = MU,
		u = a % m,
		v = b % m,
		c, d, e, f, g,
		w, x, z;
	_Bool p, q, r;

	c = _shrqdq(a, b, SHIFT);
	d = _mulq(a, b);
	e = _mulhiq(a, b);
	f = _caddq(a, b, CTRL);
	g = _csubq(a, b, CTRL);

	p = _carry_addq(a, b);
	q = _carry_subq(a, b);
	r = _cmpgeq(a, b);

	w = addmod(u, v, m);
	x = submod(u, v, m);
	z = mulmod(u, v, m, mu);

	printf("_shrqdq(0x%llX, 0x%llX, %hhu) = 0x%llX\n", a, b, SHIFT, c);
	printf("_mulq(0x%llX, 0x%llX) = 0x%llX\n", a, b, d);
	printf("_mulhiq(0x%llX, 0x%llX) = 0x%llX\n", a, b, e);
	printf("_caddq(0x%llX, 0x%llX, %hhu) = 0x%llX\n", a, b, CTRL, f);
	printf("_csubq(0x%llX, 0x%llX, %hhu) = 0x%llX\n", a, b, CTRL, g);

	printf("_carry_add(0x%llX, 0x%llX) = %hhu\n", a, b, p);
	printf("_carry_sub(0x%llX, 0x%llX) = %hhu\n", a, b, q);
	printf("_cmpgeq(0x%llX, 0x%llX) = %hhu\n", a, b, r);

	printf("0x%llX %% 0x%llX = 0x%llX\n", a, m, u);
	printf("0x%llX %% 0x%llX = 0x%llX\n", b, m, v);
	printf("(0x%llX + 0x%llX) %% 0x%llX = 0x%llX\n", u, v, m, w);
	printf("(0x%llX - 0x%llX) %% 0x%llX = 0x%llX\n", u, v, m, x);
	printf("(0x%llX * 0x%llX) %% 0x%llX = 0x%llX\n", u, v, m, z);
}

