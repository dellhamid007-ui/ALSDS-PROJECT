# include <stdio.h>
# include <time.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>
# define MAX_LOGS 100
# define MAX_KEYWORDS 10
struct Log{
char user[20];
char action[50];
char date[20];
char time[10];
int code; // 0 info, 1 warning, 2 error
};
int equalStrings(char a[], char b[]){
    int i= 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
        {
            return 0; //not equal
        }
        i++;
    }
    return (a[i] == '\0' && b[i] =='\0'); // equal if both strings ended
}

int isLeapYear(int year){
    return(year % 4 == 0 &&(year % 100 != 0) || year % 400 == 0);
}


int Dateformat(const char *date ,  char *formatted){ //check if the date format is correct
    // the user needs to enter an 8 digit date (DD/MM/YYYY)
    if (strlen(date) != 8)
    {
        return 0;
    }
    for (int  i = 0; i < 8; i++)
    {
        if (!isdigit((unsigned char)date[i]))
        {
            return 0;
        }
        
    }
    int day = atoi(date); 
    int month = atoi(date + 2);
    int year = atoi(date + 4);
    if (month < 1 || month > 12 )
    {
        return 0;
    }
    if (day < 1 )
    {
        return 0;
    }
    switch (month)
    {
    case 2: //February
        if (isLeapYear(year))
        {
            if (day > 29) // every four years
            {
                return 0;
            }
            
        }else{
            if (day > 28) // the other years
            {
                return 0;
            }
            
        }
        
        break;
       case 4: case 6: case 9: case 11:
     if (day > 30)
     {
        return 0;
     }
     default:
      if (day > 31)
      {
        return 0;
      }
       
    }
    sprintf(formatted ,"%02d/%02d/%04d" , day,month,year );
    return 1;
    


}
int Timeformat(const char *time , char *formatted ){
// the time should be 4 digits : HH:MM
if (strlen(time) != 4)
{
    return 0;
}
for (int  i = 0; i < 4; i++)
{
    if (!isdigit((unsigned char )time[i]))
    {
        return 0;
    }
    
}
int hour = atoi(time);
int minutes = atoi(time + 2);
if (hour < 0 || hour > 23 )
{
    return 0;
}
if (minutes < 0 || minutes > 59)
{
    return 0;
}
formatted[0] = (hour / 10) + '0';
formatted[1] = (hour % 10) + '0';
formatted[2] = ':';
formatted[3] = (minutes / 10) + '0';
formatted[4] = (minutes % 10 ) + '0';
formatted[5] = '\0';
return 1;
}
void getArchiveDate(char cutoffDate[]){ //useful for archiveLogs 
    char input[20]; //input from the user
    char cutoff[20]; // formatted date in the form DD/MM/YYYY
    int isValid;
    do
    {
        printf("Enter cutoff date for archiving (DD/MM/YYYY)");
        scanf("%s", input);
        isValid = Dateformat(input , cutoffDate); // returns 1 if valid
        if (!isValid)
        {
            printf("Invalid date! Please enter in DD/MM/YYYY");
        }
        
        
    } while (!isValid);
    
    
}
void toLowercase (char *dest , char *src){
    for (int  i = 0; src[i]; i++)
    {
        dest[i] = tolower((unsigned char)src[i]);

    
    }
    dest[strlen(src)] = '\0';
    
}
void initLogs(struct Log logs[], int n){
    for (int  i = 0; i < n; i++)
    {
        logs[i].user[0] = '\0';
        logs[i].action[0] = '\0';
        logs[i].date[0] = '\0';
        logs[i].time[0] = '\0';
        logs[i].code = 0;//info
    }
    



}
void addLog(struct Log logs[], int n, char user[], char action[], int code){
    int i;
    for ( i = 0; i < MAX_LOGS; i++)
    {
        if (logs[i].user[0] == '\0') //empty slot
        {
            break;
        }
        
    
    if (i == MAX_LOGS)
    {
        printf("Log list is full cannot add a new log!!");
        return;
    }
    strncpy(logs[i].user , user , sizeof(logs[i].user) - 1);
    logs[i].user[sizeof(logs[i].user)-1] = '\0';

    strncpy(logs[i].action , action , sizeof(logs[i].action) - 1);
    logs[i].action[sizeof(logs[i].action)-1] = '\0';

    logs[i].code = code;

   }

}
void displayLogs(struct Log logs[], int n){
    for (int  i = 0; i < n; i++)
    {
        if (logs[i].user[0] == '\0')
        {
            continue;
        }
        printf("[%s %s] %s: %s (%s)\n", 
            logs[i].date,
            logs[i].time,
            logs[i].user,
            logs[i].action,
            logs[i].code == 0 ? "INFO" :
            logs[i].code == 1 ? "WARNING" : "CODE"); // if code == 1 then print warning else print error 

        
        
        
        
        
        
        
        
        
        
    }
    





}
void searchLogsByUser(struct Log logs[], int n, char user[]){
    
    int isFound = 0;
    for (int  i = 0; i < n; i++)
    {
        if (logs[i].user[0] == '\0')
        {
            continue;
        }
        if (strcmp(logs[i].user , user) == 0) //im gonna replace it with compare messages 
        {
             printf("[%s %s] %s: %s (%s)\n", 
            logs[i].date,
            logs[i].time,
            logs[i].user,
            logs[i].action,
            logs[i].code == 0 ? "INFO" :
            logs[i].code == 1 ? "WARNING" : "CODE");
            isFound =1;
        }
           
    }
    if (!isFound)
    {
        printf("No logs found for user '%s'.\n" , user );
    }
    

}
void searchLogsByDate(struct Log logs[], int n, char date[]){
    int isFound = 0;
    for (int  i = 0; i < n; i++)
    {
        if (logs[i].user[0] == '\0')
        {
          continue;
        }
        if (strcmp(logs[i].date , date ) == 0)
        {
            
             printf("[%s %s] %s: %s (%s)\n", 
            logs[i].date,
            logs[i].time,
            logs[i].user,
            logs[i].action,
            logs[i].code == 0 ? "INFO" :
            logs[i].code == 1 ? "WARNING" : "CODE");
            isFound = 1;            
        }
        
        
    }
    if (!isFound)
    {
        printf("No logs were found for date : %s" , date);
    }
    

}
int countErrorLogs(struct Log logs[], int n){
    int Erc = 0;
    for (int  i = 0; i < n; i++)
    {
        if (logs[i].user[0] == '\0')
        {
            continue;
        }
        if (logs[i].code == 2)
        {
            Erc++;
        }
        
        
    }
    return Erc;

}

