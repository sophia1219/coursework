#ifndef __UTILITY_H__
#define __UTILITY_H__

// ʵ��ͷ�ļ�

// ANSI C++��׼��ͷ�ļ�
#include <string>		// ��׼���Ͳ���
#include <iostream>		// ��׼������
#include <limits>		// ����
#include <cmath>		// ���ݺ���
#include <fstream>		// �ļ��������
#include <cctype>       // �ַ�����
#include <ctime>        // ���ں�ʱ�亯��
#include <conio.h>		// �����������
#include <cstdlib>      // ��׼��
#include <cstdio>       // ��׼�������
#include <iomanip>		// �����������ʽ����	
#include <cstdarg> 		// ֧�ֱ䳤��������	
using namespace std;	// ��׼������������ռ�std��

// �Զ�������
enum Status_code {SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW,RANGE_ERROR, DUPLICATE_ERROR,
	NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND};

#endif