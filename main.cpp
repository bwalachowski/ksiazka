#include <iostream>
#include <stdlib.h>
#include <string>
#include "funkcje.hh"
#include <vector>


using namespace std;

int main()
{
    lista_przepisow *ksiazka = NULL;
    lista_przepisow *wybrane_przepisy = NULL;
    int recipe;
    wczytaj_przepis_z_pliku("przepisiki.txt", ksiazka);
    string imie;
    cout<<"Hello and welcome to my cookbook"<<endl;
    cout<<"What's your name?"<<endl;
    cin>>imie;
    cout<<"Hello  "<<imie<<endl;
    char wybor;
    do{

    cout<<"What would you like to eat?"<<"\n"<<"A. Breakfast "<<"\n"<<"B. Dinner "<<"\n"<<"C. Supper "<<"\n"<<"Choose A,B or C "<<endl;
    cout<<"If you want to add recipe press E"<<endl;
    cout<<"If you want to delete recipe press D"<<endl;
    cout<<"x - exit from program"<<endl;
    cin>>wybor;
    if(wybor=='A'){
        wybrane_przepisy = wybierz_typ(ksiazka, 1);
        cout<<"You chose breakfast"<<endl;
        cout<<"Do you want to see all breakfasts?"<<"\n"<<"press y if yes"<<"\t"<<"press anything else for no"<<endl;
        cin>>wybor;
        if(wybor=='y'){
            wyswietl_ksiazke(wybrane_przepisy);
            cout<<"Choose your recipe (write its number)"<<endl;
            cin>>recipe;
            wyswietl_przepis(wybrane_przepisy, recipe);

        }else{
        cout<<"What ingredients do you have?"<<endl;
            string sklad;
            cin>>sklad;
            wybrane_przepisy = wyszukaj_sklad(wybrane_przepisy, sklad);
            cout<<"These are all breakfasts with "<<sklad<<" :"<<endl;
            wyswietl_ksiazke(wybrane_przepisy);
            cout<<"Choose your recipe (write its number)"<<endl;
            cin>>recipe;
            wyswietl_przepis(wybrane_przepisy, recipe);
        }


    }else if(wybor=='B'){
        wybrane_przepisy = wybierz_typ(ksiazka, 2);
        cout<<"you chose dinner"<<endl;
        cout<<"Do you want to see all dinners?"<<"\n"<<"press y if yes"<<"\t"<<"press anything else for no"<<endl;
        cin>>wybor;
        if(wybor=='y'){
            wyswietl_ksiazke(wybrane_przepisy);
            cout<<"Choose your recipe (write its number)"<<endl;
            cin>>recipe;
            wyswietl_przepis(wybrane_przepisy, recipe);

        }else{
        cout<<"What ingredients do you have?"<<endl;
        string sklad;
        cin>>sklad;
        wybrane_przepisy = wyszukaj_sklad(wybrane_przepisy, sklad);
        cout<<"These are all dinners with "<<sklad<<" :"<<endl;
            wyswietl_ksiazke(wybrane_przepisy);
            cout<<"Choose your recipe (write its number)"<<endl;
            cin>>recipe;
            wyswietl_przepis(wybrane_przepisy, recipe);
        }


    }else if(wybor=='C'){
        wybrane_przepisy = wybierz_typ(ksiazka, 3);
        cout<<"you chose supper"<<endl;
        cout<<"Do you want to see all suppers?"<<"\n"<<"press y if yes"<<"\t"<<"press anything else for no"<<endl;
        cin>>wybor;
        if(wybor=='y'){
            wyswietl_ksiazke(wybrane_przepisy);
            cout<<"Choose your recipe (write its number)"<<endl;
            cin>>recipe;
            wyswietl_przepis(wybrane_przepisy, recipe);

        }else{
        cout<<"What ingredients do you have?"<<endl;
            string sklad;
            cin>>sklad;
            wybrane_przepisy = wyszukaj_sklad(wybrane_przepisy, sklad);
            cout<<"These are all suppers with "<<sklad<<" :"<<endl;
            wyswietl_ksiazke(wybrane_przepisy);
            cout<<"Choose your recipe (write its number)"<<endl;
            cin>>recipe;
            wyswietl_przepis(wybrane_przepisy, recipe);
        }

    }else if(wybor=='D'){
        cout << "Choose category from which you want to remove a recipe" << endl;
        cout << "A. Breakfast " << "\n" << "B. Dinner " << "\n" << "C. Supper " << "\n" << "Choose A,B or C " << endl;
        char wybor2;
        cin >> wybor2;
        if (wybor2 == 'A') {
            wybrane_przepisy = wybierz_typ(ksiazka, 1);
            wyswietl_ksiazke(wybrane_przepisy);
            cout << "Select a recipe to remove it";
            cin >> recipe;
            usun_przepis(wybrane_przepisy, ksiazka, recipe);
        }
        if (wybor2 == 'B') {
            wybrane_przepisy = wybierz_typ(ksiazka, 2);
            wyswietl_ksiazke(wybrane_przepisy);
            cout << "Select a recipe to remove it";
            cin >> recipe;
            usun_przepis(wybrane_przepisy, ksiazka, recipe);
        }
        if (wybor2 == 'C') {
            wybrane_przepisy = wybierz_typ(ksiazka, 3);
            wyswietl_ksiazke(wybrane_przepisy);
            cout << "Select a recipe to remove it";
            cin >> recipe;
            usun_przepis(wybrane_przepisy, ksiazka, recipe);
        }
    }else if(wybor=='E'){
        cout << "What category is your recipe: write 1 for breakfast, 2 for dinner, 3 for supper" << endl;
        int kat;
        cin >> kat;
        cout << "Write its name" << endl;
        string name;
        cin.get();
        getline(cin, name);
        cout << "How many minutes does i take?" << endl;
        int mins;
        cin >> mins;
        ingredient* skladniki = NULL;
        cout << "Write name of next ingredient or 'x' to finish adding ingredients" << endl;
        string iname;
        cin.get();
        getline(cin, iname);
        while (iname.compare("x") != 0) {
            cout << "Write quantity" << endl;
            string quant;
            getline(cin, quant);
            dodaj_skladnik(quant, iname, skladniki);
            cout << "Write name of next ingredient or 'x' to finish adding ingredients" << endl;
            getline(cin, iname);
        }
        cout << "write description" << endl;
        string desc;
        getline(cin, desc);
        dodaj_przepis(kat, name, mins, skladniki, desc, ksiazka);
    }
    usun_liste(wybrane_przepisy);
    }while(wybor!='x');

    wyczysc_ksiazke(ksiazka);
}



