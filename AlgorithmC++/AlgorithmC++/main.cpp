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

int NumberOfOne(int n) {
    int count = 0;
    while (n) {
        if (n & 1)
            count ++;
        n = n >> 1; // 右移运算，相当于 n = n / 2
    }
    return count;
}

int NumberOfOneU(int n)
{
    int count = 0;
    unsigned int flag = 1;
    while (flag) {
        if (n & flag)
            count ++;
        flag = flag << 1; // 左移运算
    }
    return count;
}

int NumberOfOneT(int n)
{
    int count = 0;
    while (n) {
        ++ count;
        n = (n - 1) & n;
    }
    return count;
}

#pragma mark -- 6.求整数的次方

double PowerWithUnsignedExponent1(double base, unsigned int exponent)
{
    if (exponent == 0) return 1;
    if (exponent == 1) return base;
    
    double result = PowerWithUnsignedExponent1(base, exponent >> 1);
    result *= result;
    if ((exponent & 0x1) == 1) // 用位与运算符代替了求余运算符(%)来判断一个数是奇数还是偶数。
        result *= base;
    return result;
}

bool g_InvalidInput = false;

bool equal1(double num1, double num2)
{
    if (num1 - num2 > - 0.0000001 && num1 - num2 < 0.0000001)
        return true;
    else
        return false;
}

double PowerWithUnsignedExponent2(double base, unsigned int exponent)
{
    double result = 1;
    for (int i = 0; i <= exponent; ++ i)
        result *= base;
    return result;
}

double Power1(double base, int exponent)
{
    g_InvalidInput = false;
    if (equal1(base, 0.0) && exponent < 0) {
        g_InvalidInput = true;
        return 0.0;
    }
    
    unsigned int absExponent = (unsigned int)exponent;
    if (exponent < 0) absExponent = (unsigned int)(-exponent);
    
    double result = PowerWithUnsignedExponent2(base, absExponent);
    if (exponent < 0) result = 1.0 / result;
    return result;
}


#pragma mark -- 7.打印1到最大的n位数
// a.未考虑n为大数。
void Print1ToMaxOfDigits_1A(int n)
{
    int number = 1;
    int i = 0;
    while (i ++ < n)
        number *= 10;
    for (i = 1; i < number; ++ i) {
        printf("%d\t", i);
    }
}

// b.使用字符串表示大数,最直观的方法就是字符串里每个字符都是‘0’到‘9’之间的某一个字符。
void PrintNumber_1B(char* number)
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

// Increment_1B实现在表示数字的字符串number上增加1（模拟整数的加法），使用PrintNumber_1B打印出来。
bool Increment_1B(char* number) // 实现了用O(1)时间判断是不是已经达到了最大的n位数。
{
    bool isOverflow = false;
    int nTakeOver = 0;
    int nLength = (int)strlen(number);
    for (int i = nLength - 1; i >= 0; i --) {
        int nSum = number[i] - '0' + nTakeOver;
        if (i == nLength - 1)
            nSum ++;
        
        if (nSum >= 10)
        {
            if (i == 0)
                isOverflow = true;
            else
            {
                nSum -= 10;
                nTakeOver = 1;
                number[i] = '0' + nSum;
            }
        }else {
            number[i] = '0' + nSum;
            break;
        }
    }
    return isOverflow;
}

void Print1ToMaxOfDigits_1B(int n)
{
    if (n <= 0) return;
    char* number =  new char[n + 1];
    // memset 把字符串数字的前n个字符设置为为‘0’。
    memset(number, '0', n);
    number[n] = '\0';
    
    while (!Increment_1B(number)) {
        PrintNumber_1B(number);
    }
    
    delete []number;
}

// c.转换成数字排列的问题，使用递归
void Print1ToMaxOfDigitsRecursively_1(char* number, int length, int index)
{
    if (index == length - 1)
    {
        PrintNumber_1B(number);
        return;
    }
    for (int i = 0; i < 10; ++ i) {
        number[index + 1] = i + '0';
        Print1ToMaxOfDigitsRecursively_1(number, length, index + 1);
    }
}

void Print1ToMaxOfDigits_1C(int n)
{
    if (n <= 0) return;
    
    char* number = new char[n + 1];
    number[n] = '\0';
    
    for (int i = 0; i < 10; ++ i) {
        number[0] = i + '0';
        Print1ToMaxOfDigitsRecursively_1(number, n, 0);
    }
    delete []number;
    
}

#pragma mark -- 8.在O(1)的时间删除结点
struct ListNode {
    int         m_value;
    ListNode*   m_pNext;
};

