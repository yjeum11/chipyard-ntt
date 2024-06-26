	.file	"main128.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	_shrq
	.type	_shrq, @function
_shrq:
	srl	a0,a0,a1
	ret
	.size	_shrq, .-_shrq
	.align	1
	.globl	_addq
	.type	_addq, @function
_addq:
	add	a0,a0,a1
	ret
	.size	_addq, .-_addq
	.align	1
	.globl	_subq
	.type	_subq, @function
_subq:
	sub	a0,a0,a1
	ret
	.size	_subq, .-_subq
	.align	1
	.globl	_mulq
	.type	_mulq, @function
_mulq:
	mul	a0,a0,a1
	ret
	.size	_mulq, .-_mulq
	.align	1
	.globl	_adcq
	.type	_adcq, @function
_adcq:
	add	a2,a2,a1
	add	a0,a2,a0
	ret
	.size	_adcq, .-_adcq
	.align	1
	.globl	_sbcq
	.type	_sbcq, @function
_sbcq:
	sub	a0,a0,a1
	sub	a0,a0,a2
	ret
	.size	_sbcq, .-_sbcq
	.align	1
	.globl	_shrqdq
	.type	_shrqdq, @function
_shrqdq:
	addiw	a4,a2,-64
	blt	a4,zero,.L9
	srl	a0,a0,a4
	ret
.L9:
	li	a5,63
	slli	a0,a0,1
	subw	a5,a5,a2
	sll	a5,a0,a5
	srl	a0,a1,a2
	or	a0,a5,a0
	ret
	.size	_shrqdq, .-_shrqdq
	.align	1
	.globl	_mulhiq
	.type	_mulhiq, @function
_mulhiq:
	mulhu	a0,a0,a1
	ret
	.size	_mulhiq, .-_mulhiq
	.align	1
	.globl	_caddq
	.type	_caddq, @function
_caddq:
	beq	a2,zero,.L13
	add	a0,a0,a1
.L13:
	ret
	.size	_caddq, .-_caddq
	.align	1
	.globl	_cnaddq
	.type	_cnaddq, @function
_cnaddq:
	bne	a2,zero,.L18
	add	a0,a0,a1
.L18:
	ret
	.size	_cnaddq, .-_cnaddq
	.align	1
	.globl	_csubq
	.type	_csubq, @function
_csubq:
	beq	a2,zero,.L20
	sub	a0,a0,a1
.L20:
	ret
	.size	_csubq, .-_csubq
	.align	1
	.globl	_cnsubq
	.type	_cnsubq, @function
_cnsubq:
	bne	a2,zero,.L25
	sub	a0,a0,a1
.L25:
	ret
	.size	_cnsubq, .-_cnsubq
	.align	1
	.globl	_cadcq
	.type	_cadcq, @function
_cadcq:
	beq	a3,zero,.L27
	add	a2,a2,a1
	add	a0,a0,a2
.L27:
	ret
	.size	_cadcq, .-_cadcq
	.align	1
	.globl	_cnadcq
	.type	_cnadcq, @function
_cnadcq:
	bne	a3,zero,.L32
	add	a2,a2,a1
	add	a0,a0,a2
.L32:
	ret
	.size	_cnadcq, .-_cnadcq
	.align	1
	.globl	_csbcq
	.type	_csbcq, @function
_csbcq:
	beq	a3,zero,.L34
	sub	a0,a0,a1
	sub	a0,a0,a2
.L34:
	ret
	.size	_csbcq, .-_csbcq
	.align	1
	.globl	_cnsbcq
	.type	_cnsbcq, @function
_cnsbcq:
	bne	a3,zero,.L39
	sub	a0,a0,a1
	sub	a0,a0,a2
.L39:
	ret
	.size	_cnsbcq, .-_cnsbcq
	.align	1
	.globl	_carry_addq
	.type	_carry_addq, @function
_carry_addq:
	add	a1,a0,a1
	sltu	a0,a1,a0
	ret
	.size	_carry_addq, .-_carry_addq
	.align	1
	.globl	_carry_subq
	.type	_carry_subq, @function
_carry_subq:
	sub	a1,a0,a1
	sgtu	a0,a1,a0
	ret
	.size	_carry_subq, .-_carry_subq
	.align	1
	.globl	_carry_adcq
	.type	_carry_adcq, @function
_carry_adcq:
	add	a2,a1,a2
	add	a0,a2,a0
	sltu	a1,a2,a1
	sltu	a0,a0,a2
	add	a0,a0,a1
	andi	a0,a0,1
	ret
	.size	_carry_adcq, .-_carry_adcq
	.align	1
	.globl	_carry_sbcq
	.type	_carry_sbcq, @function
_carry_sbcq:
	sub	a1,a0,a1
	sgtu	a0,a1,a0
	sub	a2,a1,a2
	sgtu	a2,a2,a1
	neg	a0,a0
	sub	a0,a0,a2
	srli	a0,a0,63
	ret
	.size	_carry_sbcq, .-_carry_sbcq
	.align	1
	.globl	_cmpgeq
	.type	_cmpgeq, @function
