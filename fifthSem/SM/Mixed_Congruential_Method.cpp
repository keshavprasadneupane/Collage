#include <iomanip>
#include <iostream>
using ll = long long;

void GenerateLCG(ll M, ll A, ll C, ll X0, int count = 20) {
	ll m = M, a = A, c = C, x0 = X0;
	ll current_x = x0;

	std::cout << "\nGenerating " << count
			  << " Pseudo-Random Numbers using LCG:" << std::endl;
	std::cout << "Formula: X_{n+1} = (" << a << " * X_n + " << c << ") mod "
			  << m << std::endl;
	std::cout << "--------------------------------------------------"
			  << std::endl;
	std::cout << std::setw(5) << "n" << std::setw(15) << "X_n" << std::endl;

	for (int i = 1; i <= count; ++i) {
		current_x = (a * current_x + c) % m;
		std::cout << std::setw(5) << i << std::setw(15) << current_x
				  << std::endl;
	}
}

int main() {
	GenerateLCG(100, 13, 7, 5);
	return 0;
}