#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "common.h"

int main(int argc, char const *argv[])
{
    FILE *infp;
    struct Write w;
    strcpy(w.dates, argv[1]);
    w.cases = atoi(argv[2]);
    w.rcases = atoi(argv[3]);
    w.id = atoi(argv[4]);
    infp = fopen("alldata.txt", "a");
    if (infp == NULL)
    {
        kill(getppid(), SIGUSR1);
        exit(0);
    }
    if (fwrite(&w, sizeof(w), 1, infp) != 1)
    {
        kill(getppid(), SIGUSR1);
        exit(0);
    }
    fclose(infp);
}