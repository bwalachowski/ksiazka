#ifndef FUNKCJE_HH_INCLUDED
#define FUNKCJE_HH_INCLUDED
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

struct ingredient{
    string nazwa;
    string ilosc;
    ingredient* nast;
};

struct lista_przepisow;

struct przepis{
    string nazwa;
    int typ_dania; //1-breakfast, 2-dinner, 3-supper
    ingredient *skladniki;
    string opis;
    int czas; //w minutach
    lista_przepisow* miejsce_w_ksiazce;
};

struct lista_przepisow {
    przepis* przepis;
    lista_przepisow* nast;
    lista_przepisow* poprz;
};



void wczytaj_przepis_z_pliku(string nazwa_pliku, lista_przepisow* &ksiazka_kucharska);

void usun_przepis(lista_przepisow* &wybrane_przepisy, lista_przepisow* &ksiazka, int recipe);

void sortuj_alf(lista_przepisow* &ksiazka_kucharska);

void sortuj_czas(lista_przepisow* &ksiazka_kucharska);

lista_przepisow* wyszukaj_sklad(lista_przepisow* ksiazka_kucharska, string nazwa_skladnika);

void wyswietl_ksiazke(lista_przepisow* ksiazka_kucharska);

lista_przepisow* wybierz_typ(lista_przepisow* ksiazka_kucharska, int typ_dania);

void wyswietl_przepis(lista_przepisow* wybrane_przepisy, int n);

void usun_liste(lista_przepisow* wybrane_przepisy);

void wyczysc_ksiazke(lista_przepisow* ksiazka);

void dodaj_skladnik(string quant, string iname, ingredient* &skladniki);

void dodaj_przepis(int kat,string name,int mins,ingredient* skladniki, string desc, lista_przepisow* &ksiazka);



#endif // FUNKCJE_HH_INCLUDED
