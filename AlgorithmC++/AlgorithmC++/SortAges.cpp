//
//  SortAges.cpp
//  AlgorithmC++
//
//  Created by GaoCheng.Zou on 2017/6/26.
//  Copyright © 2017年 Minxin. All rights reserved.
//

#include "SortAges.hpp"
#include <iostream>

using namespace std;

void SortAges(int ages[], int length)
{
    if (ages == NULL || length <= 0) return;
    
    const int oldestAge = 99;
    int timesOfAge[oldestAge + 1]; // timesOfAge[]用来统计每个年龄出现的次数
    
    for (int i = 0; i <= oldestAge; ++ i)
        timesOfAge[i] = 0;
    
    for (int i = 0; i < length; ++ i) {
        int age = ages[i];
        if (age < 0 || age > oldestAge) {
            throw new out_of_range("age out of range.");
        }
        ++ timesOfAge[age];
    }
    
    int index = 0;
    for (int i = 0; i <= oldestAge; ++ i) {
        for (int j = 0; j < timesOfAge[i]; ++ i) {
            ages[index] = i;
            ++ index;
        }
    }
    
}

//
//int main(int argc, const char * argv[]) {
//    // insert code here...
//    int a[] = {1, 8, 5, 9, 4, 7, 2};
//    SortAges(a, 7);
//    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
//        cout << a[i] << endl;
//    }
//    return 0;
//}
