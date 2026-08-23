// Write a C/C++ program to recognize strings under 'a*', 'a*b+', 'abb'
#include <iostream>
#include <string>

int main() {
	std::string s;
	int state = 0;

	std::cout << "Enter a string: ";
	std::getline(std::cin, s);

	for (char c : s) {
		switch (state) {
		case 0:
			if (c == 'a')
				state = 1;
			else if (c == 'b')
				state = 2;
			else
				state = 6;
			break;
		case 1:
			if (c == 'a')
				state = 3;
			else if (c == 'b')
				state = 4;
			else
				state = 6;
			break;
		case 2:
			if (c == 'a')
				state = 6;
			else if (c == 'b')
				state = 2;
			else
				state = 6;
			break;
		case 3:
			if (c == 'a')
				state = 3;
			else if (c == 'b')
				state = 2;
			else
				state = 6;
			break;
		case 4:
			if (c == 'a')
				state = 6;
			else if (c == 'b')
				state = 5;
			else
				state = 6;
			break;
		case 5:
			if (c == 'a')
				state = 6;
			else if (c == 'b')
				state = 2;
			else
				state = 6;
			break;
		case 6:
			break;
		}

		if (state == 6) {
			break;
		}
	}

	// State 0 (empty string), State 1 ('a'), and State 3 ('aa', 'aaa', etc.)
	// match 'a*'
	if (state == 0 || state == 1 || state == 3) {
		std::cout << s << " is accepted under rule 'a*'\n";
	} else if (state == 2 || state == 4) {
		std::cout << s << " is accepted under rule 'a*b+'\n";
	} else if (state == 5) {
		std::cout << s << " is accepted under rule 'abb'\n";
	} else {
		std::cout << s << " is not recognized\n";
	}

	return 0;
}