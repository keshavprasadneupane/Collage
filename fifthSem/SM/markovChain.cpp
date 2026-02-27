#include <iomanip>
#include <iostream>
#include <vector>

int main() {
	// Transition Matrix P
	// [ P(H|H)  P(Y|H) ] -> [ 0.7  0.3 ]
	// [ P(H|Y)  P(Y|Y) ] -> [ 0.2  0.8 ]
	double transition[2][2] = {{0.7, 0.3}, {0.2, 0.8}};
	double state[2] = {1.0, 0.0};
	int steps = 3;
	std::cout << "Markov Chain Transitions for Honda User:" << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
	for (int i = 1; i <= steps; ++i) {
		double next_honda =
			state[0] * transition[0][0] + state[1] * transition[1][0];
		double next_yamaha =
			state[0] * transition[0][1] + state[1] * transition[1][1];

		state[0] = next_honda;
		state[1] = next_yamaha;

		std::cout << "\nPurchase " << i << ":" << std::endl;
		std::cout << "P(Honda)  = " << std::fixed << std::setprecision(4)
				  << state[0] << std::endl;
		std::cout << "P(Yamaha) = " << std::fixed << std::setprecision(4)
				  << state[1] << std::endl;
	}

	return 0;
}