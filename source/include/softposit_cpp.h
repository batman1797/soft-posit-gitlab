/*
 * softposit_cpp.h
 *
 *  Created on: Jul 2, 2018
 *      Author: cerlane
 */

#ifndef INCLUDE_SOFTPOSIT_CPP_H_
#define INCLUDE_SOFTPOSIT_CPP_H_


#include "softposit.h"
#include "math.h"

#ifdef __cplusplus
struct posit8{
	uint8_t value;
	posit8(double x=0) : value(castUI8(convertDoubleToP8(x))) {
	}

	//Equal
	posit8& operator=(const double a) {
		value = castUI8(convertDoubleToP8(a));
		return *this;
	}
	posit8& operator=(const int a) {
		value = castUI8(i32_to_p8(a));
		return *this;
	}

	//Add
	posit8 operator+(const posit8 &a) const{
		posit8 ans;
		ans.value = castUI8(p8_add(castP8(value), castP8(a.value)));
		return ans;
	}

	//Add equal
	posit8& operator+=(const posit8 &a) {
		value = castUI8(p8_add(castP8(value), castP8(a.value)));
		return *this;
	}

	//Subtract
	posit8 operator-(const posit8 &a) const{
		posit8 ans;
		ans.value = castUI8(p8_sub(castP8(value), castP8(a.value)));
		return ans;
	}

	//Subtract equal
	posit8& operator-=(const posit8 &a) {
		value = castUI8(p8_sub(castP8(value), castP8(a.value)));
		return *this;
	}

	//Multiply
	posit8 operator*(const posit8 &a) const{
		posit8 ans;
		ans.value = castUI8(p8_mul(castP8(value), castP8(a.value)));
		return ans;
	}

	//Multiply equal
	posit8& operator*=(const posit8 &a) {
		value = castUI8(p8_mul(castP8(value), castP8(a.value)));
		return *this;
	}


	//Divide
	posit8 operator/(const posit8 &a) const{
		posit8 ans;
		ans.value = castUI8(p8_div(castP8(value), castP8(a.value)));
		return ans;
	}

	//Divide equal
	posit8& operator/=(const posit8 &a) {
		value = castUI8(p8_div(castP8(value), castP8(a.value)));
		return *this;
	}

	//less than
	bool operator<(const posit8 &a) const{
		return p8_lt(castP8(value), castP8(a.value));
	}

	//less than equal
	bool operator<=(const posit8 &a) const{
		return p8_le(castP8(value), castP8(a.value));
	}

	//equal
	bool operator==(const posit8 &a) const{
		return p8_eq(castP8(value), castP8(a.value));
	}


	//Not equalCPP
	bool operator!=(const posit8 &a) const{
		return !p8_eq(castP8(value), castP8(a.value));
	}

	//greater than
	bool operator>(const posit8 &a) const{
		return p8_lt(castP8(a.value), castP8(value));
	}

	//greater than equal
	bool operator>=(const posit8 &a) const{
		return p8_le(castP8(a.value), castP8(value));
	}

	//plus plus
	posit8& operator++() {
		value = castUI8(p8_add(castP8(value), castP8(0x40)));
		return *this;
	}

	//minus minus
	posit8& operator--() {
		value = castUI8(p8_sub(castP8(value), castP8(0x40)));
		return *this;
	}

	//Binary operators

	posit8& operator>>(const int &x) {
		value = value>>x;
		return *this;
	}

	posit8& operator>>=(const int &x) {
		value = value>>x;
		return *this;
	}

	posit8& operator<<(const int &x) {
		value = (value<<x)&0xFFFF;
		return *this;
	}

	posit8& operator<<=(const int &x) {
		value = (value<<x)&0xFF;
		return *this;
	}


	//Negate
	posit8 operator-() const{
		posit8 ans;
		ans.value = -value;
		return ans;
	}

	//NOT
	posit8& operator~() {
		value = ~value;
		return *this;
	}

