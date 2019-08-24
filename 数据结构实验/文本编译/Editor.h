#ifndef __EDITOR_H__
#define __EDITOR_H__

#include "Utility.h"
#include "dbl_lk_list.h"
#include "String.h"

// 文本编辑类
class Editor
{
public:
//  方法声明:
	Editor(ifstream *file_in, ofstream *file_out);	// 构造函数
	bool get_command();				// 读取操作命令字符user_command
	void run_command();				// 运行操作命令

private:
//	成员变量
	DblLinkList<String> text;		// 文本缓存
	int current_line_no;			// 当前行号
	ifstream *infile;				// 输入文件
	ofstream *outfile;				// 输出文件
	char user_command;				// 用户命令

//  辅助函数
	Status_code next_line();		// 转到下一行
	Status_code previous_line();	// 转到前一行
	Status_code goto_line();		// 转到指定行
	Status_code insert_line();		// 插入一行	
	Status_code substitute_line();	// 替换指定行
	Status_code change_line();		// 替换当前行
	void read_file();				// 读入文本文件
	void write_file();				// 写文本文件
	void find_string();				// 查找串
	bool user_says_yes();			// 回答yes/no
};


Editor::Editor(ifstream *file_in, ofstream *file_out)
// 构造函数，用输入文件file_in和输出文件file_out构造编辑器
{
	infile = file_in;				// 输入文件
	outfile = file_out;				// 输出文件
	current_line_no = 0;			// 当前行号
}


bool Editor::get_command()
// 读取操作命令字符user_command，除非user_command为'q'，否则返回true
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
		cout << "文件缓存是空的(请用输入r读取文件到缓存中). \n?";
	}

	cin >> user_command;    // 忽略空格并取得操作命令字符
	user_command = tolower(user_command);	// 转换为小字字母
	while (cin.get() != '\n');	// 忽略用户输入的其他字符
	if (user_command == 'q')
	{	// user_command为'q'时返回false 
		return false;
	}
	else
	{	// user_command不为'q'时返回true
		return true;
	}
}


void Editor::run_command()
// 运行操作命令
{
	String temp_string;		// 临时串
	switch (user_command) 
	{
	case 'b':	// 转到第1行b(egin)
		if (text.Empty())
		{	// 文本缓存空
			cout << " 警告: 文本缓存空 " << endl;
		}
		else
		{	// 文本缓存非空, 转到第1行
			current_line_no = 1;
		}
		break;

	case 'c':	// 替换当前行c(hange)
		if (text.Empty())
		{
			cout << " 警告: 文本缓存空" << endl;
		}
		else if (change_line() != SUCCESS)
		{	// 替换当失败
			cout << " 错误: 替换失败 " << endl;
		}
		break;

	case 'd':	// 删除当前行d(el)
		if (text.Delete(current_line_no, temp_string) != SUCCESS)
		{	// 删除当前行失败
			cout << " 错误: 删除失败 " << endl;
		}
		break;

	case 'e':	// 转到最后一行e(nd)
		if (text.Empty())
		{
			cout << " 警告: 文本缓存空 " << endl;
		}
		else
		{	// 转到第一行
			current_line_no = text.Length();
		}
		break;

	case 'f':	// 从当前行开始查找指定文本f(ind)
		if (text.Empty())
		{
			cout << " 警告: 文本缓存空 " << endl;
		}
		else
		{	// 从当前行开始查找指定文本
			find_string();
		}
		break;

	case 'g':	// 转到指定行g(o)
		if (goto_line() != SUCCESS)
		{	// 转到指定行失败
			cout << " 警告: 没有那样的行" << endl;
		}
		break;

	case '?':	// 获得帮助?
	case 'h':	// 获得帮助h(elp)
		cout << "有效命令: b(egin) c(hange) d(el) e(nd)" << endl
			<< "f(ind) g(o) h(elp) i(nsert) l(ength) n(ext) p(rior) " << endl
			<< "q(uit) r(ead) s(ubstitute) v(iew) w(rite) " << endl;
		break;

	case 'i':	// 插入指定行i(nsert)
		if (insert_line() != SUCCESS)
			cout << " 错语: 插入行出错 " << endl;
		break;

	case 'l':	// 显示文本行数l(ength)
		cout << "在文件中有 " << text.Length() << " 行文本串." << endl;
		if (!text.Empty())
		{	// 非空文件
			String cur_line;			// 当前行	
			text.GetElem(current_line_no, cur_line);
			cout << "当前行是："
				<< strlen(cur_line.c_str()) << endl;
		}
		break;

	case 'n':	// 转到下一行n(ext)
		if (next_line() != SUCCESS)
		{	// 无下一行
			cout << " 警告: 当前行已是最后一行" << endl;
		}
		break;

	case 'p':	// 转到前一行p(rior)
		if (previous_line() != SUCCESS)
		{	// 无前一行
			cout << " 警告: 当前行已是第一行" << endl;
		}
		break;

	case 'r':	// 读入文本件r(ead)
		read_file();
		break;

	case 's':	// 替换指定行s(ubstitute)
		if (substitute_line() != SUCCESS)
		{	// 替换指定行失败
			cout << " 错误: 替换指定行失败 " << endl;
		}
		break;

	case 'v':	// 显示文本v(iew)
		text.Traverse(write);
		break;

	case 'w':	// 写文本缓存到输出文件中w(rite)
		if (text.Empty())
		{	// 文本缓存空
			cout << " 警告: 文本缓存空" << endl;
		}
		else
		{	// 写文本缓存到输出文件中
			write_file();
		}
		break;

	default :
		cout << "输入h或?获得帮助或输入有效命令字符: \n";
	}
}


