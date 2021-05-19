// "gcc -o accountbook sqlite3.c main.c" is build command 
#include <stdio.h> // standard input/output header
#include <stdlib.h> // To Use system function
#include "sqlite3.h" // To Use sqlite3

int save(); int modi(); int load(); 
int UI(); int reset_nNum(); int create_table();
static int search_cb();
int search_db(); int search_db_UI();
typedef struct search_cb_data_t
{
    char List[32];
    int found;
    int Date;
    int Price;
} search_cb_data_t;

/***********************Below this line is a main function***********************/

int main()
{
int nNum=0;
UI(nNum);

    if(nNum==1) printf("프로그램을 이용해주셔서 감사합니다."); system("exit");

    if(nNum==2) {save(); reset_nNum(nNum); UI(nNum); return 0;} // input information in database file

    if(nNum==3) {modi(); reset_nNum(nNum); UI(nNum); return 0;} // modify information in database file

    if(nNum==4) {load(); reset_nNum(nNum); UI(nNum); return 0;} // load information in database file

}

/***********************Below this line is a function realization***********************/

int UI(int nNum)
{
printf("1. 프로그램 종료\n");
printf("2. 정보 입력\n");
printf("3. 정보 수정\n");
printf("4. 정보 조회\n");
printf("실행할 작업의 숫자를 입력해주세요 : "); scanf("%d",&nNum);
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
    create_table(db);
int nNum_value=0;char *List;int Date;int Price;
   char *zErrMsg=0;
   char query[128]={0,};
   if(!db||!List||!Date||!Price) return -1;
   printf("몇 개의 데이터를 삽입하시겠습니까? : ");
   scanf("%d",&nNum_value);
   while(nNum_value=0)
   {
    sprintf_s(query, 128, "\n어떤 데이터를 삽입하시겠습니까? 날짜,내용,가격(krw)순으로 입력해주세요. ex)10101,A,10000 ('%d', '%s', '%d');", Date,List,Price);
    printf("현재 %d 번째 데이터를 삽입하셨습니다.",nNum_value);
    nNum_value=nNum_value-1;
   if (sqlite3_exec(db, query, NULL, 0, &zErrMsg) != SQLITE_OK)
   {
        _trace(TEXT("INSERT : %S\r\n"), zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
   }
   }
   return 0;
   rc=sqlite3_exec(db,query,0,0,&err_msg);
   if(rc!=SQLITE_OK) //occur error when close database file
   {
        fprintf(stderr,"SQL Error ( %s ) \n",err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
   }
   sqlite3_close(db); // close database file
   printf("정보가 입력되었습니다.");
   return 0;
}

int modi()
{
printf("Not realized, yet.");
//function_Get_Data
//save to 
}

int create_table(sqlite3 *db)
{
    char *zErrMsg=0;
    char *create_query="CREATE TABLE Info(Date TEXT PRIMARY KEY NOT NULL, List TEXT NOT NULL, Price TEXT NOT NULL);";
    if(!db) return -1;
    if (sqlite3_exec(db, create_query, NULL, NULL, &zErrMsg) != SQLITE_OK)
    {
    _trace(TEXT("Create Table: %S\r\n"), zErrMsg);
    sqlite3_free(zErrMsg);
    return -1;
    }
    _trace(TEXT("Success to make table ! \r\n"));
 
 return 0;
}

static int search_cb(void *data,int argc,char **argv,char **azColName)
{
    search_cb_data_t *user_data=(search_cb_data_t*)data;
    if (user_data)
 {
 if (argc == 3 && strcmp(azColName[0], "List") == 0
     && argv[0] && strcmp(argv[0], user_data->List) == 0
     && strcmp(azColName[1], "Date") == 0
     && strcmp(azColName[2], "Price") == 0)
    {
    user_data->found = 1;
    if (argv[1]) user_data->Date = atoi(argv[1]);
    if (argv[2]) user_data->Price = atoi(argv[2]);
    }
 }

 return 0;
}


int search_db(sqlite3* db, char *List, int *Date, int *Price)
{
 char *zErrMsg = 0;
 search_cb_data_t user_data = { 0, };
 char query[128] = { 0, };

 if (!db || !List) return -1;

 memset(&user_data, 0, sizeof(search_cb_data_t));

 sprintf_s(user_data.List, 32, "%s", List);
 sprintf_s(query, 128, "SELECT * FROM List WHERE L LIKE '%s';", List);

 if (sqlite3_exec(db, query, search_cb, (void*)&user_data, &zErrMsg) != SQLITE_OK) // if NotFound
 {
 _trace(TEXT("SELECT : %S\n"), zErrMsg);
 sqlite3_free(zErrMsg);
 return -1;
 }
 if (user_data.found)
 {
 if (Date) *Date = user_data.Date;
 if (Price) *Price = user_data.Price;
 return 0;
 }
 return -1;
}

int search_db_UI(int nSearch_num);
{
int nSearch_num=0;
printf("어떤 형태의 데이터를 검색하시겠습니까?\n");
printf("1. Date\n");
printf("2. List\n");
printf("3. Price\n");
printf("숫자로 입력해주세요. ");
scanf("%d",&nSearch_num);

}