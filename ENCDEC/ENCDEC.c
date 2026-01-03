# include <stdio.h>
#include "ENCDEC.h"
#include "../USRMGMT/USRMGMT.h"




int find_newline(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            return i;
        }
        i++;
    }
    return -1; 
}


void inputMessage(struct Message *m) {
    printf("Enter a message: \t");
    fgets(m->text, 200, stdin);
    
    
    int newline_pos = find_newline(m->text);
    if (newline_pos != -1) {
        m->text[newline_pos] = '\0';
    }
}


void DisplayMessage( struct Message m){
    printf("\nYou entered : \t%s" , m.text);
    
    
}



int isUppercase(char c ){
    if (c  >= 'A' && c <= 'Z')
    {
        return 1; 
    }else{
        return 0; 
    }

    
}

char charUpper(char c){
    if(isUppercase(c) == 1) return c;

    if(isLowercase(c) == 1) return c-32;

    return c;
}

char charLower(char c){
    if(isLowercase(c) == 1) return c;

    if(isUppercase(c) == 1) return c+32;

    return c;
}



int isLowercase(char c){
    if (c >= 'a' && c <= 'z')
    {
        return 1; 
    }else{
        return 0; 
    }
    
}




int isAlphabetic(char c){
    if (isUppercase(c) || isLowercase(c))
    {
        
        return 1;

    }else{
        
        return 0;
    }
}   



void toUppercase( struct Message *m){
    
     for (int  i = 0; i < stringLength(m->text); i++)
     {
        if (isLowercase(m->text[i]))
        {
            m->text[i] = m->text[i] - ('a' - 'A'); 
            
        }
        
     }
     
}




void toLowercase(struct Message *m){
    for (int  i = 0; i < stringLength(m->text); i++)
    {
        if (isUppercase(m->text[i]))
        {
            m->text[i] = m->text[i] + ('a' - 'A');
        }
        
    }
    
}



void reverseMessage(struct Message* m){
int i = 0;
int j = stringLength(m->text) - 1;
char temp;
while (i < j)
{
    temp = m->text[i];
    m->text[i] = m->text[j];
    m->text[j] = temp;
    i++;
    j--; 
    
}
    
}  



void removeSpaces(struct Message *m){
    int i = 0, j = 0;
    char temp[200];
    while (m->text[i] != '\0')
    {
        if (m->text[i] != ' ')
        {
            temp[j++] = m->text[i];
            
        }
        i++;
    }
    temp[j] = '\0';
    stringModify(m->text, temp);
    

    
    
}



void encryptCesar(struct Message *m , int key){   
    int i;
    

    
    for (int  i = 0; i < stringLength(m->text); i++)
    {
       if (isUppercase(m->text[i]))
       {
            m->text[i] = ((m->text[i] + key - 'A') % 26) + 'A';
       }
       else if (isLowercase(m->text[i]))
       {
         m->text[i] = ((m->text[i] + key - 'a') % 26) + 'a';
       }
       
       
        
    }
    
    
}



void decryptCesar(struct Message *m , int key ){  
    int i;
    
        for (i = 0; m->text[i] != '\0'; i++)
        {
            if (isUppercase(m->text[i]))
            {
                m->text[i] = ((m->text[i] -'A' - key + 26 ) % 26) + 'A';
            }
            else if (isLowercase(m->text[i]))
            {
                m->text[i] = ((m->text[i] - 'a'- key + 26) % 26) + 'a';
            }
            else{
                m->text[i] = m->text[i];
            }
            

        }
        m->text[i] = '\0';    
    
}

void toHexString(const unsigned char *inputText, int len, char *outputText) { 
    const char hex[] = "0123456789ABCDEF";
    for (size_t i = 0; i < len; i++) {
        outputText[i*2]     = hex[(inputText[i] >> 4) & 0xF];
        outputText[i*2 + 1] = hex[inputText[i] & 0xF];
    }
    outputText[len*2] = '\0'; 
}


    void encryptXOR(struct Message *m, unsigned char  key){
        
        for (int  i = 0; i < stringLength(m->text); i++)
        {
            m->text[i] ^= (unsigned char) key;
        }

        
        printf("%s", m->text);
    }

    unsigned char hexCharToByte(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
    return 0; 
}


void hexStringToBytes(const char *hex, int len, unsigned char *outputText) {

    for (int  i = 0; i < len; i++) {
        unsigned char high = hexCharToByte(hex[i*2]);
        unsigned char low  = hexCharToByte(hex[i*2 + 1]);
        outputText[i] = (high << 4) | low;
    }
}


