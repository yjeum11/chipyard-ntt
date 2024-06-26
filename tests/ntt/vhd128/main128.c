#include <stdio.h>
#include <stdint.h>

#include "../vhd64/vhd64.h"

#define USE_VHD64
//#define USE_INT128
#define USE_KARATSUBA
#define USE_MBIT124

// typedef __uint128_t uint128_t;
typedef unsigned __int128 uint128_t;

#define LO64(val)           ((uint64_t)(val))
#define HI64(val)           ((uint64_t)((val) >> 64))
#define INT128(hi, lo)      (((uint128_t)(hi) << 64) | (uint128_t)(lo))

#ifdef USE_MBIT124
// #define MBITS 124
// //  MODULUS		21267647932558653966460912964485513157 = 2^124-59
// //              0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC5
// #define MODULUS INT128(0xFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFC5ULL)        
// //  MU			170141183460469231731687303715884106200
// //              0x800000000000000000000000000001D8
// #define MU      INT128(0x8000000000000000ULL, 0x1D8ULL)
#define MBITS 116
//  MODULUS		41538374868278621028243970639921153
//              0x800000000000000000000005E0001
#define MODULUS INT128(0x8000000000000ULL, 0x00000000005E0001ULL)        
//  MU			1329227995784915872903807060083212256
//              0xFFFFFFFFFFFFFFFFFFFFFFF43FFFE0
#define MU      INT128(0xFFFFFFFFFFFFFF, 0xFFFFFFFFF43FFFE0)
#else

#define MBITS 116
//  MODULUS		41538374868278621028243970639921153
//              0x800000000000000000000005E0001
#define MODULUS INT128(0x8000000000000ULL, 0x00000000005E0001ULL)        
//  MU			1329227995784915872903807060083212256
//              0xFFFFFFFFFFFFFFFFFFFFFFF43FFFE0
#define MU      INT128(0xFFFFFFFFFFFFFF, 0xFFFFFFFFF43FFFE0)
#endif

#ifdef USE_VHD64

uint128_t addmod128(uint128_t a, uint128_t b, uint128_t m) {
    uint64_t cl, ch, el, eh, ml, mh;
    _Bool elc, ehc, clc, ctrl;

    ml = LO64(m);
    mh = HI64(m);
    _addqc(el, elc, LO64(a), LO64(b));
    _adcqc(eh, ehc, HI64(a), HI64(b), elc);
    _cncmpgq(eh, mh, ehc, ehc);
    _cncmplq(eh, mh, ehc, ctrl = ehc);
    _cncmpgq(el, ml, ctrl, ehc);
    _csubqc(cl, clc, el, ml, ctrl);
    ch = _csbcq(eh, mh, clc, ctrl);

    printf("using this one\n");
    uint128_t result = INT128(ch, cl);
    if (result > m) {
      printf("result is bigger than modulus\n");
    }
    return INT128(ch, cl);
}

uint128_t submod128(uint128_t a, uint128_t b, uint128_t m) {
	uint64_t cl, ch, el, eh, ml, mh;
	_Bool elc, ehc, clc, ctrl;

	ml = LO64(m);
	mh = HI64(m);
	_subqc(el, elc, LO64(a), LO64(b));
	_sbcqc(eh, ehc, HI64(a), HI64(b), elc);
	_cncmpneq(eh, mh, ehc, ctrl = ehc);
	_cncmpeq(el, ml, ctrl, ehc);
    _caddqc(cl, clc, el, ml, ctrl);
	ch = _cadcq(eh, mh, clc, ctrl);
	return INT128(ch, cl);
}

#ifdef USE_KARATSUBA
void mul128(uint128_t* ch, uint128_t* cl, uint128_t a, uint128_t b) {
    uint64_t al, ah, bl, bh, clh, chl, chh,
        ul, vl, xl, xh, xc, xh1, xh2, xh2a, xh2b,
        yh, yl, zh, zl, qh, ql, rl, qh1, rh, wl, wh, xca, xcb;
    _Bool uc, vc, qc1, qc, rlc, rc, rc1, rc2, clc, wlc, chlc, xc1, xc2, xc3;

    al = LO64(a);
    ah = HI64(a);
    bl = LO64(b);
    bh = HI64(b);

    _addqc(ul, uc, ah, al);
    _addqc(vl, vc, bh, bl);
    _muldqqq(xh1, xl, ul, vl);
    xh2a = _czeroq(vl, uc);
    xh2b = _czeroq(ul, vc);
    _addqc(xh2, xc1, xh2a, xh2b);
    xc2 = _andb(uc, vc);
    _addqc(xh, xc3, xh1, xh2);
    xca = _cvtbq(xc1);
    xcb = _cincq(xca, xc2);
    xc = _cincq(xcb, xc3);
    _muldqqq(yh, yl, ah, bh);
    _muldqqq(zh, zl, al, bl);
    _addqc(ql, qc1, yl, zl);
    _adcqc(qh, qc, yh, zh, qc1);
    _subqc(rl, rlc, xl, ql);
    _sbcqc(rh, rc1, xh, qh, rlc);
    rc2 = _cdecq(xc, qc);
    rc = _cdecq(rc2, rc1);
    _addqc(clh, clc, zh, rl);
    _cincqc(wl, wlc, rh, clc);
    wh = _cincq(rc, wlc);
    _addqc(chl, chlc, yl, wl);
    chh = _adcq(yh, wh, chlc);

    *ch = INT128(chh, chl);
    *cl = INT128(clh, zl);
}

