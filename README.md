This version supports a 16-bit with one exponential bit (posit16_t). 

This code is tested on 

 GNU gcc (SUSE Linux) 4.8.5
 Apple LLVM version 9.1.0 (clang-902.0.39.2)
 
 Add, minus, multiply and divide are exhaustively tested. 
 
 Note: 
 [13 June 2018] Using a HPC resource to exhaustively test p16_mulAdd, reveals a bug that we are now working to fix.

------------------------------------------
An example on how to use the code to add:
------------------------------------------
union ui16_p16 uA, uB, uZ;

uA.ui = 0x42;

uB.ui = 0x23;

uZ.p = p16_add(uA.p, uB.p);

//To check answer

double dZ = convertP16ToDec_f(uZ.p);

//To print result in binary

printBinary(&uZ.ui, 16);

------------------------------------------
Build - softposit.a
------------------------------------------

cd SoftPosit/build/Linux-x86_64-GCC

make -j6 all

Please link to the archive to use.

------------------------------------------
Features
------------------------------------------

Main Posit Functionalities:

------------------------------------------
Add : posit16_t p16_add(posit16_t, posit_16)

Subtract : posit16_t p16_sub(posit16_t, posit_16)

Divide : posit16_t p16_div(posit16_t, posit_16)

Multiply : posit16_t p16_mul(posit16_t, posit_16)

Fused Multiply Add : posit16_t p16_mulAdd(posit16_t, posit_16, posit_16)
p16_mulAdd(a, b, c) <=> a*b + c


Main Quire Functionalities
------------------------------------------

Fused dot product-add  : quire16_t q16_fdp_add(quire16_t, posit_16, posit_16)

Fused dot product-subtract  : quire16_t q16_fdp_sub(quire16_t, posit_16, posit_16)

Set quire variable to zero : quire16_t q16_clr(quire16_t)

Convert quire to posit : posit_16 convertQ16ToP16(quire16_t)


Additional Posit Functionalites
------------------------------------------

Square root : posit16_t p16_sqrt(posit16_t)

Round to nearest integer : posit16_t p16_roundToInt(posit16_t)

Check equal : bool p16_eq( posit16_t, posit16_t )

Check less than equal : bool p16_le( posit16_t, posit16_t )

Check less than : bool p16_lt( posit16_t, posit16_t )

Convert p16 to integer (32 bits) : int_fast32_t p16_to_i32( posit16_t )

Convert p16 to long integer (64 bits) : int_fast64_t p16_to_i64( posit16_t)

Convert unsigned integer (32 bits) : posit16_t ui32_to_p16( uint32_t a )

Convert unsigned long int (64 bits) : posit16_t ui64_to_p16( uint64_t a )

Convert integer (32 bits) : posit16_t i32_to_p16( int32_t a )

Convert long integer (64 bits) : posit16_t i64_to_p16( int64_t a )

Convert p16 to unsigned integer (32 bits) : uint_fast32_t p16_to_ui32( posit16_t )

Convert p16 to unsigned long integer (64 bits) : uint_fast64_t p16_to_ui64( posit16_t)

Convert p16 to p32 (posit<32, 2>) : posit32_t p16_to_p32( posit16_t )

Convert p16 to double (64 bits) : double convertP16ToDec_f(posit16_t)

Convert double (64 bits) to posit  : posit16_t convertdoubleToP16(double)
