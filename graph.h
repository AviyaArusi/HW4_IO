#include <stdlib.h>

#ifndef GRAPH_
#define GRAPH_


typedef struct GRAPH_NODE_ *pNode;

typedef struct edge_ {
    int weight;
    pNode endpoint;
    struct edge_ *next;
} Edge, *pEdge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pEdge edges;
    int distance;
    int visited;//Boolean value.
    struct GRAPH_NODE_ *next;
} Node, *pNode;

void build_graph_cmd(pNode *head);
void insert_node_cmd(pNode *head);
void delete_node_cmd(pNode *head);
void printGraph_cmd(pNode head); //for self debug
void deleteGraph_cmd(pNode* head);
int shortsPath_cmd(pNode head);
int TSP_cmd(pNode head);

void TSP_helper_cmd(pNode head, int *arr,int num, int curr,int *pmin);
void swap_place(int *arr, int index_1, int index_2);
pNode contains(pNode head, int node_to_serch);
void replace_address_in_all_edges(pNode node_to_insert, pNode node_to_replace, pNode head);
void delete_node(pNode *head, int node_to_remove);
void add_edges(pNode head, pNode node);
int shortest_path(pNode head, int source, int dest);
void reset_nodes_dis_and_vis(pNode head);
pNode get_the_min_not_visited(pNode head);


#endif
