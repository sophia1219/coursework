#ifndef __EDITOR_H__
#define __EDITOR_H__

#include "Utility.h"
#include "dbl_lk_list.h"
#include "String.h"

// �ı��༭��
class Editor
{
public:
//  ��������:
	Editor(ifstream *file_in, ofstream *file_out);	// ���캯��
	bool get_command();				// ��ȡ���������ַ�user_command
	void run_command();				// ���в�������

private:
//	��Ա����
	DblLinkList<String> text;		// �ı�����
	int current_line_no;			// ��ǰ�к�
	ifstream *infile;				// �����ļ�
	ofstream *outfile;				// ����ļ�
	char user_command;				// �û�����

//  ��������
	Status_code next_line();		// ת����һ��
	Status_code previous_line();	// ת��ǰһ��
	Status_code goto_line();		// ת��ָ����
	Status_code insert_line();		// ����һ��	
	Status_code substitute_line();	// �滻ָ����
	Status_code change_line();		// �滻��ǰ��
	void read_file();				// �����ı��ļ�
	void write_file();				// д�ı��ļ�
	void find_string();				// ���Ҵ�
	bool user_says_yes();			// �ش�yes/no
};


Editor::Editor(ifstream *file_in, ofstream *file_out)
// ���캯�����������ļ�file_in������ļ�file_out����༭��
{
	infile = file_in;				// �����ļ�
	outfile = file_out;				// ����ļ�
	current_line_no = 0;			// ��ǰ�к�
}


bool Editor::get_command()
// ��ȡ���������ַ�user_command������user_commandΪ'q'�����򷵻�true
{
	String cur_line;
	if (current_line_no != 0)
	{
		text.GetElem(current_line_no, cur_line);
		cout << current_line_no << " : "
			<< cur_line.c_str() << "\n?";
	}
	else
	{
		cout << "�ļ������ǿյ�(��������r��ȡ�ļ���������). \n?";
	}

	cin >> user_command;    // ���Կո�ȡ�ò��������ַ�
	user_command = tolower(user_command);	// ת��ΪС����ĸ
	while (cin.get() != '\n');	// �����û�����������ַ�
	if (user_command == 'q')
	{	// user_commandΪ'q'ʱ����false 
		return false;
	}
	else
	{	// user_command��Ϊ'q'ʱ����true
		return true;
	}
}


