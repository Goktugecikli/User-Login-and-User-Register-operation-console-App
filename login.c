#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <ctype.h>

#define ENTER 13
#define TAB 9
#define BCKSPC 8
#define DEL 127

#define ANSI_COLOR_GREEN  "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define COLOR_BOLD  "\e[1m"
#define COLOR_OFF   "\e[m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

struct User 
{
    char userName[20] ;
    char password[10] ;
    char checkPassword[10];
    char name[20];
    char surname[20];
    char email[50];
};

int UserInfo();
void takePassword();
void takeInput();
int Login();
int SignIn();
int Selection();
int ShowMenu();
int Exit();

int GetSize(char *str, char ch);
void GetIndexes(int *indexOfPasswordBegin, int *indexOfEnd, char *str, int lengthStr);
bool CheckCredential(char *str, int length,char *loginUsername,char *loginUserPass);

int GetIndexName(int *indexOfNameBegin,int *indexOfNameEnd,char *str,int *indexOfSurnameBegin);
int CheckCredentials(char *str, int length);
int GetIndexSurname(int *indexOfSurnameBegin,int *indexOfSurnameEnd,char *str,int length,int *indexOfEmailBegin);

void GetContent(char *str,int start,int end,int length,char *info);
bool CheckCredential2(char *str, int length,char *username,char *pword);

bool ValidaitePassword(char *password);

int main()
{
    
    ShowMenu();

    return 0;
}


/*---------------------------------------LOGIN MENU--------------------------------------------*/
int Login()
{
    system("cls");
      FILE *fp  = fopen("Users.txt","r");

         if(fp == NULL)
    {
        perror("Unable to open the file");
        exit(1);
    }

      int tryCountLogin = 0;
      char MainMenu;

      char username[200],pword[20];
    
      printf("Enter username : ");
      scanf("%s",&username);
      
      printf("Enter password : ");
      takePassword(pword);

    char line[50];
    bool isExists = false;
    int length; 

        while(fgets(line, sizeof(line), fp))
    {
        // printf("\nDosyadan Okunan: %s", line);
        length = GetSize(line, '?');
        if(length != -1)
            isExists = CheckCredential(line, length,username,pword);
          if(isExists)
            break;
    }
    if(isExists)
           {
            UserInfo(username,pword);
            }  
    else
           {
            printf("\n\n\t\tWrong Password or Username\n");
            Login();
           }

           return 0;
}


/*--------------------------------------SIGN IN MENU-------------------------------------------*/
int SignIn()
{
      FILE *fp;
      char MainMenu;

      struct User user;

      int tryCountSignin = 0;

      bool isValidate  = true;

      system("cls");
      printf("\nFirst Name : ");
      scanf("%s",user.name);

      printf("Last Name : ");
      scanf("%s",user.surname);

      printf("Email : ");
      scanf("%s",user.email);
      
      printf("Username = ");
      scanf("%s",user.userName);

      printf(ANSI_COLOR_RED"\t\t\t\t!! WARNING !!");
      printf(COLOR_BOLD"\n(The password must contain at least one uppercase letter, one lowercase letter and numbers.)\n"COLOR_OFF);
    do
    {
      printf("Password = ");
      takePassword(user.password,user.checkPassword);
      isValidate = ValidaitePassword(user.password);
    }while(!isValidate);
      
    
      if(isValidate)
      {
        printf("\nComfirm Password = ");
        takePassword(user.checkPassword);

        if(!strcmp(user.password,user.checkPassword))
        {
            fp = fopen("Users.txt","a+");
            fprintf(fp,"%s-%s?%s$%s#%s!\n",user.userName,user.password,user.name,user.surname,user.email);
            fclose(fp);

        }

         else
            {
                printf("\nPassword DO NOT matched !!!\n");
                Beep(750,300);
                fclose(fp);
            }

    ShowMenu();
      }
      else
      {
        SignIn();
      }


        

    return 0;
}

/*---------------------------------------MAIN MENU---------------------------------------------*/

