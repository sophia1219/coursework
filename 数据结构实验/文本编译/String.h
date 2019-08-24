#ifndef __STRING_H__
#define __STRING_H__

#include "Utility.h"
#include "dbl_lk_list.h"

// ����
class String 
{
public:                           
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
   
	String();							// ���캯�� 
	~String();							// ��������
	String(const String &copy);			// ���ƹ��캯��
	String(const char * copy);			// ��C���ת�����캯��
	String(DblLinkList<char> &copy);	// �����Ա�ת�����캯��

	void operator =(const String &copy);// ��ֵ�������
	const char *c_str() const;			// ����ת����C���

protected:
	char *entries;						// ��ֵ
	int length;							// ����	
};

// ����غ���
String read_in(istream &input);						
	// �����������봮
String read_in(istream &input,char &terminal_char);
	// �����������봮������terminal_char���ش������ַ�
void write(String &s);					// �����
void strcat(String &add_to, const String &add_on);
	// ����add_on���ӵ�add_to���ĺ���
void strcpy(String &copy, const String &original);
	// ����original���Ƶ���copy
void strncpy(String &copy, const String &original, int n);
	// ����original����n���ַ�����copy 
int strstr(const String &text, const String &target);
	// ����ģʽ��target��һ����Ŀ�괮text�г��ֵ�λ��
bool operator ==(const String &first, const String &second);
	// ���ع�ϵ�����==
bool operator <(const String &first, const String &second);
	// ���ع�ϵ�����<
bool operator >(const String &first, const String &second);
	// ���ع�ϵ�����>
bool operator <=(const String &first, const String &second);
	// ���ع�ϵ�����<=
bool operator >=(const String &first, const String &second);
	// ���ع�ϵ�����>=
bool operator !=(const String &first, const String &second);
	// ���ع�ϵ�����!=


String::String()
// ���캯�� 
{
	length = 0;				// ������Ϊ0
	entries = NULL;			// �մ�
}


String::~String()
// ��������
{
	delete []entries;		// �ͷŴ�entries
}


String::String(const String &copy)
// ���ƹ��캯��
{
	length = strlen(copy.c_str());	// ����
	entries = new char[length + 1];	// ����洢�ռ�
	strcpy(entries, copy.c_str());	// ���ƴ�ֵ
}


String::String(const char *in_string)
// ��C���ת�����캯��
{
	length = strlen(in_string);		// ����
	entries = new char[length + 1];	// ����洢�ռ� 
	strcpy(entries, in_string);		// ���ƴ�ֵ
}


String::String(DblLinkList<char> &copy)
// �����Ա�ת�����캯��
{
	length = copy.Length();		// ����
	entries = new char[length + 1];	// ����洢�ռ� 
	for (int i = 0; i < length; i++) 
	{	// ���ƴ�ֵ
		copy.GetElem(i + 1, entries[i]);
	}
	entries[length] = '\0';			// ��ֵ��'\0'����	
}


void String::operator =(const String &copy)
// ��ֵ�������
{
	delete []entries;				// �ͷ�ԭ���洢�ռ�
	length = strlen(copy.c_str());	// ����
	entries = new char[length + 1];	// ����洢�ռ� 
	strcpy(entries, copy.c_str());	// ���ƴ�ֵ
}


const char*String::c_str() const
// ����ת����C���
{
	return (const char *)entries;	// ��ֵ����ת��
}


void strcat(String &add_to, const String &add_on)
// ����add_on���ӵ�add_to���ĺ���
{
	const char *cfirst = add_to.c_str();	// ָ���һ����
	const char *csecond = add_on.c_str();	// ָ��ڶ�����
	char *copy = new char[strlen(cfirst) + strlen(csecond) + 1];	
		// ����洢�ռ�
	strcpy(copy, cfirst);					// ���Ƶ�һ����
	strcat(copy, csecond);					// ���ӵڶ�����
	add_to = copy;							// ����ֵ
	delete []copy;							// �ͷ�copy
}


