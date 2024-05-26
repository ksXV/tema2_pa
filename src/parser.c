#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "team.h"

struct Queue *parseData(FILE *output) {
    assert(output != NULL);
    fseek(output, 0, SEEK_END);
    size_t fileLength = ftell(output);
    fseek(output, 0, SEEK_SET);
    
    char *data = calloc(sizeof(char), fileLength + 1);

    size_t bytesRead = fread(data, sizeof(char), fileLength, output);
    assert(fileLength == bytesRead);

    struct Queue *teams = calloc(sizeof(struct Queue), 1);
    assert(teams != NULL);

    char *p = strtok(data, "\r\n");
    int position = 1;
    for (int i = 0; p && i < 32; ++i) {
        struct Team *newTeam = calloc(sizeof(struct Team), 1);
        assert(newTeam != NULL);
        newTeam->points = atof(p);

        newTeam->name = calloc(sizeof(char), strlen(p + 5) + 1);
        assert(newTeam->name != NULL);
        strcpy(newTeam->name, p + 5);

        newTeam->position = position++;

        enqueue(teams, newTeam);
        p = strtok(NULL, "\r\n");
    }
    free(data);
    return teams;
}
