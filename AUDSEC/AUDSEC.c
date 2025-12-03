#include <stdio.h>
#include <string.h>

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
    char SpecialList[] = "0123456789@!?#$&*_/~";
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

    int _bonus = (40 - 0.016*(upc - 50)*(upc- 50)) + (SpecChar *5) + (len - 8) ;   

    int finalscore = basescore + _bonus;

     if (finalscore <= 100) return finalscore;
     else return 100; // to prevent score from going above max
}

int main(){
    char text[] = "Th1s 1s A TeSt STrinG";

    printf("%d",passwordScore(""));

}