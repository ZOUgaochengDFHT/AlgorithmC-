//
//  CStack.cpp
//  AlgorithmC++
//
//  Created by GaoCheng.Zou on 2017/6/26.
//  Copyright © 2017年 Minxin. All rights reserved.
//

#include "CStack.hpp"
#include <queue>

#pragma mark - 使用队列实现栈。


using namespace std;

template <typename T>
class CStack {
    
public:
    CStack(void);
    ~CStack(void);
    void appendTail(const T &node);
    T deleteHead();
private:
    queue<T> queue1;
    queue<T> queue2;
};

template <typename T>
void CStack<T>::appendTail(const T &element)
{
    queue1.push(element);
}

template <typename T>
T CStack<T>::deleteHead() {
    if (queue2.size() <= 0) {
        if (queue1.size() > 0) {
            T &data = queue1.top();
            queue1.pop();
            queue2.push(data);
        }
    }
    if (queue2.size() == 0) {
        throw out_of_range("stack in empty");
    }
    T head = queue2.top();
    return head;
}


#pragma mark - 定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的min函数。在该栈中，调用push、min和pop的时间复杂度都是O(1)。

#include <stack>
#include <assert.h>

template <typename T>
class StackWithMin {
public:
    StackWithMin(void){};
    virtual ~StackWithMin(void){};
    
    T& top(void);
    const T& top(void) const;
    
    void push(const T& value);
    void pop(void);
    
    const T& min(void) const;
    
    bool empty() const;
    size_t size() const;
private:
    stack<T> m_data;
    stack<T> m_min;
};


template <typename T>
void StackWithMin<T>::push(const T& value) {
    m_data.push(value);
    
    if (m_min.size() == 0 || value < m_min.top())
        m_min.push(value);
    else
        m_min.push(m_min.top());
}

template <typename T>
void StackWithMin<T>::pop() {
    assert(m_data.size() > 0 && m_data.size() > 0);
    m_data.pop();
    m_min.pop();
}

template <typename T>
const T& StackWithMin<T>::min() const {
    assert(m_data.size() > 0 && m_min.size() > 0);
    return m_min.top();
}

template <typename T>
T& StackWithMin<T>::top()
{
    return m_data.top();
}

template <typename T>
const T& StackWithMin<T>::top() const
{
    return m_data.top();
}

template <typename T>
bool StackWithMin<T>::empty() const
{
    return m_data.empty();
}

template <typename T>
size_t StackWithMin<T>::size() const
{
    return m_data.size();
}

#include <stack>

#pragma mark - 输入两个整数序列，第一个序列表示栈的压顺序，判断第二个序列是否为该栈的弹出序列。

/**
 若两个指针指向同一数组的元素，，则两个指针变量的值之差是两个指针之间的元素。
 */
bool IsPopOrder(const int* pPush, const int* pPop, int nLength)
{
    bool bPossible = false;
    if (pPush != NULL && pPop != NULL && nLength > 0)
    {
        const int* pNextPush = pPush;
        const int* pNextPop = pPop;
        
        stack<int> stackData;
        while (pNextPop - pPop < nLength) {
            while (stackData.empty() || stackData.top() != *pNextPop) {
                if (pNextPush - pPush == nLength)
                    break;
                stackData.push(*pNextPush);
                pNextPush ++;
            }
            if (stackData.top() != *pNextPop)
                break;
            
            stackData.pop();
            pNextPop ++;
        }
        if (stackData.empty() && pNextPop - pPop == nLength)
            bPossible = true;
    }
    return bPossible;
}