uint128_t mulhi128(uint128_t a, uint128_t b) {
    uint64_t al, ah, bl, bh, chl, chh,
        ul, vl, xl, xh, xc, xh1, xh2, xh2a, xh2b,
        yh, yl, zh, zl, qh, ql, rl, rh, wl, wh, xca, xcb;
    _Bool uc, vc, qc1, qc, rlc, rc, rc1, rc2, clc, wlc, chlc, xc1, xc2, xc3;

    al = LO64(a);
    ah = HI64(a);
    bl = LO64(b);
    bh = HI64(b);

    _addqc(ul, uc, ah, al);
    _addqc(vl, vc, bh, bl);
    _muldqqq(xh1, xl, ul, vl);
    xh2a = _czeroq(vl, uc);
    xh2b = _czeroq(ul, vc);
    _addqc(xh2, xc1, xh2a, xh2b);
    xc2 = _andb(uc, vc);
    _addqc(xh, xc3, xh1, xh2);
    xca = _cvtbq(xc1);
    xcb = _cincq(xca, xc2);
    xc = _cincq(xcb, xc3);
    _muldqqq(yh, yl, ah, bh);
    _muldqqq(zh, zl, al, bl);
    _addqc(ql, qc1, yl, zl);
    _adcqc(qh, qc, yh, zh, qc1);
    _subqc(rl, rlc, xl, ql);
    _sbcqc(rh, rc1, xh, qh, rlc);
    rc2 = _cdecq(xc, qc);
    rc = _cdecq(rc2, rc1);
    clc = _carry_addq(zh, rl);
    _cincqc(wl, wlc, rh, clc);
    wh = _cincq(rc, wlc);
    _addqc(chl, chlc, yl, wl);
    chh = _adcq(yh, wh, chlc);

    return INT128(chh, chl);
}

#else

void mul128(uint128_t* ch, uint128_t* cl, uint128_t a, uint128_t b) {
    uint64_t al, ah, bl, bh, cll, clh, chl, chh, cxl, cxh, albll, alblh, albhl, albhh, ahblh, ahbll, ahbhh, ahbhl, cx2l, cx2h, chxl, chxh;
    _Bool cxc, cx2c, chxc;
    uint128_t albl, albh, ahbl, ahbh, cx, cx2, chx;

    al = LO64(a);
    ah = HI64(a);
    bl = LO64(b);
    bh = HI64(b);

    _muldqqq(alblh, albll, al, bl);
    _muldqqq(albhh, albhl, al, bh);
    _muldqqq(ahblh, ahbll, ah, bl);
    _muldqqq(ahbhh, ahbhl, ah, bh);
    _addqc(cxl, cxc, albhl, ahbll);
    cxh = _adcq(albhh, ahblh, cxc);
    _addqc(cx2l, cx2c, cxl, alblh);
    cx2h = _cincq(cxh, cx2c);
    _addqc(chxl, chxc, ahbhl, cx2h);
    chxh = _cincq(ahbhh, chxc);

    *ch = INT128(chxh, chxl);
    *cl = INT128(cx2l, albll);
}

uint128_t mulhi128(uint128_t a, uint128_t b) {
    uint64_t al, ah, bl, bh, cxl, cxh, alblh, albhl, albhh, ahblh, ahbll, ahbhh, ahbhl, cx2h, chxl, chxh;
    _Bool cxc, cx2c, chxc;

    al = LO64(a);
    ah = HI64(a);
    bl = LO64(b);
    bh = HI64(b);

    alblh = _mulhiq(al, bl);
    _muldqqq(albhh, albhl, al, bh);
    _muldqqq(ahblh, ahbll, ah, bl);
    _muldqqq(ahbhh, ahbhl, ah, bh);
    _addqc(cxl, cxc, albhl, ahbll);
    cxh = _adcq(albhh, ahblh, cxc);
    cx2c = _carry_addq(cxl, alblh);
    cx2h = _cincq(cxh, cx2c);
    _addqc(chxl, chxc, ahbhl, cx2h);
    chxh = _cincq(ahbhh, chxc);

    return INT128(chxh, chxl);
}
#endif

