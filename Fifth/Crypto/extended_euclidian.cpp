#include <iostream>
struct EEResult {
	int gcd, x, y;
};

EEResult REEuclidean(int a, int b) {
	if (b == 0) {
		return {a, 1, 0};
	}

	EEResult result = REEuclidean(b, a % b);
	int x = result.y;
	int y = result.x - (a / b) * result.y;
	return {result.gcd, x, y};
}

EEResult IEEuclidean(int a, int b) {
	int x0 = 1, y0 = 0;
	int x1 = 0, y1 = 1;
	while (b != 0) {
		int q = a / b;
		int r = a % b;
		a = b;
		b = r;
		int xTemp = x1;
		int yTemp = y1;
		x1 = x0 - q * x1;
		y1 = y0 - q * y1;
		x0 = xTemp;
		y0 = yTemp;
	}

	return {a, x0, y0};
}

int main() {
	int a, b;
	std::cout << "Enter two integers (a and b): ";
	std::cin >> a >> b;
	auto r_result = REEuclidean(a, b);
	std::cout << "Recursive: GCD(" << a << ", " << b << ") = " << r_result.gcd
			  << " , " << a << "*" << r_result.x << " + " << b << "*"
			  << r_result.y << " = " << r_result.gcd << std::endl;

	auto i_result = IEEuclidean(a, b);
	std::cout << "Iterative: GCD(" << a << ", " << b << ") = " << i_result.gcd
			  << " , " << a << "*" << i_result.x << " + " << b << "*"
			  << i_result.y << " = " << i_result.gcd << std::endl;

	return 0;
}