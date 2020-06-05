#include "funkcje.hh"

void wczytaj_przepis_z_pliku(string nazwa_pliku, lista_przepisow* &ksiazka_kucharska){
	ifstream plik(nazwa_pliku);
	if (plik.is_open()) {
		while (!plik.eof()) {
			string nazwa;
			getline(plik, nazwa);
			ingredient* skladniki = NULL;
			char c = ' ';
			while (c != ';') {
				string ilosc;
				getline(plik, ilosc, '|');
				string snazwa;
				getline(plik, ilosc, ',');
				plik.get(c);
				dodaj_skladnik(ilosc, snazwa, skladniki);
				cout << c << endl;
			}
			plik.get();
			int kat;
			plik >> kat;

			plik.get();
			int czas;
			plik >> czas;

			string opis;
			plik.get();
			getline(plik, opis, ';');
			cout << opis << endl;
			plik.get();

			dodaj_przepis(kat, nazwa, czas, skladniki, opis, ksiazka_kucharska);
		}
	}

};

void usun_skladniki(ingredient* skladniki) {
	if (skladniki) {
		usun_skladniki(skladniki->nast);
		delete skladniki;
	}
}

void usun_przepis(lista_przepisow* &wybrane_przepisy, lista_przepisow* &ksiazka, int recipe) {
	lista_przepisow* pom = wybrane_przepisy;
	int i = 1;
	while (i < recipe && pom) {
		pom = pom->nast;
		++i;
	}
	if (pom) {
		przepis* pom2 = pom->przepis;
		if (!pom->poprz) {
			wybrane_przepisy = pom->nast;
			pom->nast->poprz = NULL;
		}
		else if (!pom->nast) {
			pom->poprz->nast = NULL;
		}
		else {
			pom->nast->poprz = pom->poprz;
			pom->poprz->nast = pom->nast;
		}
		delete pom;

		pom = ksiazka;
		while (pom && pom->przepis != pom2) {
			pom = pom->nast;
		}
		if (pom) {
			usun_skladniki(pom2->skladniki);
			if (!pom->poprz) {
				ksiazka = pom->nast;
				pom->nast->poprz = NULL;
			}
			else if (!pom->nast) {
				ksiazka = NULL;
			}
			else {
				pom->nast->poprz = pom->poprz;
				pom->poprz->nast = pom->nast;
			}
			delete pom->przepis;
			delete pom;
		}
	}
}

void sortuj_alf(lista_przepisow* &ksiazka_kucharska){
	if (ksiazka_kucharska) {
		lista_przepisow* babel = ksiazka_kucharska->nast;

		while (babel && babel->poprz) {

			lista_przepisow* pom = babel->poprz;

			while (pom && pom->przepis->nazwa.compare(babel->przepis->nazwa) > 0) {
				pom = pom->poprz;
			}

			lista_przepisow* pom2 = babel;
			babel = babel->nast;
			pom2->poprz->nast = babel;
			if (babel) {
				babel->poprz = babel->poprz->poprz;
			}

			if (!pom) {
				pom2->poprz = NULL;
				pom2->nast = ksiazka_kucharska;
				ksiazka_kucharska->poprz = pom2;
				ksiazka_kucharska = pom2;
			}

			else {
				pom2->poprz = pom;
				pom2->nast = pom->nast;
				pom->nast = pom2;
				if (pom2->nast) {
					pom2->nast->poprz = pom2;
				}
			}
		}
	}
};

void sortuj_czas(lista_przepisow* &ksiazka_kucharska){
	if (ksiazka_kucharska) {
		lista_przepisow* babel = ksiazka_kucharska->nast;

		while (babel && babel->poprz) {

			lista_przepisow* pom = babel->poprz;

			while (pom && pom->przepis->czas > babel->przepis->czas) {
				pom = pom->poprz;
			}

			lista_przepisow* pom2 = babel;
			babel = babel->nast;
			pom2->poprz->nast = babel;
			if (babel) {
				babel->poprz = babel->poprz->poprz;
			}

			if (!pom) {
				pom2->poprz = NULL;
				pom2->nast = ksiazka_kucharska;
				ksiazka_kucharska->poprz = pom2;
				ksiazka_kucharska = pom2;
			}

			else {
				pom2->poprz = pom;
				pom2->nast = pom->nast;
				pom->nast = pom2;
				if (pom2->nast) {
					pom2->nast->poprz = pom2;
				}
			}
		}
	}
};

bool jest_skladnik(ingredient* skladniki, string nazwa) {
	if (!skladniki) {
		return false;
	}
	if (skladniki->nazwa.compare(nazwa) == 0) {
		return true;
	}
	return jest_skladnik(skladniki->nast, nazwa);
}

