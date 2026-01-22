#ifndef LOGMGMT_H
#define LOGMGMT_H



#define LOGMGMT_H

// Structure for a log entry
struct Log {
    char user[20];
    char action[50];
    char date[20];
    char time[10];
    int code; // 0 = info, 1 = warning, 2 = error
};
int equalStrings(char a[], char b[]);
int isLeapYear(int year);
int Dateformat(const char *date ,  char *formatted);
int Timeformat(const char *time , char *formatted );
void getArchiveDate(char cutoffDate[]);
void toLowercase (char *dest , char *src);

// 1. Initializes log list
void initLogs(struct Log logs[], int n);

// 2. Adds a log entry
void addLog(struct Log logs[], int n, char user[], char action[], int code);

// 3. Displays all logs
void displayLogs(struct Log logs[], int n);

// 4. Searches logs by user
void searchLogsByUser(struct Log logs[], int n, char user[]);

// 5. Searches logs by date
void searchLogsByDate(struct Log logs[], int n, char date[]);

// 6. Counts error entries
int countErrorLogs(struct Log logs[], int n);

// 7. Counts login events
int countLoginLogs(struct Log logs[], int n);

// 8. Counts blocked attempts
int countBlockedLogs(struct Log logs[], int n);

// 9. Shows statistics
void displayLogStats(struct Log logs[], int n);

// 10. Sorts logs by date
void sortLogsByDate(struct Log logs[], int n);

// 11. Sorts logs by username
void sortLogsByUser(struct Log logs[], int n);

// 12. Detects anomalies for a user
int detectSuspiciousActivity(struct Log logs[], int n, char user[]);

// 13. Counts daily connections
int dailyConnections(struct Log logs[], int n, char date[]);

// 14. Computes error percentage
float errorRate(struct Log logs[], int n);

// 15. Exports logs to CSV
void exportLogsCSV(struct Log logs[], int n);

// 16. Imports logs from CSV
void importLogsCSV(struct Log logs[], int n);

// 17. Clears all logs
void clearLogs(struct Log logs[], int n);

// 18. Displays last events
void recentLogs(struct Log logs[], int n, int nb);

// 19. Archives old logs
void archiveLogs(struct Log logs[], int n);

// 20. Displays top frequent errors
void showTopErrors(struct Log logs[], int n);





#define ver "1.0.0"

#endif