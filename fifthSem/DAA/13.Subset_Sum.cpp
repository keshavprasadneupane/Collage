#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int total_nodes = 0;

void printSubset(const vector<int> &subset) {
	for (int num : subset)
		cout << num << " ";
	cout << "\n";
}

void subsetSum(const vector<int> &arr, vector<int> &current, int index,
			   int current_sum, int target) {
	total_nodes++;

	// If target achieved
	if (current_sum == target) {
		printSubset(current);
		return;
	}

	// Pruning condition
	if (current_sum > target || index >= arr.size())
		return;

	for (int i = index; i < arr.size(); i++) {
		// Prune early (since sorted)
		if (current_sum + arr[i] > target)
			break;

		current.push_back(arr[i]);
		subsetSum(arr, current, i + 1, current_sum + arr[i], target);
		current.pop_back(); // backtrack
	}
}

void generateSubsets(vector<int> &arr, int target) {
	sort(arr.begin(), arr.end()); // Sort for pruning

	int total = 0;
	for (int num : arr)
		total += num;

	if (!arr.empty() && arr[0] <= target && total >= target) {
		vector<int> current;
		subsetSum(arr, current, 0, 0, target);
	}
}

int main() {
	vector<int> weights = {15, 22, 14, 26, 32, 9, 16, 8};
	int target = 53;
	generateSubsets(weights, target);
	cout << "Nodes generated: " << total_nodes << endl;

	return 0;
}