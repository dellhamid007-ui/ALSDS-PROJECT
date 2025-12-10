#include <stdio.h>
#include<string.h>
struct User{                                                    //Deleted <-> can be overwritten
    char name[20];          //0 for deleted users
    char password[20];      //0 for deleted users    
    int role;               //0:user, 1:admin, 999:deleted 
    int state;              //0:active 1:blocked 999:deleted
};
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
            return i;  // Found at index i
        }
    }
    return -1;  // Not found
}

void deleteUser(struct User users[], int n, char *name){
    printf("Enter the User you want to delete: "); scanf("%19s", name);

    int usrIndex = searchUser(users, n, name);
    int found = 0;

    if(usrIndex != -1){
        stringModify(users[usrIndex].name, "0");
        stringModify(users[usrIndex].password, "0");
        users[usrIndex].role = 999;
        users[usrIndex].state = 999;     
        printf("User Successfully deleted");

    }
    else printf("ERROR: User Not found\n");
}


int main(){
    char name[20];
    struct User users[5];
    stringModify(users[0].name,"User1");
    stringModify(users[1].name,"User2");
    stringModify(users[2].name,"User3");
    stringModify(users[3].name,"User4");
    stringModify(users[4].name,"User5");

    displayUsers(users,5);

    initUsers(users,5);


    displayUsers(users,5);

    addUser(users, 3);
    stringModify(users[4].name,"User5");
    users[4].role = 1;

    displayUsers(users,5);

    deleteUser(users,5,name);
    
    displayUsers(users,5);
}