void Editor::run_command()
// ���в�������
{
	String temp_string;		// ��ʱ��
	switch (user_command) 
	{
	case 'b':	// ת����1��b(egin)
		if (text.Empty())
		{	// �ı������
			cout << " ����: �ı������ " << endl;
		}
		else
		{	// �ı�����ǿ�, ת����1��
			current_line_no = 1;
		}
		break;

	case 'c':	// �滻��ǰ��c(hange)
		if (text.Empty())
		{
			cout << " ����: �ı������" << endl;
		}
		else if (change_line() != SUCCESS)
		{	// �滻��ʧ��
			cout << " ����: �滻ʧ�� " << endl;
		}
		break;

	case 'd':	// ɾ����ǰ��d(el)
		if (text.Delete(current_line_no, temp_string) != SUCCESS)
		{	// ɾ����ǰ��ʧ��
			cout << " ����: ɾ��ʧ�� " << endl;
		}
		break;

	case 'e':	// ת�����һ��e(nd)
		if (text.Empty())
		{
			cout << " ����: �ı������ " << endl;
		}
		else
		{	// ת����һ��
			current_line_no = text.Length();
		}
		break;

	case 'f':	// �ӵ�ǰ�п�ʼ����ָ���ı�f(ind)
		if (text.Empty())
		{
			cout << " ����: �ı������ " << endl;
		}
		else
		{	// �ӵ�ǰ�п�ʼ����ָ���ı�
			find_string();
		}
		break;

	case 'g':	// ת��ָ����g(o)
		if (goto_line() != SUCCESS)
		{	// ת��ָ����ʧ��
			cout << " ����: û����������" << endl;
		}
		break;

	case '?':	// ��ð���?
	case 'h':	// ��ð���h(elp)
		cout << "��Ч����: b(egin) c(hange) d(el) e(nd)" << endl
			<< "f(ind) g(o) h(elp) i(nsert) l(ength) n(ext) p(rior) " << endl
			<< "q(uit) r(ead) s(ubstitute) v(iew) w(rite) " << endl;
		break;

	case 'i':	// ����ָ����i(nsert)
		if (insert_line() != SUCCESS)
			cout << " ����: �����г��� " << endl;
		break;

	case 'l':	// ��ʾ�ı�����l(ength)
		cout << "���ļ����� " << text.Length() << " ���ı���." << endl;
		if (!text.Empty())
		{	// �ǿ��ļ�
			String cur_line;			// ��ǰ��	
			text.GetElem(current_line_no, cur_line);
			cout << "��ǰ���ǣ�"
				<< strlen(cur_line.c_str()) << endl;
		}
		break;

	case 'n':	// ת����һ��n(ext)
		if (next_line() != SUCCESS)
		{	// ����һ��
			cout << " ����: ��ǰ���������һ��" << endl;
		}
		break;

	case 'p':	// ת��ǰһ��p(rior)
		if (previous_line() != SUCCESS)
		{	// ��ǰһ��
			cout << " ����: ��ǰ�����ǵ�һ��" << endl;
		}
		break;

	case 'r':	// �����ı���r(ead)
		read_file();
		break;

	case 's':	// �滻ָ����s(ubstitute)
		if (substitute_line() != SUCCESS)
		{	// �滻ָ����ʧ��
			cout << " ����: �滻ָ����ʧ�� " << endl;
		}
		break;

	case 'v':	// ��ʾ�ı�v(iew)
		text.Traverse(write);
		break;

	case 'w':	// д�ı����浽����ļ���w(rite)
		if (text.Empty())
		{	// �ı������
			cout << " ����: �ı������" << endl;
		}
		else
		{	// д�ı����浽����ļ���
			write_file();
		}
		break;

	default :
		cout << "����h��?��ð�����������Ч�����ַ�: \n";
	}
}


Status_code Editor::next_line()
// ת����һ��
{
	if ( current_line_no >= text.Length())
	{	// ��ǰ�к��������һ��
		return FAIL;
	}
	else
	{	// ��ǰ�кŲ������һ��
		current_line_no++;
		return SUCCESS;
	}
}


Status_code Editor::previous_line()
// ת��ǰһ��
{
	if(current_line_no <= 1)
	{	// ��ǰ�к����ǵ�һ��
		return FAIL;
	}
	else
	{	// ��ǰ�кŲ��ǵ�һ��
		current_line_no--;
		return SUCCESS;
	}
}


Status_code Editor::goto_line()
// ת��ָ����
{
	int line_number;
	cout << " ����ָ�����к�: ";
	cin  >> line_number;
	if(line_number < 1 || line_number > text.Length())
	{	// �кŷ�Χ��
		return RANGE_ERROR;
	}
	else
	{	// �кŷ�Χ��ȷ
		current_line_no = line_number;
		return SUCCESS;
	}
}


Status_code Editor::insert_line()
// ����ָ����
{
	int line_number;	
	cout << " ����ָ���к�? ";
	cin  >> line_number;
	while (cin.get() != '\n');	// ���������ַ�
	cout << " ���������ı���: ";
	String to_insert = read_in(cin);
	if (text.Insert(line_number, to_insert) == SUCCESS)
	{	// ����ɹ�
		current_line_no = line_number;
		return SUCCESS;
	}
	else
	{	// ����ʧ��
		return RANGE_ERROR;
	}
}


Status_code Editor::substitute_line()
// �滻ָ����
{
	int line_number;
	char ch;
	String new_line;
	cout << " ����ָ���к�:";
	cin  >> line_number;
	if(line_number < 1 || line_number > text.Length())
	{	// ��Χ��
		return RANGE_ERROR;
	}
	else
	{
		current_line_no = line_number;
		cout<<" ���������ı���:" << endl;
		while ((ch = cin.get()) != '\n');  // �������������ַ�
		new_line = read_in(cin);		// ��������
		text.SetElem(line_number, new_line);
		return SUCCESS;
   }
}


