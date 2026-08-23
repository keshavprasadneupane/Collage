// Write a C program to test whether a given identifier is valid or not
#include <cctype>
#include <iostream>
#include <string>

int main() {
	std::string id;

	std::cout << "Enter an identifier: ";
	std::getline(std::cin, id);

	// Empty input check
	if (id.empty()) {
		std::cout << "Not a valid identifier\n";
		return 0;
	}

	bool is_valid = true;

	// Check if first character is a letter or underscore
	if (!std::isalpha(id[0]) && id[0] != '_') {
		is_valid = false;
	} else {
		// Check remaining characters for alphanumeric or underscore
		for (size_t i = 1; i < id.length(); ++i) {
			if (!std::isalnum(id[i]) && id[i] != '_') {
				is_valid = false;
				break;
			}
		}
	}

	if (is_valid) {
		std::cout << "Valid identifier\n";
	} else {
		std::cout << "Not a valid identifier\n";
	}

	return 0;
}