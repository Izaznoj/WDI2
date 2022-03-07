#include <stdbool.h> // bool

// LISTA 1-KIERUNKOWA

#include <stdlib.h>  // NULL, malloc, free
#include <stdio.h>   // printf

struct element;
typedef struct element element, *list;  // Aliasy typu elementu listy
// i wskaźnika do listy

typedef int info_t;  // Alias typu wartości przechowywanej w liście,
// żeby łatwo było przystosować listę do przechowywania
// innego typu wartości.

/* Deklaracja elementu (węzła) listy 1-kierunkowej
 */
struct element {
    info_t info;
    element *next;
};

/* Inicjalizacja listy 1-kierunkowej
 */
void ini(list * h) {
    *h = NULL;
}

/* Tworzenie nowego elementu listy 1-kierunkowej
 */
element * nowy(info_t a) {
    element * u;
    u = malloc(sizeof(element));
    u->next = NULL;
    u->info = a;
    return u;
}

/* Dodawanie elementu do listy 1-kierunkowej (na jej początku)
 */
void dodaj(list * h, element * u) {
    u->next = *h;
    *h = u;
}

/* Usuwanie pierwszego elementu z listy 1-kierunkowej
 * (o lista nie jest pusta)
 */
void usun(list * w) {
    list u;
    if (*w != NULL) {
        u = *w;
        *w = (*w)->next;
        free(u);
    }
}

/* Wypisanie listy 1-kierunkowej
 */
void druk(list u) {
    while (u != NULL) {
        printf("%d ", u->info);
        u = u->next;
    }
    printf("\n");
}

// IMPLEMENTACJA STOSU OPARTEGO NA LIŚCIE 1-KIERUNKOWEJ

/* Alias reprezentujący wskaźnik na wierzchołek stosu
 */
typedef list stos;

/* Sprawdza czy stos S jest pusty
 */
bool empty(stos S) {
    return S == NULL;
}

/* Wstawia liczbę x na wierzch stosu S
 */
void push(stos * S, info_t x) {
    dodaj(S, nowy(x));
}

/* Zdejmuje element z wierzchu stosu S i daje jego wartość w wyniku.
 * Zwraca 0, gdy stos jest pusty.
 */
info_t pop(stos * S) {
    info_t wynik = 0;
    if (!empty(*S)) {
        wynik = (*S)->info;
        usun(S);
    }
    return wynik;
}

/* Daje liczbę elementów umieszczonych na stosie
 */
int size(stos S) {
    int licznik = 0;
    while (S != NULL) {
        ++licznik;
        S = S->next;
    }
    return licznik;
}

/* Prosty program testujący działanie stosu
 */
int main() {
    stos S;
    ini(&S);
    push(&S, 5);
    push(&S, -30);
    push(&S, 129);
    push(&S, -420);
    druk(S);

    while (!empty(S)) {
        printf("%d | ", pop(&S));
        druk(S);
    }
    printf("\n");

    for (int k = 0; k < 10000000; ++k)
        push(&S, k);
    printf("|S| = %d\n\n", size(S));
    for (int k = 0; k < 10000000; ++k)
        pop(&S);
    printf("|S| = %d\n\n", size(S));

    return 0;
}
