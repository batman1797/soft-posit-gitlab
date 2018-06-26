
/*============================================================================

This C header file is part of the SoftPosit Posit Arithmetic Package
by S. H. Leong (Cerlane).

Copyright 2017, 2018 A*STAR.  All rights reserved.

This C header file was based on SoftFloat IEEE Floating-Point Arithmetic
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


/*============================================================================
| Note:  If SoftPosit is modified from SoftFloat and is made available as a
| general library for programs to use, it is strongly recommended that a
| platform-specific version of this header, "softposit.h", be created that
| folds in "softposit_types.h" and that eliminates all dependencies on
| compile-time macros.
*============================================================================*/


#ifndef softposit_h
#define softposit_h 1

#include <stdbool.h>
#include <stdint.h>

#ifdef SOFTPOSIT_QUAD
#include <quadmath.h>
#endif

#include "softposit_types.h"

#include <stdio.h>


#ifndef THREAD_LOCAL
#define THREAD_LOCAL
#endif


/*----------------------------------------------------------------------------
| Integer-to-posit conversion routines.
*----------------------------------------------------------------------------*/
posit8_t  ui32_to_p8( uint32_t );
posit16_t ui32_to_p16( uint32_t );
posit32_t ui32_to_p32( uint32_t );
posit64_t ui32_to_p64( uint32_t );


posit8_t  ui64_to_p8( uint64_t );
posit16_t ui64_to_p16( uint64_t );
posit32_t ui64_to_p32( uint64_t );
posit64_t ui64_to_p64( uint64_t );

posit8_t  i32_to_p8( int32_t );
posit16_t i32_to_p16( int32_t );
posit32_t i32_to_p32( int32_t );
posit64_t i32_to_p64( int32_t );

posit8_t  i64_to_p8( int64_t );
posit16_t i64_to_p16( int64_t );
posit32_t i64_to_p32( int64_t );
posit64_t i64_to_p64( int64_t );



/*----------------------------------------------------------------------------
| 8-bit (quad-precision) posit operations.
*----------------------------------------------------------------------------*/
#define isNaRP8UI( a ) ( (a ^ 0x80) == 0 )

uint_fast32_t p8_to_ui32( posit8_t );
uint_fast64_t p8_to_ui64( posit8_t );
int_fast32_t p8_to_i32( posit8_t);
int_fast64_t p8_to_i64( posit8_t);

posit16_t p8_to_p16( posit8_t );
posit32_t p8_to_p32( posit8_t );
//posit64_t p8_to_p64( posit8_t );

posit8_t p8_roundToInt( posit8_t );
posit8_t p8_add( posit8_t, posit8_t );
posit8_t p8_sub( posit8_t, posit8_t );
posit8_t p8_mul( posit8_t, posit8_t );
posit8_t p8_mulAdd( posit8_t, posit8_t, posit8_t );
posit8_t p8_div( posit8_t, posit8_t );
posit8_t p8_sqrt( posit8_t );
bool p8_eq( posit8_t, posit8_t );
bool p8_le( posit8_t, posit8_t );
bool p8_lt( posit8_t, posit8_t );


//Quire 8
quire8_t q8_fdp_add(quire8_t, posit8_t, posit8_t);
quire8_t q8_fdp_sub(quire8_t, posit8_t, posit8_t);
posit8_t q8_to_p8(quire8_t);
#define isNaRQ8( q ) ( q.v==0x80000000  )
#define isQ8Zero(q) ( q.v==0 )
#define q8_clr(q) ({\
	q.v=0;\
	q;\
})

#define castP8(a)({\
		union ui8_p8 uA;\
		uA.ui = a;\
		uA.p;\
})


#define castUI8(a)({\
		union ui8_p8 uA;\
		uA.p = a;\
		uA.ui;\
})

//Helper
double convertP8ToDouble(posit8_t);
posit8 convertP8ToDec(posit8_t);
posit8_t convertDoubleToP8(double);
posit8_t convertDecToP8(posit8);

/*----------------------------------------------------------------------------
| 16-bit (half-precision) posit operations.
*----------------------------------------------------------------------------*/
#define isNaRP16UI( a ) ( (a ^ 0x8000) == 0 )

uint_fast32_t p16_to_ui32( posit16_t );
uint_fast64_t p16_to_ui64( posit16_t );
int_fast32_t p16_to_i32( posit16_t);
int_fast64_t p16_to_i64( posit16_t );
posit8_t p16_to_p8( posit16_t );
posit32_t p16_to_p32( posit16_t );
//posit64_t p16_to_p64( posit16_t );

