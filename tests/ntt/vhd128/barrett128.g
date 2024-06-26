HexPrint := i -> Print("0x"::ToUpperHexStr(HexInt(i)));
HexPrintLine := i -> PrintLine("0x"::ToUpperHexStr(HexInt(i)));
INT128 := (h, l) -> IntHexString(h) * 2^64 + IntHexString(l);
LO32 := n -> Mod(n, 2^32);
HI32 := n -> (n - LO32(n)) / 2^32;
LO64 := n -> Mod(n, 2^64);
HI64 := n -> (n - LO64(n)) / 2^64;
LO128 := n -> Mod(n, 2^128);
HI128 := n -> (n - LO128(n)) / 2^128;
SHRLO := (n, s) -> Mod(n, 2^s);
SHR := (n, s) -> (n - SHRLO(n, s)) / 2^s;

#mbits := 116;
#m := INT128("0x8000000000000", "0x00000000005E0001");
#mu := INT128("0xFFFFFFFFFFFFFF", "0xFFFFFFFFF43FFFE0");

mbits := 124;
m := 2^124-59;
mu := 170141183460469231731687303715884106200;

a := Mod(INT128("0x3456789ABCDEF", "0xFEDCBA0987654321"), m);
b := Mod(INT128("0x5BA0987654321", "0xF23456789ABCDEF0"), m);

x := Mod(a * b, m);
HexPrintLine(w);

# correct by Wolfram Alpha
# dc6c992956fdf134deddc13e7cf1cf9_16
Print("(", HexPrint(a), " * ", HexPrint(b), ") % ", HexPrint(m), " = ", HexPrint(x), "\n");

xl := LO64(x);
xh := HI64(x);
HexPrintLine(xl);
HexPrintLine(xh);

####
al := LO64(a);
ah := HI64(a);
bl := LO64(b);
bh := HI64(b);
HexPrintLine(al);
HexPrintLine(ah);
HexPrintLine(bl);
HexPrintLine(bh);

ml := LO64(m);
mh := HI64(m);
mu_l := LO64(mu);
mu_h := HI64(mu);
HexPrintLine(ml);
HexPrintLine(mh);
HexPrintLine(mu_l);
HexPrintLine(mu_h);

# =============================================
# Barrett

q := a * b;
tmp := q;

q := SHR(q, mbits-2);
HexPrintLine(LO128(q));

q := q * mu;
q := SHR(q, mbits+5);
tmp := tmp - q * m;
c := Cond(tmp > m, tmp - m , tmp);

c = x;


