#include<stdio.h>
#include<stdlib.h>
int greedy(int *x,int k,int n)
{
    int sum=0,s=0;
    for(int j=0;j<k;j++)
    {
         if(x[j]>n)
        {
            printf("No Solution!\n");
            return -1;
        } 
    }       
    for(int i=0;i<k;i++)
   {
        s+=x[i];
        if(s>n)
       {
           sum++;
           s=x[i];
       }
   }
    return sum;    
}

int main()
{
    int dis=0;//�����Ϳ���ʻ��� 
    int sta=0;//�ܼ���վ��
    printf("����������ͺ����ʻ��̣�\n");
    scanf("%d",&dis);
    printf("�������ܼ���վ����\n");
    scanf("%d",&sta);
    int a[sta+1];
    printf("������������վ֮��ľ��룺\n");
    for(int i=0;i<sta+1;i++)
    scanf("%d",&a[i]);
    printf("���ټ��ʹ���Ϊ��%d\n",greedy(a,sta+1,dis));
    system("pause");
    return 0;
}    
