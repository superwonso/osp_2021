#include <stdio.h> // In Windows 10
#include <stdlib.h>
#include "sqlite3.h" // in Project folder

int save();
int UI();

int main(void)
{
int num;
UI(num);
sqlite3 *db; // handle of database
char *err_msg=0; // if occur errors, this pointer point to error msg

if(num==0) system("exit");

if(num==1) // no.1 is input information in database file
{
    int rc=sqlite3_open("date.db",&db); // open "date.db" database file
    if(rc!=SQLITE_OK)
    {
        fprintf(stderr,"Cannot Open Database File ( %s ) \n",sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    char *sql="DROP TABLE IF EXISTS Info;"
            "CREATE TABLE Info(Date INT,List TEXT, Price INT);"
            "INSERT INTO Info(20210503,'Test',100000;";
    rc=sqlite3_exec(db,sql,0,0,&err_msg);
    if(rc!=SQLITE_OK) //occur error when close database file
    {
        fprintf(stderr,"SQL Error ( %s ) \n",err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db); // close database file
    return 0;
}

if (num==2)
{

}

}

int UI(int num)
{
printf("1. 정보 입력\n");
printf("2. 정보 조회\n");
printf("0. 프로그램 종료\n");
printf("실행할 작업의 숫자를 입력해주세요 : ");
scanf("%d",&num);
}
//system("command") -> typing "command" in terminal