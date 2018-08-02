#pragma once
class Calculator 
{
public:
    static int Add(int& a, int&b)
    {
        return a + b;
    }

    static int Subtract(int& a, int&b)
    {
        return a - b;
    }

    static int Mutiply(int& a, int&b)
    {
        return a * b;
    }

    static int Divide(int& a, int&b)
    {
        return a / b;
    }

};