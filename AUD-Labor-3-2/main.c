/******************************************************************
 * Projekt: Algorithmen und Datenstrukturen
 * Dateiname: main.c
 * Beschreibung: AUD-Labor-3-2
 * Autor: Nico Petersen
 * Matr.-Nr.: ******
 * Erstellt: 23.04.2021
 ******************************************************************/
/*********** Hinweis ***********/
/*
 Einzelne Tests in CodeFreak können unerwartet fehlschlagen.
 Das kann auch daran liegen, dass die Aufgabenstellung im Detail
 unterschiedlich interpretiert werden kann. Beispielsweise setzen die
 Tests voraus, dass bei einer leeren Liste immer ein Element an Position 1
 eingefügt werden kann.
 
 Funktioniert das Programm in Ihren Augen korrekt, fragen Sie gern nach,
 warum ein bestimmter Test fehlschlägt.
 */


#include <stdio.h>
#include <stdlib.h>

// Hier Konstanten und Statuscodes definieren
#define NOT_IMPLEMENTED_ERROR -1000  // bei mir 24
#define POSITION_NOT_USED -55
#define DELETED_SUCCESSFULLY 20
#define ERROR_PRINTING_LIST -10
#define POSITION_NOT_LOGICAL -20
#define NO_LIST_AVAILABLE -30
#define NO_RAM_AVAILABLE -40



// Hier Struktur und globale Variablen definieren


// Vorgegebene Enumeration als Hilfestellung
enum DIRECTION { FORWARD, REVERSE } direction;

typedef struct _List{
    int data;
    struct _List *next;
} List;

List *start = NULL;


/* Vorgegebene Unterprogramme zur Verwaltung der verketteten Liste */
/* Die folgenden 6 Funktionen werden von CodeFreak erwartet.       */
/* Fehler sollten durch die Rückgabe eines negativen Statuscodes   */
/* kenntlich gemacht werden. */
int put_entry(int position, int aktdata);  /* Eintrag einfuegen */
int del_entry(int position);               /* Eintrag loeschen  */
int find_entry(int value);                 /* Eintrag suchen    */
int del_list(void);                       /* Liste loeschen    */
int get_anzentries(void);                  /* Anzahl ermitteln  */
int printall(enum DIRECTION direction);    /* Liste ausgeben    */
List *createElement(int value);

List *createElement(int value) {
    List *temp = (List *) malloc(sizeof(List));
    if (temp == NULL) return NULL;
    temp->next = NULL;
    temp->data = value;
    return temp;
}

void testProgramm() {
    
    printall(FORWARD);
    printall(REVERSE);
    del_list();
    del_entry(-1);
    del_entry(10);
    del_entry(0);
    find_entry(-1);
    find_entry(10);
    find_entry(0);
    get_anzentries();
    put_entry(-1, 10);
    printall(FORWARD);
    printall(REVERSE);
    get_anzentries();
    put_entry(0, 5);
    get_anzentries();
    printall(FORWARD);
    printall(REVERSE);
    put_entry(2003435687, -178);
    printall(FORWARD);
    printall(REVERSE);
    del_list();
    del_list();
    del_list();
    put_entry(8029, 12);
    put_entry(2000000000, 23);
    printall(FORWARD);
    printall(REVERSE);

}

int main(void)
{
    testProgramm();

    printf("Anzahl der Listenitems %d\n", get_anzentries());
    put_entry(1, 1);
    put_entry(20000, 305854);
    put_entry(2, 2);
    put_entry(3, 3);
    put_entry(0, 5);
    put_entry(20, 10);
    printf("Anzahl der Listenitems %d\n", get_anzentries());
    del_list();
    find_entry(20000);
    find_entry(-1);
    find_entry(2);
    del_entry(2);
    printf("Anzahl der Listenitems %d\n", get_anzentries());
    printall(FORWARD);
    printall(REVERSE);


    printf("\n\nENDE DES PROGRAMMS\n\n");
    return 0;
}


/* Unterprogramm zum Einfuegen eines Nutzdatenelements
 *  Parameter: position = Einfuegepos.; 0 = vor pstart
 *             aktdata  = einzufuegende Zahl
 */