Status_code Editor::next_line()
// 转到下一行
{
	if ( current_line_no >= text.Length())
	{	// 当前行号已是最后一行
		return FAIL;
	}
	else
	{	// 当前行号不是最后一行
		current_line_no++;
		return SUCCESS;
	}
}


Status_code Editor::previous_line()
// 转到前一行
{
	if(current_line_no <= 1)
	{	// 当前行号已是第一行
		return FAIL;
	}
	else
	{	// 当前行号不是第一行
		current_line_no--;
		return SUCCESS;
	}
}


Status_code Editor::goto_line()
// 转到指定行
{
	int line_number;
	cout << " 输入指定的行号: ";
	cin  >> line_number;
	if(line_number < 1 || line_number > text.Length())
	{	// 行号范围错
		return RANGE_ERROR;
	}
	else
	{	// 行号范围正确
		current_line_no = line_number;
		return SUCCESS;
	}
}


Status_code Editor::insert_line()
// 插入指定行
{
	int line_number;	
	cout << " 输入指定行号? ";
	cin  >> line_number;
	while (cin.get() != '\n');	// 跳过其他字符
	cout << " 输入新行文本串: ";
	String to_insert = read_in(cin);
	if (text.Insert(line_number, to_insert) == SUCCESS)
	{	// 插入成功
		current_line_no = line_number;
		return SUCCESS;
	}
	else
	{	// 插入失败
		return RANGE_ERROR;
	}
}


Status_code Editor::substitute_line()
// 替换指定行
{
	int line_number;
	char ch;
	String new_line;
	cout << " 输入指定行号:";
	cin  >> line_number;
	if(line_number < 1 || line_number > text.Length())
	{	// 范围错
		return RANGE_ERROR;
	}
	else
	{
		current_line_no = line_number;
		cout<<" 输入新行文本串:" << endl;
		while ((ch = cin.get()) != '\n');  // 跳过行中其它字符
		new_line = read_in(cin);		// 输入新行
		text.SetElem(line_number, new_line);
		return SUCCESS;
   }
}


Status_code Editor::change_line()
// 替换当前行，用户输入当前行中的指定文本，用输入的新文本替换指定文本
// 替换成功返回SUCCESS，否则返回FAIL
{
	Status_code result = SUCCESS;
	cout << " 输入要被替换的指定文本: ";
	String old_text = read_in(cin);
	cout << " 输入新文本:";
	String new_text = read_in(cin);

	String cur_line;			// 当前行	
	text.GetElem(current_line_no, cur_line);
	int index = strstr(cur_line, old_text);
	if (index == -1) 
	{	// 模式匹配失败
		result = FAIL;
	}
	else 
	{	// 模式匹配成功
		String new_line;	// 新行
		strncpy(new_line, cur_line, index);	 // 复指定文本前的串
		strcat(new_line, new_text);	// 连接新文本串
		const char *old_line = (cur_line).c_str();
		strcat(new_line, (String)(old_line + index + strlen(old_text.c_str())));
			// 连接指定文本后的串
		text.SetElem(current_line_no, new_line);	// 设置当前行新串
   }
   return result;
}


bool Editor::user_says_yes()
// 回答yes/no
{
	char answer;
	cin >> answer;
	answer = tolower(answer);	// 转换为小写字母
	if (answer == 'y' || answer == 't' || answer=='o')
	{	// 回答yes
		return true;
	}
	else
	{	// 回答no
		return false;
	}
}

   
void Editor::read_file()
// 读入文本件
{
	bool proceed = true;
	if (!text.Empty()) 
	{	// 文本缓存非空
		cout << "文本缓存非空; 读入文件时将复盖它." << endl;
		cout << " 回答yes将执行此操作? " << endl;
		if (proceed = user_says_yes()) 
		{	// 回答yes
			text.Clear();
		}
	}

	int line_number = 1;
	char terminal_char;
	while (proceed) 
	{
		String in_string = read_in(*infile, terminal_char);
		if (terminal_char == EOF) 
		{	// 以文件结束符结束, 输入已结束
			proceed = false;
			if (strlen(in_string.c_str()) > 0) 
			{	// 插入非空串
				text.Insert(line_number , in_string);
			}
		}
		else
		{	// 输入未结束
			text.Insert(line_number++, in_string);
		}
	}

	if (text.Empty())
	{	// 当前文本缓存为空
		current_line_no = 0;
	}
	else
	{	// 当前文本缓存非空
		current_line_no = 1;
	}
}


void Editor::write_file()
// 写文本缓存到输出文件中
{
	String cur_line;
    int line_number;
	for(line_number=1; line_number <= text.Length(); line_number++)
	{	// 写文本缓存各行到输出文件中
		text.GetElem(line_number, cur_line);
		*outfile << cur_line.c_str() << endl;
	}
}


void Editor::find_string()
// 从当前行开始查找指定文本
{
	int index;
	cout << "输入被查找的文本串:" << endl;
	String search_string = read_in(cin);
	String cur_line;			// 当前行	
	text.GetElem(current_line_no, cur_line);
	while ((index = strstr(cur_line, search_string)) == -1)
	{
		if (current_line_no < text.Length()) 
		{	// 查找下一行
			current_line_no++;
			text.GetElem(current_line_no, cur_line);
		}
		else
		{	// 已查找完所有行
			break;
		}
	}
	
	if (index == -1) 
	{	// 查找失败
		cout << "查找串失败.";
	}
	else 
	{	// 查找成功
		cout << cur_line.c_str() << endl;
		for (int i = 0; i < index; i++)
		{	// 在查找串前的位置显行空格
			cout << " ";
		}
		for (int j = 0; j < strlen(search_string.c_str()); j++)
		{	// 在查找串前的位置显行^
			cout << "^";
		}
   }
   cout << endl;
}

#endif