	//AND
	posit8 operator&(const posit8 &a) const{
		posit8 ans;
		ans.value = (value & a.value);
		return *this;
	}

	//AND equal
	posit8& operator&=(const posit8 &a) {
		value = (value & a.value);
		return *this;
	}

	//OR
	posit8 operator|(const posit8 &a) const{
		posit8 ans;
		ans.value = (value | a.value);
		return ans;
	}


	//OR equal
	posit8& operator|=(const posit8 &a) {
		value = (value | a.value);
		return *this;
	}

	//XOR
	posit8 operator^(const posit8 &a) const{
		posit8 ans;
		ans.value = (value ^ a.value);
		return ans;
	}

	//XOR equal
	posit8& operator^=(const posit8 &a) {
		value = (value ^ a.value);
		return *this;
	}

	//Logical Operator
	//!
	bool operator!()const{
		return !value;
	}

	//&&
	bool operator&&(const posit8 &a) const{
		return (value && a.value);
	}

	//||
	bool operator||(const posit8 &a) const{
		return (value || a.value);
	}

	bool isNaR(){
		return isNaRP8UI(value);
	}

	double toDouble()const{
		return convertP8ToDouble(castP8(value));
	}

	/*int toInteger()const{
		return p8_to_i32(p8_floor(castP8(value)));
	}*/

	posit8& fma(posit8 a, posit8 b){ // += (a*b)
		value = castUI8(p8_mulAdd(castP8(a.value), castP8(b.value), castP8(value)));
		return *this;
	}

	posit8& toNaR(){
		value = 0x80;
		return *this;
	}


};


struct posit16{
	uint16_t value;
	posit16(double x=0) : value(castUI16(convertDoubleToP16(x))) {
	}

	//Equal
	posit16& operator=(const double a) {
		value = castUI16(convertDoubleToP16(a));
		return *this;
	}
	posit16& operator=(const int a) {
		value = castUI16(i32_to_p16(a));
		return *this;
	}

	//Add
	posit16 operator+(const posit16 &a) const{
		posit16 ans;
		ans.value = castUI16(p16_add(castP16(value), castP16(a.value)));
		return ans;
	}

	//Add equal
	posit16& operator+=(const posit16 &a) {
		value = castUI16(p16_add(castP16(value), castP16(a.value)));
		return *this;
	}

	//Subtract
	posit16 operator-(const posit16 &a) const{
		posit16 ans;
		ans.value = castUI16(p16_sub(castP16(value), castP16(a.value)));
		return ans;
	}

	//Subtract equal
	posit16& operator-=(const posit16 &a) {
		value = castUI16(p16_sub(castP16(value), castP16(a.value)));
		return *this;
	}

	//Multiply
	posit16 operator*(const posit16 &a) const{
		posit16 ans;
		ans.value = castUI16(p16_mul(castP16(value), castP16(a.value)));
		return ans;
	}

	//Multiply equal
	posit16& operator*=(const posit16 &a) {
		value = castUI16(p16_mul(castP16(value), castP16(a.value)));
		return *this;
	}


	//Divide
	posit16 operator/(const posit16 &a) const{
		posit16 ans;
		ans.value = castUI16(p16_div(castP16(value), castP16(a.value)));
		return ans;
	}

	//Divide equal
	posit16& operator/=(const posit16 &a) {
		value = castUI16(p16_div(castP16(value), castP16(a.value)));
		return *this;
	}

	//less than
	bool operator<(const posit16 &a) const{
		return p16_lt(castP16(value), castP16(a.value));
	}

	//less than equal
	bool operator<=(const posit16 &a) const{
		return p16_le(castP16(value), castP16(a.value));
	}

	//equal
	bool operator==(const posit16 &a) const{
		return p16_eq(castP16(value), castP16(a.value));
	}


	//Not equal
	bool operator!=(const posit16 &a) const{
		return !p16_eq(castP16(value), castP16(a.value));
	}

	//greater than
	bool operator>(const posit16 &a) const{
		return p16_lt(castP16(a.value), castP16(value));
	}

