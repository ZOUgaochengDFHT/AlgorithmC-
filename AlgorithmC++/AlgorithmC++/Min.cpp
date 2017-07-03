//
//  Min.cpp
//  AlgorithmC++
//
//  Created by GaoCheng.Zou on 2017/6/26.
//  Copyright © 2017年 Minxin. All rights reserved.
//

#include "Min.hpp"
#include <iostream>

using namespace std;

/**
 顺序查找
 */
int MinInOrder(int* numbers, int index1, int index2)
{
    int result = numbers[index1];
    for (int i = index1 + 1; i <= index2; ++ i) {
        if (result > numbers[i]) result = numbers[i];
    }
    return result;
}

/**
 二分法求最小值
 
 @param numbers 数组
 @param length  长度
 
 @return 最小值
 */

int Min(int* numbers, int length)
{
    if (numbers == NULL || length < 0)
        throw invalid_argument("Invalid parameters");
    
    int index1 = 0;
    int index2 = length - 1;
    int indexMid = index1;
    while (numbers[index1] >= numbers[index2]) {
        if (index2 - index1 == 1) {
            indexMid = index2;
            break;
        }
        indexMid = (index1 + index2) / 2;
        // 如果下标为index1、index2和indexMid指向的三个数字相等，则只能顺序查找。
        if (numbers[index1] == numbers[index2] && numbers[indexMid] == numbers[index1])
            return MinInOrder(numbers, index1, index2);
        if (numbers[indexMid] >= numbers[index1])
            index1 = index1;
        else if (numbers[indexMid] <= numbers[index2])
            index2 = index1;
    }
    
    return numbers[indexMid];
}
