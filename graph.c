#include <stdio.h>
#include <limits.h>
#include "graph.h"
#include "nodes.h"
#include "edges.h"


void build_graph_cmd(pNode *head)
{
    char input = ' '; // Gets the user input char after char.
    pNode last_node = NULL; // Hold the last node we worked on.
    int node_index = 0; // Hold a specific node number to work on.
    int num_of_nodes = 0; // Hold the node's number for creating the new node.
    scanf("%d", &num_of_nodes); // Get from user input how much node to creat.
    int num_of_loops = num_of_nodes;
    pNode *arr = (pNode*)malloc(num_of_nodes * sizeof(pNode)); // Save all the nodes in arr to get to any node in O(1).
    last_node = new_node(--num_of_nodes); // Creat new node.
    arr[num_of_nodes] = last_node;// Add the new node to the array.
    while (num_of_nodes != 0) // Creat nodes as the user input number.
    {
        pNode temp = new_node(--num_of_nodes); // Creat a temporary node to add the linkedList.
        arr[num_of_nodes] = temp; // save the node in the right index.
        temp->next = last_node;
        last_node = temp;
    }

    pNode src_node = NULL; // The src node that we are adding edges from.
    pNode dest_node = NULL; // The dest node that we are adding edges to.
    int weight = 0; // Weight for the curr edge.
    pEdge curr_edge = NULL; // The new edge that we creat.

    for (int i = 0; i < num_of_loops; i++)
    {
        scanf("%c", &input);
        if (input == 'n')
        {
            scanf("%d", &node_index);
            src_node = arr[node_index];// Get the src node in O(1).
            while ((!feof(stdin)) && (scanf("%d", &node_index)))
            {
                dest_node = arr[node_index]; // Get the dest node.
                scanf("%d", &weight);
                curr_edge = new_edge(weight, dest_node);// Creat new edge.
                add_edge(src_node, curr_edge);
            }
        }

    }
    *head = (arr[0]);// Return the head of the new graph to &head.
    free(arr);
}

void insert_node_cmd(pNode *head)
{
    int node_to_serch = 0; // Hold the number of the node to insert.
    scanf("%d", &node_to_serch);
    pNode node_to_replace = NULL; // Hold the old node with the same number.
    pNode node_to_insert = new_node( node_to_serch ); // Creat the new node to insert.
    node_to_replace = contains(*head, node_to_serch);
    if( node_to_replace != NULL ) // If this node is already in the graph.
    {
        // Replace the old node address <-> new node address in all the edges.
        replace_address_in_all_edges(node_to_insert, node_to_replace, *head);
        delete_node(head, node_to_serch);// Delete the old node
    }
    add_edges(*head, node_to_insert);// Add the new edges to the new node.
    node_to_insert->next = (*head);
    (*head) = node_to_insert;
}

void add_edges(pNode head, pNode src)
{
    int node_num = 0; // Hold a specific node number to work on.
    pNode src_node = src; // The src node that we are adding edges from.
    pNode dest_node = NULL; // The dest node that we are adding edges to.
    int weight = 0; // Weight for the curr edge.
    pEdge curr_edge = NULL; // The new edge that we creat.
    while ( (!feof(stdin)) && (scanf("%d", &node_num)) )
    {
        dest_node = contains(head, node_num); // Get the dest node.
        scanf("%d", &weight);
        curr_edge = new_edge(weight, dest_node);// Creat new edge.
        add_edge(src_node, curr_edge);
    }
}

void delete_node_cmd(pNode *head)
{
    int node_num = 0;
    scanf("%d", &node_num);// Get from user the num of the node to delete.
    // Delete all the edges that get to the node.
    pNode curr_node = *head;
    pEdge curr_edge;
    pEdge prev_edge;
    while (curr_node != NULL)
    {
        curr_edge = curr_node->edges;
        if (curr_edge != NULL) {
            // Delete from start.
            if( (curr_edge->endpoint->node_num == node_num) && (curr_edge == curr_node->edges ) )
            {
                curr_node->edges = curr_edge->next;
                free_edge(curr_edge);
                goto finish_this_node;
            }
            // Delete from middle.
            while ( (curr_edge != NULL) && (curr_edge->endpoint->node_num != node_num) )
            {
                prev_edge = curr_edge;
                curr_edge = curr_edge->next;
            }
            if(curr_edge == NULL) { goto finish_this_node; }
            else
            {
                prev_edge->next = curr_edge->next;
                free_edge(curr_edge);
                goto finish_this_node;
            }
        }
        finish_this_node:
        curr_node = curr_node->next;
    }
    delete_node(head, node_num);
}

void printGraph_cmd(pNode head)
{
    if (head == NULL)
    {
        printf("The head is null!\n");
        return;
    }
    printf("\nPrint the graph:\n");
    pNode curr_node = head;
    pEdge curr_edge = head->edges;
    while (curr_node != NULL)
    {
        printf("Node number: %d --> ", curr_node->node_num);
        curr_edge = curr_node->edges;
        while (curr_edge != NULL)
        {
            printf(", (%d,%d)=%d", curr_node->node_num, curr_edge->endpoint->node_num, curr_edge->weight);
            curr_edge = curr_edge->next;
        }
        printf("\n");
        curr_node = curr_node->next;
    }

}

