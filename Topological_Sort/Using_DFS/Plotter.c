 #include <stdio.h>
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
        count++;
        if (graph[start][i] && visited[i] == 1 && path[i] == 1)
            c = 1;
        if (graph[start][i] && visited[i] == 0)
            dfs(n, i);
    }
    path[start] = 0;
    stack[++top] = start;
}

void ploter(int k)
{
    FILE *f1 = fopen("bestcase.txt", "a");
    FILE *f2 = fopen("worstcase.txt", "a");
    if (!f1 || !f2)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int v = 1; v <= 10; v++)
    {
        int **arr = (int **)malloc(v * sizeof(int *));
        for (int i = 0; i < v; i++)
            arr[i] = (int *)malloc(v * sizeof(int));

        // Initialize the visited array
        for (int i = 0; i < MAX; i++)
        {
            visited[i] = 0;
            path[i] = 0;
        }

        if (k == 0)
        {
            for (int i = 0; i < v; i++)
            {
                for (int j = 0; j < v; j++)
                {
                    arr[i][j] = 0;
                }
            }
            for (int i = 0; i < v - 1; i++)
            {
                arr[i][i + 1] = 1;
            }
        }

        if (k == 1)
        {
            for (int i = 0; i < v; i++)
            {
                for (int j = 0; j < v; j++)
                {
                    if (i != j)
                    {
                        arr[i][j] = 1;
                    }
                    else
                    {
                        arr[i][j] = 0;
                    }
                }
            }
        }

        count = 0;
        for (int i = 0; i < v; i++)
        {
            if (visited[i] == 0)
                dfs(v, i);
        }

        if (k == 0)
            fprintf(f1, "%d\t%d\n", v, count);
        else
            fprintf(f2, "%d\t%d\n", v, count);

        for (int i = 0; i < v; i++)
            free(arr[i]);
        free(arr);
    }

    fclose(f1);
    fclose(f2);
}

int main()
{
    for (int i = 0; i < 2; i++)
        ploter(i);
    return 0;
}