_cmpgeq:
	sltu	a0,a0,a1
	xori	a0,a0,1
	andi	a0,a0,1
	ret
	.size	_cmpgeq, .-_cmpgeq
	.align	1
	.globl	_cmplq
	.type	_cmplq, @function
_cmplq:
	sltu	a0,a0,a1
	ret
	.size	_cmplq, .-_cmplq
	.align	1
	.globl	_cmpeq
	.type	_cmpeq, @function
_cmpeq:
	sub	a0,a0,a1
	seqz	a0,a0
	ret
	.size	_cmpeq, .-_cmpeq
	.align	1
	.globl	_orb
	.type	_orb, @function
_orb:
	or	a0,a0,a1
	ret
	.size	_orb, .-_orb
	.align	1
	.globl	_andb
	.type	_andb, @function
_andb:
	beq	a0,zero,.L49
	mv	a0,a1
.L49:
	ret
	.size	_andb, .-_andb
	.align	1
	.globl	_xorb
	.type	_xorb, @function
_xorb:
	xor	a0,a0,a1
	ret
	.size	_xorb, .-_xorb
	.align	1
	.globl	_notb
	.type	_notb, @function
_notb:
	xori	a0,a0,1
	ret
	.size	_notb, .-_notb
	.align	1
	.globl	_cvtbq
	.type	_cvtbq, @function
_cvtbq:
	ret
	.size	_cvtbq, .-_cvtbq
	.align	1
	.globl	_czeroq
	.type	_czeroq, @function
_czeroq:
	snez	a1,a1
	neg	a1,a1
	and	a0,a0,a1
	ret
	.size	_czeroq, .-_czeroq
	.align	1
	.globl	__ccmpeq
	.type	__ccmpeq, @function
__ccmpeq:
	mv	a5,a0
	mv	a0,a2
	beq	a3,zero,.L60
	sub	a0,a5,a1
	seqz	a0,a0
.L60:
	ret
	.size	__ccmpeq, .-__ccmpeq
	.align	1
	.globl	__ccmpneq
	.type	__ccmpneq, @function
__ccmpneq:
	mv	a5,a0
	mv	a0,a2
	beq	a3,zero,.L65
	sub	a0,a5,a1
	snez	a0,a0
.L65:
	ret
	.size	__ccmpneq, .-__ccmpneq
	.align	1
	.globl	__ccmpgq
	.type	__ccmpgq, @function
__ccmpgq:
	mv	a5,a0
	mv	a0,a2
	beq	a3,zero,.L70
	sgtu	a0,a5,a1
.L70:
	ret
	.size	__ccmpgq, .-__ccmpgq
	.align	1
	.globl	__ccmpgeq
	.type	__ccmpgeq, @function
__ccmpgeq:
	mv	a5,a0
	mv	a0,a2
	beq	a3,zero,.L75
	sltu	a0,a5,a1
	xori	a2,a0,1
	andi	a0,a2,0xff
.L75:
	ret
	.size	__ccmpgeq, .-__ccmpgeq
	.align	1
	.globl	__ccmplq
	.type	__ccmplq, @function
__ccmplq:
	mv	a5,a0
	mv	a0,a2
	beq	a3,zero,.L80
	sltu	a0,a5,a1
.L80:
	ret
	.size	__ccmplq, .-__ccmplq
	.align	1
	.globl	__ccmpleq
	.type	__ccmpleq, @function
__ccmpleq:
	mv	a5,a0
	mv	a0,a2
	beq	a3,zero,.L85
	sgtu	a0,a5,a1
	xori	a2,a0,1
	andi	a0,a2,0xff
.L85:
	ret
	.size	__ccmpleq, .-__ccmpleq
	.align	1
	.globl	__cncmpeq
	.type	__cncmpeq, @function
__cncmpeq:
	mv	a5,a0
	mv	a0,a2
	bne	a3,zero,.L90
	sub	a0,a5,a1
	seqz	a0,a0
.L90:
	ret
	.size	__cncmpeq, .-__cncmpeq
	.align	1
	.globl	__cncmpneq
	.type	__cncmpneq, @function
__cncmpneq:
	mv	a5,a0
	mv	a0,a2
	bne	a3,zero,.L92
	sub	a0,a5,a1
	snez	a0,a0
.L92:
	ret
	.size	__cncmpneq, .-__cncmpneq
	.align	1
	.globl	__cncmpgq
	.type	__cncmpgq, @function
__cncmpgq:
	mv	a5,a0
	mv	a0,a2
	bne	a3,zero,.L94
	sgtu	a0,a5,a1
.L94:
	ret
	.size	__cncmpgq, .-__cncmpgq
	.align	1
	.globl	__cncmpgeq
	.type	__cncmpgeq, @function
