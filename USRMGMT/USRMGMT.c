#include <stdio.h>

struct User{
    char name[20];          //00000000000000000000 for deleted users
    char password[20];      //00000000000000000000 for deleted users    
    int role;               //0:user, 1:admin, 999:deleted users
    int state               //0:active 1:blocked 999:deleted
};