int countLoginLogs(struct Log logs[], int n){
    int cll = 0;
    char temp_action[50];
    char search[] = "login"; // the word used for the search
    for (int  i = 0; i < n; i++)
    {
        if (logs[i].user[0] == '\0')
        {
            continue;
        }
        toLowercase(temp_action , logs[i].action);
        if (strstr(temp_action , search) != NULL)
        {
            cll++;
        }
        
    }
    return cll;
}
int countBlockedLogs(struct Log logs[], int n){
    int cbl = 0;
    char temp_action[50];
    // dictionary for blocked logs
    const char *BlockedDictionary[MAX_KEYWORDS] ={
        "blocked",
        "login blocked",
        "user blocked",
        "suspeneded account",
        "authentification failed"





    };
    int numberKeywords = sizeof(BlockedDictionary) / sizeof(BlockedDictionary[0]);
    for (int i = 0; i < n; i++)
    {
        if (logs[i].user[0] == '\0')
        {
            continue;
        }
        int keywords;
        for (keywords = 0; i < numberKeywords; i++)
        {   
            if (strstr(temp_action , BlockedDictionary[keywords])!= NULL
        )
            {
                 cbl++;
                 break;// stop checking once a keyword is found
            }
            
           
           
        }
        
    }
    
   
    return cbl;

}
void displayLogStats(struct Log logs[], int n){
    // count : info,warning,error
    // Login logs
    // Blocked logs 
    int infoCount = 0;
    int warningCount = 0;
    int errorCount = 0;
    for (int  i = 0; i < n; i++)
    {
        if (logs[i].user[0] == '\0') 
        {
            continue;
        }
        switch (logs[i].code) // count code
        {
        case 0: infoCount++; break;
        case 1: warningCount++; break;
        case 2: errorCount++; break;
        }
    }
    // count login events and blocked attempts
    int logincount = countLoginLogs(logs , n);
    int blockedcount = countBlockedLogs(logs , n);
    // stats
    int total_logs = infoCount + warningCount + errorCount + logincount + blockedcount;
    printf("Log statistics\n");
    printf("=================\n");
    printf("Total logs : %d\n", total_logs );
    printf("Info logs : %d\n", infoCount);
    printf("Warning logs : %d\n", warningCount);
    printf("Error logs : %d\n", errorCount );
    printf("Login events : %d\n", logincount);
    printf("Blocked Attempts : %d\n", blockedcount);
     




}
void sortLogsByDate(struct Log logs[], int n){ //bubble sort
    for (int  i = 0; i < n - 1; i++)
    {
       for (int j = 0; j < n - i - 1; j++)
       {
         int day1 = (logs[j].date[0] - '0')*10 + (logs[j].date[1] - '0');
         int month1 = (logs[j].date[3] - '0')*10 + (logs[j].date[4] -'0');
         int year1 = (logs[j].date[6]- '0')*1000 + (logs[j].date[7]-'0')*100 +
                     (logs[j].date[8]- '0')*10 + (logs[j].date[9]-'0');
         int hour1 = (logs[j].time[0] - '0')*10 + (logs[j].time[1]-'0');
         int min1 =  (logs[j].time[3]- '0')*10  + (logs[j].time[4]-'0');

         // the next log
         int day2 = (logs[j+1].date[0] - '0')*10 + (logs[j+1].date[1] - '0');
         int month2 = (logs[j+1].date[3] - '0')*10 + (logs[j+1].date[4] -'0');
         int year2 = (logs[j+1].date[6]- '0')*1000 + (logs[j+1].date[7]-'0')*100 +
                     (logs[j+1].date[8]- '0')*10 + (logs[j+1].date[9]-'0');
         int hour2 = (logs[j+1].time[0] - '0')*10 + (logs[j+1].time[1]-'0');
         int min2 =  (logs[j+1].time[3]- '0')*10  + (logs[j+1].time[4]-'0');
         //comparison of logs 
         int swap = 0;
         if (year1 > year2)
         {
            swap = 1;
         }
         else if (year1 == year2 && month1 > month2)
         {
            swap = 1;
         }
         else if (year1 == year2 && month1 == month2 && day1 > day2 )
         {
             swap = 1;
         }
         else if (year1 == year2 && month1 == month2 && day1 == day2 && hour1 == hour2 && min1 > min2)
         {
             swap = 1;
         }
         if(swap){
            struct Log temp = logs[j];
            logs[j] = logs[j+1];
            logs[j+1] = temp;
         }
         
          
        }
       
    }
}
void sortLogsByUser(struct Log logs[], int n){
   
    for (int  i = 0; i < n - 1; i++)
    {
        for (int  j = 0; j < n - i - 1; j++)
        {
            int swap = 0;
            int idx = 0;
            while (logs[j].user[idx] != '\0' && logs[j+1].user[idx] != '\0')
            {
                if (logs[j].user[idx] > logs[j+1].user[idx])
                {
                    swap = 1;
                    break;
                }
                else if (logs[j].user[idx] < logs[j+1].user[idx])
                {
                    break;
                }
                idx++;
            }
            if (!swap && logs[j].user[idx] != '\0' && logs[j+1].user[idx] == '\0')
            {
                swap = 1;
            }
            
           if(swap){
            struct Log temp = logs[j];
            logs[j] = logs[j+1];
            logs[j+1] = temp;
           }
     }

   }
}
int detectSuspiciousActivity(struct Log logs[], int n,char user[]){
    int err_count = 0;
    for (int  i = 0; i < n; i++)
    {
        if (equalStrings(logs[i].user, user) && logs[i].code == 2)
        {
            err_count++;
        }
        
    }
    if (err_count >= 3)
    {
        printf("Suspicous activity detcted for user :  %s\n ", user);
    }
    else{
        printf("No suspicious activity detected for the user : %s\n");
    }


}
int dailyConncetions(struct Log logs[], int n, char date[]){
    int count = 0;
    //dictionary of keywords for successful login
    const char *LoginDictionary[] = {
        "welcome",
        "login",
        "logged in",
        "successful login"

    };
    for ( int i = 0; i < n; i++)
    {
        if (equalStrings(logs[i].date, date) && equalStrings(logs[i].action, LoginDictionary))
        {
           count++;
        }
        
    }
    return count;
}
float errorRate(struct Log logs[], int n){
    reutrn (n == 0) ? 0 : ((float)countErrorLogs(logs, n) /n) * 100; // checking if n = 0 if it's true then return 0 (avoid div by 0), else calculate error rate
}

