//"gcc -o accountbook sqlite3.c main.c" is build command 
#include <stdio.h> // In Windows 10
#include <stdlib.h> // To Use system function
#include "sqlite3.h" // in Project folder


int save(); int modi(); int load();
int UI(); int reset_nNum();


/***********************Below this line is a main function***********************/

int main()
{
int nNum=0;
UI(nNum);

    if(nNum==1) printf("���α׷��� �̿����ּż� �����մϴ�."); system("exit");

    if(nNum==2) {save(); reset_nNum(nNum); UI(nNum); return 0;} // input information in database file

    if(nNum==3) {modi(); reset_nNum(nNum); UI(nNum); return 0;} // modify information in database file

    if(nNum==4) {load(); reset_nNum(nNum); UI(nNum); return 0;} // load information in database file

}

/***********************Below this line is a function realization***********************/

int UI(int nNum)
{
printf("1. ���α׷� ����\n");
printf("2. ���� �Է�\n");
printf("3. ���� ����\n");
printf("4. ���� ��ȸ\n");
printf("������ �۾��� ���ڸ� �Է����ּ��� : "); scanf("%d",&nNum);
}

int reset_nNum(int nNum)
{
nNum=0;
}

int save()
{
sqlite3 *db; // handle of database
char *err_msg=0; // if occur errors, this pointer point to error msg
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
    printf("������ �ԷµǾ����ϴ�.");
    return 0;
}

int modi()
{
printf("Not realized, yet.");
}

int load()
{
printf("Not relized, yet.");
}