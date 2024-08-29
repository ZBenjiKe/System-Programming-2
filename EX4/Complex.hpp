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

        bool operator<(const Complex &other) const {
            return (real < other.real) || (real == other.real && imag < other.imag);
        }

        friend std::ostream &operator<<(std::ostream &os, const Complex &c) {
            os << c.real << " + " << c.imag << "i";
            return os;
        }
    };

}

#endif // COMPLEX_HPP
