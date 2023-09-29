#include "graph.h"
#include "SeqQueue.h"
/*
	Get_Index:获取顶点下标
	如果不存在则返回-1
*/
int Get_Index(Graph* g,char v)
{
	int i;
	for(i=0;i<g->vexnum;i++)
	{
		if(g->V[i] == v)
		{
			return i;
		}
	}
	return -1;
}

/*
	根据用户输入 ABCD AB2 AC3 AD4 CD6 ##0
	创建一个图(邻接矩阵):Create_Graph
	@void
	返回值:
		Graph* 返回图的结构体指针
*/
Graph* Create_Graph(void)
{
	//1.初始化一个图的结构体
	Graph* g = malloc(sizeof(*g));
	g->arcnum = g->vexnum = 0;

	//2.输入顶点
	printf("请输入顶点的字符串:\n");
	scanf("%s",g->V);
	getchar();//吸收输入后按的回车符

	//g->v :ABCD\0
	g->vexnum = strlen(g->V);

	//3.输入顶点与顶点的关系比 如AB5
	//初始化邻接矩阵 让每个权都为无穷大
	int i,j;
	for(i=0;i<g->vexnum;i++)
	{
		for(j=0;j<g->vexnum;j++)
		{
			g->A[i][j]=VERY_BIG;
		}
	}
	//输入每条边的信息 输入##0 表示输入结束 AB5 
	printf("请输入各边的信息:\n");

	while(1)
	{
		//起始s  结束e
		char s,e;//用来保存起点 终点
		Adjtype w;
		scanf("%c%c%d",&s,&e,&w);
		getchar();
		if(s == '#') break;
		
		//获取顶点的下标
		i = Get_Index(g,s);
		j = Get_Index(g,e);

		if(i==-1 || j==-1)
		{
			printf("您输入错误 请重新输入\n");
			continue;
		}
		
		g->A[i][j]=w;
	}
	return g;
}

/*
	输出图 输出表格
*/
void Print_Graph(Graph* g)
{
	int i,j;
	if(NULL == g) return;
	printf("-------------------------------------\n");
	printf("\t");
	for(i=0;i<g->vexnum;i++)
	{
		printf("%c\t",g->V[i]);
	}
	printf("\n");
	for(i=0;i<g->vexnum;i++)
	{
		printf("%c\t",g->V[i]);
		for(j=0;j<g->vexnum;j++)
		{
			if(g->A[i][j]==VERY_BIG)
			{
				printf("∞\t");
			}
			else
			{
				printf("%d\t",g->A[i][j]);
			}
		}
		printf("\n");
	}
	printf("-------------------------------------\n");
}


/*
	取图g中的顶点v0的下一个邻接点(遍历二维数组的一行)
	@g:
	@v0:需要找下一个邻接点的顶点的下标
	@v:每次开始找的起点
	返回值
		返回下一个邻接点的下标 没有找到返回-1
*/
int Find_Next_Adj(Graph* g,int v0,int v)
{
	int i;
	for(i=v;i<g->vexnum;i++)
	{
		if(g->A[v0][i]!=VERY_BIG)
			return i;
	}
	return -1;
}

/*
	辅助数组
	int visited[MAXN] = {0};//每个顶点有没有被访问
	0 未被访问
	1 已被访问
*/
int visited[MAXN] = {0};

void DFS(Graph * g, int v0)
{
	printf("%c ",g->V[v0]);
	visited[v0]=1;//标记已被访问

	//找v0的第一个邻接点
	//找到了按照DFS遍历 返回之后 访问下一个邻接点 下一个邻接点从上一个邻接点的下一个开始
	int u;//记录v0的下一个邻接点
	for(u=Find_Next_Adj(g,v0,0);u!=-1;u=Find_Next_Adj(g,v0,u+1))//访问v0的所有的邻接点
	{
		if(visited[u]==0)
			DFS(g,u);
	}
}

/*按照DFS来遍历图*/
void DFS_Traver(Graph* g)
{
	printf("DFS: ");//DFS:A B C D
	int i;
	//为了防止多次使用 所以每次都需要把visted数组清0
	for(i=0;i<g->vexnum;i++)
	{
		visited[i]=0;
	}
	//适应非连通图 所以必须要从每一个顶点出发进行一遍DFS
	for(i=0;i<g->vexnum;i++)
	{
		if(visited[i]==0)
			DFS(g,i);
	}
	printf("\n");
}

// void BFS(Graph* g)
// {
// 	printf("BFS: ");
// 	//初始化visited
// 	int i;
// 	//为了防止多次使用 所以每次都需要把visted数组清0
// 	for(i=0;i<g->vexnum;i++)
// 	{
// 		visited[i]=0;
// 	}
// 	//初始化队列
// 	SqQueue*q = InitQueue(1024);
// 	//适应非连通图 所以必须要从每一个顶点出发进行一遍DFS
// 	for(i=0;i<g->vexnum;i++)
// 	{
// 		if(visited[i])
// 		continue;
// 		//1.先访问
// 		printf("%c ",g->V[i]);
// 		//2.标记
// 		visited[i]=1;
// 		//3.入队
// 		EnQueue(q,i);
// 		//4.访问v0的所有邻接点 直到队列为空为止
// 		while(!QueueIsEmpty(q))
// 		{
// 			//出队
// 			int v;
// 			DeQueue(q,&v);
// 			//让出队元素的所有的未被访问的邻接点入队
// 			int u;//记录v0的下一个邻接点
// 			for(u=Find_Next_Adj(g,v,0);u!=-1;u=Find_Next_Adj(g,v,u+1))//访问v0的所有的邻接点
// 			{
// 				if(visited[u]==0)
// 				{
// 					printf("%c ",g->V[u]);
// 					visited[u]=1;
// 					EnQueue(q,u);
// 				}
// 			}
// 		}
// 	}
// 	printf("\n");
// }

