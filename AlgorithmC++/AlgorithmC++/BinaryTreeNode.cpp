//
//  BinaryTreeNode.cpp
//  AlgorithmC++
//
//  Created by GaoCheng.Zou on 2017/6/24.
//  Copyright © 2017年 Minxin. All rights reserved.
//

#include "BinaryTreeNode.hpp"
#include <stdexcept>


struct BinaryTreeNode {
    int               m_nValue;
    BinaryTreeNode*   m_pLeft;
    BinaryTreeNode*   m_pRight;
};




/**
 递归构建左子树和右子树
 
 @param startPreorder 前序遍历数组
 @param endPreorder   数组长度
 @param startInorder  中序遍历数组
 @param endInorder    数组长度
 
 @return 根节点
 */
BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder)
{
    // 前序遍历的第一个数字就是根节点的值。
    int rootValue = startPreorder[0];
    BinaryTreeNode* root = new BinaryTreeNode();
    root->m_nValue = rootValue;
    root->m_pLeft = root->m_pRight = NULL;
    
    if (startPreorder == endPreorder) {
        if (startInorder == endInorder && *startPreorder == *startInorder) {
            printf("%d\n", root->m_nValue);
            return root;
        }else {
            throw std::invalid_argument("Invalid input.");
        }
    }
    
    // 在中序遍历中查找根节点的值
    int* rootInorder = startInorder;
    while (rootInorder <= endInorder && *rootInorder != rootValue)
        ++ rootInorder;
    
    if (rootInorder == endInorder && *rootInorder != rootValue)
        throw std::invalid_argument("Invalid input.");
    
    long leftLength = rootInorder - startInorder;
    int* leftPreorderEnd = startPreorder + leftLength;
    if (leftLength > 0) {
        // 构建左子树
        root->m_pLeft = ConstructCore(startPreorder + 1, leftPreorderEnd, startInorder, rootInorder - 1);
    }
    if (leftLength < endPreorder - startPreorder) {
        // 构建右子树
        root->m_pRight = ConstructCore(leftPreorderEnd + 1, endPreorder, rootInorder + 1, endInorder);
    }
    printf("%d\n", root->m_nValue);
    return root;
}


/**
 构建二叉树
 
 @param preorder 前序遍历数组
 @param inorder  中序遍历数组
 @param length   数组长度
 
 @return 根节点
 */
BinaryTreeNode* Construct(int* preorder, int* inorder, int length)
{
    if (preorder == NULL || inorder == NULL || length <= 0)
        return NULL;
    return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}



/**
 判断根节点和叶节点是都相同
 
 @param pRoot1 树1的根节点
 @param pRoot2 树2的根节点
 
 @return 树1是否包含树2
 */
bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    if (pRoot1 == NULL) return false;
    // 当树2为的头指针为NULL，树1肯定包含树2。
    // 多处判断指针是不是为NULL，这样做是为了避免试图访问空指针而造成崩溃。
    if (pRoot2 == NULL) return true;
    if (pRoot1->m_nValue != pRoot2->m_nValue) return false;
    return DoesTree1HaveTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) && DoesTree1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight);
}


/**
 当叶节点不相同时，递归遍历下一个叶节点
 
 @param pRoot1 pRoot1 树1的根节点
 @param pRoot2 pRoot2 树2的根节点
 
 @return  树1是否包含树2
 */
bool HasSubTree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    bool result = false;
    if (pRoot1 != NULL && pRoot2 != NULL) {
        if (pRoot1->m_nValue == pRoot2->m_nValue) result = DoesTree1HaveTree2(pRoot1, pRoot2);
        if (!result) result = HasSubTree(pRoot1->m_pLeft, pRoot2);
        if (!result) result = HasSubTree(pRoot1->m_pRight, pRoot2);
    }
    return result;
}



/**
 求二叉树的镜像
 
 @param pNode 树的头指针
 */
void MirrorRecursively(BinaryTreeNode* pNode)
{
    if (pNode == NULL) return;
    if (pNode->m_pLeft == NULL && pNode->m_pRight == NULL) return;
    BinaryTreeNode* pTemp = pNode->m_pLeft;
    pNode->m_pLeft = pNode->m_pRight;
    pNode->m_pRight = pTemp;
    if (pNode->m_pLeft) MirrorRecursively(pNode->m_pLeft);
    if (pNode->m_pRight) MirrorRecursively(pNode->m_pRight);
}


/**
 循环遍历求镜像，只要左右子节点不同时为NULL即可
 
 @param pNode 树的头指针
 */
void Mirror(BinaryTreeNode* pNode)
{
    if (pNode == NULL) return;
    while (!(pNode->m_pLeft == NULL && pNode->m_pRight == NULL)) {
        BinaryTreeNode* pTemp = pNode->m_pLeft;
        pNode->m_pLeft = pNode->m_pRight;
        pNode->m_pRight = pTemp;
    }
}

#include <deque>

/**
 从上到下打印二叉树

 @param pTreeRoot 根节点
 */
