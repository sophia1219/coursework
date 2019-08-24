#include"Utility.h"
#include"lk_list.h"
#include"string.h"
#include"node.h"
#include"Huffman_tree_node.h"
#include"Huffman_tree.h"
int main() 
{
	HuffmanTree hf;
	char c=0;
	while(c!='3')  
	{
		cout<<endl<<"1.Huffman compress.";
		cout<<endl<<"2.Huffman decompress.";
		cout<<endl<<"3.Exit.";
		cout<<endl<<"Please select:";
		cin>>c;
		switch(c)
		{
			case '1':   
				hf.Encode(CharType ch);
				break;
			case '2':
				hf.Decode(String strCode);
		}
	}
	system("pause");
	return 0;
}
