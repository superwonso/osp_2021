#include <stdio.h>
#include <sqlite3.h> // in "AccountBook" folder

int save();
int UI();

int main(void)
{
int num;
printf("실행할 작업의 번호를 입력해주세요.");
scanf("%d",&num);
system("cls");
UI(num);
sqlite3 *db; // handle of database
char *err_msg=0; // if occur errors, this pointer point to error msg

if(num==1) // no.1 is input information in database file
{
int rc=sqlite3_open("date.db",&db); // open "date.db" database file
if(rc!=SQLITE_OK)
{
    fprintf(stderr,"Cannot Open Database File (file category : %s\n",sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
}
char *sql="DROP TABLE IF EXISTS Info;"
"CREATE TABLE Info(Date INT,List TEXT, Price INT);"
}

return 0;
}

int UI(int num)
{

}
//system("command") -> typing "command" in terminal