String read_in(istream &input)
// �����������봮������terminal_char���ش������ַ�
{
	DblLinkList<char> temp;					// ��ʱ���Ա�
	int size = 0;							// ��ʼ���Ա���
	char c;									// ��ʱ�ַ�
	while ((c = input.peek()) != EOF &&		// peek()����������ȡһ���ַ�
											// ������ָ�벻��
		(c = input.get()) != '\n')			// get()����������ȡһ���ַ�
											// ������ָ��ָ����һ���ַ�
	{	// ��������ַ�׷�����Ա���
		temp.Insert(++size, c);
	}
	String answer(temp);					// ���촮
	return answer;							// ���ش�
}


String read_in(istream &input,char &terminal_char)
// �����������봮������terminal_char���ش������ַ�
{
	DblLinkList<char> temp;					// ��ʱ���Ա�
	int size = 0;							// ��ʼ���Ա���
	char c;									// ��ʱ�ַ�
	while ((c = input.peek()) != EOF && 
		(c = input.get()) != '\n')
	{	// ��������ַ�׷�����Ա���
		temp.Insert(++size, c);
	}
	terminal_char=c;	// ��terminal_char���ش������ַ�
	String answer(temp);					// ���촮
	return answer;							// ���ش�
}


void write(String &s)
// �����
{
	cout << s.c_str() << endl;				// �����ֵ
}


void strcpy(String &copy, const String &original)
// ����original���Ƶ���copy
{
	const char *coriginal = original.c_str();// ��ʼ��
	char *ccopy = new char[strlen(coriginal) + 1];// ����洢�ռ�
	strcpy(ccopy, coriginal);				// ���ƴ�
	copy = ccopy;							// ����ֵ
	delete []ccopy;							// �ͷŴ�ccopy
}


void strncpy(String &copy, const String &original, int n)
// ����original����n���ַ�����copy 
{
	const char *coriginal = original.c_str();// ��ʼ��
	int len = strlen(coriginal) < n ? strlen(coriginal) : n;//Ŀ�괮��
	char *ccopy = new char[len + 1];		// ����洢�ռ�
	strncpy(ccopy, coriginal, n);			// ���ƴ�
	ccopy[len] = '\0';						// ��ֵ��'\0'����
	copy = ccopy;							// ����ֵ
	delete []ccopy;							// �ͷŴ�ccopy
}


int strstr(const String &text, const String &target)
// ����ģʽ��target��һ����Ŀ�괮text�г��ֵ�λ��
{
	const char *ctext = text.c_str();		// Ŀ�괮
	const char *ctarget = target.c_str();	// ģʽ��
	char *ptr=strstr(ctext, ctarget);		// ģʽƥ��
	if (ptr == NULL)
	{	// ƥ��ʧ��	
		return -1; 
	}
	else
	{	// ƥ��ɹ�	
		return ptr - ctext;
	}
}


bool operator ==(const String &first, const String &second)
// ���ع�ϵ�����==
{
	return strcmp(first.c_str(), second.c_str()) == 0;
}


bool operator <(const String &first, const String &second)
// ���ع�ϵ�����<
{
	return strcmp(first.c_str(), second.c_str()) < 0;
}


bool operator >(const String &first, const String &second)
// ���ع�ϵ�����>
{
	return strcmp(first.c_str(), second.c_str()) > 0;
}


bool operator <=(const String &first, const String &second)
// ���ع�ϵ�����<=
{
	return strcmp(first.c_str(), second.c_str()) <= 0;
}


bool operator >=(const String &first, const String &second)
// ���ع�ϵ�����>=
{
	return strcmp(first.c_str(), second.c_str()) >= 0;
}

bool operator !=(const String &first, const String &second)
// ���ع�ϵ�����!=
{
	return strcmp(first.c_str(), second.c_str()) != 0;
}

#endif