uint128_t mullo128(uint128_t a, uint128_t b) {
    uint64_t al, ah, bl, bh, cxl, albll, alblh, albhl, ahbll, cx2l;
    _Bool cxc, cx2c, chxc;

    al = LO64(a);
    ah = HI64(a);
    bl = LO64(b);
    bh = HI64(b);

    _muldqqq(alblh, albll, al, bl);
    albhl = _mulq(al, bh);
    ahbll = _mulq(ah, bl);
    cxl = _addq(albhl, ahbll);
    cx2l = _addq(cxl, alblh);

    return INT128(cx2l, albll);;
}

#ifdef USE_MBIT124
uint128_t mulmod128(uint128_t a, uint128_t b, uint128_t m, uint128_t mu) {
    uint128_t ql, qh, qqml, qq, qmh1;
    uint64_t qmhh, qmhl, qmh1h, qmh1l, qmh2h, qmh2l, qqh, qql, tmpll, tmplh, qqmll, qqmlh, mh, ml, cl, ch, qhh, qhl, qlh, qll, mul;
    _Bool cc, qmhc, tmplc, ccc, clc;

    // no-ops
    mh = HI64(m);
    ml = LO64(m);
    mul = LO64(mu);
    // mul128
    mul128(&qh, &ql, a, b);
    // no-ops
    qhh = HI64(qh);
    qhl = LO64(qh);
    qlh = HI64(ql);
    qll = LO64(ql);
    // tmpl = ql;
    tmplh = qlh;
    tmpll = qll;
    // ql1 = ql >> (MBITS - 2);
    // ql2 = qh << (128 - (MBITS - 2));
    // ql = ql2 | ql1;
    qll = _shrqdq(qhl, qlh, MBITS - 2 - 64);
    qlh = _shrqdq(qhh, qhl, MBITS - 2 - 64);
    // qh = qh >> (MBITS - 2);
    qhl = _shrq(qhh, MBITS - 2 - 64);
    // no-ops
    ql = INT128(qlh, qll);
    // mulhi128
    qmh1 = mulhi128(ql, mu);
    _muldqqq(qmh2h, qmh2l, qhl, mul);
    // no-ops
    qmh1h = HI64(qmh1);
    qmh1l = LO64(qmh1);
    // qmh = qmh1 + qmh2;
    _addqc(qmhl, qmhc, qmh1l, qmh2l);
    qmhh = _adcq(qmh1h, qmh2h, qmhc);
    // qq = qmh >> 1;
    qql = _shrqdq(qmhh, qmhl, 1);
    qqh = _shrq(qmhh, 1);
    // mullo128
    qq = INT128(qqh, qql);
    qqml = mullo128(qq, m);
    qqmlh = HI64(qqml);
    qqmll = LO64(qqml);
    // tmpl = tmpl - qqml;
    _subqc(tmpll, tmplc, tmpll, qqmll);
    tmplh = _sbcq(tmplh, qqmlh, tmplc);
    // cc = (tmpl < m); => tmpl - m has carry
    ccc = _carry_subq(tmpll, ml);
    cc = _carry_sbcq(tmplh, mh, ccc);
    //c = cc ? tmpl : tmpl - m;
    _cnsubqc(cl, clc, tmpll, ml, cc);
    ch = _cnsbcq(tmplh, mh, clc, cc);
    //return c;
    return INT128(ch, cl);
}
#endif
#else
#ifdef USE_INT128

uint128_t addmod128(uint128_t a, uint128_t b, uint128_t m) {
    _Bool c3, c4, c5, i14;
    uint64_t d4, d6, t18, t19, al, ah, bl, bh, cl, ch, ml, mh, s17, s17a;
    uint128_t ax, s16, s18, s18a, cx, dx, c;

    // no-ops
    al = (uint64_t)(a);
    ah = (uint64_t)(a >> 64);
    bl = (uint64_t)(b);
    bh = (uint64_t)(b >> 64);
    ml = (uint64_t)(m);
    mh = (uint64_t)(m >> 64);

    // add + carry flag
    s16 = ((uint128_t)al) + ((uint128_t)bl);
    t18 = (uint64_t)s16;
    c3 = (s16 >> 64) & 0x1;
    // adc + carry flag
    s18 = ((uint128_t)ah) + ((uint128_t)bh) + ((uint128_t)c3);
    t19 = (uint64_t)s18;
    c4 = (s18 >> 64) & 0x1;
    // no-op
    cx = (((uint128_t)t19) << 64) | ((uint128_t)t18);
    // sub + carry flag
    ax = ((uint128_t)ml) - ((uint128_t)t18);
    s17a = (uint64_t)ax;
    c5 = (_Bool)(ax >> 64) & 0x1;
    // neg
    d4 = -s17a;
    // sub
    d6 = t19 - mh;
    // no-op
    dx = (((uint128_t)d6) << 64) | ((uint128_t)d4);
    // sbc + carry flag
    s18a = ((uint128_t)mh) - ((uint128_t)t19) - ((uint128_t)c5);
    i14 = (_Bool)(s18a >> 64) & 0x1;
    // cmov + cmov
    c = i14 ? dx : cx;

    return c;
}

