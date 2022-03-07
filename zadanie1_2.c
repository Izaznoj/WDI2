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

// IMPLEMENTACJA KOLEJKI OPARTEJ NA LIŚCIE 1-KIERUNKOWEJ

/* Alias reprezentujący wskaźnik na wierzchołek stosu
 */
typedef list kolejka;

/* Sprawdza czy stos K jest pusty
 */
bool empty(kolejka K) {
    return K == NULL;
}

/* Wstawia liczbę x na koniec kolejki S
 */
void push_back(kolejka K, info_t x) {
    while (K->next != NULL) {
        K = K->next;
    }
    K->next = nowy(x);
}

/* Zdejmuje element z początku kolejki S i daje jego wartość w wyniku.
 * Zwraca 0, gdy stos jest pusty.
 */
info_t pop_front(kolejka * K) {
    info_t wynik = 0;
    if (!empty(*K)) {
        wynik = (*K)->info;
        usun(K);
    }
    return wynik;
}

/* Daje liczbę elementów umieszczonych na stosie
 */
int size(kolejka K) {
    int licznik = 0;
    while (K != NULL) {
        ++licznik;
        K = K->next;
    }
    return licznik;
}

/* Prosty program testujący działanie stosu
 */
int main() {
    kolejka K;
    ini(&K);
    push_back(K, 5);
    push_back(K, -30);
    push_back(K, 129);
    push_back(K, -420);
    druk(K);

    while (!empty(K)) {
        printf("%d | ", pop_front(&K));
        druk(K);
    }
    printf("\n");

    for (int k = 0; k < 10000000; ++k)
        push_back(K, k);
    printf("|K| = %d\n\n", size(K));
    for (int k = 0; k < 10000000; ++k)
        pop_front(&K);
    printf("|K| = %d\n\n", size(K));

    return 0;
}
