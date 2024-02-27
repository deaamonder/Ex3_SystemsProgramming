#include <stdio.h>
#include <stdlib.h>
#include "StrList.h"
#include "StrList.c"

int main() {
    StrList* stringList = StrList_alloc();

    int choice;
    char buffer[256];  // Buffer for user input

    do {
        // Display the menu
        printf("\nMenu:\n");
        printf("1. Insert strings to the list\n");
        printf("2. Insert string at a specific index\n");
        printf("3. Print the list\n");
        printf("4. Print the length of the list\n");
        printf("5. Print string at a specific index\n");
        printf("6. Print the number of occurrences of a string\n");
        printf("7. Remove all occurrences of a string\n");
        printf("8. Remove element at a specific index\n");
        printf("9. Reverse the list\n");
        printf("10. Delete entire list\n");
        printf("11. Sort the list\n");
        printf("12. Check if the list is sorted\n");
        printf("13. Exit\n");

        // Get user choice
        printf("Enter your choice (0-13): ");
        scanf("%d", &choice);

        // Clear the input buffer
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                // Insert strings to the list
                printf("Enter strings separated by space: ");
                fgets(buffer, sizeof(buffer), stdin);

                // Tokenize the input string
                char* token = strtok(buffer, " ");
                while (token != NULL) {
                    StrList_insertLast(stringList, token);
                    token = strtok(NULL, " ");
                }
                break;
            case 2:
                // Insert string at a specific index
                printf("Enter index: ");
                int index;
                scanf("%d", &index);
                printf("Enter string: ");
                scanf("%s", buffer);
                StrList_insertAt(stringList, buffer, index);
                break;
            case 3:
                // Print the list
                StrList_print(stringList);
                break;
            case 4:
                // Print the length of the list
                printf("Length of the list: %zu\n", StrList_size(stringList));
                break;
            case 5:
                // Print string at a specific index
                printf("Enter index: ");
                scanf("%d", &index);
                StrList_printAt(stringList, index);
                break;
            case 6:
                // Print the number of occurrences of a string
                printf("Enter string: ");
                scanf("%s", buffer);
                printf("Occurrences: %d\n", StrList_count(stringList, buffer));
                break;
            case 7:
                // Remove all occurrences of a string
                printf("Enter string to remove: ");
                scanf("%s", buffer);
                StrList_remove(stringList, buffer);
                break;
            case 8:
                // Remove element at a specific index
                printf("Enter index to remove: ");
                scanf("%d", &index);
                StrList_removeAt(stringList, index);
                break;
            case 9:
                // Reverse the list
                StrList_reverse(&stringList);
                break;
            case 10:
                // Delete entire list
                StrList_free(stringList);
                stringList = StrList_alloc();
                break;
            case 11:
                // Sort the list
                StrList_sort(stringList);
                break;
            case 12:
                // Check if the list is sorted
                printf("%d",StrList_isSorted(stringList));
                break;
            case 13:
                // Exit the program
                break;
            default:
                printf("Invalid choice. Please enter a number between 0 and 13.\n");
                break;
        }
    } while (choice != 13);

    // Free memory before exiting
    StrList_free(stringList);

    return 0;
}   