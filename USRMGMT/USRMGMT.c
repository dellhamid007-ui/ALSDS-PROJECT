#include <stdio.h>
#include <string.h>
#include "USRMGMT.h"

int checkWhitespace(char c){  //to fix usernames not matching
    return(c == ' ' || c == '\t' || c== '\n' || c == '\r' || c == '\f' || c == 'v' );
}

char* stringModify(char* dest, const char* source){ //rewritten strcpy
    char* og_dest = dest;

    while(*source != '\0'){
        *dest = *source;
        dest ++;
        source ++;
    }

    *dest = '\0';
    
    return og_dest;
}

int compareString(const char *str1, const char *str2 ){ //rewritten strcmp
    while(1){
        while(checkWhitespace(*str1)) str1++;
        while(checkWhitespace(*str2)) str2++;

        if(*str1 == '\0' && *str2 == '\0') return 0;

        if(*str1 != *str2) return (int)((unsigned char)*str1 - (unsigned char)*str2);

        
        if(*str1 != '\0') str1++;
        if(*str2 != '\0') str2++;
    }
}



void initUsers(struct User users[], int n){
    for(int i = 0; i<n;i++){
        stringModify(users[i].name, "0");
        stringModify(users[i].password, "0");
        users[i].role = 999;
        users[i].state = 999;
    }

    printf("User list initialized!\n");
}

void displayUsers(struct User users[],int n){
    for(int i=0; i<n; i++){
        printf("%d-%s\n",i+1,users[i].name);
    }
}

void addUser(struct User users[],int n){
    if(users[n].state =999){
        printf("Enter Username:"); scanf("%s",&users[n].name);
        printf("Enter Password: "); scanf("%s",&users[n].password);
        printf("Choose User role: "); scanf("%d",&users[n].role);
        if(users[n].role < 0 || users[n].role >1 ){
            printf("ERROR: Invalid Role\n");
                stringModify(users[n].name, "0");
                stringModify(users[n].password, "0");
                users[n].role = 999;
                users[n].state = 999;   
        }
        else users[n].state = 0;

    }
    else printf("ERROR: User Already exists");
}

int searchUser(struct User users[], int n, char name[]){
    for(int i = 0; i < n; i++) {
        if (compareString(users[i].name, name) == 0) {
            return i + 1;  // Found at index i
        }
    }
    return -1;  // Not found
}

void deleteUser(struct User users[], int n, char *name){
    printf("Enter the User you want to delete: "); scanf("%19s", name);

    int usrIndex = searchUser(users, n, name) - 1;
    int found = 0;

    if(compareString(name, users[usrIndex].name) == 0){
        stringModify(users[usrIndex].name, "0");
        stringModify(users[usrIndex].password, "0");
        users[usrIndex].role = 999;
        users[usrIndex].state = 999;     
        printf("User Successfully deleted\n");

    }
    else printf("ERROR: User Not found\n");
}

void changePassword(struct User users[], int n, char name[]){
    int usrIndex = searchUser(users, n, name) - 1;
    char newPass[20];
    printf("Enter the new password: "); scanf("%s",&newPass);

    stringModify(users[usrIndex].password, newPass);
    
}


int checkLogin(struct User users[], int n, char name[], char pass[]){
    int usrIndex = searchUser(users, n, name) - 1;
    if (compareString(name, users[usrIndex].name) == 0){
        if(compareString(pass, users[usrIndex].password) == 0){
            return 1;
        }
        else return 0;
    }
    else return 0;
}

int strongPassword(char pass[]){
    if (passwordScore(pass) >= 60) return 1;
    else return 0;
}

void blockUser(struct User users[], int n, char name[]){
    int usrIndex = searchUser(users, n, name) - 1;

    if(users[usrIndex].role == 0){
        if(users[usrIndex].state == 0){
            users[usrIndex].state = 1;
            printf("User Blocked Successfully\n");
        }
        else printf("User is already blocked or is deleted\n");
    }
    else printf("Cannot block an admin\n");
}

void unblockUser(struct User users[], int n, char name[]){

    int usrIndex = searchUser(users, n, name) - 1;

    if(users[usrIndex].state == 1){
            users[usrIndex].state = 0;
            printf("User Unblocked Successfully\n");
        }
        else printf("User is not blocked\n");
}

void changeRole(struct User users[], int n, char name[], int role){

    int usrIndex = searchUser(users, n, name) - 1;

    if(users[usrIndex].role == role){
        printf("User already has this role\n");
    }
    else{
        users[usrIndex].role = role;
        printf("Role was successfully changed\n");
    }
}

void listAdmins(struct User users[], int n){
    printf("ID- Admin Username\n");
    for(int i =0; i<n ; i++){
        if(users[i].role == 1){
            printf("%d- %s\n", i+1, users[i].name);
        }
    }
}

int stringLength(char str[]){
    int i;
    for(i = 0; str[i] != '\0'; i++);

    return i;
}

int containsUppercase(char str[]){
    int i =0;
    while(str[i] != '\0'){
        if(str[i] >= 'A' && str[i] <= 'Z' ) return 1;
        else i++;
    }
    return 0;
}

int containsLowercase(char str[]){
    int i =0;
    while(str[i] != '\0'){
        if(str[i] >= 'a' && str[i] <= 'z' ) return 1;
        else i++;
    }
    return 0;
}

int containsDigit(char str[]){
    int i =0;
    while(str[i] != '\0'){
        if(str[i] >= '0' && str[i] <= '9' ) return 1;
        else i++;
    }
    return 0;
}

int containsSymbol(char str[]){   //Reused the lookup table approach
    
    char SpecialList[] = "`~!@#$%%^&*()_+=-|[{}]'/;:.>,<";
    //creating a lookup table
    int lookup[256] ={0};

    for (int i =0; SpecialList[i] !='\0'; i++){
        unsigned char c = (unsigned char)SpecialList[i];
        lookup[c] =1;
    }

    int i =0;
    while(str[i] != '\0'){
        unsigned char c = str[i];
        if(lookup[c]) return 1;
        else i++;
    }
    return 0;

}