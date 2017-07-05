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


#pragma mark -- 26.复杂链表的复制

struct ComplexListNode {
    int               m_nValue;
    ComplexListNode*  m_pNext;
    ComplexListNode*  m_pSibling; // 指向链表中的任意结点或者NULL
};


/**
 第一步根据原始链表的结点N创建对应的N‘

 @param pHead 头结点
 */
void CloneNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while (pNode != NULL) {
        ComplexListNode *pCloned = new ComplexListNode();
        pCloned->m_nValue = pNode->m_nValue;
        pCloned->m_pNext = pNode->m_pNext;
        pCloned->m_pSibling = NULL;
        
        pNode->m_pNext = pCloned;
        pNode = pCloned->m_pNext;
    }
}


/**
 第二步设置复制出来的m_pSibling结点

 @param pHead 头结点
 */
void ConnectSiblingNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while (pNode != NULL) {
        ComplexListNode* pCloned = pNode->m_pNext;
        if (pNode->m_pSibling != NULL) pCloned->m_pSibling = pNode->m_pSibling->m_pNext;
        pNode = pCloned->m_pNext;
    }
}


/**
 第三步把这个长链表拆分成两个链表：把奇数位置的结点用m_pNext链接起来就是原始表，把偶数位置的结点用m_pNext链接起来就是复制链表。

 @param pHead 头结点
 @return 复制结点
 */
ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    ComplexListNode* pClonedHead = NULL;
    ComplexListNode* pClonedNode = NULL;
    
    if (pNode != NULL) {
        pClonedHead = pClonedNode = pNode->m_pNext;
        pNode->m_pNext = pClonedNode->m_pNext;
        pNode = pNode->m_pNext;
    }
    
    while (pNode != NULL) {
        pClonedNode->m_pNext = pNode->m_pNext;
        pClonedNode = pClonedNode->m_pNext;
        pNode->m_pNext = pClonedNode->m_pNext;
        pNode = pNode->m_pNext;
    }
    return pClonedNode;
}

ComplexListNode* Clone(ComplexListNode* pHead)
{
    CloneNodes(pHead);
    ConnectSiblingNodes(pHead);
    return ReconnectNodes(pHead);
}

#pragma mark -- 27.二叉搜索树转双向链表

struct BinaryTreeNode {
    int              m_nValue;
    BinaryTreeNode*  m_pLeft;
    BinaryTreeNode*  m_pRight;
};


/**
 递归
 */
void ConvertNode(BinaryTreeNode* pNode, BinaryTreeNode** pLastNodeInList)
{
    if (pNode == NULL) return;
    BinaryTreeNode* pCurrent = pNode;
    if (pCurrent->m_pLeft != NULL) ConvertNode(pCurrent->m_pLeft, pLastNodeInList);
    pCurrent->m_pLeft = *pLastNodeInList;
    if (pCurrent->m_pRight != NULL) ConvertNode(pCurrent->m_pRight, pLastNodeInList);
}

BinaryTreeNode* Convert(BinaryTreeNode* pRootOfTree)
{
    BinaryTreeNode* pLastNodeInList = NULL;
    ConvertNode(pRootOfTree, &pLastNodeInList);
    
    // pLastNodeInList指向双向链表的尾结点，我们需要返回头结点
    BinaryTreeNode* pHeadOfList = pLastNodeInList;
    while (pHeadOfList != NULL && pHeadOfList->m_pLeft != NULL) pHeadOfList = pHeadOfList->m_pLeft;
    return pHeadOfList;
}

#pragma mark -- 28.字符串的排列  
//http://blog.csdn.net/hackbuteer1/article/details/7462447

#include <assert.h>
/**
 在每一次递归的时候，从pBegin向后扫描每一个字符（即指针pCh指向的字符）。在交换pBegin和pCh指向的字符后，再对pBegin后面的字符串递归地做排列操作，直至PBegin指向字符串的末尾。

 @param pStr 指针pStr指向整个字符串的第一个字符
 @param pBegin 指针pBegin指向当前做操作的字符串的第一个字符
 */
void Permutation(char* pStr, char* pBegin)
{
    if (pStr == NULL) return;
    if (*pBegin == '\0') {
        printf("%s\n", pStr);
    }else {
        for (char* pCh = pBegin; *pCh != '\0'; ++ pCh) {
            char temp = *pCh;
            *pCh = *pBegin;
            *pBegin = temp;
            
            Permutation(pStr, pBegin + 1);
            
            temp = *pCh;
            *pCh = *pBegin;
            *pBegin = temp;
        }
    }
}


/**
 @param pStr 指针pStr指向整个字符串的第一个字符
 @param k k表示当前选取到第几个数
 @param m m表示共有多少个数
 */
void Permutation_A(char* pStr, int k, int m)
{
    assert(pStr != NULL);
    if (k == m) {
        static int num = 1; //局部静态变量，用来统计全排列的个数
        printf("第%d个排列\t%s\n", num ++, pStr);
    } else {
        for (int i = k; i <= m; i ++) {
            char temp = *(pStr + k);
            *(pStr + k) = *(pStr + i);
            *(pStr + i) = temp;
            
            Permutation_A(pStr, k + 1, m);
            
            temp = *(pStr + k);
            *(pStr + k) = *(pStr + i);
            *(pStr + i) = temp;
        }
    }
}

