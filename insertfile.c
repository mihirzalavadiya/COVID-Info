#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "common.h"

/* Isert a file based data store*/
void idfile()
{
    struct Write w;
    char filename[20];

    printf("Insert File Name: ");
    scanf("%s", filename);

    FILE *infp, *infp1;
    infp = fopen(filename, "r");

    infp1 = fopen("alldata.txt", "a");
    if (infp1 == NULL)
    {
        kill(getppid(), SIGUSR1);
        exit(0);
    }
    while (!feof(infp))
    {
        fscanf(infp, "%d\n%s\n%d\n%d\n", &w.id, w.dates, &w.cases, &w.rcases);
        if (feof(infp))
            break;
        if (fwrite(&w, sizeof(w), 1, infp1) != 1)
        {
            kill(getppid(), SIGUSR1);
            exit(0);
        }
    }
    fcloseall();
}