uint128_t submod128(uint128_t a, uint128_t b, uint128_t m) {
    _Bool c1, c3, i28, q1, q2;
    uint64_t d1, d2, d3, t28, t29, t30, al, ah, bl, bh, cl, ch, ml, mh;
    uint128_t s16, s17, s18, cx, cx2, c;

    // no-ops
    al = (uint64_t)(a);
    ah = (uint64_t)(a >> 64);
    bl = (uint64_t)(b);
    bh = (uint64_t)(b >> 64);
    ml = (uint64_t)(m);
    mh = (uint64_t)(m >> 64);

    // sub + carry flag
    s16 = ((uint128_t)al) - ((uint128_t)bl);
    t30 = (uint64_t)s16;
    c1 = (s16 >> 64) & 0x1;
    // sbc + carry flag
    s17 = ((uint128_t)ah) - ((uint128_t)bh) - c1;
    t29 = (uint64_t)s17;
    i28 = (s17 >> 64) & 0x1;
    // no-op
    cx = (((uint128_t)t29) << 64) | ((uint128_t)t30);
    // adc + add
    cx2 = cx + m;
    // cmov + cmov
    c = i28 ? cx2 : cx;

    return c;
}

void mul128(uint128_t* ch, uint128_t* cl, uint128_t a, uint128_t b) {
    uint64_t al, ah, bl, bh, cll, clh, chl, chh, cxl;
    uint128_t albl, albh, ahbl, ahbh, cx, cx2, chx;

    // no-ops
    al = (uint64_t)(a);
    ah = (uint64_t)(a >> 64);
    bl = (uint64_t)(b);
    bh = (uint64_t)(b >> 64);

    // widening mult
    albl = ((uint128_t)al) * ((uint128_t)bl);
    // widening mult
    albh = ((uint128_t)al) * ((uint128_t)bh);
    // widening mult
    ahbl = ((uint128_t)ah) * ((uint128_t)bl);
    // widening mult
    ahbh = ((uint128_t)ah) * ((uint128_t)bh);

    // adc + add
    cx = albh + ahbl;
    // adc/cinc + add
    cx2 = cx + (albl >> 64);
    // adc/cinc + add
    chx = ahbh + (cx2 >> 64);

    // no-ops
    cll = (uint64_t)albl;
    clh = (uint64_t)cx2;
    *ch = chx;
    *cl = (((uint128_t)clh) << 64) | ((uint128_t)cll);
}

uint128_t mullo128(uint128_t a, uint128_t b) {
    uint64_t al, ah, bl, bh, cll, clh, cx, cx2, albhl, ahbll;
    uint128_t albl, cl;

    // no-ops
    al = (uint64_t)(a);
    ah = (uint64_t)(a >> 64);
    bl = (uint64_t)(b);
    bh = (uint64_t)(b >> 64);

    // widening mult
    albl = ((uint128_t)al) * ((uint128_t)bl);
    // mult
    albhl = al * bh;
    // mult
    ahbll = ah * bl;
    // add
    cx = albhl + ahbll;
    // add
    cx2 = cx + (albl >> 64);

    // no-ops
    cll = (uint64_t)albl;
    clh = (uint64_t)cx2;
    cl = (((uint128_t)clh) << 64) | ((uint128_t)cll);
    return cl;
}

uint128_t mulhi128(uint128_t a, uint128_t b) {
    uint64_t al, ah, bl, bh, cll, clh, chl, chh, cxl, cx2h, alblh;
    uint128_t albh, ahbl, ahbh, cx, cx2, chx, ch;

    // no-ops
    al = (uint64_t)(a);
    ah = (uint64_t)(a >> 64);
    bl = (uint64_t)(b);
    bh = (uint64_t)(b >> 64);

    // mulhi
    alblh = (((uint128_t)al) * ((uint128_t)bl)) >> 64;
    // widening mult
    albh = ((uint128_t)al) * ((uint128_t)bh);
    // widening mult
    ahbl = ((uint128_t)ah) * ((uint128_t)bl);
    // widening mult
    ahbh = ((uint128_t)ah) * ((uint128_t)bh);

    // adc + add
    cx = albh + ahbl;
    // adc/cinc + add
    cx2 = cx + alblh;
    cx2h = cx2 >> 64;
    // adc/cinc + add
    chx = ahbh + cx2h;

    // no-ops
    return chx;
}


