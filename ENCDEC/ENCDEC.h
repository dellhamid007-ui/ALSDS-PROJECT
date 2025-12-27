#ifndef ENCDEC_H
#define ENCDEC_H

#include <stddef.h> // this defines size_t


struct Message{
     char text[200]; // 199 characters(string) + '\0'
     int length;
};


void inputMessage(struct Message *m);
void DisplayMessage( struct Message m);
int isUppercase(char c );
int isLowercase(char c);
int isAlphabetic(char c);
void toUppercase( struct Message *m);
void toLowercase(struct Message *m);
void reverseMessage(struct Message* m);
void removeSpaces(struct Message *m);
void encryptCesar(struct Message *m , int key);
void decryptCesar(struct Message *m , int key );
void toHexString(const unsigned char *inputText, int len, char *outputText);
void encryptXOR(struct Message *m, unsigned char  key);
void hexStringToBytes(const char *hex, int len, unsigned char *outputText);
void decryptXOR(struct Message *m , int key);
void encryptSubstitution(struct Message *m , char key[26]);
void decryptSubstitution(struct Message *m, char key[26]);
int isValidKey(char key[26]);
int compareMessages(struct Message m1 , struct Message m2);
int countCharacter(struct Message m , char c);
void frequencyAnalysis(struct Message m);
double coincidenceIndex(struct Message m);






#define ver "1.0.0"
#endif