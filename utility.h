#include <stdio.h>
typedef enum {false, true} bool;
typedef enum {type, address, quantity, date, contact} Vaccine_Slot_Line_State;
typedef enum {registered_slot_type, registered_slot_address, registered_slot_patient} Registered_Slot_State;
typedef enum {id, name, password} User_Details;

int Get_Menu_Choice(char menu[][30], int menuLength, char menuTitle[])
{
    printf("\n%s\n\n", menuTitle);
    for(int i = 0; i < menuLength; i++)
    {
        printf("%d) ", i + 1);
        for (int j = 0; j < sizeof(menu[i]); j++)
        {
            printf("%c", menu[i][j]);
        }
        printf("\n");
    }
    int choice;
    printf("Enter your choice : ");
    scanf("%d", &choice);

    return choice - 1;
}

struct Vaccine_Slot
{
    char type[20];
    char address[100];
    char quantity[3];
    char date[10];
    char contact[10];
};

void Display_Available_Vaccine_Slots()
{
    char file[] = "database/available_vaccine_slots.txt";
    
    printf("\nAvailable Slots\n---------------\n");
    
    FILE *fptr;
    fptr = fopen(file, "r");

    char filecharacter;
    Vaccine_Slot_Line_State vaccine_slot_line_state;
    struct Vaccine_Slot vaccine_slot;
    bool new_slot;

    filecharacter = fgetc(fptr);
    vaccine_slot_line_state = type;
    new_slot = true;
    
    while (filecharacter != EOF)
    {

        if(new_slot)
        {
            strcpy(vaccine_slot.type, "");
            strcpy(vaccine_slot.address, "");
            strcpy(vaccine_slot.quantity, "");
            strcpy(vaccine_slot.date, "");
            strcpy(vaccine_slot.contact, "");
            new_slot = false;
        }

        switch(filecharacter)
        {
            case '\n':
                new_slot = true;
                vaccine_slot_line_state = type;
                printf("Type : %s\n", vaccine_slot.type);
                printf("Address : %s\n", vaccine_slot.address);
                printf("Quantity : %s\n", vaccine_slot.quantity);
                printf("Date : %s\n", vaccine_slot.date);
                printf("Contact : %s\n", vaccine_slot.contact);
                printf("\n\n");
                break;
            case '#':
                switch(vaccine_slot_line_state)
                {
                    case type:
                        vaccine_slot_line_state = address;
                        break;
                    case address:
                        vaccine_slot_line_state = quantity;
                        break;
                    case quantity:
                        vaccine_slot_line_state = date;
                        break;
                    case date:
                        vaccine_slot_line_state = contact;
                        break;
                }
                break;
            default:
                switch(vaccine_slot_line_state)
                {
                case type:
                    strncat(vaccine_slot.type, &filecharacter, 1);
                    break;
                case quantity:
                    strncat(vaccine_slot.quantity, &filecharacter, 1);
                    break;
                case address:
                    strncat(vaccine_slot.address, &filecharacter, 1);
                    break;
                case date:
                    strncat(vaccine_slot.date, &filecharacter, 1);
                    break;
                case contact:
                    strncat(vaccine_slot.contact, &filecharacter, 1);
                    break;
                }
                break;
        }
        filecharacter = fgetc(fptr);
    }
    fclose(fptr);
}

struct Registered_Slot
{
    char type[20];
    char address[100];
    char patientid[20];
};

