#ifndef __VHD64_H__
#define __VHD64_H__

#define _sign_int65(_v)				((_Bool)((_v) >> 64))
#define _sign_int128(_v)			((_Bool)((_v) >> 127))
#define _lower_uint64(_v)			((__uint64_t)(_v))		
#define _upper_uint64(_v)			((__uint64_t)((_v) >> 64))		
#define _concat_uint64x2(_v, _w)	((((__uint128_t)(_v)) << 64) | (_w))

#define _HAS_MULDQQQ
#define _HAS_CFLAG

#ifdef _HAS_CFLAG
#define	_addqc(_c, _cflag, _a, _b) {(_cflag) = _carry_addq((_a), (_b)); (_c) = _addq((_a), (_b));}
#define	_subqc(_c, _cflag, _a, _b) {(_cflag) = _carry_subq((_a), (_b)); (_c) = _subq((_a), (_b));}

#define	_adcqc(_c, _cflag, _a, _b, _cf) {(_cflag) = _carry_adcq((_a), (_b), (_cf)); (_c) = _adcq((_a), (_b), (_cf));}
#define	_sbcqc(_c, _cflag, _a, _b, _cf) {(_cflag) = _carry_sbcq((_a), (_b), (_cf)); (_c) = _sbcq((_a), (_b), (_cf));}

#define	_caddqc(_c, _cflag, _a, _b, _ctrl) {(_cflag) = (_ctrl) ? _carry_addq((_a), (_b)) : 0; (_c) = (_ctrl) ? _addq((_a), (_b)): (_a);}
#define	_csubqc(_c, _cflag, _a, _b, _ctrl) {(_cflag) = (_ctrl) ? _carry_subq((_a), (_b)) : 0; (_c) = (_ctrl) ? _subq((_a), (_b)): (_a);}

#define	_cnaddqc(_c, _cflag, _a, _b, _ctrl) {(_cflag) = (!_ctrl) ? _carry_addq((_a), (_b)) : 0; (_c) = (!_ctrl) ? _addq((_a), (_b)): (_a);}
#define	_cnsubqc(_c, _cflag, _a, _b, _ctrl) {(_cflag) = (!_ctrl) ? _carry_subq((_a), (_b)) : 0; (_c) = (!_ctrl) ? _subq((_a), (_b)): (_a);}

#endif

#ifdef _HAS_MULDQQQ
#define _muldqqq(_ch, _cl, _a, _b) {(_ch) = _mulhiq((_a), (_b)); (_cl) = _mulq((_a), (_b));}
#endif

__uint64_t _shrq(__uint64_t a, __uint8_t shift) {
	return a >> shift;
}

__uint64_t _addq(__uint64_t a, __uint64_t b) {
	return a + b;
}

__uint64_t _subq(__uint64_t a, __uint64_t b) {
	return a - b;
}

__uint64_t _mulq(__uint64_t a, __uint64_t b) {
	return a * b;
}


__uint64_t _adcq(__uint64_t a, __uint64_t b, _Bool carry) {
	return a + b + carry;
}

__uint64_t _sbcq(__uint64_t a, __uint64_t b, _Bool carry) {
	return a - b - carry;
}


__uint64_t _shrqdq(__uint64_t a, __uint64_t b, __uint8_t shift) {
	return _lower_uint64(_concat_uint64x2(a, b) >> shift);
}

__uint64_t _mulhiq(__uint64_t a, __uint64_t b) {
	return _upper_uint64(((__uint128_t)a) * ((__uint128_t)b));
}

__uint64_t _caddq(__uint64_t a, __uint64_t b, _Bool ctrl) {
	return ctrl ? a + b : a;
}

__uint64_t _cnaddq(__uint64_t a, __uint64_t b, _Bool ctrl) {
	return !ctrl ? a + b : a;
}

__uint64_t _csubq(__uint64_t a, __uint64_t b, _Bool ctrl) {
	return ctrl ? a - b : a;
}

__uint64_t _cnsubq(__uint64_t a, __uint64_t b, _Bool ctrl) {
	return !ctrl ? a - b : a;
}

__uint64_t _cadcq(__uint64_t a, __uint64_t b, _Bool carry, _Bool ctrl) {
	return ctrl ? a + b + carry: a;
}

__uint64_t _cnadcq(__uint64_t a, __uint64_t b, _Bool carry, _Bool ctrl) {
	return !ctrl ? a + b + carry : a;
}

__uint64_t _csbcq(__uint64_t a, __uint64_t b, _Bool carry, _Bool ctrl) {
	return ctrl ? a - b - carry: a;
}

__uint64_t _cnsbcq(__uint64_t a, __uint64_t b, _Bool carry, _Bool ctrl) {
	return !ctrl ? a - b - carry : a;
}

_Bool _carry_addq(__uint64_t a, __uint64_t b) {
	return _sign_int65((__uint128_t)a + (__uint128_t)b);
}

_Bool _carry_subq(__uint64_t a, __uint64_t b) {
	return _sign_int128((__uint128_t)a - (__uint128_t)b);
}

