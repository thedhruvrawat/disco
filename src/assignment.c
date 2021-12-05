#include<stdio.h>
#include<string.h>
#include<unistd.h>

#include "csv2array.c"
#include "universal.c"
#include "existential.c"
#include "menu5.c"
#include "partialMenu4.c"
#include "menu2.c"

char* S[100]; // Set of all websites
int **matrix;
int n; //number of websites

int** create2dArray(int n) {  // utility function to create a 2d array
    int **matrix;
    matrix = malloc(n*sizeof (int*));
    for(int i=0; i<n; i++) {
        int* m1 = malloc(n*(sizeof(int)));
        matrix[i] = m1;
    }
    return matrix;
}

void plot(char * fname){ // code taken from visualiser.c
    int pid;
    if((pid = fork())==0){
        if(execlp("python", "python","visualise.py",fname,(char*)NULL)==-1){
        	execlp("python3", "python3","visualise.py",fname,(char*)NULL);
        };
    }
}

int checkPoset() {
    if (checkReflexive(n, matrix) && checkAntiSymmetric(n, matrix) && checkTransitive(n, matrix)) {
        return 1;
    }
    return 0;
}

int checkEquivalenceRelation() {
    if (checkReflexive(n, matrix) && checkSymmetric(n, matrix) && checkTransitive(n, matrix)) {
        return 1;
    }
    return 0;
}

void equivalenceClass() { // prints the various equivalence classes separately
    int website_counted[n];
    for (int i=0; i<n; i++) {
        website_counted[i]=0; // 0 indicates the website hasn't been put in any class
    }
    int piece = 1;
    for (int i=0; i<n; i++) {
        if (website_counted[i]==1)
            continue;
        printf("Piece %d: %s", piece, S[i]);
        website_counted[i] = 1;
        for (int j=i+1; j<n; j++) {
            if (website_counted[j]==1)
                continue;
            if (matrix[i][j]==1) {
                printf(", %s", S[j]);
                website_counted[j]=1;
            }
        }
        printf("\n");
        piece++;
    }
}

int** hasseMatrix() { // generates a hasse matrix to be used for plotting hasse diagram later on
    int** redundant = create2dArray(n);
    int** hasse = create2dArray(n);
    for (int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            redundant[i][j] = 0;
            hasse[i][j] = 0;
        }
    }
    for(int i1=0; i1<n; i1++) {  // first element in the matrix
        for(int j1=0; j1<n;j1++) {
            if (matrix[i1][j1] == 0)
                continue;
            if (i1==j1) {
                redundant[i1][j1]=1;
                continue;
            }
            for(int i2=0; i2<n; i2++) { // second element in the matrix
                for(int j2=0; j2<n;j2++) {
                    if (!(i2==j2) && matrix[i2][j2]==1 && j1==i2) {
                        redundant[i1][j2] = 1;
                    }
                }
            }
        }
    }
    for(int i=0; i<n; i++) { // remove tranisitive and reflexive elements
        for(int j=0; j<n; j++) {
            hasse[i][j] = matrix[i][j]-redundant[i][j];
        }
    }
    return hasse;
}

void plotHasse() {
    int** hasse = hasseMatrix();
    char* fileName = "hasse.csv";
    array2csv(n, S, hasse, fileName);
    printf("%s", fileName);
    plot(fileName);
}

void plotReflexiveClosure() {
    int** reflexive = reflexiveClosure(n, matrix);
    char* fileName = "closure.csv";
    array2csv(n, S, reflexive, fileName);
    printf("%s", fileName);
    plot(fileName);
}

void plotSymmetricClosure() {
    int** symmetric = symmetricClosure(n, matrix);
    char* fileName = "closure.csv";
    array2csv(n, S, symmetric, fileName);
    printf("%s", fileName);
    plot(fileName);
}

void plotTransitiveClosure() {
    int** transitive = transitive_closure(n, matrix);
    char* fileName = "closure.csv";
    array2csv(n, S, transitive, fileName);
    printf("%s", fileName);
    plot(fileName);
}

int* getLevel(int** hasse) { // we find the level of every node in the hasse diagram to be used later on while finding lub and glb
    // a higher level for a node indicates
    // higher position in the hasse diagram
    int elements = n;
    int* level = malloc(n*sizeof(int));
    for (int i=0; i<n; i++) level[i] = 0;
    int l=1;
    for (int i=0; i<n; i++) { // minimal element
        for (int j=0; j<n; j++) {
            if (hasse[j][i]==1)
                break;
            if (j==n-1) {
                level[i] = l;
                elements--;
            }
        }
    }
    while(elements) {
        l++;
        for (int i=0; i<n; i++) {
            if (level[i]!=l-1) continue;
            for (int j=0; j<n; j++) {
                if(hasse[i][j]==1) {
                    if (level[j]==0) elements--;
                    level[j] = l>level[j]?l:level[j];
                }
            }
        }
    }
    return level;
}