	//greater than equal
	bool operator>=(const posit16 &a) const{
		return p16_le(castP16(a.value), castP16(value));
	}

	//plus plus
	posit16& operator++() {
		value = castUI16(p16_add(castP16(value), castP16(0x4000)));
		return *this;
	}

	//minus minus
	posit16& operator--() {
		value = castUI16(p16_sub(castP16(value), castP16(0x4000)));
		return *this;
	}

	//Binary operators

	posit16& operator>>(const int &x) {
		value = value>>x;
		return *this;
	}

	posit16& operator>>=(const int &x) {
		value = value>>x;
		return *this;
	}

	posit16& operator<<(const int &x) {
		value = (value<<x)&0xFFFF;
		return *this;
	}

	posit16& operator<<=(const int &x) {
		value = (value<<x)&0xFFFF;
		return *this;
	}

	//Negate
	posit16 operator-() const{
		posit16 ans;
		ans.value = -value;
		return ans;
	}

	//Binary NOT
	posit16& operator~() {
		value = ~value;
		return *this;
	}

	//AND
	posit16 operator&(const posit16 &a) const{
		posit16 ans;
		ans.value = (value & a.value);
		return ans;
	}

	//AND equal
	posit16& operator&=(const posit16 &a) {
		value = (value & a.value);
		return *this;
	}

	//OR
	posit16 operator|(const posit16 &a) const{
		posit16 ans;
		ans.value = (value | a.value);
		return ans;
	}


	//OR equal
	posit16& operator|=(const posit16 &a) {
		value = (value | a.value);
		return *this;
	}

	//XOR
	posit16 operator^(const posit16 &a) const{
		posit16 ans;
		ans.value = (value ^ a.value);
		return ans;
	}

	//XOR equal
	posit16& operator^=(const posit16 &a) {
		value = (value ^ a.value);
		return *this;
	}

	//Logical operator
	//!
	bool operator!()const{
		return !value;
	}

	//&&
	bool operator&&(const posit16 &a) const{
		return (value && a.value);
	}

	//||
	bool operator||(const posit16 &a) const{
		return (value || a.value);
	}

	bool isNaR(){
		return isNaRP16UI(value);
	}

	double toDouble()const{
		return convertP16ToDouble(castP16(value));
	}

	/*int toInteger()const{
		return p16_to_i32(p16_floor(castP16(value)));
	}*/

	posit16& fma(posit16 a, posit16 b){ // += (a*b)
		value = castUI16(p16_mulAdd(castP16(a.value), castP16(b.value), castP16(value)));
		return *this;
	}

	posit16& toNaR(){
		value = 0x8000;
		return *this;
	}


};

struct posit32{
	uint32_t value;
};


struct quire8{
	uint32_t value;

	quire8 (uint32_t value=0) : value(value){
	}

	quire8& clr(){
		value = 0;
		return *this;
	}

	bool isNaR(){
		return isNaRQ8(castQ8(value));
	}

	quire8& qma(posit8 a, posit8 b){ // q += a*b
		 quire8_t q = q8_fdp_add(castQ8(value), castP8(a.value), castP8(b.value));
		 value = q.v;
		 return *this;
	}
	quire8& qms(posit16 a, posit16 b){ // q -= a*b
		 quire8_t q = q8_fdp_sub(castQ8(value), castP8(a.value), castP8(b.value));
		 value = q.v;
		 return *this;
	}
	posit8 p8(){
		posit8 a;
		a.value = castUI8(q8_to_p8(castQ8(value)));
		return a;
	}

};
struct quire16{
	uint64_t lvalue;
	uint64_t rvalue;

	quire16 (uint64_t lvalue=0, uint64_t rvalue=0) : lvalue(lvalue), rvalue(rvalue){
	}

	quire16& clr(){
		lvalue = 0;
		rvalue = 0;
		return *this;
	}

	bool isNaR(){
		return isNaRQ16(castQ16(lvalue, rvalue));
	}

