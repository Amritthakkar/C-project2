#include <stdio.h>
#include <string.h>
#include "utility.h"

int main()
{
    char mainmenu[][30] = {
        "Exit",
        "Register Vaccine Slot",
        "Login",
        "Sign Up"
    };
    
    int main_menu_choice = Get_Menu_Choice(mainmenu, 4, "Main Menu");

    char user_type_menu[][30] = {
        "Staff",
        "Patient"
    };
    int user_type_menu_choice;

    switch(main_menu_choice)
    {
        case 0:
            printf("Good Bye !");
            break;
        case 1:
            printf("Registering new vaccine slots");
            break;
        case 2:
            user_type_menu_choice = Get_Menu_Choice(user_type_menu, 2, "Login as-");
            Login_As(user_type_menu[user_type_menu_choice], user_type_menu_choice);
            break;
        case 3:
            user_type_menu_choice = Get_Menu_Choice(user_type_menu, 2, "Sign Up as-");
            break;
    }

    return 0;
}