//CSV : Comma Separated Values

void exportLogsCSV(struct Log logs[], int n){
    // fopen will return NULL if it fails , which can be for several reasons :
    // 1.The program doesn't have write permission.
    //2.file doesn't exist

   
   
    FILE *file = fopen("logs.csv", "w"); //open the file in write mode
    if (file == NULL) 
    {
        printf("Cannot open the file!\n");
        return;
    }
    
}
fclose(file);
void importLogsCSV(struct Log logs[], int n){
    //1.Open the file in read mode.
    //2.Skip the header line.
    //3.Read each line of the file.
    //4.Split it into fields and store it in logs[] array.
    //Note : CSV files often contain the names of columns i.e what each field separates not actual data that's why we skip it
    FILE *file = fopen("logs.csv", "r");
    if (file == NULL)
    {
        printf("Error while opening the file!\n");
        return;
    }
    char line[200]; // buffer to hold each line
    
    fgets(line , sizeof(line), file);
    
    int i = 0;
    
    while(fgets(line , sizeof(line), file) && i < n){; //skip the header line (reads it but does nothing with it)
    int i =0;
    sscanf(line , "%[^,],%[^,],%[^,],%[^,],%d",
        logs[i].user,
        logs[i].action,
        logs[i].date,
        logs[i].time,
        &logs[i].code);
        i++;
    }
    fclose(file); 
    printf("Logs imported from logs.csv\n");
}
void clearLogs(struct Log logs[], int n){
 //Note : if the first character of the string is a NULL character that mean the string is empty 
    for (int i = 0; i < n; i++)
{
    logs[i].user[0] = '\0';
    logs[i].action[0] = '\0';
    logs[i].date[0] = '\0';
    logs[i].time[0] = '\0';
    logs[i].code = 0; //set code to info
}
printf("All logs are cleared.\n");

}
void recentLogs(struct Log logs[], int n, int nb){
    // n : total number of logs
    // nb : number of recent logs you want to display
    if (nb > n)
    {
        nb = n; //Adjust it to all logs
    
    }
    int reverse; // for the user to choose on how how to display logs
    do
    {
        printf("Choose order : 0 for normal, 1 for reverse");
        scanf("%d", &reverse);
        if (reverse != 0 && reverse != 1)
        {
            printf("Invalid choice! Please enter 0 or 1.\n");
        }
        
    } while (reverse != 0 && reverse != 1);
    if (reverse == 0)
    {
        //Normal order: oldest --> newest
        struct Log temp[nb];
        for (int  i = 0; i < nb; i++)
        {
            temp[i] = logs[n - nb + i];
        }
        displayLogs(temp , nb);
    }
    else{
        //Reverse order: newest --> oldest
       for (int  i = n -1 ; i >= n - nb; i--)
       {   
        struct Log single[1];// temporary single element array for displaylogs
        single[0] = logs[i];
        displayLogs(single , 1); // reuse displaylogs
       }
    }
   
}
void archiveLogs(struct Log logs[], int n){
    char cutoff[20];
    getArchiveDate(cutoff);
    
    
    FILE *file = fopen("archive.csv", "a"); //append to archive file
    if (file == NULL )
    {
        printf("Error opening the archive file!\n");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        
    if (logs[i].user[0] != '\0' && strcmp(logs[i].date, cutoff) < 0) // archiving only existing logs and older than the cutoff date specified by the user
    {
        fprintf(file, "%s,%s,%s,%s,%d\n",
            logs[i].user,
            logs[i].action,
            logs[i].date,
            logs[i].time,
            logs[i].code
        
        
        
        
        );
        // clear archived log since we no longer need them in the main logs[] array
        logs[i].user[0] = '\0';
        logs[i].action[0] = '\0';
        logs[i].date[0] = '\0';
        logs[i].time[0] = '\0';
        logs[i].code = 0;
    }
}    
fclose(file);
printf("Logs older than %s are archived successdully.\n", cutoff);


}

