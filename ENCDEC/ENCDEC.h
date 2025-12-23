#ifndef ENCDEC_H
#define ENCDEC_H

#include <stddef.h> // this defines size_t

size_t string_length(char *text);
void my_strncpy(char destination[] , const char source[] );
void inputMessage(struct Message m[]);
void DisplayMessage( struct Message m);
int isUpperCase(char c );
int isLowercase(char c);
int isAlphabetic(char c);
void toUppercase( struct Message *m);
void toLowercase(struct Message *m);
void reverseMessage(struct Message m);
void removeSpaces(struct Message *m);
void encryptCesar(struct Message *m , int key);
void decryptCesar(struct Message *m , int key );
void encryptXOR(struct Message *m, unsigned char  key);
void decryptXOR(struct Message *m , int key);
void encryptsubstitution(struct Message *m , char key[26]);
void decryptSubstitution(struct Message *m, char key[26]);
int isValidKey(char key[26]);
int compareMessages(struct Message m1 , struct Message m2);
int countCharacter(struct Message m , char c);
void frequencyAnalysis(struct Message m);
int coincidenceIndex(struct Message m);






#define ver "1.0.0"
#endif