#ifdef USE_MBIT124
uint128_t mulmod128(uint128_t a, uint128_t b, uint128_t m, uint128_t mu) {
    uint128_t ql, qh, tmpl, qqml, qq, qmh, c, qmh1, ql1, ql2;
    uint64_t qhq, qmh2;
    _Bool cc;

    mul128(&qh, &ql, a, b);
    tmpl = ql;

    // shr + shrc
    ql1 = ql >> (MBITS - 2);
    // shl + shlc
    ql2 = qh << (128 - (MBITS - 2));
    // or + or
    ql = ql2 | ql1;
    // shr + shrc
    qhq = (uint64_t)(qh >> (MBITS - 2));

    qmh1 = mulhi128(ql, mu);
    // mul
    qmh2 = qhq * LO64(mu);

    // add + adc
    qmh = qmh1 + qmh2;
    //srh + shrc
    qq = qmh >> 1;

    qqml = mullo128(qq, m);

    // sub + subc
    tmpl = tmpl - qqml;
    // sub + subc
    cc = (tmpl < m);
    // cmov + cmov
    c = cc ? tmpl : tmpl - m;

    return c;
}
#endif
#else

uint128_t addmod128(uint128_t a, uint128_t b, uint128_t m) {
    _Bool a31, a34, a35, a38, a41, a43, a44, b1, c1, c2, i27, i28, q1, q2, q3, q4;
    uint64_t a32, a36, a39, a47, a49, a51, d1, d2, d3, t28, t29, t30, al, ah, bl, bh, cl, ch, ml, mh;

    al = LO64(a);
    ah = HI64(a);
    bl = LO64(b);
    bh = HI64(b);
    ml = LO64(m);
    mh = HI64(m);
    t30 = al + bl;
    q1 = (t30 < al);
    q2 = (t30 < bl);
    c1 = q1 || q2;
    t28 = ah + bh;
    t29 = t28 + c1;
    q3 = (t29 <= ah);
    q4 = (t29 <= bh);
    c2 = q3 || q4;
    a31 = (mh < t29);
    a35 = (mh == t29);
    a38 = (ml < t30);
    a34 = (a35 && a38);
    i27 = (a31 || a34);
    a41 = (0 < c2);
    a44 = (c2 == 0);
    a43 = (a44 && i27);
    i28 = (a41 || a43);
    d1 = t30 - ml;
    b1 = (t30 < ml);
    d2 = t29 - mh;
    d3 = d2 - b1;
    ch = i28 ? d3 : t29;
    cl = i28 ? d1 : t30;
    return INT128(ch, cl);
}


uint128_t submod128(uint128_t a, uint128_t b, uint128_t m) {
    _Bool c1, c3, i28, q1, q2;
    uint64_t d1, d2, d3, t28, t29, t30, al, ah, bl, bh, cl, ch, ml, mh;

    al = LO64(a);
    ah = HI64(a);
    bl = LO64(b);
    bh = HI64(b);
    ml = LO64(m);
    mh = HI64(m);
    t30 = al - bl;
    c1 = (bl > al);
    t28 = bh + c1;
    t29 = ah - t28;
    i28 = (t28 > ah);
    d1 = t30 + ml;
    q1 = (d1 < t30);
    q2 = (d1 < ml);
    c3 = q1 || q2;
    d2 = t29 + c3;
    d3 = d2 + mh;
    ch = i28 ? d3 : t29;
    cl = i28 ? d1 : t30;
    return INT128(ch, cl);
}


void mul64(uint64_t* ch, uint64_t* cl, uint64_t a, uint64_t b) {
    uint64_t al, ah, bl, bh, c1, c2, cc, cc1, cx, cxl, ch1, ch2, ch3, cl1, cl1h, cc2, cc1a, cc1b, ch11, cha;

    al = a & 0xFFFFFFFF;
    ah = a >> 32;
    bl = b & 0xFFFFFFFF;
    bh = b >> 32;

    c1 = ah * bl;
    c2 = al * bh;
    cx = c1 + c2;
    cc1a = (cx < c1);
    cc1b = (cx < c2);
    cc1 = cc1a || cc1b;
    ch1 = ah * bh;
    ch2 = cx >> 32;
    cc = cc1 << 32;
    ch3 = cc | ch2;
    cl1 = a * b;
    cl1h = cl1 >> 32;
    cxl = cx & 0xFFFFFFFF;
    cc2 = (cl1h < cxl);
    ch11 = ch1 + cc2;
    cha = ch11 + ch3;

    *ch = cha;
    *cl = cl1;
}

uint64_t mullo64(uint64_t a, uint64_t b) {
    return a * b;
}

uint64_t mulhi64(uint64_t a, uint64_t b) {
    uint64_t al, ah, bl, bh, c1, c2, cc, cc1, cx, cxl, ch1, ch2, ch3, cl1, cl1h, cc2, cc1a, cc1b, ch11, cha;

    al = a & 0xFFFFFFFF;
    ah = a >> 32;
    bl = b & 0xFFFFFFFF;
    bh = b >> 32;

    c1 = ah * bl;
    c2 = al * bh;
    cx = c1 + c2;
    cc1a = (cx < c1);
    cc1b = (cx < c2);
    cc1 = cc1a || cc1b;
    ch1 = ah * bh;
    ch2 = cx >> 32;
    cc = cc1 << 32;
    ch3 = cc | ch2;
    cl1 = a * b;
    cl1h = cl1 >> 32;
    cxl = cx & 0xFFFFFFFF;
    cc2 = (cl1h < cxl);
    ch11 = ch1 + cc2;
    cha = ch11 + ch3;

    return cha;
}


