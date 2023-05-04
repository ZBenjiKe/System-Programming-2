#include "Fraction.hpp"
#include <iostream>

namespace ariel {


	// Constructors
	Fraction::Fraction(const int& numerator, const int& denominator):
		_numerator(numerator),
		_denominator(denominator) {	
			if(denominator == 0){
				throw std::invalid_argument("Denominator can't be 0.\n");
			}
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
		_numerator(num * 1000),
		_denominator(1000){}

	// Destructor
	Fraction::~Fraction(){}


	
	// Arithmetic Operators
	Fraction Fraction::operator+(const Fraction& other) const {
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

	Fraction Fraction::operator-(const Fraction& other) const {
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

	Fraction Fraction::operator*(const Fraction& other) const {
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

	Fraction Fraction::operator/(const Fraction& other) const {
		int numerator = getNumerator() * other.getDenominator();
		int denominator = getDenominator() * other.getNumerator();
		Fraction quotient(numerator, denominator);
		quotient.reduce();
		return quotient;
	}
	Fraction Fraction::operator/(const float& other) const {
		if(other == 0){
			throw std::invalid_argument("Denominator can't be 0.\n");
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
		return (temp.getNumerator() < 0 || temp.getDenominator() < 0);
	}
	bool Fraction::operator<(const float& other) const {
		Fraction otherFrac(other);
		return *this < otherFrac;
	}
	bool operator<(const float& left, const Fraction& right) {
		return right > left;
	}

	bool Fraction::operator>=(const Fraction& other) const {
		Fraction temp(*this - other);
		return temp.getNumerator() / temp.getDenominator() >= 0;
	}
	bool Fraction::operator>=(const float& other) const {
		Fraction otherFrac(other);
		return *this >= otherFrac;
	}
	bool operator>=(const float& left, const Fraction& right) {
		return right <= left;
	}

	bool Fraction::operator<=(const Fraction& other) const {
		Fraction temp(*this - other);
		return temp.getNumerator() / temp.getDenominator() <= 0;
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
	Fraction Fraction::operator++(int suffix) {
		Fraction temp(*this);
		setNumerator(getNumerator()+getDenominator());;
		return temp;
	}

	Fraction& Fraction::operator--() {
		setNumerator(getNumerator()-getDenominator());;
		return *this;
	}
	Fraction Fraction::operator--(int suffix) {
		Fraction temp(*this);
		setNumerator(getNumerator()-getDenominator());;
		return temp;
	}



	std::ostream& operator <<(std::ostream& out, const Fraction& frac) {
		out << frac.getNumerator() << '/' << frac.getDenominator();
		return out;
	}
	std::istream& operator >>(std::istream& in, Fraction& frac) {
		return in;
	}


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
		if(b==0){
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
		this->setNumerator(numerator);
		this->setDenominator(denominator);
	}
}