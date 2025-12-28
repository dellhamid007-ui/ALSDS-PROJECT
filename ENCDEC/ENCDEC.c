# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <ENCDEC.h>

struct Message{
     char text[200]; // 199 characters(string) + '\0'
     int length;
};
// Our own string.h library functions
//Begin


size_t string_length(char *text){ // counting the string lenghting to avoid using strlen() function
     size_t length = 0;
    while (text[length] != '\0')
    {
        length++;
    }
    return length;
    
}



void my_strncpy(char destination[] , const char source[] ){
    int i = 0; 
    while ((destination[i] = source[i]) != '\0')
    {
        i++;
    }
    
}
//End



void inputMessage(struct Message m[]) // Asking the user to enter a message
{
    printf("Enter a message: \t");
    fgets( m[0].text , 200 , stdin); // here the user enter the message
    m[0].text[strcspn(m[0].text , "\n")] = '\0'; // replacing \n with the string terminator '\0'
};
// Dsiplaying the message



void DisplayMessage( struct Message m){
    printf("\nYou entered : \t%s" , m.text);
    
    
}



int isUpperCase(char c ){
    if (c  >= 'A' && c <= 'Z')
    {
        return 1; //true
    }else{
        return 0; //false
    }

    
}



int isLowercase(char c){
    if (c >= 'a' && c <= 'z')
    {
        return 1; //true
    }else{
        return 0; // false
    }
    
}




int isAlphabetic(char c){
    if (isUpperCase(c) || isLowercase(c))
    {
        
        return 1;

    }else{
        
        return 0;
    }
}   



void toUppercase( struct Message *m){
    
     for (int  i = 0; i < string_length(m->text); i++)
     {
        if (isLowercase(m->text[i]))
        {
            m->text[i] = m->text[i] - ('a' - 'A'); //lower case character - 32 gives us an upper case (ASCII table)
            
        }
        
     }
     
}




void toLowercase(struct Message *m){
    for (int  i = 0; i < string_length(m->text); i++)
    {
        if (isUpperCase(m->text[i]))
        {
            m->text[i] = m->text[i] + ('a' - 'A');
        }
        
    }
    
}



void reverseMessage(struct Message m){
int i = 0;
int j = string_length(m.text) - 1;
char temp;
while (i < j)
{
    temp = m.text[i];
    m.text[i] = m.text[j];
    m.text[j] = temp;
    i++;
    j--; 
    
}
printf("\nThe reversed message is :\n %s" , m.text );
    
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
    my_strncpy(m->text, temp);
    

    
    
}



void encryptCesar(struct Message *m , int key){   //applying a Cesar cipher
    int i;
    

    
    for (int  i = 0; i < string_length(m->text); i++)
    {
       if (isUpperCase(m->text[i]))
       {
            m->text[i] = ((m->text[i] + key - 'A') % 26) + 'A';
       }
       else if (isLowercase(m->text[i]))
       {
         m->text[i] = ((m->text[i] + key - 'a') % 26) + 'a';
       }
       
       
        
    }
    
    
}



void decryptCesar(struct Message *m , int key ){  //possible message decryption based on shift value
    int i;
    char cesardct[200];
    
    
        for (i = 0; m->text[i] != '\0'; i++)
        {
            if (isUpperCase(m->text[i]))
            {
                cesardct[i] = ((m->text[i] -'A' - key + 26 ) % 26) + 'A';
            }
            else if (isLowercase(m->text[i]))
            {
                cesardct[i] = ((m->text[i] - 'a'- key + 26) % 26) + 'a';
            }
            else{
                cesardct[i] = m->text[i];
            }
            

        }
        cesardct[i] = '\0';
        printf("\nkey = %d : %s\n" , key , cesardct);   
    
    
}


void encryptXOR(struct Message *m, unsigned char  key){
    // we need to apply XOR  : 0 and 1 = 1 and if the same then let it be 0
    for (int  i = 0; i < string_length(m->text); i++)
    {
        m->text[i] ^= (unsigned char) key;
    }
    printf("The encrypted XOR message is : %s" , m->text);
    
    
}


