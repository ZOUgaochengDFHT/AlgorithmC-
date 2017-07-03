//
//  ReorderOddEven.cpp
//  AlgorithmC++
//
//  Created by GaoCheng.Zou on 2017/6/27.
//  Copyright © 2017年 Minxin. All rights reserved.
//

#include "ReorderOddEven.hpp"

/**
 交换奇偶
 
 @param pBegin 第一个指针
 @param pEnd  第二个指针
 */
void SwapOddEven(int* pBegin, int* pEnd)
{
    int temp;
    temp = *pBegin;
    *pBegin = *pEnd;
    *pEnd = temp;
}

/**
 重新排序奇偶。使用两个指针，一个指向数组的第一个元素，一个指向数组的最后一个元素。
 
 @param pData  整数数组
 @param length 数组长度
 */
int* ReorderOddEven(int* pData, unsigned int length)
{
    int* pBegin = pData;
    int* pEnd = pData + length - 1;
    while (pBegin < pEnd) {
        //        if (*pBegin % 2 != 0) pBegin++;
        //        if (*pEnd % 2 == 0) pEnd--;
        //        if (pBegin >= pEnd) break;
        //        if (*pBegin % 2 == 0 && *pEnd % 2 != 0) {
        //            SwapOddEven(pBegin, pEnd);
        //        }
        while (pBegin < pEnd && (*pBegin & 1) != 0) {
            pBegin ++;
        }
        while (pBegin < pEnd && (*pEnd & 0x1) == 0) {
            pEnd--;
        }
        if (pBegin < pEnd) {
            SwapOddEven(pBegin, pEnd);
        }
    }
    return pData;
}
