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

int main(){
    char text[] = "Th1s 1s A TeSt STrinG";

    displayTextStats(text);

    showSecurityTips();

}