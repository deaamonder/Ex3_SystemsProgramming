#include <stdio.h>
#include <stdlib.h>
#include "StrList.h"
#include <string.h>

struct _StrList{
    char* data;
    struct _StrList* next;
};typedef struct _StrList StrList;

StrList* StrList_alloc(){
    StrList* newList = (StrList*)malloc(sizeof(StrList));
    if(newList==NULL){
        exit(EXIT_FAILURE);
    }
    newList->data = NULL;
    newList->next = NULL;
    return newList;
}

void StrList_free(StrList* strList){
    StrList* current = strList;
    while(current != NULL){
        StrList* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(strList);
}

size_t StrList_size(const StrList* strList){
    size_t count = 0;
    const StrList* temp = strList;
    while(temp!=NULL){
        count++;
        temp = temp->next;
    }
    return count;
}

void StrList_insertLast(StrList* strList, const char* data) {
    StrList* newStrList = (StrList*)malloc(sizeof(StrList));
    if (newStrList == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    newStrList->data = data;
    newStrList->next = NULL;

    if (strList == NULL) {
        strList = newStrList;
    } else {
        StrList* current = strList;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStrList;
    }
}

void StrList_insertAt(StrList* strList, const char* data, int index) {
    StrList* newStrList = (StrList*)malloc(sizeof(StrList));
    if (newStrList == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    newStrList->data = strdup(data);
    newStrList->next = NULL;

    if (index == 0) {
        newStrList->next = strList;
        strList = newStrList;
    } else {
        int count = 0;
        StrList* current = strList;
        while (current != NULL) {
            if (count == index - 1) {
                newStrList->next = current->next;
                current->next = newStrList;
                break;
            }
            current = current->next;
            count++;
        }
    }
}

char* StrList_firstData(const StrList* strList){
    const StrList* temp = strList;
    return temp->data;
}

//private function
char* StrList_lastData(const StrList* strList){
    const StrList* temp = strList;
    while(temp->next != NULL){
        temp = temp->next;
    }
    return temp->data;
}

void StrList_print(const StrList* strList){
    const StrList* temp = strList;
    while(temp != NULL){
        printf("%s \n",temp->data);
        temp = temp->next;
    }
}

void StrList_printAt(const StrList* strlist,int index){
    int count = 0;
    const StrList* temp = strlist;
    while(temp != NULL){
        if(count == index){
            printf("%s \n", temp->data);
        }
        count++;
        temp = temp->next;
    }
}

int StrList_printLen(const StrList* strlist){
    const StrList* temp = strlist;
    int count =0;
    while(temp != NULL){
        int charCount = sizeof(temp);
        count+=charCount;
    }
    return count;
}

int StrList_count(StrList* strList, const char* data) {
    const StrList* temp = strList;
    int count = 0;
    while (temp != NULL) {
        if (temp->data != NULL && strcmp(temp->data, data) == 0) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}
    
void StrList_remove(StrList* strList, const char* data){
    StrList* temp = strList;
    while(temp->next !=NULL){
        if(strcmp((temp->next)->data, data) == 0){
            free((temp->next)->data);
            free(temp->next);
            temp->next = (temp->next)->next;
        }
        else{
            temp = temp->next;
        }
    }
}

void StrList_removeAt(StrList* strList, int index){
    StrList* temp = strList;
    int count =0;
    while(temp->next != NULL){
        if(count == index){
            free((temp->next)->data);
            free(temp->next);
            temp->next = (temp->next)->next;
            break;
        }
        count++;
        temp = temp->next;
    }
}

int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){ 
    const StrList* temp1 = StrList1;
    const StrList* temp2 = StrList2;
    while(temp1!=NULL && temp2!=NULL){
        if(temp1->data != temp2->data){
            return 0;
        }
        temp1 = temp1->next;
        temp2 = temp2->next; 
    }
    return 1;
}

StrList* StrList_clone(const StrList* strList){
    StrList* newStrList = (StrList*)malloc(StrList_size(strList)*sizeof(strList));
    if (newStrList == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    const StrList* temp = strList;
    while(temp != NULL){
        newStrList->data = temp->data;
        newStrList->next = temp->next;
        temp=temp->next;
        newStrList = newStrList->next;
    }
    return newStrList;
}

void StrList_reverse( StrList* strList){
    const StrList* tempList = StrList_alloc();
    const StrList* temp = strList;
    while(temp->next!=NULL){
        StrList_insertLast(tempList,StrList_lastData(strList));
        StrList_removeAt(strList,StrList_size(strList)-1);
        temp = temp->next;
    }
    strList = StrList_clone(tempList);
}

// Compare function for qsort
int compareStrings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

void StrList_sort(StrList* strList) {
    // Count the number of elements in the list
    size_t count = StrList_size(strList);

    // Create an array to store the strings
    StrList* temp = strList;
    char** stringArray = (char**)malloc(count * sizeof(char*));

    if (stringArray == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Copy the strings from the linked list to the array
    for (size_t i = 0; i < count; ++i) {
        stringArray[i] = strdup(temp->data);
        temp = temp->next;
    }

    
    qsort(stringArray, count, sizeof(char*), compareStrings);

    temp = strList;
    for (size_t i = 0; i < count; ++i) {
        free(temp->data);  // Free the old string data
        temp->data = strdup(stringArray[i]);
        temp = temp->next;
    }

    // Free the temporary array
    for (size_t i = 0; i < count; ++i) {
        free(stringArray[i]);
    }
    free(stringArray);
}

int StrList_isSorted(StrList* strList){
    const StrList* tempList = StrList_clone(strList);
    StrList_sort(tempList);
    if(StrList_isEqual(tempList,strList)==1){
        return 1;
    }
    return 0;
}