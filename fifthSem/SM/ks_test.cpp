#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

void ksTest(std::vector<double> R, float critical_value) {
	int n = R.size();
	std::sort(R.begin(), R.end());

	std::cout << "Sorted Numbers: ";
	for (double val : R)
		std::cout << val << " ";
	std::cout << "\n\n";

	double max_d_plus = 0;
	double max_d_minus = 0;

	std::cout << std::setw(5) << "i" << std::setw(10) << "Ri" << std::setw(10)
			  << "i/n" << std::setw(10) << "D+" << std::setw(10) << "D-"
			  << std::endl;

	for (int i = 1; i <= n; ++i) {
		double d_plus = (double)i / n - R[i - 1];
		double d_minus = R[i - 1] - (double)(i - 1) / n;

		if (d_plus > max_d_plus)
			max_d_plus = d_plus;
		if (d_minus > max_d_minus)
			max_d_minus = d_minus;

		std::cout << std::setw(5) << i << std::setw(10) << R[i - 1]
				  << std::setw(10) << (double)i / n << std::setw(10) << d_plus
				  << std::setw(10) << d_minus << std::endl;
	}

	double D = std::max(max_d_plus, max_d_minus);

	std::cout << "\nMax D+ = " << max_d_plus << std::endl;
	std::cout << "Max D- = " << max_d_minus << std::endl;
	std::cout << "Calculated D = " << D << std::endl;

	std::cout << "Critical Value (D_0.05, 5) = " << critical_value << std::endl;
	if (D <= critical_value) {
		std::cout
			<< "Result: Accept H0 (The numbers are uniformly distributed)."
			<< std::endl;
	} else {
		std::cout
			<< "Result: Reject H0 (The numbers are not uniformly distributed)."
			<< std::endl;
	}
}

int main() {
	std::vector<double> R = {0.44, 0.81, 0.14, 0.05, 0.91};
	ksTest(R, 0.565); // Critical value for n=5 at alpha=0.05
	return 0;
}