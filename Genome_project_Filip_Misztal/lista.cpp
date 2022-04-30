#include "lista.h"
#include <iostream>
#include <math.h>

Item *SearchItem(List *list, string key)                         //funkcja wyszukująca dany gram w liście
{
    Item *temp=list->first;
    while(temp)
    {
        if(temp->Ngram.gram==key)
            return temp;
        temp=temp->next;
    }
    return NULL;
}

void Progress(double position, double size, double &percent)    //funkcja do pokazywania postępów działania programu
{
    if(!percent)
    {
        printf("\rPrzeanalizowano 0%% danych");
        if(size>40000)
            percent=0.01;
        else
            percent=0.1;
    }

    if(((position)/size)>percent)
    {
        printf("\rPrzeanalizowano %d%% danych", (int)round(percent*100));
        if(size>40000)
            percent+=0.01;
        else
            percent+=0.1;
    }
}

void addNewCounting(List *&list, string gram)       //funkcja dodająca pozycję do listy, która dodatkowo zlicza powtórzenia danych sekwencji
{                                                   //(ostatecznie zastosowałem drzewo więc jest ona nieprzydatna, ale ją tutaj zostawiłem  )
    Item *temp;
    if(!list)
    {
        list=new List;
        list->first=new Item;
        list->last=list->first;
        list->number=1;
        temp= list->first;
        temp->Ngram.gram=gram;
        temp->Ngram.frequency=1;
        temp->position=1;
        temp->next=NULL;
        temp->prev=NULL;
    }
    else
    {
        Item *temp;
        if(temp=SearchItem(list, gram))
            temp->Ngram.frequency++;
        else
        {
            temp=list->last;
            temp->next=new Item;
            temp->next->prev=temp;
            temp=temp->next;
            temp->position=temp->prev->position;
            temp->position++;
            temp->next=NULL;
            temp->Ngram.gram=gram;
            temp->Ngram.frequency=1;
            list->last=temp;
            list->number++;
        }
    }
}

void addNew(List *&list, string gram, int frequency)        //funkcja dodająca nowy gram do listy wraz z policzoną już częstotliwością
{
    Item *temp;
    if(!list)
    {
        list=new List;
        list->first=new Item;
        list->last=list->first;
        list->number=1;
        temp= list->first;
        temp->Ngram.gram=gram;
        temp->Ngram.frequency=frequency;
        temp->position=1;
        temp->next=NULL;
        temp->prev=NULL;
    }
    else
    {
        temp=list->last;
        temp->next=new Item;
        temp->next->prev=temp;
        temp=temp->next;
        temp->position=temp->prev->position;
        temp->position++;
        temp->next=NULL;
        temp->Ngram.gram=gram;
        temp->Ngram.frequency=frequency;
        list->last=temp;
        list->number++;
    }
}

void removeItem(List *list, Item *element)                //usuwanie jednej pozycji z listy
{
    Item *temp=list->first;
    if(!element || !(list->first))
        return;
    if(temp==element)
    {
        list->first=temp->next;
        if(temp->next)
            temp->next->prev=NULL;
        else
            list->last=NULL;
        free(element);
        list->number--;
        return;
    }
    while(temp)
    {
        if(temp==element)
        {
            if(!temp->next)
            {
                temp->prev->next=NULL;
                list->last=temp->prev;
            }
            else
            {
                temp->prev->next=temp->next;
                temp->next->prev=temp->prev;
            }
            free(element);
            list->number--;
            break;
        }
        temp=temp->next;
    }
}

Item *SearchMinItem(List *list, int &flaga)     //funkcja wyszukująca gram o najmniejszej częstotliwości
{                                               //głównie pomocnicza do funkcji sort
    int min=0;
    Item *minelem=NULL;
    Item *temp=list->first;
    if(!temp)
        return NULL;
    while(temp)
    {
        if(temp->Ngram.frequency<min || !minelem)
        {
            minelem=temp;
            min=temp->Ngram.frequency;
        }
        if(temp->Ngram.frequency==flaga)
            break;
        temp=temp->next;
    }
    flaga=minelem->Ngram.frequency;
    return minelem;
}

void Sort(List *list)       //sortowanie listy (niestety mało wydajne, testowałem jeszcze 3 inne sposoby, najszybciej przebiegało sortowanie drzewem,
{                           //lecz przy dużych bazach i gramach dłuższych niż 15 otrzymywałem błąd sigsegv, którego nie potrafiłem wyeliminować
    List *nowa=NULL;
    Item *temp;
    double size=list->number, position=0, percent=0;
    int flaga=1;
    while(temp=SearchMinItem(list, flaga))
    {
        addNew(nowa, temp->Ngram.gram, temp->Ngram.frequency);
        removeItem(list,temp);
        Progress(position++, size, percent);
    }
    printf("\rPrzeanalizowano 100%% danych");
    list->first=nowa->first;
    list->last=nowa->last;
    list->number=nowa->number;
    delete[] temp;
}

