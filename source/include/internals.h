
/*============================================================================

This C header file is part of the SoftPosit Posit Arithmetic Package
by S. H. Leong (Cerlane).

Copyright 2017, 2018 A*STAR.  All rights reserved.

This C header file is part of the SoftFloat IEEE Floating-Point Arithmetic
Package, Release 3d, by John R. Hauser.

Copyright 2011, 2012, 2013, 2014, 2015, 2016, 2017 The Regents of the
University of California.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions, and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions, and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

 3. Neither the name of the University nor the names of its contributors may
    be used to endorse or promote products derived from this software without
    specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS "AS IS", AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ARE
DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=============================================================================*/

#ifndef internals_h
#define internals_h 1

#include <stdbool.h>
#include <stdint.h>

#include "softposit_types.h"

#include <stdio.h>

#ifdef SOFTPOSIT_EXACT
	typedef struct { uint8_t v; bool exact; } uint8e_t;
	typedef struct { uint16_t v; bool exact; } uint16e_t;
	typedef struct { uint32_t v; bool exact; } uint32e_t;
	typedef struct { uint64_t v; bool exact; } uint64e_t;
	typedef struct { uint64_t v[2]; bool exact; } uint128e_t;

	union ui8_p8   { uint8e_t ui; posit8_t p; };
	union ui16_p16 { uint16e_t ui; posit16_t p; };
	union ui32_p32 { uint32e_t ui; posit32_t p; };
	union ui64_p64 { uint64e_t ui; posit64_t p; };

	union ui128_q16 { uint64_t ui[2]; quire16_t q; };
#else
	union ui8_p8   { uint8_t ui; posit8_t p; };
	union ui16_p16 { uint16_t ui; posit16_t p; };
	union ui32_p32 { uint32_t ui; posit32_t p; };
	union ui64_p64 { uint64_t ui; posit64_t p; };
	union ui128_p128c {uint64_t ui[2]; posit128_t p;}; //c to differentiate from original implementation
	union ui32_q8 {
		uint32_t ui;
		quire8_t q;
	};
	union ui128_q16 {
		struct{
			uint64_t left64;
			uint64_t right64;
		} ui;
		quire16_t q;
	};

	union ui512_q32 {
		uint64_t ui[8];
		quire32_t q;
	};
#endif

enum {
    softposit_mulAdd_subC    = 1,
    softposit_mulAdd_subProd = 2
};


/*----------------------------------------------------------------------------
*----------------------------------------------------------------------------*/
/*#define signP8UI( a ) ((bool) ((uint8_t) (a)>>7))
#define signregP8UI( a ) ((bool) (((uint8_t) (a)>>6) & 0x1))
#define packToP8UI( regime, fracA) ((uint8_t) regime + ((uint8_t)(fracA)) )
uint_fast16_t reglengthP8UI (uint8_t);
int regkP8UI (uint8_t);
#define regP8UI( a ) (( ((uint8_t) (a) & (0x7F)) >> max(0, 6-reglengthP8UI(a) ) ))
#define useed8P 2;
#define expP8UI(a) ((int_fast8_t)  0)
#define expP8sizeUI 0;
uint_fast16_t fracP8UI(uint8_t);

#define isNaRP8UI( a ) ( ((a) ^ 0x80) == 0 )

posit8_t softposit_addMagsP8( uint_fast8_t, uint_fast8_t );
posit8_t softposit_subMagsP8( uint_fast8_t, uint_fast8_t );
posit8_t softposit_mulAddP8( uint_fast8_t, uint_fast8_t, uint_fast8_t, uint_fast8_t );

double convertP8ToDec_f(posit8_t);
posit8 convertP8ToDec(posit8_t);
posit8_t convertDoubleToP8(double);
posit8_t convertDecToP8(posit8);


//Quire 8
quire8_t q8_fdp_add(quire8_t, posit8_t, posit8_t);
quire8_t q8_fdp_sub(quire8_t, posit8_t, posit8_t);
posit8_t convertQ8ToP8(quire8_t);
#define isNaRQ8( q ) ( q.v==0x80000000  )
#define isQ8Zero(q) ( q.v==0 )
#define q8_clr(q) ({\
	q.v=0;\
	q;\
})*/


/*----------------------------------------------------------------------------
*----------------------------------------------------------------------------*/
#define signP16UI( a ) ( (bool) ( ( uint16_t ) (a)>>15 ) )
#define signregP16UI( a ) ( (bool) (((uint16_t) (a)>>14) & 0x1) )
#define expP16UI( a, regA ) ((int_fast8_t) ((a)>>(13-regA) & 0x0001))
#define packToP16UI( regime, regA, expA, fracA) ((uint16_t) regime + ((uint16_t) (expA)<< (13-regA)) + ((uint16_t)(fracA)) )
uint_fast16_t reglengthP16UI ( uint_fast16_t );
int_fast8_t regkP16UI ( bool , uint_fast16_t );
uint_fast16_t fracP16UI( uint_fast16_t, uint_fast16_t);
#define regP16UI( a, regLen )  ( ( uint_fast16_t ) (((a) & (0x7FFF)) >> (14-regLen)) )
#define USEED16P 4;
#define MAXPOS16P 0x7FFF; //integer value (not actual posit computed value)