void BFS(Graph *graph) {
	printf("BFS: ");
	for (int i = 0; i < graph->vexnum; i++) {
		visited[i] = 0;
	}

	SqQueue *queue = InitQueue(1024);

	for (int vertex = 0; vertex < graph->vexnum; vertex++) {
		if (visited[vertex])
			continue;

		visited[vertex] = 1;
		printf("%c ", graph->V[vertex]);
		EnQueue(queue, vertex);

		while (!QueueIsEmpty(queue)) {
			int pop;
			DeQueue(queue, &pop);

			for (int i = Find_Next_Adj(graph, pop, 0); i != -1; i = Find_Next_Adj(graph, pop, i + 1)) {
				if (visited[i] == 0) {
					printf("%c ", graph->V[i]);
					visited[i] = 1;
					EnQueue(queue, i);
				}
			}
		}
	}
	putchar('\n');

	return ;
}

/*
	迪杰斯特拉算法
*/
//辅助向量
int S[MAXN];//标记V0到其他顶点的最短路径是不是已经求出
int dist[MAXN];//最短路径的距离
char path[MAXN][MAXN];//V->A->B V->C->A ....

/*
	Dijstra:使用迪杰斯特拉算法求最短路径
	@g:指向图
	@V0:源点的下标
	返回值:void 结果保存在辅助向量中
*/
void Dijstra(Graph* g,int V0)
{
	if(NULL == g) return ;
	//1.初始化辅助向量 
	int  i;
	for(i=0;i<g->vexnum;i++)
	{
		S[i] = 0;//开始的时候V0到各个顶点的最短路径未求出
		dist[i] = g->A[V0][i];//最短路径开始的初始化为V0各个顶点的直接距离
		memset(path[i],'\0',MAXN);
		path[i][0] = g->V[V0];//
		path[i][1] = g->V[i];//V->A->B 
	}
	//V0->V0  是已知的为无穷大 
	S[V0] = 1;
	int n = 0;
	while(++n<g->vexnum)//需要g->vexnum-1次 
	{
		/*2.1
		step1:
		显然,从源点V到其他顶点的第一条最短路径长度dist[u]
		dist[u]=min{dist[w]|w=0,1,2,..n-1且S[w]=0}
		表示在所有未求出最短路径中找出一条最短的，这条路径作为当前求出的最短路径。*/
		int min_dist = VERY_BIG; 
		int u;
		for(i=0;i<g->vexnum;i++)
		{
			if(S[i]==0)
			{
				if(dist[i]<min_dist)
				{
					min_dist = dist[i];
					u = i;//记录下标
				}
			}
		}
		//dist[u]就是最短路径 V[v0]->V[u] 的最短路径已求出 path[u]
		S[u] = 1;
		
		/*2.2
		step2:
		对所有的S[W]=0的顶点，更新dist[w]
		if dist[u]+<u,w> < dist[w]
			dist[W] = dist[u]+<u,w>
		*/
		for(i=0;i<g->vexnum;i++)
		{
			if(S[i]==0)
			{
				if(dist[u]+g->A[u][i] < dist[i])
				{
					dist[i] = dist[u]+g->A[u][i];
					//更新path VB    VA更新VAB
					//更新path VC   VC V->A->B 更新C V->A->B->C
					strcpy(path[i],path[u]);//VA  VAB
					path[i][strlen(path[i])] = g->V[i];//B VABC
				}
			}
		}
	}
	//输出打印 V->A[3]:V->A 
	for(i=0;i<g->vexnum;i++)
	{
		if(i==V0) continue;
		printf("%c->%c[%d]:",g->V[V0],g->V[i],dist[i]);

		//打印路径 遍历path[i]
		int j;
		for(j=0;j<strlen(path[i])-1;j++)
		{
			printf("%c->",path[i][j]);//V->A-> 最后一个字符单独处理
		}
		printf("%c\n",path[i][j]);
	}
}


/*
	Prim: 在图g中，找到有begin顶点出发的最小生成树
*/
void Prim(Graph *g, int begin)
{

	/*step1: 初始化close_edge数组*/
	for(int i=0;i<g->vexnum;i++)
	{
		close_edge[i].start = begin;
		close_edge[i].end = i;
		close_edge[i].weight = g->A[begin][i];
	}
	close_edge[begin].weight = -1;//表示begin已经在最小生成树中了

	for(int i=0;i<g->vexnum-1;i++)
	{
		/*step2: 筛选出最优顶点*/
		int min = VERY_BIG,index;
		for(int j=0;j<g->vexnum;j++)
		{
			if(close_edge[j].weight!=-1 && close_edge[j].weight <= min)
			{
				min = close_edge[j].weight;
				index = j;
			}
		}
		close_edge[index].weight = -1;

		/*step3: 用当前最优顶点到其他顶点的权去更新数组*/
		for(int j=0;j<g->vexnum;j++)
		{
			if(g->A[close_edge[index].end][j] < close_edge[j].weight)
			{
				close_edge[j].weight = g->A[close_edge[index].end][j];
				close_edge[j].start = close_edge[index].end;
				close_edge[j].end = j;
			}
		}
	}
}
