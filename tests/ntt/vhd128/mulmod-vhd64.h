#ifdef USE_VHD64
void mul128(uint128_t* ch, uint128_t* cl, uint128_t a, uint128_t b) {
    uint64_t al, ah, bl, bh, clh, chl, chh,
        ul, vl, xl, xh, xc, xh1, xh2, xh2a, xh2b, xh3,
        yh, yl, zh, zl, qh, ql, yh1, rl, qh1, rh, wl, wh, xca, xcb;
    _Bool uc, vc, qc1, qc, rlc, rc, rc1, rc2, clc, wlc, chlc, xc1, xc2, xc3;

    al = LO64(a);
    ah = HI64(a);
    bl = LO64(b);
    bh = HI64(b);

    // (uc ul) = (ah + al)
    _addqc(ul, uc, ah, al);
    // (vc vl) = (bh + bl)
    _addqc(vl, vc, bh, bl);
    //  (xc xh xl) = (uc ul) * (vc vl)
    //  x1h xl =  ul*vl
    _muldqqq(xh1, xl, ul, vl);
    //  (uc*vl+ul*vc)*2^64 = xc1 xh2 0
    xh2a = _czeroq(vl, uc);
    xh2b = _czeroq(ul, vc);
    _addqc(xh2, xc1, xh2a, xh2b);
    //  xh2 = xh2a + xh2b;
    xc2 = _andb(uc, vc);
    //  xh = x1h + xh2
    _addqc(xh, xc3, xh1, xh2);
    // xc
    xca = _cvtbq(xc1);
    xcb = _cincq(xca, xc2);
    xc = _cincq(xcb, xc3);
    //  (yh yl) = (ah * bh) 
    _muldqqq(yh, yl, ah, bh);
    //  (zh zl) = (al * bl) 
    _muldqqq(zh, zl, al, bl);
    //  (qc qh ql) = (yh yl) + (zh zl)
    _addqc(ql, qc1, yl, zl);
    _adcqc(qh, qc, yh, zh, qc1);
    //  (rc rh rl) = (xc xh xl) - (qc qh ql)
    _subqc(rl, rlc, xl, ql);
    _sbcqc(rh, rc1, xh, qh, rlc);
    rc2 = _cdecq(xc, qc);
    rc = _cdecq(rc2, rc1);
    //  (clc clh cll) = (zh zl) + (rl 0)
    _addqc(clh, clc, zh, rl);
    //  (wh wl) = (rc rh) + (0 clc)
    _cincqc(wl, wlc, rh, clc);
    wh = _cincq(rc, wlc);
    //  (chh chl) = (yh yl) + (wh wl)
    _addqc(chl, chlc, yl, wl);
    chh = _adcq(yh, wh, chlc);

    *ch = INT128(chh, chl);
    *cl = INT128(clh, zl);
}
#endif