int lub_index(int a, int b, int* level) { // return the index of lub between two elements a and b if it exists else -1
    int lub=-1;
    for (int i=0; i<n; i++) {
        if (matrix[a][i]==1 && matrix[b][i]==1) {
            if (lub==-1) lub = i;
            else lub = level[lub]<level[i]?lub:i;
        }
    }
    if (lub==-1) return lub;
    // check if only one lub else return -1
    for (int i=0; i<n; i++) {
        if (i==lub) continue;
        if (matrix[a][i]==1 && matrix[b][i]==1)
            if (level[lub]==level[i]) return -1;
    }
    return lub;
}

int glb_index(int a, int b, int* level) { // return the index of glb between two elements a and b if it exists else -1
    int glb=-1;
    for (int i=0; i<n; i++) {
        if (matrix[i][a]==1 && matrix[i][b]==1) {
            if (glb==-1) glb = i;
            else glb = level[glb]>level[i]?glb:i;
        }
    }
    if (glb==-1) return glb;
    // check if only one glb else return -1
    for (int i=0; i<n; i++) {
        if (i==glb) continue;
        if (matrix[i][a]==1 && matrix[i][b]==1)
            if (level[glb]==level[i]) return -1;
    }
    return glb;
}

int checkLattice() {
    int** hasse = hasseMatrix();
    int* level = getLevel(hasse);
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            int glb=0, lub=0;
            // check for greatest lower bound (or meet a^b)
            glb = glb_index(i, j, level);
            if (glb==-1) return 0;
            // check for lowest upper bound (or join a&b)
            lub = lub_index(i, j, level);
            if (lub==-1) return 0;
        }
    }
    return 1;
}

int checkDistributiveLattice() {
    int** hasse = hasseMatrix();
    int* level = getLevel(hasse);
    for (int x=0; x<n; x++) {
        for (int y=0; y<n; y++) {
            for (int z=0; z<n; z++) {
                int join1, join2, meet1, meet2, meet3;
                join1 = lub_index(y, z, level); // y V z
                meet1 = glb_index(x, join1, level); // x ^ (y V z)
                meet2 = glb_index(x, y, level); // x ^ y
                meet3 = glb_index(x, z, level); // x ^ z
                join2 = lub_index(meet2, meet3, level); // (x ^ y) V (x ^ z)
                if (join2!=meet1) return 0;
            }
        }
        // the second condition required for finding lattice distributive is the dual of the above
    }
    return 1;
}

void menu2(int n) {
    printf("\nMenu 2\n");
    printf("Do you want to visualise how the network will look if we add minimum links to satisfy the property? (If yes, display the graph, else return back to Main Menu)\n");
    char option_chose[4];
    printf("Please answer yes or no: ");
    scanf("%s", option_chose);
    printf("%s\n", option_chose);
    if (!strcmp(option_chose, "yes")) {
        if(n==0) { // Work in progress
            printf("Equivalence classes plotted\n");
            plotSymmetricClosure();
        } else if(n==1) {
            printf("Reflexive closure plotted\n");
            plotReflexiveClosure();
        } else if(n==2) {
            printf("Symmetric closure plotted\n");
            plotSymmetricClosure();
        } else if(n==3) {
            printf("Transitive closure plotted\n");
            plotTransitiveClosure();
        }
    }
}

void menu3() {
    printf("\nMenu 3\n");
    printf("Do you want to know the nodes in each piece? (List all the pieces and their corresponding websites else return to Main Menu)\n");
    char option_chose[4];
    printf("Please answer yes or no: ");
    scanf("%s", option_chose);
    if (!strcmp(option_chose, "yes")) {
        equivalenceClass();
    }
}

void menu5(); // declared menu 5 earlier since need to be called in menu 4

void printArrayMenu4(int* array) { // utility function for printing output given by some functions in menu4
    for (int i=0; i<n; i++) {
        if (array[i]==-1 || array[i]==1)
            printf("%s ", S[i]);
    }
    printf("\n");
}

