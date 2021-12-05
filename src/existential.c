#include <stdio.h>

int notExistsSymmetric(int n, int** matrix) { //If 0, means it is not impossible to return, i.e. a symmetric relation exists
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(matrix[i][j]==1 && matrix[j][i]==1)
                return 0;
        }
    }
    return 1;
}

int notExistsSymmetricWithoutReflexive(int n, int** matrix) { //If 0, means it is not impossible to return, i.e. a non-reflexive but symmetric relation exists
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(matrix[i][j]==1 && matrix[j][i]==1 && j!=i)
                return 0;
        }
    }
    return 1;
}

int existsReflexive(int n, int** matrix) {
	for (int i = 0; i < n; i++) {
		if (matrix[i][i] == 1) {
			return 1;
		}
	}
	return 0;
}
