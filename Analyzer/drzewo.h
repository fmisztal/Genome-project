#ifndef DRZEWO_H
#define DRZEWO_H
#include <iostream>

using namespace std;

struct Gram{
    string gram;
    int frequency;
};

struct Branch
{
    struct Gram dana;
    int number;
    struct Branch *A;
    struct Branch *T;
    struct Branch *G;
    struct Branch *C;
};

struct Tree
{
    Branch *root;
};

void NewBranch(Branch *&element, string leaf, int frequency, double pointer);
void NewTree(Tree *tree);
Branch *Search(Branch *element, string key);
void NewLeaf(Branch *element, string leaf);
void DeleteBranch(Branch *element);
void DeleteTree(Tree *tree);

#endif // DRZEWO_H
