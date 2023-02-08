#include <stdio.h>
#include<stdlib.h>
#include<conio.h>//getch()
#include<string.h>//for compare string strcmp func,
#include<windows.h>
#include <time.h>
#include <ctype.h>
#define _GNU_SOURCE
#define QNO 30
#define totques 10
#define size 200
void asked(char option[size], const char option1[size], const char option2[size],
	const char option3[size], const char option4[size],const char correct[size], const char category[size],FILE * fp,int *);

void gotoxy(int ,int );
void gotoxy(int x,int y)
{
        COORD c;
        c.X=x;
        c.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void menu();
void verify_pass();
int password();
void admin_menu();
void record();
void search();
void change_pass();
void player_menu();
void display1();
void quiz();
void display();
void top();
void help();
char enter_pass[20];

struct player
{
    char name[20];
    int scored;
    char uniq_id[20];
    int age;
    char quiz[20];
    char mobile[20];
};


void top()
{
    struct player p;
    system("cls");
    gotoxy(10,3);
    FILE *fp;
    fp = fopen("record.txt","ab+");
    if(fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    printf("<--:TOP SCORE:-->");

    int a[100],d[100];
    char b[100][20],c[100][20],e[100][20];
    int i=0;
    while(fread(&p,sizeof(p),1,fp) == 1)
    {
        a[i]=p.scored;
        strcpy(b[i],p.name);
        strcpy(c[i],p.uniq_id);
        d[i]=p.age;
        strcpy(e[i],p.mobile);
        i++;
    }

    int max = a[0];
    for (int j = 0; j < i; j++)
    {
       if(a[j] > max)
           max = a[j];
    }
    printf("%d",max);
    for (int j = 0; j < i; j++)
    {
       if(a[j] == max)
           {
               printf("\n\n\tName :%s\n",b[j]);
               printf("\tUnique ID :%s\n",c[j]);
               printf("\tAge :%d\n",d[j]);
               printf("\tMobile :%s\n",e[j]);
               printf("\tscore :%d\n",a[j]);
           }
    }
    printf("\n\n\t\t\t\t\t");
    system("pause");
}
void player_menu()
{
        int ch;
        do{
           system("cls");
           printf("\n-----------------------------------------------------------------------------------------------------------------------");
           printf("\n\t\t\t\t\t\tW  E  L  C  O  M  E ");
           printf("\n-----------------------------------------------------------------------------------------------------------------------");

           printf("\n\n\t1. Start Quiz\n\n\t2. Access your previous Record \n\n\t3. Hand Over to Admin\n\n\t4. Back to Main Menu\n\n\t5. Exit\n");
           printf("\n\n\tEnter your Choice : ");
           scanf("%d",&ch);
           switch(ch)
              {
                case 1:
                        quiz();
                        break;
                case 2: search();
                        break;
                case 3: verify_pass();
                        admin_menu();
                        break;
                case 4: menu();
                        break;
                case 5: exit(0);

                default : printf("\n\tInvalid Choice!\n");
                          printf("\n\n\t");
                          system("pause");
              }
           }while(ch!=5);
}

void quiz()
{
    printf("start quiz");
    struct player p;
    system("cls");
    FILE *fp;
    fp = fopen("record.txt","ab+");
    if(fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    fflush(stdin);
    printf("\n\tEnter first Name : ");
    gets(p.name);
    printf("\n\tCreate a ID : ");
    scanf("%s",p.uniq_id);
    fflush(stdin);
    printf("\n\tEnter age in years : ");
    scanf("%d",&p.age);
    fflush(stdin);
    printf("\n\tEnter Mobile Number : ");
    scanf("%s",p.mobile);
    p.scored=question();
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
}

void record()
{
    FILE *fp;
    int i=1,j;
    struct player p;
    system("cls");
    gotoxy(10,3);
    printf("<--:VIEW RECORD:-->");
    gotoxy(10,5);
    printf("S.No   Name of Student      Unique Id    Age      Mobile No   score");
    gotoxy(10,6);
    printf("--------------------------------------------------------------------");
    fp = fopen("record.txt","rb+");
    if(fp == NULL)
    {
        gotoxy(10,8);
        printf("Error opening file.");
        exit(1);
    }
    j=8;
    while(fread(&p,sizeof(p),1,fp) == 1)
    {
        gotoxy(10,j);
        printf("%-7d%-22s%-12s%-9d%-12s%-7d",i,p.name,p.uniq_id,p.age,p.mobile,p.scored);
        i++;
        j++;
    }
    fclose(fp);
    gotoxy(10,j+3);
    printf("Press any key to continue.");
    getch();
    admin_menu();
}

void search()
{
    char ch;
    FILE *fp;
    struct player p;
    char unq_id[20];
    system("cls");
    gotoxy(10,3);
    printf("<--:SEARCH RECORD:-->");
    gotoxy(12,7);
    printf("Enter your ID : ");
    fflush(stdin);
    gets(unq_id);
    fp = fopen("record.txt","rb+");
    if(fp == NULL)
    {
        gotoxy(12,9);
        printf("Error opening file");
        exit(1);
    }
    int c=0;
    while(fread(&p,sizeof(p),1,fp ) == 1)
    {
        if(strcmp(unq_id,p.uniq_id) == 0)
        {
            gotoxy(12,10);
            printf("Name : %s",p.name);
            gotoxy(12,12);
            printf("Mobile Number : %s",p.mobile);
            gotoxy(12,14);
            printf("Age : %d",p.age);
            gotoxy(12,16);
            printf("Score : %d",p.scored);
            c=1;
        }
    }
    if(c==0)
    {
        gotoxy(12,10);
        printf("No record found!!");
    }
    fclose(fp);
    gotoxy(12,20);
    system("pause");
    player_menu();
}

void change_pass()
{
    system("cls");
    int i=0;
    char chng_pass[20],chng_pass1[20];
    char ch,ch1;
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
    i=0;
    fflush(stdin);
    printf("\n\n\n\t\tRe-Enter new password : ");
    while(1)
    {
        ch1=getch();
        if(ch1==13) // 13 stands for ENTER
        {
            chng_pass1[i]='\0';
            break;
        }
        else if(ch1==8)// 8 stands for BACKSPACE
        {
            if(i>0);
            {
                i--;
                printf("\b \b");
            }
        }
        else if(ch1==9||ch1==32)// 9 stands for TAB // 32 stands for SPACE
        {
            continue;
        }
        else
        {
            chng_pass1[i]=ch1;
            i++;
            printf("*");
        }
    }


    int c = strcmp(chng_pass,chng_pass1);

    if(c==0)
    {
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
        printf("\n\n\t\t\t\t\t");
        system("pause");
        admin_menu();
    }
    else
    {
        printf("\n\n\n\n\t\t\t\t\t");
        printf("Passwords doesn't match, re-enter");
        printf("\n\n\n\n\t\t\t\t\t");
        system("pause");
        change_pass();

    }
}

void admin_menu()
{
        int ch;
        do{
           system("cls");
           printf("\n\n");
           printf("\n-----------------------------------------------------------------------------------------------------------------------");
           printf("\n\t\t\t\t\tW E L C O M E   S H R U T I");
           printf("\n-----------------------------------------------------------------------------------------------------------------------");

           gotoxy(1,5);
           printf("\n\n\t1. Access Players Record\n\n\t2. Top Scores \n\n\t3. Change Password\n\n\t4. Hand Over to Player\n\n\t5. Back to Main Menu\n\n\t6. Exit\n");
           printf("\n\n\tEnter your Choice : ");
           scanf("%d",&ch);
           switch(ch){
           case 1: record();
                   break;
           case 2: top();
                   break;
           case 3: verify_pass();
                   change_pass();
                   break;
           case 4: player_menu();
                   break;
           case 5: menu();
                   break;
           case 6: exit(0);

           default : printf("\n\tInvalid Choice!\n");
                     printf("\n\n\t");
                     system("pause");
           }
        }while(ch!=6);
}

int password()
{
    system("cls");
    printf("\n\n\n");
    int count,i=0;
    char ch;
    char str[20];
    FILE *fp;
    fp=fopen("password.txt","r");
    if(fp==NULL)
    {
        printf("\n\tError!");
        exit(1);
    }
    while(!feof(fp))
    {
        fgets(str,9,fp);
    }
    fclose(fp);
    printf("\n\t\tEnter password for verification : ");
    while(1)
    {
        ch=getch();
        if(ch==13) // 13 stands for ENTER
        {
            enter_pass[i]='\0';
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
            enter_pass[i]=ch;
            i++;
            printf("*");
        }
    }
    count=strcmp(str,enter_pass);
    return(count);

}

void verify_pass()
{
    system("cls");
    int result;
    int count=3;
    do{
        result=password();
        if(result==0)
        {



           count=4;
        }
        else
        {
            count--;
            printf("\n\n\t\tIncorrect Password!!\n\n\t\t%d trial left\a",count);
            if(count==0)
            {
                printf("\n\n\n\t\tProgram Terminated!!\a");
                exit(1);
            }
            printf("\n\n\n\t\t\t\t\t");
            system("pause");
        }
     }while(count!=4);
}

void menu()
{
    char ch;
    do{
    system("cls");
    gotoxy(1,10);

    printf("\t\t1. Admin \n\n");
    printf("\t\t2. Player\n\n");
    printf("\t\t3. Help\n\n");
    printf("\t\t4. Exit\n\n");
    printf("\n\t\tEnter your Choice : ");
    scanf("%d",&ch);
    switch(ch){
        case 1: verify_pass();
                admin_menu();
                break;
        case 2: player_menu();
                break;
        case 3: help();
                break;
        case 4: exit(0);

        default : printf("\n\t\tInvalid Choice!\n");
                  printf("\n\n\t\t");
                  getch();
    }

    }while(ch!=4);
}
void help()
{
    system("cls");
    printf("\n\n\n\n\n\t\t\t\t ABOUT QUIZZET      \n\n\n");
        printf("\t\t\t\t -> Its having two modes 1)ADMIN  2)PLAYER       \n\n");
        printf("\t\t\t\t -> To access admin rights you have to enter password  \n");
        printf("\t\t\t\t -> Admin can view all records\n\t\t\t\t -> admin can view toppers record\n\t\t\t\t -> admin can change the password\n\n");
        printf("\t\t\t\t -> To access Plalyer rights no password is required  \n");
        printf("\t\t\t\t -> Player can play quiz\n\t\t\t\t -> Player can look for previous records if any\n\n");
        printf("\n\t\t\t\t           ");
		system("pause");

}
void display1()
{
        system("cls");
        printf("\n\n\n\n\n\t\t\t\t RULES OF THE QUIZ       \n\n\n");
        printf("\t\t\t\t -> A TOTAL OF 10 QUESTION WILL BE THERE          \n\n");
		printf("\t\t\t\t -> 4 MARKS WILL BE AWARDED FOR CORRECT ANSWER   \n\n");
		printf("\t\t\t\t -> NO MARKS WILL AWARDED FOR INCORRECT ANSWER    \n\n");
		printf("\t\t\t\t -> NO NEGATIVE MARKING         \n\n");
		printf("\t\t\t\t -> SCORE CARD WILL BE GIVEN AT END         \n\n");
		printf("\n\t\t\t\t           ");
		system("pause");
		system("cls");
}

void display()
	{
	    system("cls");
		printf("\n\n\n\n\n\n");
		printf("\n\t   +-------+                       _______      _______     _______      ______     _______    ");
        printf("\n\t   |       |      |         |         |               /            /     |             |       ");
        printf("\n\t   |       |      |         |         |              /            /      |             |       ");
		printf("\n\t   |       |      |         |         |             /            /       |_____        |       ");
		printf("\n\t   |    // |      |         |         |            /            /        |             |       ");
		printf("\n\t   |   //  |      |         |         |           /            /         |             |       ");
		printf("\n\t   +--//---+      |_________|      ___|___       /_______     /______    |______       |       ");
		printf("\n\n\n\n\n\n\t\t\t      ");
		system("pause");
		system("cls");
	}

int question()
{
    char text[size],option1[size], option2[size], option3[size], option4[size], option[size], correct[size], category[size];
	char empty[256][256];
	int i,j,k;
	int arr[QNO],x,loc;
	time_t t;
	char line[256];
	int score = 0;
    int ch;
    FILE * fp;
    FILE * output;
    system("cls");
    printf("\n\n\t1. Computer Quiz\n\n\t2. GK Quiz \n\n\t3. Exit\n");
    printf("\n\n\tEnter your Choice : ");
    scanf("%d",&ch);
    if(ch==1)
    fp = fopen("cquiz.txt","r");
    else if (ch==2)
            fp = fopen("Quiz.txt","r");
    else if(ch==3)
        player_menu();
    else
    {
              printf("\n\n\t\tEnter a valid choice");
              printf("\n\n\n\t\t\t\t");
 system("pause");
 question();
    }
    system("cls");
    display1();
    output = fopen("NewText.txt","w");
    if(fp == NULL)
    {
    	printf("\n\n\n \t\t\t Quiz File Can't Be OPENED \t\t\t \n\n\n");
	}
	if(output == NULL)
	{
		printf("\n\n\n \t\t\t NewText File Can't Be CREATED \t\t\t \n\n\n");
	}
	k = 0;
	for (i = 0; i < 30; i++)
	{
		arr[i] = 10 * i + 1;
	}
	for (j = 0; j < totques; j++)
	{
		srand((unsigned)time(&t));
		x = rand() % 3;
		loc = (3 * j) + x;

		for (i = arr[3 * j]; i < arr[loc]; i++)
		{
		fgets(empty[k],sizeof(empty[k]),fp);
			k++;
		}

		for (i = 1; i <= 10; i++)
		{
			fgets(line,sizeof(line),fp);
			if(i==1)
			{
			  printf("\n\n\n\n\n\nQ%d) %s",j+1,line);
			  fprintf(output,"Q%d) %s",j+1,line);

			}

				if(i==2)
				{
					fputs(line,output);
				}

				if(i == 3)
			strncpy(option1,line,30);

				if(i == 4)
			strncpy(option2,line,30);

				if(i == 5)
			strncpy(option3,line,30);

				if(i == 6)
			strncpy(option4,line,30);

			if (i >1&&i<=7)
			{
				printf("%s",line);

			}
			if (i == 8)
			strncpy(correct,line,30);

			if (i == 9)
			strncpy(category,line,30);
		}


		asked(option, option1, option2, option3, option4, correct, category,output,&score);

		if(j!=9)
		{

		if (arr[loc] + 10 < arr[3 * (j + 1)])
		  {
			for (i = arr[loc] + 10; i < arr[3 * (j + 1)]; i++)
			{
			fgets(empty[k],sizeof(empty[k]),fp);
				k++;
			}
		  }
		}
		system("cls");
	}
	fprintf(output," \n You got total %d out of 40 ",score);
	fclose(fp);
	fclose(output);
	output = fopen("Newtext.txt","r");

	while(fgets(line,sizeof(line),output))
	{
		printf(" %s",line);
	}
	fclose(output);
	printf("\n\n\n\t\t\t\t\t");
	system("pause");
    return(score);
}

void asked(char option[size], const char option1[size], const char option2[size], const char option3[size], const char option4[size],
	 const char correct[size], const char category[size],FILE * fp,int *score)
	{
		printf("Your Option : ");
		scanf("%str",&option[0]);
		option[1] = '\0';
		strupr(option);

			char correctanswer[size];
			char wronganswer[size];

			fprintf(fp,"%s \n",category);

		if (option[0] == correct[0])
		{
			if (option[0] == option1[0])
				fprintf(fp," \nYou entered correct answer : %s  \n ", option1);
			if (option[0] == option2[0])
				fprintf(fp," \nYou entered correct answer : %s  \n ", option2);
			if (option[0] == option3[0])
				fprintf(fp," \nYou entered correct answer : %s  \n ", option3);
			if (option[0] == option4[0])
				fprintf(fp," \nYou entered correct answer : %s  \n ", option4);

				*score += 4;

			fprintf(fp," \n You are awarded 4 marks for this correct answer \n ");
		}
		else
		{

			if (correct[0] == option1[0])
				strncpy(correctanswer, option1,24);
			if (correct[0] == option2[0])
				strncpy(correctanswer, option2,24);
			if (correct[0] == option3[0])
				strncpy(correctanswer, option3,24);
			if (correct[0] == option4[0])
				strncpy(correctanswer, option4,24);

			correctanswer[24] = '\0';

			if (option[0] == option1[0])
				strncpy(wronganswer, option1,24);
			if (option[0] == option2[0])
				strncpy(wronganswer, option2,24);
			if (option[0] == option3[0])
				strncpy(wronganswer, option3,24);
			if (option[0] == option4[0])
				strncpy(wronganswer, option4,24);

			wronganswer[24] = '\0';

			fprintf(fp," You entered     : %s \n", wronganswer);
			fprintf(fp," Correct answer  : %s \n", correctanswer);
			fprintf(fp," \n You are awarded 0 marks for this wrong answer \n ");
		}

			fprintf(fp," -----------------------------------------------------------------------------\n");
			fprintf(fp," -----------------------------------------------------------------------------\n");
	}

int main()
{
    system("color f4");
    display();
    menu();

}
