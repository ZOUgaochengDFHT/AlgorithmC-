
//
//  MergeArray.cpp
//  AlgorithmC++
//
//  Created by GaoCheng.Zou on 2017/6/23.
//  Copyright © 2017年 Minxin. All rights reserved.
//

#include "MergeArray.hpp"
#include <iostream>
#include <vector>

using namespace std;
/**
 合并连个排序数组
 
 @param a      数组A
 @param aCount 数组A的实际（狭义）长度
 @param b      数组B
 @param blen   数组B的实际长度
 */
void MergeArray(int a[], int aCount, int b[], int blen)//aCount为a数组实际（狭义）长度，blen为b数组实际长度
{
    int len = aCount + blen - 1;//合并数组的长度也就是a数组的广义长度
    aCount--;
    blen--;
    while (aCount>=0 && blen>=0)
    {
        if (a[aCount] >= b[blen])
        {
            a[len--] = a[aCount--];
        }
        else
        {
            a[len--] = b[blen--];
        }
    }
    for (int i = 0; i < 10; i++)
    {
        cout<<a[i]<<" ";
    }
    printf("\n");
    while(blen >= 0)
    {
        a[len--] = b[blen--];
    }
    
//    std::vector<int> A = {2, 4, 6, 8, 10, 0, 0, 0, 0, 0};
//    std::vector<int> B = {1, 3, 5, 7, 9};
//    
//    std::vector<int> C;
//    std::vector<int>::iterator i1 = A.begin();
//    std::vector<int>::iterator i2 = B.begin();
//    
//    while (i1 != A.end() && i2 != B.end()) {
//        if (*i1 < *i2) {
//            C.push_back(*i1);
//            i1++;
//        }else {
//            C.push_back(*i2);
//            i2++;
//        }
//    }
//    
//    while(i1 != A.end())
//        C.push_back(*i1++);
//    
//    while(i2 != B.end())
//        C.push_back(*i2++);
//    
//    for (int i = 0; i < 10; i++)
//    {
//        cout<<C[i]<<" ";
//    }
}