lista_przepisow* wyszukaj_sklad(lista_przepisow* ksiazka_kucharska, string nazwa_skladnika){
	lista_przepisow* pom = ksiazka_kucharska;
	lista_przepisow* akt = NULL;
	lista_przepisow* wybrane_przepisy = NULL;
	while (pom) {
		if (jest_skladnik(pom->przepis->skladniki, nazwa_skladnika)) {
			if (!akt) {
				wybrane_przepisy = new lista_przepisow;
				wybrane_przepisy->przepis = pom->przepis;
				wybrane_przepisy->nast = NULL;
				wybrane_przepisy->poprz = NULL;
				akt = wybrane_przepisy;
			}
			else {
				akt->nast = new lista_przepisow;
				akt->nast->poprz = akt;
				akt = akt->nast;
				akt->przepis = pom->przepis;
				akt->nast = NULL;
			}
		}
		pom = pom->nast;
	}
	return wybrane_przepisy;
};

void wyswietl_ksiazke(lista_przepisow* ksiazka_kucharska){
	int n = 1;
	lista_przepisow* pom = ksiazka_kucharska;
	while (pom) {
		cout << n << ". " << pom->przepis->nazwa << endl;
		++n;
		pom = pom->nast;
	}
};

lista_przepisow* wybierz_typ(lista_przepisow* ksiazka_kucharska, int typ_dania){
	lista_przepisow* pom = ksiazka_kucharska;
	lista_przepisow* akt = NULL;
	lista_przepisow* wybrane_przepisy = NULL;
	while(pom) {
		if (pom->przepis->typ_dania == typ_dania) {
			if (!akt) {
				wybrane_przepisy = new lista_przepisow;
				wybrane_przepisy->przepis = pom->przepis;
				wybrane_przepisy->nast = NULL;
				wybrane_przepisy->poprz = NULL;
				akt = wybrane_przepisy;
			}
			else {
				akt->nast = new lista_przepisow;
				akt->nast->poprz = akt;
				akt = akt->nast;
				akt->przepis = pom->przepis;
				akt->nast = NULL;
			}
		}
		pom = pom->nast;
	}
	return wybrane_przepisy;
};

void wyswietl_przepis(lista_przepisow* wybrane_przepisy, int n){
	lista_przepisow* pom = wybrane_przepisy;
	int i = 1;
	while (i < n) {
		pom = pom->nast;
		++i;
	}
	cout << pom->przepis->nazwa << endl;
	cout << "Prep time: " << pom->przepis->czas << " mins" << endl;
	cout << "Ingredients: " << endl;
	ingredient* pomIng = pom->przepis->skladniki;
	while (pomIng) {
		cout << pomIng->nazwa << " " << pomIng->ilosc << endl;
		pomIng = pomIng->nast;
	}
	cout << "opis:" << endl;
	cout << pom->przepis->opis << endl;
}

void usun_liste(lista_przepisow* wybrane_przepisy)
{
	if (wybrane_przepisy) {
		usun_liste(wybrane_przepisy->nast);
		delete wybrane_przepisy;
	}
}

void wyczysc_ksiazke(lista_przepisow* ksiazka)
{
	if (ksiazka) {
		wyczysc_ksiazke(ksiazka->nast);
		usun_skladniki(ksiazka->przepis->skladniki);
		delete ksiazka->przepis;
		delete ksiazka;
	}
}

void dodaj_skladnik(string quant, string iname, ingredient* &skladniki)
{
	if (skladniki) {
		ingredient* pom = skladniki;
		while (pom->nast) {
			pom = pom->nast;
		}
		pom->nast = new ingredient;
		pom = pom->nast;
		pom->ilosc = quant;
		pom->nazwa = iname;
		pom->nast = NULL;

	}
	else {
		skladniki = new ingredient;
		skladniki->ilosc = quant;
		skladniki->nazwa = iname;
		skladniki->nast = NULL;
	}
}

void dodaj_przepis(int kat, string name, int mins, ingredient* skladniki, string desc, lista_przepisow* &ksiazka)
{
	if (ksiazka) {
		lista_przepisow* pom = ksiazka;
		while (pom->nast) {
			pom = pom->nast;
		}
		pom->nast = new lista_przepisow;
		pom->nast->poprz = pom;
		pom = pom->nast;
		pom->przepis = new przepis;
		pom->przepis->typ_dania = kat;
		pom->przepis->miejsce_w_ksiazce = pom;
		pom->przepis->czas = mins;
		pom->przepis->nazwa = name;
		pom->przepis->skladniki = skladniki;
		pom->przepis->opis = desc;
		pom->nast = NULL;
	}
	else {
		ksiazka = new lista_przepisow;
		ksiazka = ksiazka;
		ksiazka->przepis = new przepis;
		ksiazka->przepis->typ_dania = kat;
		ksiazka->przepis->miejsce_w_ksiazce = ksiazka;
		ksiazka->przepis->czas = mins;
		ksiazka->przepis->nazwa = name;
		ksiazka->przepis->skladniki = skladniki;
		ksiazka->przepis->opis = desc;
		ksiazka->poprz = NULL;
		ksiazka->nast = NULL;
	}
	
}


