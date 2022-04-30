#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <cstring>
#include "lista.h"


int main()
{
    List *list=NULL;
    ifstream ifs;

    printf("--------------------------------------------------------------------------\n");
    printf("Wpisz nazwe programu \"Analyzer\", wraz z dlugoscia gramu i nazwa pliku.\n");
    printf("Po wykonaniu tej czynnosci i jej pomyslnym przebiegu wpisz \"exit\"\n");
    printf("--------------------------------------------------------------------------\n");
    system("cmd");

    ifs.open("baza.txt");
    if(!ifs.good())                 //sprawdzenie czy udało się otworzyć bazę danych
    {
        cerr << "Nie udalo sie otworzyc bazy danych" << endl;
        return 1;
    }

    FILE *fp=fopen("baza.txt", "r");;
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0)             //sprawdzenie czy baza danych nie jest pusta
    {
        cerr << "Baza danych jest pusta!" << endl;
        return 2;
    }
    else
        fseek(fp, 0, SEEK_SET);

    printf("Trwa przetwarzanie danych...\n");

    string reading1, reading2;      //odczyt bazy danych, reading1- gram, reading2- jego częstość występowania
    int number;
    do
    {
        getline(ifs, reading1);
        getline(ifs, reading2);
        number = atoi(reading2.c_str());                //konwersja stringa z częstotliwością na inta
        if(reading1 == "" || reading2 == "")
            break;
        addNew(list, reading1, number);
    }
    while(reading1 != "" || reading2 != "");

    Sort(list);

    ifs.close();

    char choice;
    string exit="no";

    do      //pętla w której może poruszać się użytkownik
    {
        system("cls");
        printf("------------------------------------------------------------\n");
        printf("Wybierz czynnosc, ktora chcesz wykonac wpisujac dana liczbe:\n");
        printf("1. Wypisz liste gramow\n");
        printf("2. Wypisz liste gramow wspak\n");
        printf("3. Wypisz szukany gram\n");
        printf("4. Wypisz wybrany przeddzial gramow\n");
        printf("5. Zlicz przestrzen\n");
        printf("6. Zaladuj nowy plik\n");
        printf("7. Wyjdz z programu\n");
        printf("-------------------------------------------------------------\n");
        cin >> choice;
        system("cls");

        switch(choice)
        {
        case '1':
            Write(list);
        break;

        case '2':
            WriteBackwards(list);
        break;

        case '3':
        {
            string searched;
            printf("Wpisz N-gram ktory chcesz wyszukac: \n");
            cin >> searched;
            WriteSearchedItem(list, searched);
        }
        break;

        case '4':
        {
            string bottoms, tops;
            int bottom, top;
            printf("Wpisz dolna i gorna granice przedzialu ktory chcesz wypisac: \n");
            cin >> bottoms >> tops;
            if(atoi(bottoms.c_str()) && atoi(tops.c_str()))     //sprawdzenie czy użytkownik podał liczby
            {
                bottom = atoi(bottoms.c_str());
                top = atoi(tops.c_str());
            }
            else
            {
                printf("Podano nieprawidlowe wartosci przedzialu!\n");
                break;
            }
            WriteInterval(list, bottom, top);
        }
        break;

        case '5':
            SpaceCounting(list);
        break;

        case '6':
        {
            removeList(list);
            delete list;
            list=NULL;      //usuwanie starej listy oraz dalej tworzenie nowej listy tak jak przy starcie programu

            printf("--------------------------------------------------------------------------\n");
            printf("Wpisz nazwe programu \"Analyzer\", wraz z dlugoscia gramu i nazwa pliku.\n");
            printf("Po wykonaniu tej czynnosci i jej pomyslnym przebiegu wpisz \"exit\"\n");
            printf("--------------------------------------------------------------------------\n");
            system("cmd");

            ifs.open("baza.txt");
            if(!ifs.good())
            {
                cerr << "Nie udalo sie otworzyc bazy danych" << endl;
                return 1;
            }

            FILE *fp=fopen("baza.txt", "r");;
            fseek(fp, 0, SEEK_END);
            if (ftell(fp) == 0)
            {
                cerr << "Baza danych jest pusta!" << endl;
                return 2;
            }
            else
                 fseek(fp, 0, SEEK_SET);

            printf("Trwa przetwarzanie danych...\n");

            do
            {
                getline(ifs, reading1);
                getline(ifs, reading2);
                number = atoi(reading2.c_str());
                if(reading1 == "" || reading2 == "")
                    break;
                addNew(list, reading1, number);
            }
            while(reading1 != "" || reading2 != "");

            Sort(list);
            printf("\nNowy plik zaladowany!\n");
            ifs.close();
        }
        break;

        case '7':
            return 0;
        break;

        default:
            continue;
        break;
        }

        system("PAUSE");        //pauza żeby użytkownik mógł zdecydować kiedy chce zakończyć dane działanie

    }while(exit=="no");

    delete list;
    list=NULL;

    return 0;
}
