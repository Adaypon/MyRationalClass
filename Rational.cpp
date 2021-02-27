#include "Rational.h"
#include <iostream>
#include <cmath>

// НОД
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

// НОК
int lcm(int a, int b) {
	return a / gcd(a, b) * b;
}

// конструктор
Rational::Rational(int x = 1, int y = 1)
    : numerator(x), denumerator(y) 
{
    // Если y равен 0, значит выполнили где-то деление на 0
    // Выставим nan в true
    nan = (y == 0);
}

// конструктор копирования
Rational::Rational(const Rational& copy) {
	this->nan = copy.nan;
	this->numerator = copy.numerator;
	this->denumerator = copy.denumerator;
}

// присваивание копирование
Rational& Rational::operator=(const Rational& other) {
	Rational copy(other);
	std::swap(this->nan, copy.nan);
	std::swap(this->numerator, copy.numerator);
	std::swap(this->denumerator, copy.denumerator);
	return *this;
}


/**
 * Арифметические операции (перегрузки операторов)
 */

Rational Rational::operator+(const Rational& other) {
    if (checkNAN(*this, other)) {
        std::cout << "sum Illegal operation: one of objects is NAN" << std::endl;
        return Rational(1, 0); // возврат NAN (стоит ли возвращать что-то другое?)
    }
	int commonDenumerator = lcm(denumerator, other.denumerator); // общий знаменатель
	return Rational(
		numerator * (commonDenumerator / denumerator) + other.numerator * (commonDenumerator / other.denumerator),
		commonDenumerator
	);
}

Rational Rational::operator-(Rational& other) { // нужна ли const Rational&, если вызывается neg()?
    return (*this + other.neg());
}

Rational Rational::operator*(const Rational& other) {
    if (checkNAN(*this, other)) {
        std::cout << "mul Illegal operation: one of objects is NAN" << std::endl;
        return Rational(1, 0); // возврат NAN
    }
    
	return Rational(
		numerator * other.numerator,
		denumerator * other.denumerator
	);
}

Rational Rational::operator/(Rational& other) {
    if (checkNAN(*this, other)) {
        std::cout << "div Illegal operation: one of objects is NAN" << std::endl;
        return Rational(1, 0); // возврат NAN
    }
	return (*this * other.inv());
}


/**
 * Операции сравнения
 */

bool Rational::operator==(const Rational& other) {
    if (checkNAN(*this, other)) {
        std::cout << "Illegal comparison: one of objects is NAN" << std::endl;
        return false;
    }
    return
        numerator * other.denumerator == other.numerator * denumerator;
}

bool Rational::operator!=(const Rational& other) {
    return !(*this == other);
}

bool Rational::operator<(const Rational& other) {
    if (checkNAN(*this, other)) {
        std::cout << "Illegal comparison: one of objects is NAN" << std::endl;
        return false;
    }
    if (denumerator == other.denumerator) {
        return numerator < other.numerator;
    }
    return
        numerator * other.denumerator < other.numerator * denumerator;
}

bool Rational::operator>(const Rational& other) {
    if (checkNAN(*this, other)) {
        std::cout << "Illegal comparison: one of objects is NAN" << std::endl;
        return false;
    }
    if (denumerator == other.denumerator) {
        return numerator > other.numerator;
    }
    return
        numerator * other.denumerator > other.numerator * denumerator;
}

bool Rational::operator<=(const Rational& other) {
    return !(*this > other);
}

bool Rational::operator>=(const Rational& other) {
    return !(*this < other);
}


// Сокращение
Rational Rational::reduce() {
	int del = abs(gcd(numerator, denumerator));
	if (del != 1) {
		return Rational(
			numerator / del,
			denumerator / del
		);
	}
    else if (del < 0) {
        return Rational(
			numerator,
			denumerator
		).neg();
    }
	else {
		return Rational(
			numerator,
			denumerator
		);
	}
}

// *-1
Rational Rational::neg() {
    return Rational(
            -1 * numerator,
            denumerator
    );
}

// ^-1
Rational Rational::inv() {
    return Rational(
        denumerator,
        numerator
    );
}


/*
Rational Rational::sum(Rational r) {
    if (checkNAN(*this, r)) {
        std::cout << "sum Illegal operation: one of objects is NAN" << std::endl;
        return *this;
    }
	int commonDenumerator = lcm(denumerator, r.denumerator); // общий знаменатель
	return Rational(
		numerator * (commonDenumerator / denumerator) + r.numerator * (commonDenumerator / r.denumerator),
		commonDenumerator
	);
}

Rational Rational::sub(Rational r) {
	return sum(r.neg());
}

Rational Rational::mul(Rational r) {
    if (checkNAN(*this, r)) {
        std::cout << "mul Illegal operation: one of objects is NAN" << std::endl;
        return *this;
    }
    
	return Rational(
		numerator * r.numerator,
		denumerator * r.denumerator
	);
}

Rational Rational::div(Rational r) {
    if (checkNAN(*this, r)) {
        std::cout << "div Illegal operation: one of objects is NAN" << std::endl;
        return *this;
    }
	return mul(r.inv());
}



bool Rational::eq(Rational r) {
    if (checkNAN(*this, r)) {
        std::cout << "Illegal operation: one of objects is NAN" << std::endl;
        return false;
    }
    return
        numerator * r.denumerator == r.numerator * denumerator;
}

bool Rational::neq(Rational r) {
    return !eq(r);
}

bool Rational::lt(Rational r) {
    if (checkNAN(*this, r)) {
        std::cout << "Illegal operation: one of objects is NAN" << std::endl;
        return false;
    }
    return
        numerator * r.denumerator < r.numerator * denumerator;
}

bool Rational::leq(Rational r) {
    return !gt(r);
}

bool Rational::gt(Rational r) {
    if (checkNAN(*this, r)) {
        std::cout << "Illegal operation: one of objects is NAN" << std::endl;
        return false;
    }
    return
        numerator * r.denumerator > r.numerator * denumerator;
}

bool Rational::geq(Rational r) {
    return !lt(r);
}
*/


/**
 * служебные операции
 */

void Rational::print() {
	if (nan)
        std::cout << "<NAN>" << std::endl;
    else
        std::cout 
            << numerator
            << "/"
            << denumerator
            << std::endl;
	
}

void Rational::scan() {
    std::cin
        >> numerator
        >> denumerator;
    nan = (denumerator == 0);
}

bool Rational::isNAN() {
    return this->nan;
}

bool Rational::checkNAN(Rational a, Rational b) {
    if (a.isNAN() || b.isNAN()) {
        return true;
    }
    return false;
}


int main() {
    Rational x;
    Rational y;
    x.scan();
    y.scan();
    Rational c = x + y;
    c.print();
    c.reduce().print();

    return 0;
}