#include "Utility.h"
#include "dbl_lk_list.h"
#include "String.h"
#include "Editor.h"


void main(int argc, char *argv[])	// �����в���
// ǰ������: ���������и��������ļ�������ļ�
// �������: �������ļ����е��ı������У�ִ�м򵥵��б༭,��д�ı����浽����ļ���
{
	char infName[256],outfName[256];

	if (argc < 2) 
	{	// argc < 2���������ļ���
		cout << "�������ļ���(ȱʡ: file_in.txt):";
		strcpy(infName, read_in(cin).c_str());
		if (strlen(infName) == 0)
		{	// infNameΪ��
			strcpy(infName, "file_in.txt");
		}
	}
	else
	{	// ��argv[1]���Ƹ�infName
		strcpy(infName, argv[1]);
	}

	ifstream file_in(infName);   // ���岢�������ļ���
	if (file_in == 0) {
		cout << "�������ļ�" << infName << "ʧ��" << endl;
		exit(1);
	}
	
	if (argc < 3) 
	{		// argc < 3��������ļ���
		cout << "������ļ���(ȱʡ: file_out.txt):";
		strcpy(outfName, read_in(cin).c_str());
		if (strlen(outfName) == 0)
		{	// outfNameΪ��
			strcpy(outfName, "file_out.txt");
		}
	}
	else
	{	// ��argv[2]���Ƹ�outfName
		strcpy(outfName,argv[2]);
	}

	ofstream file_out(outfName);   // ���岢������ļ���.
	if (file_out == 0) {
		cout << "�������ļ�" << outfName << "ʧ��" << endl;
		exit(2);
	}

	Editor buffer(&file_in, &file_out);	// �����ı�����
	while (buffer.get_command())
	{	// ���ղ�ִ���û���������
		buffer.run_command();
	}
}
