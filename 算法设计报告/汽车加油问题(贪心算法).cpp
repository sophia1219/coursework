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
    int dis=0;//加满油可行驶里程 
    int sta=0;//总加油站数
    printf("请输入加满油后可行驶里程：\n");
    scanf("%d",&dis);
    printf("请输入总加油站数：\n");
    scanf("%d",&sta);
    int a[sta+1];
    printf("请逐个输入加油站之间的距离：\n");
    for(int i=0;i<sta+1;i++)
    scanf("%d",&a[i]);
    printf("最少加油次数为：%d\n",greedy(a,sta+1,dis));
    system("pause");
    return 0;
}    
