#include "Fraction.hpp"
#include <iostream>
#include <limits>

namespace ariel {


	// Constructors
	Fraction::Fraction(const int& numerator, const int& denominator):
		_numerator(numerator),
		_denominator(denominator) {	
			if(denominator == 0){
				throw std::invalid_argument("Denominator can't be 0.\n");
			}
			this->reduce();
		}

	// Copy
	Fraction::Fraction(const Fraction& other):
		_numerator(other._numerator),
		_denominator(other._denominator) {}

	// Move
	Fraction::Fraction(Fraction&& other) noexcept:
		_numerator(other._numerator),
		_denominator(other._denominator) {}

	// Convert float
	Fraction::Fraction(float num):
		_numerator((int)(num * 1000)),
		_denominator(1000){
			this->reduce();
		}

	// Convert double
	Fraction::Fraction(double num):
		_numerator((int)(num * 1000)),
		_denominator(1000){
			this->reduce();
		}

	// Destructor
	Fraction::~Fraction(){}


	
	// Assignment Operators
	Fraction& Fraction::operator =(Fraction&& other) noexcept {
		if(*this != other) {
			_numerator = std::__exchange(other._numerator, 0);
			_denominator = std::__exchange(other._denominator, 0);			
		}
		return *this;
	}
	Fraction& Fraction::operator =(const Fraction& other) {
		if(*this != other) {
			int numerator = other.getNumerator();
			int denominator = other.getDenominator();
			this->_numerator = numerator;
			this->_denominator = denominator;
		}
		return *this;
	}


	// Arithmetic Operators
	void add_overflow(const Fraction& frac1, const Fraction& frac2) {
		int res1, res2, res3, res4;
		if(__builtin_mul_overflow(frac1.getDenominator(), frac2.getDenominator(), &res1) || 
			__builtin_mul_overflow(frac1.getDenominator(), frac2.getNumerator(), &res2) || 
			__builtin_mul_overflow(frac2.getDenominator(), frac1.getNumerator(), &res3) ||
			__builtin_add_overflow(res2, res3, &res4)){
			throw std::overflow_error("Arithmetic overflow!\n"); 
		}
	}
	Fraction Fraction::operator+(const Fraction& other) const {
		add_overflow(*this, other);
		int numerator = (getNumerator() * other.getDenominator()) + (other.getNumerator()*getDenominator());
		int denominator = (getDenominator()*other.getDenominator());
		Fraction sum(numerator, denominator);
		sum.reduce();
		return sum;
	}
	Fraction Fraction::operator+(const float& other) const {
		Fraction temp(other);
		return (*this + temp);
	}
	Fraction operator+(const float& num, const Fraction& frac){
		return (frac + num);
	}


	void sub_overflow(const Fraction& frac1, const Fraction& frac2) {
		int res1, res2, res3, res4;
		if(__builtin_mul_overflow(frac1.getDenominator(), frac2.getDenominator(), &res1) || 
			__builtin_mul_overflow(frac1.getDenominator(), frac2.getNumerator(), &res2) || 
			__builtin_mul_overflow(frac2.getDenominator(), frac1.getNumerator(), &res3) ||
			__builtin_sub_overflow(res2, res3, &res4)){
			throw std::overflow_error("Arithmetic overflow!\n"); 
		}
	}
	Fraction Fraction::operator-(const Fraction& other) const {
		sub_overflow(*this, other);
		int numerator = (getNumerator() * other.getDenominator()) - (other.getNumerator()*getDenominator());
		int denominator = (getDenominator()*other.getDenominator());
		Fraction diff(numerator, denominator);
		diff.reduce();
		return diff;
	}
	Fraction Fraction::operator-(const float& other) const {
		Fraction temp(other);
		return (*this - temp);
	}
	Fraction operator-(const float& num, const Fraction& frac){
		Fraction temp(num);
		return (temp - frac);
	}


	void mul_overflow(const Fraction& frac1, const Fraction& frac2) {
		// int num_mul = frac1.getNumerator() * frac2.getNumerator();
		// if (num_mul / frac1.getNumerator() != frac2.getNumerator()) {
		// 	throw std::overflow_error("Arithmetic overflow!\n"); 
		// }
		// int den_mul = frac1.getDenominator() * frac2.getDenominator();
		// if (den_mul / frac1.getDenominator() != frac2.getDenominator()) {
		// 	throw std::overflow_error("Arithmetic overflow!\n");
		// }
		int res1, res2;
		if((__builtin_mul_overflow(frac1.getNumerator(), frac2.getNumerator(), &res1)) || 
			(__builtin_mul_overflow(frac1.getDenominator(), frac2.getDenominator(), &res2))){
			throw std::overflow_error("Arithmetic overflow!\n"); 
		}
	}
	Fraction Fraction::operator*(const Fraction& other) const {
		mul_overflow(*this, other);
		int numerator = getNumerator() * other.getNumerator();
		int denominator = getDenominator() * other.getDenominator();
		Fraction product(numerator, denominator);
		product.reduce();
		return product;
	}
	Fraction Fraction::operator*(const float& other) const {
		Fraction temp(other);
		return (temp * (*this));
	}
	Fraction operator*(const float& num, const Fraction& frac){
		return frac * num;
	}


