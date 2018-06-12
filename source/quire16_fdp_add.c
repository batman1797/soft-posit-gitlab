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
#include <inttypes.h>


#include "softposit.h"
#include "platform.h"
#include "internals.h"
#include "specialize.h"

//#include <stdio.h>

quire16_t q16_fdp_add( quire16_t q, posit16_t pA, posit16_t pB ){

	union ui16_p16 uA, uB;
	union ui128_q16 uZ, uZ1, uZ2;
	uint_fast16_t uiA, uiB;
	uint_fast16_t regA, fracA, regime, tmp;
	bool signA, signB, signZ2, regSA, regSB, bitNPlusOne=0, bitsMore=0, rcarry;
	int_fast8_t expA, expB;
	int_fast16_t kA=0, shiftRight=0;
	uint_fast32_t frac32Z;
	//For add
	bool rcarryb, b1, b2, rcarryZ, rcarrySignZ;

	uZ1.q = q;

	uA.p = pA;
	uiA = uA.ui;
	uB.p = pB;
	uiB = uB.ui;

	//NaR
	if (isNaRQ16(q) || isNaRP16UI(uA.ui) || isNaRP16UI(uB.ui)){
		uZ2.ui.left64=0x8000000000000000ULL;
		uZ2.ui.right64 = 0;
		return uZ2.q;
	}
	else if (uiA==0 || uiB==0)
		return q;

//printPositQuireAsBinary(&uiA, 16);
//printPositQuireAsBinary(&uiB, 16);

	//max pos (sign plus and minus)
	signA = signP16UI( uiA );
	signB = signP16UI( uiB );
	signZ2 = signA ^ signB;

	if(signA) uiA = (-uiA & 0xFFFF);
	if(signB) uiB = (-uiB & 0xFFFF);
//printPositQuireAsBinary(&uiA, 16);
//printPositQuireAsBinary(&uiB, 16);
	regSA = signregP16UI(uiA);
	regSB = signregP16UI(uiB);

	tmp = (uiA<<2) & 0xFFFF;
	if (regSA){
		while (tmp>>15){
			kA++;
			tmp= (tmp<<1) & 0xFFFF;
		}
	}
	else{
		kA=-1;
		while (!(tmp>>15)){
			kA--;
			tmp= (tmp<<1) & 0xFFFF;
		}
		tmp&=0x7FFF;
	}
	expA = tmp>>14;
	fracA = (0x4000 | tmp);
//printf("kA: %d expA: %d \n", kA, expA);
//printPositQuireAsBinary(&fracA, 16);
	tmp = (uiB<<2) & 0xFFFF;
	if (regSB){
		while (tmp>>15){
			kA++;
			tmp= (tmp<<1) & 0xFFFF;
		}
	}
	else{
		kA--;
		while (!(tmp>>15)){
			kA--;
			tmp= (tmp<<1) & 0xFFFF;
		}
		tmp&=0x7FFF;
	}
	expA += tmp>>14;
	frac32Z = (uint_fast32_t) fracA * (0x4000 | tmp);
//printf("kA: %d expA: %d \n", kA, expA);
//printPositQuireAsBinary(&tmp, 16);
//printPositQuireAsBinary(&frac32Z, 32);
	if (expA>1){
		kA++;
		expA ^=0x2;
	}
	rcarry = frac32Z>>29;//3rd bit (position 2) of frac32Z, hidden bit is 4th bit (position 3)
	if (rcarry){
		if (expA) kA ++;
		expA^=1;
		frac32Z>>=1;
	}
//printPositQuireAsBinary(&frac32Z, 32);

	//default dot is between bit 71 and 72, extreme left bit is bit 0. Last right bit is bit 127.
	//Scale = 2^es * k + e  => 2k + e
	int firstPos = 71 - (kA<<1) - expA;

//printf("firstPos: %d kA: %d expA: %d \n",firstPos, kA, expA);
	//No worries about hidden bit moving before position 4 because fraction is right aligned so
	//there are 16 spare bits
	if (firstPos>63){ //This means entire fraction is in right 64 bits
		uZ2.ui.left64 = 0;
		shiftRight = firstPos-99;//99 = 63+ 4+ 32
		if (shiftRight<0){//shiftLeft
			uZ2.ui.right64 =  ((uint64_t)frac32Z) << -shiftRight;
			//(shiftRight<-64)?(uZ2.ui.right64 = 0):(uZ2.ui.right64 =  ((uint64_t)frac32Z) << -shiftRight);
		}
		else
			uZ2.ui.right64 = (uint64_t) frac32Z >> shiftRight;
	}
	else{//frac32Z can be in both left64 and right64
		shiftRight = firstPos - 35;// -35= -3-32
		if (shiftRight<0)
			uZ2.ui.left64  = ((uint64_t)frac32Z) << -shiftRight;
		else{
			uZ2.ui.left64 = (uint64_t)frac32Z >> shiftRight;
			uZ2.ui.right64 =  (uint64_t) frac32Z <<  (64 - shiftRight);
		}

	}
//printf("shiftRight: %d\n", shiftRight);
//printPositQuireAsBinary(&uZ2.ui.left64, 64);
//printPositQuireAsBinary(&uZ2.ui.right64, 64);

//printPositQuireAsBinary(&uZ1.ui.left64, 64);
//printPositQuireAsBinary(&uZ1.ui.right64, 64);
	//if (signZ2) uZ2.q  = q16_TwosComplement(uZ2.q);
	if (signZ2){
		if (uZ2.ui.right64>0){
			uZ2.ui.right64 = - uZ2.ui.right64;
			uZ2.ui.left64 = ~uZ2.ui.left64;
		}
		else{
			uZ2.ui.left64 = -uZ2.ui.left64;
		}
	}
	/*regA = reglengthP16UI(uiA);
	regSA = signregP16UI(uiA);
	expA = expP16UI( uiA, regA );
	kA = regkP16UI(regSA, regA );
	regB = reglengthP16UI(uiB);
	regSB = signregP16UI(uiB);
	expB = expP16UI( uiB, regB );
	kB = regkP16UI(regSB, regB );


	expA += expB;
	if (expA>1){
		expA=0; //^=0x2;
		kA ++;
	}

	if (regA>=14)
		fracA=1;
	else{
		rightPadding += 13-regA;
		fracA = fracP16UI( uiA, regA ) | ( 1<<(13-regA) ); // add hidden bit
	}
	if (regB>=14)
		fracB=1;
	else{
		rightPadding += 13-regB;
		fracB = fracP16UI( uiB, regB ) | ( 1<<(13-regB) );
	}

	frac32Z = (uint_fast32_t) fracA * fracB;



	rcarry = ((frac32Z >> (rightPadding+1)) &0x1);
//printf("rcarry: %d\n", rcarry);
	if (rcarry){
		if (expA==1) kA ++;
		expA^=0x1;//=1-expA;
	}

	regA = kA + kB+ 1;
//printf("kA: %d  kB: %d regA: %d\n", kA, kB, regA);
	if(regA&0x8000){
		regA = (-regA & 0xFFFF) + 1;
		regSA = 0;
	}
	else if (regA==0){
		regA=1;
		regSA=0;
	}
	else
		regSA =1;


	//if(regA>=15) expA=0;  //TODO can be removed.. just for checking expA value

	//Make it into a quire16
	//printstringasbinary19(&frac32Z, 32);

	(regSA) ? ( kA=regA-1 ) : (kA=(int)-regA);
	//printf("regA: %d  kA: %d expA: %d\n", regA, kA, expA);

	//default dot is between bit 71 and 72, extreme left bit is bit 0. Last right bit is bit 127.
	//if first_pos is negative, the hidden one is right of dot. i.e. 71 - first_pos
	//if first_pos is positive, the hidden one is left of dot. i.e. 71 - first_pos
	// that is, if first_pos = (kA<<1) + expA + 1;
	//Scale = 2^es * k + e  => 2k + e

	int firstPos = 71 - (kA<<1) - expA;
	int noLZ = clz32(frac32Z) +32; //frac32Z is 32 bits but we need 64 bits
	int aligned_noLZ = noLZ + 64;
	int rightShift = firstPos - aligned_noLZ -1;

///	printf("kA: %d kB: %d regSA: %d regA: %d last_pos: %d frac_len: %d noLZ: %d  rightShift: %d expA=%d\n",
//			kA, kB, regSA, regA, last_pos, frac_len, noLZ,  rightShift, expA);
	//printf("kA: %d kB: %d regSA: %d regA: %d noLZ: %d  first_pos: %d, rightShift: %d expA=%d\n",
	//			kA, kB, regSA, regA, noLZ, first_pos, rightShift, expA);

	if (rightShift<0){
		//leftShift instead
		int leftShift = -rightShift - 1;
//printf("left shift: %d\n", leftShift);
		if (leftShift>noLZ){
			//bits are shifted to left64
			leftShift -= (noLZ);
//printf("left shift: %d\n", leftShift);
			leftShift = noLZ+leftShift-64;
//printf("left shift: %d\n", leftShift);
			if (leftShift < 0){
				//rightShift (that means some bits will stay in right64)
				rightShift = -leftShift;// + 1;
				uZ2.ui.left64 = (uint64_t) frac32Z >> rightShift;
				uZ2.ui.right64 =  (uint64_t) frac32Z <<  (64 - rightShift);
				//printf("1 rightShift: %d\n", rightShift);
			}
			else{
				//all bits in left64
				uZ2.ui.left64 = (uint64_t) frac32Z << leftShift;
				uZ2.ui.right64 = (uint64_t) 0;
				//printf("2 leftShift: %d\n", leftShift);
			}

		}
		else{
			//bits stayed in right64
			uZ2.ui.left64 = (uint64_t) 0;
			uZ2.ui.right64 = (uint64_t) frac32Z << leftShift;
			//printf("3 leftShift: %d\n", leftShift);

		}
	}
	else{
		uZ2.ui.right64 = (uint64_t) frac32Z >> rightShift;
		uZ2.ui.left64 = (uint64_t)0;
		//printf("4 rightShift: %d\n", rightShift);
	}




	//printf("signZ2: %d expA: %d\n", signZ2, expA);

	if (signZ2) uZ2.q  = q16_TwosComplement(uZ2.q);*/
		/*if (uZ2.ui.right64>0){
			uZ2.ui.right64 = - uZ2.ui.right64;
			uZ2.ui.left64 = ~uZ2.ui.left64;
		}
		else{
			uZ2.ui.left64 = -uZ2.ui.left64;
		}*/

	//}

	//Addition
	b1 = uZ1.ui.right64&0x1;
	b2 = uZ2.ui.right64&0x1;
	rcarryb = b1 & b2;
	uZ.ui.right64 = (uZ1.ui.right64>>1) + (uZ2.ui.right64>>1) + rcarryb;

	rcarryZ = uZ.ui.right64>>63;
	/*printf("b1: %d b2: %d rcarryb: %d rcarryZ: %d (b1^b2): %d\n", b1, b2, rcarryb, rcarryZ, (b1^b2));*/
	//printPositQuireAsBinary(&uZ.ui.right64, 64);


	uZ.ui.right64 = (uZ.ui.right64<<1 | (b1^b2) );
	//printPositQuireAsBinary(&uZ.ui.right64, 64);

	b1 = uZ1.ui.left64&0x1;
	b2 = uZ2.ui.left64&0x1;
	rcarryb = b1 & b2 ;
	int_fast8_t rcarryb3 = b1 + b2 + rcarryZ;

	uZ.ui.left64 = (uZ1.ui.left64>>1) + (uZ2.ui.left64>>1) + ((rcarryb3>>1)& 0x1);
	rcarrySignZ = uZ.ui.left64>>63;


	uZ.ui.left64 = (uZ.ui.left64<<1 | (rcarryb3 & 0x1) );

	//Exception handling
	if (isNaRQ16(uZ.q) ) uZ.q = q16_clr(uZ.q);

	//if (uZ.ui.left64!=0 && uZ.ui.right64!=0)
	//	uZ.ui.left64 = uZ.ui.left64  | ( (uint64_t) rcarrySignZ<<63 | (uint64_t) rcarrySignZ<<62 );
	//uZ.ui.left64 = uZ1.ui.left64 + uZ2.ui.left64 + rcarryZ;

	//printf("mult start 2:\n");
	/*printPositQuireAsBinary(&uZ1.ui.left64, 64);
	printPositQuireAsBinary(&uZ1.ui.right64, 64);
	printPositQuireAsBinary(&uZ2.ui.left64, 64);
	printPositQuireAsBinary(&uZ2.ui.right64, 64);
	printPositQuireAsBinary(&uZ.ui.left64, 64);
	printPositQuireAsBinary(&uZ.ui.right64, 64);*/
	//printf("mult end 2:\n");

	return uZ.q;
}
