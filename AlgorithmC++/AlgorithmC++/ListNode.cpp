//
//  ListNode.cpp
//  AlgorithmC++
//
//  Created by GaoCheng.Zou on 2017/6/23.
//  Copyright © 2017年 Minxin. All rights reserved.
//

#include "ListNode.hpp"
#include <stack>

/**
 链表结点
 */
struct ListNode {
    int        m_nValue;
    ListNode*  m_pNext;
};



/**
 往链表的末尾添加一个节点
 
 @param pHead 指向指针的指针，需要插入的结点
 @param value 结点的值
 */
void AddToTail(ListNode** pHead, int value)
{
    ListNode* pNew = new ListNode();
    pNew->m_nValue = value;
    pNew->m_pNext = NULL;
    if (*pHead == NULL) {
        *pHead = pNew;
    }else
    {
        ListNode* pNode = *pHead;
        while (pNode->m_pNext != NULL)
            pNode = pNode->m_pNext;
        pNode->m_pNext = pNew;
    }
}


/**
 删除结点
 
 @param pHead 要删除的结点
 @param value 要删除的结点的值
 */
void RemoveNode(ListNode** pHead, int value)
{
    if (pHead == NULL || *pHead == NULL)
        return;
    
    ListNode* pToBeDeleted = NULL;
    if ((*pHead)->m_nValue == value) {
        pToBeDeleted = *pHead;
        *pHead = (*pHead)->m_pNext;
    }else {
        ListNode* pNode = *pHead;
        while (pNode->m_pNext != NULL && pNode->m_pNext->m_nValue != value) {
            pNode = pNode->m_pNext;
        }
        if (pNode->m_pNext != NULL && pNode->m_pNext->m_nValue == value) {
            pToBeDeleted = pNode->m_pNext;
            pNode->m_pNext = pNode->m_pNext->m_pNext;
        }
    }
    if (pToBeDeleted != NULL) {
        delete pToBeDeleted;
        pToBeDeleted = NULL;
    }
}



/**
 反向输出链表
 
 @param pHead 链表头结点
 */
void PrintListReversingly_Iteratively(ListNode* pHead)
{
    std::stack<ListNode *>nodes;
    
    ListNode* pNode = pHead;
    
    while (pNode != NULL) {
        nodes.push(pNode);
        pNode = pNode->m_pNext;
    }
    
    while (!nodes.empty()) {
        pNode = nodes.top();
        printf("%d\t", pNode->m_nValue);
        nodes.pop();
        printf("%lu", nodes.size());
    }
}



/**
 求链表的倒数第k个结点
 
 @param pListHead 头指针的指针
 @param k         数目
 
 @return 倒数第k个结点
 */
ListNode* FindKthToTail(ListNode** pListHead, unsigned int k)
{
    // 当k等于0时
    if (k == 0) return NULL;
    ListNode *pAhead = *pListHead;
    if (pAhead->m_pNext == NULL) return NULL;
    ListNode *pBehind = NULL;
    // 先循环遍历到链表k-1的位置
    for (unsigned int i = 0; i < k - 1; ++ i) {
        if (pAhead->m_pNext != NULL) {
            pAhead = pAhead->m_pNext;
        }else {
            // 当链表的结点数小于k
            return NULL;
        }
    }
    // 继而给pBehind赋初值，pAhead和pBehind相差k-1
    pBehind = *pListHead;
    // 继续循环遍历，直到pAhead变成尾指针，即pAhead = NULL，返回pBehind即为所求值
    while (pAhead->m_pNext != NULL) {
        pAhead = pAhead->m_pNext;
        pBehind = pBehind->m_pNext;
    }
    return pBehind;
}


/**
 求链表的中间结点
 
 @param pListHead 头指针的指针
 
 @return 中间结点
 */
ListNode* FindMidNode(ListNode** pListHead)
{
    ListNode *pFast = *pListHead;
    if (pFast->m_pNext == NULL) return NULL;
    ListNode *pSlow = *pListHead;
    while (pFast != NULL && pFast->m_pNext != NULL) {
        pFast = pFast->m_pNext->m_pNext;
        pSlow = pSlow->m_pNext;
    }
    return pSlow;
}


