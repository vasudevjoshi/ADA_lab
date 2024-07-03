#include<stdio.h>
#include <stdlib.h>
#define MAX 100

int graph[MAX][MAX], visited[MAX], path[MAX], count = 0;
int stack[MAX], top = -1;
int c = 0;

void dfs(int n, int start)
{
    visited[start] = 1;
    path[start] = 1;
    for (int i = 0; i < n; i++)
    {
        if (graph[start][i])
        {
            if (visited[i] == 1 && path[i] == 1)
            {
                c = 1; // Cycle detected
                return;
            }
            if (visited[i] == 0)
                dfs(n, i);
        }
    }
    path[start] = 0;
    stack[++top] = start;
}

int main()
{
    int n;
    printf("Enter the number of vertices:\n");
    scanf("%d", &n);
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
        visited[i] = 0;
        path[i] = 0; // Initialize the path array
    }

    printf("Topological Order:\n");
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
            dfs(n, i);
    }
    if (c == 1)
    {
        printf("IT HAS A LOOP SO NO TOPOLOGICAL ORDER\n");
        return 0;
    }
    while (top != -1)
    {
        printf(" --> %c", stack[top--] + 65);
    }
    printf("\n");
    return 0;
}