void showTopErrors(struct Log logs[], int n){
// loop through all logs
// count only logs with code == 2
// count the frequency of each unique error message
// display top frequent errors
int totalErrors = countErrorLogs(logs , n);
if (totalErrors == 0)
{
    printf("No error logs found.\n");
    return;
}
// array to store unique error messages and counts them
int uniqueErrors[n][50]; //each row represents one error message and each column holds the characters of that message
int frequency[n];
int uniqueCount = 0;
for (int i = 0; i < n; i++)
{
    frequency[i] = 0;
}

for (int  i = 0; i < n; i++)
{
    if (logs[i].user[0] == '\0' || logs[i].code != 2)
    {
        continue;
    }
    int isFound = 0;
    for (int  j = 0; i < uniqueCount; j++)
    {
        if (strcmp(uniqueErrors[j],logs[i].action ) == 0)
        {
            frequency[j]++;
            isFound = 1;
            break;
        }
        
    }
    if (!isFound)
    {
        strcpy(uniqueErrors[uniqueCount], logs[i].action);
        frequency[uniqueCount] = 1;
        uniqueCount++;
    }
    
    
}
// sorting errors by frequency(descending order)
for (int  i = 0; i < uniqueCount - 1 ; i++)
{
    for (int  j = i + 1; j < uniqueCount; j++)
    {
        if (frequency[j] > frequency[i])
        {
            int temp = frequency[i];
            frequency[i] = frequency[j];
            frequency[j] = temp; // swap counts
        }
        //swap messages
        char tempStr[50];
        strcpy(tempStr , uniqueErrors[i]);
        strcpy(uniqueErrors[i] , uniqueErrors[j]);
        strcpy(uniqueErrors[j], tempStr);
    }
    
}
int topN;
printf("Enter the number of top frequent errors to display:");
scanf("%d", &topN);
if (topN > uniqueCount)
{
    topN = uniqueCount;
}
printf("Top %d frequent errors:\n", topN);
for (int i = 0; i < topN; i++)
{
    printf("%s : %d times\n", uniqueErrors[i], frequency[i]);
}








}
