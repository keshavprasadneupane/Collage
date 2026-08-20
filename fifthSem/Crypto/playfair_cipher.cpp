#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using Matrix = std::vector<std::vector<char>>;
const int M_SIZE = 5;
using Str = std::string;

const Str ALPHABET = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // J omitted
// just for printing.
Matrix mKey(M_SIZE, std::vector<char>(M_SIZE));
// actual efficient mapping of characters to their positions in the matrix for
// O(1) lookup.
std::unordered_map<char, std::pair<int, int>> cPos;

struct MatrixPosition {
	int r1, c1, r2, c2;
};

void PrintMatrix(const Matrix &matrix) {
	for (const auto &row : matrix) {
		for (char c : row) {
			std::cout << c << " ";
		}
		std::cout << std::endl;
	}
}

Matrix CreateMatrix(const Str &key) {
	// lookup for used characters in the matrix.
	std::unordered_set<char> usedChars;
	int index = 0;

	for (char ch : key) {
		char c = std::toupper(ch);
		if (!std::isalpha(c))
			continue;

		if (c == 'J')
			c = 'I';

		if (usedChars.find(c) == usedChars.end()) {
			usedChars.insert(c);
			mKey[index / M_SIZE][index % M_SIZE] = c;
			cPos[c] = {index / M_SIZE, index % M_SIZE};
			index++;
		}
	}
	for (char c : ALPHABET) {
		if (usedChars.find(c) == usedChars.end()) {
			mKey[index / M_SIZE][index % M_SIZE] = c;
			cPos[c] = {index / M_SIZE, index % M_SIZE};
			index++;
		}
	}
	return mKey;
}

MatrixPosition FindPosition(char a, char b) {
	MatrixPosition pos{-1, -1, -1, -1};
	if (cPos.find(a) != cPos.end()) {
		pos.r1 = cPos[a].first;
		pos.c1 = cPos[a].second;
	}
	if (cPos.find(b) != cPos.end()) {
		pos.r2 = cPos[b].first;
		pos.c2 = cPos[b].second;
	}
	return pos;
}

Str CipherPair(const Matrix &matrix, MatrixPosition pos, bool encrypt) {
	int shift = encrypt ? 1 : 4;

	if (pos.r1 == pos.r2) {
		return Str() + matrix[pos.r1][(pos.c1 + shift) % M_SIZE] +
			   matrix[pos.r2][(pos.c2 + shift) % M_SIZE];
	}
	if (pos.c1 == pos.c2) {
		return Str() + matrix[(pos.r1 + shift) % M_SIZE][pos.c1] +
			   matrix[(pos.r2 + shift) % M_SIZE][pos.c2];
	}
	return Str() + matrix[pos.r1][pos.c2] + matrix[pos.r2][pos.c1];
}

Str PrepareText(const Str &text) {
	Str clean;
	for (char c : text) {
		if (std::isalpha(c)) {
			c = std::toupper(c);
			if (c == 'J')
				c = 'I';
			clean += c;
		}
	}
	Str result;
	for (size_t i = 0; i < clean.length(); ++i) {
		result += clean[i];

		if (i + 1 < clean.length() && clean[i] == clean[i + 1]) {
			result += 'X';
		}
	}
	if (result.length() % 2 != 0) {
		result += 'Z';
	}
	return result;
}

Str PlayfairCipher(const Str &text, const Str &key, bool encrypt = true) {
	Matrix matrix = CreateMatrix(key);

	if (encrypt) {
		PrintMatrix(matrix);
	}

	Str input = encrypt ? PrepareText(text) : text;
	Str result;

	for (int i = 0; i < input.length(); i += 2) {
		char a = encrypt ? input[i] : std::toupper(input[i]);
		char b = encrypt ? input[i + 1] : std::toupper(input[i + 1]);

		MatrixPosition pos = FindPosition(a, b);
		result += CipherPair(matrix, pos, encrypt);
	}

	return result;
}

int main() {
	Str text, key;

	std::cout << "Enter text: ";
	std::getline(std::cin, text);

	std::cout << "Enter key: ";
	std::getline(std::cin, key);

	Str encrypted = PlayfairCipher(text, key);
	std::cout << "Encrypted: " << encrypted << std::endl;

	Str decrypted = PlayfairCipher(encrypted, key, false);
	std::cout << "Decrypted: " << decrypted << std::endl;
	return 0;
}