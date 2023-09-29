#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// 基于邻接矩阵实现无向图
typedef struct graphAdjMat {
    char *vertices; // 顶点列表
    unsigned int **adjMat; // 邻接矩阵
    int size; // 顶点数量
    int capacity; // 图容量
} graphAdjMat;

/*
    createGraph: 创建一个图结构体
        @vertices: 顶点数组
        @size: 顶点个数
        @capacity: 图容积
        @retval: 图结构体指针
*/
graphAdjMat *createGraph(char *vertices, int size, int capacity) {
    // 创建图结构体
    graphAdjMat *graph = (graphAdjMat *)malloc(sizeof(*graph));
    graph->vertices = (char *)malloc(sizeof(char) * capacity);
    graph->adjMat = (unsigned int **)malloc(sizeof(unsigned int *) * capacity);
    graph->size = size;
    graph->capacity = capacity;

    // 初始化大小为capacity的顶点列表
    memset(graph->vertices, 0, sizeof(char) * capacity);
    memcpy(graph->vertices, vertices, sizeof(char) * size);

    // 初始化大小为 capacity * capacity 的邻接矩阵
    unsigned int *temp = (unsigned int *)malloc(sizeof(unsigned int) * capacity * capacity);
    memset(temp, 0, sizeof(unsigned int) * capacity * capacity);
    for (int i = 0; i < capacity; i++) {
        graph->adjMat[i] = temp + i * capacity;
    }

    return graph;
}

/*
    freeGraph: 释放图
        @graph: 图指针
        @retval: 空
*/
void freeGraph(graphAdjMat *graph) {
    assert(graph);

    if (graph->vertices) {
        free(graph->vertices); graph->vertices = NULL;
    }   
    if (graph->adjMat) {
        free(graph->adjMat[0]);
        free(graph->adjMat); graph->adjMat = NULL;
    }
    free(graph); graph = NULL;

    return ;
}

/*
    addEdge: 为两顶点添加的边
        @graph: 图指针
        @i: 顶点
        @j: 顶点
        @retval: 空
*/
void addEdge(graphAdjMat *graph, int i, int j, int weight) {
    if (i < 0 || j < 0 || i >= graph->size || j >= graph->size || i == j) {
        printf("Out of range in %s: %d\n", __FUNCTION__, __LINE__);
        exit(1);
    }

    graph->adjMat[i][j] = weight;

    return ;
}

/*
    addVertices: 添加新顶点
        @graph: 图指针
        @i: 顶点值
        @retval: 空
*/
void addVertices(graphAdjMat *graph, char value) {
    // 没有超过最大容量, 可以直接添加顶点
    if (graph->size < graph->capacity) {
        graph->vertices[graph->size] = value;

        // 为新增列赋初值
        for (int i = 0; i < graph->size; i++) {
            graph->adjMat[i][graph->size] = 0;
        }
        // 为新增行赋初值
        memset(graph->adjMat[graph->size], 0, sizeof(unsigned int) * graph->size + 1);
        graph->size += 1;
        
        return ;
    }

    // 扩容
    // 为顶点列表扩容
    graph->capacity = graph->capacity * 2;
    char *vertices = (char *)malloc(sizeof(char) * graph->capacity); // 创建新的顶点列表
    memset(vertices, 0, sizeof(char) * graph->capacity); // 为新顶点列表赋初值
    memcpy(vertices, graph->vertices, sizeof(char) * graph->size); // 将原列表复制过来

    free(graph->vertices);
    graph->vertices = vertices; // 顶点列表指针指向扩容后顶点列表
    graph->vertices[graph->size] = value;
    // for (int i = 0; i <= graph->size; i++) {
    //     printf("%d ", graph->vertices[i]);
    // }
    // putchar('\n');

    // 为邻接矩阵扩容
    unsigned int **adjMat = (unsigned int **)malloc(sizeof(unsigned int *) * graph->capacity); // 创建新的邻接矩阵
    unsigned int *temp = (unsigned int *)malloc(sizeof(unsigned int) * graph->capacity * graph->capacity); // 创建新的连续空间
    memset(temp, 0, sizeof(unsigned int) * graph->capacity * graph->capacity); // 为连续空间赋初值
    for (int i = 0; i < graph->capacity; i++) {
        adjMat[i] = temp + i * graph->capacity; // 二维指针指向连续空间
    }
    
    for (int i = 0; i < graph->size; i++) {
        memcpy(adjMat[i], graph->adjMat[i], sizeof(unsigned int) * graph->size); // 将院邻接矩阵值赋值给新邻接矩阵
    }

    for (int i = 0; i < graph->size; i++) {
        adjMat[i][graph->size + 1] = 0; // 为新顶点的列赋初值
    }

    memset(adjMat[graph->size + 1], 0, sizeof(unsigned int) * graph->capacity); // 为新顶点的行赋初值

    free(graph->adjMat[0]);
    free(graph->adjMat);
    graph->adjMat = adjMat; // 图的邻接矩阵指针指向扩容后邻接矩阵

    graph->size++;
    
    return ;
}


void printGraph(graphAdjMat *graph) {
    printf("顶点列表: \n[");
    for (int i = 0; i < graph->size; i++) {
        if (i != graph->size - 1) {
            printf("%c, ", graph->vertices[i]);
        } else {
            printf("%c]\n\n", graph->vertices[i]);
        }
    }

    printf("邻接矩阵: \n[\n");
    for (int i = 0; i < graph->size; i++) {
        printf("[");
        for (int j = 0; j < graph->size; j++) {
            if (j != graph->size - 1) {
                printf("%2d,", graph->adjMat[i][j]);
            } else {
                printf("%2d", graph->adjMat[i][j]);
            }
        }
        printf("]\n");
    }
    printf("]\n\n");

    return ;
}

int search(graphAdjMat *graph, char target) {
    for (int i = 0; i < graph->size; i++) {
        if (graph->vertices[i] == target)
            return i;
    }

}

int main()
{
    char vertices[] = {'a', 'b', 'c', 'd', 'e'};
    int size = sizeof(vertices) / sizeof(char);
    int capacity = size * 2;

    graphAdjMat *graph = createGraph(vertices, size, capacity);

    printf("size: %d\n\nn", graph->size);
    printf("capacity: %d\n\n", graph->capacity);

    addVertices(graph, 'f');
    addVertices(graph, 'g');


    addEdge(graph, search(graph, 'a'), search(graph, 'b'), 15);
    addEdge(graph, search(graph, 'a'), search(graph, 'c'), 2);
    addEdge(graph, search(graph, 'a'), search(graph, 'd'), 12);
    addEdge(graph, search(graph, 'b'), search(graph, 'e'), 6);
    addEdge(graph, search(graph, 'c'), search(graph, 'e'), 8);
    addEdge(graph, search(graph, 'c'), search(graph, 'f'), 4);
    addEdge(graph, search(graph, 'd'), search(graph, 'g'), 3);
    addEdge(graph, search(graph, 'e'), search(graph, 'g'), 9);
    addEdge(graph, search(graph, 'f'), search(graph, 'd'), 5);
    addEdge(graph, search(graph, 'f'), search(graph, 'g'), 10);
    addEdge(graph, search(graph, 'g'), search(graph, 'b'), 4);


    printf("size: %d\n\nn", graph->size);
    printf("capacity: %d\n\n", graph->capacity);
    
    printGraph(graph);

    freeGraph(graph);

    return 0;
}



