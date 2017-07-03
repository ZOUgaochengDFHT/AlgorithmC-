//
//  CQueue.cpp
//  AlgorithmC++
//
//  Created by GaoCheng.Zou on 2017/6/26.
//  Copyright © 2017年 Minxin. All rights reserved.
//

#include "CQueue.hpp"
#include <stack>


using namespace std;

template <typename T>
class CQueue {
public:
    CQueue(void);
    ~CQueue(void);
    
    void appendTail(const T& node);
    T deleteHead();
    T deleteHead1();
private:
    stack<T> stack1;
    stack<T> stack2;
};

template <typename T>
void CQueue<T>::appendTail(const T& element) {
    stack1.push(element);
}

template <typename T>
T CQueue<T>::deleteHead() {
    if (stack2.size() <= 0) {
        while (stack1.size() > 0) {
            T& data = stack1.top();
            stack1.pop();
            stack2.push(data);
        }
    }
    if (stack2.size() == 0) {
        throw out_of_range("queue in empty");
    }
    T head = stack2.top();
    stack2.pop();
    return head;
}

template <typename T>
T CQueue<T>::deleteHead1() {
    if (stack2.size() <= 0) {
        if (stack1.size() > 0) {
            T &data = stack1.top();
            stack1.pop();
            stack2.push(data);
        }
    }
    if (stack2.size() == 0) {
        throw out_of_range("queue in empty");
    }
    T head = stack2.top();
    stack2.pop();
    return head;
}
