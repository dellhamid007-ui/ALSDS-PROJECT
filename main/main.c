
#include <stdio.h>
#include "../USRMGMT/USRMGMT.h"
#include "../AUDSEC/AUDSEC.h"

int main(){
    char str[] = "@";
    printf("%d %d %d %d", containsUppercase(str),containsLowercase(str),containsDigit(str),containsSymbol(str));
}