#ifdef USE_KARATSUBA
void mul128(uint128_t* ch, uint128_t* cl, uint128_t a, uint128_t b) {
    uint64_t al, ah, bl, bh, cll, clh, chl, chh, uc1, uc2, vc1, vc2, xc11, xc12,
        uc, ul, vc, vl, xl, xh, xc, xc1, xh1, xh2, xh2a, xh2b, xc2, xc3, xh3, xc1a, xc31, xc32,
        yh, yl, zh, zl, qc, qh, ql, qc1, yh1, rl, rlc, qh1, rh, rc, clc, wl, wlc, wh, chlc, wh1,
        qc11, qc12, qca, qcb, clc1, clc2, wlc1, wlc2, chlc1, chlc2, rc1, rc2;

    al = LO64(a);
    ah = HI64(a);
    bl = LO64(b);
    bh = HI64(b);

    ul = ah + al;
    uc1 = (ul < al);
    uc2 = (ul < ah);
    uc = uc1 || uc2;
    vl = bh + bl;
    vc1 = (vl < bl);
    vc2 = (vl < bl);
    vc = vc1 || vc2;
    mul64(&xh1, &xl, ul, vl);
    xh2a = ((-(int64_t)uc) & vl);
    xh2b = ((-(int64_t)vc) & ul);
    xh2 = xh2a + xh2b;
    xc11 = (xh2 < xh2a);
    xc12 = (xh2 < xh2b);
    xc1 = xc11 || xc12;
    xc2 = uc & vc;
    xh = xh1 + xh2;
    xc31 = (xh < xh1);
    xc32 = (xh < xh2);
    xc3 = xc31 || xc32;
    xc1a = xc1 + xc3;
    xc = xc1a + xc2;
    mul64(&yh, &yl, ah, bh);
    mul64(&zh, &zl, al, bl);
    ql = yl + zl;
    qc11 = (ql < yl);
    qc12 = (ql < zl);
    qc1 = qc11 || qc12;
    yh1 = yh + qc1;
    qh = yh1 + zh;
    qca = (qh < yh1);
    qcb = (qh < zh);
    qc = qca || qcb;
    rl = xl - ql;
    rlc = (ql > xl);
    qh1 = qh + rlc;
    rh = xh - qh1;
    rc1 = (qh1 > xh);
    rc2 = xc - qc;
    rc = rc2 - rc1;
    cll = zl;
    clh = zh + rl;
    clc1 = (clh < zh);
    clc2 = (chl < rl);
    clc = clc1 || clc2;
    wl = rh + clc;
    wlc1 = (wl < rh);
    wlc2 = (wl < clc);
    wlc = wlc1 || wlc2;
    wh = rc + wlc;
    chl = yl + wl;
    chlc1 = (chl < yl);
    chlc2 = (chl < wl);
    chlc = chlc1 || chlc2;
    wh1 = wh + chlc;
    chh = yh + wh1;

    *ch = INT128(chh, chl);
    *cl = INT128(clh, cll);
}
#else

void mul128(uint128_t* ch, uint128_t* cl, uint128_t a, uint128_t b) {
    uint64_t al, ah, bl, bh, chl, chh,
        albll, alblh, albhh, albhl, ahblh, ahbll, ahbhh, ahbhl,
        cxl, cxh, cx2l, cx2h, chxl, chxh;
    _Bool cx2c, cx2c1, cx2c2, chxc, chxc1, chxc2;
    
    al = LO64(a);
    ah = HI64(a);
    bl = LO64(b);
    bh = HI64(b);

    mul64(&alblh, &albll, al, bl);
    mul64(&albhh, &albhl, al, bh);
    mul64(&ahblh, &ahbll, ah, bl);
    mul64(&ahbhh, &ahbhl, ah, bh);
    cxl = albhl + ahbll;
    cxh = albhh + ahblh;
    cx2l = cxl + alblh;
    cx2c1 = (cx2l < cxl);
    cx2c2 = (cx2l < alblh);
    cx2c = cx2c1 || cx2c2;
    cx2h = cxh + cx2c;
    chxl = ahbhl + cx2h;
    chxc1 = (chxl < ahbhl);
    chxc2 = (chxl < cx2h);
    chxc = chxc1 || chxc2;
    chxh = ahbhh + chxc;

    *ch = INT128(chxh, chxl);
    *cl = INT128(cx2l, albll);
}

#endif

uint128_t mullo128(uint128_t a, uint128_t b) {
    uint64_t al, ah, bl, bh, 
        albll, alblh, albhh, albhl, ahblh, ahbll, ahbhl, cxl, cx2l;

    al = LO64(a);
    ah = HI64(a);
    bl = LO64(b);
    bh = HI64(b);

    mul64(&alblh, &albll, al, bl);
    albhl = mullo64(al, bh);
    ahbll = mullo64(ah, bl);
    cxl = albhl + ahbll;
    cx2l = cxl + alblh;
   
    return INT128(cx2l, albll);
}

