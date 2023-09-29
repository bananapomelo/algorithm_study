#include "graph.h"

int main()
{
	Graph* g = Create_Graph();
	Print_Graph(g);
	DFS_Traver(g);
	BFS(g);
	Dijstra(g,0);
}
