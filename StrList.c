#include "StrList.h"

#define INCORRECT_INDEX_ERROR "Error: incorrect index!"


typedef struct _Node {
    char* data;
    struct _Node* next;
} Node;

typedef struct _StrList {
    Node* head;
    size_t size;
} StrList;

/*
 * Allocates a new empty StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_alloc(){
    StrList* strList = NULL;
    strList = (StrList*)malloc(sizeof(StrList));

    if (strList == NULL) {
        printf("%s\n", "memory allocation error");
    }
    strList->head = NULL;
    strList->size = 0;

    return strList;        // returns NULL if allocation failed
}

/*
 * Frees the memory and resources allocated to StrList.
 * If StrList==NULL does nothing (same as free).
 * it's the user's responsibility to change strList to NULL afer freeing.
 */
void StrList_free(StrList* strList){
    // Frees the list and all its nodes
    if (strList != NULL) {
        Node *p = strList->head;
        Node *temp = p;

        while (p != NULL){
            temp = p;
            p = p->next;
            if (temp->data != NULL)
                free(temp->data);
            free(temp);
        }
        free(strList);
    }
}

Node* Node_alloc(const char* data, Node* next){
    // Create a new node
    Node *node = NULL;
    node = (Node*)malloc(sizeof(Node));
    if (node == NULL){
        printf("%s\n", "memory allocation error");
        return NULL;
    }

    node->data = (char*)malloc(sizeof(char) * (strlen(data) + 1));
    if (node->data == NULL) {
        printf("%s\n", "memory allocation error");
        free (node); 
        return NULL;
    }
    strcpy(node->data, data);   // deep copy data
    return node;
}

void Node_free(Node* node){
    if (node != NULL){
        if (node->data != NULL){
            free (node->data);
        }
        free (node);
    }
}


/*
 * Returns the number of elements in the StrList.
 */
size_t StrList_size(const StrList* strList){
    return strList->size;
}

/*
 * Inserts an element in the end of the StrList.
 */
void StrList_insertLast(StrList* strList, const char* data){
    if (strList == NULL) {
        strList = StrList_alloc();
    }

    Node *temp = NULL;
    temp = Node_alloc(data, NULL);

    if (temp == NULL){
        Node_free(temp);
        return;//if we reach this it means that the memory allocation failed
    }

    /* If strList->head in NULL - this is the first node.
        else - find the last node and insert in there */
    if (strList->head == NULL){
        strList->head = temp;
        temp->next = NULL;
    }
    else {
        Node *p = strList->head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = temp;
        temp->next = NULL;
    }
    strList->size++;
}

/*
* Inserts an element at given index
    assuming the index is valid
*/
void StrList_insertAt(StrList* strList, const char* data,int index){
    // Check if list in not NULL and the index is avaialble
    if (strList == NULL || index > strList->size || index < 0){
        printf("%s\n", "incorect index");
        return;
    }

    // Create a new node
    Node *temp = NULL;
    temp = Node_alloc(data, NULL);

    if (temp == NULL){
        Node_free(temp);
        return;//if we reach this it means that the memory allocation failed
    }

    if (index == 0){ 
        if (strList->head == NULL){
            temp->next = NULL;
        }
        else {
            if (strList->head->next != NULL){
                temp->next = strList->head;
            }   
        }
        strList->head = temp;
    }
    else {
        Node *p = strList->head;
        int count = 0;
        
        while (count < index-1) {
            p = p->next;
            count++;
        }
        
        temp->next = p->next;
        p->next = temp;
    }

    strList->size++;
}


/*
 * Returns the StrList first data.
 */
char* StrList_firstData(const StrList* strList){
    if (strList != NULL && strList->head != NULL)
        return strList->head->data;
    return NULL;
}

/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList* strList){
    const Node *p = NULL;
    if (strList != NULL) {
        p = strList->head;
    }
    while (p != NULL){
        if (p->data != NULL) {
            printf("%s", p->data);
        }
        if (p->next != NULL){
            printf(" ");
        }
        p = p->next;
    }
    printf("\n");
}

/*
 Prints the word at the given index to the standard output.
*/
void StrList_printAt(const StrList* strList,int index){
    if (index > strList->size || index < 0){
        printf("%s\n", "incorect index");
        return;
    }
    // Go through list until the node at the desired index is reached
    const Node *p = NULL;
    if (strList != NULL){
        p = strList->head;
    }
    int count = 0;
    while (count != index && p != NULL) {
        p = p->next;
        count++;
    }
    if (p != NULL) {
        printf("%s\n", p->data);
    }
    else {
        printf("\n");
    }
}

/*
 * Return the amount of chars in the list without spaces
*/
int StrList_printLen(const StrList* strList) {
    int count = 0;
    const Node *p = NULL;
    if (strList != NULL){
        p = strList->head;
    }
    while (p != NULL){
        count += strlen(p->data);
        p = p->next;
    }
    return count;
}

