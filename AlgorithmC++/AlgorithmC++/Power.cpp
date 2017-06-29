//
//  Power.cpp
//  AlgorithmC++
//
//  Created by GaoCheng.Zou on 2017/6/27.
//  Copyright © 2017年 Minxin. All rights reserved.
//

#include "Power.hpp"

bool g_Invalidinput = false;

bool equal(double num1, double num2)
{
    if (num1 - num2 > -0.0000001 && num1 - num2 < 0.0000001) return true;
    else return false;
}

double PowerWithUnsignedExponent(double base, unsigned int exponent)
{
    //    double result = 1.0;
    //    for(int i = 1; i <= exponent; ++ i)
    //        result *= base;
    if (exponent == 0)
        return 1;
    if (exponent == 1)
        return base;
    double result = PowerWithUnsignedExponent(base, exponent >> 1);
    result *= result;
    if ((exponent & 0x1) == 1)
        result *= base;
    return result;
}

double Power(double base, int exponent)
{
    g_Invalidinput = false;
    
    if (equal(base, 0.0) && exponent < 0) {
        g_Invalidinput = true;
        return 0.0;
    }
    
    unsigned int absExponent = (unsigned int)(exponent);
    if (exponent < 0) absExponent = (unsigned int) (-exponent);
    
    double result = PowerWithUnsignedExponent(base, exponent);
    if (exponent < 0) result = 1.0 / result;
    return result;
}
