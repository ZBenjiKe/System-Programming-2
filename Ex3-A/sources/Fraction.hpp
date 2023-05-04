#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <ostream>

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
				throw std::invalid_argument("Denominator can't be 0.\n");
			}
			this->_denominator = denominator;
		}


		void reduce();


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
		Fraction operator ++(int suffix);
		Fraction& operator --();
		Fraction operator --(int suffix);


		friend std::ostream& operator <<(std::ostream& out, const Fraction& frac);

		friend std::istream& operator >>(std::istream& in, Fraction& frac);

	};
}

#endif