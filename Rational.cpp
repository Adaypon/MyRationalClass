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
 
Rational::Rational() {
    numerator = 1;
    denumerator = 1;
}

Rational::Rational(int x, int y) {
    numerator = x;
    denumerator = y;

    // Если y равен 0, значит выполнили где-то
    // деление на 0
    // Выставим nan в true
    nan = (y == 0);
}

Rational::Rational(int x) {
    numerator = x;
    denumerator = 1;
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
 * Арифмитические операции
 */

Rational Rational::sum(Rational r) {
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
    return
        numerator * r.denumerator == r.numerator * denumerator;
}

bool Rational::neq(Rational r) {
    return !eq(r);
}

bool Rational::lt(Rational r) {
    return
        numerator * r.denumerator < r.numerator * denumerator;
}

bool Rational::leq(Rational r) {
    return
        numerator * r.denumerator <= r.numerator * denumerator;
}

bool Rational::gt(Rational r) {
    return
        numerator * r.denumerator > r.numerator * denumerator;
}

bool Rational::geq(Rational r) {
    return
        numerator * r.denumerator >= r.numerator * denumerator;
}

/**
 * служебные операции
 */

void Rational::print() {
	/*
	std::cout 
        << numerator
        << "/"
        << denumerator
        << std::endl;
	*/
	
    if (nan)
        std::cout << "<NAN>\n"
        << std::endl;
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
}

int main() {
	
    Rational x; // 1/1
    Rational y(10, 5); // 10/5
    Rational z(7);
	
	x.print();
	y.print();
	z.print();
	
    std::cout << "x.eq(y): ";
    std::cout << x.eq(y) << std::endl;
    std::cout << "x.neq(y): ";
    std::cout << x.neq(y) << std::endl;
    std::cout << "z.neg(): ";
    z.neg().print();
	std::cout << "z.inv(): ";
    z.inv().print();
	std::cout << std::endl;
    
	Rational n(10, 0);
	n.print();
    n.mul(Rational(1)).print();
    Rational(1).mul(n).print();
	std::cout << std::endl;
	
	std::cout << "Enter rational number z: ";
	z.scan();
	z.print();
	z.sum(y).reduce().print();
	z.print();
	
}
