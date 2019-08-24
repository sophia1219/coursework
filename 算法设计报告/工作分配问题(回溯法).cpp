#include<stdio.h>
#include<stdlib.h>
int c[21][21];
int x[21];        //��¼��ǰ������
int bestx[21];    //��¼���ŷ���ʱ��һ������
int besttime;     //��¼���ŵķ�ʱ
int ctime;       //��ʾ��ǰ�ķ�ʱ
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
 printf("�����빤��������\n");
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
  printf("��С�ܷ���Ϊ��%d\n",besttime);
 }
 system("pause"); 
 return 0;
}
