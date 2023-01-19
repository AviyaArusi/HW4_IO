#include <stdio.h>
#include "graph.h"


#define END_OF_PROGRAM 0


int main(){

    char user_decision = ' ';
    int answer = 0;
    pNode last_graph = NULL;
    while ( !feof(stdin) )
    {
        user_decision = getchar();
        switch (user_decision)
        {
            case 'A':
                if (last_graph != NULL)
                {
                    deleteGraph_cmd(&last_graph);
                }
                build_graph_cmd(&last_graph);
                break;

            case 'B':
                insert_node_cmd(&last_graph);
                break;

            case 'D':
                delete_node_cmd(&last_graph);
                break;

            case 'S':
                answer = shortsPath_cmd(last_graph);
                printf("Dijsktra shortest path: %d \n", answer);
                break;

            case 'T':
                answer= TSP_cmd(last_graph);
                printf("TSP shortest path: %d \n", answer);
                break;
        }
    }

    if (last_graph != NULL)
    {
        deleteGraph_cmd(&last_graph);
    }

    return END_OF_PROGRAM;
}