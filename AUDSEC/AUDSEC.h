
#ifndef __AUDSEC_H__
#define __AUDSEC_H__

#include "../USRMGMT/USRMGMT.h"

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
int globalSecurityLevel(struct User users[], int n);








#define VER "1.0.0"

#endif