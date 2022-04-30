#include "drzewo.h"
#include <iostream>

//drzewo o nietypowej formie, bo dane umieściłem jedynie na końcach gałęzi, lecz tak było mi prościej je skonstruować

void NewBranch(Branch *&element, string leaf, int frequency, double pointer)    //funkcja do tworzenia nowego elementu drzewa
{
    if(!element)                                                                //gdy istnieje dopiero tylko korzeń
    {
        element=new Branch;
        element->number=pointer+1;
        element->A=NULL;
        element->T=NULL;
        element->G=NULL;
        element->C=NULL;
        element->dana.frequency=NULL;
    }

    pointer++;
    if(leaf[pointer]==NULL)                                                     //gdy dotrze w odpowiednie miejsce, dodaje "liść"
    {
        element->dana.gram=leaf;
        element->dana.frequency=frequency;
        return;
    }

    if (leaf[element->number]=='A')                                             //jeśli to nie to miejsce, idzie dalej
        NewBranch(element->A, leaf, frequency, pointer);
    if (leaf[element->number]=='T')
        NewBranch(element->T, leaf, frequency, pointer);
    if (leaf[element->number]=='G')
        NewBranch(element->G, leaf, frequency, pointer);
    if (leaf[element->number]=='C')
        NewBranch(element->C, leaf, frequency, pointer);
}

void NewTree(Tree *tree)                                                       //funkcja pomocnicza do tworzenia nowego drzewa
{
    tree->root = new Branch;
    tree->root->number=0;
    tree->root->A=NULL;
    tree->root->T=NULL;
    tree->root->G=NULL;
    tree->root->C=NULL;
    tree->root->dana.frequency=0;
}

Branch *Search(Branch *element, string key)                                    //funkcja do wyszukiwania elementu w drzewie
{
    Branch *temp=element;
    do
    {
        switch(key[temp->number])                                              //porusza się po gałęzi aż do jej końca
        {
        case 'A':
            temp=temp->A;
        break;

        case 'T':
            temp=temp->T;
        break;

        case 'G':
            temp=temp->G;
        break;

        case 'C':
            temp=temp->C;
        break;

        default:
            return NULL;
        break;
        }
        if(temp)
            if (temp->dana.gram==key)
                return temp;

    }while(temp);
    return NULL;
}

void NewLeaf(Branch *element, string leaf)                                   //funkcja rozstrzygająca co zrobić z nową daną
{
    Branch *temp;
    if(temp=Search(element, leaf))
        temp->dana.frequency++;
    else
        NewBranch(element, leaf, 1, -1);
}

void DeleteBranch(Branch *element)                                          //funkcje do usuwania drzewa
{
    if (element->A)
        DeleteBranch(element->A);
    if (element->T)
        DeleteBranch(element->T);
    if (element->G)
        DeleteBranch(element->G);
    if (element->C)
        DeleteBranch(element->C);
    delete element;
}

void DeleteTree(Tree *tree)
{
    if (tree->root!=NULL)
        DeleteBranch(tree->root);
    tree->root=NULL;
}
