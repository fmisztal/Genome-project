#ifndef KOLEJKA_H
#define KOLEJKA_H

struct Queue{
    char base;
    struct Queue *next;
    struct Queue *prev;
};

void push(Queue **first, Queue **last, char symbol);
void pop(Queue **first);
void show(Queue *first);

#endif // KOLEJKA_H
