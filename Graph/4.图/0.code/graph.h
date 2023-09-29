#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERY_BIG 65536

/*类型结构*/
typedef char Vtype;//图中顶点元素的类型
typedef int  Adjtype;//边上权的类型 

#define MAXN 100 //图中顶点的最大个数 

typedef struct //描述图 "邻接矩阵"
{
  Vtype V[MAXN];//一维数组用来保存图中的顶点
  Adjtype A[MAXN][MAXN];//二维数组，“邻接矩阵”，存储“边”
  
  int vexnum;//图中有效顶点的个数
  int arcnum;//图中边的条数
	//....
}Graph;

/*函数声明*/
Graph* Create_Graph(void);
void Print_Graph(Graph* g);
void DFS_Traver(Graph* g);
void BFS(Graph* g);
void Dijstra(Graph* g,int V0);


#endif  
