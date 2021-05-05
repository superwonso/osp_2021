// "gcc -o accountbook sqlite3.c main.c" is build command 
#include <stdio.h> // standard input/output header
#include <stdlib.h> // To Use system function
#include "sqlite3.h" // To Use sqlite3

int save(); int modi(); int load(); 
int insert();
int UI(); int reset_nNum();
struct {
int Date;
char List[100];
int Price;
} d1;

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
int nNum_value=0;
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
              "CREATE TABLE Info(Date INT,List TEXT, Price INT);";
              insert(nNum_value); // data insert function
              while(nNum_value=0)
              {
              "INSERT INTO Info(d1.Date,d1.List,d1.Price);";
              }
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

int insert(int nNum_value)
{
   int nNum_value=0;
   printf("�� ���� �����͸� �����Ͻðڽ��ϱ�? : ");
   scanf("%d",&nNum_value);
   while(nNum_value=0)
   {
   printf("\n� �����͸� �����Ͻðڽ��ϱ�? ��¥(���ڷθ� �̷���� �־�� ��),����,���� ������ �Է����ּ���. ���� %d ��° �����͸� �������Դϴ�.",nNum_value);
   scanf("%d,%c,%d",&d1.Date,d1.List,&d1.Price);
   nNum_value=nNum_value-1;
   }
}

int modi()
{
printf("Not realized, yet.");
}

int load()
{
printf("Not relized, yet.");
}