/**
 判断链表是否有环
 
 @param pListHead 头指针的指针
 
 @return 是否有环
 */
bool isAnnularLinkedList(ListNode **pListHead)
{
    bool isAnnular = false;
    ListNode* pFast = *pListHead;
    if (pFast->m_pNext == NULL) return isAnnular;
    ListNode* pSlow = *pListHead;
    while (pFast != NULL && pFast->m_pNext != NULL) {
        pFast = pFast->m_pNext->m_pNext;
        pSlow = pSlow->m_pNext;
        if (pFast == pSlow) {
            isAnnular = true;
            break;
        }
    }
    return isAnnular;
}


/**
 单链表反转之循环遍历
 
 @param pListHead 头指针
 
 @return 尾指针
 */
ListNode* ReverseList(ListNode** pListHead)
{
    ListNode* pReversedHead = NULL;
    ListNode* pNode = *pListHead;
    // 链表只有一个结点
    if (pNode->m_pNext == NULL) return *pListHead;
    ListNode* pPrev = NULL;
    while (pNode != NULL) {
        ListNode* pNext = pNode->m_pNext;
        // 发现尾指针
        if (pNext == NULL) pReversedHead = pNode;
        pNode->m_pNext = pPrev;
        pPrev = pNode;
        pNode = pNext;
    }
    return pReversedHead;
}


/**
 单链表反转之递归遍历
 
 @param pListHead 头指针
 
 @return 尾指针
 */
ListNode* ReverseList_Recursive(ListNode *pListHead)
{
    if (pListHead == NULL || pListHead->m_pNext == NULL) return pListHead;
    ListNode *pNode = ReverseList_Recursive(pListHead->m_pNext);
    pListHead->m_pNext->m_pNext = pListHead;
    pListHead->m_pNext = NULL;
    return pNode;
}



/**
 单链表删除结点
 
 @param pListHead    头指针、指向指针的指针
 @param pToBeDeleted 要删除的结点
 */
// 时间复杂度是[(n-1)*O(1) + O(n)]/n，结果还是O(1)
void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted)
{
    if (!pListHead || !pToBeDeleted) return;
    
    // 要删除的结点不是尾结点
    if (pToBeDeleted->m_pNext != NULL) {
        // 把结点pToBeDeleted->m_pNext的内容复制到结点pToBeDeleted，接下来再把结点pToBeDeleted->m_pNext的m_pNext指向pToBeDeleted的下一个结点之后删除pToBeDeleted->m_pNext。这种方法不用遍历链表上的节点pToBeDeleted之前的结点。所以算法的时间复杂度为O(1)。
        ListNode *pNext = pToBeDeleted->m_pNext;
        pToBeDeleted->m_nValue = pNext->m_nValue;
        pToBeDeleted->m_pNext = pNext->m_pNext;
        
        delete pNext;
        pNext = NULL;
    }
    // 链表只有一个结点，删除头结点（也是尾结点）
    else if (*pListHead == pToBeDeleted) {
        delete pToBeDeleted;
        pToBeDeleted = NULL;
        *pListHead = NULL;
    }
    // 链表有多个结点，删除尾结点
    else {
        ListNode *pNode = *pListHead;
        // 从头到尾遍历直到找到尾结点
        while (pNode->m_pNext != pToBeDeleted) {
            pNode = pNode->m_pNext;
        }
        pNode->m_pNext = NULL;
        delete pToBeDeleted;
        pToBeDeleted = NULL;
    }
}


/**
 合并俩个排序链表
 
 @param pListHead1 链表一的头指针
 @param pListHead2 链表二的头指针
 */
ListNode* MergeList(ListNode *pListHead1, ListNode *pListHead2)
{
    if (pListHead1 == NULL) return pListHead2;
    if (pListHead2 == NULL) return pListHead1;
    ListNode *pMergeNode = NULL;
    if (pListHead1->m_nValue < pListHead2->m_nValue) {
        pMergeNode = pListHead1;
        pMergeNode ->m_pNext = MergeList(pListHead1->m_pNext, pListHead2);
    }else {
        pMergeNode = pListHead2;
        pMergeNode ->m_pNext = MergeList(pListHead2->m_pNext, pListHead1);
    }
    return pMergeNode;
}
