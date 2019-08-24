#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#define MAX_VERTEX_NUM 30
#define ERROR 0
#define OK 1
typedef struct ArcNode{                          //图的邻接表存储结构
	int adjvex;
	struct ArcNode *nextarc;
	int *info;                                   
}ArcNode;
typedef struct VNode{
	char data;                                   //顶点信息
	ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct{
	AdjList vertices;
	int vexnum,arcnum;
}ALGraph;                                        //定义图
typedef struct{                                  //定义栈
	int *base;
	int *top;
	int  stacksize;
}SqStack;
int InitStack(SqStack &S)                        //初始化栈
{
	S.base=(int*)malloc(MAX_VERTEX_NUM*sizeof(int));
	if(!S.base) exit(-1);
	S.top=S.base;
	S.stacksize=MAX_VERTEX_NUM;
	return OK;
}
int Push(SqStack &S,int e)                       //压栈
{   
	*S.top++=e;
	return OK;
}
int Pop(SqStack &S,int &e)                       //出栈
{   
	if(S.top==S.base) return ERROR;
	e=* --S.top;
	return OK;
}
bool StackEmpty(SqStack &S)                      //判断栈是否为空，若为空则返回1，否则返回0
{
	if(S.top==S.base) return 1;
	else return 0;
}
void CreateGraph(ALGraph &G)                     //邻接表创建图
{
    int i,j,k,m;
	char x,y,z;
	ArcNode *P;
	P=NULL;
	printf("输入顶点数:");
	scanf("%d",&G.vexnum);
	printf("输入弧数:");
	scanf("%d",&G.arcnum);
	while(G.arcnum>G.vexnum*(G.vexnum-1)/2)
	{
		printf("输入弧数有误，请重新输入!\n");
		scanf("%d",&G.arcnum);
	}
	printf("输入顶点名称:");
	for(i=0;i<G.vexnum;i++)
	{
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc=NULL;
	}
	printf("输入弧及其权值:");
	printf("\n");
    for(i=0;i<G.arcnum;i++)
	{
		j=k=-1;
		P=(ArcNode*)malloc(sizeof(ArcNode));
		P->info=(int *)malloc(sizeof(int));        //分配内存空间
		cin>>x>>z>>y>>z>>*P->info;
		for(m=0;m<G.vexnum;m++)
		{
			if(x==G.vertices[m].data) j=m;
			if(y==G.vertices[m].data) k=m;
		}
		if(j==-1||k==-1)
		{
			printf("输入顶点名称有误，请重新输!\n");
			i--;
		}
		else{
		P->adjvex=k;                               //采用逆序插入一条弧
		P->nextarc=G.vertices[j].firstarc;
		G.vertices[j].firstarc=P;}
	}
}
void FindInDegree(ALGraph G,int indegree[MAX_VERTEX_NUM])//建立存放顶点入度的数组
{
	int i;
    ArcNode *P;
	P=(ArcNode*)malloc(sizeof(ArcNode));
	for(i=0;i<G.vexnum;i++)
	{
		for(P=G.vertices[i].firstarc;P;P=P->nextarc)
		{
            indegree[P->adjvex]++;
		}
	}
}
int ve[MAX_VERTEX_NUM]={0};                         //ve存放各顶点事件的最早时间
SqStack T;                                          //拓扑序列顶点栈，从栈底到栈顶为按拓扑序列排好的顶点
int TopologicalOrder(ALGraph G,SqStack &T)
{
	int i,k,count=0;                                //count用来记录拓扑排序过程所遍历到的顶点的个数
    int indegree[MAX_VERTEX_NUM]={0};
	SqStack S;                                      //S为零入度顶点栈
	ArcNode *P;
	P=(ArcNode*)malloc(sizeof(ArcNode));
	FindInDegree(G,indegree);
	InitStack(S);
	InitStack(T);
	for(i=0;i<G.vexnum;i++)
	     if(!indegree[i]) Push(S,i);                //首先将入度为零的顶点入栈
	if(StackEmpty(S))                               //如果此时栈为空，则说明工程不可进行  
	{
		printf("项目不可进行!\n");
		return ERROR;
	}   	
	while(!StackEmpty(S))
	{
		Pop(S,i);
		Push(T,i);
		count++;
        for(P=G.vertices[i].firstarc;P;P=P->nextarc)
		{
			k=P->adjvex;
            if(!(--indegree[k])) Push(S,k);         //将弧尾顶点的入度减一，若此时其入度为零，则入栈
			if(ve[i]+*(P->info)>ve[k]) ve[k]=ve[i]+*(P->info);//按ve(k)=Max{ve(i)+dut(<i,k>)}求ve(k)
		}		  
	}
	if (count<G.vexnum)                             //count小于顶点总数，则说明图中存在环，工程不可进行
	{
		printf("项目不可进行!\n");
		return ERROR;
	}
    else 
	{
		printf("项目可进行!\n");
		return OK;
	}
}
int vl[MAX_VERTEX_NUM];                            //vl存放各顶点事件的最迟时间
int CriticalPath(ALGraph G)
{
	int i,k,dut,t;
	int ee,el;
	if(!TopologicalOrder(G,T)) return ERROR;
	Pop(T,t);                                      //用t暂时存放拓扑排序中最后一个顶点在G.vertices[]中的位置
	for(i=0;i<G.vexnum;i++)
		vl[i]=ve[t];                               //初始化vl数组，将每一个元素赋值为拓扑排序中最后一个顶点代表事件的最早发生时间
	Push(T,t);                                     //再将t压入栈中
	ArcNode *P;
	P=(ArcNode*)malloc(sizeof(ArcNode));
    while(!StackEmpty(T))
        for(Pop(T,i),P=G.vertices[i].firstarc;P;P=P->nextarc)
		{
			k=P->adjvex;
            dut=*(P->info);
			if(vl[k]-dut<vl[i]) vl[i]=vl[k]-dut;    //按vl(i)=Min{vl(i)-dut(<i,k>)}求vl(i)
		}
	printf("完成整整个项目至少需要的时间:%d\n",ve[t]);//最后一个顶点的最早发时间即为该工程完成所需的最短时间
	for(i=0;i<G.vexnum;i++)
		{
			for(P=G.vertices[i].firstarc;P;P=P->nextarc)
			{
				k=P->adjvex;
				dut=*(P->info);
				ee=ve[i];
				el=vl[k]-dut;
				if(ee==el)                           //如果某个活动的最早发生时间和最晚发生时间相等，则此活动为关键活动
				{
					printf("关键活动:<%c,%c>\n",G.vertices[i].data,G.vertices[k].data);
					printf("此关键活动所依附的两个顶点:%c,%c\n",G.vertices[i].data,G.vertices[k].data);
					printf("此关键活动的最早(晚)发生时间:%d\n",ee);
				}
			}
		}
	return OK;
}
int main()
{
	int choice;
	printf("选项\n");
	printf("0:退出 1:创建项目 2:清理屏幕\n");
	printf("请输入你的选择:");
	scanf("%d",&choice);
	switch (choice)
	{
	case 0:return 0;break;
	case 1:printf("请创建一个项目：\n");
           ALGraph G;
	       CreateGraph(G);
       	   CriticalPath(G);
	       break;
    case 2:system("cls");
	system("pause");
    return 0; 
	}
}


