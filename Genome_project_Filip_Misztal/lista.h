#ifndef LISTA_H
#define LISTA_H
#include <iostream>

using namespace std;

struct Ngram{
    string gram;
    int frequency;
};

struct Item{
    Ngram Ngram;
    int position;
    struct  Item *next;
    struct  Item *prev;
};

struct List{
    Item *first;
    Item *last;
    int number;
};

Item *SearchItem(List *list, string key);
void addNewCounting(List *&list, string gram);
void addNew(List *&list, string gram, int frequency);
void removeItem(List *list, Item *element);
Item *SearchMinItem(List *list, int &flaga);
void Sort(List *list);
void removeList(List *list);
void Write(List *list);
void WriteBackwards(List *list);
void WriteInterval(List *list, int bottom, int top);
void WriteSearchedItem(List *list, string key);
void Progress(double position, double size, double &percent);
void RecursiveLoop(List *&list, List *&newlist, int n, int &k, char gram[], double &percent, int &counter);
void SpaceCounting(List *list);

#endif // LISTA_H
