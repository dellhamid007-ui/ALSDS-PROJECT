# include <stdio.h>
# include <time.h>
#include <stdlib.h>
#include "ENCDEC.h"
#include "USRMGMT.h"
#include "LOGMGMT.h"

int containsSubstring(const char* str, const char* sub) {
    if(!*sub) return 1; // empty string matches
    for(int i = 0; str[i]; i++){
        int j = 0;
        while(str[i+j] && sub[j] && str[i+j]==sub[j]) j++;
        if(!sub[j]) return 1; // full match
    }
    return 0;
}


void strToLower(char *dest, const char *src){
    for (int i = 0; src[i]; i++) {
        dest[i] = charLower((unsigned char)src[i]);
    }
    dest[stringLength(src)] = '\0';
}


int stringFind(const char *text, const char *pattern) {
    if (!*pattern) return 1;

    for (int i = 0; text[i]; i++) {
        int j = 0;
        while (text[i + j] && pattern[j] &&
               text[i + j] == pattern[j]) {
            j++;
        }
        if (pattern[j] == '\0')
            return 1;
    }
    return 0;
}

void stringCopy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}



int isDigit(char c) {
    return (c >= '0' && c <= '9');
}


char* stringCopyN(char* dest, const char* source, int max_len){
    if (max_len <= 0) return dest; 
    
    char* og_dest = dest;
    int i = 0;
    
    while(i < max_len - 1 && *source != '\0'){
        *dest = *source;
        dest++;
        source++;
        i++;
    }
    *dest = '\0';  
    
    return og_dest;
}


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

int Dateformat(const char *date, char *formatted) {
    // Expect DDMMYYYY (8 digits)
    if (stringLength(date) != 8)
        return 0;

    for (int i = 0; i < 8; i++) {
        if (!isDigit(date[i]))
            return 0;
    }

    int day   = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[2] - '0') * 10 + (date[3] - '0');
    int year  = (date[4] - '0') * 1000 +
                (date[5] - '0') * 100 +
                (date[6] - '0') * 10 +
                (date[7] - '0');

    if (month < 1 || month > 12) return 0;
    if (day < 1) return 0;

    switch (month) {
        case 2:
            if (isLeapYear(year)) {
                if (day > 29) return 0;
            } else {
                if (day > 28) return 0;
            }
            break;

        case 4: case 6: case 9: case 11:
            if (day > 30) return 0;
            break;

        default:
            if (day > 31) return 0;
    }

    // Format as DD/MM/YYYY
    sprintf(formatted, "%02d/%02d/%04d", day, month, year);
    return 1;
}


int Timeformat(const char *time , char *formatted ){
// the time should be 4 digits : HH:MM
if (stringLength(time) != 4)
{
    return 0;
}
for (int  i = 0; i < 4; i++)
{
    if (!isDigit((unsigned char )time[i]))
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
        fgets(input, sizeof(input), stdin);


        isValid = Dateformat(input , cutoffDate); // returns 1 if valid
        if (!isValid)
        {
            printf("Invalid date! Please enter in DD/MM/YYYY");
        }
        
        
    } while (!isValid);
    
    
}


void initLogs(struct Log logs[], int n){
    for (int  i = 0; i < n; i++)
    {
        logs[i].user[0] = '\0';
        logs[i].action[0] = '\0';
        logs[i].date[0] = '\0';
        logs[i].time[0] = '\0';
        logs[i].code = -1;//info
    }
    



}
void addLog(struct Log logs[], int n, char user[], char action[], int code) {
    int i;
    for (i = 0; i < n; i++) {
        if (logs[i].user[0] == '\0')
            break;
    }

    if (i == n) {
        printf("Log list is full!\n");
        return;
    }

    stringCopyN(logs[i].user, user, sizeof(logs[i].user));
    stringCopyN(logs[i].action, action, sizeof(logs[i].action));
    logs[i].code = code;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(logs[i].date, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    sprintf(logs[i].time, "%02d:%02d", tm.tm_hour, tm.tm_min);
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
            logs[i].code == 1 ? "WARNING" : "ERROR"); // if code == 1 then print warning else print error 

        
        
        
        
        
        
        
        
        
        
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
        if (compareString(logs[i].user , user) == 0) //im gonna replace it with compare messages 
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
        if (compareString(logs[i].date , date ) == 0)
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
        strToLower(temp_action , logs[i].action);
        if (stringFind(temp_action , search))
        {
            cll++;
        }
        
    }
    return cll;
}