int put_entry(int position, int aktdata) /* Einfuegen */
{
    
    int currentPos = 1;
    List *temp = start;
    List *new = createElement(aktdata);
    if (new == NULL) {
        return NO_RAM_AVAILABLE;
    }
    if (start == NULL) {
        start = new;
        return 0;
    } else if(position == 0) {
        new->next = start;
        start = new;
    } else if (position < 0){
        return POSITION_NOT_LOGICAL;
    } else if(position > get_anzentries()) {
        while (1) {
            if(temp->next == NULL) {
                temp->next = new;
                return 0;
            }
            temp = temp->next;
        }
    } else {
        while(temp->next != NULL) {
            
            if (currentPos == position) {
                new->next = temp->next;
                temp->next = new;
            }
            temp = temp->next;
            currentPos++;
        }
    }
    return 0;
}


/* Unterprogramm zu Ausgabe aller Listenelemente
 *  Parameter: direction  = FORWARD    vorwaerts
 *                        = REVERSE    rueckwaerts
 *  Return:    0          = alles OK
 *         negative Werte = Fehler
 */
int printall(enum DIRECTION direction)
{
    
    if(get_anzentries() == 1) {
        printf("%d\n", start->data);
        return 0;
    }
    if (direction == FORWARD){
        printf("\n\n");
        List *temp = start;
        if (temp != NULL) {
            do {
                printf("%d\n", temp->data);
                temp = temp->next;
            } while (temp != NULL);
        }
        printf("\n\n");
        return 0;
        
    } else if (direction == REVERSE){ // 1 2 3 4 5 6 NULL
        printf("\n\n");
        List *temp = start;
        int anzahl = get_anzentries();
        List *ptr[anzahl];
        for (int i = 0; i < anzahl; i++) {
            ptr[i] = temp;
            temp = temp->next;
        }
        for (int i = anzahl - 1; i >= 0; i--) {
            printf("%d\n", ptr[i]->data);
        }
        
        
        
        
        printf("\n\n");
        return 0;
        
    }
    return ERROR_PRINTING_LIST;
}


/* Unterprogramm zum Loeschen der gesamten Liste
 *  Parameter: keine
 *  Return:    0         = Loeschen OK
 *         negative Werte = Fehler
 */
int del_list(void)
{
    
    if (get_anzentries() == 0) return 0;
    if (get_anzentries() == 1) {
        free(start);
        start = NULL;
        return 0;
    } else {
        List *temp = start;
        int anzahl = get_anzentries();
        List *ptr[anzahl];
        for (int i = 0; i < anzahl; i++) {
            ptr[i] = temp;
            temp = temp->next;
        }
        for (int i = anzahl - 1; i >= 0; i--) {
            free(ptr[i]);

        }
        start = NULL;
        return 0;
    }
}


/* Unterprogramm zum Loeschen eines Nutzdatenelements
 *  Parameter: position   = Loeschpos.;
 *  Return:    0          = Loeschen OK
 *         negative Werte = Fehler
 */
int del_entry(int position) /* Loeschen (delete) */
{
    
    if (position <= 0) {
        return POSITION_NOT_LOGICAL;
    }
    if (position == 1) {
        if (get_anzentries() > 1) {
            List *temp = start;
            start = start->next;
            free(temp);
            return 0;
        } else {
            del_list();
            return 0;
        }
    }
    
    int currentPos;
    List *temp = start;
    List *tempForFree = NULL;
    if(position > get_anzentries()) {
        return POSITION_NOT_USED;
    } else {
        for (currentPos = 1; currentPos < position - 1; currentPos++ ) {
            temp = temp->next;
        }
        tempForFree = temp->next;
        temp->next = temp->next->next;
        free(tempForFree);
        return 0;
    }
    
}


/* Unterprogramm zur Ermittlung der Elementanzahl
 *  Parameter: keine
 *  Return:    aktuelle Anzahl der Element
 */
int get_anzentries(void)      /* Anzahl ermitteln  */
{
    
    int anz = 0;
    List *temp = start;
    while (temp != NULL) {
        anz++;
        temp = temp->next;
    }
    return anz;
}


/* Unterprogramm zum Suchen eines Elementes
 *  Parameter: value      = Zahl, nach der gesucht wird
 *  Return:    0          = nicht gefunden
 *         negative Werte = Fehler
 */
int find_entry(int value)
{
    
    if (get_anzentries() == 0) return NO_LIST_AVAILABLE;
    int position = 1;
    List *temp = start;
    
    do {
        if (temp->data == value) {
            return position;
        } else {
            position++;
        }
        
    } while (temp->next != NULL);
    return 0;
    
    return NOT_IMPLEMENTED_ERROR;
}