void decryptXOR(struct Message *m , int key){
        for (int  i = 0; i < string_length(m->text); i++)
        {
            m->text[i] ^= (unsigned char ) key;
        }
        printf("\nThe decrypted XOR message is : %s\n" , m->text);


}

    
    void encryptsubstitution(struct Message *m , char key[26]){
   /*
    1. key must be 26 characters long
    2. key must only be letters and no duplicates
    3. plaintext letter cases must be maintained when converting to ciphertext 
   
   */
   if (m == NULL || m->text == NULL)
   {
      return;
   }
   
    for (int i = 0; m->text[i] != '\0'; i++)
    {
        if (isLowercase(m->text[i]))
        {
            int index = m->text[i] - 'a';
            if (index >= 0 && index < 26)
            {
                m->text[i] = key[index];
            }
            
        }
        else if(isUpperCase(m->text[i])){
            int index = m->text[i] - 'A';
            if (index >= 0 && index < 26)
            {
                m->text[i] = key[index] - 'a' + 'A'; // convert to upper case
            }
            
        }
        // non alphabetical characters will not be changed
        
    }
    printf("\nThe ecnrypted substition message is : %s" , m->text);
    
}
void decryptSubstitution(struct Message *m, char key[26]){
   if (m == NULL || m->text == NULL)
   {
        return;
   }
   for (int  i = 0; m->text[i] != '\0'; i++)
   {
     if (isUpperCase(m->text[i]))
     {
        for (int j = 0; j < 26; j++)
        {
            if (toupper(key[j]) == m->text[i])
            {
                m->text[i] = 'A' + j;
                break;
            }
            
        }
        
        
        
     }
     else if (isLowercase(m->text[i]))
     {
       
        for (int  j = 0; j < 26; j++)
        {
            
           
            if (tolower(key[j])== m->text[i])
            {
                m->text[i] = 'a' + j;
                break;
            }
            
        }
        
     }
     
     
   }
   printf("The decrypted message is : %s" , m->text);


}
int isValidKey(char key[26]){
   int frq[26];
   int i , j , counter;
   int valid = 1; // valid until proven otherwise 
   if (string_length(key) != 26) // chekc the string length
   {
      valid = 0;
   }
   

   for ( i = 0; i < 26; i++) // check for duplicates
   
   if (!isAlphabetic(key[i])) // check for alphabets
   {
     valid = 0;
     frq[i] = -1;
   }
   
   {
     
    
   }
   for ( i = 0; i < 26; i++)
   {
     
     if (frq[i] == 0)
     {
        continue;
     }
     counter = 1;
     for ( j = i + 1; j < 26; j++)
     {
        if (key[i] == key[j])
        {
            counter++;
            frq[j] = 0;
        }
       
        
     }
     frq[i] = counter;
     if (counter != 1)
     {
        valid = 0;
     }
     
   
   
   
}
 
   return valid;
    
}
int compareMessages(struct Message m1 , struct Message m2){
    struct Message m1copy = m1;
    struct Message m2copy = m2;

    toLowercase(&m1copy);
    toLowercase(&m2copy);
    int i = 0 , j =0;
    while (m1.text[i] != '\0' && m2.text[j] != '\0')
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
    int frq[26];
    for (int  i = 0; i < string_length(m.text); i++)
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
    for (int  i = 0; i < string_length(m.text); i++)
    {
        char c = m.text[i];
        if (isUpperCase(c))
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
int coincidenceIndex(struct Message m){
    int frq[26] = {0};
    int N = 0; // number of alphabetic letters
    for (int  i = 0; m.text[i] != '\0'; i++)
    {
        char c = m.text[i];
        if (isUpperCase(c))
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
        return 0.0; // avoid division by 0
    }
    int sum = 0;
    for (int  i = 0; i < 26; i++)
    {
        sum += frq[i] * (frq[i] - 1);
    }
    return (double)sum / (N * (N - 1)); // coincidence index
}