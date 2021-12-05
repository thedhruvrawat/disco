#include <stdio.h>

int checkSymmetric(int n, int** matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(matrix[i][j]!=matrix[j][i] && (matrix[i][j]==1 || matrix[j][i]==1))
                return 0;
        }
    }
    return 1;
}

int checkAntiSymmetric(int n, int** matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(matrix[i][j]==1 && matrix[j][i]==1 && i!=j)
                return 0;
        }
    }
    return 1;
}

int checkReflexive(int n, int **matrix) {
	for (int i = 0; i < n; i++) {
		if (matrix[i][i] != 1) {
			return 0;
		}
	}
	return 1;
}

// int checkAntiSymmetricWithoutReflexive(int n, int** matrix) {
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             if(matrix[i][j]==1 && matrix[j][i]==1 && i!=j)
//                 return 0;
//             else if (matrix[i][j]==1 && i==j)
//                 return 0;
//         }
//     }
//     return 1;
// }

// int main() {
//     int mat[3][3] = { { 0, 1, 1 },
//                       { 1, 0, 1 },
//                       { 1, 1, 0 } };
//     if (checkSymmetric(3, mat)) printf("Yes, symmetric\n");
//     else printf("No, not symmetric\n");
//     if (checkAntiSymmetric(3, mat)) printf("Yes, anti-symmetric\n");
//     else printf("No, not anti-symmetric\n");
//     if (checkAntiSymmetricWithoutReflexive(3, mat)) printf("Yes, anti-symmetric w/o reflexive\n");
//     else printf("No, not anti-symmetric w/o reflexive\n");
//     return 0;
// }
