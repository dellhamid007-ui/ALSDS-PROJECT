
#ifndef __AUDSEC_H__
#define __AUDSEC_H__

struct User{                                                    //Deleted <-> can be overwritten
    char name[20];          //0 for deleted users
    char password[20];      //0 for deleted users    
    int role;               //0:user, 1:admin, 999:deleted 
    int state;              //0:active 1:blocked 999:deleted
};

int textLength(char text[]);
int countUppercase(char text[]);
int countLowercase(char text[]);  
int countDigits(char text[]); 
float percentUppercase(char text[]);
void displayTextStats(char text[]);
int veryStrongPassword(char pass[]);
void generateKey(int length, char key[]);
int isHexKey(char key[]);
void generateRandomPassword(int length, char pass[]);
int passwordScore(char pass[]);
float averageScore(struct User users[], int n);
void displaySecurityReport(struct User users[], int n);
int countStrongUsers(struct User users[], int n);
void showSecurityTips();
int checkEmailFormat(char email[]);
int checkLoginFormat(char name[]);
void generateHexKey(int length, char key[]); 
void top3Passwords(struct User users[], int n);







#define VER "1.0.0"

#endif