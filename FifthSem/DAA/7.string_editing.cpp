#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int c = 0;

int min3(int a, int b, int c) {
    return min(min(a, b), c);
}

int editDistance(string str1, string str2) {

    int m = str1.length();
    int n = str2.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    vector<vector<string>> arrow(m + 1, vector<string>(n + 1));

    c = 0;

    // BUILD DP TABLE
    for (int i = 0; i <= m; i++) {

        for (int j = 0; j <= n; j++) {

            // First row
            if (i == 0) {

                dp[i][j] = j;

                if (j == 0)
                    arrow[i][j] = "•";
                else
                    arrow[i][j] = "←";

                c++;
            }

            // First column
            else if (j == 0) {

                dp[i][j] = i;
                arrow[i][j] = "↑";

                c++;
            }

            // Characters match
            else if (str1[i - 1] == str2[j - 1]) {

                dp[i][j] = dp[i - 1][j - 1];
                arrow[i][j] = "↖";

                c += 6;
            }

            // Characters different
            else {

                int insertCost  = dp[i][j - 1];
                int deleteCost  = dp[i - 1][j];
                int replaceCost = dp[i - 1][j - 1];

                dp[i][j] = 1 + min3(insertCost,
                                    deleteCost,
                                    replaceCost);

                // Determine direction
                if (dp[i][j] == replaceCost + 1)
                    arrow[i][j] = "↖";

                else if (dp[i][j] == deleteCost + 1)
                    arrow[i][j] = "↑";

                else
                    arrow[i][j] = "←";

                c += 10;
            }

            c += 4;
        }

        c += 4;
    }

    // PRINT TABLE
    cout << "\nEdit Distance Table:\n\n";

    cout << setw(6) << " ";

    for (int j = 0; j < n; j++) {
        cout << setw(6) << str2[j];
    }

    cout << endl;

    for (int i = 0; i <= m; i++) {

        if (i == 0)
            cout << setw(3) << " ";
        else
            cout << setw(3) << str1[i - 1];

        for (int j = 0; j <= n; j++) {

            cout << setw(3) << dp[i][j]
                 << arrow[i][j];
        }

        cout << endl;
    }

    // BACKTRACK OPTIMAL PATH
    cout << "\nOptimal Path:\n\n";

    int i = m;
    int j = n;

    while (i > 0 || j > 0) {

        cout << "(" << i << "," << j << ") ";

        if (arrow[i][j] == "↖") {

            if (str1[i - 1] == str2[j - 1]) {

                cout << "↖  Match : "
                     << str1[i - 1];
            }
            else {

                cout << "↖  Replace : "
                     << str1[i - 1]
                     << " -> "
                     << str2[j - 1];
            }

            i--;
            j--;
        }

        else if (arrow[i][j] == "↑") {

            cout << "↑  Delete : "
                 << str1[i - 1];

            i--;
        }

        else {

            cout << "←  Insert : "
                 << str2[j - 1];

            j--;
        }

        cout << endl;
    }

    cout << "(0,0) Start\n";

    return dp[m][n];
}

int main() {

    string str1, str2;

    cout << "Enter first string  : ";
    cin >> str1;

    cout << "Enter second string : ";
    cin >> str2;

    int ans = editDistance(str1, str2);

    cout << "\nMinimum Edit Distance = "
         << ans << endl;

    cout << "Approximate Step Count = "
         << c << endl;

    return 0;
}