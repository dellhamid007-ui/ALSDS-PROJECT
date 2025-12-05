#include <time.h>
#include <stdio.h>
#include <string.h>

struct User{
    char name[20];
    char password[20];
    int role; //0: User, 1: Admin
    int state;  //0: Active, 2:Blocked
};


int textLength(char text[]){
    int len = 0;

    while(text[len] != '\0'){
        len ++;
    }
    return len;
}

int countDigits(char text[]){
    int count = 0;
    for (int i=0; i<= textLength(text); i++) {
        if (text[i]>= '0' && text[i] <= '9') {
            count++;
        }
    }

    return count;
}

int countUppercase(char text[]){
    int count = 0;
    for (int i=0; i<= textLength(text); i++){
        if (text[i]>= 'A' && text[i] <= 'Z') {
            count++;
        }
    }

    return count;
}


int countLowercase(char text[]){
    int count = 0;
    for (int i=0; i<= textLength(text); i++){
        if (text[i]>= 'a' && text[i] <= 'z') {
            count++;
        }
    }

    return count;
}


float percentUppercase(char text[]){
    float percentage = ((float)countUppercase(text)/(float)textLength(text))*100;

    return percentage;
}

void displayTextStats(char text[]){
    printf("The number of Uppercase letters: %d\nThe number of Lowercase letters: %d\nThe number of Digits: %d\nThe text is: %d characters long\nUppercase Letters percentage:%.2f%%\n",countUppercase(text),countLowercase(text),countDigits(text),textLength(text),percentUppercase(text));
}

void showSecurityTips(){
    printf("Security tips:\n1-Use a mix of uppercase letters, lowercase letters, digits, and special characters in your password.\n2-Regularly change your password.\n3-NEVER share your password with others.\n4-Beware of scams and phishing sites.");
}


int getSpecCharNumber(char pass[]){
    int counter = 0;
    //establishing usable special characters
    char SpecialList[] = "@!?#$&*_/~";
    //creating a lookup table
    int lookup[256] ={0};

    for (int i =0; SpecialList[i] !='\0'; i++){
        unsigned char c = (unsigned char)SpecialList[i];
        lookup[c] =1;
    }

    //counting special characters
    for(int i =0; pass[i] !='\0'; i++){
        unsigned char c = (unsigned char)pass[i];
        if(lookup[c]){
            counter++;
        }
    }
    return counter;

}

int passwordScore(char pass[]){   //score is capped at 100, passwords of score 60 and above are strong, passwords of score 90 are very strong
    float basescore = 30; //constant base score for all passwords
    int len = textLength(pass); //used to count extra score from length
    float upc = percentUppercase(pass);
    int SpecChar = getSpecCharNumber(pass);

    int _bonus = (25 - 0.01*(upc - 50)*(upc- 50)) + (SpecChar *8) + (len - 8) ;   

    int finalscore = basescore + _bonus;

     if (finalscore <= 100) return finalscore;
     else return 100; // to prevent score from going above max
}

int veryStrongPassword(char pass[]){
    if (passwordScore(pass) >= 90) return 1;
    else return 0;
}

float averageScore(struct User users[],int n){
    float sum = 0;
    for(int i =0; i<n;i++){
        sum += (float)passwordScore(users[i].password);
    }

    float avg = sum / n;
    return avg;
}

int countStrongUsers(struct User users[], int n){
    int count = 0;
    for(int i = 0;i<n; i++){
        if(passwordScore(users[i].password)>=60) count ++;
    }

    return count;
}

void top3Passwords(struct User users[], int n){ //sorts only first 3 users, then checks if others make it to the top 3
    int top1 = 0;
    int top2 = 1;
    int top3 = 2;

    int top1_score = passwordScore(users[0].password);
    int top2_score = passwordScore(users[1].password);
    int top3_score = passwordScore(users[2].password);

    if(top2_score > top1_score){
        int tmp_index = top1;
        top1 = top2;
        top2 = tmp_index;

        int tmp_score = top1_score;
        top1_score = top2_score;
        top2_score = tmp_score;
    }

    if (top3_score > top1_score){
        top3 = top2;
        top2 = top1;
        top1 = 2;
    }
    else if(top3_score > top2_score){
        top3 = top2;
        top2 = 2;
    }

    for(int i =3; i<n; i++){
        int score = passwordScore(users[i].password);

        if(score> passwordScore(users[top1].password)){
            top3 = top2;
            top2 = top1;
            top1 = i;
        }
        else if(score> passwordScore(users[top2].password)){
            top3 = top2;
            top2 = i;
        }
        else if(score> passwordScore(users[top3].password)){
            top3 = i;
        }
    }

    printf("Top 3 Passwords:\n");
    printf("1-%s Score: %d\n", users[top1].password, passwordScore(users[top1].password));
    printf("2-%s Score: %d\n", users[top2].password, passwordScore(users[top2].password));
    printf("3-%s Score: %d\n", users[top3].password, passwordScore(users[top3].password));


}

