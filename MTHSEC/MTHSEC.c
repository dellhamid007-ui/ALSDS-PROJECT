#include <stdio.h>
#include "MTHSEC.h"

int isEven(int n){
    if (n%2 == 0) return 1;
    else return 0;
}

int isPrime(int n){
    if(n == 1) return 0;
    for (int i =2; i <= (n/2); i++){
        if (n % i == 0) return 0;
    }
    return 1;
}

int gcd(int a, int b){
    if (a%b == 0) return b;
    if (b%a == 0) return a;

    while(a%b != 0){
        int rem = a%b;
        a = b;
        b = rem;
    }

    return b;
}

int lcm(int a, int b){
    if(a == 0 || b == 0){
        return 0;
    }

    int g = gcd(a,b);

    return (a*b)/g;
}

int modExp(int base, int exp, int mod){
    if (mod == 1) return 0;

    int result = 1;
    base %= mod;

    while(exp >0){
        if(exp %2 == 1){
            result = (result*base)%mod;
        }

        exp /= 2;
        base = (base*base) %mod;
    }

    return result;

}

int factorial(int n){
    if(n==0) return 1;
    if(n<0) return -1;

    int f = 1;

    while(n>1){
        f *=n;
        n --;
    }

    return f;
}

int sumDigits(int n){
    if(n<0) n = -n;
    int sum = 0;
    while(n >0){
        sum += n%10;
        n /= 10;
    }

    return sum;
}

int reverseNumber(int n){
    int r = 0;
    int sign = 0;
    if (n<0){
        n = -n;
        sign = 1;
    }
    while(n>0){
        r = r*10 + n%10;
        n /= 10;
    }

    if(sign ==0 ) return r;
    else return -r;
}

int isPalindromeNumber(int n){
    int r = reverseNumber(n);
    if(n == r) return 1;
    else return 0;
}


int sumDivisors(int n){
    if (n <=0) return -1;
    int sum = 0;
    for(int i=1; i<=n/2; i++){
        if (n%i==0) sum += i;
    }
    sum += n;

    return sum;
}

int isPerfectNumber(int n){
    if(n <= 0 || n%2 !=0) return 0;  


    if(2*n == sumDivisors(n)) return 1;
    else return 0;
}

int numDigits(int n){
    if(n==0) return 1;
    int m=0;
    while(n!=0){
        m++;
        n /=10;
    }

    return m;
}

int power(int n, int m){
    if(n==0 || n==1 || m ==1) return n;
    if(m==0) return 1;
    int res =1;
    for(int i = 1; i<=m;i++){
        res *=n;
    }

    return res;
}

int isArmstrong(int n){
    int sum = 0;
    int temp = n;
    int dig = numDigits(n);
    while (temp !=0){
        int lastDigit = temp%10;
        sum += power(lastDigit, dig);
        temp /=10;
    }

    if(n == sum) return 1;
    else return 0;
}

int randomNumber(int min, int max){
    int range = max - min +1;

    int random = RNG();
    if(random<0) random = -random;

    return min + (random%range);
    
}

int sumArray(int T[], int n){
    int sum = 0;
    for(int i =0; i<n; i++){
        sum += T[i];
    }
    return sum;
}

float averageArray(int T[],int n){
    if(n==0) return 0;
    return (float)sumArray(T,n)/n;
}

int maxArray(int T[], int n){
    int max = T[0];
    for(int i=0; i<n;i++){
        if(T[i]> max) max = T[i];
    }

    return max;
}

int minArray(int T[], int n){
    int min = T[0];
    for(int i=0; i<n;i++){
        if(T[i]< min) min = T[i];
    }

    return min;
}

void sortAscending(int T[], int n){  //Bubble sort algorithm
    for(int i =0; i<n-1; i++){
        for(int j = 0; j<n-i-1; j++){
            if(T[j]>T[j+1]){
                int t= T[j+1];
                T[j+1] = T[j];
                T[j] = t;
            }
        }
    }
}

void displayMatrix(struct Matrix M){
    for(int i = 0; i <M.n; i++){
        for(int j = 0; j< M.p; j++){
            printf("%d  ",M.data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void addMatrices(struct Matrix A, struct Matrix B, struct Matrix *C){
    if(A.n != B.n || A.p != B.p){
        printf("Error");
        return;
    }

    C->n =A.n;
    C->p = A.p;

    for (int i = 0; i < A.n; i++) {
        for (int j = 0; j < A.p; j++) {
            C->data[i][j] = A.data[i][j] + B.data[i][j];
        }
    }
}

