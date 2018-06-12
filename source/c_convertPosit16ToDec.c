
/*============================================================================

This C source file is part of the SoftPosit Posit Arithmetic Package
by S. H. Leong (Cerlane).

Copyright 2017, 2018 A*STAR.  All rights reserved.

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

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "softposit.h"
#include "platform.h"
#include "internals.h"
#include "specialize.h"


double convertP16ToDec_f(posit16_t a){
	posit16 b = convertP16ToDec(a);
	return b.f;//
}
posit16 convertP16ToDec(posit16_t a){

	union ui16_p16 uZ;
	posit16 p16;
	uZ.p = a;

	if (uZ.ui==0){
		p16.f = 0;
		return p16;
	}
	else if(uZ.ui==0x7FFF){ //maxpos -> 32767
		p16.f = 268435456;
		return p16;
	}
	else if (uZ.ui==0x8001){ //-maxpos -> 32769
		p16.f = -268435456;
		return p16;
	}
	else if (uZ.ui == 0x8000){ //NaR -> 32768
		p16.f = INFINITY;
		return p16;
	}

	bool regS, sign;
	uint_fast16_t reg, shift=2, frac;
	int_fast16_t k=0;
	int_fast8_t exp;
	double fraction_max;

	sign = signP16UI( uZ.ui );
	if (sign)
		uZ.ui = -uZ.ui & 0xFFFF;
	regS = signregP16UI( uZ.ui );

	uint_fast16_t tmp = (uZ.ui<<2) & 0xFFFF;
	if (regS){
		while (tmp>>15){
			k++;
			shift++;
			tmp= (tmp<<1) & 0xFFFF;
		}
		reg = k+1;
	}
	else{
		k=-1;
		while (!(tmp>>15)){
			k--;
			shift++;
			tmp= (tmp<<1) & 0xFFFF;
		}
		tmp&=0x7FFF;
		reg =-k;
	}
	exp = tmp>>14;
	frac = (tmp & 0x3FFF) >> shift;


	fraction_max = pow(2, 13-reg) ;
	p16.f = (double)( pow(4, k)* pow(2, exp) * (1+((double)frac/fraction_max)) );

	if (sign)
		p16.f = -p16.f;

	return p16;
}

