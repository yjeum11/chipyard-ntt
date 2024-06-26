a := IntHexString("123456789ABCDEF");
b := IntHexString("FEDCBA0987654321");
m := 1152921504606846577;
mu := 9223372036854779000;
mbits := 60;
shft := 4;
ctrl := true;
_positive := i -> Cond(i<0, i+2^64, i);
_shl := (n, i) -> (n - Mod(n, 2^(i))) / 2^(i);
_low64 := n -> Mod(n, 2^64);
_HexPrint := i -> PrintLine("0x"::ToUpperHexStr(HexInt(i)));

c :=  _low64(_shl(a*2^64+b, 4));
d := _low64(a*b);
e := _low64(_shl(a*b, 64));
f := Cond(ctrl, a+b, a);
g := Cond(ctrl, _positive(a-b), a);

u := Mod(a, m);
v := Mod(b, m);
w := Mod(u + v, m);
x := _positive(Mod(u - v, m));
z := Mod(u * v, m);

_HexPrint(a);
_HexPrint(b);
_HexPrint(m);

_HexPrint(c);
_HexPrint(d);
_HexPrint(e);
_HexPrint(f);
_HexPrint(g);

_HexPrint(u);
_HexPrint(v);
_HexPrint(w);
_HexPrint(x);
_HexPrint(z);

#	q = DBigInt(a[i]) * DBigInt(b[i]);  // note 2x #bits
q := u*v;
_HexPrint(q);
#	tmp = q;
tmp := q;
#   q >>= (mbits - 2 = 58);
q := _shl(q, mbits-2);
_HexPrint(q);
#   q *= DBigInt(mu);
q := q * mu;
_HexPrint(q);
#   q >>= (mbits + 5);
q := _shl(q, mbits + 5);
_HexPrint(q);
#   tmp -= q * DBigInt(mod);
qm := q*m;
_HexPrint(qm);
tmp := tmp - qm;
_HexPrint(tmp);
#   c =  BigInt(tmp);
cc := _low64(tmp);
_HexPrint(cc);
#   if (c >= mod) c -= mod;
cc := Cond(cc >= m, cc - m, cc);
_HexPrint(cc);

z = cc;
