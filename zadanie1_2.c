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

// Zadanie 7
void usun_podzielne(list * l, int k){
    list pierwszy = (*l);
    while ((*l)->next != NULL) {
        if((*l)->next->info % k == 0) {
            list nast = (*l)->next->next;
            usun(&(*l)->next);
            (*l)->next = nast;
        }
        else
            *l = (*l)->next;
    }
    *l = pierwszy;
}

//Zadanie 8
void usun_wszystkie(list * l) {
    while(*l != NULL) {
        usun(l);
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


//Zadanie3
void dodaj_liczbe(list h, int a) {
    while(h != NULL) {
        h->info += a;
        h = h->next;
    }

}

//Zadanie 4
void odwroc_rek(list * l) {
    if(*l != NULL && (*l)->next != NULL) {
        list reszta = (*l)->next;
        odwroc_rek(&reszta);
        (*l)->next->next = *l;
        (*l)->next = NULL;
        *l = reszta;
    }
}

void odwroc_it(list * l) {
    if(*l != NULL) {
        list odwr = NULL;
        list nast;
        while((*l)->next != NULL) {
            nast = (*l)->next;
            (*l)->next = odwr;
            odwr = (*l);
            (*l) = nast;
        }
        (*l)->next = odwr;
    }

}

//Zadanie 5
int podzielne(list l, int k) {
    int licznik = 0;
    while(l != NULL) {
        if (l->info % k == 0) {
            ++licznik;
        }
        l = l->next;
    }
    return licznik;
}

//Zadanie 6
bool niemalejąca(list l) {
    while (l->next != NULL) {
        if (l->next->info < l->info)
            return false;
        l = l->next;
    }
    return true;
}



// IMPLEMENTACJA KOLEJKI OPARTEJ NA LIŚCIE 1-KIERUNKOWEJ

/* Alias reprezentujący wskaźnik na początek
 */
typedef list kolejka;

/* Sprawdza czy stos K jest pusty
 */
bool empty(kolejka Q) {
    return Q == NULL;
}

/* Wstawia liczbę x na koniec kolejki Q
 */
void push_back(kolejka * Q, info_t x) {
    if (empty(*Q)) {
        dodaj(Q, nowy(x));
    }
    else {
        element* q = *Q;
        while (q->next != NULL) {
            q = q->next;
        }
        dodaj(&(q->next), nowy(x));

    }
}

/* Zdejmuje element z początku kolejki S i daje jego wartość w wyniku.
 * Zwraca 0, gdy stos jest pusty.
 */
info_t pop_front(kolejka * Q) {
    info_t wynik = 0;
    if (!empty(*Q)) {
        wynik = (*Q)->info;
        usun(Q);
    }
    return wynik;
}

/* Daje liczbę elementów umieszczonych na stosie
 */
int size(kolejka Q) {
    int licznik = 0;
    while (Q != NULL) {
        ++licznik;
        Q = Q->next;
    }
    return licznik;
}

/* Prosty program testujący działanie stosu
 */
int main() {
    kolejka K;
    ini(&K);
    push_back(&K, 5);
    push_back(&K, 30);
    push_back(&K, 30);
    push_back(&K, 129);
    push_back(&K, 420);
    if(niemalejąca(K))
        printf("jest niemalejaca\n");
    else
        printf("nie jest niemalejaca\n");

    druk(K);

    dodaj_liczbe(K, 5);
    druk(K);

    odwroc_rek(&K);
    druk(K);

    odwroc_it(&K);
    druk(K);

    //test zadanie 7
    usun_podzielne(&K,35);
    druk(K);


    // test zadanie 8
    usun_wszystkie(&K);
    printf("----\n");
    druk(K);
    printf("----\n");

    printf("%d \n\n ", podzielne(K, 5));

    while (!empty(K)) {
        printf("%d | ", pop_front(&K));
        druk(K);
    }
    printf("\n");

    for (int k = 0; k < 1000; ++k)
        push_back(&K, k);
    printf("|K| = %d\n\n", size(K));
    for (int k = 0; k < 1000; ++k)
        pop_front(&K);
    printf("|K| = %d\n\n", size(K));

    return 0;
}
