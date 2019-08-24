#include<stdio.h>
#include<stdlib.h>
int c[21][21];
int x[21];        //记录当前的排列
int bestx[21];    //记录最优费用时的一个排列
int besttime;     //记录最优的费时
int ctime;       //表示当前的费时
void swap(int &x,int &y)
{
 int temp;
 temp=x;
 x=y;
 y=temp;
}
void backtrack(int n,int t)
{
 int i;
 if(t>n)
 {
  if(ctime<besttime)
  {
   for(i=1;i<=n;i++)
    bestx[i]=x[i];
   besttime=ctime;
  }
       return;
 }
 for(i=t;i<=n;i++)
 {
  swap(x[t],x[i]);
  ctime+=c[x[t]][t];
  if(ctime<besttime)  
  backtrack(n,t+1);
  ctime-=c[x[t]][t];
  swap(x[t],x[i]);
 }
}
int main()
{
 int n;
 printf("请输入工作数量：\n");
 while(scanf("%d",&n)!=EOF)
 {
  besttime=10000;
  for(int i=1;i<=n;i++)
  {  
    x[i]=i;
    for(int j=1;j<=n;j++)
    scanf("%d",&c[i][j]);
  }
  backtrack(n,1);
  printf("最小总费用为：%d\n",besttime);
 }
 system("pause"); 
 return 0;
}