int RNG(){              //Random Number Generator using LCG and time.h
    static unsigned int seed = 0;

    if(seed == 0){
        seed = time(NULL); //returns current Unix Epoch time
       }   
    
    seed = seed * 1103515245 + 12345; //Arbitrary numbers, not truly random but too chaotic to predict

    return seed;
}

void generateKey(int length, char key[]){   //Must be maxed at 30 characters due to weak RNG
    char characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i =0; i<length;i++){
        int index = (unsigned int)RNG() % 36;
        key[i] = characters[index];
    }
    key[length+1] = '\0'; //Null Terminator
}

void generateHexKey(int length, char key[]){    
    char characters[] = "0123456789ABCDEF";
    for(int i =0; i<length;i++){
        int index = (unsigned int)RNG() % 16;
        key[i] = characters[index];
    }
    key[length+1] = '\0'; //Null Terminator
}

int isHexKey(char key[]){       //Also uses a lookup table like getSpecCharNumber() //case sensitive
    char HexList[] = "0123456789ABCDEF";

    int lookup[256] ={0};

    for (int i =0; HexList[i] !='\0'; i++){
        unsigned char c = (unsigned char)HexList[i];
        lookup[c] =1;
    }

    for(int i =0; key[i] !='\0'; i++){
        unsigned char c = (unsigned char)key[i];
        if(!lookup[c]){
            return 0;
        }
    }
    return 1;

}

void generateRandomPassword(int length, char pass[]){  //Must be maxed at 30 characters due to weak RNG
    char characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@!?#$&*_/~";
    for(int i =0; i<length;i++){
        int index = (unsigned int)RNG() % 72;
        pass[i] = characters[index];
    }
    pass[length+1] = '\0'; //Null Terminator
}



int checkEmailFormat(char email[]){ //email rules are included in the .txt file
    int ATcounter = 0; //makes sure @ is not used twice

    char AllowedCharacters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.-_@0123456789";
    //creating a lookup table
    int lookup[256] ={0};

    for (int i =0; AllowedCharacters[i] !='\0'; i++){
        unsigned char c = (unsigned char)AllowedCharacters[i];
        lookup[c] =1;
    }

    if(email[0] == '@' || email[0] =='.') return 0;

    for (int i = 0; email[i] != '\0'; i++)
    {
        unsigned char c = (unsigned char)email[i];
        if(!lookup[c]) return 0;
        else{
            if (email[i] == '@') ATcounter++;
            
            if(email[i] == '.' && email[i+1] == '.') return 0;
            if(email[i] == '.' && email[i+1] == '@') return 0;
            if(email[i] == '@' && email[i+1] == '.') return 0;
            if(email[i] == '.' && email[i+1] == '\0') return 0;
            if(email[i] == '@' && email[i+1] == '\0') return 0;
        }


        
    }
    if (ATcounter != 1) return 0;
    else return 1;


    

}

void displaySecurityReport(struct User users[], int n){
    float avg_score = averageScore(users,n);
    int strong_users = countStrongUsers(users, n);

    printf("Total amount of users: %d\n", n);
    printf("The average password Score: %.2f ",avg_score);
    if(avg_score>=90) printf("(Very Strong)\n");
    else {
        if (avg_score >= 60) printf("(Strong)\n");  
        else {
            if(avg_score>= 40) printf("(Decent)\n");
            else printf("(Weak)\n");
        }
    }

    printf("The amount of users with strong passwords: %d\n",strong_users);
    top3Passwords(users,n);
}


int main(){
    struct User users[5];
    char pass[20];

    int user_count = sizeof(users)/ sizeof(users[0]);

    generateRandomPassword(20,pass);
    strcpy(users[0].password,pass);
    generateRandomPassword(20,pass);
    strcpy(users[1].password,pass);
    generateRandomPassword(20,pass);
    strcpy(users[2].password,pass);
    generateRandomPassword(20,pass);
    strcpy(users[3].password,pass);
    generateRandomPassword(20,pass);
    strcpy(users[4].password,pass);
    
    displaySecurityReport(users,user_count);
}