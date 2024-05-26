#include <stdio.h>
#include <assert.h>
#include "src/parser.h"
#include "src/magic.h"
#include "src/queue.h"
#include "src/team.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("usage: %s [date.in] [output1.out] [output2.out]", argv[0]);
        return 1;
    }

    FILE *readFrom = fopen(argv[1], "r");
    if (readFrom == NULL) {
        printf("%s doesn't exist or some other error occured so sorry", argv[1]);
        return 1;
    }

    FILE *writeGraph = fopen(argv[2], "w");
    if (readFrom == NULL) {
        printf("%s doesn't exist or some other error occured so sorry", argv[2]);
        return 1;
    }

    FILE *writeScores = fopen(argv[3], "w");
    if (readFrom == NULL) {
        printf("%s doesn't exist or some other error occured so sorry", argv[3]);
        return 1;
    }

    struct Queue ranking;
    printGraphToFile(startMatches(parseData(readFrom), &ranking), writeGraph);
    printRankingToFile(&ranking, writeScores);


    fclose(readFrom);
    fclose(writeGraph);
    fclose(writeScores);
    return 0;
}