void removeList(List *list)           //usuwanie całej listy
{
    Item *temp;
    while(list->first)
    {
        temp=list->first;
        list->first=list->first->next;
        free(temp);
    }
    list->last=list->first;
    list->number=0;
}

void Write(List *list)               //wypisuje całą listę od początku do końca
{
    if(!list || (list->first==NULL && list->last==NULL))
        printf("Lista jest pusta\n");
    else
    {
        Item *temp=list->first;
        do{
            printf("N-gram %d = %s: %d\n",temp->position,temp->Ngram.gram.c_str(),temp->Ngram.frequency);
            temp=temp->next;
        }while(temp);
        printf("Lista ma %d N-gramow\n",list->number);
    }
}

void WriteBackwards(List *list)     //wypisanie listy od tyłu
{
    if(!list || (list->first==NULL && list->last==NULL))
        printf("Lista jest pusta\n");
    else
    {
        Item *temp=list->last;
        do{
            printf("N-gram %d = %s: %d\n",temp->position,temp->Ngram.gram.c_str(),temp->Ngram.frequency);
            temp=temp->prev;
        }while(temp);
        printf("Lista ma %d N-gramow\n",list->number);
    }
}

void WriteInterval(List *list, int bottom, int top)     //funkcja wypisująca gramy o czętotliwościach z przedziału podanego przez użytkownika
{
    Item *temp=list->first;
    List *nowa=NULL;
    while(temp)
    {
        if(temp->Ngram.frequency>=bottom && temp->Ngram.frequency<=top)
            addNew(nowa, temp->Ngram.gram, temp->Ngram.frequency);
        temp=temp->next;
    }
    Write(nowa);
}

void WriteSearchedItem(List *list, string key)         //funkcja wypisująca gram podany przez użytkownika
{
    Item *temp=list->first;
    Item *searched=NULL;
    while(temp)
    {
        if(temp->Ngram.gram==key)
        {
            searched=temp;
            break;
        }
        temp=temp->next;
    }
    if(!searched)
        printf("Nie udalo sie znalezc N-gramu: %s\n",key.c_str());
    else
    {
        printf("N-gram %d = %s: %d\n",temp->position,searched->Ngram.gram.c_str(),searched->Ngram.frequency);
    }
}

void RecursiveLoop(List *&list, List *&newlist, int n, int &k, char gram[], double &percent, int &counter)     //funkcja zawierająca pętlę for, która wywołuje się do momentu, w którym dana sekwencja DNA
{                                                                                                              //osiągnie porządaną długość. Służy do utworzenia listy brakujących n-gramów
    char tab[4]={'A','T','G','C'};

    for(int i=0; i<4; i++)
    {
        gram[k]=tab[i];
        if(k!=n-1)
        {
            k++;
            RecursiveLoop(list, newlist, n, k, gram, percent, counter);
        }
        else
        {
            counter++;
            string dana=gram;
            if(!SearchItem(list, dana))
                addNew(newlist, dana, 0);
            Progress(counter,pow(4,n),percent);
        }
    }
    k--;
}

void SpaceCounting(List *list)      //funkcja zliczająca przestrzeń zajętą przez n-gramy obecne w genotypie dla wszystkich możliwych kombinacji
{                                   //dodałem do tego również możliwość wypisania brakujących gramów (przy dłuższych gramach mało wydajne, ale nie ustalałem limitu)
    string choice;
    int size=(list->first->Ngram.gram).length();
    printf("Czy chcesz od razu wypisac brakujace gramy? Jesli tak, wpisz \"tak\": ");
    cin >> choice;
    if(choice=="tak")
    {
        printf("Trwa wyszukiwanie brakujacych N-gramow...\n");
        List *nowa=NULL;
        char gram[size+1];
        gram[size]=NULL;
        int k=0, counter=0;
        double percent;
        RecursiveLoop(list, nowa, size, k, gram, percent, counter);
        printf("\rPrzeanalizowano 100%% danych\n");
        Write(nowa);
    }
    double result;
    result=(list->number/(pow(4,size)))*100;
    printf("Procent mozliwej przestrzeni dla N-gramow obecna w genotypie: %f%\n", result);
}