__cncmpgeq:
	mv	a5,a0
	mv	a0,a2
	bne	a3,zero,.L96
	sltu	a0,a5,a1
	xori	a2,a0,1
	andi	a0,a2,0xff
.L96:
	ret
	.size	__cncmpgeq, .-__cncmpgeq
	.align	1
	.globl	__cncmplq
	.type	__cncmplq, @function
__cncmplq:
	mv	a5,a0
	mv	a0,a2
	bne	a3,zero,.L98
	sltu	a0,a5,a1
.L98:
	ret
	.size	__cncmplq, .-__cncmplq
	.align	1
	.globl	__cncmpleq
	.type	__cncmpleq, @function
__cncmpleq:
	mv	a5,a0
	mv	a0,a2
	bne	a3,zero,.L100
	sgtu	a0,a5,a1
	xori	a2,a0,1
	andi	a0,a2,0xff
.L100:
	ret
	.size	__cncmpleq, .-__cncmpleq
	.align	1
	.globl	addmod128
	.type	addmod128, @function
addmod128:
	mv	a6,a0
	add	a0,a0,a2
	bgeu	a6,a2,.L102
	mv	a6,a2
.L102:
	sltu	a6,a0,a6
	add	a7,a1,a3
	mv	a2,a1
	add	a1,a6,a7
	bgeu	a2,a3,.L103
	mv	a2,a3
.L103:
	beq	a5,a1,.L108
	bleu	a1,a2,.L105
	bltu	a5,a1,.L105
.L106:
	bleu	a1,a2,.L105
	ret
.L108:
	bgeu	a4,a0,.L106
.L105:
	sgtu	a3,a4,a0
	sub	a1,a1,a3
	sub	a1,a1,a5
	sub	a0,a0,a4
	ret
	.size	addmod128, .-addmod128
	.align	1
	.globl	submod128
	.type	submod128, @function
submod128:
	sltu	a6,a0,a2
	mv	a7,a1
	add	a3,a6,a3
	sub	a0,a0,a2
	sub	a1,a1,a3
	bgeu	a7,a3,.L110
	mv	a3,a4
	add	a4,a4,a0
	bltu	a3,a0,.L112
	sltu	a3,a4,a3
	add	a1,a3,a1
	add	a1,a1,a5
	mv	a0,a4
.L110:
	ret
.L112:
	mv	a3,a0
	sltu	a3,a4,a3
	add	a1,a3,a1
	add	a1,a1,a5
	mv	a0,a4
	j	.L110
	.size	submod128, .-submod128
	.align	1
	.globl	mul64
	.type	mul64, @function
mul64:
	li	a6,-1
	srli	a6,a6,32
	srli	a7,a2,32
	and	a4,a3,a6
	mul	a4,a4,a7
	and	a6,a2,a6
	srli	t1,a3,32
	mul	a6,a6,t1
	mv	a5,a4
	mul	a2,a2,a3
	add	a4,a4,a6
	bgeu	a5,a6,.L114
	mv	a5,a6
.L114:
	slli	a6,a4,32
	sltu	a5,a4,a5
	srli	a3,a2,32
	srli	a6,a6,32
	srli	a4,a4,32
	slli	a5,a5,32
	mul	a7,a7,t1
	sltu	a3,a3,a6
	or	a5,a5,a4
	add	a4,a3,a7
	add	a5,a5,a4
	sd	a5,0(a0)
	sd	a2,0(a1)
	ret
	.size	mul64, .-mul64
	.align	1
	.globl	mullo64
	.type	mullo64, @function
mullo64:
	mul	a0,a0,a1
	ret
	.size	mullo64, .-mullo64
	.align	1
	.globl	mulhi64
	.type	mulhi64, @function
mulhi64:
	li	a2,-1
	srli	a2,a2,32
	srli	a7,a0,32
	srli	t1,a1,32
	and	a4,a1,a2
	and	a6,a0,a2
	mul	a4,a4,a7
	mul	a6,a6,t1
	mv	a3,a4
	mul	a5,a0,a1
	add	a4,a4,a6
	and	a2,a4,a2
	mul	a7,a7,t1
	srli	a5,a5,32
	sltu	a5,a5,a2
	add	a5,a5,a7
	bgeu	a3,a6,.L117
	mv	a3,a6
.L117:
	sltu	a0,a4,a3
	slli	a0,a0,32
	srli	a4,a4,32
	or	a0,a0,a4
	add	a0,a5,a0
	ret
	.size	mulhi64, .-mulhi64
	.align	1
	.globl	mul128
	.type	mul128, @function
mul128:
	addi	sp,sp,-80
	sd	s0,72(sp)
	sd	s1,64(sp)
	sd	s2,56(sp)
	sd	s3,48(sp)
	sd	s4,40(sp)
	sd	s5,32(sp)
	sd	s6,24(sp)
	sd	s7,16(sp)
	sd	s8,8(sp)
	add	t5,a2,a3
	mv	t6,a3
	bltu	a2,a3,.L119
	mv	t6,a2
