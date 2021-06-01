// "gcc -std=c11 -o accountbook sqlite3.c main.c" is build command
#include "sqlite3.h" // To Use sqlite3
#include <stdio.h>   // standard input/output header
#include <stdlib.h>  // To Use system function
#include <string.h>  // To Use memory function
int save(); int callback(); int update_db(); int UI();
int reset_nNum(); int create_table();
static int search_cb(); int search_db(); int export_db();
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
    int nNum = 0;
    reset_nNum(nNum);
    system("cls");
    UI(nNum);

    if (nNum == 1)
    printf("Thank you for using this program :)");
    system("timeout -t 1 /NOBREAK");
    system("exit");

    if (nNum == 2)
    {
        save();
        return 0;
    } // input information in database file

    if (nNum == 3)
    {
        update_db();
        return 0;
    } // update(modify) information in database file

    if (nNum == 4)
    {
        callback();
        return 0;
    } // load information in database file

    if (nNum == 5)
    {
        search_db();
        return 0;
    } // search information in database file

    if (nNum == 6)
    {
        export_db();
        return 0;
    }
    return 0;
}

/***********************Below this line is a function realization***********************/

int UI(int nNum)
{
    printf("1. Quit Program \n");
    printf("2. Enter Information \n");
    printf("3. Update Information \n");
    printf("4. Load Information \n");
    printf("5. Search Information \n");
    printf("6. Export database to csv file \n");
    printf("Typing  : ");
    scanf("%d", &nNum);
    return 0;
}

int reset_nNum(int nNum)
{
    nNum = 0;
    return 0;
}

int save(void)
{
    sqlite3 *db;                           // handle of database
    char *err_msg = 0;                     // if occur errors, this pointer point to error msg
    int rc = sqlite3_open("date.db", &db); // open "date.db" database file
    if (rc != SQLITE_OK)
    {
        fprintf_s(stderr, "Cannot Open Database File ( %s ) \n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    create_table(db);
    int nNum_value = 0;
    char *List;
    int Date;
    int Price;
    char *zErrMsg = 0;
    char query[128] = {
        0,
    };
    if (!db || !List || !Date || !Price)
        return -1;
    printf("How many data do you want to inster? : ");
    scanf("%d", &nNum_value);
    while (nNum_value == 0)
    {
        sprintf_s(query, 128, "\n What data do you want to insert? Please enter in order date,contents,price[krw]. ex)20000214,A,10000 ('%d', '%s', '%d');", Date, List, Price);
        puts(query);
        printf("You have now entered the %dth data.", nNum_value);
        nNum_value = nNum_value - 1;
        if (sqlite3_exec(db, query, NULL, 0, &zErrMsg) != SQLITE_OK)
        {
            _trace(TEXT("INSERT : %S\r\n"), zErrMsg);
            sqlite3_free(zErrMsg);
            return -1;
        }
    }
    return 0;
    rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    if (rc != SQLITE_OK) //occur error when close database file
    {
        fprintf_s(stderr, "SQL Error ( %s ) \n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db); // close database file
    printf("Information is entered.");
    main();
    return 0;
}

int update_db()
{
    sqlite3 *db;
    char *List;
    int *Date;
    int *Price;
    int what;
    printf("What data do you want to update?\n 1. Price \n 2. Date");
    scanf("%d", &what);
    char *zErrMsg = 0;
    char query[128] = {
        0,
    };

    if (!db || !List)
        return -1;

    if (what == 2)
    {
        sprintf_s(query, 128, "UPDATE Info SET Date = '%d' WHERE List ='%s';\0", Date, List);
        if (sqlite3_exec(db, query, NULL, 0, &zErrMsg) != SQLITE_OK)
        {
            _trace(TEXT("Database Updated : %S\r\n"), zErrMsg);
            sqlite3_free(zErrMsg);
            return -1;
        }
    }

    else if (what == 1)
    {
        sprintf_s(query, 128, "UPDATE Info SET Price = '%d' WHERE List ='%s';\0", Price, List);
        if (sqlite3_exec(db, query, NULL, 0, &zErrMsg) != SQLITE_OK)
        {
            _trace(TEXT("Datebase Updated : %S\r\n"), zErrMsg);
            sqlite3_free(zErrMsg);
            return -1;
        }
    }
    main();
    return 0;
}

int create_table(sqlite3 *db)
{
    char *zErrMsg = 0;
    char *create_query = "CREATE TABLE Info(Date TEXT PRIMARY KEY NOT NULL, List TEXT NOT NULL, Price TEXT NOT NULL);";
    if (!db)
        return -1;
    if (sqlite3_exec(db, create_query, NULL, NULL, &zErrMsg) != SQLITE_OK)
    {
        _trace(TEXT("Create Table: %S\r\n"), zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }
    _trace(TEXT("Success to make table ! \r\n"));

    return 0;
}

static int search_cb(void *data, int argc, char **argv, char **azColName)
{
    search_cb_data_t *user_data = (search_cb_data_t *)data;
    if (user_data)
    {
        if (argc == 3 && strcmp(azColName[0], "List") == 0 && argv[0] && strcmp(argv[0], user_data->List) == 0 && strcmp(azColName[1], "Date") == 0 && strcmp(azColName[2], "Price") == 0)
        {
            user_data->found = 1;
            if (argv[1])
                user_data->Date = atoi(argv[1]);
            if (argv[2])
                user_data->Price = atoi(argv[2]);
        }
    }

    return 0;
}

int search_db()
{
    sqlite3 *db;
    char *List;
    int *Date;
    int *Price;
    char *zErrMsg = 0;
    search_cb_data_t user_data = {
        0,
    };
    char query[128] = {
        0,
    };

    if (!db || !List)
        return -1;

    memset(&user_data, 0, sizeof(search_cb_data_t));

    printf("What type of data do you want to search? ");
    sprintf_s(user_data.List, 32, "%s", List);
    sprintf_S(query, 128, "SELECT * FROM Info WHERE List LIKE '%s';", List);

    if (sqlite3_exec(db, query, search_cb, (void *)&user_data, &zErrMsg) != SQLITE_OK) // if NotFound
    {
        _trace(TEXT("SELECT : %S\n"), zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }
    if (user_data.found)
    {
        if (Date)
            *Date = user_data.Date;
        if (Price)
            *Price = user_data.Price;
        return 0;
    }
    main();
    return -1;
}

int export_db()
{
    char c[1000];
    FILE *fptr;
    fptr = fopen("output.csv", "w");
    system("sqlite3 -header -csv 'date.db' 'select * from Info;' > output.csv");
    main();
    return 0;
}

int callback()
{    void *NotUsed; int argc; char **argv; char **azColName;
    NotUsed = 0;
    for (int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    } 
    printf("\n");
    return 0;
}