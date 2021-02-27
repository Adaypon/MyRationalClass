#pragma once

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
    Rational operator-(Rational&);
    Rational operator*(const Rational&);
    Rational operator/(Rational&);
    
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


    // Вывести на экран
    void print();
    // Считать с клавиатуры
    void scan();
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