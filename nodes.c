#include<stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "nodes.h"


pNode new_node(int node_number)
{
    pNode new_node = (pNode)malloc(sizeof(Node));
    if(new_node == NULL)
    {
        return NULL;
    }
    new_node->node_num = node_number;
    new_node->next = NULL;
    new_node->edges = NULL;
    new_node->distance = INT_MAX;
    new_node->visited = 0;
    return new_node;
}

void node_free(pNode node)
{
    pEdge curr_1 = node->edges;
    pEdge curr_2;
    while (curr_1 != NULL)
    {
        curr_2 = curr_1;
        curr_1 = curr_1->next;
        free(curr_2);
    }
    free(node);
}

void add_edge(pNode node, pEdge edge)
{
    edge->next = node->edges;
    node->edges = edge;
}

