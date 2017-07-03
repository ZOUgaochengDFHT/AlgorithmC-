//
//  Matrix.cpp
//  AlgorithmC++
//
//  Created by GaoCheng.Zou on 2017/6/28.
//  Copyright © 2017年 Minxin. All rights reserved.
//

#include "Matrix.hpp"

/**
 二维数组中查找
 
 @param matrix  二维数组
 @param rows    行数
 @param columns 列数
 @param number  需要查找的数
 
 @return 是否查到
 */
bool Find(int* matrix, int rows, int columns, int number)
{
    bool found = false;
    
    if (matrix != NULL && rows > 0 && columns > 0) {
        int column = columns - 1;
        int row = 0;
        while (row < rows && column >= 0) {
            if (matrix[row * columns + column] == number) {
                found = true;
                break;
            }else if (matrix[row * columns + column] > number)
                -- column;
            else
                ++ row;
        }
    }
    
    return found;
}



void PrintNumber(int number)
{
    printf("%d\t", number);
}

void PrintMatrixInCircle(int** numbers, int columns, int rows, int start)
{
    int endX = columns - 1 - start;
    int endY = rows - 1 - start;
    
    // 从左到右打印一行
    for (int i = start; i <= endX; ++ i) {
        int number = numbers[start][i];
        PrintNumber(number);
    }
    
    // 从上到下打印一行
    if (start < endY) {
        for (int i = start + 1; i <= endY; ++ i) {
            int number = numbers[i][endX];
            PrintNumber(number);
        }
    }
    
    // 从右到左打印一行
    if (start < endX && start < endY) {
        for (int i = endX - 1; i >= start; -- i) {
            int number = numbers[endY][i];
            PrintNumber(number);
        }
    }
    
    // 从下到上打印一行
    if (start < endX && start < endY - 1) {
        for (int i = endY - 1; i >= start + 1; -- i) {
            int number = numbers[i][start];
            PrintNumber(number);
        }
    }
}

/**
 顺时针打印矩阵
 1  2   3  4
 5  6   7  8
 9  10  11 12
 13 14  15 16
 */
void PrintMatrixClockwisely(int** numbers, int columns, int rows)
{
    if (numbers == NULL || columns <= 0 || rows <= 0) return;
    int start = 0;
    // 由于矩阵左上角的坐标中行标和列标总是相同的，于是可以在矩阵中选取左上角为(start,start)的一圈作为分析的目标，对于4x4的矩阵，最后一圈有四个数字，左上角的坐标是(1,1)，发现4>1x1，继而得出循环条件是columns>startX*2并且rows>startY*2。
    while (columns > start * 2 && rows > start * 2) {
        PrintMatrixInCircle(numbers, columns, rows, start);
        ++ start;
    }
}

