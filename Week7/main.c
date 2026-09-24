#include <stdio.h>
#include <string.h>

int main() {
    char supplierName[100] = "";
    char email[100] = "";
    char phone[30] = "";
    char town[50] = "";
    char backup[100] = "";
    char description[200] = "";
    char searchName[100] = "";
    int choice;

    do {
        printf("\n================================\n");
        printf(" MUNICIPAL FINANCIAL MANAGEMENT\n");
        printf("================================\n");
        printf("1. Add Supplier\n");
        printf("2. Display Supplier\n");
        printf("3. Search Supplier\n");
        printf("4. Show Name Length\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();   

        switch (choice) {
            case 1:
                printf("Enter supplier name: ");
                fgets(supplierName, sizeof(supplierName), stdin);
                supplierName[strcspn(supplierName, "\n")] = '\0';

                printf("Enter email: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = '\0';

                printf("Enter phone: ");
                fgets(phone, sizeof(phone), stdin);
                phone[strcspn(phone, "\n")] = '\0';

                printf("Enter town: ");
                fgets(town, sizeof(town), stdin);
                town[strcspn(town, "\n")] = '\0';

                /* LAB TASK 4*/
                strcpy(backup, supplierName);

                /* LAB TASK 5*/
                strcpy(description, supplierName);
                strcat(description, " operates in ");
                strcat(description, town);
                strcat(description, ".");
                break;

            case 2:
                printf("\n--- SUPPLIER DETAILS ---\n");
                printf("Name : %s\n", supplierName);
                printf("Email: %s\n", email);
                printf("Phone: %s\n", phone);
                printf("Town : %s\n", town);
                printf("Backup name: %s\n", backup);
                printf("Description: %s\n", description);
                break;

            case 3:
                printf("Enter supplier name to search: ");
                fgets(searchName, sizeof(searchName), stdin);
                searchName[strcspn(searchName, "\n")] = '\0';

                if (strcmp(supplierName, searchName) == 0) {
                    printf("Supplier found.\n");
                } else {
                    printf("Supplier not found.\n");
                }
                break;

            case 4:
                printf("Supplier name length: %zu\n", strlen(supplierName));
                printf("Email length: %zu\n", strlen(email));
                printf("Town length: %zu\n", strlen(town));
                break;

            case 5:
                printf("Goodbye.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}