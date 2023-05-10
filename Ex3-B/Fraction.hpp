#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <limits>

namespace ariel{

	class Fraction {
	private:
		int _numerator;
		int _denominator;

	public:
		Fraction(const int& numerator = 1, const int& denominator = 1);
		Fraction(const Fraction& other);
		Fraction(Fraction&& other) noexcept;
		Fraction(float num);
		Fraction(double num);
		~Fraction();

		int getNumerator() const {
			return this->_numerator;
		}

		int getDenominator() const {
			return this->_denominator;
		}

		void setNumerator(int numerator) {
			this->_numerator = numerator;
		}
		void setDenominator(int denominator) {
			if(denominator == 0){
				throw std::runtime_error("Denominator can't be 0.\n");
			}
			this->_denominator = denominator;
		}


		void reduce();


		Fraction& operator =(Fraction&& other) noexcept;
		Fraction& operator =(const Fraction& other);


		Fraction operator +(const Fraction& other) const;
		Fraction operator +(const float& other) const;
		friend Fraction operator +(const float& num, const Fraction& frac);

		Fraction operator -(const Fraction& other) const;
		Fraction operator -(const float& other) const;
		friend Fraction operator -(const float& num, const Fraction& frac);

		Fraction operator *(const Fraction& other) const;
		Fraction operator *(const float& other) const;
		friend Fraction operator *(const float& num, const Fraction& frac);

		Fraction operator /(const Fraction& other) const;
		Fraction operator /(const float& other) const;
		friend Fraction operator /(const float& left, const Fraction& right);

		bool operator ==(const Fraction& other) const;
		bool operator ==(const float& other) const;
		friend bool operator ==(const float& left, const Fraction& right);

		bool operator >(const Fraction& other) const;
		bool operator >(const float& other) const;
		friend bool operator >(const float& left, const Fraction& right);

		bool operator <(const Fraction& other) const;
		bool operator <(const float& other) const;
		friend bool operator <(const float& left, const Fraction& right);

		bool operator >=(const Fraction& other) const;
		bool operator >=(const float& other) const;
		friend bool operator >=(const float& left, const Fraction& right);

		bool operator <=(const Fraction& other) const;
		bool operator <=(const float& other) const;
		friend bool operator <=(const float& left, const Fraction& right);


		Fraction& operator ++();
		Fraction operator ++(int postfix);
		Fraction& operator --();
		Fraction operator --(int postfix);


		friend std::ostream& operator <<(std::ostream& output, const Fraction& frac);

		friend std::istream& operator >>(std::istream& input, Fraction& frac);

	};
}

#endif