#pragma mark -- 字符串的组合

#include <vector>
#include <assert.h>

void Combination(char* string, int number, vector<char>& result);

void Combination(char* string)
{
    assert(string != NULL);
    vector<char> result;
    
    for (int i = 1; i <= strlen(string); ++ i) Combination(string, i, result);
}

void Combination(char* string, int number, vector<char>& result)
{
    assert(string != NULL);
    if (number == 0) {
        static int num = 1;
        printf("第%d个组合\t", num++);
        
        vector<char>::iterator iter = result.begin();
        for (; iter != result.end(); ++ iter) printf("%c", *iter);
        printf("\n");
        return;
    }
    if (*string == '\0') return;
    
    result.push_back(*string);
    Combination(string + 1, number - 1, result);
    result.pop_back();
    Combination(string + 1, number, result);
}

#pragma mark -- 用位运算来实现求字符串的组合

#include <iostream>
using namespace std;

int a[] = {1,3,5,4,6};
char str[] = "abc";

void print_subset(int n , int s)
{
    printf("{");
    for(int i = 0 ; i < n ; ++ i)
    {
        if(s & (1 << i))         // 判断s的二进制中哪些位为1，即代表取某一位
            printf("%c", str[i]);   //或者a[i]
    }
    printf("}\n");
}

void subset(int n)
{
    for(int i = 0 ; i < (1<<n) ; ++ i)
    {
        print_subset(n, i);
    }
}

#pragma mark -- 字符串全排列拓展----八皇后问题

/**
 由于八个皇后的任意两个不能处在同一行，那么这肯定是每一个皇后占据一行。于是我们可以定义一个数组columnIndex[8]，数组中第i个数字表示位于第i行的皇后的列号。先把columnIndex的八个数字分别用0-7初始化，接下来我们要做的事情就是对数组columnIndex做全排列。由于我们是用不同的数字初始化数组中的数字，因此任意两个皇后肯定不同列。我们只需要判断得到的每一个排列对应的八个皇后是不是在同一对角斜线上，也就是数组的两个下标i和j，是不是i-j==columnIndex[i]-Column[j]或者j-i==columnIndex[i]-columnIndex[j]。
 */

#include<iostream>
using namespace std;

int g_number = 0;
void Permutation(int * , int  , int );
void Print(int * , int );

void EightQueen( )
{
    const int queens = 8;
    int columnIndex[queens];
    for(int i = 0; i < queens; ++ i)
        columnIndex[i] = i;    //初始化
    Permutation(columnIndex , queens , 0);
}

bool Check(int columnIndex[] , int length)
{
    int i,j;
    for(i = 0 ; i < length; ++i)
    {
        for(j = i + 1 ; j < length; ++j)
        {
            if( i - j == columnIndex[i] - columnIndex[j] || j - i == columnIndex[i] - columnIndex[j])   //在正、副对角线上
                return false;
        }
    }
    return true;
}
void Permutation(int columnIndex[] , int length , int index)
{
    if(index == length)
    {
        if( Check(columnIndex , length) )   //检测棋盘当前的状态是否合法
        {
            ++ g_number;
            Print(columnIndex , length);
        }
    }
    else
    {
        for(int i = index ; i < length; ++i)   //全排列
        {
            swap(columnIndex[index] , columnIndex[i]);
            Permutation(columnIndex , length , index + 1);
            swap(columnIndex[index] , columnIndex[i]);
        }
    }
}

void Print(int columnIndex[] , int length)
{
    printf("%d\n",g_number);
    for(int i = 0; i < length; ++ i)
        printf("%d ",columnIndex[i]);
    printf("\n");
}

#pragma mark -- 输入两个整数n和m，从数列1,2,3...n中随意取几个数，使其和等于m，要求列出所有的组合。

#include <iostream>
#include <list>
using namespace std;


list<int> list1;

void find_factor(int sum,int n)
{
    //递归出口
    if(n <= 0 || sum <= 0)
        return;
    //输出找到的数
    if(sum == n)
    {
        list1.reverse();
        for(list<int>::iterator iter = list1.begin(); iter != list1.end(); iter++)
            cout<< *iter <<"+";
        cout << n << endl;
        list1.reverse();
    }
    list1.push_front(n);
    find_factor(sum-n,n-1);//n放在里面
    list1.pop_front();
    find_factor(sum,n-1);//n不放在里面
}


#pragma mark -- 29.数组中出现次数超过一半的数字

bool g_bInputInvalid = false;

bool CheckInvalidArray(int*, int);
bool CheckMoreThanHalf(int*, int, int);

