#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "common.h"

/* insert the data*/
void insertdata(int id)
{
    char dates[11];
    int cases, recoverCases;

    printf("Enter the date: ");
    scanf("%s", dates);

    printf("Enter the Total Cases for covid: ");
    scanf("%d", &cases);

    printf("Enter the recover pateints: ");
    scanf("%d", &recoverCases);

    // printf("Hello %s\n",dates);

    int pid = fork();
    if (pid == 0)
    {
        char temp[10], temp2[10], temp3[10];
        sprintf(temp, "%d", cases);
        sprintf(temp2, "%d", recoverCases);
        sprintf(temp3, "%d", id);
        execl("./fileio.out", "./fileio.out", dates, temp, temp2, temp3, NULL);
        // printf("ERROR\n");
        exit(0);
    }
}

/* use for display --> call display data and all data */
void switchcase(struct Write *w)
{
    char s[20];
    printf("\n\n");
    // printf("ID - %d\n", w.id);
    switch (w->id)
    {
    case 1:
        strcpy(s, "Australia");
        break;

    case 2:
        strcpy(s, "Brazil");
        break;

    case 3:
        strcpy(s, "France");
        break;

    case 4:
        strcpy(s, "Germany");
        break;

    case 5:
        strcpy(s, "India");
        break;

    case 6:
        strcpy(s, "Russia");
        break;

    case 7:
        strcpy(s, "USA");
        break;
    }
    printf("Country Name - %s\n", s);
    printf("Date         - %s\n", w->dates);
    printf("case         - %d\n", w->cases);
    printf("recover case - %d\n", w->rcases);
}

/* country wise data display*/
void displaydata(int id)
{
    struct Write w;
    FILE *infp;
    infp = fopen("alldata.txt", "r");
    while (!feof(infp))
    {
        fread(&w, sizeof(w), 1, infp);
        if (feof(infp))
            break;
        if (id == w.id)
        {
            switchcase(&w);
            // printf("||    Country Name    ||          Date        ||    Cases     ||    Recover Cases     ||     Age      ||");
            // printf("\n||    %s       ||     %s     ||     %d       ||         %d           ||     %d       ||", s, w.dates, w.cases, w.rcases, w.age);
        }
    }
    if (id == 8)
    {
        alldata();
    }
    fclose(infp);
}

/* all data display*/
void alldata()
{
    struct Write w;
    FILE *infp;
    infp = fopen("alldata.txt", "r");
    printf("\n\n        All Data\n");
    printf("----------------------------\n");
    while (!feof(infp))
    {
        fread(&w, sizeof(w), 1, infp);
        if (feof(infp))
            break;
        switchcase(&w);
    }
    printf("----------------------------\n");
}

/* date wise filter */
void *datefilter(void *p)
{
    FILE *infp;
    int totalcase, totalrecovercase;
    infp = fopen("alldata.txt", "r");
    struct Write w;
    while (!feof(infp))
    {
        fread(&w, sizeof(w), 1, infp);
        if(feof(infp))
            break;
        if (strcmp(w.dates, (char *)p) == 0)
        {
            totalcase += w.cases;
            totalrecovercase += w.rcases;
        }
    }
    printf("\nTotal Case on %s         : %d", (char *)p, totalcase);
    printf("\nTotal Recover Case on %s : %d\n", (char *)p, totalrecovercase);
    // printf("%s\n", (char *)p);
}

/* call datefilter using thread*/
void dateDiffrence()
{
    char dt[11];
    printf("Enter a date [DD-MM-YYYY] - ");
    scanf("%s", dt);
    pthread_t signal_thread;
    pthread_create(&signal_thread, NULL, datefilter, (void *)&dt);
    sleep(1);
}

void australia()
{
    insertdata(1);
    sleep(1);
    displaydata(1);
}

void brajil()
{
    insertdata(2);
    sleep(1);
    displaydata(2);
}

void france()
{
    insertdata(3);
    sleep(1);
    displaydata(3);
}

void germany()
{
    insertdata(4);
    sleep(1);
    displaydata(4);
}

void india()
{
    insertdata(5);
    sleep(1);
    displaydata(5);
}

void russia()
{
    insertdata(6);
    sleep(1);
    displaydata(6);
}

void usa()
{
    insertdata(7);
    sleep(1);
    displaydata(7);
}

void stop1()
{
    exit(0);
}

void selectcountry()
{
    void (*fns[9])() = {australia, brajil, france, germany, india, russia, usa, alldata, stop1};
    int i, ch;

    printf("\nEnter operation to country: ");
    scanf("%d", &ch);

    if (ch < 1 || ch > 9)
    {
        printf("%d Invalid Option\n", ch);
    }
    else
    {
        fns[ch - 1]();
    }
}