.L119:
	li	a7,-1
	add	s2,a4,a5
	srli	a7,a7,32
	and	a6,s2,a7
	srli	s4,t5,32
	mul	a6,a6,s4
	srli	t4,s2,32
	and	a7,t5,a7
	sltu	t6,t5,t6
	sltu	t1,s2,a4
	mul	a7,a7,t4
	mv	t3,a6
	mul	t0,t5,s2
	add	a6,a6,a7
	bgeu	t3,a7,.L122
	mv	t3,a7
.L122:
	li	a7,-1
	srli	a7,a7,32
	and	s8,a5,a7
	srli	s0,a3,32
	srli	s1,a5,32
	and	s3,a3,a7
	mul	s4,s4,t4
	and	a7,a6,a7
	sltu	t3,a6,t3
	srli	t4,t0,32
	sltu	t4,t4,a7
	srli	a6,a6,32
	slli	t3,t3,32
	neg	a7,t6
	neg	t2,t1
	or	t3,t3,a6
	mul	s8,s8,s0
	add	a6,t4,s4
	and	a7,a7,s2
	and	t2,t2,t5
	add	t3,t3,a6
	add	t5,a7,t2
	add	t4,t5,t3
	mul	s3,s3,s1
	mv	a6,s8
	mul	a5,a3,a5
	add	s8,s8,s3
	bgeu	a6,s3,.L123
	mv	a6,s3
.L123:
	li	s7,-1
	srli	s7,s7,32
	and	s4,a4,s7
	and	s6,a2,s7
	srli	s2,a2,32
	srli	s3,a4,32
	mul	s0,s0,s1
	sltu	a3,s8,a6
	and	s7,s8,s7
	srli	s5,a5,32
	slli	a3,a3,32
	srli	s8,s8,32
	sltu	s5,s5,s7
	or	a3,a3,s8
	mul	s4,s4,s2
	add	s0,s5,s0
	add	a3,a3,s0
	mul	s6,s6,s3
	mv	a6,s4
	mul	a4,a2,a4
	add	a2,s4,s6
	bgeu	s4,s6,.L124
	mv	a6,s6
.L124:
	slli	s1,a2,32
	sltu	a6,a2,a6
	srli	s1,s1,32
	srli	s0,a4,32
	sltu	s0,s0,s1
	slli	a6,a6,32
	mul	s2,s2,s3
	srli	a2,a2,32
	or	a6,a6,a2
	add	s3,a4,a5
	mv	s1,a4
	add	s2,s0,s2
	add	a6,a6,s2
	bgeu	a4,a5,.L125
	mv	s1,a5
.L125:
	sltu	s1,s3,s1
	add	s1,s1,a3
	sgtu	a2,s3,t0
	add	s0,s1,a6
	add	a2,a2,s0
	sub	s2,t0,s3
	sub	t0,t4,a2
	bgeu	a7,t2,.L126
	mv	a7,t2
.L126:
	and	t6,t1,t6
	add	a3,t6,a3
	sltu	t1,t5,a7
	add	t1,t1,a3
	mv	a7,t5
	bgeu	t5,t3,.L127
	mv	a7,t3
.L127:
	sltu	a7,t4,a7
	mv	a3,s1
	add	t1,t1,a7
	bgeu	s1,a6,.L128
	mv	a3,a6
.L128:
	add	a6,s2,a6
	snez	t3,s2
	sltu	a7,a6,s2
	or	a7,a7,t3
	andi	a7,a7,0xff
	sltu	s0,s0,a3
	add	t3,a7,t0
	sub	t1,t1,s0
	add	a3,t3,a5
	bgeu	a7,t0,.L131
	mv	a7,t0
.L131:
	sltu	t4,t4,a2
	sltu	a7,t3,a7
	sub	t1,t1,t4
	add	a7,a7,t1
	bgeu	t3,a5,.L132
	mv	t3,a5
.L132:
	sltu	t3,a3,t3
	ld	s0,72(sp)
	add	a7,a7,t3
	sd	a3,0(a0)
	sd	a7,8(a0)
	sd	a4,0(a1)
	sd	a6,8(a1)
	ld	s1,64(sp)
	ld	s2,56(sp)
	ld	s3,48(sp)
	ld	s4,40(sp)
	ld	s5,32(sp)
	ld	s6,24(sp)
	ld	s7,16(sp)
	ld	s8,8(sp)
	addi	sp,sp,80
	jr	ra
	.size	mul128, .-mul128
	.align	1
	.globl	mullo128
	.type	mullo128, @function
