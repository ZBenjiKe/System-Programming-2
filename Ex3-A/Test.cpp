#include "doctest.h"
#include <iostream>
#include "sources/Fraction.hpp"
using namespace ariel;


TEST_CASE("Case 1: Constructors.\n") {
	CHECK_THROWS(Fraction(1,0));
	CHECK_NOTHROW(Fraction(1,7));
	CHECK_NOTHROW(Fraction(-2,5));
	Fraction f1(2,3);
	Fraction f2(f1);
	CHECK(f1 == f2);
	Fraction f3((float)5.23);
	Fraction f4(f3);
	CHECK(f3 == f4);
}

TEST_CASE("Case 2: Getters and setters.\n") {
	Fraction f1(2,3);

	int numerator = f1.getNumerator();
	int denominator = f1.getDenominator();
	CHECK(numerator == 2);
	CHECK(denominator == 3);

	f1.setNumerator(6);
	f1.setDenominator(7);
	int newNumerator = f1.getNumerator();
	int newDenominator = f1.getDenominator();
	CHECK(newNumerator == 6);
	CHECK(newDenominator == 7);

	CHECK_THROWS(f1.setDenominator(0));
}

TEST_CASE("Case 3: Reducing fractions.\n") {
	Fraction f1(2,3);
	f1.reduce();
	CHECK(f1.getNumerator() == 2);
	CHECK(f1.getDenominator() == 3);
	Fraction f2(20,80);
	f2.reduce();
	CHECK(f2.getNumerator() == 1);
	CHECK(f2.getDenominator() == 4);
	Fraction f3(2142,4074);
	f3.reduce();
	CHECK(f3.getNumerator() == 51);
	CHECK(f3.getDenominator() == 97);
	Fraction f4(14,14);
	f4.reduce();
	CHECK(f4.getNumerator() == 1);
	CHECK(f4.getDenominator() == 1);
	Fraction f5((float)0.75);
	f5.reduce();
	CHECK(f5.getNumerator() == 3);
	CHECK(f5.getDenominator() == 4);
}

TEST_CASE("Case 4: '==' operator.\n") {
	Fraction f1(2,3);
	Fraction f2(6,9);
	Fraction f3(1,4);
	CHECK(f1 == f2);
	CHECK(f1 != f3);
}

TEST_CASE("Case 5: '+' operator.\n") {
	Fraction f1(2,3);
	Fraction f2(4,5);
	Fraction f3(f1+f2);
	CHECK(f3.getNumerator() == 22);
	CHECK(f3.getDenominator() == 15);

	Fraction f4(2,3);
	Fraction f5(5,15);
	Fraction f6(f4+f5);
	CHECK(f6.getNumerator() == 1);
	CHECK(f6.getDenominator() == 1);

	Fraction f7(f2+(float)0.20);
	CHECK(f7.getNumerator() == 1);
	CHECK(f7.getDenominator() == 1);

	Fraction f8(4,10);
	Fraction f9(f8 + (float)0.1);
	CHECK(f9.getNumerator() == 1);
	CHECK(f9.getDenominator() == 2);
}

TEST_CASE("Case 6: '-' operator.\n") {
	Fraction f1(2,3);
	Fraction f2(3,9);
	Fraction f3(f1-f2);
	CHECK(f3.getNumerator() == 1);
	CHECK(f3.getDenominator() == 3);

	Fraction f4(1,5);
	Fraction f5(2,10);
	Fraction f6(f4-f5);
	CHECK(f6.getNumerator() == 0);

	Fraction f7(f4-(float)0.20);
	CHECK(f7.getNumerator() == 0);

	Fraction f8(6,10);
	Fraction f9(f8 - (float)0.1);
	CHECK(f9.getNumerator() == 1);
	CHECK(f9.getDenominator() == 2);
}

TEST_CASE("Case 7: '*' operator.\n") {
	Fraction f1(1,2);
	Fraction f2(f1*f1);
	CHECK(f2.getNumerator() == 1);
	CHECK(f2.getDenominator() == 4);

	CHECK(f2 * 0 == 0);

	Fraction f3(3,6);
	Fraction f4(f3 * f3 *(-1));
	CHECK(f4 == -0.25);
}

TEST_CASE("Case 8: '/' operator.\n") {
	Fraction f1(1,4);
	Fraction f2(f1/f1);
	CHECK(f2 == 1);
	CHECK(f1 / 0.5 == 0.5);
	CHECK(0.5 / f1 == 2);
	CHECK_THROWS(f2 / 0);
}

TEST_CASE("Case 9: Boolean operators.\n") {
	Fraction f1(1,4);
	Fraction f2(2,3);
	Fraction f3(4,16);
	CHECK_FALSE(f3 > f1);
	CHECK(f1 < f2);
	CHECK(f2 > f3);
	CHECK(f2 >= f1);
	CHECK(f3 >= f1);
	CHECK_FALSE(f1 < f3);
}

TEST_CASE("Case 10: Incrementing operators.\n") {
	Fraction f1(1,4);
	Fraction f2(8,2);
	CHECK(f1++ == 0.25);
	CHECK(++f1 == 2.25);
	CHECK(f2-- == 4);
	CHECK(--f2 == 2);
}

