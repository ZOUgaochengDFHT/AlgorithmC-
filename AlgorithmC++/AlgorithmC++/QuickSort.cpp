//
//  QuickSort.cpp
//  AlgorithmC++
//
//  Created by GaoCheng.Zou on 2017/6/26.
//  Copyright © 2017年 Minxin. All rights reserved.
//

#include "QuickSort.hpp"
#include <iostream>
#include <exception>

using namespace std;

/**
 随机取值
 */
int RandomInRange(int start, int end)
{
    srand((unsigned)time(NULL));
    int value = rand() % (end - start + 1)+ start;
    return value;
}


/**
 必须是指针的交换
 
 @param a 指针a
 @param b 指针b
 */
void Swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int data[], int length, int start, int end)
{
    if (data == NULL || length <= 0 || start < 0 || end >= length)
        throw std::invalid_argument("Invalid Parameters");
    int index = RandomInRange(start, end);
    Swap(&data[index], &data[end]); // 将选取的数字放到最后
    
    int small = start - 1;
    for (index = start; index < end; ++ index) { // 此处是从一边遍历，另外可以从两边开始遍历
        if (data[index] < data[end]) {
            ++ small;// 位置在small之前的数字，都是比选取的数字小的
            if (small != index) {
                Swap(&data[index], &data[small]);
            }
        }
    }
    
    ++ small;
    Swap(&data[small], &data[end]);// 最后将选取的数字放到合适的位置
    return small;
}

void QuickSort(int data[], int length, int start, int end)
{
    if (start == end) return;
    int index = Partition(data, length, start, end);
    if (index > start) {
        QuickSort(data, length, start, index - 1);
        if (index < end)
            QuickSort(data, length, index + 1, end);
    }
}


int _main(int argc, const char * argv[]) {
    // insert code here...
    int data[] = {2,4,3,8,5,7,6};
    QuickSort(data, 7, 0, 6);
    for(int i = 0; i < 7; i++) {
        cout << data[i] << endl;
    }
    return 0;
}