mullo128:
	li	a7,-1
	srli	a7,a7,32
	srli	t3,a0,32
	srli	t4,a2,32
	and	a5,a2,a7
	and	t1,a0,a7
	mul	a5,a5,t3
	mv	a6,a0
	mul	t1,t1,t4
	mv	a4,a5
	mul	a0,a0,a2
	add	a5,a5,t1
	and	a7,a5,a7
	mul	a2,a2,a1
	srli	a1,a0,32
	sltu	a1,a1,a7
	mul	t3,t3,t4
	mul	a6,a6,a3
	add	a2,a2,t3
	add	a2,a2,a6
	add	a2,a2,a1
	bgeu	a4,t1,.L136
	mv	a4,t1
.L136:
	sltu	a1,a5,a4
	slli	a1,a1,32
	srli	a5,a5,32
	or	a1,a1,a5
	add	a1,a2,a1
	ret
	.size	mullo128, .-mullo128
	.align	1
	.globl	mulhi128
	.type	mulhi128, @function
mulhi128:
	li	a5,-1
	addi	sp,sp,-32
	srli	a5,a5,32
	srli	t0,a2,32
	and	a6,a2,a5
	sd	s0,24(sp)
	sd	s1,16(sp)
	srli	s0,a0,32
	and	s1,a0,a5
	mul	t5,s0,a6
	sd	s2,8(sp)
	mul	a4,s1,t0
	mv	t1,t5
	mul	a7,a0,a2
	add	t5,t5,a4
	and	a5,t5,a5
	mul	t3,s0,t0
	srli	a7,a7,32
	sltu	a7,a7,a5
	add	a7,a7,t3
	bgeu	t1,a4,.L138
	mv	t1,a4
.L138:
	li	a5,-1
	srli	a5,a5,32
	srli	t4,a3,32
	and	a4,a3,a5
	mul	t6,a4,s0
	sltu	t1,t5,t1
	srli	t3,a1,32
	srli	t5,t5,32
	slli	t1,t1,32
	and	t2,a1,a5
	or	t1,t1,t5
	add	a7,a7,t1
	mul	s1,t4,s1
	mv	t1,t6
	mul	a0,a0,a3
	add	t6,t6,s1
	and	a5,t6,a5
	mul	t5,t3,t0
	srli	s2,a0,32
	sltu	a5,s2,a5
	mul	s0,t4,s0
	mul	t0,t2,t0
	add	t5,t5,s0
	add	a5,a5,t5
	mul	a6,t3,a6
	mul	a2,a1,a2
	add	s0,a6,t0
	mul	a4,t3,a4
	add	a0,a2,a0
	mul	t2,t2,t4
	mul	a3,a1,a3
	add	t5,a4,t2
	bgeu	t1,s1,.L139
	mv	t1,s1
.L139:
	sltu	t1,t6,t1
	slli	t1,t1,32
	srli	t6,t6,32
	slli	a1,s0,32
	or	t1,t1,t6
	srli	a2,a2,32
	srli	a1,a1,32
	add	a5,a5,t1
	sltu	a2,a2,a1
	add	a5,a5,a2
	bgeu	a6,t0,.L140
	mv	a6,t0
.L140:
	sltu	a6,s0,a6
	slli	a6,a6,32
	srli	s0,s0,32
	or	a6,a6,s0
	mv	a2,a0
	add	a5,a5,a6
	add	a0,a0,a7
	bgeu	a2,a7,.L141
	mv	a2,a7
.L141:
	sltu	a0,a0,a2
	add	a5,a5,a0
	add	a0,a5,a3
	bgeu	a4,t2,.L142
	mv	a4,t2
.L142:
	mul	t3,t3,t4
	slli	a2,t5,32
	sltu	a1,t5,a4
	srli	a2,a2,32
	srli	a4,a3,32
	slli	a1,a1,32
	srli	t5,t5,32
	sltu	a4,a4,a2
	or	a1,a1,t5
	add	t3,a4,t3
	add	a1,a1,t3
	bgeu	a5,a3,.L143
	mv	a5,a3
.L143:
	ld	s0,24(sp)
	sltu	a5,a0,a5
	ld	s1,16(sp)
	ld	s2,8(sp)
	add	a1,a1,a5
	addi	sp,sp,32
	jr	ra
	.size	mulhi128, .-mulhi128
	.align	1
	.globl	mulmod128
	.type	mulmod128, @function
mulmod128:
	addi	sp,sp,-96
	sd	s1,72(sp)
	sd	s2,64(sp)
	mv	s1,a4
	mv	s2,a5
	mv	a4,a2
	mv	a5,a3
	mv	a2,a0
	mv	a3,a1
	addi	a0,sp,16
	mv	a1,sp
	sd	ra,88(sp)
	sd	s0,80(sp)
	sd	s3,56(sp)
	sd	s4,48(sp)
	sd	s5,40(sp)
	mv	s4,a6
	mv	s5,a7
	call	mul128
	ld	a0,16(sp)
	ld	s0,24(sp)
	ld	s3,8(sp)
	srli	a1,a0,58
	slli	a5,s0,6
	srli	a4,s3,58
	slli	a0,a0,6
	mv	a3,s5
	or	a0,a4,a0
	mv	a2,s4
	or	a1,a1,a5
	call	mulhi128
	srli	s0,s0,58
	mul	a6,s0,s4
	ld	a4,0(sp)
	mv	a3,a6
	add	a6,a6,a0
	bgeu	a3,a0,.L146
	mv	a3,a0
