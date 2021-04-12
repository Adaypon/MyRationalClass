#include "Rational.h"

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
    return this->sum(other);
}

Rational Rational::operator-(const Rational& other) {
    return this->sub(other);
}

Rational Rational::operator*(const Rational& other) {
    return this->mul(other);
}

Rational Rational::operator/(const Rational& other) {
    return this->div(other);
}


/**
 * Операции сравнения (перегрузки операторов)
 */

bool Rational::operator==(const Rational& other) {
    return this->eq(other);
}

bool Rational::operator!=(const Rational& other) {
    return this->neq(other);
}

bool Rational::operator<(const Rational& other) {
    return this->lt(other);
}

bool Rational::operator>(const Rational& other) {
    return this->gt(other);
}

bool Rational::operator<=(const Rational& other) {
    return this->leq(other);
}

bool Rational::operator>=(const Rational& other) {
    return this->geq(other);
}

// TODO префиксные/постфиксные операторы

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

/**
 * арифметические операции
 */

Rational Rational::sum(Rational r) {
    if (checkNAN(*this, r)) {
        std::cout << "sum Illegal operation: one of objects is NAN" << std::endl;
        return Rational(1, 0); // возврат NAN (стоит ли возвращать что-то другое?)
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
        return Rational(1, 0); // возврат NAN
    }
    
	return Rational(
		numerator * r.numerator,
		denumerator * r.denumerator
	);
}

Rational Rational::div(Rational r) {
    if (checkNAN(*this, r)) {
        std::cout << "div Illegal operation: one of objects is NAN" << std::endl;
        return Rational(1, 0); // возврат NAN
    }
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

void Rational::print(std::ostream& s = std::cout) {
	if (nan)
        s << "<NAN>" << std::endl;
    else
        s   << numerator
            << "/"
            << denumerator;
	
}

void Rational::scan(std::istream& s = std::cin) {
    s   >> numerator
        >> denumerator;
    nan = (denumerator == 0);
}

std::ostream& operator<<(std::ostream& s, Rational a) {
	a.print(s);
	return s;
}

std::istream& operator>>(std::istream& s, Rational& a) {
	a.scan(s);
	return s;
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
    std::cin >> x >> y;
    std::cout << (x + y).reduce() << std::endl;

    return 0;
}