// 时间复杂度是[(n-1)*O(1) + O(n)]/n = O(1)
void DeleteNode_A(ListNode** pListHead, ListNode* pToBeDeleted)
{
    if (!pListHead || !pToBeDeleted) return;
    
    // 要删除的结点不是尾结点（把要删除的结点i的下一个结点j的值复制到i上，然后把i指向j的下一个结点，再删除j，即相当于删除i）。
    if (pToBeDeleted->m_pNext != NULL) {
        ListNode* pNext = pToBeDeleted->m_pNext;
        pToBeDeleted->m_value = pNext->m_value;
        pToBeDeleted->m_pNext = pNext->m_pNext;
        
        delete pNext;
        pNext = NULL;
    }
    // 链表只有一个结点，删除头结点（也是尾结点）
    else if (*pListHead == pToBeDeleted)
    {
        delete pToBeDeleted;
        pToBeDeleted = NULL;
        *pListHead = NULL;
    }
    // 链表中有多个结点，删除尾结点
    else{
        ListNode* pNode = *pListHead;
        while (pNode->m_pNext != pToBeDeleted) {
            pNode = pNode->m_pNext;
        }
        pNode->m_pNext = NULL;
        delete pToBeDeleted;
        pToBeDeleted = NULL;
    }
}

#pragma mark -- 9.调整数组顺序使奇数位于偶数前面

/**
 维护两个指针，第一个指针初始化时指向数组的第一个数字，它只向后移动。第二个指针初始化时指向数组的最后一个数字，它只向前移动。在两个指针相遇之前，第一个指针总是位于第二个指针之前。如果第一个指针指向的数字是偶数，而第二个指针指向的数字是奇数，则交换。
 */
void ReorderOddEven_A(int* pData, unsigned int length)
{
    if (pData == NULL || length == 0) return;
    
    int *pBegin = pData;
    int *pEnd = pData + length - 1;
    
    while (pBegin < pEnd) {
        // 向后移动pBegin，直到它指向偶数
        while (pBegin < pEnd && (*pBegin & 0x1) != 0)
            pBegin ++;
        // 向前移动pEnd，直到它指向奇数
        while (pBegin < pEnd && (*pEnd & 0x1) == 0)
            pEnd --;
        if (pBegin < pEnd) {
            int temp = *pBegin;
            *pBegin = *pEnd;
            *pEnd = temp;
        }
    }
}

bool isEven(int n)
{
    return (n & 1) == 0;
}

void Reorder_B(int* pData, unsigned int length, bool (*func)(int))
{
    if (pData == NULL || length <= 0) return;
    
    int *pBegin = pData;
    int *pEnd = pData + length - 1;
    
    while (pBegin < pEnd) {
        while (pBegin < pEnd && !func(*pBegin))
            pBegin ++;
        while (pBegin < pEnd && func(*pEnd))
            pEnd --;
        if (pBegin < pEnd) {
            int temp = *pBegin;
            *pBegin = *pEnd;
            *pEnd = temp;
        }
    }
}

void ReorderOddEven_B(int* pData, unsigned int length)
{
    Reorder_B(pData, length, isEven);
}

#pragma mark -- 10.求链表的倒数第k个结点

struct ListNode10 {
    int          m_value;
    ListNode10*  m_pNext;
};


int main(int arg, const char * argv[])
{
//    // 1.
//    int a[] = {1, 2, 3, 8, 9, 4, 7, 10, 5, 6};
////    QuickSort1(a, 10, 1, 7);
//    // 2.
//    SortAges1(a, 10);
//    for (int i = 0; i < sizeof(a)/sizeof(*a); ++ i) {
//        cout << a[i] << endl;
//    }
//    // 3.
//    int c[] = {1, 2, 0, 1, 1};
//    cout << Min1(c, 5) <<endl;
//    // 4.
//    cout << Fibonacci1(10) << endl;
//    return 0;
    // 5.
//    cout << NumberOfOne(10) << endl;
    // 6.
//    cout << PowerWithUnsignedExponent1(10, 4) << endl;
    // 7.
//    Print1ToMaxOfDigits_1A(2);
//    Print1ToMaxOfDigits_1B(2);
//    Print1ToMaxOfDigits_1C(2);
    // 9.
    int a[] = {1, 2, 3, 4, 5,  6, 7, 8};
    ReorderOddEven_A(a, 8);
    for (int i = 0; i < sizeof(a)/sizeof(*a); ++ i) {
        cout << a[i] << endl;
    }
}



