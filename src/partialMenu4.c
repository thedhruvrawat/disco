#include <stdio.h>
#include <stdlib.h>

int** transitive_closure(int n,int** a)
{
    int **transitiveClosure;
    transitiveClosure= malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++)
    {
        transitiveClosure[i]=malloc(sizeof(int*)*n);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            transitiveClosure[i][j]=a[i][j];
        }
    }

    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                transitiveClosure[i][j]=transitiveClosure[i][j]|(transitiveClosure[i][k]&transitiveClosure[k][j]);
            }
        }
    }
    return transitiveClosure;
}

int checkTransitive(int n,int** a){
    int **transitiveClosure=malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++)
    {
        transitiveClosure[i]=malloc(sizeof(int*)*n);
    }
    transitiveClosure=transitive_closure(n,a);
    int flag=1;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(a[i][j]!=transitiveClosure[i][j])
            {
                flag=0;
                break;
            }
        }
    }
    return flag;
}



int* menu4_q2(int n, int** a)
{
    int flag=-1;
    int count=0;
    int *web;
    web=malloc(n*sizeof(int*));
    
    //printf("hello\n");
  for(int i=0;i<n;i++)
  {    count=0;
    //    printf("inside loop\n");
      for(int j=0;j<n;j++)
      {
          if(a[j][i]==1){
          count++;}
      }
      //printf("outside inner loop\n");
      if(count==n)
      {
          
      web[i]=flag;
      }
  }
  //printf("Loopdone\n");
  //printf("%d",web[1]);
  return web;
}


int* menu4_q3(int n,int** a )
{
   int flag=-1;
    int count=0;
    int *web;
    web=malloc(sizeof(int*)*n);
  for(int i=0;i<n;i++)
  {count=0;
        
      for(int j=0;j<n;j++)
      {
          if(a[i][j]==1)
          count++;
      }
      if(count==n)
      web[i]=flag;
  }
   return web; 
}

int* menu4_q4(int n,int** a)
{
    int flag=0;
    int *ans=malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++)
    {
        flag=0;
        if(a[i][i]==1)
        {
        for(int j=0;j<n;j++)
        {
            if(i!=j&&a[i][j]==1)
            {
                flag=1;
            }
            
            }
        }
        if(flag==0)
        ans[i]=-1;
    }
    return ans;
}
int* menu4_q5(int n,int** a)
{
    int flag=0;
    int *ans=malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++)
    {
        flag=0;
        if(a[i][i]==1)
        {
        for(int j=0;j<n;j++)
        {
            if(i!=j&&a[j][i]==1)
            {
                flag=1;
            }
            
            }
        }
        if(flag==0)
        ans[i]=-1;
    }
    return ans;
}

int* menu4_q6(int n,int k,int** a,int* indexOfWebsites)
{
    //This method returns the 1d array containing ones for the websites which are reachable for all the given websites, mentioned in the form of indices in the indexOfWebsites.
    int **transitiveClosure;
    transitiveClosure= malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++)
    {
        transitiveClosure[i]=malloc(sizeof(int*)*n);
    }
    transitiveClosure=transitive_closure(n,a);
    int *ans;
    ans=malloc(sizeof(int*)*n);
    
    for(int i=0;i<n;i++)
    {
        ans[i]=transitiveClosure[indexOfWebsites[0]][i];
    }
    
    for(int i=1;i<k;i++)
    {
       for(int j=0;j<n;j++)
       ans[j]=ans[j] & transitiveClosure[indexOfWebsites[i]][j];
    }

    return ans;
}

int* menu4_q7(int n,int k,int** a,int* indexOfWebsites)
{
    //This method returns the 1d array containing ones for the websites which are reachable for all the given websites, mentioned in the form of indices in the indexOfWebsites.
    int **transitiveClosure;
    transitiveClosure= malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++)
    {
        transitiveClosure[i]=malloc(sizeof(int*)*n);
    }
    transitiveClosure=transitive_closure(n,a);
    int *ans;
    ans=malloc(sizeof(int*)*n);
    
    for(int i=0;i<n;i++)
    {
        ans[i]=transitiveClosure[i][indexOfWebsites[0]];
    }
    
    for(int i=1;i<k;i++)
    {
       for(int j=0;j<n;j++)
       ans[j]=ans[j] & transitiveClosure[j][indexOfWebsites[i]];
    }

return ans;
}

// int main()
// {
//     printf("Hello, World!\n");
//     int n=2;
//     int x[2][2]={{1,1},{0,1}};
//     int *p1;
//     int *p2;
    
//     p1=menu4_q2(2,2,x);
//     p2=menu4_q3(2,2,x);
//     for(int i=0;i<2;i++)
//     {
        
//         printf("%d",p1[i]);
        
//     }
//     printf("\n");
    
//      for(int i=0;i<2;i++)
//     {
        
//         printf("%d",p2[i]);
        
//     }
//     printf("\n");
//     int **transitiveClosure=transitive_closure(2,2,x);
//     for(int i=0;i<n;i++)
//     {
//         for(int j=0;j<n;j++)
//         {
//             printf("%d",transitiveClosure[i][j]);
//         }
//         printf("\n");
//     }

//     return 0;
// }