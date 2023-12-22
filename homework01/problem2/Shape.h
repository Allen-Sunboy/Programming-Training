#pragma once

const double PI = 3.14159;

class Shape {
    public:
        virtual double getarea() { return 0; }
};

class Circle : public Shape {
    private:
        double r; // 半径
    public:
        Circle(double R) : r(R) {}
        double getarea() { return PI * r * r; }
};

class Square : public Shape {
    private:
        double a; // 边长
    public:
        Square(double A) : a(A) {}
        double getarea() { return a * a; }
};

class Rectangle : public Shape {
    private:
        double a;
        double b; // 长 宽
    public:
        Rectangle(double A, double B) : a(A), b(B) {}
        double getarea() { return a * b; }
};