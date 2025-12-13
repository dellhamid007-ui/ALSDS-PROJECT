
#include <stdio.h>
#include "../USRMGMT/USRMGMT.h"
#include "../AUDSEC/AUDSEC.h"
#include "../MTHSEC/MTHSEC.h"




int main(){
    struct Matrix M1 = {
        .data = {
            {1,5,6,1},
            {1,54,78,1}
        },
        .n =2,
        .p = 4
    };

    struct Matrix M2 = {
        .data = {
            {9,7,0,21},
            {5,16,12,1}
        },
        .n =2,
        .p = 4
    };


    struct Matrix M3;


    displayMatrix(M1);
    displayMatrix(M2);
    addMatrices(M1,M2,&M3);
    displayMatrix(M3);
}