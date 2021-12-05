#include <stdio.h>

//Two websites are given

//**************STACK****************
// int MAXSIZE = 5;  //This should be order of matrix

// int MATRIX[5][5] = {
//     {0,1,0,1,1},
//     {0,0,1,0,1},
//     {0,1,0,1,1},
//     {1,0,1,0,1},
//     {1,1,1,1,1}
// };

int top = -1;

int isempty() {
   if(top == -1) return 1;
   else return 0;
}

int isfull(int MAXSIZE) {
   if(top == MAXSIZE) return 1;
   else return 0;
}


int pop(int MAXSIZE, int* stack) {
   int data;
   if(!isempty()) {
      data = stack[top];
      top = top - 1;
      return data;
   } else {
      printf("Empty Stack!\n");
   }
}

int push(int data, int MAXSIZE, int* stack) {
   if(!isfull(MAXSIZE)) {
      top = top + 1;
      stack[top] = data;
   } else {
      printf("Full stack!\n");
   }
}
//*****************END STACK***************



int menu5a(int MAXSIZE, int** MATRIX, char** S) {
    int* arr = malloc(MAXSIZE*sizeof(int));
    for (int i=0; i<MAXSIZE; i++) arr[i]=0;
    int* stack = malloc(MAXSIZE*sizeof(int));
    int k, l;
    printf("Input the indices of the website A and B (follow 0 indexing): ");
    scanf("%d", &k);
    scanf("%d", &l);
    int ctr = 0; // stores no of sites both A and B can reach
    for (int i = 0; i < MAXSIZE; i++) {
        if (MATRIX[k][i] == 1 && MATRIX[l][i] == 1) {
            arr[i] = 1;
            ctr++;
        }
    }
    for (int i = 0; i < MAXSIZE; i++) {
        if(arr[i]==1) {
            int flag = 0;
            for (int j = 0; j < MAXSIZE; j++) {
                if(MATRIX[i][j]==1 && arr[j]==1) {
                        flag+=1;
                }
            }
            if (flag == ctr)
                push(i, MAXSIZE, stack);
        }
    }

    printf("\nSites reachable by both A and B as well those which can reach all websites A and B can reach: ");
    // print stack data
    while (!isempty()) {
        int data = pop(MAXSIZE, stack);
        printf("%s ", S[data]);
    }
    printf("\n");

    return 0;
}

int menu5b(int MAXSIZE, int** MATRIX, char** S) {
    int* arr = malloc(MAXSIZE*sizeof(int));
    for (int i=0; i<MAXSIZE; i++) arr[i]=0;
    int* stack = malloc(MAXSIZE*sizeof(int));
    int k, l;
    printf("Input the indices of the website A and B (follow 0 indexing): ");
    scanf("%d", &k);
    scanf("%d", &l);
    int ctr = 0; // stores no of sites which can reach both A and B
    for (int i = 0; i < MAXSIZE; i++) {
        if (MATRIX[i][k] == 1 && MATRIX[i][l] == 1) {
            arr[i] = 1;
            ctr++;
        }
    }

    for (int i = 0; i < MAXSIZE; i++) {
        if(arr[i]==1) {
            int flag = 0;
            for (int j = 0; j < MAXSIZE; j++) {
                if(MATRIX[j][i]==1 && arr[j]==1) {
                        flag+=1;
                }
            }
            if (flag == ctr)
                push(i, MAXSIZE, stack);
        }
    }

    // printf("Sites which can reach both A and B: ");
    // for (int i = 0; i < MAXSIZE; i++) {
    //     if (arr[i])
    //         printf("%d ", i);
    // }

    printf("\nSites which can reach both A and B and reachable from all sites which can reach A and B: ");
    // print stack data
    while (!isempty()) {
        int data = pop(MAXSIZE, stack);
        printf("%s ", S[data]);
    }
    printf("\n");

    return 0;
}

// int main() {
//     menu5a();
//     // menu5b();
//     return 0;
// }
