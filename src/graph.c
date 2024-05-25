#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

struct Graph *makeGraph(int vertexes)  {
    struct Graph *g = calloc(sizeof(struct Graph), 1);
    assert(g != NULL);
    g->vertexes = vertexes;
    g->matrix = calloc(sizeof(int *), vertexes);
    assert(g->matrix != NULL);
    for (int i = 0; i < vertexes; ++i) {
        g->matrix[i] = calloc(sizeof(int), vertexes);
        assert(g->matrix[i] != NULL);
    }
    
    return g;
}

void connectVertexes(struct Graph *g, int i, int j) {
    assert(g != NULL);
    assert(g->matrix != NULL);
    assert(i < g->vertexes && j < g->vertexes && i >= 0 && j >= 0);
    assert(g->matrix[i] != NULL);
    if (g->matrix[i][j] == 0) {
        g->matrix[i][j] = 1;
        g->edges++;
    }
}

void printGraph(struct Graph *g) {
    assert(g != NULL);
    assert(g->matrix != NULL);
    for (int i = 0; i < g->vertexes; i++) {
        assert(g->matrix[i] != NULL);
        for (int j = 0; j < g->vertexes; j++) {
            printf("%d ", g->matrix[i][j]);
        }
        putchar('\n');
    }
}
