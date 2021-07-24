#include <stdio.h>
typedef enum {false, true} bool;
typedef enum {type, address, quantity, date, contact} Vaccine_Slot_Line_State;

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

void Display_Vaccine_Slots()
{
    char file[] = "database/available_vaccine_slots.txt";
    
    printf("\nAvailable Slots\n---------------\n");
    
    
    FILE *fptr;
    fptr = fopen(file, "r");

    char filecharacter;
    Vaccine_Slot_Line_State vaccine_slot_line_state;
    struct Vaccine_Slot available_vaccine_slots[100];
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