void menu4() {
    printf("\nMenu 4\n");
    printf("1. Display the hasse diagram.\n");
    printf("2. Display the website whose link available in every website.\n");
    printf("3. Display the website which has links of every website.\n");
    printf("4. Display the websites that do not have links to any other website except itself.\n");
    printf("5. Display the websites which can't be reached from any other website except itself.\n");
    printf("6. Given some websites, display the websites which are reachable from all of them. (Take some input from user and display result)\n");
    printf("7. Given some websites, display the websites from which you can reach all those websites. (Process similar to 5)\n");
    printf("8. Is this relation an example of lattice?\n");
    printf("9. Return to Main Menu\n");
    int option_chose;
    printf("Please chose your option: ");
    scanf("%d", &option_chose);
    if (option_chose==1) {
        plotHasse();
    }
    else if (option_chose==2) {
        int* array = menu4_q2(n, matrix);
        printArrayMenu4(array);
    }
    else if (option_chose==3) {
        int* array = menu4_q3(n, matrix);
        printArrayMenu4(array);
    }
    else if (option_chose==4) {
        int* array = menu4_q4(n, matrix);
        printArrayMenu4(array);
    }
    else if (option_chose==5) {
        int* array = menu4_q5(n, matrix);
        printArrayMenu4(array);
    }
    else if (option_chose==6) {
        printf("Input the number of websites you are going to input: ");
        int k;
        scanf("%d", &k);
        printf("Input the indices of the website for choosing it (follow 0 indexing): ");
        int* index_of_websites = malloc(k*sizeof(int));
        for(int i=0; i<k; i++)
            scanf("%d", &index_of_websites[i]);
        int* array = menu4_q6(n, k, matrix, index_of_websites);
        printArrayMenu4(array);
    }
    else if (option_chose==7) {
        printf("Input the number of websites you are going to input: ");
        int k;
        scanf("%d", &k);
        printf("Input the indices of the website for choosing it (follow 0 indexing): ");
        int* index_of_websites = malloc(k*sizeof(int));
        for(int i=0; i<k; i++)
            scanf("%d", &index_of_websites[i]);
        int* array = menu4_q7(n, k, matrix, index_of_websites);
        printArrayMenu4(array);
    }
    else if (option_chose==8) {
        if (checkLattice()) {
            printf("Yes\n");
            menu5();
        }
        else {
            printf("No\n");
        }
    }
}

void menu5() {
    printf("\nMenu 5\n");
    printf("1. Given two websites A and B, display the website which is reachable by both A and B and can also reach to all such websites that both A and B can reach.\n");
    printf("2. Given two websites A and B, display the website which can reach to both A and B and is also reachable from all such websites which can reach to both A and B.\n");
    printf("3. Is the lattice distributive?\n");
    printf("4. Return to Menu 4\n");
    int option_chose;
    printf("Please chose your option: ");
    scanf("%d", &option_chose);
    if (option_chose==1) {
        menu5a(n, matrix, S);
    }
    if (option_chose==2) {
        menu5b(n, matrix, S);
    }
    if (option_chose==3) {
        if (checkDistributiveLattice()) {
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }
    if (option_chose==4) {
        menu4();
    }
}

void main() {
    char input_file_name[50];
    printf("Please enter a file name with .csv mentioned: ");
    scanf("%s", input_file_name);
    matrix = create2dArray(100);
    n = csv2array(input_file_name, S, matrix);
    while (1) {
        printf("\nMain Menu\n");
        printf("1. Does every website link to itself?\n");
        printf("2. Is it possible to always return back to the previous website from the current website in one step?\n");
        printf("3. Does every website has all the links to the websites which are reachable from it?\n");
        printf("4. Does there exist any website that contains a link to itself?\n");
        printf("5. Is it impossible to return to the previous website from the current website in one step?\n");
        printf("6. Is it impossible to return to the previous website from the current website in one step(excluding the cases where the current website is same)?\n");
        printf("7. Is it possible to divide the network into multiple pieces such that every website in a piece is reachable from every other website in that piece?\n");
        printf("8. Is this relation an example of Poset?\n");
        printf("9. Exit\n");
        int option_chose;
        printf("Please chose your option: ");
        scanf("%d", &option_chose);
        if (option_chose==1) {
            if (checkReflexive(n, matrix)) {
                printf("Yes\n");
            }
            else {
                printf("No\n");
                menu2(1);
            }
        }
        else if (option_chose==2) {
            if (checkSymmetric(n, matrix)) {
                printf("Yes\n");
            }
            else {
                printf("No\n");
                menu2(2);
            }
        }
        else if (option_chose==3) {
            if (checkTransitive(n, matrix)) {
                printf("Yes\n");
            }
            else {
                printf("No\n");
                menu2(3);
            }
        }
        else if (option_chose==4) {
            if (existsReflexive(n, matrix)) {
                printf("Yes\n");
            }
            else {
                printf("No\n");
            }
        }
        else if (option_chose==5) {
            if (notExistsSymmetric(n, matrix)) {
                printf("Yes\n");
            }
            else printf("No\n");
        }
        else if (option_chose==6) {
            if (notExistsSymmetricWithoutReflexive(n, matrix)) {
                printf("Yes\n");
            }
            else printf("No\n");
        }
        // Is partition of set such that all elements in it are related, possible?
        else if (option_chose==7) {
            if (checkEquivalenceRelation()) {
                printf("Yes\n");
                menu3();
            }
            else {
                printf("No\n");
                menu2(0);
            }
        }
        // Is it checkPoset
        else if (option_chose==8) {
            if (checkPoset()) {
                printf("Yes\n");
                menu4();
            }
            else
                printf("No\n");
        }
        // Exit the program
        else if (option_chose==9) {break;}
    }
}
