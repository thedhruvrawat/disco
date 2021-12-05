#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int csv2array(char *fileName, char** websites, int** mat) {
    // The relation matrix and the websites set is passed by reference
    // The function returns the number of websites
    char buffer[1024] ;
    char *record, *line;
    int i=0, j=0;
    FILE *fstream = fopen(fileName,"r");
    if(fstream == NULL) {
        printf("\n file opening failed ");
        return 0;
    }
    int row_1 =1;
    while((record=fgets(buffer,sizeof(buffer),fstream))!=NULL) {
        char delim[] = ",";
        char *ptr = strtok(record, delim);
        int col_1 = 1;
        j=0;
        while(ptr != NULL) {
            if (!row_1 && !col_1) {
                mat[i][j] = (int)*ptr-'0';
            }
            else if(row_1==1) {
                int len = strlen(ptr);
                char* tmp = (char*) malloc((len+1)*sizeof(char));
                strcpy(tmp, ptr);
                websites[j] = tmp;
            }
            ptr = strtok(NULL, delim);
            j++;
            if(!row_1 && col_1==1)
                col_1=j=0;
        }
        i++;
        if (row_1==1)
            row_1=i=0;
    }
    int len = strlen(websites[i-1]);
    websites[i-1][len-2] = 0; // remove newline character from last string
    return i;
}

void array2csv(int n, char* S[n], int** mat, char* fileName) {
    FILE *fp1 = fopen(fileName,"w");
    if (fp1 == NULL) {
        printf("\n file opening failed ");
        return;
    }
    for (int i = 0; i<n; i++){
        fprintf(fp1, ",%s", S[i]);
    }
    fprintf(fp1, "\n");
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n; j++){
            if (j==0) fprintf(fp1, "%s,", S[i]);
            fprintf(fp1, "%d%s", mat[i][j], (j<n-1?",":""));
        }
        fprintf(fp1,"\n");
    }
    fclose(fp1);
}
