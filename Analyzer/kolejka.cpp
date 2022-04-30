#include "kolejka.h"
#include <iostream>

//kolejka FIFO

void push(Queue **first, Queue **last, char symbol)     //dodaje element na koniec kolejki
{
    Queue *nowy;
    nowy=new Queue;
    nowy->base=symbol;
    nowy->next=NULL;
    nowy->prev=NULL;

    if(*first==NULL)                                   //jeśli jeszcze nie istnieje
    {
        *first=nowy;
        *last=nowy;
    }
    else
    {
        nowy->prev=(*last);
        (*last)->next=nowy;
        (*last)=nowy;
    }
}

void pop(Queue **first)                     //usuwa element z kolejki (pierwszy)
{
    Queue *temp=(*first);
    if((*first)==NULL)                      //gdy kolejka jest już pusta
        printf("Brak pozycji w kolejce");
    else
    {
        if((*first)->next==NULL)            //gdy kolejka ma tylko jeden element
            *first=NULL;
        else                                //gdy kolejka istnieje i ma więcej niż 1 element
        {
            (*first)=(*first)->next;
            (*first)->prev=NULL;
            free(temp);
        }
    }
}

void show(Queue *first)     //funkcja właściwie nie potrzebna w tym programie, przydawała się do testowania działania kolejki
{                           //uznałem, że mimo wszystko ją zostawię
    if(first==NULL)
        printf("Brak pozycji w kolejce");
    else
        while(first!=NULL)
        {
            printf("%c\n", first->base);
            first=first->next;
        }
}