void PrintFromTopToBottom(BinaryTreeNode* pTreeRoot)
{
    //    while (!(pTreeRoot->m_pLeft == NULL && pTreeRoot->m_pRight == NULL)) {
    //        printf("%d", pTreeRoot->m_nValue);
    //        if (pTreeRoot->m_pLeft != NULL) PrintFromTopToBottom(pTreeRoot->m_pLeft);
    //        if (pTreeRoot->m_pRight != NULL) PrintFromTopToBottom(pTreeRoot->m_pRight);
    //    }
    
    if (pTreeRoot == NULL) return;
    
    std::deque<BinaryTreeNode*> dequeTreeNode;
    dequeTreeNode.push_back(pTreeRoot);
    
    while (dequeTreeNode.size()) {
        BinaryTreeNode* pNode = dequeTreeNode.front();
        
        printf("%d", pNode->m_nValue);
        
        if (pNode->m_pLeft)
            PrintFromTopToBottom(pTreeRoot->m_pLeft);
        if (pNode->m_pRight)
            PrintFromTopToBottom(pTreeRoot->m_pRight);
    }
}



// ====================测试代码====================

BinaryTreeNode* CreateBinaryTreeNode(int value)
{
    BinaryTreeNode* pNode = new BinaryTreeNode();
    pNode->m_nValue = value;
    pNode->m_pLeft = NULL;
    pNode->m_pRight = NULL;
    
    return pNode;
}

void ConnectTreeNodes(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight)
{
    if(pParent != NULL)
    {
        pParent->m_pLeft = pLeft;
        pParent->m_pRight = pRight;
    }
}

void PrintTreeNode(BinaryTreeNode* pNode)
{
    if(pNode != NULL)
    {
        printf("value of this node is: %d\n", pNode->m_nValue);
        
        if(pNode->m_pLeft != NULL)
            printf("value of its left child is: %d.\n", pNode->m_pLeft->m_nValue);
        else
            printf("left child is null.\n");
        
        if(pNode->m_pRight != NULL)
            printf("value of its right child is: %d.\n", pNode->m_pRight->m_nValue);
        else
            printf("right child is null.\n");
    }
    else
    {
        printf("this node is null.\n");
    }
    
    printf("\n");
}

void PrintTree(BinaryTreeNode* pRoot)
{
    PrintTreeNode(pRoot);
    
    if(pRoot != NULL)
    {
        if(pRoot->m_pLeft != NULL)
            PrintTree(pRoot->m_pLeft);
        
        if(pRoot->m_pRight != NULL)
            PrintTree(pRoot->m_pRight);
    }
}

void DestroyTree(BinaryTreeNode* pRoot)
{
    if(pRoot != NULL)
    {
        BinaryTreeNode* pLeft = pRoot->m_pLeft;
        BinaryTreeNode* pRight = pRoot->m_pRight;
        
        delete pRoot;
        pRoot = NULL;
        
        DestroyTree(pLeft);
        DestroyTree(pRight);
    }
}



void Test(char* testName, BinaryTreeNode* pRoot)
{
    if(testName != NULL)
        printf("%s begins: \n", testName);
    
    PrintTree(pRoot);
    
    printf("The nodes from top to bottom, from left to right are: \n");
    // 测试代码写在这里
    
    printf("\n\n");
}

//            10
//         /      \
//        6        14
//       /\        /\
//      4  8     12  16
void Test1()
{
    BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
    BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* pNode14 = CreateBinaryTreeNode(14);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
    BinaryTreeNode* pNode16 = CreateBinaryTreeNode(16);
    
    ConnectTreeNodes(pNode10, pNode6, pNode14);
    ConnectTreeNodes(pNode6, pNode4, pNode8);
    ConnectTreeNodes(pNode14, pNode12, pNode16);
    
    char str[] = "Test1";
    Test(str, pNode10);
    
    DestroyTree(pNode10);
}

//               5
//              /
//             4
//            /
//           3
//          /
//         2
//        /
//       1
void Test2()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
    
    ConnectTreeNodes(pNode5, pNode4, NULL);
    ConnectTreeNodes(pNode4, pNode3, NULL);
    ConnectTreeNodes(pNode3, pNode2, NULL);
    ConnectTreeNodes(pNode2, pNode1, NULL);
    
    char str[] = "Test2";
    Test(str, pNode5);
    
    DestroyTree(pNode5);
}

// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
void Test3()
{
    BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    
    ConnectTreeNodes(pNode1, NULL, pNode2);
    ConnectTreeNodes(pNode2, NULL, pNode3);
    ConnectTreeNodes(pNode3, NULL, pNode4);
    ConnectTreeNodes(pNode4, NULL, pNode5);
    
    char str[] = "Test3";
    Test(str, pNode1);
    
    DestroyTree(pNode1);
}

// 树中只有1个结点
void Test4()
{
    BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
    char str[] = "Test4";
    Test(str, pNode1);
    
    DestroyTree(pNode1);
}

// 树中没有结点
void Test5()
{
    char str[] = "Test5";
    Test(str, NULL);
}