	void div_overflow(const Fraction& frac1, const Fraction& frac2) {
		// int num_div = frac1.getNumerator() * frac2.getDenominator();
		// if (num_div / frac1.getNumerator() != frac2.getDenominator()) {
		// 	throw std::overflow_error("Arithmetic overflow!\n"); 
		// }
		// int den_div = frac1.getDenominator() * frac2.getNumerator();
		// if (den_div / frac1.getDenominator() != frac2.getNumerator()) {
		// 	throw std::overflow_error("Arithmetic overflow!\n");
		// }
		int res1, res2;
		if((__builtin_mul_overflow(frac1.getNumerator(), frac2.getDenominator(), &res1)) || 
			(__builtin_mul_overflow(frac1.getDenominator(), frac2.getNumerator(), &res2))){
			throw std::overflow_error("Arithmetic overflow!\n"); 
		}
	}
	Fraction Fraction::operator/(const Fraction& other) const {
		if (other.getNumerator() == 0) {
			throw std::runtime_error("Can't divide by 0.\n"); 
		}
		div_overflow(*this, other);
		int numerator = getNumerator() * other.getDenominator();
		int denominator = getDenominator() * other.getNumerator();
		Fraction quotient(numerator, denominator);
		quotient.reduce();
		return quotient;
	}
	Fraction Fraction::operator/(const float& other) const {
		if(other == 0){
			throw std::runtime_error("Can't divide by 0.\n");
		}
		Fraction temp(other);
		return ((*this) / temp);
	}
	Fraction operator/(const float& num, const Fraction& frac) {
		Fraction temp(num);
		return temp / frac;
	}



	// Boolean functions
	bool Fraction::operator==(const Fraction& other) const {
		Fraction temp(*this - other);
		return temp.getNumerator() == 0;
	}
	bool Fraction::operator==(const float& other) const {
		Fraction otherFrac(other);
		return *this == otherFrac;
	}
	bool operator==(const float& left, const Fraction& right) {
		return right == left;
	}

	bool Fraction::operator>(const Fraction& other) const {
		Fraction temp(*this - other);
		return (temp.getNumerator() > 0 && temp.getDenominator() > 0);
	}
	bool Fraction::operator>(const float& other) const {
		Fraction otherFrac(other);
		return *this > otherFrac;
	}
	bool operator>(const float& left, const Fraction& right) {
		return right < left;
	}

	bool Fraction::operator<(const Fraction& other) const {
		Fraction temp(*this - other);
		int num = temp.getNumerator();
		int den = temp.getDenominator();
		return((num < 0 && den > 0)||(num > 0 && den < 0));
	}
	bool Fraction::operator<(const float& other) const {
		Fraction otherFrac(other);
		return *this < otherFrac;
	}
	bool operator<(const float& left, const Fraction& right) {
		return right > left;
	}

	bool Fraction::operator>=(const Fraction& other) const {
		return(*this > other || *this == other);
	}
	bool Fraction::operator>=(const float& other) const {
		Fraction otherFrac(other);
		return *this >= otherFrac;
	}
	bool operator>=(const float& left, const Fraction& right) {
		return right <= left;
	}

	bool Fraction::operator<=(const Fraction& other) const {
		return(*this < other || *this == other);
	}
	bool Fraction::operator<=(const float& other) const {
		Fraction otherFrac(other);
		return *this <= otherFrac;
	}
	bool operator<=(const float& left, const Fraction& right) {
		return right >= left;
	}



	// Incrementing operators
	Fraction& Fraction::operator++() {
		setNumerator(getNumerator()+getDenominator());;
		return *this;
	}
	Fraction Fraction::operator++(int postfix) {
		Fraction temp(*this);
		setNumerator(getNumerator()+getDenominator());;
		return temp;
	}

	Fraction& Fraction::operator--() {
		setNumerator(getNumerator()-getDenominator());;
		return *this;
	}
	Fraction Fraction::operator--(int postfix) {
		Fraction temp(*this);
		setNumerator(getNumerator()-getDenominator());;
		return temp;
	}


	// Input/Output operators
	std::ostream& operator <<(std::ostream& output, const Fraction& frac) {
		output << frac.getNumerator() << '/' << frac.getDenominator();
		return output;
	}
	std::istream& operator >>(std::istream& input, Fraction& frac) {
		int numerator = 1;
		int denominator = 1;
		input >> numerator >> denominator;
		if (!input) {
			throw std::runtime_error("Not enough parameters.\n");
		}
		if (denominator == 0) {
			throw std::runtime_error("Denominator can't be 0.\n");
		}
		frac._numerator = numerator;
		frac._denominator = denominator;
		frac.reduce();
		return input;
	}

	//Functions for reducing the fraction form
	int gcd(int a, int b) {
		if(a < 0) {
			a *= (-1);
		}
		if(b < 0){
			b *= (-1);
		}
		if (a == b){
			return a;
		}
		if(a == 0){
			return b;
		}
		if(b == 0){
			return a;
		}
		while(b != 0){
			int r = a % b;
			a = b;
			b = r;
		}
		return a;
	}

	void Fraction::reduce() {
		int divisor = gcd(getNumerator(), getDenominator());
		int numerator = getNumerator() / divisor;
		int denominator = getDenominator() / divisor;
		if ((numerator < 0 && denominator < 0) || (numerator > 0 && denominator < 0)) {
			numerator *= (-1);
			denominator *= (-1);
		}
		this->setNumerator(numerator);
		this->setDenominator(denominator);
	}
}