#define expP16sizeUI 1;

double convertP16ToDec_f(posit16_t);
posit16 convertP16ToDec(posit16_t);
posit16_t convertDecToP16(posit16);
posit16_t convertfloatToP16(float);
posit16_t convertdoubleToP16(double);
//__float128 convertP16ToQuadDec(posit16_t);
//posit16_t convertQuadToP16(__float128);

posit16 p16_dec_add(posit16, posit16 );
posit16 p16_dec_sub(posit16, posit16 );
posit16 p16_dec_mul(posit16, posit16 );
float p16_dec_add_f(float, float );
float p16_dec_sub_f(float, float );
float p16_dec_mul_f(float, float );
#define isNaRP16UI( a ) ( ((a) ^ 0x8000) == 0 )

int_fast64_t p16_to_i64_2( posit16_t );

//Quire 16
quire16_t q16_fdp_add(quire16_t, posit16_t, posit16_t);
quire16_t q16_fdp_sub(quire16_t, posit16_t, posit16_t);
posit16_t convertQ16ToP16(quire16_t);
#define isNaRQ16( q ) ( q.v[0]==0x8000000000000000ULL && q.v[1]==0 )
#define isQ16Zero(q) (q.v[0]==0 && q.v[1]==0)
quire16_t q16_TwosComplement(quire16_t);
void printBinary(uint64_t*, int);
#define q16_clr(q) ({\
	q.v[0]=0;\
	q.v[1]=0;\
	q;\
})

posit16_t softposit_addMagsP16( uint_fast16_t, uint_fast16_t );
posit16_t softposit_subMagsP16( uint_fast16_t, uint_fast16_t );
posit16_t softposit_mulAddP16( uint_fast16_t, uint_fast16_t, uint_fast16_t, uint_fast16_t );

/*----------------------------------------------------------------------------
*----------------------------------------------------------------------------*/
/*#define signP32UI( a ) ((bool) ((uint32_t) (a)>>31))
#define signregP32UI( a ) ((bool) (((uint32_t) (a)>>30) & 0x1))
#define packToP32UI(regime, expA, fracA) ( (uint32_t) regime + (uint32_t) expA + ((uint32_t)(fracA)) )
uint_fast16_t reglengthP32UI (uint32_t);
int_fast16_t regkP32UI(bool, uint_fast32_t);
#define expP32UI( a, regA ) ((int_fast16_t) ((a>>(28-regA)) & 0x2))
#define regP32UI( a, regLen ) (  ((( uint_fast32_t ) (a) & (0x7FFFFFFF)) >> (30-regLen))) )
#define isNaRP32UI( a ) ( ((a) ^ 0x80000000) == 0 )
#define useed32P 16;
//int_fast16_t expP32UI(uint32_t);
#define expP32sizeUI 2;
uint_fast32_t fracP32UI(uint_fast32_t, uint_fast16_t);

double convertP32ToDec_f(posit32_t);
posit32 convertP32ToDec(posit32_t);
posit32_t convertDecToP32(posit32);
posit32_t convertfloatToP32(float);
posit32_t convertdoubleToP32(double );
//posit32_t convertQuadToP32(__float128);
//__float128 convertP32ToQuadDec(posit32_t);


//posit32_t c_roundPackToP32( bool, bool, int_fast16_t, int_fast16_t, uint_fast16_t, bool, bool );

//#define isNaNP32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & 0x007FFFFF))


//posit32_t softposit_roundPackToP32( bool, int_fast16_t, uint_fast32_t );
//posit32_t softposit_normRoundPackToP32( bool, int_fast16_t, uint_fast32_t );

posit32_t softposit_addMagsP32( uint_fast32_t, uint_fast32_t );
posit32_t softposit_subMagsP32( uint_fast32_t, uint_fast32_t );
posit32_t softposit_mulAddP32(uint_fast32_t, uint_fast32_t, uint_fast32_t, uint_fast16_t);


//quire32_t quire32_add(quire32_t, quire32_t);
//quire32_t quire32_sub(quire32_t, quire32_t);
quire32_t quire32_mul(posit32_t, posit32_t);
quire32_t q32_fdp_add(quire32_t, posit32_t, posit32_t);
quire32_t q32_fdp_sub(quire32_t, posit32_t, posit32_t);
posit32_t convertQ32ToP32(quire32_t);
#define isNaRQ32( q ) ( q.v[0]==0x8000000000000000ULL && q.v[1]==0 && q.v[2]==0 && q.v[3]==0 && q.v[4]==0 && q.v[5]==0 && q.v[6]==0 && q.v[7]==0)
#define isQ32Zero(q) (q.v[0]==0 && q.v[1]==0 && q.v[2]==0 && q.v[3]==0 && q.v[4]==0 && q.v[5]==0 && q.v[6]==0 && q.v[7]==0)
quire32_t q32_TwosComplement(quire32_t);
#define q32_clr(q) ({\
	q.v[0]=0;\
	q.v[1]=0;\
	q.v[2]=0;\
	q.v[3]=0;\
	q.v[4]=0;\
	q.v[5]=0;\
	q.v[6]=0;\
	q.v[7]=0;\
	q;\
})
*/


#endif