	quire16& qma(posit16 a, posit16 b){ // q += a*b
		 quire16_t q = q16_fdp_add(castQ16(lvalue, rvalue), castP16(a.value), castP16(b.value));
		 lvalue = q.v[0];
		 rvalue = q.v[1];
		 return *this;
	}
	quire16& qms(posit16 a, posit16 b){ // q -= a*b
		 quire16_t q = q16_fdp_sub(castQ16(lvalue, rvalue), castP16(a.value), castP16(b.value));
		 lvalue = q.v[0];
		 rvalue = q.v[1];
		 return *this;
	}
	posit16 p16(){
		posit16 a;
		a.value = castUI16(q16_to_p16(castQ16(lvalue, rvalue)));
		return a;
	}

};



inline posit8 operator+(int a, posit8 b){
	b.value = castUI8(p8_add(i32_to_p8(a), castP8(b.value)));
	return b;
}
inline posit16 operator+(int a, posit16 b){
	b.value = castUI16(p16_add(i32_to_p16(a), castP16(b.value)));
	return b;
}
inline posit8 operator+(double a, posit8 b){
	b.value = castUI8(p8_add(convertDoubleToP8(a), castP8(b.value)));
	return b;
}
inline posit16 operator+(double a, posit16 b){
	b.value = castUI16(p16_add(convertDoubleToP16(a), castP16(b.value)));
	return b;
}



inline posit8 operator-(int a, posit8 b){
	b.value = castUI8(p8_sub(i32_to_p8(a), castP8(b.value)));
	return b;
}
inline posit16 operator-(int a, posit16 b){
	b.value = castUI16(p16_sub(i32_to_p16(a), castP16(b.value)));
	return b;
}
inline posit8 operator-(double a, posit8 b){
	b.value = castUI8(p8_sub(convertDoubleToP8(a), castP8(b.value)));
	return b;
}
inline posit16 operator-(double a, posit16 b){
	b.value = castUI16(p16_sub(convertDoubleToP16(a), castP16(b.value)));
	return b;
}



inline posit8 operator/(int a, posit8 b){
	b.value = castUI8(p8_div(i32_to_p8(a), castP8(b.value)));
	return b;
}
inline posit16 operator/(int a, posit16 b){
	b.value = castUI16(p16_div(i32_to_p16(a), castP16(b.value)));
	return b;
}
inline posit8 operator/(double a, posit8 b){
	b.value = castUI8(p8_div(convertDoubleToP8(a), castP8(b.value)));
	return b;
}
inline posit16 operator/(double a, posit16 b){
	b.value = castUI16(p16_div(convertDoubleToP16(a), castP16(b.value)));
	return b;
}



inline posit8 operator*(int a, posit8 b){
	b.value = castUI8(p8_mul(i32_to_p8(a), castP8(b.value)));
	return b;
}
inline posit16 operator*(int a, posit16 b){
	posit16 ans;
	ans.value = castUI16(p16_mul(i32_to_p16(a), castP16(b.value)));
	return ans;
}
inline posit8 operator*(double a, posit8 b){
	b.value = castUI8(p8_mul(convertDoubleToP8(a), castP8(b.value)));
	return b;
}
inline posit16 operator*(double a, posit16 b){
	posit16 ans;
	ans.value = castUI16(p16_mul(convertDoubleToP16(a), castP16(b.value)));
	return ans;
}




//fused-multiply-add
inline posit8 fma(posit8 a, posit8 b, posit8 c){ // (a*b) + c
	a.value = castUI8(p8_mulAdd(castP8(a.value), castP8(b.value), castP8(c.value)));
	return a;
}
inline posit16 fma(posit16 a, posit16 b, posit16 c){ // (a*b) + c
	a.value = castUI16(p16_mulAdd(castP16(a.value), castP16(b.value), castP16(c.value)));
	return a;
}

