#include <iostream>
#include <string>
using str = std::string;

str CeaserCipher(const str &text, int shift) {
	str result;
	for (int i = 0; i < text.length(); ++i) {
		char c = text[i];
		if (std::isalpha(c)) {
			char base = std::isupper(c) ? 'A' : 'a';
			result += (c - base + shift) % 26 + base;
		} else {
			result += c;
		}
	}

	return result;
}

str CeaserDecipher(const str &text, int shift) {
	return CeaserCipher(text, 26 - (shift % 26));
}

int main() {
	str text;
	int shift;
	std::cout << "Enter the text to encrypt: ";
	std::getline(std::cin, text);
	std::cout << "\nEnter the shift value: ";
	std::cin >> shift;

	str encrypted = CeaserCipher(text, shift);
	std::cout << "Encrypted text: " << encrypted << "\n\n";

	str decrypted = CeaserDecipher(encrypted, shift);
	std::cout << "Decrypted text: " << decrypted << std::endl;
	return 0;
}