void deleteGraph_cmd(pNode* head)
{
    pNode prev;
    while (( *head) != NULL)
    {
        prev = (*head);
        (*head) = (*head)->next;
        node_free(prev);
    }
}

int shortsPath_cmd(pNode head)
{
    int input_node_1 = 0;// The first node num.
    int input_node_2 = 0;// The second node num.
    scanf("%d", &input_node_1);
    scanf("%d", &input_node_2);
    int ans = shortest_path(head, input_node_1, input_node_2);
    return ans;
}

int TSP_cmd(pNode head)
{
    int num_of_node = 0;
    scanf("%d", &num_of_node);
    int *arr = (int*)(malloc(sizeof(int)*num_of_node));// Array to hold the node num.
    int min = INT_MAX;
    int * pmin = &min;
    for(int i = 0 ; i < num_of_node; i++)
    {
        scanf("%d", &arr[i]);
    }
    for(int i = 0;i<num_of_node;i++)
    {
        swap_place(arr,0,i);
        TSP_helper_cmd(head,arr,num_of_node,0,pmin);
        swap_place(arr,i,0);
    }
    free(arr);
    if (min == INT_MAX) {return  -1;} // If there is no path.
    return min;
}

void TSP_helper_cmd(pNode head, int *arr,int num_of_nodes, int curr,int *pmin)
{
    if(num_of_nodes == 2)
    {
        int finshdist = shortest_path(head,arr[0],arr[1]);
        if(finshdist != -1)
        {
            if( (curr + finshdist) < *pmin )
            {
                *pmin = (curr+finshdist);
            }
        }
        return;
    }
    for(int i = 1 ; i < num_of_nodes; i++)
    {
        swap_place(arr,1,i);
        int dist = shortest_path(head,arr[0],arr[1]);
        if(dist == -1)
        {
            return;
        }
        TSP_helper_cmd(head,arr+1,num_of_nodes-1,curr+dist, pmin);
        swap_place(arr,i,1);
    }
}

void swap_place(int *arr, int index_1, int index_2)
{
    int temp = arr[index_1];
    arr[index_1] = arr[index_2];
    arr[index_2] = temp;
}

pNode contains(pNode head, int node_to_serch)
{
    pNode curr_1 = head;
    while (curr_1 != NULL)
    {
        if(curr_1->node_num == node_to_serch)
        {
            return curr_1;
        }
        curr_1 = curr_1->next;
    }
    return NULL;
}

void replace_address_in_all_edges(pNode node_to_insert, pNode node_to_replace, pNode head)
{
    pNode curr_node = head;
    pEdge curr_edge;
    while (curr_node != NULL)
    {
        curr_edge = curr_node->edges;
        while (curr_edge != NULL)
        {
            if( curr_edge->endpoint == node_to_replace )
            {
                curr_edge->endpoint = node_to_insert;
                break;
            }
            curr_edge = curr_edge->next;
        }
        curr_node = curr_node->next;
    }
}

void delete_node(pNode *head, int node_to_remove) {
    pNode curr = *head;
    pNode prev;

    if (curr != NULL)
    {
        // Delete from start.
        if ((curr->node_num == node_to_remove) && (curr == *head)) {
            *head = curr->next;
            node_free(curr);
            return;
        }
        // Delete from middle.
        while ((curr != NULL) && (curr->node_num != node_to_remove)) {
            prev = curr;
            curr = curr->next;
        }
        if (curr == NULL) { return; }
        else {
            prev->next = curr->next;
            node_free(curr);
        }
    }
}

int shortest_path(pNode head, int src, int des) {
    pNode source = contains(head, src);
    pNode dest = contains(head, des);
    if( (source == NULL) || (dest == NULL)) { return -1;}
    // Set the distance of the source node to 0
    reset_nodes_dis_and_vis(head);
    source->distance = 0;
    pNode curr_node = source;
    pEdge curr_edge;
    int curr_dist;
    while (curr_node != NULL) {
        curr_node->visited = 1;
        curr_edge = curr_node->edges;
        // For each edge in the linked list of edges
        while (curr_edge != NULL) {
            // Get the destination node
            curr_dist = curr_node->distance + curr_edge->weight;
            // Relax the edge
            if ( (curr_edge->endpoint->visited != 1) && (curr_edge->endpoint->distance > curr_dist))
            {
                curr_edge->endpoint->distance = curr_dist;
            }
            curr_edge = curr_edge->next;
        }
        curr_node = get_the_min_not_visited(head);
    }
    if (dest->distance < INT_MAX) { return dest->distance; }

    // If the destination node is unreachable
    return -1;
}

// Reset all the distance and visited values in all the graph.
void reset_nodes_dis_and_vis(pNode head)
{
    pNode curr = head;
    while(curr!=NULL)
    {
        curr->visited = 0;
        curr->distance = INT_MAX;
        curr = curr->next;
    }
}

pNode get_the_min_not_visited(pNode head)
{
    pNode curr_min = NULL;
    pNode curr = head;
    int min_distance = INT_MAX;
    while (curr != NULL)
    {
        if( (curr->visited == 0) && (curr->distance < min_distance) )
        {
            curr_min = curr;
            min_distance = curr->distance;
        }
        curr = curr->next;
    }
    return curr_min;
}