void decryptXOR(struct Message *m , int key){
        for (int  i = 0; i < stringLength(m->text); i++)
        {
            m->text[i] ^= (unsigned char ) key;
        }


}

    
void encryptSubstitution(struct Message *m , char key[26]){
    if (m == NULL || m->text == NULL) return;

    for (int i = 0; m->text[i] != '\0'; i++) {
        if (isLowercase(m->text[i])) {
            int index = m->text[i] - 'a';
            if (index >= 0 && index < 26) {
                m->text[i] = charLower(key[index]); 
            }
        } else if (isUppercase(m->text[i])) {
            int index = m->text[i] - 'A';
            if (index >= 0 && index < 26) {
                m->text[i] = charUpper(key[index]); 
            }
        }
        
    }
}


void decryptSubstitution(struct Message *m, char key[26]){
    if (m ==NULL || m->text == NULL) return;

    char reverseUppercase[26] = {};
    char reverseLowercase[26] = {};

    for(int i =0; i<26; i++){
        char keyChar = key[i];


        if(isUppercase(keyChar)){
            reverseUppercase[keyChar - 'A'] = 'A' + i;
            reverseLowercase[keyChar - 'A'] = 'a' + i;
        }
        else if(isLowercase(keyChar)){
            reverseUppercase[keyChar - 'a'] = 'A' + i;
            reverseLowercase[keyChar - 'a'] = 'a' + i;
        }
    }

    for (int i =0; m->text[i] != '\0'; i++){
        char current = m->text[i];
        if(isUppercase(current)){
            m->text[i] = reverseUppercase[current - 'A'];
        }
        else if(isLowercase(current)){
            m->text[i] = reverseLowercase[current - 'a'];

        }
    }
}
int isValidKey(char key[27]){
   int frq[26] ={0};

 
   if (stringLength(key) > 27) 
   {
      return 0;
   }

   for(int i =0; i<26;i++){
        if(!isAlphabetic(key[i])){
            return 0;
        }

        int index = charLower(key[i]) - 'a';
        frq[index]++;
   }

   for(int i=0; i<26; i++){
    if(frq[i] !=1){
        return 0;
    }
   }

   return 1;
    
}
int compareMessages(struct Message m1 , struct Message m2){
    struct Message m1copy = m1;
    struct Message m2copy = m2;

    toLowercase(&m1copy);
    toLowercase(&m2copy);
    int i = 0 , j =0;
    while (m1copy.text[i] != '\0' && m2copy.text[j] != '\0')
    {
        while(m1copy.text[i] != '\0' && !isAlphabetic(m1copy.text[i]))i++;
        while(m2copy.text[j] != '\0' && !isAlphabetic(m2copy.text[j]))j++;
        if (m1copy.text[i] == '\0' && m2copy.text[j] == '\0')
        {
            break;
        }
        if (m1copy.text[i] != m2copy.text[j])
        {
            return 0;
        }
        i++;
        j++;
        
    }
    
    return 1;
}
int countCharacter(struct Message m , char c){
    int count = 0;
    for (int  i = 0; i < stringLength(m.text); i++)
    {
        if (m.text[i] == c)
        {
            count++;
        }
        
    }
    return count;



}
void frequencyAnalysis(struct Message m){
    int frq[26] = {0};
    char c;
    for (int  i = 0; i < stringLength(m.text); i++)
    {
        char c = m.text[i];
        if (isUppercase(c))
        {
            frq[c - 'A']++;
        }
        else if (isLowercase(c))
        {
            frq[c - 'a']++;
        }
        
        

    }
     printf("Frequency analysis of the message :\n");
     for (int i = 0; i < 26; i++)
     {
        if (frq[i] > 0)
        {
            printf("%c : %d\n" , 'A' + i , frq[i] );
        }
        
     }
        


}
double coincidenceIndex(struct Message m){
    int frq[26] = {0};
    int N = 0; 
    for (int  i = 0; m.text[i] != '\0'; i++)
    {
        char c = m.text[i];
        if (isUppercase(c))
        {
            frq[c - 'A']++;
            N++;

        }
        if (isLowercase(c))
        {
            frq[c - 'a']++;
            N++;
        }
        
    }
    if (N <= 1)
    {
        return 0.0; 
    }
    int sum = 0;
    for (int  i = 0; i < 26; i++)
    {
        sum += frq[i] * (frq[i] - 1);
    }
    return (double)sum / (N * (N - 1)); 
}