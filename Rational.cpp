#include "Rational.h"
#include <iostream>

// НОД
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

// НОК
int lcm(int a, int b) {
	return a / gcd(a, b) * b;
}

/**
 * Конструкторы
 */

Rational::Rational(int x = 1, int y = 1)
    : numerator(x), denumerator(y) 
{
    // Если y равен 0, значит выполнили где-то
    // деление на 0
    // Выставим nan в true
    nan = (y == 0);
}

Rational::Rational(const Rational& copy) {
	this->nan = copy.nan;
	this->numerator = copy.numerator;
	this->denumerator = copy.denumerator;
}

Rational& Rational::operator=(const Rational& other) {
	Rational copy(other);
	std::swap(this->nan, copy.nan);
	std::swap(this->numerator, copy.numerator);
	std::swap(this->denumerator, copy.denumerator);
	return *this;
}


// Сокращение
Rational Rational::reduce() {
	int del = gcd(numerator, denumerator);
	if (del != 1) {
		return Rational(
			numerator / del,
			denumerator / del
		);
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

/**
 * Арифметические операции
 */

Rational Rational::sum(Rational r) {
    if (checkNAN(*this, r)) {
        std::cout << "Illegal operation: one of objects is NAN" << std::endl;
        return *this;
    }
	int commonDenumerator = lcm(denumerator, r.denumerator); // общий знаменатель
	return Rational(
		numerator * (commonDenumerator / denumerator) + r.numerator * (commonDenumerator / r.denumerator),
		commonDenumerator
	).reduce(); // после сложения сокращаем число
}

Rational Rational::sub(Rational r) {
	return sum(r.neg());
}

Rational Rational::mul(Rational r) {
    if (checkNAN(*this, r)) {
        std::cout << "Illegal operation: one of objects is NAN" << std::endl;
        return *this;
    }
	return Rational(
		numerator * r.numerator,
		denumerator * r.denumerator
	).reduce(); // после перемножения сокращаем число
}

Rational Rational::div(Rational r) {
	return mul(r.inv());
}

/**
 * Операции сравнения
 */

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
    x.print();
    x = x.inv();
    x = x.sum(y);
    x.print();
}