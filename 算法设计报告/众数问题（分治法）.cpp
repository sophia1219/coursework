#include<stdio.h>
#include<iostream>  
  
using namespace std;  
//结构体用来保存众数的元素与重数  
typedef struct  
{  
    int value;//元素  
    int count;//重数  
}num;  
//记录中位数的起始下标  
typedef struct  
{  
    int low;  
    int high;  
}node;  
//快排  
num x;  
//int data=1;  
int Swap(int &a,int &b)
{
    int temp=a;
    a=b;
    b=temp;
}
    
int Partition(int a[],int p,int r)   //划分 
{
    int i=p;
    int j=r+1;
    int x=a[p];
    //将小于x的元素交换到左边区域，将大于x的元素交换到右边区域
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

int QuickSort(int a[],int p,int r)//快速排序 
{
    if(p<r)
    {
        int q=Partition(a,p,r);
        QuickSort(a,p,q-1); //对左半段排序 
        QuickSort(a,q+1,r); //对右半段排序 
    }
}            
//中位数  
int madian(int *a,int l,int r)  
{  
    int x=r+l+1;  
    return a[x/2];//为奇数时  
}  
//返回中位数的起始点  
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
//众数的重数求取  
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
    cout<<"请输入数的个数：";
    cin>>n; 
    for(int i=0;i<n;i++)  
    {  
    cin>>a[i];  
    }  
    QuickSort(a,0,n-1);  
    mode(a,0,n-1);
    if(x.count==1)
    cout<<"多重集无众数"<<endl;
    else  
    cout<<"众数为："<<x.value<<"\n"<<"重数为："<<x.count<<endl;  
    delete []a;
    system("pause");
    return 0;  
} 

