#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#define MAX_VERTEX_NUM 30
#define ERROR 0
#define OK 1
typedef struct ArcNode{                          //ͼ���ڽӱ�洢�ṹ
	int adjvex;
	struct ArcNode *nextarc;
	int *info;                                   
}ArcNode;
typedef struct VNode{
	char data;                                   //������Ϣ
	ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct{
	AdjList vertices;
	int vexnum,arcnum;
}ALGraph;                                        //����ͼ
typedef struct{                                  //����ջ
	int *base;
	int *top;
	int  stacksize;
}SqStack;
int InitStack(SqStack &S)                        //��ʼ��ջ
{
	S.base=(int*)malloc(MAX_VERTEX_NUM*sizeof(int));
	if(!S.base) exit(-1);
	S.top=S.base;
	S.stacksize=MAX_VERTEX_NUM;
	return OK;
}
int Push(SqStack &S,int e)                       //ѹջ
{   
	*S.top++=e;
	return OK;
}
int Pop(SqStack &S,int &e)                       //��ջ
{   
	if(S.top==S.base) return ERROR;
	e=* --S.top;
	return OK;
}
bool StackEmpty(SqStack &S)                      //�ж�ջ�Ƿ�Ϊ�գ���Ϊ���򷵻�1�����򷵻�0
{
	if(S.top==S.base) return 1;
	else return 0;
}
void CreateGraph(ALGraph &G)                     //�ڽӱ���ͼ
{
    int i,j,k,m;
	char x,y,z;
	ArcNode *P;
	P=NULL;
	printf("���붥����:");
	scanf("%d",&G.vexnum);
	printf("���뻡��:");
	scanf("%d",&G.arcnum);
	while(G.arcnum>G.vexnum*(G.vexnum-1)/2)
	{
		printf("���뻡����������������!\n");
		scanf("%d",&G.arcnum);
	}
	printf("���붥������:");
	for(i=0;i<G.vexnum;i++)
	{
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc=NULL;
	}
	printf("���뻡����Ȩֵ:");
	printf("\n");
    for(i=0;i<G.arcnum;i++)
	{
		j=k=-1;
		P=(ArcNode*)malloc(sizeof(ArcNode));
		P->info=(int *)malloc(sizeof(int));        //�����ڴ�ռ�
		cin>>x>>z>>y>>z>>*P->info;
		for(m=0;m<G.vexnum;m++)
		{
			if(x==G.vertices[m].data) j=m;
			if(y==G.vertices[m].data) k=m;
		}
		if(j==-1||k==-1)
		{
			printf("���붥������������������!\n");
			i--;
		}
		else{
		P->adjvex=k;                               //�����������һ����
		P->nextarc=G.vertices[j].firstarc;
		G.vertices[j].firstarc=P;}
	}
}
void FindInDegree(ALGraph G,int indegree[MAX_VERTEX_NUM])//������Ŷ�����ȵ�����
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
int ve[MAX_VERTEX_NUM]={0};                         //ve��Ÿ������¼�������ʱ��
SqStack T;                                          //�������ж���ջ����ջ�׵�ջ��Ϊ�����������źõĶ���
int TopologicalOrder(ALGraph G,SqStack &T)
{
	int i,k,count=0;                                //count������¼��������������������Ķ���ĸ���
    int indegree[MAX_VERTEX_NUM]={0};
	SqStack S;                                      //SΪ����ȶ���ջ
	ArcNode *P;
	P=(ArcNode*)malloc(sizeof(ArcNode));
	FindInDegree(G,indegree);
	InitStack(S);
	InitStack(T);
	for(i=0;i<G.vexnum;i++)
	     if(!indegree[i]) Push(S,i);                //���Ƚ����Ϊ��Ķ�����ջ
	if(StackEmpty(S))                               //�����ʱջΪ�գ���˵�����̲��ɽ���  
	{
		printf("��Ŀ���ɽ���!\n");
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
            if(!(--indegree[k])) Push(S,k);         //����β�������ȼ�һ������ʱ�����Ϊ�㣬����ջ
			if(ve[i]+*(P->info)>ve[k]) ve[k]=ve[i]+*(P->info);//��ve(k)=Max{ve(i)+dut(<i,k>)}��ve(k)
		}		  
	}
	if (count<G.vexnum)                             //countС�ڶ�����������˵��ͼ�д��ڻ������̲��ɽ���
	{
		printf("��Ŀ���ɽ���!\n");
		return ERROR;
	}
    else 
	{
		printf("��Ŀ�ɽ���!\n");
		return OK;
	}
}
int vl[MAX_VERTEX_NUM];                            //vl��Ÿ������¼������ʱ��
int CriticalPath(ALGraph G)
{
	int i,k,dut,t;
	int ee,el;
	if(!TopologicalOrder(G,T)) return ERROR;
	Pop(T,t);                                      //��t��ʱ����������������һ��������G.vertices[]�е�λ��
	for(i=0;i<G.vexnum;i++)
		vl[i]=ve[t];                               //��ʼ��vl���飬��ÿһ��Ԫ�ظ�ֵΪ�������������һ����������¼������緢��ʱ��
	Push(T,t);                                     //�ٽ�tѹ��ջ��
	ArcNode *P;
	P=(ArcNode*)malloc(sizeof(ArcNode));
    while(!StackEmpty(T))
        for(Pop(T,i),P=G.vertices[i].firstarc;P;P=P->nextarc)
		{
			k=P->adjvex;
            dut=*(P->info);
			if(vl[k]-dut<vl[i]) vl[i]=vl[k]-dut;    //��vl(i)=Min{vl(i)-dut(<i,k>)}��vl(i)
		}
	printf("�����������Ŀ������Ҫ��ʱ��:%d\n",ve[t]);//���һ����������緢ʱ�伴Ϊ�ù��������������ʱ��
	for(i=0;i<G.vexnum;i++)
		{
			for(P=G.vertices[i].firstarc;P;P=P->nextarc)
			{
				k=P->adjvex;
				dut=*(P->info);
				ee=ve[i];
				el=vl[k]-dut;
				if(ee==el)                           //���ĳ��������緢��ʱ���������ʱ����ȣ���˻Ϊ�ؼ��
				{
					printf("�ؼ��:<%c,%c>\n",G.vertices[i].data,G.vertices[k].data);
					printf("�˹ؼ������������������:%c,%c\n",G.vertices[i].data,G.vertices[k].data);
					printf("�˹ؼ��������(��)����ʱ��:%d\n",ee);
				}
			}
		}
	return OK;
}
int main()
{
	int choice;
	printf("ѡ��\n");
	printf("0:�˳� 1:������Ŀ 2:������Ļ\n");
	printf("���������ѡ��:");
	scanf("%d",&choice);
	switch (choice)
	{
	case 0:return 0;break;
	case 1:printf("�봴��һ����Ŀ��\n");
           ALGraph G;
	       CreateGraph(G);
       	   CriticalPath(G);
	       break;
    case 2:system("cls");
	system("pause");
    return 0; 
	}
}


