#include <cctype>
#include <iostream>
#include <string>
#include <unordered_set>

const std::unordered_set<std::string> KEYWORDS = {
	"auto",		"break",  "case",	 "char",   "const",	   "continue",
	"default",	"do",	  "double",	 "else",   "enum",	   "extern",
	"float",	"for",	  "goto",	 "if",	   "int",	   "long",
	"register", "return", "short",	 "signed", "sizeof",   "static",
	"struct",	"switch", "typedef", "union",  "unsigned", "void",
	"volatile", "while"};

bool isKeyword(const std::string &str) { return KEYWORDS.count(str) > 0; }

void processToken(std::string &buffer) {
	if (buffer.empty())
		return;

	if (isKeyword(buffer)) {
		std::cout << buffer << " is keyword\n";
	} else {
		std::cout << buffer << " is identifier\n";
	}
	buffer.clear();
}

int main() {
	std::string input;
	std::cout << "Enter code/tokens: ";
	std::getline(std::cin, input);

	std::string buffer = "";
	const std::string operators = "+-*/%=";
	bool foundComma = false;
	for (char ch : input) {
		if (operators.find(ch) != std::string::npos) {
			processToken(buffer);
			std::cout << ch << " is operator\n";
		}

		else if (ch == ' ' || ch == '\t' || ch == ',') {
			processToken(buffer);
			if (ch == ',') {
				foundComma = true;
			}
		} else if (std::isalnum(ch) || ch == '_') {
			buffer += ch;
		}
	}

	processToken(buffer);

	if (foundComma) {
		std::cout << "',' is separator for this input stream\n";
	}
	return 0;
}