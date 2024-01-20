#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 30

// Function to find the maximum of two integers
int max(int a, int b);
// Function to print all Longest Common Subsequences (LCS) between two strings
void printAllLCS(char X[], char Y[], int n, int m, int dp[][MAX_LENGTH], char result[], int index, int *counter, char uniqueResults[][MAX_LENGTH]);
// Function to find the Length of Longest Common Subsequence (LCS) between two strings
int LCS(char X[], char Y[], int n, int m);
// Function to print a matrix
void printMatrix(int matrix[][MAX_LENGTH], int row, int column);

int main() {
    char X[MAX_LENGTH], Y[MAX_LENGTH];
    printf("Sirasiyla iki adet string giriniz:\n");
    scanf("%s %s", X, Y);
    int n, m;
    n = strlen(X); // length of the string X
    m = strlen(Y); // length of the string Y

    int length = LCS(X, Y, n, m);
    return 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void printAllLCS(char X[], char Y[], int n, int m, int dp[][MAX_LENGTH], char result[], int index, int *counter, char uniqueResults[][MAX_LENGTH]) {
    if (n == 0 || m == 0) {
        // Check if the current result is unique before printing
        int found = 0, i = 0;
		while( i < *counter && !found) {
            if (strcmp(result, uniqueResults[i]) == 0) {
                found = 1;
            }
            i++;
        }
        
        if (!found) { // If the current result is unique
            strcpy(uniqueResults[(*counter)++], result); // Add it to the uniqueResults matrix
            printf("LCS: %s\n", result); // And print it
        }
        return;
    }

    if (X[n - 1] == Y[m - 1]) { 
        result[index - 1] = X[n - 1]; // store the matched charachter
        printAllLCS(X, Y, n - 1, m - 1, dp, result, index - 1, counter, uniqueResults);
    } else if (dp[n - 1][m] > dp[n][m - 1]) { // move dp[n - 1][m]
        printAllLCS(X, Y, n - 1, m, dp, result, index, counter, uniqueResults);
    } else if (dp[n - 1][m] < dp[n][m - 1]) { // move dp[n][m - 1]
        printAllLCS(X, Y, n, m - 1, dp, result, index, counter, uniqueResults);
    } else { // (dp[n - 1][m] == dp[n][m - 1])
		// If multiple choices are possible -> either can move dp[n - 1][m] OR dp[n][m - 1]
        printAllLCS(X, Y, n - 1, m, dp, result, index, counter, uniqueResults); // moving dp[n - 1][m]
        printAllLCS(X, Y, n, m - 1, dp, result, index, counter, uniqueResults); // moving dp[n][m - 1]
    }
}

int LCS(char X[], char Y[], int n, int m) {
    int dp[n + 1][MAX_LENGTH]; // DP - matrix
    int isChosen[n + 1][MAX_LENGTH]; // Matrix to store whether a character is chosen

    // base case --> for initialization of dp and isChosen matrices
    int i, j;
    for (i = 0; i <= n; i++) {
    	for (j = 0; j <= m; j++) {
    		dp[i][j] = 0;
    		isChosen[i][j] = 0;
		}
	}
    
    /* NORMALLY THAT INITIALIZATON WAS ENOUGH
    for (j = 0; j <= m; j++) { // initialize 0. row for dp and isChosen to 0
        dp[0][j] = 0;
        isChosen[0][j] = 0;
    }
    for (i = 0; i <= n; i++) { // initialize 0. column for dp and isChosen to 0
        dp[i][0] = 0;
        isChosen[i][0] = 0;
    }*/

	printf("\nDP matris ilk hali\n");
	printMatrix(dp, n, m);
	printf("Ek matris ilk hali\n");
	printMatrix(isChosen, n, m);
	
	
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (X[i - 1] == Y[j - 1]) { // if a charachter in two strings is machted  
                dp[i][j] = 1 + dp[i - 1][j - 1]; // current = previous diagonal + 1
                isChosen[i][j] = 1; // Mark as chosen
            } else { // if not machted
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]); // current = max(left, up)
                //isChosen[i][j] = 0; // Not chosen
            }
        }
        printf("\n%d.satir icin DP matrisi\n", i);
		printMatrix(dp, n, m);
		printf("%d.satir icin Ek matris\n", i);
		printMatrix(isChosen, n, m);
    }

    int length = dp[n][m]; // Length of LCS
    char result[length + 1]; // To store each LCS
    result[length] = '\0'; // Null character at the end of the result string

    char uniqueResults[MAX_LENGTH][MAX_LENGTH]; // To store unique LCS
    int counter = 0; // Counter to track the number of unique LCS found

    printf("\nEn uzun ifadenin boyutu: %d\n", length);
    printf("\nEn uzun ifade(ler):\n");
    printAllLCS(X, Y, n, m, dp, result, length, &counter, uniqueResults);

    return length;
}

void printMatrix(int matrix[][MAX_LENGTH], int row, int column) {
    int i, j;
    for (i = 0; i <= row; i++) {
        for (j = 0; j <= column; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