posit16_t p16_roundToInt( posit16_t);
posit16_t p16_add( posit16_t, posit16_t );
posit16_t p16_sub( posit16_t, posit16_t );
posit16_t p16_mul( posit16_t, posit16_t );
posit16_t p16_mulAdd( posit16_t, posit16_t, posit16_t );
posit16_t p16_div( posit16_t, posit16_t );
posit16_t p16_rem( posit16_t, posit16_t );
posit16_t p16_sqrt( posit16_t );
bool p16_eq( posit16_t, posit16_t );
bool p16_le( posit16_t, posit16_t );
bool p16_lt( posit16_t, posit16_t );


#ifdef SOFTPOSIT_QUAD
	__float128 convertP16ToQuadDec(posit16_t);
	posit16_t convertQuadToP16(__float128);
#endif

//Quire 16
quire16_t q16_fdp_add(quire16_t, posit16_t, posit16_t);
quire16_t q16_fdp_sub(quire16_t, posit16_t, posit16_t);
posit16_t convertQ16ToP16(quire16_t);
posit16_t q16_to_p16(quire16_t);
#define isNaRQ16( q ) ( q.v[0]==0x8000000000000000ULL && q.v[1]==0 )
#define isQ16Zero(q) (q.v[0]==0 && q.v[1]==0)
quire16_t q16_TwosComplement(quire16_t);

void printBinary(uint64_t*, int);
void printHex(uint64_t*);

#define q16_clr(q) ({\
	q.v[0]=0;\
	q.v[1]=0;\
	q;\
})

#define castP16(a)({\
		union ui16_p16 uA;\
		uA.ui = a;\
		uA.p;\
})

#define castUI16(a)({\
		union ui16_p16 uA;\
		uA.p = a;\
		uA.ui;\
})

//Helper

double convertP16ToDouble(posit16_t);
posit16 convertP16ToDec(posit16_t);
posit16_t convertDecToP16(posit16);
posit16_t convertFloatToP16(float);
posit16_t convertDoubleToP16(double);

/*----------------------------------------------------------------------------
| 32-bit (single-precision) posit operations.
*----------------------------------------------------------------------------*/
/*uint_fast32_t p32_to_ui32( posit32_t, uint_fast16_t, bool );
uint_fast64_t p32_to_ui64( posit32_t, uint_fast16_t, bool );
int_fast32_t p32_to_i32( posit32_t );
int_fast64_t p32_to_i64( posit32_t, uint_fast16_t, bool );

posit8_t p32_to_p8( posit32_t );
posit16_t p32_to_p16( posit32_t );
//posit64_t p32_to_p64( posit32_t );


posit32_t p32_roundToInt( posit32_t );
posit32_t p32_add( posit32_t, posit32_t );
posit32_t p32_sub( posit32_t, posit32_t );
posit32_t p32_mul( posit32_t, posit32_t );
posit32_t p32_mulAdd( posit32_t, posit32_t, posit32_t );
posit32_t p32_div( posit32_t, posit32_t );
posit32_t p32_rem( posit32_t, posit32_t );
posit32_t p32_sqrt( posit32_t );
bool p32_eq( posit32_t, posit32_t );
bool p32_le( posit32_t, posit32_t );
bool p32_lt( posit32_t, posit32_t );*/


double convertP32ToDouble(posit32_t);
posit32 convertP32ToDec(posit32_t);
posit32_t convertDecToP32(posit32);
posit32_t convertFloatToP32(float);
posit32_t convertDoubleToP32(double);

#ifdef SOFTPOSIT_QUAD
	posit32_t convertQuadToP32(__float128);
#endif

/*----------------------------------------------------------------------------
| 64-bit (double-precision) floating-point operations.
*----------------------------------------------------------------------------*/
/*uint_fast32_t p64_to_ui32( posit64_t, uint_fast16_t, bool );
uint_fast64_t p64_to_ui64( posit64_t, uint_fast16_t, bool );
int_fast32_t p64_to_i32( posit64_t, uint_fast16_t, bool );
int_fast64_t p64_to_i64( posit64_t, uint_fast16_t, bool );

posit8_t p64_to_p8( posit64_t );
posit16_t p64_to_p16( posit64_t );
posit32_t p64_to_p32( posit64_t );

posit64_t p64_roundToInt( posit64_t, uint_fast16_t, bool );
posit64_t p64_add( posit64_t, posit64_t );
posit64_t p64_sub( posit64_t, posit64_t );
posit64_t p64_mul( posit64_t, posit64_t );
posit64_t p64_mulAdd( posit64_t, posit64_t, posit64_t );
posit64_t p64_div( posit64_t, posit64_t );
posit64_t p64_rem( posit64_t, posit64_t );
posit64_t p64_sqrt( posit64_t );
bool p64_eq( posit64_t, posit64_t );
bool p64_le( posit64_t, posit64_t );*/

#endif