int  ShowMenu()
{
    system("cls");
   printf(ANSI_COLOR_YELLOW"\n--------------------Main Menu--------------------\n");
   printf("Login [L/l]\n");
   printf("SignIn[S/s]\n");
   printf("Exit[E/e]\n");

    char select;
    int tryCount = 0;

    printf("Press Key : ");

    do{


    scanf("%s",&select);


    if(select == 108 || select == 76)
           {
            tryCount++;
            Login();
           }
    else if(select == 115 || select == 83)
           {
            tryCount++ ;
            SignIn();
           }
    else if(select == 101 || select == 69)
        //    Exit();
            return 0;
    else
        {
            tryCount++;
            ShowMenu();
        }
    }while(tryCount == 3);

    return 0;

}

/*----------------------------------------PASSWORD----------------------------------------------*/
void takePassword(char pwd[50])
{
    int i =0;
    char ch;

    while((ch =  getch()) != 13)
      {
        pwd[i] = ch;
        i++;
        printf("*");
      }
      pwd[i] = '\0';
}
/*------------------------------------------Exit------------------------------------------------*/
int Exit()
{
    return 0;
}
/*----------------------------------------Get Size----------------------------------------------*/
int GetSize(char *str, char ch)
{
    int i = 0;
    do{
        i++;
        if(str[i] == ch)
            break;
    }while(str[i] != '\0');
    if(i != 0)
        return (i);
    return -1;
}
/*----------------------------------------Get Index----------------------------------------------*/
void GetIndexes(int *indexOfPasswordBegin, int *indexOfEnd, char *str, int lengthStr)
{
    for(int i=0; i<=lengthStr; i++)
    {
        if(str[i] == '-')
            *indexOfPasswordBegin = i;
        else if(str[i] == '?')
        {*indexOfEnd = i;break;} 
    }

}
/*--------------------------------------Check Credential-------------------------------------------*/
bool CheckCredential(char *str, int length,char *username,char *pword)
{
    char next;

    int indexOfPasswordBegin = -1,indexOfEnd = -1;

    GetIndexes(&indexOfPasswordBegin, &indexOfEnd, str, length); 

    if((GetSize(username, '\0') != indexOfPasswordBegin) ||(GetSize(pword, '\0') != (indexOfEnd-indexOfPasswordBegin-1)))
        return false;
    for(int i=0; i<(indexOfPasswordBegin); i++)
    {
        if(str[i] != username[i])
            return false;  
    }
    int j=0;
    for(int i=(indexOfPasswordBegin+1); i<(indexOfEnd); i++)
    {
        if(str[i] != pword[j])
            return false; 
        j++;
    }
    
    printf("\n\n\t\t\tPress [C/c] to go account...");
    scanf("%c\n",&next);
    return true;
}

/*----------------------------------------User Info---------------------------------------------*/
int UserInfo(char *usernameAccount,char *pwordAccount)
{
    FILE *fp = fopen("Users.txt","r");

    char line[100];
    int length; 
    char exit;
    char checkExit;

    int tryCountExit = 0;
    int tryCountCheckExit = 0;

  

    bool correctUser = false;

    //printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------------------------------\n");
    system("cls");
    printf("\t\t\t\tWELCOME %s !!!\n",usernameAccount);
    printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------\n\n");
            //   printf(ANSI_COLOR_GREEN "\n\t\t\t\tUsername: %s",usernameAccount);
            //   printf(ANSI_COLOR_GREEN "\n\t\t\t\tPassword: %s\n",pwordAccount);

    while(fgets(line, sizeof(line), fp))
    {
        //printf("\nDosyadan Okunan: %s", line);
        length = GetSize(line,'!') ;
        // printf("\n%d\n",length);
        correctUser = CheckCredential2(line,length,usernameAccount,pwordAccount);
        if(correctUser)
         CheckCredentials(line, length);
        
          do{
            scanf("%c",&exit);
            if(exit  == 69 || exit == 101)
                {
                    system("cls");
                    ShowMenu();
                }
            else
                tryCountExit++;
            }while(tryCountExit == 3);
    }
    printf(ANSI_COLOR_CYAN"\n\n------------------------------------------------------------------------------------\n");

    return 0;
     
}

