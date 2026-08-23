// WAP to  implement Shift Reduce Parser

#include <iomanip>
#include <iostream>
#include <string>

void checkAndReduce(std::string &stack, const std::string &input,
					size_t input_idx) {
	bool reduced = true;

	while (reduced) {
		reduced = false;

		// Reduce handle 'a' -> E
		if (!stack.empty() && stack.back() == 'a') {
			stack.back() = 'E';
			std::cout << "$" << std::left << std::setw(15) << stack
					  << std::setw(15) << (input.substr(input_idx) + "$")
					  << "Reduce E->a\n";
			reduced = true;
		}
		// Reduce handle 'b' -> E
		else if (!stack.empty() && stack.back() == 'b') {
			stack.back() = 'E';
			std::cout << "$" << std::left << std::setw(15) << stack
					  << std::setw(15) << (input.substr(input_idx) + "$")
					  << "Reduce E->b\n";
			reduced = true;
		}
		// Reduce handle 'E+E' -> E
		else if (stack.length() >= 3 &&
				 stack.substr(stack.length() - 3) == "E+E") {
			stack.erase(stack.length() - 3);
			stack += 'E';
			std::cout << "$" << std::left << std::setw(15) << stack
					  << std::setw(15) << (input.substr(input_idx) + "$")
					  << "Reduce E->E+E\n";
			reduced = true;
		}
		// Reduce handle 'E*E' -> E
		else if (stack.length() >= 3 &&
				 stack.substr(stack.length() - 3) == "E*E") {
			stack.erase(stack.length() - 3);
			stack += 'E';
			std::cout << "$" << std::left << std::setw(15) << stack
					  << std::setw(15) << (input.substr(input_idx) + "$")
					  << "Reduce E->E*E\n";
			reduced = true;
		}
		// Reduce handle 'E/E' -> E
		else if (stack.length() >= 3 &&
				 stack.substr(stack.length() - 3) == "E/E") {
			stack.erase(stack.length() - 3);
			stack += 'E';
			std::cout << "$" << std::left << std::setw(15) << stack
					  << std::setw(15) << (input.substr(input_idx) + "$")
					  << "Reduce E->E/E\n";
			reduced = true;
		}
	}
}

int main() {
	std::string input;

	std::cout << "SHIFT REDUCE PARSER\n";
	std::cout << "GRAMMAR:\n E -> E+E\n E -> E/E\n E -> E*E\n E -> a | b\n\n";
	std::cout << "Enter the input symbol: ";
	std::cin >> input;

	std::string stack = "";

	std::cout << "\n"
			  << std::left << std::setw(16) << "Stack" << std::setw(15)
			  << "Input Symbol"
			  << "Action\n";
	std::cout << "___________________________________________\n";
	std::cout << "$" << std::left << std::setw(15) << stack << std::setw(15)
			  << (input + "$") << "--\n";

	for (size_t i = 0; i < input.length(); ++i) {
		// Shift action
		stack += input[i];
		std::string action = "Shift " + std::string(1, input[i]);

		std::cout << "$" << std::left << std::setw(15) << stack << std::setw(15)
				  << (input.substr(i + 1) + "$") << action << "\n";

		// Reduce action check
		checkAndReduce(stack, input, i + 1);
	}

	if (stack == "E") {
		std::cout << "$" << std::left << std::setw(15) << stack << std::setw(15)
				  << "$"
				  << "ACCEPT\n";
	} else {
		std::cout << "$" << std::left << std::setw(15) << stack << std::setw(15)
				  << "$"
				  << "REJECT\n";
	}

	return 0;
}