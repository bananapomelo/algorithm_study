#include "graph.h"

int main()
{
	Graph* g = Create_Graph();
	Print_Graph(g);
	DFS_Traver(g);
	BFS(g);
	Dijstra(g,0);

	printf("最小生成树的路径以及权值为:\n");
	Prim(g,0);
	char flag=g->V[0];
	for(int i=1;i<g->vexnum;i++){
		for(int j=1;j<g->vexnum;j++){
			if(g->V[close_edge[j].start]==flag){
				char Start = g->V[close_edge[j].start];
				char End = g->V[close_edge[j].end];
				int Weight = g->A[close_edge[j].start][close_edge[j].end];

				printf("%c->%c:[%d]\n",Start,End,Weight);

				flag=g->V[close_edge[j].end];
				break;
			}
		}
	}
}