//Round to nearest integer
inline posit8 rint(posit8 a){
	a.value = castUI8( p8_roundToInt(castP8(a.value)) );
	return a;
}
inline posit16 rint(posit16 a){
	a.value = castUI16( p16_roundToInt(castP16(a.value)) );
	return a;
}

//Square root
inline posit8 sqrt(posit8 a){
	a.value = castUI8( p8_sqrt(castP8(a.value)) );
	return a;
}
inline posit16 sqrt(posit16 a){
	a.value = castUI16( p16_sqrt(castP16(a.value)) );
	return a;
}



// Convert to integer

inline uint32_t uint32 (posit8 a){
	return p8_to_ui32(castP8(a.value));
}

inline uint32_t uint32 (posit16 a){
	return p16_to_ui32(castP16(a.value));
}


inline int32_t int32(posit8 a){
	return p8_to_i32(castP8(a.value));
}

inline int32_t int32(posit16 a){
	return p16_to_i32(castP16(a.value));
}


inline uint64_t uint64(posit8 a){
	return p8_to_ui64(castP8(a.value));
}
inline uint64_t uint64(posit16 a){
	return p16_to_ui64(castP16(a.value));
}


inline int64_t int64(posit8 a){
	return p8_to_i64(castP8(a.value));
}
inline int64_t int64(posit16 a){
	return p16_to_i64(castP16(a.value));
}


//Convert To Posit
inline posit8 p8(posit16 a){
	posit8 b;
	b.value = castUI8(p16_to_p8(castP16(a.value)));
	return b;
}
/*inline posit8 p8(posit32 a){
	posit8 b;
	b.value = castUI8(p32_to_p8(castP32(a.value)));
	return b;
}*/


inline posit16 p16(posit8 a){
	posit16 b;
	b.value = castUI16(p8_to_p16(castP8(a.value)));
	return b;
}
/*inline posit16 p16(posit32 a){
	posit32 b;
	b.value = castUI16(p32_to_p16(castP32(a.value)));
	return b;
}*/


inline posit32 p32(posit8 a){
	posit32 b;
	b.value = castUI32(p8_to_p32(castP8(a.value)));
	return b;
}
inline posit32 p32(posit16 a){
	posit32 b;
	b.value = castUI32(p16_to_p32(castP16(a.value)));
	return b;
}


inline posit8 p8(uint32_t a){
	posit8 b;
	b.value = castUI8(ui32_to_p8(a));
	return b;
}
inline posit16 p16(uint32_t a){
	posit16 b;
	b.value = castUI16(ui32_to_p16(a));
	return b;
}


inline posit8 p8(int32_t a){
	posit8 b;
	b.value = castUI8(i32_to_p8(a));
	return b;
}
inline posit16 p16(int32_t a){
	posit16 b;
	b.value = castUI16(i32_to_p16(a));
	return b;
}


inline posit8 p8(uint64_t a){
	posit8 b;
	b.value = castUI8(ui64_to_p8(a));
	return b;
}
inline posit16 p16(uint64_t a){
	posit16 b;
	b.value = castUI16(ui64_to_p16(a));
	return b;
}


inline posit8 p8(int64_t a){
	posit8 b;
	b.value = castUI8(i64_to_p8(a));
	return b;
}
inline posit16 p16(int64_t a){
	posit16 b;
	b.value = castUI16(i64_to_p16(a));
	return b;
}

inline posit8 p8(double a){
	posit8 b;
	b.value = castUI8(convertDoubleToP8(a));
	return b;
}
inline posit16 p16(double a){
	posit16 b;
	b.value = castUI16(convertDoubleToP16(a));
	return b;
}



inline posit8 p8(quire8 a){
	posit8 b;
	b.value = castUI8(q8_to_p8(castQ8(a.value)));
	return b;
}
inline posit16 p16(quire16 a){
	posit16 b;
	b.value = castUI16(q16_to_p16(castQ16(a.lvalue, a.rvalue)));
	return b;
}




#endif //CPLUSPLUS

#endif /* INCLUDE_SOFTPOSIT_CPP_H_ */