.L146:
	sgtu	a3,a3,a6
	add	a1,a3,a1
	slli	a5,a1,63
	srli	a6,a6,1
	li	a0,-1
	or	a2,a6,a5
	srli	a0,a0,32
	srli	t1,a2,32
	and	a7,a2,a0
	srli	t4,s1,32
	and	a6,s1,a0
	mul	a6,a6,t1
	srli	a3,a1,1
	mul	a7,a7,t4
	mv	a5,a6
	mul	t3,s1,a2
	add	a1,a6,a7
	and	a0,a1,a0
	mul	a3,s1,a3
	srli	a6,t3,32
	sltu	a0,a6,a0
	mul	t1,t1,t4
	mul	a2,s2,a2
	add	a3,a3,t1
	add	a3,a3,a2
	add	a3,a3,a0
	bgeu	a5,a7,.L147
	mv	a5,a7
.L147:
	sltu	a5,a1,a5
	slli	a5,a5,32
	srli	a1,a1,32
	or	a5,a5,a1
	sub	a2,a4,t3
	add	a3,a3,a5
	mv	a0,a2
	sub	a1,s3,a3
	sgtu	a4,a4,a2
	li	a5,1
	bne	a3,zero,.L148
	sgtu	a5,t3,a2
.L148:
	or	a4,a4,a5
	andi	a4,a4,0xff
	sub	a1,a1,a4
	beq	s2,a1,.L158
	bgtu	s2,a1,.L155
	mv	a5,s1
	sub	a0,a2,s1
	bltu	s1,a2,.L159
	sgtu	a5,a5,a0
	add	a5,a5,s2
	sub	a1,a1,a5
.L155:
	ld	ra,88(sp)
	ld	s0,80(sp)
	ld	s1,72(sp)
	ld	s2,64(sp)
	ld	s3,56(sp)
	ld	s4,48(sp)
	ld	s5,40(sp)
	addi	sp,sp,96
	jr	ra
.L158:
	bgtu	s1,a2,.L155
	mv	a1,s1
	sub	a0,a2,s1
	bgeu	s1,a2,.L154
	mv	a1,a2
.L154:
	sltu	a1,a0,a1
	neg	a1,a1
	j	.L155
.L159:
	mv	a5,a2
	sgtu	a5,a5,a0
	add	a5,a5,s2
	sub	a1,a1,a5
	j	.L155
	.size	mulmod128, .-mulmod128
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC0:
	.string	"\nmode = C"
	.align	3
.LC1:
	.string	", USE_KARATSUBA"
	.align	3
.LC2:
	.string	", MBIT = 124"
	.align	3
.LC3:
	.string	"\n"
	.text
	.align	1
	.globl	printconf
	.type	printconf, @function
printconf:
	lui	a0,%hi(.LC0)
	addi	sp,sp,-16
	addi	a0,a0,%lo(.LC0)
	sd	ra,8(sp)
	call	printf
	lui	a0,%hi(.LC1)
	addi	a0,a0,%lo(.LC1)
	call	printf
	lui	a0,%hi(.LC2)
	addi	a0,a0,%lo(.LC2)
	call	printf
	ld	ra,8(sp)
	lui	a0,%hi(.LC3)
	addi	a0,a0,%lo(.LC3)
	addi	sp,sp,16
	tail	puts
	.size	printconf, .-printconf
	.section	.rodata.str1.8
	.align	3
.LC4:
	.string	"ok"
	.align	3
.LC5:
	.string	"fail"
	.align	3
.LC15:
	.string	"(0x%llX%016llX + 0x%llX%016llX) %% 0x%llX%016llX = 0x%llX%016llX\n"
	.align	3
.LC17:
	.string	"%s\n\n"
	.align	3
.LC19:
	.string	"(0x%llX%016llX - 0x%llX%016llX) %% 0x%llX%016llX = 0x%llX%016llX\n"
	.align	3
.LC24:
	.string	"0x%llX%016llX * 0x%llX%016llX = 0x%llX%016llX%016llX%016llX\n"
	.align	3
.LC26:
	.string	"0x%llX%016llX *lo 0x%llX%016llX = 0x%llX%016llX\n"
	.align	3
.LC27:
	.string	"0x%llX%016llX *hi 0x%llX%016llX = 0x%llX%016llX\n"
	.align	3
