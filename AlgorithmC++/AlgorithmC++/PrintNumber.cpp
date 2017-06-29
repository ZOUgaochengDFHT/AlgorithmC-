//
//  PrintNumber.cpp
//  AlgorithmC++
//
//  Created by GaoCheng.Zou on 2017/6/27.
//  Copyright © 2017年 Minxin. All rights reserved.
//

#include "PrintNumber.hpp"
#include <iostream>
/**
 每次增长1后，实现用O(1)时间判断是不是已经达到了最大的n位数
 
 @param number 数组
 
 @return 是否达到最大的n位数
 */
bool Increment(char* number)
{
    bool isOverFlow = false;
    int nTakeOver = 0;
    int nLength = (int)strlen(number);
    for (int i = nLength - 1; i >= 0; i --) {
        int nSum = number[i] - '0' + nTakeOver;
        if (i == nLength - 1) nSum++;
        if (nSum >= 10) {
            if (i == 0) {
                isOverFlow = true;
            }else {
                nSum -= 10;
                nTakeOver = 1;
                number[i] = '0' + nSum;
            }
        }else {
            number[i] = '0' + nSum;
            break;
        }
    }
    return isOverFlow;
}

/**
 打印
 
 @param number 数组
 */
void PrintNumber(char* number)
{
    bool isBeginning0 = true;
    int nLength = (int)strlen(number);
    for (int i = 0; i < nLength; ++ i) {
        if (isBeginning0 && number[i] != '0') isBeginning0 = false;
        if (!isBeginning0) {
            printf("%c", number[i]);
        }
        printf("\t");
    }
}

void Print1ToMaxOfNDigits(int n)
{
    if (n < 0) return;
    
    char *number = new char[n + 1]; // 初始化数组
    memset(number, '0', n); // 往字符数组中添加n个0
    number[n] = '0'; // 往字符数组末尾添加0
    
    while (!Increment(number)) {
        PrintNumber(number);
    }
    delete []number;
}
