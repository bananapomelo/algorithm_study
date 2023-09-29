#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// 基于邻接矩阵实现无向图
typedef struct graphAdjMat {
    unsigned int *vertices; // 顶点列表
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
graphAdjMat *createGraph(int *vertices, int size, int capacity) {
    // 创建图结构体
    graphAdjMat *graph = (graphAdjMat *)malloc(sizeof(*graph));
    graph->vertices = (unsigned int *)malloc(sizeof(unsigned int) * capacity);
    graph->adjMat = (unsigned int **)malloc(sizeof(unsigned int *) * capacity);
    graph->size = size;
    graph->capacity = capacity;

    // 初始化大小为capacity的顶点列表
    memset(graph->vertices, 0, sizeof(unsigned int) * capacity);
    memcpy(graph->vertices, vertices, sizeof(unsigned int) * size);

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

    if (graph->adjMat) {
        free(graph->adjMat[0]);
        free(graph->adjMat); graph->adjMat = NULL;
    }
    if (graph->vertices) {
        free(graph->vertices); graph->vertices = NULL;
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
void addEdge(graphAdjMat *graph, int i, int j) {
    if (i < 0 || j < 0 || i >= graph->size || j >= graph->size || i == j) {
        printf("Out of range in %s: %d\n", __FUNCTION__, __LINE__);
        exit(1);
    }

    graph->adjMat[i][j] = 1;
    graph->adjMat[j][i] = 1;
    
    return ;
}

/*
    delEdge: 删除两顶点的边
        @graph: 图指针
        @i: 顶点
        @j: 顶点
        @retval: 空
*/
void delEdge(graphAdjMat *graph, int i, int j) {
    if (i < 0 || j < 0 || i >= graph->size || j >= graph->size || i == j) {
        printf("Out of range in %s: %d\n", __FUNCTION__, __LINE__);
        exit(1);
    }

    graph->adjMat[i][j] = 0;
    graph->adjMat[j][i] = 0;

    return ;
}

/*
    addVertices: 添加新顶点
        @graph: 图指针
        @i: 顶点值
        @retval: 空
*/
void addVertices(graphAdjMat *graph, int value) {
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
    unsigned int *vertices = (unsigned int *)malloc(sizeof(unsigned int) * graph->capacity); // 创建新的顶点列表
    memset(vertices, 0, sizeof(unsigned int) * graph->capacity); // 为新顶点列表赋初值
    memcpy(vertices, graph->vertices, sizeof(unsigned int) * graph->size); // 将原列表复制过来

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

/*
    delVertices: 删除节点
        @graph: 图指针
        @value: 顶点值
        @retval: 空
*/
void delVertices(graphAdjMat *graph, int value) {
    if (graph->size == 0) {
        printf("图中无节点, 无法继续删除\n");
        return ;
    }
    int index = -1;
    for (int i = 0; i < graph->size; i++) {
        if (graph->vertices[i] == value) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Not search %d vertices\n", value);
        return ;
    }

    // 删除顶点列表中的顶点
    for (int i = 0; i < graph->size - 1; i++) {
        if (i >= index) {
            graph->vertices[i] = graph->vertices[i + 1];
        }
    }
    graph->vertices[graph->size - 1] = 0; 

    // 删除邻接矩阵中顶点的列 
    for (int i = 0; i < graph->size; i++) {
        for (int j = 0; j < graph->size - 1; j++) {
            if (j >= index) {
                graph->adjMat[i][j] = graph->adjMat[i][j + 1];
            }
        }
        graph->adjMat[i][graph->size - 1] = 0;
    }
    // 删除邻接矩阵中顶点的列
    for (int i = 0; i < graph->size - 1; i++) {
        if (i >= index) {
            memcpy(graph->adjMat[i], graph->adjMat[i + 1], sizeof(unsigned int) * graph->size);
        }
    }
    memset(graph->adjMat[graph->size - 1], 0, sizeof(unsigned int) * graph->size);

    graph->size--;

    return ;
}

void printGraph(graphAdjMat *graph) {
    printf("顶点列表: \n[");
    for (int i = 0; i < graph->size; i++) {
        if (i != graph->size - 1) {
            printf("%u ", graph->vertices[i]);
        } else {
            printf("%u]\n\n", graph->vertices[i]);
        }
    }

    printf("邻接矩阵: \n[\n");
    for (int i = 0; i < graph->size; i++) {
        printf("[");
        for (int j = 0; j < graph->size; j++) {
            if (j != graph->size - 1) {
                printf("%d, ", graph->adjMat[i][j]);
            } else {
                printf("%d", graph->adjMat[i][j]);
            }
        }
        printf("]\n");
    }
    printf("]\n\n");

    return ;
}

int search(graphAdjMat *graph, int target) {
    for (int i = 0; i < graph->size; i++) {
        if (graph->vertices[i] == target)
            return i;
    }

}

int main()
{
    int vertices[] = {1, 2, 3, 4, 5};
    int size = sizeof(vertices) / sizeof(int);
    int capacity = size * 2;

    graphAdjMat *graph = createGraph(vertices, size, capacity);

    printf("size: %d\n\nn", graph->size);
    printf("capacity: %d\n\n", graph->capacity);
    // (1, 2), (1, 3), (1, 5), (2, 3), (2, 4), (2, 5), (4, 5)
    addEdge(graph, search(graph, 1), search(graph, 2));
    addEdge(graph, search(graph, 1), search(graph, 3));
    addEdge(graph, search(graph, 1), search(graph, 5));
    addEdge(graph, search(graph, 2), search(graph, 3));
    addEdge(graph, search(graph, 2), search(graph, 4));
    addEdge(graph, search(graph, 2), search(graph, 5));
    addEdge(graph, search(graph, 4), search(graph, 5));

    addVertices(graph, 6);
    addVertices(graph, 7);
    addVertices(graph, 8);
    addVertices(graph, 9);
    addVertices(graph, 10);
    addVertices(graph, 11);

    printf("size: %d\n\nn", graph->size);
    printf("capacity: %d\n\n", graph->capacity);
    printGraph(graph);

    delVertices(graph, 1);
    delVertices(graph, 2);
    delVertices(graph, 3);
    delVertices(graph, 4);
    delVertices(graph, 5);
    delVertices(graph, 6);
    delVertices(graph, 7);
    delVertices(graph, 8);
    delVertices(graph, 9);
    delVertices(graph, 10);
    delVertices(graph, 12);
    delVertices(graph, 11);
    delVertices(graph, 12);

    printf("size: %d\n\nn", graph->size);
    printf("capacity: %d\n\n", graph->capacity);
    printGraph(graph);

    freeGraph(graph);

    return 0;
}



