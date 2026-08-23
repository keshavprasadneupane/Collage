// Write a C program for constructing of LL (1) parsing
#include <iostream>
#include <string>
#include <vector>

int getNTIndex(char c) {
	switch (c) {
	case 'e':
		return 0; // E
	case 'b':
		return 1; // E'
	case 't':
		return 2; // T
	case 'c':
		return 3; // T'
	case 'f':
		return 4; // F
	default:
		return -1;
	}
}

int getTIndex(char c) {
	switch (c) {
	case 'i':
		return 0; // id
	case '+':
		return 1;
	case '*':
		return 2;
	case '(':
		return 3;
	case ')':
		return 4;
	case '$':
		return 5;
	default:
		return -1;
	}
}

int main() {
	// LL(1) Parsing Table: m[Non-Terminal][Terminal]
	// 'n' represents epsilon (null production)
	std::string m[5][6] = {{"tb", "", "", "tb", "", ""},
						   {"", "+tb", "", "", "n", "n"},
						   {"fc", "", "", "fc", "", ""},
						   {"", "n", "*fc", "", "n", "n"},
						   {"i", "", "", "(e)", "", ""}};

	std::string s;
	std::cout << "Enter the input string: ";
	std::cin >> s;
	s += "$";

	std::vector<char> stack = {'$', 'e'};
	size_t j = 0;

	std::cout << "\nStack\t\tInput\n";
	std::cout << "______________________\n";

	while (!stack.empty()) {
		for (char c : stack)
			std::cout << c;
		std::cout << "\t\t" << s.substr(j) << "\n";

		char top = stack.back();
		char current_input = s[j];

		if (top == '$' && current_input == '$') {
			std::cout << "\nSUCCESS\n";
			return 0;
		}

		if (top == current_input) {
			stack.pop_back();
			j++;
		} else {
			int row = getNTIndex(top);
			int col = getTIndex(current_input);

			if (row == -1 || col == -1 || m[row][col].empty()) {
				std::cout << "\nERROR\n";
				return 0;
			}

			std::string prod = m[row][col];
			stack.pop_back();

			if (prod != "n") {
				for (int k = prod.length() - 1; k >= 0; --k) {
					stack.push_back(prod[k]);
				}
			}
		}
	}

	std::cout << "\nERROR\n";
	return 0;
}