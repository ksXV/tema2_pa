#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "queue.h"
#include "graph.h"
#include "team.h"

#define GET_TEAM(DATA) ((struct Team *) DATA)
#define FREE_TEAM(team) {                           \
            __auto_type t = GET_TEAM(team);         \
            if (t->name) free(t->name);             \
            free(t);                                \
}

bool compareTeams(struct Team *teamOne, struct Team *teamTwo) {
    assert(teamOne != NULL && teamTwo != NULL);
    if (teamOne->points != teamTwo->points) {
        return teamOne->points > teamTwo->points;
    } else {
        return strcmp(teamOne->name, teamTwo->name) > 0;
    }
}

struct Graph *startMatches(struct Queue *teams, struct Queue *losers) {
    assert(teams != NULL);
    struct Graph *ranking = makeGraph(32);
    assert(ranking != NULL);

    struct Queue winners = {.head = NULL, .tail = NULL};
    
    while (!isQueueEmpty(teams)) {
        struct Node *firstTeam = dequeue(teams);
        struct Node *secondTeam = dequeue(teams);
        if (compareTeams(firstTeam->data, secondTeam->data)) {
            enqueue(&winners, firstTeam->data);
            connectVertexes(ranking, GET_TEAM(secondTeam->data)->position - 1, GET_TEAM(firstTeam->data)->position - 1);
            enqueue(losers, secondTeam->data);
            free(firstTeam);
            free(secondTeam);
        } else {
            enqueue(losers, firstTeam->data);
            connectVertexes(ranking, GET_TEAM(firstTeam->data)->position - 1, GET_TEAM(secondTeam->data)->position - 1);
            enqueue(&winners, secondTeam->data);
            free(firstTeam);
            free(secondTeam);
        }
    }
    free(teams);

    while (!isQueueEmpty(&winners)) {
        struct Node *firstTeam = dequeue(&winners);
        assert(firstTeam != NULL);
        struct Node *secondTeam = dequeue(&winners);
        if (secondTeam == NULL) {
            enqueue(losers, firstTeam->data);
            free(firstTeam);
            break;
        }
        if (compareTeams(firstTeam->data, secondTeam->data)) {
            enqueue(&winners, firstTeam->data);
            connectVertexes(ranking, GET_TEAM(secondTeam->data)->position - 1, GET_TEAM(firstTeam->data)->position - 1);
            enqueue(losers, secondTeam->data);
            free(firstTeam);
            free(secondTeam);
        } else {
            connectVertexes(ranking, GET_TEAM(firstTeam->data)->position - 1, GET_TEAM(secondTeam->data)->position - 1);
            enqueue(losers, firstTeam->data);
            enqueue(&winners, secondTeam->data);
            free(firstTeam);
            free(secondTeam);
        }
    }

    return ranking;
}

void printGraphToFile(struct Graph *g, FILE *output) {
    assert(g != NULL);
    assert(g->matrix != NULL);
    for (int i = 0; i < g->vertexes; i++) {
        assert(g->matrix[i] != NULL);
        for (int j = 0; j < g->vertexes; j++) {
            fprintf(output, "%d ", g->matrix[i][j]);
        }
        putc('\n', output);
    }

    for (int i = 0; i < g->vertexes; i++) {
        free(g->matrix[i]);
    }
    free(g->matrix);
    free(g);
}

double magicFormula(int r) {
    const float q = 0.15;
    const float l = 6.0;
    return q * pow((2.0 - q), r) / (pow(2.0, l) + pow((2.0 - q), l) * (q - 1.0));
}

void printRankingToFile(struct Queue *teams, FILE *output) {
    assert(teams != NULL);
    assert(output != NULL);
    for (int i = 0; i < 16; i++) {
        struct Node *item = dequeue(teams);
        fprintf(output, "%.4f %s\n", magicFormula(0), GET_TEAM(item->data)->name);
        FREE_TEAM(item->data);
        free(item);
    }

    for (int i = 0; i < 8; i++) {
        struct Node *item = dequeue(teams);
        fprintf(output, "%.4f %s\n", magicFormula(1), GET_TEAM(item->data)->name);
        FREE_TEAM(item->data);
        free(item);
    }

    for (int i = 0; i < 4; i++) {
        struct Node *item = dequeue(teams);
        fprintf(output, "%.4f %s\n", magicFormula(2), GET_TEAM(item->data)->name);
        FREE_TEAM(item->data);
        free(item);
    }

    for (int i = 0; i < 2; i++) {
        struct Node *item = dequeue(teams);
        fprintf(output, "%.4f %s\n", magicFormula(3), GET_TEAM(item->data)->name);
        FREE_TEAM(item->data);
        free(item);
    }

    struct Node *item = dequeue(teams);
    fprintf(output, "%.4f %s\n", magicFormula(4), GET_TEAM(item->data)->name);
    FREE_TEAM(item->data);
    free(item);

    item = dequeue(teams);
    fprintf(output, "%.4f %s\n", magicFormula(5), GET_TEAM(item->data)->name);
    FREE_TEAM(item->data);
    free(item);
}
