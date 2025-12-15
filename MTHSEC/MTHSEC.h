#ifndef MTHSEC_H
#define MTHSEC_H

struct Matrix_{
    int data[10][10];
    int n,p;
};

int RNG();

int isEven(int n);
int isPrime(int n);
int gcd(int a, int b);
int lcm(int a, int b);
int modExp(int base, int exp, int mod);
int factorial(int n);
int sumDigits(int n);
int reverseNumber(int n);
int isPalindromeNumber(int n);
int sumDivisors(int n);
int randomNumber(int min, int max);
int sumArray(int T[], int n);
float averageArray(int T[],int n);
int maxArray(int T[], int n);
int minArray(int T[], int n);
void sortAscending(int T[], int n);
void displayMatrix(struct Matrix_ M);
void addMatrices(struct Matrix_ A, struct Matrix_ B, struct Matrix_ *C);
void multiplyMatrices(struct Matrix_ A, struct Matrix_ B, struct Matrix_ *C);
void transposeMatrix(struct Matrix_ A, struct Matrix_ *T);
int determinant2x2(int A[2][2]);
int isSymmetric(struct Matrix_ M);
int isIdentity(struct Matrix_ M);




#define ver "1.0.0"
#endif