
#include <stdio.h>
#include "../USRMGMT/USRMGMT.h"
#include "../AUDSEC/AUDSEC.h"



int main(){
    char name[20];
    struct User users[5];

    initUsers(users,5);
    displayUsers(users,5);
    loadUsers(users,5);

    displayUsers(users,5);


    userStatistics(users, 5);

}