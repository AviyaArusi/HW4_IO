#include <stdio.h>
#include <stdlib.h>
#include "edges.h"


pEdge new_edge(int weight, pNode endpoint)
{
    pEdge p = (pEdge)(malloc(sizeof(Edge)));
    if(p == NULL) { return NULL; }
    p -> weight = weight;
    p -> endpoint = endpoint;
    p -> next = NULL;
    return p;
}

void free_edge(pEdge edge)
{
    free(edge);
}