_Bool _carry_adcq(__uint64_t a, __uint64_t b, _Bool cf) {
	return _sign_int65((__uint128_t)a + (__uint128_t)b + (__uint128_t)cf);
}

_Bool _carry_sbcq(__uint64_t a, __uint64_t b, _Bool cf) {
	return _sign_int128((__uint128_t)a - (__uint128_t)b - (__uint128_t)cf);
}

_Bool _cmpgeq(__uint64_t a, __uint64_t b) {
	return a >= b;
}

_Bool _cmplq(__uint64_t a, __uint64_t b) {
	return a < b;
}

_Bool _cmpeq(__uint64_t a, __uint64_t b) {
	return a == b;
}

_Bool _orb(_Bool a, _Bool b) {
	return a || b;
}

_Bool _andb(_Bool a, _Bool b) {
	return a && b;
}

_Bool _xorb(_Bool a, _Bool b) {
	return a ^ b;
}

_Bool _notb(_Bool a) {
	return !a;
}

__uint64_t _cvtbq(_Bool b) {
	return (__uint64_t)b;
}

__uint64_t _czeroq(__uint64_t a, _Bool ctrl) {
	return ctrl ? a : 0;
}

_Bool __ccmpeq(__uint64_t a, __uint64_t b, _Bool dval, _Bool ctrl) {
	return ctrl ? (a == b) : dval;
}

_Bool __ccmpneq(__uint64_t a, __uint64_t b, _Bool dval, _Bool ctrl) {
	return ctrl ? (a != b) : dval;
}

_Bool __ccmpgq(__uint64_t a, __uint64_t b, _Bool dval, _Bool ctrl) {
	return ctrl ? (a > b) : dval;
}

_Bool __ccmpgeq(__uint64_t a, __uint64_t b, _Bool dval, _Bool ctrl) {
	return ctrl ? (a >= b) : dval;
}

_Bool __ccmplq(__uint64_t a, __uint64_t b, _Bool dval, _Bool ctrl) {
	return ctrl ? (a < b) : dval;
}

_Bool __ccmpleq(__uint64_t a, __uint64_t b, _Bool dval, _Bool ctrl) {
	return ctrl ? (a <= b) : dval;
}

_Bool __cncmpeq(__uint64_t a, __uint64_t b, _Bool dval, _Bool ctrl) {
	return !ctrl ? (a == b) : dval;
}

_Bool __cncmpneq(__uint64_t a, __uint64_t b, _Bool dval, _Bool ctrl) {
	return !ctrl ? (a != b) : dval;
}

_Bool __cncmpgq(__uint64_t a, __uint64_t b, _Bool dval, _Bool ctrl) {
	return !ctrl ? (a > b) : dval;
}

_Bool __cncmpgeq(__uint64_t a, __uint64_t b, _Bool dval, _Bool ctrl) {
	return !ctrl ? (a >= b) : dval;
}

_Bool __cncmplq(__uint64_t a, __uint64_t b, _Bool dval, _Bool ctrl) {
	return !ctrl ? (a < b) : dval;
}

_Bool __cncmpleq(__uint64_t a, __uint64_t b, _Bool dval, _Bool ctrl) {
	return !ctrl ? (a <= b) : dval;
}

#define _ccmpeq(_a, _b, _d, _c)		{(_d) = __ccmpeq(_a, _b, _d, _c);}
#define _cncmpeq(_a, _b, _d, _c)	{(_d) = __cncmpeq(_a, _b, _d, _c);}

#define _ccmpneq(_a, _b, _d, _c)		{(_d) = __ccmpneq(_a, _b, _d, _c);}
#define _cncmpneq(_a, _b, _d, _c)	{(_d) = __cncmpneq(_a, _b, _d, _c);}

#define _ccmpgq(_a, _b, _d, _c)		{(_d) = __ccmpgq(_a, _b, _d, _c);}
#define _cncmpgq(_a, _b, _d, _c)	{(_d) = __cncmpgq(_a, _b, _d, _c);}

#define _ccmplq(_a, _b, _d, _c)		{(_d) = __ccmplq(_a, _b, _d, _c);}
#define _cncmplq(_a, _b, _d, _c)	{(_d) = __cncmplq(_a, _b, _d, _c);}

#define _ccmpgeq(_a, _b, _d, _c)	{(_d) = __ccmpgeq(_a, _b, _d, _c);}
#define _cncmpgeq(_a, _b, _d, _c)	{(_d) = __cncmpgeq(_a, _b, _d, _c);}

#define _ccmpleq(_a, _b, _d, _c)	{(_d) = __ccmpleq(_a, _b, _d, _c);}
#define _cncmpleq(_a, _b, _d, _c)	{(_d) = __cncmpleq(_a, _b, _d, _c);}

#define _cincqc(_c, _cc, _a, _ac)	_adcqc((_c), (_cc), (_a), 0, (_ac))
#define _cincq(_a, _ac)				_adcq((_a), 0, (_ac))

#define _cdecqc(_c, _cc, _a, _ac)	_sbcqc((_c), (_cc), (_a), 0, (_ac))
#define _cdecq(_a, _ac)				_sbcq((_a), 0, (_ac))

#endif
