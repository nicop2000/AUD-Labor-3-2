//
//  main2.c
//  AUD-Labor-3-2
//
//  Created by Nico Petersen on 12.05.21.
//

#include <stdio.h>


/******************************************************************
 * Projekt: Algorithmen und Datenstrukturen
 * Dateiname: main.c
 * Beschreibung: AUD-Labor-3-2
 * Autor: Nico Petersen
 * Matr.-Nr.: 937369
 * Erstellt: 23.04.2021
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1;
#define FALSE 0;
typedef int BOOL;

typedef struct _List{
    int data;
    struct _List *next;
} List;

List *start = NULL;

List *createElement(int value) {
    List *temp = (List *) malloc(sizeof(List));
    temp->next = NULL;
    return temp;
}

void addAtStart(List *newStart) {
    newStart->next = start;
    start = newStart;
    
}

void addMiddle() {
    
}

void addAtEnd(List *newEnd) {
    if (start == NULL) {
        start = newEnd;
        return;
    }
    List *startLocal = start;
    
    while (1){
        if (startLocal->next == NULL){
            startLocal->next = newEnd;
            break;
        }
        startLocal = startLocal->next;
       
    }
}

int getListLength() {
    if (start == NULL) {
        return 0;
    }
    List *startLocal = start;
    int counter = 0;
    while(startLocal->next != NULL) {
        if (startLocal->next == startLocal) {
            break;
        }
        counter++;
    }
    return counter;
}

void addItemToList(int value, int position) {
    List *iterLocal = start;
    List *new = createElement(value);
    int counter = 0;
    if(position == 0) {
        addAtStart(new);
        return;
    } else if (position >= getListLength()) {
        addAtEnd(new);
    }
    else {
        while (iterLocal->next != NULL){
            counter++;
            if (counter == position) {
                new->next = iterLocal->next;
                iterLocal->next = new;
                return;
            }
            
        }
    }
    
}



void removeItemFromList() {
    
}

void searchForElementData() {
    
}

void deleteList() {
    
}





void printList() {
    List *startLocal = start;
    int counter = 0;
    do {
        printf("%d\n", startLocal->data);
    } while(startLocal->next != NULL);
    
    
}











//int main(int argc, const char * argv[]) {
//
//    addItemToList(10, 2);
//    addItemToList(11, 3);
//    addItemToList(9, 1);
//    printList();
//
//
//    printf("Hello, World!\n");
//    return 0;
//}
//
//
//
///
