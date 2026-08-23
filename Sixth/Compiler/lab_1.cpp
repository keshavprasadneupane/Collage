// Write program in C to test whether given entered string within valid
// comment section or not.
#include <iostream>
#include <string>

int main() {
	std::string com;

	std::cout << "Enter comment: ";
	std::getline(std::cin, com);

	bool is_comment = false;

	// Single-line comment check (starts with //)
	if (com.length() >= 2 && com[0] == '/' && com[1] == '/') {
		is_comment = true;
	}
	// Multi-line comment check (starts with /* and ends with */)
	else if (com.length() >= 4 && com[0] == '/' && com[1] == '*') {
		for (size_t i = 2; i < com.length() - 1; ++i) {
			if (com[i] == '*' && com[i + 1] == '/') {
				is_comment = true;
				break;
			}
		}
	}

	if (is_comment) {
		std::cout << "It is a comment\n";
	} else {
		std::cout << "It is not a comment\n";
	}

	return 0;
}