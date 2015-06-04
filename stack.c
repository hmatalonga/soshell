#include "shell.h"

mystack *append(mystack *head, char value[]) {
    mystack *newp = (mystack *) malloc(sizeof(mystack)), *aux = head;
    if (newp == NULL)
        exit(1);
    strcpy(newp->value, value);
    newp->next = NULL;
    if (aux == NULL)
        return newp;
    else {
        while (aux->next != NULL) aux = aux->next;
        aux->next = newp;
    }
    return head;
}

mystack *push(mystack *head, char value[]) {
    mystack *newp = (mystack *) malloc(sizeof(mystack));
    if (newp == NULL)
        exit(1);
    strcpy(newp->value, value);
    newp->next = head;
    return newp;
}