// for 2x2 matrix only
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using Str = string;
using Matrix = vector<vector<int>>;

int FindInverse(int num, int mod) {
	int a1 = mod, a2 = num, t1 = 0, t2 = 1;
	while (a2 > 0) {
		int q = a1 / a2;
		int a = a1 - q * a2;
		int t = t1 - q * t2;
		a1 = a2;
		a2 = a;
		t1 = t2;
		t2 = t;
	}
	int inverse = t1 % mod;
	if (inverse < 0) {
		inverse += mod;
	}
	return inverse;
}

const int A_SIZE = 26;

Matrix ModInverse(const Matrix &matrix, int mod) {
	int det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	det = (det % mod + mod) % mod;
	if (det == 0) {
		throw runtime_error("Matrix is not invertible");
	}
	int invDet = FindInverse(det, mod);

	Matrix inv(2, std::vector<int>(2));
	inv[0][0] = matrix[1][1] * invDet % mod;
	inv[0][1] = (-matrix[0][1] + mod) * invDet % mod;
	inv[1][0] = (-matrix[1][0] + mod) * invDet % mod;
	inv[1][1] = matrix[0][0] * invDet % mod;

	return inv;
}

Str HillCipher(const Str &text, const Matrix &key, bool encrypt = true) {
	if (text.length() % 2 != 0) {
		throw runtime_error("Text length must be even");
	}

	Matrix usedKey = encrypt ? key : ModInverse(key, A_SIZE);
	Str result;

	for (size_t i = 0; i < text.length(); i += 2) {
		int a = tolower(text[i]) - 'a';
		int b = tolower(text[i + 1]) - 'a';

		int r1 = (usedKey[0][0] * a + usedKey[0][1] * b) % A_SIZE;
		int r2 = (usedKey[1][0] * a + usedKey[1][1] * b) % A_SIZE;

		result += (r1 + 'a');
		result += (r2 + 'a');
	}

	return result;
}

int main() {
	Str text;
	Matrix key(2, vector<int>(2));
	cout << "Enter the text to encrypt (even length): ";
	getline(std::cin, text);
	cout << "Enter the 2x2 key matrix (row-wise): ";
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			cin >> key[i][j];
		}
	}

	Str encrypted = HillCipher(text, key);
	cout << "Encrypted text: " << encrypted << endl;

	Str decrypted = HillCipher(encrypted, key, false);
	cout << "Decrypted text: " << decrypted << endl;
	return 0;
}