// 1.基于Partition函数时间效率为O(n)的算法
int MoreThanHalfNum(int* numbers, int length)
{
    if (CheckInvalidArray(numbers, length)) return 0;
    
    int middle = length >> 1;
    int start = 0;
    int end = length - 1;
    int index = Partition1(numbers, length, start, end);
    while (index != middle) {
        if (index > middle) {
            end = index - 1;
        }else {
            start = index + 1;
        }
        index = Partition1(numbers, length, start, end);
    }
    
    int result = numbers[middle];
    if (!CheckMoreThanHalf(numbers, length, result)) result = 0;
    return result;
}

// 2.根据数组特点找出时间效率为O(n)的算法
int MoreThanHalfNum_A(int* numbers, int length)
{
    if (CheckInvalidArray(numbers, length)) return 0;
    
    int result = numbers[0];
    int times = 1;
    for (int i = 0; i < length; ++ i) {
        if (times == 0) {
            result = numbers[i];
            times = 1;
        }else if (numbers[i] == result)
            times ++;
        else
            times --;
    }
    if (!CheckMoreThanHalf(numbers, length, result)) result = 0;
    return result;
}

// 判断输入是否有效
bool CheckInvalidArray(int* numbers, int length)
{
    g_InvalidInput = false;
    if (numbers == NULL || length <= 0) g_bInputInvalid = true;
    return g_bInputInvalid;
}

// 判断输入的数组是否满足要求
bool CheckMoreThanHalf(int* numbers, int length, int number)
{
    int times = 0;
    for (int i = 0; i < length; ++ i) {
        if (numbers[i] == number) times++;
    }
    
    bool isMoreThanHalf = true;
    if (times * 2 <= length)
    {
        g_bInputInvalid = true;
        isMoreThanHalf = false;
    }
    return isMoreThanHalf;
}

#pragma mark -- 30.最小的k个数

// 1.基于Partition函数的时间效率为O(n)的算法，只有当可以修改输入的数组时可用

void GetLeastNumbers(int* input, int n, int k)
{
    if (input == NULL || k > n || n <= 0 || k <= 0) return;
    
    int start = 0;
    int end = n - 1;
    int index = Partition1(input, n, start, end);
    while (index != k - 1) {
        if (index > k - 1)
            end = index - 1;
        else
            start = index + 1;
        index = Partition1(input, n, start, end);
    }
    for (int i = 0; i < k; ++ i) {
        cout << input[i] << endl;
    }
}

// 2.基于堆和红黑树的适合海量数据的时间效率为O(nlogk)的算法。红黑树的删除、查找和插入操作都只需要O(logk)时间。
#include <set>

typedef multiset<int, greater<int>>            intset;
typedef multiset<int, greater<int>> ::iterator setIterator;

void GetLeastNumbers_A(const vector<int>& data, intset& leastNumbers, int k)
{
    leastNumbers.clear();
    if (data.size() < k || k < 1) return;
    
    vector<int>::const_iterator iter = data.begin();
    for (; iter != data.end(); ++ iter) {
        if (leastNumbers.size() < k)
            leastNumbers.insert(*iter);
        else
        {
            setIterator iterGreatest = leastNumbers.begin();
            if (*iter < *leastNumbers.begin())
            {
                leastNumbers.erase(iterGreatest);
                leastNumbers.insert(*iter);
            }
        }
    }
}

#pragma mark -- 31.连续子数组的最大和



int main(int arg, const char * argv[])
{
    // 1.
//    int a[] = {1, 2, 3, 8, 9, 4, 7, 10, 5, 6};
////    QuickSort1(a, 10, 1, 7);
    // 2.
//    SortAges1(a, 10);
//    for (int i = 0; i < sizeof(a)/sizeof(*a); ++ i) {
//        cout << a[i] << endl;
//    }
    // 3.
//    int c[] = {1, 2, 0, 1, 1};
//    cout << Min1(c, 5) <<endl;
    // 4.
//    cout << Fibonacci1(10) << endl;
    // 5.
//    cout << NumberOfOne(10) << endl;
    // 6.
//    cout << PowerWithUnsignedExponent1(10, 4) << endl;
    // 7.
//    Print1ToMaxOfDigits_1A(2);
//    Print1ToMaxOfDigits_1B(2);
//    Print1ToMaxOfDigits_1C(2);
    // 9.
//    int a[] = {1, 2, 3, 4, 5,  6, 7, 8};
//    ReorderOddEven_A(a, 8);
//    for (int i = 0; i < sizeof(a)/sizeof(*a); ++ i) {
//        cout << a[i] << endl;
//    }
    // 28.
//    char a[] = "abc";
//    Combination(a);
//    subset(5);
//    EightQueen();
//    int sum,n;
//    cin>>sum>>n;
//    cout<<"所有可能的序列，如下："<<endl;
//    find_factor(sum,n);
    // 29.
//    int number[] = {1,2,3,2,2,2,5,4,2};
//    cout << MoreThanHalfNum(number, 9) << endl;
//    cout << MoreThanHalfNum_A(number, 9) << endl;
    // 30.
    int number[] = {1,2,3,2,2,2,5,4,2};
    GetLeastNumbers(number, 9, 5);
    return 0;
}



