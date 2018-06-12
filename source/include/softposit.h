
/*============================================================================

This C source file is part of the SoftPosit Posit Arithmetic Package
by S. H. Leong (Cerlane).

Copyright 2017, 2018 A*STAR.  All rights reserved.

This C source file was based on SoftFloat IEEE Floating-Point Arithmetic
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

#include "softposit_types.h"

//#include <stdio.h>

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
/*uint_fast32_t p8_to_ui32( posit8_t, uint_fast16_t, bool );
uint_fast64_t p8_to_ui64( posit8_t, uint_fast16_t, bool );
int_fast32_t p8_to_i32( posit8_t, uint_fast16_t, bool );
int_fast64_t p8_to_i64( posit8_t, uint_fast16_t, bool );

posit16_t p8_to_p16( posit8_t );
posit32_t p8_to_p32( posit8_t );
//posit64_t p8_to_p64( posit8_t );


posit8_t p8_roundToInt( posit8_t );
posit8_t p8_add( posit8_t, posit8_t );
posit8_t p8_sub( posit8_t, posit8_t );
posit8_t p8_mul( posit8_t, posit8_t );
posit8_t p8_mulAdd( posit8_t, posit8_t, posit8_t );
posit8_t p8_div( posit8_t, posit8_t );
posit8_t p8_rem( posit8_t, posit8_t );
posit8_t p8_sqrt( posit8_t );
bool p8_eq( posit8_t, posit8_t );
bool p8_le( posit8_t, posit8_t );
bool p8_lt( posit8_t, posit8_t );*/


/*----------------------------------------------------------------------------
| 16-bit (half-precision) posit operations.
*----------------------------------------------------------------------------*/
uint_fast32_t p16_to_ui32( posit16_t );
uint_fast64_t p16_to_ui64( posit16_t );
int_fast32_t p16_to_i32( posit16_t);
int_fast64_t p16_to_i64( posit16_t );

posit8_t p16_to_p8( posit16_t );
posit32_t p16_to_p32( posit16_t );
posit64_t p16_to_p64( posit16_t );

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

