#ifndef __UTILITY_H__
#define __UTILITY_H__

// 实用头文件

// ANSI C++标准库头文件
#include <string>		// 标准串和操作
#include <iostream>		// 标准流操作
#include <limits>		// 极限
#include <cmath>		// 数据函数
#include <fstream>		// 文件输入输出
#include <cctype>       // 字符处理
#include <ctime>        // 日期和时间函数
#include <conio.h>		// 输入输出控制
#include <cstdlib>      // 标准库
#include <cstdio>       // 标准输入输出
#include <iomanip>		// 输入输出流格式设置	
#include <cstdarg> 		// 支持变长函数参数	
using namespace std;	// 标准库包含在命名空间std中

// 自定义类型
enum Status_code {SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW,RANGE_ERROR, DUPLICATE_ERROR,
	NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND};

#endif