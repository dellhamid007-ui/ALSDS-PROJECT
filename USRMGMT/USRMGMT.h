#ifndef USRMGMT_H
#define USRMGMT_H

struct User{                                                    //Deleted <-> can be overwritten
    char name[20];          //0 for deleted users
    char password[20];      //0 for deleted users    
    int role;               //0:user, 1:admin, 999:deleted 
    int state;              //0:active 1:blocked 999:deleted
};



int passwordScore(char pass[]);
int textLength(char text[]);



int checkWhitespace(char c);
char* stringModify(char* dest, const char* source);
int compareString(const char *str1, const char *str2 );
void initUsers(struct User users[], int n);
void displayUsers(struct User users[],int n);
void addUser(struct User users[],int n);
int searchUser(struct User users[], int n, char name[]);
void deleteUser(struct User users[], int n, char *name);
void changePassword(struct User users[], int n, char name[]);
int checkLogin(struct User users[], int n, char name[], char pass[]);
int strongPassword(char pass[]);
void blockUser(struct User users[], int n, char name[]);
void unblockUser(struct User users[], int n, char name[]);
void changeRole(struct User users[], int n, char name[], int role);
void listAdmins(struct User users[], int n); 
int stringLength(char str[]);
int containsUppercase(char str[]);
int containsLowercase(char str[]);
int containsDigit(char str[]);
int containsSymbol(char str[]);
void userStatistics(struct User users[], int n);
void saveUsers(struct User users[], int n);
void loadUsers(struct User users[], int n);





#define ver "1.0.0"
#endif