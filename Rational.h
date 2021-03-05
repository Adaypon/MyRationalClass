#pragma once
#include <iostream>
#include <cmath>

/**
 * Дробь, x/y
 */
class Rational {
public:
    explicit Rational(int, int);
	
    // конструктор копирования
	Rational(const Rational&);
	
    // присваивание копирование
	Rational& operator=(const Rational&);

    Rational operator+(const Rational&);
    Rational operator-(const Rational&);
    Rational operator*(const Rational&);
    Rational operator/(const Rational&);
    
    bool operator==(const Rational&);
    bool operator!=(const Rational&);
    bool operator<(const Rational&);
    bool operator<=(const Rational&);
    bool operator>(const Rational&);
    bool operator>=(const Rational&);

    // Сокращение
    Rational reduce();

    // *-1
    Rational neg();
    // ^-1
    Rational inv();

    Rational sum(Rational);
    Rational sub(Rational);
    Rational mul(Rational);
    Rational div(Rational);

    // ==
    bool eq(Rational);
    // !=
    bool neq(Rational);
    // less than
    // <
    bool lt(Rational);
    // less or equal than
    // <=
    bool leq(Rational);
    // greater than
    // >
    bool gt(Rational);
    // greater or equal than
    // >=
    bool geq(Rational);

    // Вывести на экран
    void print(std::ostream&);
    // Считать с клавиатуры
    void scan(std::istream&);
	// Перегрузки операторов ввода-вывода
	friend std::ostream& operator<<(std::ostream&, Rational);
	friend std::istream& operator>>(std::istream&, Rational&);
    
    // Возврат переменной nan
    bool isNAN();
    // Проверка на NAN
    bool checkNAN(Rational, Rational);

private:
    // not a number
    // Указывает, что число не является числом
    // по аналогии с float
    // Устанавливается в true,
    // если выполнили операцию
    // с делением на ноль
    bool nan = false;
    int numerator;
    int denumerator;
};