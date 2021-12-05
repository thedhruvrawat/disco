#include <stdio.h>
#include <stdlib.h>

int** symmetricClosure(int n,int** a)
{
    int **symmetricClosure;
    symmetricClosure= malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++)
    {
        symmetricClosure[i]=malloc(sizeof(int*)*n);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            symmetricClosure[i][j]=a[i][j];
        }
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(symmetricClosure[i][j]==1) symmetricClosure[j][i]=1;
        }
    }
    return symmetricClosure;
}

int** reflexiveClosure(int n,int** a)
{
    int **reflexiveClosure;
    reflexiveClosure= malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++)
    {
        reflexiveClosure[i]=malloc(sizeof(int*)*n);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            reflexiveClosure[i][j]=a[i][j];
        }
    }
    for(int i=0;i<n;i++)
    {
        reflexiveClosure[i][i] = 1;
    }
    return reflexiveClosure;
}