uint128_t mulhi128(uint128_t a, uint128_t b) {
    uint64_t al, ah, bl, bh, chl, chh,
        albll, alblh, albhh, albhl, ahblh, ahbll, ahbhh, ahbhl,
        cxl, cxh, cx2l, cx2h, chxl, chxh;
    _Bool cx2c, cx2c1, cx2c2, chxc, chxc1, chxc2;

    al = LO64(a);
    ah = HI64(a);
    bl = LO64(b);
    bh = HI64(b);

    alblh = mulhi64(al, bl);
    mul64(&albhh, &albhl, al, bh);
    mul64(&ahblh, &ahbll, ah, bl);
    mul64(&ahbhh, &ahbhl, ah, bh);
    cxl = albhl + ahbll;
    cxh = albhh + ahblh;
    cx2l = cxl + alblh;
    cx2c1 = (cx2l < cxl);
    cx2c2 = (cx2l < alblh);
    cx2c = cx2c1 || cx2c2;
    cx2h = cxh + cx2c;
    chxl = ahbhl + cx2h;
    chxc1 = (chxl < ahbhl);
    chxc2 = (chxl < cx2h);
    chxc = chxc1 || chxc2;
    chxh = ahbhh + chxc;

    return INT128(chxh, chxl);
}


#ifdef USE_MBIT124
// translate to bitops
uint128_t mulmod128(uint128_t a, uint128_t b, uint128_t m, uint128_t mu) {
    uint128_t ql, qh, qqml, qq, qmh1;
    uint64_t qhq, qll, qlh, qhl, qhh, tmpll, tmplh, qlla, qllb, qll1, qlha, qlhb, qlh1, qmh1h, qmh1l, qmhh, qmhl, 
        qmh2, qql, qqh, qql1, qql2, tmpll1, tmplh1, tmplh1a, qqmll, qqmlh, ml, mh, tmplmh, tmplml, tmplmha, cl, ch;
    _Bool cc, qmhc1, qmhc2,  qmhc, tmplc1, tmplc2, tmplc, cc1, cc2, cc3, cc4, tmplmc1, tmplmc2, tmplmc;

    // mul
    mul128(&qh, &ql, a, b);
    ml = LO64(m);
    mh = HI64(m);
    qll = LO64(ql);
    qlh = HI64(ql);
    qhl = LO64(qh);
    qhh = HI64(qh);
    // copy
    tmpll = qll;
    tmplh = qlh;
    // shifts
    qlla = qlh >> (MBITS - 2 - 64);
    qllb = qhl << (128 - MBITS + 2);
    qll1 = qlla | qllb;
    qlha = qhl >> (MBITS - 2 - 64);
    qlhb = qhh << (128 - MBITS + 2);
    qlh1 = qlha | qlhb;
    // shr + shrc
    qhq = qhh >> (MBITS - 2 - 64);
    // mul
    ql = INT128(qlh1, qll1);
    qmh1 = mulhi128(ql, mu);
    // mul
    qmh2 = qhq * LO64(mu);
    // adds
    qmh1h = HI64(qmh1);
    qmh1l = LO64(qmh1);
    qmhl = qmh1l + qmh2;
    qmhc1 = (qmhl < qmh1l);
    qmhc2 = (qmhl < qmh2);
    qmhc = qmhc1 || qmhc2;
    qmhh = qmh1h + qmhc;
    // shift
    qql1 = qmhl >> 1;
    qql2 = qmhh << 63;
    qql = qql1 | qql2;
    qqh = qmhh >> 1;
    qq = INT128(qqh, qql);
    // mul
    qqml = mullo128(qq, m);
    qqmll = LO64(qqml);
    qqmlh = HI64(qqml);
    // sub
    tmpll1 = tmpll - qqmll;
    tmplc1 = (tmpll1 < tmpll);
    tmplc2 = (tmpll1 < qqml);
    tmplc = tmplc1 || tmplc2;
    tmplh1a = tmplh - qqmlh;
    tmplh1 = tmplh1a - tmplc;
    // cmp
    cc1 = (tmplh1 < mh);
    cc2 = (tmplh1 == mh);
    cc3 = (tmpll1 < ml);
    cc4 = cc2 && cc3;
    cc = cc1 || cc4;
    // sub
    tmplml = tmpll1 - ml;
    tmplmc1 = (tmplml < tmpll1);
    tmplmc2 = (tmplml < ml);
    tmplc = tmplmc1 || tmplmc2;
    tmplmha = tmplh1 - mh;
    tmplmh = tmplmha - tmplc;
    // cmov
    cl = cc ? tmpll1 : tmplml;
    ch = cc ? tmplh1 : tmplmh;

    return INT128(ch, cl);
}
#endif

