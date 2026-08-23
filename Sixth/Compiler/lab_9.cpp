// WAP for intermediate Code Generation
#include <iostream>
#include <string>
#include <vector>

struct Operator {
	size_t pos;
	char op;
};

std::string str, leftOp, rightOp;
std::vector<Operator> operators;
char tmpch = 'Z';

void findOperators() {
	// Operators order by precedence: :, /, *, +, -
	const std::string opOrder = ":/*+-";
	for (char targetOp : opOrder) {
		for (size_t i = 0; i < str.length(); ++i) {
			if (str[i] == targetOp) {
				operators.push_back({i, targetOp});
			}
		}
	}
}

void findLeftOperand(int x) {
	int flag = 0;
	leftOp.clear();
	x--;
	while (x >= 0 && str[x] != '+' && str[x] != '*' && str[x] != '=' &&
		   str[x] != '-' && str[x] != '/' && str[x] != ':') {
		if (str[x] != '$' && flag == 0) {
			leftOp = str[x] + leftOp;
			str[x] = '$';
			flag = 1;
		}
		x--;
	}
}

void findRightOperand(int x) {
	int flag = 0;
	rightOp.clear();
	x++;
	while (x < static_cast<int>(str.length()) && str[x] != '+' &&
		   str[x] != '*' && str[x] != '=' && str[x] != ':' && str[x] != '-' &&
		   str[x] != '/') {
		if (str[x] != '$' && flag == 0) {
			rightOp += str[x];
			str[x] = '$';
			flag = 1;
		}
		x++;
	}
}

void explore() {
	size_t i = 1;
	while (i < operators.size()) {
		findLeftOperand(operators[i].pos);
		findRightOperand(operators[i].pos);
		str[operators[i].pos] = tmpch;

		std::cout << "\t" << tmpch << " := " << leftOp << " " << operators[i].op
				  << " " << rightOp << "\t\t";
		for (char c : str) {
			if (c != '$')
				std::cout << c;
		}
		std::cout << "\n";
		tmpch--;
		i++;
	}

	if (!operators.empty()) {
		findRightOperand(-1);
		findLeftOperand(str.length());
		std::cout << "\t" << leftOp << " := " << str[operators[0].pos] << "\n";
	}
}

int main() {
	std::cout << "\t\t INTERMEDIATE CODE GENERATION\n\n";
	std::cout << "Enter the Expression : ";
	std::cin >> str;

	std::cout << "\nThe intermediate code:\t\t Expression\n";
	findOperators();
	explore();

	return 0;
}