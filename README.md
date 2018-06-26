This version supports:

    16-bit with one exponential bit (posit16_t). 
    
    8-bit with zero exponential bit (posit8_t). 
    

This code is tested on 

 GNU gcc (SUSE Linux) 4.8.5
 Apple LLVM version 9.1.0 (clang-902.0.39.2)
 
 Add, minus, multiply and divide are exhaustively tested. 
 

-----------------------------------------------------
A 8-bit example on how to use the code to add:
-----------------------------------------------------

```
#include "softposit.h"

int main (int argc, char *argv[]){

    posit8_t pA, pB, pZ;
    pA = castP8(0xF2);
    pB = castP8(0x23);

    pZ = p8_add(pA, pB);

    //To check answer by converting it to double
    double dZ = convertP8ToDouble(pZ);

    //To print result in binary
    uint8_t uiZ = castUI8(pZ);
    printBinary(&uiZ, 8);
    
    return 0;

}
```

-----------------------------------------------------
A 16-bit example on how to use the code to multiply:
-----------------------------------------------------

```
#include "softposit.h"

int main (int argc, char *argv[]){

    posit16_t pA, pB, pZ;
    pA = castP16(0x0FF2);
    pB = castP16(0x2123);

    pZ = p16_mul(pA, pB);

   //To check answer by converting it to double
    double dZ = convertP16ToDouble(pZ);

    //To print result in binary
    uint16_t uiZ = castUI16(pZ);
    printBinary((uint64_t*)&uiZ, 16);

    return 0;
}
```

------------------------------------------
Build - softposit.a
------------------------------------------

```
cd SoftPosit/build/Linux-x86_64-GCC
make -j6 all

```

------------------------------------------
Link - softposit.a
------------------------------------------

If your source code is for example "main.c" and you want to create an executable "main".
Assume that SoftPosit is installed and installed in the same directory (installing in the same directory is NOT recommended).

```
gcc -lm -o main \
    main.c SoftPosit/build/Linux-x86_64-GCC/softposit.a  -I../../SoftPosit/source/include -O2 

```

------------------------------------------
Features
------------------------------------------

Main Posit Functionalities:

------------------------------------------

Add : 

     posit16_t p16_add(posit16_t, posit16_t)
     
     posit8_t p8_add(posit8_t, posit8_t)

Subtract : 

    posit16_t p16_sub(posit16_t, posit16_t)
    
    posit8_t p8_sub(posit8_t, posit8_t)
    

Divide : 

    posit16_t p16_div(posit16_t, posit16_t)
    
    posit8_t p8_div(posit8_t, posit8_t)

Multiply : 

    posit16_t p16_mul(posit16_t, posit16_t)
    
    posit8_t p8_mul(posit8_t, posit8_t)
    

Fused Multiply Add : 
    
    posit16_t p16_mulAdd(posit16_t, posit16_t, posit16_t)
    
    posit8_t p8_mulAdd(posit8_t, posit8_t, posit8_t)
    
    
    Note: p16_mulAdd(a, b, c) <=> a*b + c


Main Quire Functionalities
------------------------------------------

Fused dot product-add  : 

    quire16_t q16_fdp_add(quire16_t, posit16_t, posit16_t)
    
    quire8_t q16_fdp_add(quire8_t, posit8_t, posit8_t)
    
    Note: q8_fdp_add (a, b, c) <=> a + b*c

Fused dot product-subtract  : 

    quire16_t q16_fdp_sub(quire16_t, posit16_t, posit16_t)
    
    quire8_t q8_fdp_sub(quire8_t, posit8_t, posit8_t)

Set quire variable to zero : 

    quire16_t q16_clr(quire16_t)
    
    quire8_t q8_clr(quire8_t)

Convert quire to posit : 

    posit16_t q16_to_p16(quire16_t)
    
    posit8_t q8_to_p8(quire8_t)


Functionalites in Posit Standard
------------------------------------------

Square root : 

    posit16_t p16_sqrt(posit16_t)
    
    posit8_t p8_sqrt(posit8_t)

Round to nearest integer : 

    posit16_t p16_roundToInt(posit16_t)
    
    posit8_t p8_roundToInt(posit8_t)

Check equal : 

    bool p16_eq( posit16_t, posit16_t )
    
    bool p8_eq( posit8_t, posit8_t )

Check less than equal : 

    bool p16_le( posit16_t, posit16_t )
    
    bool p8_le( posit8_t, posit8_t )

Check less than : 

    bool p16_lt( posit16_t, posit16_t )
    
    bool p8_lt( posit8_t, posit8_t )

Convert posit to integer (32 bits) : 

    int_fast32_t p16_to_i32( posit16_t )
    
    int_fast32_t p8_to_i32( posit8_t )

Convert posit to long long integer (64 bits) : 

    int_fast64_t p16_to_i64( posit16_t)
    
    int_fast64_t p8_to_i64( posit8_t)

Convert unsigned integer (32 bits) to posit: 

    posit16_t ui32_to_p16( uint32_t a )
    
    posit8_t ui32_to_p8( uint32_t a )

Convert unsigned long long int (64 bits) to posit: 

    posit16_t ui64_to_p16( uint64_t a )
    
    posit8_t ui64_to_p8( uint64_t a )

Convert integer (32 bits) to posit: 

    posit16_t i32_to_p16( int32_t a )
    
    posit8_t i32_to_p8( uint32_t a )

Convert long integer (64 bits) to posit: 

    posit16_t i64_to_p16( int64_t a )
    
    posit8_t i64_to_p8( uint64_t a )

Convert posit to unsigned integer (32 bits) : 

    uint_fast32_t p16_to_ui32( posit16_t )
    
    uint_fast32_t p8_to_ui32( posit8_t )

Convert posit to unsigned long long integer (64 bits) : 

    uint_fast64_t p16_to_ui64( posit16_t)
    
    uint_fast64_t p8_to_ui64( posit8_t)
    
Convert posit to integer (32 bits) : 

    uint_fast32_t p16_to_i32( posit16_t )
    
    uint_fast32_t p8_to_i32( posit8_t )

Convert posit to long long integer (64 bits) : 

    uint_fast64_t p16_to_i64( posit16_t)
    
    uint_fast64_t p8_to_i64( posit8_t)

Convert posit to posit of another size : 

    posit8_t p16_to_p8( posit16_t )
    
    posit32_t p16_to_p32( posit16_t )
    
    posit16_t p8_to_p16( posit8_t )
    
    posit32_t p8_to_p32( posit8_t )



Helper Functionalites (NOT in Posit Standard)
---------------------------------------------

Convert posit to double (64 bits) : 

    double convertP16ToDouble(posit16_t)
    
    double convertP8ToDouble(posit8_t)

Convert double (64 bits) to posit  : 

    posit16_t convertDoubleToP16(double)
    
    posit8_t convertDoubleToP8(double)
    
Cast binary expressed in unsigned integer to posit :

    posit16_t castP16(uint16_t)
    
    posit8_t castP8(uint8_t)
    
Cast posit into binary expressed in unsigned integer

    uint16_t castUI16(posit16_t)
    
    uint8_t castUI8(posit8_t)
    
