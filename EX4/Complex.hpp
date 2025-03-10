#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

namespace ariel {

    class Complex {
    private:
        double real;
        double imag;

    public:
        Complex(double r = 0, double i = 0) : real(r), imag(i) {}

        Complex operator+(const Complex &other) const {
            return Complex(real + other.real, imag + other.imag);
        }

        Complex operator-(const Complex &other) const {
            return Complex(real - other.real, imag - other.imag);
        }

        Complex operator*(const Complex &other) const {
            return Complex((real * other.real) - (imag * other.imag), (real * other.imag) + (imag * other.real));
        }

        friend bool operator==(const Complex &c1, const Complex &c2) {
            return ((c1.real == c2.real) && (c1.imag == c2.imag));
        }

        friend std::ostream &operator<<(std::ostream &os, const Complex &c) {
            os << c.real << " + " << c.imag << "i";
            return os;
        }
    };

}

#endif // COMPLEX_HPP
