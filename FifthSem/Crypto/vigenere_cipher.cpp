#include <iostream>
#include <string>
using Str = std::string;
const int A_SIZE = 26;
const char BASE = 'a';

Str MakeLowerCase(const Str &s) {
	Str result;
	for (char c : s) {
		result += std::tolower(c);
	}
	return result;
}
Str VigenereCipher(const Str &text, const Str &key) {
	Str result;
	Str lText = MakeLowerCase(text);
	Str lKey = MakeLowerCase(key);
	int keyLen = lKey.length();

	for (int i = 0; i < lText.length(); ++i) {
		char c = lText[i];
		if (std::isalpha(c)) {
			char k = lKey[i % keyLen] - BASE;
			result += (c - BASE + k) % A_SIZE + BASE;
		} else {
			result += c;
		}
	}
	return result;
}

Str VigenereDecipher(const Str &text, const Str &key) {
	Str result;
	Str lText = MakeLowerCase(text);
	Str lKey = MakeLowerCase(key);
	int keyLen = lKey.length();
	for (int i = 0; i < lText.length(); ++i) {
		char c = lText[i];
		if (std::isalpha(c)) {
			char k = lKey[i % keyLen] - BASE;
			result += (c - BASE - k + A_SIZE) % A_SIZE + BASE;
		} else {
			result += c;
		}
	}
	return result;
}

int main() {
	Str text, key;
	std::cout << "Enter the text to encrypt: ";
	std::getline(std::cin, text);
	std::cout << "Enter the key: ";
	std::getline(std::cin, key);

	Str encrypted = VigenereCipher(text, key);
	std::cout << "Encrypted text: " << encrypted << std::endl;

	Str decrypted = VigenereDecipher(encrypted, key);
	std::cout << "Decrypted text: " << decrypted << std::endl;
	return 0;
}