HexPrint := i -> Print("0x"::ToUpperHexStr(HexInt(i)));
HexPrintLine := i -> PrintLine("0x"::ToUpperHexStr(HexInt(i)));
INT128 := (h, l) -> IntHexString(h) * 2^64 + IntHexString(l);
LO64 := n -> Mod(n, 2^64);
HI64 := n -> (n - LO64(n)) / 2^64;



mbits := 116;
ml := IntHexString("0x00000000005E0001");
mh := IntHexString("0x8000000000000");

#m := IntHexString("0x800000000000000000000005E0001");
#mu := IntHexString("0xFFFFFFFFFFFFFFFFFFFFFFF43FFFE0");
#a := Mod(IntHexString("0x123456789ABCDEFFEDCBA0987654321"), m);
#b := Mod(IntHexString("0xEDCBA0987654321123456789ABCDEF0"), m);

a := Mod(INT128("0x3456789ABCDEF", "0xFEDCBA0987654321"), m);
b := Mod(INT128("0x5BA0987654321", "0x123456789ABCDEF0"), m);
m := INT128("0x8000000000000", "0x00000000005E0001");

c := Mod(a + b, m);
u := Mod(a - b, m);

u128 := u + 2^128;
ul := LO64(u128);
uh := HI64(u128);
HexPrintLine(ul);
HexPrintLine(uh);


e128 := a + m;
HexPrintLine(e128);

el := LO64(e128);
eh := HI64(e128);
HexPrintLine(el);
HexPrintLine(eh);

bl := LO64(b);
bh := HI64(b);
HexPrintLine(bl);
HexPrintLine(bh);

cl := el - bl;
HexPrintLine(cl);






Print("(", HexPrint(a), " - ", HexPrint(b), ") % ", HexPrint(m), " = ", HexPrint(c), "\n");

