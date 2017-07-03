//
//  main.cpp
//  AlgorithmC++
//
//  Created by GaoCheng.Zou on 2017/6/21.
//  Copyright © 2017年 Minxin. All rights reserved.
//

#include <iostream>

using namespace std;

#pragma mark -- 1.快速排序


/**
 交换
 */
void Swap1(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 随机取值
 */
int RandomInRange1(int start, int end)
{
    srand((unsigned)time(NULL));
    int value = rand() % (end - start + 1) + start;
    return value;
}


/**
 把数组以选中数字为准，把比这个数小的移到数组的左边，比这个数大的移到数组的右边
 */
int Partition1(int data[], int length, int start, int end)
{
    if (data == NULL || length <= 0 || start < 0 || end >= length)
        throw invalid_argument("Invalid Parameters");
    
    int index = RandomInRange1(start, end);
    Swap1(&data[index], &data[end]);
    
    int small = start - 1;
    for (index = start; index < end; ++ index) {
        if (data[index] < data[end]) {
            ++ small;
            if (small != index)
                Swap1(&data[index], &data[small]);
        }
    }
    
    ++ small;
    Swap1(&data[small], &data[end]);
    printf("%d\n", small);
    return small;
}

/**
 递归
 */
void QuickSort1(int data[], int length, int start, int end)
{
    if (start == end)
        return;
    int index = Partition1(data, length, start, end);
    if (index > start)
        QuickSort1(data, length, start, index - 1);
    if (index < end)
        QuickSort1(data, length, index + 1, end);
    
}


#pragma mark -- 2.对公司所有的员工的年龄排序

/**
 快速排序虽然总体的平均效率最好，但是在当数组已经排序好，且每一轮都是以最后一个数字作为比较标准时，此时快速排序的效率只有O(n²)。因此这种情况下的快速排序就不是最优算法。如下，利用长度为100的整数数组作为辅助空间换来了O(n)的时间效率。
 */
void SortAges1(int ages[], int length)
{
    if (ages == NULL || length <= 0)
        return;
    const int oldestAge = 99;
    int timesOfAge[oldestAge + 1];
    
    for (int i = 0; i <= oldestAge; ++ i) {
        timesOfAge[i] = 0;
    }
    
    for (int j = 0; j < length; ++ j) {
        int age = ages[j];
        if (age < 0 || age > oldestAge)
            throw invalid_argument("age out of range.");
        ++ timesOfAge[age];
    }
    
    int index = 0;
    for (int i = 0; i <= oldestAge; ++ i) {
        for (int j = 0; j < timesOfAge[i]; ++ j) {
            ages[index] = i;
            ++ index;
        }
    }
    
}

#pragma mark -- 3.输入一个递增排序的数组的一个旋转，输入旋转数组的最小元素。

/**
 顺序查找
 */
int MinInOrder1(int* numbers, int index1, int index2)
{
    int result = numbers[index1];
    for (int i = index1 + 1; i <= index2; ++ i) {
        if (result > numbers[i])
            result = numbers[i];
    }
    return result;
}
/**
 利用二分查找法实现时间效率为O(logn)的查找。
 */
int Min1(int* numbers, int length)
{
    if (numbers == NULL || length <= 0)
        throw new invalid_argument("Invalid parameters");
    // 两个指针，一个指向数组的第一个元素，一个指向数组的最后一个元素。
    int index1 = 0;
    int index2 = length - 1;
    // 把排序数组前面的0个元素搬到后面，即排序数组本身，这仍是数组的旋转。这就是设置indexMid=index1的原因。数组中最小的元素就是第一个是元素。直接返回最小值。
    int indexMid = index1;
    // 因为是一个递增数组的旋转，所以这个numbers[index1] >= numbers[index2]成立，可作为判断条件
    while (numbers[index1] >= numbers[index2]) {
        // 数组只有两个元素时
        if (index2 - index1 == 1) {
            indexMid = index2;
            break;
        }
        indexMid = (index1 + index2)/2;
        // 如果下标为index1、index2和indexMid指向的三个数字相等，则只能顺序查找
        if (numbers[index1] == numbers[index2] && numbers[indexMid] == numbers[index1])
            return MinInOrder1(numbers, index1, index2);
        if (numbers[indexMid] >= numbers[index2])
            index1 = indexMid;
        else if (numbers[indexMid] <= numbers[index2])
            index2 = indexMid;
    }
    return numbers[indexMid];
}

#pragma mark -- 4.斐波那契数列

/**
 时间复杂度为O(n)的算法，从下往上计算，先计算f(0)和f(1)，然后依次计算。
 */
long long Fibonacci1(unsigned n)
{
    int result[2] = {0, 1};
    if (n < 2)
        return result[n];
    
    long long fibNMinusOne = 1;
    long long fibNMinusTwo = 0;
    long long fibN = 0;
    for (unsigned i = 2; i < n; ++ i) {
        fibN = fibNMinusOne + fibNMinusTwo;
        fibNMinusTwo = fibNMinusOne;
        fibNMinusOne = fibN;
    }
    return fibN;
}

#pragma mark -- 5.实现一个函数，输入一个整数，输出二进制表示中1的个数。

int 

int main(int arg, const char * argv[])
{
    // 1.
    int a[] = {1, 2, 3, 8, 9, 4, 7, 10, 5, 6};
//    QuickSort1(a, 10, 1, 7);
    // 2.
    SortAges1(a, 10);
    for (int i = 0; i < sizeof(a)/sizeof(*a); ++ i) {
        cout << a[i] << endl;
    }
    // 3.
    int c[] = {1, 2, 0, 1, 1};
    cout << Min1(c, 5) <<endl;
    // 4.
    cout << Fibonacci1(10) << endl;
    return 0;
}



