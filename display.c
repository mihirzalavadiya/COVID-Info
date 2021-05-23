#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/* Display Country Name*/
void displaycountryname(int a)
{
    char c;
    int fd;
    FILE *fp;
    if ((fd = open("countries.txt", O_RDWR | O_CREAT, 0755)) < 0)
    {
        printf("open error!");
        exit(-1);
    }
    fp = fopen("countries.txt", "r");
    if (fp == NULL)
        printf("Error Occurred while Opening the File!");
    else
    {
        c = fgetc(fp);
        while (c != EOF)
        {
            printf("%c", c);
            c = fgetc(fp);
        }
    }
    fclose(fp);
    printf("\n    8 - All data display");
    printf("\n    9 - Exit");
    if (a == 1)
    {
        selectcountry();
    }
    else
    {
        printf("\nEnter operation to country: ");
        int c;
        scanf("%d", &c);
        displaydata(c);
    }
}