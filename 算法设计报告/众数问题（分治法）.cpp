#include<stdio.h>
#include<iostream>  
  
using namespace std;  
//�ṹ����������������Ԫ��������  
typedef struct  
{  
    int value;//Ԫ��  
    int count;//����  
}num;  
//��¼��λ������ʼ�±�  
typedef struct  
{  
    int low;  
    int high;  
}node;  
//����  
num x;  
//int data=1;  
int Swap(int &a,int &b)
{
    int temp=a;
    a=b;
    b=temp;
}
    
int Partition(int a[],int p,int r)   //���� 
{
    int i=p;
    int j=r+1;
    int x=a[p];
    //��С��x��Ԫ�ؽ�����������򣬽�����x��Ԫ�ؽ������ұ�����
    while(true)
    {
        while(a[++i]<x&&i<r);
        while(a[--j]>x);
        if(i>=j)
        break;
        Swap(a[i],a[j]);
    }
    a[p]=a[j];
    a[j]=x;
    return j;
}         

int QuickSort(int a[],int p,int r)//�������� 
{
    if(p<r)
    {
        int q=Partition(a,p,r);
        QuickSort(a,p,q-1); //���������� 
        QuickSort(a,q+1,r); //���Ұ������ 
    }
}            
//��λ��  
int madian(int *a,int l,int r)  
{  
    int x=r+l+1;  
    return a[x/2];//Ϊ����ʱ  
}  
//������λ������ʼ��  
node spalit(int *a,int med,int l,int r)  
{  
    node m;  
    m.low=l;
    m.high=r;  
    for(int i=0;i<=r;i++)  
    {  
       if(med==a[i])  
        {  
           m.low=i;  
            break;  
      }  
   }  
   for(int j=r;j>=0;j--)  
   {  
       if(med==a[j])  
        {  
           m.high=j;  
            break;  
        }  
    }  
    return m;  
}  
//������������ȡ  
void mode(int *a,int l,int r)  
{  
      
    if(l>=r)
    return;   
   else  
    {  
       node n;  
          int temp=0;  
        int med;  
       med=madian(a,l,r);  
        n=spalit(a,med,l,r);  
        temp=n.high-n.low+1;  
       if(x.count<temp)  
       {  
           x.value=med;  
           x.count=temp;  
       }  
        if(n.low-l>temp)  
       {  
           if(x.count<temp)  
           {  
               x.value=med;  
               x.count=temp;  
            }  
            mode(a,l,n.low-1);  
        }  
        if(r-n.high>temp)  
       {  
            if(x.count<temp)  
            {  
                x.value=med;  
                x.count=temp;  
            }  
            mode(a,n.high+1,r);  
        }  
    }  
}  
int main()  
{  
    x.count=0;  
    int n;  
    int *a;  
    cout<<"���������ĸ�����";
    cin>>n; 
    for(int i=0;i<n;i++)  
    {  
    cin>>a[i];  
    }  
    QuickSort(a,0,n-1);  
    mode(a,0,n-1);
    if(x.count==1)
    cout<<"���ؼ�������"<<endl;
    else  
    cout<<"����Ϊ��"<<x.value<<"\n"<<"����Ϊ��"<<x.count<<endl;  
    delete []a;
    system("pause");
    return 0;  
} 