Status_code Editor::change_line()
// �滻��ǰ�У��û����뵱ǰ���е�ָ���ı�������������ı��滻ָ���ı�
// �滻�ɹ�����SUCCESS�����򷵻�FAIL
{
	Status_code result = SUCCESS;
	cout << " ����Ҫ���滻��ָ���ı�: ";
	String old_text = read_in(cin);
	cout << " �������ı�:";
	String new_text = read_in(cin);

	String cur_line;			// ��ǰ��	
	text.GetElem(current_line_no, cur_line);
	int index = strstr(cur_line, old_text);
	if (index == -1) 
	{	// ģʽƥ��ʧ��
		result = FAIL;
	}
	else 
	{	// ģʽƥ��ɹ�
		String new_line;	// ����
		strncpy(new_line, cur_line, index);	 // ��ָ���ı�ǰ�Ĵ�
		strcat(new_line, new_text);	// �������ı���
		const char *old_line = (cur_line).c_str();
		strcat(new_line, (String)(old_line + index + strlen(old_text.c_str())));
			// ����ָ���ı���Ĵ�
		text.SetElem(current_line_no, new_line);	// ���õ�ǰ���´�
   }
   return result;
}


bool Editor::user_says_yes()
// �ش�yes/no
{
	char answer;
	cin >> answer;
	answer = tolower(answer);	// ת��ΪСд��ĸ
	if (answer == 'y' || answer == 't' || answer=='o')
	{	// �ش�yes
		return true;
	}
	else
	{	// �ش�no
		return false;
	}
}

   
void Editor::read_file()
// �����ı���
{
	bool proceed = true;
	if (!text.Empty()) 
	{	// �ı�����ǿ�
		cout << "�ı�����ǿ�; �����ļ�ʱ��������." << endl;
		cout << " �ش�yes��ִ�д˲���? " << endl;
		if (proceed = user_says_yes()) 
		{	// �ش�yes
			text.Clear();
		}
	}

	int line_number = 1;
	char terminal_char;
	while (proceed) 
	{
		String in_string = read_in(*infile, terminal_char);
		if (terminal_char == EOF) 
		{	// ���ļ�����������, �����ѽ���
			proceed = false;
			if (strlen(in_string.c_str()) > 0) 
			{	// ����ǿմ�
				text.Insert(line_number , in_string);
			}
		}
		else
		{	// ����δ����
			text.Insert(line_number++, in_string);
		}
	}

	if (text.Empty())
	{	// ��ǰ�ı�����Ϊ��
		current_line_no = 0;
	}
	else
	{	// ��ǰ�ı�����ǿ�
		current_line_no = 1;
	}
}


void Editor::write_file()
// д�ı����浽����ļ���
{
	String cur_line;
    int line_number;
	for(line_number=1; line_number <= text.Length(); line_number++)
	{	// д�ı�������е�����ļ���
		text.GetElem(line_number, cur_line);
		*outfile << cur_line.c_str() << endl;
	}
}


void Editor::find_string()
// �ӵ�ǰ�п�ʼ����ָ���ı�
{
	int index;
	cout << "���뱻���ҵ��ı���:" << endl;
	String search_string = read_in(cin);
	String cur_line;			// ��ǰ��	
	text.GetElem(current_line_no, cur_line);
	while ((index = strstr(cur_line, search_string)) == -1)
	{
		if (current_line_no < text.Length()) 
		{	// ������һ��
			current_line_no++;
			text.GetElem(current_line_no, cur_line);
		}
		else
		{	// �Ѳ�����������
			break;
		}
	}
	
	if (index == -1) 
	{	// ����ʧ��
		cout << "���Ҵ�ʧ��.";
	}
	else 
	{	// ���ҳɹ�
		cout << cur_line.c_str() << endl;
		for (int i = 0; i < index; i++)
		{	// �ڲ��Ҵ�ǰ��λ�����пո�
			cout << " ";
		}
		for (int j = 0; j < strlen(search_string.c_str()); j++)
		{	// �ڲ��Ҵ�ǰ��λ������^
			cout << "^";
		}
   }
   cout << endl;
}

#endif