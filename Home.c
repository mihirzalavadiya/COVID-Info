#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <signal.h>
#include <sys/types.h>
#include <inttypes.h>
#include "common.h"

void insert()
{
    displaycountryname(1);
}

void display()
{
    displaycountryname(2);
}

void insert_as_file()
{
    idfile();
}

void date_wise_display()
{
    dateDiffrence();
}

void covid_symptoms()
{
    FILE *fp;
    char text;
    fp = fopen("symptoms.txt", "r");
    while ((text = fgetc(fp)) != EOF)
    {
        printf("%c", text);
    }
    // fgets(text, 255, (FILE *)fp);
    fclose(fp);
}

void protect_yourself()
{
    FILE *fp;
    char text;
    fp = fopen("protect.txt", "r");
    while ((text = fgetc(fp)) != EOF)
    {
        printf("%c", text);
    }
    fclose(fp);
}

void stop()
{
    exit(0);
}

void signal_handler()
{
    printf("Error while writing in file\n");
}

int main(int argc, char *argv[])
{
    void (*fns[7])() = {insert, insert_as_file, date_wise_display, display, covid_symptoms, protect_yourself, stop};
    int ch;
    signal(SIGUSR1, signal_handler);
    while (1)
    {
        printf("\n-----------------------\n");
        printf("1 - Insert Record\n");
        printf("2 - Insert as a File\n");
        printf("3 - Date wise display\n");
        printf("4 - Display Record\n");
        printf("5 - COVID Symptoms\n");
        printf("6 - Protect Yourself\n");
        printf("7 - Exit\n");
        printf("-----------------------\n");


        printf("\nEnter operation to perform : ");
        scanf("%d", &ch);

        if (ch < 1 || ch > 7)
        {
            printf("%d Invalid Option\n", ch);
        }
        else
        {
            fns[ch - 1]();
        }
    }
}