#endif
#endif


void printconf(void) {
#ifdef USE_VHD64
    printf("\nmode = VHD64");
#else
    printf("\nmode = C");
#endif
#ifdef USE_KARATSUBA
    printf(", USE_KARATSUBA");
#endif
#ifdef USE_MBIT124
    printf(", MBIT = 124");
#endif
#ifdef USE_INT128
    printf(", USE_INT128\n\n");
#else
    printf("\n\n");
#endif
}


int main() {
   uint128_t a, b, c, d, u, v, m, mu, wl, wh, zl, zh, ql, qh, x, y;

    m = MODULUS;
    mu = MU;
    a = INT128(0x3456789ABCDEFULL, 0xFEDCBA0987654321ULL) % m;
    b = INT128(0x5BA0987654321ULL, 0xF23456789ABCDEF0ULL) % m;
    wh = INT128(0x12BB9215EAULL, 0x8766A4F590461508ULL);
    wl = INT128(0xBDC6847EEABF0E40ULL, 0x36D928FE5618CF0ULL);
#ifdef USE_MBIT124
    x = INT128(0xDC6C992956FDF13ULL, 0x4DEDDC13E7CF1CF9ULL);
#endif

    c = (a + b) % m;
    d = addmod128(a, b, m);

    u = (b>a ? a+m : a) - b;
    v = submod128(a, b, m);

    // cannot do in C
    // w = a * b;
    mul128(&zh, &zl, a, b);
    ql = mullo128(a, b);
    qh = mulhi128(a, b);

    // need MBIT = 124 for Barrett efficiency
#ifdef USE_MBIT124
    // cannot do in C
    // y = (a * b) % m;
    y = mulmod128(a, b, m, mu);
#endif

    uint128_t t1, t2;
    t1 = (y + y) % m;
    t2 = addmod128(y, y, m);
    if (t1 > m) {
      printf("t1 > m\n");
    }
    if (t2 > m) {
      printf("t2 > m\n");
    }
    if (t1 != t2) {
      printf("fail");
    }

    printconf();

	printf("(0x%llX%016llX + 0x%llX%016llX) %% 0x%llX%016llX = 0x%llX%016llX\n", HI64(a), LO64(a), HI64(b), LO64(b), HI64(m), LO64(m), HI64(c), LO64(c));
    printf("(0x%llX%016llX + 0x%llX%016llX) %% 0x%llX%016llX = 0x%llX%016llX\n", HI64(a), LO64(a), HI64(b), LO64(b), HI64(m), LO64(m), HI64(d), LO64(d));
    printf("%s\n\n", c == d ? "ok" : "fail");
    printf("%s\n\n", c > m ? "c is bigger than modulus" : "smaller than modulus");

	printf("(0x%llX%016llX - 0x%llX%016llX) %% 0x%llX%016llX = 0x%llX%016llX\n", HI64(a), LO64(a), HI64(b), LO64(b), HI64(m), LO64(m), HI64(u), LO64(u));
	printf("(0x%llX%016llX - 0x%llX%016llX) %% 0x%llX%016llX = 0x%llX%016llX\n", HI64(a), LO64(a), HI64(b), LO64(b), HI64(m), LO64(m), HI64(v), LO64(v));
	printf("%s\n\n", u == v ? "ok" : "fail");

    printf("0x%llX%016llX * 0x%llX%016llX = 0x%llX%016llX%016llX%016llX\n", HI64(a), LO64(a), HI64(b), LO64(b), HI64(wh), LO64(wh), HI64(wl), LO64(wl));
    printf("0x%llX%016llX * 0x%llX%016llX = 0x%llX%016llX%016llX%016llX\n", HI64(a), LO64(a), HI64(b), LO64(b), HI64(zh), LO64(zh), HI64(zl), LO64(zl));
    printf("0x%llX%016llX *lo 0x%llX%016llX = 0x%llX%016llX\n", HI64(a), LO64(a), HI64(b), LO64(b), HI64(ql), LO64(ql));
    printf("0x%llX%016llX *hi 0x%llX%016llX = 0x%llX%016llX\n", HI64(a), LO64(a), HI64(b), LO64(b), HI64(qh), LO64(qh));
    printf("%s\n\n", (wl == zl) && (wl == ql) && (wh == zh) && (wh == qh) ? "ok" : "fail");

#ifdef USE_MBIT124
    printf("(0x%llX%016llX * 0x%llX%016llX) %% 0x%llX%016llX = 0x%llX%016llX\n", HI64(a), LO64(a), HI64(b), LO64(b), HI64(m), LO64(m), HI64(x), LO64(x));
    printf("(0x%llX%016llX * 0x%llX%016llX) %% 0x%llX%016llX = 0x%llX%016llX\n", HI64(a), LO64(a), HI64(b), LO64(b), HI64(m), LO64(m), HI64(y), LO64(y));
    printf("%s\n\n", x == y ? "ok" : "fail");
#endif
}


