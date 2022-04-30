#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "lista.h"
#include "kolejka.h"
#include "drzewo.h"

using namespace std;

void TreeToList(Branch *element, List *&list)          //funkcja do przepisywania drzewa na listę
{
    if (element->A)
        TreeToList(element->A, list);
    if (element->T)
        TreeToList(element->T, list);
    if (element->G)
        TreeToList(element->G, list);
    if (element->C)
        TreeToList(element->C, list);
    if (element->dana.gram!="")
        addNew(list, element->dana.gram, element->dana.frequency);
}


int main(int argc, char* argv[])
{
    ifstream ifs;
    ofstream ofs;

    List *list=NULL;
    Tree *tree=new Tree;
    NewTree(tree);

    Queue *first=NULL;
    Queue *last=NULL;

    if(argc!=3)                 //sprawdzenie czy użytkownik podał wszystkie potrzebne parametry w linii poleceń
    {
        cerr << "Nie podano wszystkich parametrow" << endl;
        return 1;
    }

    if(!isdigit(*argv[1]))      //sprawdzenie czy pierwszy parametr jest liczbą
    {
        cerr << "Wpisana dlugosc gramu nie jest liczba" << endl;
        return 2;
    }

    int x=atoi(argv[1]);

    if(x<=0)                    //sprawdzenie czy podana długość nie jest mniejsza lub równa 0
    {
        cerr << "Wprowadzono nieprawidlowa dlugosc gramu" << endl;
        return 3;
    }

    ifs.open(argv[2]);

    if(!ifs.good())             //sprawdzenie czy udało się otworzyć dany plik
    {
        cerr << "Nie udalo sie otworzyc pliku " << argv[2] << endl;
        return 4;
    }

    FILE *fp;
    fp=fopen(argv[2], "r");
    ofs.open("baza.txt");

    printf("\nTrwa odczytywanie danych z pliku %s\n",argv[2]);

    string firstline;
    getline(ifs, firstline);
    double start = ifs.tellg();     //ignoruję pierwszą linijkę pliku i zapisuję pozycję odczytu z jej końca

    fseek(fp, 0, SEEK_END);         //sprawdzam ile znaków znajduje się w pliku
    double size = ftell(fp);
    double percent;

    ifs.seekg(start);               //kontynuuję odczyt od drugiej linijki pliku

    int cursor=0, counter=0;        //cursor przesuwa pozycję odczytu, counter bada czy kolejka ma porządaną długość
    char symbol;

    Queue *tmp;
    while(feof(fp)==0)
    {
        fseek(fp, start+cursor, SEEK_SET);              //ustawienie pozycji odczytu

        symbol=getc(fp);

        if(symbol=='\n' || symbol==' ')
        {
            fseek(fp, start+cursor+1, SEEK_SET);        //ignorowanie znaków białych i badanie czy nie osiągnięto końca pliku
            symbol=getc(fp);
            if(feof(fp)!=0)
                break;
        }

        if(symbol=='G' || symbol=='T' || symbol=='A' || symbol=='C')
        {
            if(counter==x)                            //gdy kolejka jest już wystarczająco długa
            {
                push(&first,&last,symbol);
                pop(&first);

                tmp=first;

                int i=0;
                char *danachar = new char[x+1];
                danachar[x]=NULL;
                string dana;

                while(tmp!=NULL)
                {
                    danachar[i]=tmp->base;
                    tmp=tmp->next;
                    i++;
                }
                dana=danachar;
                delete [] danachar;
                NewLeaf(tree->root, dana);           //zapis aktualnego stanu kolejki do drzewa wraz ze zliczeniem
            }
            else                                     //gdy kolejka dopiero zaczyna się tworzyć
            {
                push(&first,&last,symbol);
                counter++;
            }
        }
        Progress(start+cursor, size, percent);       //sprawdzam postępy
        cursor++;
    }
    printf("\rPrzeanalizowano 100%% danych");

    printf("\nProgram tworzy baze danych...");
    TreeToList(tree->root, list);                   //przepisanie drzewa na listę (bo łatwiej mi było odczytywać z listy niż z drzewa a zajmuje to mało czasu)
    DeleteTree(tree);
    Item *temp = list->first;
    while(temp!=NULL)                               //zapis listy do bazy danych
    {
        ofs << temp->Ngram.gram << endl << temp->Ngram.frequency << endl;
        temp=temp->next;
    }

    ofs.close();
    ifs.close();

    printf("\rBaza danych zostala stworzona!\n");

    return 0;
}
