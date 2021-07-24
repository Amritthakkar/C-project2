#include <stdio.h>
#include <string.h>
#include "utility.h"

int main()
{
    char mainmenu[][30] = {
        "Exit",
        "Check Vaccine Slots",
        "Register Vaccine Slot",
        "Login",
        "Sign Up"
    };
    
    int main_menu_choice = Get_Menu_Choice(mainmenu, 5, "Main Menu");

    switch(main_menu_choice)
    {
        case 0:
            printf("Good Bye !");
            break;
        case 1:
            Display_Vaccine_Slots();
            break;
    }

    return 0;
}