/*
Given a string, return the number of times it exists in the list.
*/
int StrList_count(StrList* strList, const char* data){
    const Node *p = NULL;
    if (strList != NULL){
        p = strList->head;
    }
    int count = 0;
    while (p != NULL){
        if (strcmp(p->data, data) == 0){
            count++;
        }
        p = p->next;
    }
    return count;
}

/*
	Given a string and a list, remove all the appearences of this string in the list.
*/
void StrList_remove(StrList* strList, const char* data){
    Node *p = NULL;
    if (strList != NULL){
        p = strList->head;
    }
  
    while (p != NULL && p->data != NULL && strcmp(p->data, data) == 0){
        strList->head = p->next;
        free(p->data);
        free(p);
        p = strList->head;   
        strList->size--;
    }
   
    Node *temp = NULL;
    if (p != NULL){
        temp = p;
        p = p->next;
    }
    while (p != NULL && p->data != NULL){
        if (strcmp(p->data, data) == 0){
            temp->next = p->next;

            Node_free(p);

            p = temp->next;
            strList->size--;
        }
        else{
            p = p->next;
            temp = temp->next;
        }
    }
}

/*
	Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList* strList, int index){
    if (strList == NULL || strList->size == 0 || index > strList->size || index < 0){
        printf("%s\n", "incorect index");
        return;
    }
    Node *p = NULL;
    if (strList != NULL){
        p = strList->head;
    }

    
    int count = 0;
    while (count < index-1 && p != NULL){
        count++;
        p = p->next;
    }

    Node *temp = p->next;
    p->next = p->next->next;
    if (temp != NULL){
        Node_free(temp);
    }
    strList->size--;
}

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 */
int StrList_isEqual(const StrList* strList1, const StrList* strList2){
    if (strList1 != NULL && strList2 != NULL) {
        if (strList1->size != strList2->size){
            return 0;   
        }
    }
    else{
        if (strList1 == NULL && strList2 == NULL){
            return 1;
        }
    }

    // Run over both lists, with a pointer on each
    const Node *p1 = NULL;
    const Node *p2 = NULL;
    if (strList1 != NULL){
        p1 = strList1->head;
    }
    if (strList2 != NULL){
        p2 = strList2->head;
    }

    while (p1 != NULL && p2 != NULL){
        if (p1->data != NULL && p2->data != NULL && strcmp(p1->data, p2->data) != 0){
            return 0;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

    return 1;
}

/*
 * Clones the given StrList. 
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_clone(const StrList* strList){
    if (strList == NULL){
        return NULL;
    }

    StrList *clonedList = StrList_alloc();


    const Node *p = NULL;
    p = strList->head;
    while (p != NULL) {
        StrList_insertAt(clonedList, p->data, 0);
        p = p->next;
    }
    return clonedList;
}

/*
 * Reverces the given StrList. 
 */
void StrList_reverse(StrList* strList){
    if (strList == NULL || strList->size <= 1){
        return;
    }
    if (strList->size == 2){
        // reverse from HEAD -> X -> Y to HEAD -> Y -> X
        strList->head->next->next = strList->head->next;
        strList->head = strList->head->next;
        strList->head->next->next = NULL;
    }
    Node *bef = NULL, *curr = NULL, *next = NULL;
    bef = strList->head; 
    curr = bef->next;
    next = curr->next;

    bef->next = NULL;  
    while (next != NULL){
        curr->next = bef;
        bef = curr;
        curr = next;
        next = next->next;
    }
    curr->next = bef;
    strList->head = curr;
}

/*
 * Sort the given list in lexicographical order 
 */
void StrList_sort(StrList* strList){
    if (strList == NULL || strList->size <= 1 || StrList_isSorted(strList) == 1){
        return;
    }

    Node *p, *lastNode = NULL;
    int swaps = 0;

    /*
    We are using bubble-sort to send the "biggest" data to the end of the list,
    while keeping a pointer on the end of the unsorted "range", (each iteration we have 1 less node to visit).
    'swaps' holds the number of swaps while going through the list,
    if no swaps were made -> the list is sorted.
    */
    do {
        swaps = 0;
        p = strList->head;
        
        while (p->next != lastNode){
            if (strcmp(p->data, p->next->data) > 0){
                char *temp = p->data;
                p->data = p->next->data;
                p->next->data = temp;

                swaps++;
            }
            p = p->next;
        }
        lastNode = p;
    } while (swaps != 0);
}

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */
int StrList_isSorted(StrList* strList){
    if (strList->size <= 1){
        return 1;
    }
    const Node *p = strList->head;
    
    while (p->next != NULL){
        if (strcmp(p->data, p->next->data) > 0){
            return 0;
        }
        p = p->next;
    }
    return 1;
}