.LC29:
	.string	"(0x%llX%016llX * 0x%llX%016llX) %% 0x%llX%016llX = 0x%llX%016llX\n"
	.section	.text.startup,"ax",@progbits
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-240
	lui	a4,%hi(.LC6)
	lui	a5,%hi(.LC7)
	sd	s0,224(sp)
	sd	s1,216(sp)
	ld	s0,%lo(.LC7+8)(a5)
	ld	s1,%lo(.LC7)(a5)
	sd	s2,208(sp)
	sd	s3,200(sp)
	ld	s2,%lo(.LC6+8)(a4)
	ld	s3,%lo(.LC6)(a4)
	mv	a2,s1
	mv	a5,s2
	mv	a4,s3
	mv	a3,s0
	addi	a1,sp,96
	addi	a0,sp,112
	sd	ra,232(sp)
	sd	s4,192(sp)
	sd	s5,184(sp)
	sd	s6,176(sp)
	sd	s7,168(sp)
	sd	s8,160(sp)
	sd	s9,152(sp)
	sd	s10,144(sp)
	sd	s11,136(sp)
	call	mul128
	mv	a2,s3
	mv	a3,s2
	mv	a0,s1
	mv	a1,s0
	call	mullo128
	mv	s8,a0
	mv	s9,a1
	mv	a2,s3
	mv	a3,s2
	mv	a0,s1
	mv	a1,s0
	call	mulhi128
	lui	a5,%hi(.LC9)
	ld	s10,%lo(.LC9+8)(a5)
	lui	a5,%hi(.LC8)
	ld	a7,%lo(.LC8+8)(a5)
	mv	t3,a0
	mv	t1,a1
	mv	a5,s10
	li	a6,472
	li	a4,-59
	mv	a2,s3
	mv	a3,s2
	mv	a0,s1
	mv	a1,s0
	sd	t3,32(sp)
	sd	t1,40(sp)
	call	mulmod128
	mv	s6,a0
	sd	a1,24(sp)
	call	printconf
	lui	a5,%hi(.LC10)
	ld	s11,%lo(.LC10)(a5)
	lui	a5,%hi(.LC16)
	ld	s5,%lo(.LC16)(a5)
	lui	s4,%hi(.LC15)
	mv	a7,s11
	mv	a5,s10
	li	a6,-59
	mv	a4,s3
	mv	a3,s2
	mv	a2,s1
	mv	a1,s0
	sd	s5,0(sp)
	addi	a0,s4,%lo(.LC15)
	call	printf
	mv	a7,s11
	mv	a5,s10
	li	a6,-59
	mv	a4,s3
	mv	a3,s2
	mv	a2,s1
	mv	a1,s0
	sd	s5,0(sp)
	addi	a0,s4,%lo(.LC15)
	call	printf
	lui	s4,%hi(.LC4)
	lui	s5,%hi(.LC17)
	addi	a1,s4,%lo(.LC4)
	addi	a0,s5,%lo(.LC17)
	call	printf
	lui	a5,%hi(.LC18)
	ld	a7,%lo(.LC18)(a5)
	lui	a5,%hi(.LC20)
	ld	s7,%lo(.LC20)(a5)
	lui	s11,%hi(.LC19)
	mv	a5,s10
	li	a6,-59
	mv	a4,s3
	mv	a3,s2
	mv	a2,s1
	mv	a1,s0
	sd	s7,0(sp)
	addi	a0,s11,%lo(.LC19)
	call	printf
	lui	a4,%hi(.LC18)
	ld	a7,%lo(.LC18)(a4)
	mv	a5,s10
	li	a6,-59
	mv	a4,s3
	mv	a3,s2
	mv	a2,s1
	mv	a1,s0
	sd	s7,0(sp)
	addi	a0,s11,%lo(.LC19)
	call	printf
	addi	a1,s4,%lo(.LC4)
	addi	a0,s5,%lo(.LC17)
	call	printf
	lui	a5,%hi(.LC25)
	ld	s7,%lo(.LC25)(a5)
	lui	a5,%hi(.LC21)
	ld	a7,%lo(.LC21)(a5)
	lui	a5,%hi(.LC22)
	ld	a4,%lo(.LC22)(a5)
	lui	a5,%hi(.LC23)
	ld	a3,%lo(.LC23)(a5)
	lui	s10,%hi(.LC24)
	mv	a6,a4
	mv	a5,a3
	sd	a4,72(sp)
	sd	a3,88(sp)
	mv	a4,s3
	mv	a3,s2
	mv	a2,s1
	mv	a1,s0
	sd	s7,0(sp)
	addi	a0,s10,%lo(.LC24)
	sd	a7,56(sp)
	call	printf
	ld	a4,112(sp)
	ld	s11,96(sp)
	ld	a7,104(sp)
	ld	a5,120(sp)
	mv	a6,a4
	sd	a4,64(sp)
	mv	a3,s2
	mv	a4,s3
	mv	a2,s1
	mv	a1,s0
	sd	s11,0(sp)
	addi	a0,s10,%lo(.LC24)
	sd	a7,48(sp)
	sd	a5,80(sp)
	call	printf
	lui	a0,%hi(.LC26)
	mv	a6,s8
	mv	a5,s9
	mv	a4,s3
	mv	a3,s2
	mv	a2,s1
	mv	a1,s0
	addi	a0,a0,%lo(.LC26)
	call	printf
	ld	a6,32(sp)
	ld	a5,40(sp)
	lui	a0,%hi(.LC27)
	mv	a4,s3
	mv	a3,s2
	mv	a2,s1
	mv	a1,s0
	addi	a0,a0,%lo(.LC27)
	call	printf
	ld	a7,48(sp)
	beq	s11,s7,.L171