int countBlockedLogs(struct Log logs[], int n){
    int cbl = 0;
    char temp_action[50];
    const char *BlockedDictionary[MAX_KEYWORDS] = {
        "blocked",
        "login blocked",
        "user blocked",
        "suspended account",
        "authentication failed"
    };
    int numberKeywords = sizeof(BlockedDictionary)/sizeof(BlockedDictionary[0]);

    for (int i = 0; i < n; i++) {
        if (logs[i].user[0] == '\0') continue;
        strToLower(temp_action, logs[i].action); // convert once

        for (int k = 0; k < numberKeywords; k++) {
            if (stringFind(temp_action, BlockedDictionary[k])) {
                cbl++;
                break;
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
    int total_logs = infoCount + warningCount + errorCount;
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
        if (logs[j].user[0] == '\0' || logs[j+1].user[0] == '\0')
        continue;
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
        printf("No suspicious activity detected for the user : %s\n", user);
    }

    return err_count >= 3;

}
int dailyConnections(struct Log logs[], int n, char date[]){
    int count = 0;
    const char *LoginDictionary[] = { "welcome", "login", "logged in", "successful login" };
    for (int i = 0; i < n; i++) {
        if (logs[i].user[0] == '\0') continue;
        if (!equalStrings(logs[i].date, date)) continue;

        char temp_action[50];
        strToLower(temp_action, logs[i].action);
        for (int k = 0; k < sizeof(LoginDictionary)/sizeof(LoginDictionary[0]); k++) {
            if (stringFind(temp_action, LoginDictionary[k])) {
                count++;
                break;
            }
        }
    }
    return count;
}


float errorRate(struct Log logs[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        if (logs[i].user[0] != '\0')
            total++;
    }

    if (total == 0) return 0;

    return ((float)countErrorLogs(logs, n) / total) * 100;
}

//CSV : Comma Separated Values

void exportLogsCSV(struct Log logs[], int n){
    FILE *file = fopen("logs.csv", "w");
    if (!file) { 
        printf("Cannot open file!\n"); 
        return; 
    }

    fprintf(file, "user,action,date,time,code\n"); // header
    for (int i = 0; i < n; i++) {
        if (logs[i].user[0] == '\0') continue;
        fprintf(file, "%s,%s,%s,%s,%d\n",
                logs[i].user, logs[i].action,
                logs[i].date, logs[i].time,
                logs[i].code);
    }
    fclose(file);
    printf("Logs exported to logs.csv\n");
}

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

    FILE *file = fopen("archive.csv", "a"); // append to archive file
    if (file == NULL ) {
        printf("Error opening the archive file!\n");
        return;
    }

    // Parse cutoff date into integers
    int cutoff_day   = (cutoff[0]-'0')*10 + (cutoff[1]-'0');
    int cutoff_month = (cutoff[3]-'0')*10 + (cutoff[4]-'0');
    int cutoff_year  = (cutoff[6]-'0')*1000 + (cutoff[7]-'0')*100 + (cutoff[8]-'0')*10 + (cutoff[9]-'0');

    for (int i = 0; i < n; i++) {
        if (logs[i].user[0] == '\0') continue;

        // Parse log date into integers
        int day   = (logs[i].date[0]-'0')*10 + (logs[i].date[1]-'0');
        int month = (logs[i].date[3]-'0')*10 + (logs[i].date[4]-'0');
        int year  = (logs[i].date[6]-'0')*1000 + (logs[i].date[7]-'0')*100 + (logs[i].date[8]-'0')*10 + (logs[i].date[9]-'0');

        // Compare dates properly
        int older = 0;
        if (year < cutoff_year) older = 1;
        else if (year == cutoff_year && month < cutoff_month) older = 1;
        else if (year == cutoff_year && month == cutoff_month && day < cutoff_day) older = 1;

        if (older) {
            fprintf(file, "%s,%s,%s,%s,%d\n",
                logs[i].user,
                logs[i].action,
                logs[i].date,
                logs[i].time,
                logs[i].code
            );

            // Clear archived log
            logs[i].user[0] = '\0';
            logs[i].action[0] = '\0';
            logs[i].date[0] = '\0';
            logs[i].time[0] = '\0';
            logs[i].code = 0;
        }
    }

    fclose(file);
    printf("Logs older than %s are archived successfully.\n", cutoff);
}


void showTopErrors(struct Log logs[], int n){
    int totalErrors = countErrorLogs(logs, n);
    if (totalErrors == 0) {
        printf("No error logs found.\n");
        return;
    }

    char uniqueErrors[n][50]; // store messages
    int frequency[n];
    int uniqueCount = 0;
    for (int i = 0; i < n; i++) frequency[i] = 0;

    for (int i = 0; i < n; i++) {
        if (logs[i].user[0] == '\0' || logs[i].code != 2) continue;

        int isFound = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (compareString(uniqueErrors[j], logs[i].action) == 0) {
                frequency[j]++;
                isFound = 1;
                break;
            }
        }

        if (!isFound) {
            stringCopy(uniqueErrors[uniqueCount], logs[i].action);
            frequency[uniqueCount] = 1;
            uniqueCount++;
        }
    }

    // sort by frequency descending
    for (int i = 0; i < uniqueCount - 1; i++) {
        for (int j = i + 1; j < uniqueCount; j++) {
            if (frequency[j] > frequency[i]) {
                // swap frequency
                int tmp = frequency[i];
                frequency[i] = frequency[j];
                frequency[j] = tmp;
                // swap messages
                char tmpStr[50];
                stringCopy(tmpStr, uniqueErrors[i]);
                stringCopy(uniqueErrors[i], uniqueErrors[j]);
                stringCopy(uniqueErrors[j], tmpStr);
            }
        }
    }

    int topN;
    printf("Enter the number of top frequent errors to display: ");
    scanf("%d", &topN);
    if (topN > uniqueCount) topN = uniqueCount;

    printf("Top %d frequent errors:\n", topN);
    for (int i = 0; i < topN; i++) {
        printf("%s : %d times\n", uniqueErrors[i], frequency[i]);
    }
}

