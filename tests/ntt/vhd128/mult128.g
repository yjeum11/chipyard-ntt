# m := 2^124-59
# mu := 170141183460469231731687303715884106200
## mod bit:  124
## mu bit:  128

# (a+b)(c+d)-(ac+bd) = (ac+ad+bc+bd) - (ac-bd) = ad+bc
# 
# (ah*z + al) * (bh*z + bl) = (ah*bh)*z^2 + (ah*bl + al*bh)*z + (al*bl)
# (ah*z + al) * (bh*z + bl) = (ah*bh)*z^2 + ((ah+al)*(bh+bl)-((ah*bh)+(al*bl)))*z + (al*bl)
# 
# (ah al) * (bh bl) = (chh chl clh cll)
# 
# (uc ul) = (ah + al)			                       // a+b					addqc
# (vc vl) = (bh + bl)			                       // c+d					addqc
# (xc xh xl) = (uc ul) * (vc vl)		               // (a+b)*(c+d)			mulqqc
# (yh yl) = (ah * bh) 			                       // a*c					mulqqq = mulq + mulhiq
# (zh zl) = (al * bl) 			                       // b*d					mulqqq = mulq + mulhiq
# (qc qh ql) = (yh yl) + (zh zl)		               // ac+bd				    addqc + adcqc
# (rc rh rl) = (xc xh xl) - (qc qh ql)	               // (a+b)(c+d)-(ac+bd) =  ad+bc	subqc + sbcqc + xor
# 
# (clc clh cll) = (zh zl) + (rl 0)	                   // cl = (cll clh)		addqc 
# (wh wl) = (rc rh) + (0 clc)	      	               //                       cincqc + adcqc + cincq
# (chh chl) = (yh yl) + (wh wl)		                   // ch = (chl chh)		addqc + adcq
# 


HexPrint := i -> Print("0x"::ToUpperHexStr(HexInt(i)));
HexPrintLine := i -> PrintLine("0x"::ToUpperHexStr(HexInt(i)));
INT128 := (h, l) -> IntHexString(h) * 2^64 + IntHexString(l);
LO32 := n -> Mod(n, 2^32);
HI32 := n -> (n - LO32(n)) / 2^32;
LO64 := n -> Mod(n, 2^64);
HI64 := n -> (n - LO64(n)) / 2^64;
LO128 := n -> Mod(n, 2^128);
HI128 := n -> (n - LO128(n)) / 2^128;

mbits := 116;
ml := IntHexString("0x00000000005E0001");
mh := IntHexString("0x8000000000000");

m := INT128("0x8000000000000", "0x00000000005E0001");
mu = INT128("0xFFFFFFFFFFFFFF", "0xFFFFFFFFF43FFFE0");

a := Mod(INT128("0x3456789ABCDEF", "0xFEDCBA0987654321"), m);
b := Mod(INT128("0x5BA0987654321", "0xF23456789ABCDEF0"), m);

w := Mod(a * b, m);
HexPrintLine(w);

# correct by Wolfram Alpha
# 7ab88f10bab0dcf97737ab5edf8b7_16
Print("(", HexPrint(a), " * ", HexPrint(b), ") % ", HexPrint(m), " = ", HexPrint(w), "\n");


####
al := LO64(a);
ah := HI64(a);
bl := LO64(b);
bh := HI64(b);
HexPrintLine(al);
HexPrintLine(ah);
HexPrintLine(bl);
HexPrintLine(bh);

# correct by Wolfram Alpha
# 12bb9215ea8766a4f590461508bdc6847eeabf0e40036d928fe5618cf0_16
c := a * b;
cl := LO128(c);
cll := LO64(cl);
clh := HI64(cl);
HexPrintLine(cll);
HexPrintLine(clh);
ch := HI128(c);
chl := LO64(ch);
chh := HI64(ch);
HexPrintLine(chl);
HexPrintLine(chh);
HexPrintLine(c);
Print("0x"::ToUpperHexStr(HexInt(chh))::ToUpperHexStr(HexInt(chl))::ToUpperHexStr(HexInt(clh))::ToUpperHexStr(HexInt(cll))::"\n");
PrintLine("0x"::ToUpperHexStr(HexInt(chh))::"ULL");
PrintLine("0x"::ToUpperHexStr(HexInt(chl))::"ULL");
PrintLine("0x"::ToUpperHexStr(HexInt(clh))::"ULL");
PrintLine("0x"::ToUpperHexStr(HexInt(cll))::"ULL");

# Karatsuba
# (uc ul) = (ah + al)
u := ah + al;
uc := HI64(u);
ul := LO64(u);

# (vc vl) = (bh + bl)
v := bh + bl;
vc := HI64(v);
vl := LO64(v);

# (xc xh xl) = (uc ul) * (vc vl)
x := u * v;
xl := LO64(x);
xh := HI64(LO128(x));
xc := HI128(x);

# (yh yl) = (ah * bh)
y := ah * bh;
yl := LO64(y);
yh := HI64(y);

# (zh zl) = (al * bl)
z := al * bl;
zl := LO64(z);
zh := HI64(z);

# (qc qh ql) = (yh yl) + (zh zl)
q := y + z;
ql := LO64(q);
qh := HI64(LO128(q));
qc := HI128(q);

# (rc rh rl) = (xc xh xl) - (qc qh ql)
r := x - q;
rl := LO64(r);
rh := HI64(LO128(r));
rc := HI128(r);

# (ah al) * (bh bl) = (chh chl clh cll)
_c := y * 2^128 + r * 2^64 + z;
_c = c;

# (clc clh cll) = (zh zl) + (rl 0)	
_clx := z + rl * 2^64;
_cl := LO128(_clx);
_cll := LO64(_clx);
_clh := HI64(LO128(_clx));
_clc := HI128(_clx);
_cl = cl;
_cll = cll;
_clh = clh;

# (wh wl) = (rc rh) + (0 clc)
w := rh + _clc;
wl := LO64(w);
wh := HI64(w);

# (chh chl) = (yh yl) + (wh wl)
_ch := y + w;
_chl := LO64(_ch);
_chh := HI64(_ch);
_ch = ch;
_chl = chl;
_chh = chh;