/*--------------------------------------Check Credentials-------------------------------------------*/
int CheckCredentials(char *str, int length)
{
    char MainMenu;

    int tryCountLogin = 0;

    int indexOfUsernameBegin = 0;

    int indexOfUsernameEnd = GetSize(str,'-');
    
    int indexOfPasswordBegin = GetSize(str,'-') + 1;

    int indexOfPasswordEnd = GetSize(str,'?');

    int indexOfNameEnd = GetSize(str,'$');

    int indexOfNameBegin = GetSize(str,'?') +1 ;
    // printf("\n%d\n",indexOfNameBegin);


    int indexOfEmailBegin = GetSize(str,'#') ;
    //printf("\n%d\n",indexOfEmailBegin);   

    int indexOfSurnameBegin = GetSize(str,'$') +1 ;
    //printf("\n%d\n",indexOfSurnameBegin);


    int indexOfEmailEnd = GetSize(str,'!');
    //printf("\n%d\n",indexOfEmailEnd);

    int indexOfSurnameEnd = GetSize(str,'#') + 1;
    //printf("\n%d\n",indexOfSurnameEnd);

    char username[] = "Username";
    char password[] = "Password";
    char name[] = "Name";
    char surname[] = "Surname";
    char email[] = "Email";

    int nameLength = indexOfNameEnd - indexOfNameBegin - 1; 
    int surnameLength = indexOfEmailBegin - indexOfSurnameBegin - 1;
    int emailLength = indexOfEmailEnd - indexOfSurnameEnd  -1;

    int usernameLength = indexOfUsernameEnd - indexOfUsernameBegin - 1;
    int passwordLength = indexOfPasswordEnd - indexOfPasswordBegin -1 ;

    GetContent(str,indexOfUsernameBegin,indexOfUsernameEnd,usernameLength,username);
    GetContent(str,indexOfPasswordBegin,indexOfPasswordEnd,passwordLength,password);
    GetContent(str,indexOfNameBegin,indexOfSurnameBegin,nameLength,name);
    GetContent(str,indexOfSurnameBegin,indexOfEmailBegin,surnameLength,surname);
    GetContent(str,indexOfSurnameEnd,indexOfEmailEnd,emailLength,email);

    printf("\t\t\t\t\t\t\tLogOut [E/e] : ...");
    return 0;

}
/*--------------------------------------Get Content-------------------------------------------*/
void GetContent(char *str,int start,int end,int length,char *info)
{
    int i;
    int j=0;
    char content[length+1];

    for(i = start;i < end;i++)
    {
        content[j] = str[i];
        j++;
    }
    content[length+1] = '\0';
    printf(ANSI_COLOR_GREEN"\t\t\t\t%s: %s\n",info,content);   
}  

/*--------------------------------------Check Credential2-------------------------------------------*/
bool CheckCredential2(char *str, int length,char *username,char *pword)
{
    char next;

    int indexOfPasswordBegin = -1,indexOfEnd = -1;

    GetIndexes(&indexOfPasswordBegin, &indexOfEnd, str, length); 

    if((GetSize(username, '\0') != indexOfPasswordBegin) ||(GetSize(pword, '\0') != (indexOfEnd-indexOfPasswordBegin-1)))
        return false;
    for(int i=0; i<(indexOfPasswordBegin); i++)
    {
        if(str[i] != username[i])
            return false;  
    }
    int j=0;
    for(int i=(indexOfPasswordBegin+1); i<(indexOfEnd); i++)
    {
        if(str[i] != pword[j])
            return false; 
        j++;
    }
    return true;
}


bool ValidaitePassword(char *password)
{
   int length = strlen(password);
    printf("\nPass: %s\n", password);
   if(length > 10)
        return false;

    bool has_lower = false ;
    bool has_upper = false ;
    bool has_digit = false ;
    bool has_alpha = false ;

    for(int i = 0;i < length;i++)
    {
        char c = password[i];

        if(islower(c) == 1) has_lower = true;
        else if (isupper(c) == 1) has_upper = true;
        else if(isdigit(c) == 1) has_digit = true;
        else if(isalpha(c) == 0) has_alpha = true;
    }    
    if(has_lower && has_digit && has_upper)
        return true;

    return false ;
}





