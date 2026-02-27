#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int max = RAND_MAX;
time_t t = 20;

double r_point() { return (double)rand() / max * 2.0 - 1.0; }
void estimate_pi(const char *sampleCase, long long iterations) {
	long long inside_circle = 0;
	long long total_points = iterations;

	for (long long i = 0; i < total_points; ++i) {
		double x = r_point();
		double y = r_point();
		if (x * x + y * y <= 1.0) {
			inside_circle++;
		}
	}
	double pi_estimate = 4.0 * (double)inside_circle / total_points;
	std::cout << "\nSample Case: " << sampleCase << "\n";
	std::cout << "Points Inside Circle: " << inside_circle << "\n";
	std::cout << "Estimated Pi: " << pi_estimate
			  << ", With total points = " << total_points << std::endl;
}

int main() {
	srand((unsigned)time(&t));
	int total = 3;
	estimate_pi("1", 1000000);
	estimate_pi("2", 10000000);
	estimate_pi("3", 100000000);
	return 0;
}