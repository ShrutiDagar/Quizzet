#include <stdio.h>
#include<stdlib.h>
#include<conio.h>//getch()
#include<string.h>//for com



void main()
{
    system("cls");
    int i=0;
    char chng_pass[20];

    char ch;
    printf("\n\n\n\t\tEnter new password : ");
    while(1)
    {
        ch=getch();
        if(ch==13) // 13 stands for ENTER
        {
            chng_pass[i]='\0';
            break;
        }
        else if(ch==8)// 8 stands for BACKSPACE
        {
            if(i>0);
            {
                i--;
                printf("\b \b");
            }
        }
        else if(ch==9||ch==32)// 9 stands for TAB // 32 stands for SPACE
        {
            continue;
        }
        else
        {
            chng_pass[i]=ch;
            i++;
            printf("*");
        }
    }
    FILE *fp;
        fp=fopen("password.txt","w");
        if(fp==NULL)
            printf("no file");
        for(i=0;i<strlen(chng_pass);i++)
        {
            fputc(chng_pass[i],fp);
        }
        fclose(fp);
        printf("\n\n\n\n");
        printf("\n\n\t\t\t\t\tPassword changed successfully!!\n");
}
