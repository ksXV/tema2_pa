struct Graph {
    int vertexes;
    int edges;
    int **matrix;
};

struct Graph *makeGraph(int);
void connectVertexes(struct Graph *g, int i, int j);
void printGraph(struct Graph *g);
