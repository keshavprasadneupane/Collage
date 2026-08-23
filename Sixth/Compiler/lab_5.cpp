// WAP to implement first of a given grammar.
#include <cctype>
#include <iostream>
#include <set>
#include <string>
#include <vector>

std::set<char> computeFirst(char c,
							const std::vector<std::string> &productionSet) {
	std::set<char> result;

	if (!std::isupper(c)) {
		result.insert(c);
		return result;
	}

	for (const auto &prod : productionSet) {
		if (prod[0] == c) {
			if (prod.length() > 2 && prod[2] == '$') {
				result.insert('$');
			} else {
				size_t j = 2;
				while (j < prod.length()) {
					bool foundEpsilon = false;

					std::set<char> subResult =
						computeFirst(prod[j], productionSet);

					for (char subChar : subResult) {
						result.insert(subChar);
						if (subChar == '$') {
							foundEpsilon = true;
						}
					}

					if (!foundEpsilon) {
						break;
					}
					j++;
				}
			}
		}
	}
	return result;
}

int main() {
	int numOfProductions;

	std::cout << "How many number of productions? : ";
	if (!(std::cin >> numOfProductions) || numOfProductions <= 0) {
		std::cerr << "Invalid number of productions.\n";
		return 1;
	}

	std::vector<std::string> productionSet(numOfProductions);

	for (int i = 0; i < numOfProductions; ++i) {
		std::cout << "Enter production Number " << i + 1 << " : ";
		std::cin >> productionSet[i];
	}

	char choice;
	do {
		char c;
		std::cout << "\nFind the FIRST of : ";
		std::cin >> c;

		std::set<char> result = computeFirst(c, productionSet);

		std::cout << "\nFIRST(" << c << ") = { ";
		for (char symbol : result) {
			std::cout << symbol << " ";
		}
		std::cout << "}\n";

		std::cout << "Press 'y' to continue : ";
		std::cin >> choice;
	} while (choice == 'y' || choice == 'Y');

	return 0;
}