#include <iostream>
using namespace std;
int c = 0;
int min(int x, int y, int z) { return min(min(x, y), z); }

int editDistDP(string str1, string str2, int m, int n) {
	int dp[m + 1][n + 1];
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {

			if (i == 0) {
				dp[i][j] = j;
				c++;
			} else if (j == 0) {
				dp[i][j] = i;
				c++;
			} else if (str1[i - 1] == str2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1];
				c = c + 6;
			} else {
				dp[i][j] = 1 + min(dp[i][j - 1],	  // Insert
								   dp[i - 1][j],	  // Remove
								   dp[i - 1][j - 1]); // Replace
				c = c + 10;
			}
			c = c + 4;
		}
		c = c + 4;
	}

	return dp[m][n];
}

int main() {

	string str1 = "";
	string str2 = "";
	cout << "Enter first string: ";
	cin >> str1;
	cout << "Enter second string: ";
	cin >> str2;

	cout << "Maximum no. of edit required : "
		 << editDistDP(str1, str2, str1.length(), str2.length()) << endl;
	cout << "No. of steps Required : " << c;
	return 0;
}