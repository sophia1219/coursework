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
        static bool IsOperator(char ch)//判断字符ch是否为操作符 
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
        static char Precede(char theta1,char theta2)//判断操作符的优先级 
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
        static double Operate(double left,char theta,double right)//执行运算left theta right
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
    optr.push('=');//先在符号栈里面压入‘=’
    char ch;
    char optrtop;
    double operand;
    char theta;
   // char preoptr;//前一个字符（运算符） 
    cout <<"请输入你的表达式(以“=”结束):" << endl; 
    cin >> ch;
	//optr.topValue(optrtop);
    while ((optr.topValue(optrtop),optrtop!='=')||ch!='=')
    {
        if(!IsOperator(ch))//不是操作符        
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
			      case '<':         //栈顶的操作优先级低 
                    optr.push(ch);   //继续读取下一个字符 
                    cin >> ch;
                    break;   
                  case'=':            //栈顶的操作优先级与ch的优先级相等 
                    optr.pop(optrtop); //脱括号 
                    cin >> ch;
					break;    
			      case'>':      //栈顶的操作优先级搞 
                    double left,right,result;
                    Get2Operands(opnd,left,right);//取出两个操作数 
                    optr.pop(theta);      //optr退出theta 
                    result=Operate(left,theta,right);
                    opnd.push(result);//运算结果入栈
					break;
                  case 'e':
                    cout << "操作符匹配错误"<< endl;
					exit(2);
             }            
         }
		optr.topValue(optrtop);
		opnd.topValue(operand);
     }
     opnd.topValue(operand);
     cout << operand << endl;
     cout <<"表达式的值为" << operand << endl;    
}        
int main()
{

     Calculator A;
     A.Run();
     system("pause");
     return 0;                                
}        