void Display_Registered_Vaccine_Slots()
{
    char file[] = "database/registered_vaccine_slots.txt";
    
    printf("\nRegistered Slots\n---------------\n");
    
    FILE *fptr;
    fptr = fopen(file, "r");

    char filecharacter;
    Registered_Slot_State registered_slot_state;
    struct Registered_Slot registered_slot;
    bool new_slot;

    filecharacter = fgetc(fptr);
    registered_slot_state = type;
    new_slot = true;
    
    while (filecharacter != EOF)
    {

        if(new_slot)
        {
            strcpy(registered_slot.type, "");
            strcpy(registered_slot.address, "");
            strcpy(registered_slot.patientid, "");
            new_slot = false;
        }

        switch(filecharacter)
        {
            case '\n':
                new_slot = true;
                registered_slot_state = registered_slot_type;
                printf("Type : %s\n", registered_slot.type);
                printf("Address : %s\n", registered_slot.address);
                printf("Patient Id : %s\n", registered_slot.patientid);
                printf("\n\n");
                break;
            case '#':
                switch(registered_slot_state)
                {
                    case registered_slot_type:
                        registered_slot_state = registered_slot_address;
                        break;
                    case registered_slot_address:
                        registered_slot_state = registered_slot_patient;
                        break;
                }
                break;
            default:
                switch(registered_slot_state)
                {
                case registered_slot_type:
                    strncat(registered_slot.type, &filecharacter, 1);
                    break;
                case registered_slot_address:
                    strncat(registered_slot.address, &filecharacter, 1);
                    break;
                case registered_slot_patient:
                    strncat(registered_slot.patientid, &filecharacter, 1);
                    break;
                }
                break;
        }
        filecharacter = fgetc(fptr);
    }
    fclose(fptr);
}

struct User
{
    char id[20];
    char name[50];
    char password[50];
};

void Login_As(char login_as_type[30], int use_type_choice)
{
    char user_entered_id[20], user_entered_password[50], database_file[] = "database/";
    
    strcat(database_file, login_as_type);
    strcat(database_file, "s.txt");
    
    FILE *fptr;
    char filecharacter;
    
    User_Details user_details;
    struct User user;
    bool id_inccorrect;
    bool new_user;
    bool user_found;
    bool password_incorrect;

    fptr = fopen(database_file, "r");
    filecharacter = fgetc(fptr);
    user_found = false;
    password_incorrect = false;

    printf("\nEnter your %s id : ", login_as_type);
    scanf("%s", user_entered_id);

    while (filecharacter != EOF)
    {
        if(new_user)
        {
            strcpy(user.id, "");
            strcpy(user.name, "");
            strcpy(user.password, "");
            new_user = false;
        }
        if(user_found)
        {
            break;
        }

        switch(filecharacter)
        {
            case '\n':
                id_inccorrect = strcmp(user.id, user_entered_id);
                if(!id_inccorrect)
                {
                    printf("\nLogin as-\n");
                    printf("ID : %s\n", user.id);
                    printf("Name : %s\n", user.name);

                    for(int chance=3; chance>0; chance--)
                    {
                        printf("\nRemaining chances-%d", chance);
                        printf("\nEnter your password : ");
                        scanf("%s", user_entered_password);
                        password_incorrect = strcmp(user.password, user_entered_password);
                        if(!password_incorrect)
                        {
                            printf("Logged in");
                            break;
                        }
                        else
                        {
                            printf("\nIncorrect password\n");
                        }
                    }

                    user_found = true;
                }
                new_user = true;
                user_details = id;
                break;
            case '#':
                switch(user_details)
                {
                    case id:
                        user_details = name;
                        break;
                    case name:
                        user_details = password;
                        break;
                }
                break;
            default:
                switch(user_details)
                {
                case id:
                    strncat(user.id, &filecharacter, 1);
                    break;
                case name:
                    strncat(user.name, &filecharacter, 1);
                    break;
                case password:
                    strncat(user.password, &filecharacter, 1);
                    break;
                }
                break;
        }
        filecharacter = fgetc(fptr);
    }
    if(!user_found)
    {
        printf("\nSorry, no %s exists in our database with that id. :(\n", login_as_type);
    }
    
    fclose(fptr);
    
    char staff_menu[][30] = {
        "Available vaccine slots",
        "Registered vaccine slots"
    };
    int staff_menu_choice;

    switch(use_type_choice)
    {
        case 0:
            staff_menu_choice = Get_Menu_Choice(staff_menu, 2, "Staff Menu");
            switch(staff_menu_choice)
            {
                case 0:
                    Display_Available_Vaccine_Slots();
                    break;
                case 1:
                    Display_Registered_Vaccine_Slots();
                    break;
            }
            break;
        case 1:
            printf("Patient login successful");
            break;
    }
}