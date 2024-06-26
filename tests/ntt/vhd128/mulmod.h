#ifdef USE_VHD64
void mul64(uint64_t* ch, uint64_t* cl, uint64_t a, uint64_t b) {
    uint64_t al, ah, bl, bh,
        c1, c2, cc, cc1, cx, cxl, ch1, ch2, ch3, ch4, cl1, cl1h, cl3, cl4, cc2;

    al = a & 0xFFFFFFFF;
    ah = a >> 32;
    bl = b & 0xFFFFFFFF;
    bh = b >> 32;

    c1 = ah * bl;
    c2 = al * bh;
    // c = cc1 cx
    cx = c1 + c2;
    cc1 = (cx < c1) || (cx < c2);

    ch1 = ah * bh;
    ch2 = cx >> 32;
    cc = cc1 << 32;
    ch3 = cc | ch2;

    cl1 = a * b;
    cl1h = cl1 >> 32;
    cxl = cx & 0xFFFFFFFF;
    cc2 = (cl1h < cxl);

    *ch = ch1 + ch3 + cc2;
    *cl = cl1;
}


void mul128(uint128_t* ch, uint128_t* cl, uint128_t a, uint128_t b) {
    uint64_t al, ah, bl, bh, cll, clh, chl, chh,
        uc, ul, vc, vl, xl, xh, xc, xc1, xh1, xh2, xh2a, xh2b, xc2, xc3, xh3,
        yh, yl, zh, zl, qc, qh, ql, qc1, yh1, rl, rlc, qh1, rh, rc, clc, wl, wlc, wh, chlc, wh1, rc1;

    al = LO64(a);
    ah = HI64(a);
    bl = LO64(b);
    bh = HI64(b);

    // (uc ul) = (ah + al)
    ul = ah + al;
    uc = (ul < al) || (ul < ah);

    // (vc vl) = (bh + bl)
    vl = bh + bl;
    vc = (vl < bl) || (vl < bh);


    //  (xc xh xl) = (uc ul) * (vc vl)
    //  x1h xl =  ul*vl
    //  x = ((uint128_t)ul) * ((uint128_t)vl);
    //  xl = LO64(x);
    //  xh1 = HI64(x);
    mul64(&xh1, &xl, ul, vl);
    //  (uc*vl+ul*vc)*2^64 = xc1 xh2 0
    xh2a = ((-(int64_t)uc) & vl);
    xh2b = ((-(int64_t)vc) & ul);
    xh2 = xh2a + xh2b;
    xc1 = (xh2 < xh2a) || (xh2 < xh2b);
    //  (uc*vc)*2^128 = xc2
    xc2 = uc & vc;
    //  xh = x1h + xh2
    xh = xh1 + xh2;
    xc3 = (xh < xh1) || (xh < xh2);
    // xc
    xc = xc1 + xc2 + xc3;

    //  (yh yl) = (ah * bh) 
    mul64(&yh, &yl, ah, bh);

    //  (zh zl) = (al * bl) 
    mul64(&zh, &zl, al, bl);

    //  (qc qh ql) = (yh yl) + (zh zl)
    ql = yl + zl;
    qc1 = (ql < yl) || (ql < zl);
    yh1 = yh + qc1;
    qh = yh1 + zh;
    qc = (qh < yh1) || (qh < zh);

    //  (rc rh rl) = (xc xh xl) - (qc qh ql)
    rl = xl - ql;
    rlc = (ql > xl);
    qh1 = qh + rlc;
    rh = xh - qh1;
    rc1 = (qh1 > xh);
    rc = xc - qc - rc1;

    //  (clc clh cll) = (zh zl) + (rl 0)
    cll = zl;
    clh = zh + rl;
    clc = (clh < zh) || (chl < rl);

    //  (wh wl) = (rc rh) + (0 clc)
    wl = rh + clc;
    wlc = (wl < rh) || (wl < clc);
    wh = rc + wlc;

    //  (chh chl) = (yh yl) + (wh wl)
    chl = yl + wl;
    chlc = (chl < yl) || (chl < wl);
    wh1 = wh + chlc;
    chh = yh + wh1;

    *ch = INT128(chh, chl);
    *cl = INT128(clh, cll);
}
#endif