int __main(int arg, const char * argv[]) {
    int numbers[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    int **pp = new int*[4];
    for (int i = 0; i < 4; ++ i) {
        pp[i] = numbers[i];
    }
    PrintMatrixClockwisely(pp, 4, 4);
    
//    int numbers[1][4] = {{1, 2, 3, 4}};
//    int **pp = new int*[1];
//    for (int i = 0; i < 1; i++) {
//        pp[i] = numbers[i];
//    }
//    PrintMatrixClockwisely(pp, 4, 1);
    return 0;
}


#include <iostream>
#include <iomanip>
#include <vector>

#define MAX  100

using namespace std;

class MatrixDG {
    
public:
    // 创建图(自己输入数据)
    MatrixDG();
    // 创建图(用已提供的矩阵)
    MatrixDG(char vexs[], int vlen, char edges[][2], int elen);
    ~MatrixDG();
    
    // 深度优先搜索遍历图
    void DFS();
    // 广度优先搜索（类似于树的层次遍历）
    void BFS();
    // 打印矩阵队列图
    void print();
    
private:
    // 读取一个输入字符
    char readChar();
    // 返回ch在mMatrix矩阵中的位置
    int getPosition(char ch);
    // 返回顶点v的第一个邻接顶点的索引，失败则返回-1
    int firstVertex(int v);
    // 返回顶点v相对于w的下一个邻接顶点的索引，失败则返回-1
    int nextVertex(int v, int w);
    // 深度优先搜索遍历图的递归实现
    void DFS(int i, int *visited);
    
private:
    char mVexs[MAX]; // 顶点集合
    int  mVexNum; // 顶点数
    int  mEdgNum; // 边数
    int  mMatrix[MAX][MAX]; // 邻接矩阵
    
};


/*
 * 创建图(自己输入数据)
 */
MatrixDG::MatrixDG()
{
    char c1, c2;
    int i, p1, p2;
    
    // 输入"顶点数"和"边数"
    cout << "input vertex number: ";
    cin >> mVexNum;
    cout << "input edge number: ";
    cin >> mEdgNum;
    
    if ( mVexNum < 1 || mEdgNum < 1 || (mEdgNum > (mVexNum * (mVexNum-1))))
    {
        cout << "input error: invalid parameters!" << endl;
        return ;
    }
    
    // 初始化"顶点"
    for (i = 0; i < mVexNum; i++)
    {
        cout << "vertex(" << i << "): ";
        mVexs[i] = readChar();
    }
    
    // 初始化"边"
    for (i = 0; i < mEdgNum; i++)
    {
        // 读取边的起始顶点和结束顶点
        cout << "edge(" << i << "): ";
        c1 = readChar();
        c2 = readChar();
        
        p1 = getPosition(c1);
        p2 = getPosition(c2);
        if (p1==-1 || p2==-1)
        {
            cout << "input error: invalid edge!" << endl;
            return ;
        }
        
        mMatrix[p1][p2] = 1;
    }
}

/*
 * 创建图(用已提供的矩阵)
 *
 * 参数说明：
 *     vexs  -- 顶点数组
 *     vlen  -- 顶点数组的长度
 *     edges -- 边数组
 *     elen  -- 边数组的长度
 */
MatrixDG::MatrixDG(char vexs[], int vlen, char edges[][2], int elen)
{
    int i, p1, p2;
    
    // 初始化"顶点数"和"边数"
    mVexNum = vlen;
    mEdgNum = elen;
    // 初始化"顶点"
    for (i = 0; i < mVexNum; i++)
        mVexs[i] = vexs[i];
    
    // 初始化"边"
    for (i = 0; i < mEdgNum; i++)
    {
        // 读取边的起始顶点和结束顶点
        p1 = getPosition(edges[i][0]);
        p2 = getPosition(edges[i][1]);
        
        mMatrix[p1][p2] = 1;
    }
}


/*
 * 析构函数
 */
MatrixDG::~MatrixDG()
{
}

/*
 * 返回ch在mMatrix矩阵中的位置
 */
int MatrixDG::getPosition(char ch)
{
    int i;
    for(i = 0; i < mVexNum; i ++)
        if(mVexs[i] == ch)
            return i;
    return -1;
}


/*
 * 读取一个输入字符
 */
char MatrixDG::readChar()
{
    char ch;
    
    do {
        cin >> ch;
    } while(!((ch>='a'&&ch<='z') || (ch>='A'&&ch<='Z')));
    
    return ch;
}


/*
 * 返回顶点v的第一个邻接顶点的索引，失败则返回-1
 */
int MatrixDG::firstVertex(int v)
{
    int i;
    
    if (v<0 || v>(mVexNum-1))
        return -1;
    
    for (i = 0; i < mVexNum; i++)
        if (mMatrix[v][i] == 1)
            return i;
    
    return -1;
}

/*
 * 返回顶点v相对于w的下一个邻接顶点的索引，失败则返回-1
 */
int MatrixDG::nextVertex(int v, int w)
{
    int i;
    
    if (v<0 || v>(mVexNum-1) || w<0 || w>(mVexNum-1))
        return -1;
    
    for (i = w + 1; i < mVexNum; i++)
        if (mMatrix[v][i] == 1)
            return i;
    
    return -1;
}

/*
 * 深度优先搜索遍历图的递归实现
 */
void MatrixDG::DFS(int i, int *visited)
{
    int w;
    
    visited[i] = 1;
    cout << mVexs[i] << " ";
    // 遍历该顶点的所有邻接顶点。若是没有访问过，那么继续往下走
    for (w = firstVertex(i); w >= 0; w = nextVertex(i, w))
    {
        if (!visited[w])
            DFS(w, visited);
    }
    
}

/*
 * 深度优先搜索遍历图
 */
void MatrixDG::DFS()
{
    int i;
    int visited[MAX];       // 顶点访问标记
    
    // 初始化所有顶点都没有被访问
    for (i = 0; i < mVexNum; i++)
        visited[i] = 0;
    
    cout << "DFS: ";
    for (i = 0; i < mVexNum; i++)
    {
        //printf("\n== LOOP(%d)\n", i);
        if (!visited[i])
            DFS(i, visited);
    }
    cout << endl;
}

/*
 * 广度优先搜索（类似于树的层次遍历）
 */
void MatrixDG::BFS()
{
    int head = 0;
    int rear = 0;
    int queue[MAX];     // 辅组队列
    int visited[MAX];   // 顶点访问标记
    int i, j, k;
    
    for (i = 0; i < mVexNum; i++)
        visited[i] = 0;
    
    cout << "BFS: ";
    for (i = 0; i < mVexNum; i++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            cout << mVexs[i] << " ";
            queue[rear++] = i;  // 入队列
        }
        while (head != rear)
        {
            j = queue[head++];  // 出队列
            for (k = firstVertex(j); k >= 0; k = nextVertex(j, k)) //k是为访问的邻接顶点
            {
                if (!visited[k])
                {
                    visited[k] = 1;
                    cout << mVexs[k] << " ";
                    queue[rear++] = k;
                }
            }
        }
    }
    cout << endl;
}

/*
 * 打印矩阵队列图
 */
void MatrixDG::print()
{
    int i,j;
    
    cout << "Martix Graph:" << endl;
    for (i = 0; i < mVexNum; i++)
    {
        for (j = 0; j < mVexNum; j++)
            cout << mMatrix[i][j] << " ";
        cout << endl;
    }
}


int ___main(int arg, const char * argv[])
{
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    
    char edges[][2] = {
        {'A', 'B'},
        {'B', 'C'},
        {'B', 'E'},
        {'B', 'F'},
        {'C', 'E'},
        {'D', 'C'},
        {'E', 'B'},
        {'E', 'D'},
        {'F', 'G'}};
    
    int vlen = sizeof(vexs)/sizeof(vexs[0]);
    int elen = sizeof(edges)/sizeof(edges[0]);
    MatrixDG* pG;
    
    // 自定义"图"(输入矩阵队列)
    //pG = new MatrixDG();
    // 采用已有的"图"
    pG = new MatrixDG(vexs, vlen, edges, elen);
    
    pG->print();   // 打印图
    //    pG->DFS();     // 深度优先遍历
    pG->BFS();     // 广度优先遍历
    
    return 0;
    
}
