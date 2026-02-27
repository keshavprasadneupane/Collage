#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
	std::vector<double> random_numbers = {
		0.34, 0.83, 0.96, 0.47, 0.79, 0.99, 0.37, 0.72, 0.06, 0.18, 0.90, 0.76,
		0.99, 0.30, 0.71, 0.17, 0.51, 0.43, 0.39, 0.26, 0.25, 0.79, 0.77, 0.17,
		0.23, 0.99, 0.54, 0.56, 0.84, 0.97, 0.89, 0.64, 0.67, 0.82, 0.19, 0.46,
		0.01, 0.97, 0.24, 0.88, 0.87, 0.70, 0.56, 0.56, 0.82, 0.05, 0.81, 0.30,
		0.40, 0.64, 0.44, 0.81, 0.41, 0.05, 0.93, 0.66, 0.28, 0.94, 0.64, 0.47,
		0.12, 0.94, 0.52, 0.45, 0.65, 0.10, 0.69, 0.96, 0.40, 0.60, 0.21, 0.74,
		0.73, 0.31, 0.37, 0.42, 0.34, 0.58, 0.19, 0.11, 0.46, 0.22, 0.99, 0.78,
		0.39, 0.18, 0.75, 0.73, 0.79, 0.29, 0.67, 0.74, 0.02, 0.05, 0.42, 0.49,
		0.49, 0.05, 0.62, 0.78};

	int n = random_numbers.size();
	int num_intervals = 10;
	double expected_freq = (double)n / num_intervals;
	int observed_freq[10] = {0};

	for (double num : random_numbers) {
		int interval = (int)(num * 10);
		if (interval > 9)
			interval = 9;
		observed_freq[interval]++;
	}

	double chi_square_stat = 0;
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Interval | Oi | Ei | (Oi-Ei)^2 / Ei" << std::endl;
	std::cout << "------------------------------------" << std::endl;

	for (int i = 0; i < 10; i++) {
		double term = pow(observed_freq[i] - expected_freq, 2) / expected_freq;
		chi_square_stat += term;
		std::cout << i << "        | " << observed_freq[i] << " | "
				  << expected_freq << " | " << term << std::endl;
	}

	std::cout << "\nCalculated Chi-Square Statistic: " << chi_square_stat
			  << std::endl;
	std::cout << "Degrees of Freedom (k-1): 9" << std::endl;
	std::cout << "Critical Value (alpha=0.05, df=9): 16.91" << std::endl;

	if (chi_square_stat <= 16.91)
		std::cout << "Conclusion: Numbers are uniformly distributed."
				  << std::endl;
	else
		std::cout << "Conclusion: Numbers are NOT uniformly distributed."
				  << std::endl;

	return 0;
}