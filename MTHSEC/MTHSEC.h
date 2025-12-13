#ifndef MTHSEC_H
#define MTHSEC_H

struct Matrix{
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
void displayMatrix(struct Matrix M);
void addMatrices(struct Matrix A, struct Matrix B, struct Matrix *C);




#define ver "1.0.0"
#endif