// C-Program to Calculate Follow(A)
#include <cctype>
#include <iostream>
#include <set>
#include <string>
#include <vector>

std::set<char> computeFirst(char c,
							const std::vector<std::string> &productions);
std::set<char> computeFollow(char c,
							 const std::vector<std::string> &productions);

std::set<char> computeFirst(char c,
							const std::vector<std::string> &productions) {
	std::set<char> result;

	if (!std::isupper(c) && c != '#') {
		result.insert(c);
		return result;
	}

	for (const auto &prod : productions) {
		if (prod[0] == c) {
			if (prod.length() > 2 && prod[2] == '#') {
				result.insert('#');
			} else if (prod.length() > 2 && !std::isupper(prod[2])) {
				result.insert(prod[2]);
			} else if (prod.length() > 2) {
				std::set<char> subFirst = computeFirst(prod[2], productions);
				result.insert(subFirst.begin(), subFirst.end());
			}
		}
	}
	return result;
}

std::set<char> computeFollow(char c,
							 const std::vector<std::string> &productions) {
	std::set<char> result;

	if (!productions.empty() && productions[0][0] == c) {
		result.insert('$');
	}

	for (const auto &prod : productions) {
		for (size_t j = 2; j < prod.length(); ++j) {
			if (prod[j] == c) {
				if (j + 1 < prod.length()) {
					std::set<char> firstSet =
						computeFirst(prod[j + 1], productions);

					for (char sym : firstSet) {
						if (sym != '#') {
							result.insert(sym);
						}
					}

					if (firstSet.count('#') && c != prod[0]) {
						std::set<char> followLHS =
							computeFollow(prod[0], productions);
						result.insert(followLHS.begin(), followLHS.end());
					}
				} else if (j + 1 == prod.length() && c != prod[0]) {
					std::set<char> followLHS =
						computeFollow(prod[0], productions);
					result.insert(followLHS.begin(), followLHS.end());
				}
			}
		}
	}
	return result;
}

int main() {
	int n;
	std::cout << "Enter the no. of productions: ";
	if (!(std::cin >> n) || n <= 0)
		return 0;

	std::cout << " Enter " << n
			  << " productions\n Production with multiple terms should be "
				 "given as separate productions\n";
	std::vector<std::string> productions(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> productions[i];
	}

	int choice;
	do {
		char c;
		std::cout << "Find FOLLOW of --> ";
		std::cin >> c;

		std::set<char> result = computeFollow(c, productions);

		std::cout << "FOLLOW(" << c << ") = { ";
		for (char symbol : result) {
			std::cout << symbol << " ";
		}
		std::cout << "}\n";

		std::cout << "Do you want to continue(Press 1 to continue....)? ";
		std::cin >> choice;
	} while (choice == 1);

	return 0;
}