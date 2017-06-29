//
//  CMyString.cpp
//  AlgorithmC++
//
//  Created by GaoCheng.Zou on 2017/6/23.
//  Copyright © 2017年 Minxin. All rights reserved.
//

#include "CMyString.hpp"
#include <set>

class CMyString
{
public:
    // 函数声明
    CMyString(char* pData = NULL);
    CMyString(const CMyString& str);
    ~CMyString(void);
    
    // 重载操作符
    CMyString& operator = (const CMyString& str);
    
    void Print();
    
private:
    char* m_pData;
};


CMyString::CMyString(char *pData)
{
    if(pData == NULL)
    {
        m_pData = new char[1];
        m_pData[0] = '\0';
    }
    else
    {
        int length = (int)strlen(pData);
        m_pData = new char[length + 1];
        strcpy(m_pData, pData);
    }
}

CMyString::~CMyString()
{
    delete []m_pData;
}

CMyString::CMyString(const CMyString& str)
{
    int length = (int)strlen(str.m_pData);
    m_pData = new char[length + 1];
    strcpy(m_pData, str.m_pData);
}

void CMyString::Print()
{
    printf("%s", m_pData);
}

/**
 赋值运算符函数
 
 @param str 常量引用
 
 @return 类的引用
 */
CMyString& CMyString::operator = (const CMyString& str)
{
    //    if(this == &str)
    //        return *this;
    //
    //    delete []m_pData;
    //    m_pData = NULL;
    //
    //
    //    m_pData = new char[strlen(str.m_pData) + 1];
    //    strcpy(m_pData, str.m_pData);
    if (this != &str) {
        CMyString strTemp(str);
        
        char* pTemp = strTemp.m_pData;
        strTemp.m_pData = m_pData;
        m_pData = pTemp;
    }
    
    return *this;
}