.L168:
	lui	a1,%hi(.LC5)
	addi	a1,a1,%lo(.LC5)
.L163:
	addi	a0,s5,%lo(.LC17)
	call	printf
	lui	a5,%hi(.LC11)
	ld	s9,%lo(.LC11)(a5)
	lui	a5,%hi(.LC12)
	ld	s8,%lo(.LC12)(a5)
	lui	a5,%hi(.LC13)
	ld	s3,%lo(.LC13)(a5)
	lui	a5,%hi(.LC14)
	ld	s2,%lo(.LC14)(a5)
	lui	a5,%hi(.LC30)
	ld	s0,%lo(.LC30)(a5)
	lui	a5,%hi(.LC28)
	ld	s11,%lo(.LC28)(a5)
	li	s10,-1
	lui	s1,%hi(.LC29)
	mv	a7,s11
	li	a6,-59
	srli	a5,s10,4
	mv	a4,s9
	mv	a3,s8
	mv	a2,s3
	mv	a1,s2
	sd	s0,0(sp)
	addi	a0,s1,%lo(.LC29)
	call	printf
	ld	a7,24(sp)
	sd	s6,0(sp)
	li	a6,-59
	srli	a5,s10,4
	mv	a4,s9
	mv	a3,s8
	mv	a2,s3
	mv	a1,s2
	addi	a0,s1,%lo(.LC29)
	call	printf
	beq	s6,s0,.L172
.L169:
	lui	a1,%hi(.LC5)
	addi	a1,a1,%lo(.LC5)
.L164:
	addi	a0,s5,%lo(.LC17)
	call	printf
	ld	ra,232(sp)
	ld	s0,224(sp)
	ld	s1,216(sp)
	ld	s2,208(sp)
	ld	s3,200(sp)
	ld	s4,192(sp)
	ld	s5,184(sp)
	ld	s6,176(sp)
	ld	s7,168(sp)
	ld	s8,160(sp)
	ld	s9,152(sp)
	ld	s10,144(sp)
	ld	s11,136(sp)
	li	a0,0
	addi	sp,sp,240
	jr	ra
.L171:
	ld	a5,56(sp)
	bne	a7,a5,.L168
	bne	s8,s11,.L168
	bne	s9,a7,.L168
	ld	a5,64(sp)
	ld	a4,72(sp)
	bne	a5,a4,.L168
	ld	a5,80(sp)
	ld	a4,88(sp)
	bne	a5,a4,.L168
	ld	a5,32(sp)
	ld	a4,64(sp)
	bne	a5,a4,.L168
	ld	a5,40(sp)
	ld	a4,80(sp)
	addi	a1,s4,%lo(.LC4)
	bne	a5,a4,.L168
	j	.L163
.L172:
	ld	a5,24(sp)
	addi	a1,s4,%lo(.LC4)
	bne	a5,s11,.L169
	j	.L164
	.size	main, .-main
	.section	.rodata.cst16,"aM",@progbits,16
	.align	4
.LC6:
	.dword	-994074541749903632
	.dword	1611924972585761
	.align	4
.LC7:
	.dword	-81986143110479071
	.dword	920735923817967
	.align	4
.LC8:
	.dword	472
	.dword	-9223372036854775808
	.align	4
.LC9:
	.dword	-59
	.dword	1152921504606846975
	.section	.srodata.cst8,"aM",@progbits,8
	.align	3
.LC10:
	.dword	2532660896403729
	.set	.LC11,.LC6
	.set	.LC12,.LC6+8
	.set	.LC13,.LC7
	.set	.LC14,.LC7+8
	.align	3
.LC16:
	.dword	-1076060684860382703
	.align	3
.LC18:
	.dword	1152230315558079182
	.align	3
.LC20:
	.dword	912088398639424502
	.align	3
.LC21:
	.dword	-4771981074513326528
	.align	3
.LC22:
	.dword	-8690077056370338552
	.align	3
.LC23:
	.dword	80456324586
	.align	3
.LC25:
	.dword	247014701301599472
	.align	3
.LC28:
	.dword	992702399291318035
	.align	3
.LC30:
	.dword	5615386288452476153
	.ident	"GCC: (g2ee5e430018) 12.2.0"
