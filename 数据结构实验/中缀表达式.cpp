#include <iostream>
#include<stdio.h>
#include <stack>
#include <string>
using namespace std;
template<class Elem>
class Link 
{
    public:
        Elem element;
        Link *next;
        Link (const Elem &elemval,Link *nextval = NULL)
        {
            element = elemval;
            next = nextval;
        }
        Link (Link *nextval = NULL)
        {
            next = nextval;
        }    
};           
template <class Elem>
class LStack : public stack<Elem>
{
    private:
        Link<Elem> *top;
        int size;
    public:
        LStack()
        {
            top = NULL;
            size = 0;
        }
        ~LStack(){clear ();}
        void clear ()
        {
            while (top!=NULL){
                Link<Elem> *item = top;
                top=top->next;
                size=0;
                delete item;
            }
        }
        bool push(const Elem &item)
        {
            top = new Link<Elem>(item,top);
            size++;
            return true;
        }  
        bool pop(Elem &it)
        {
            if(size==0) return false;
            it = top->element;
            Link<Elem> *Itemp=top->next;
            delete top;
            top=Itemp;
            size--;
            return true;
        }
        bool topValue(Elem &it)const
        {
            if(size==0) return false;
            it=top->element;
            return true;                   
        }
};
class Calculator
{
    private:
        static bool IsOperator(char ch)//�ж��ַ�ch�Ƿ�Ϊ������ 
        {
            if((ch=='+')||(ch=='-')||(ch=='*')||(ch=='/')||(ch=='=')||(ch=='(')||(ch==')'))
            return true;
            else
            return false;
        }  
        static int in(char e) 
        { 
            if(e=='-' || e=='+') return 3; 
            if(e=='*' || e=='/') return 5; 
			if(e=='=')return 0;
			if(e==')')return 8;
			if(e=='(')return 1;
			
        } 
        static int out(char e)
        { 
            if(e=='-' || e=='+') return 2; 
            if(e=='*' || e=='/') return 4;
			if(e=='=')return 0;
			if(e==')')return 1;
			if(e=='(')return 8;


        }   
        static char Precede(char theta1,char theta2)//�жϲ����������ȼ� 
        {
		    if((theta1=='('&&theta2==')')||(theta1=='='&&theta2=='='))
               return '=';
            if((theta1==')'&&theta2=='(')||(theta1=='('&&theta2=='=')||(theta1=='='&&theta2==')'))
               return 'e';
            if(in(theta1)>out(theta2))
               return '>';
            if(in(theta1)<out(theta2))
               return '<';
            
         }         
        static double Operate(double left,char theta,double right)//ִ������left theta right
        {
            double sum; 
            if(theta=='+') sum=left+right; 
            if(theta=='-') sum=left-right; 
            if(theta=='*') sum=left*right; 
            if(theta=='/') sum=left/right; 
            return sum;
        }    
        static void Get2Operands(LStack<double> &opnd,double &left, double &right)
        {
            opnd.pop(right);
            opnd.pop(left);
        }    
    public:
        Calculator(){};
        static void Run();
};       
void Calculator::Run()
{
    LStack<double> opnd;
    LStack<char> optr;
    optr.push('=');//���ڷ���ջ����ѹ�롮=��
    char ch;
    char optrtop;
    double operand;
    char theta;
   // char preoptr;//ǰһ���ַ���������� 
    cout <<"��������ı��ʽ(�ԡ�=������):" << endl; 
    cin >> ch;
	//optr.topValue(optrtop);
    while ((optr.topValue(optrtop),optrtop!='=')||ch!='=')
    {
        if(!IsOperator(ch))//���ǲ�����        
        {
            cin.putback(ch);
            cin >> operand;
            opnd.push(operand);
            cin >> ch;
        }        
        else
        {
			switch(Precede(optrtop,ch))
			{
			      case '<':         //ջ���Ĳ������ȼ��� 
                    optr.push(ch);   //������ȡ��һ���ַ� 
                    cin >> ch;
                    break;   
                  case'=':            //ջ���Ĳ������ȼ���ch�����ȼ���� 
                    optr.pop(optrtop); //������ 
                    cin >> ch;
					break;    
			      case'>':      //ջ���Ĳ������ȼ��� 
                    double left,right,result;
                    Get2Operands(opnd,left,right);//ȡ������������ 
                    optr.pop(theta);      //optr�˳�theta 
                    result=Operate(left,theta,right);
                    opnd.push(result);//��������ջ
					break;
                  case 'e':
                    cout << "������ƥ�����"<< endl;
					exit(2);
             }            
         }
		optr.topValue(optrtop);
		opnd.topValue(operand);
     }
     opnd.topValue(operand);
     cout << operand << endl;
     cout <<"���ʽ��ֵΪ" << operand << endl;    
}        
int main()
{

     Calculator A;
     A.Run();
     system("pause");
     return 0;                                
}        
