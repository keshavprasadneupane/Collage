#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Job {
	char id;
	int deadline;
	int profit;
};

void jobScheduling(vector<Job> &jobs) {
	sort(jobs.begin(), jobs.end(),
		 [](const Job &a, const Job &b) { return a.profit > b.profit; });

	// Find maximum deadline
	int maxDeadline = 0;
	for (const auto &job : jobs)
		maxDeadline = max(maxDeadline, job.deadline);

	// Slot array
	vector<int> slot(maxDeadline, -1);

	int totalProfit = 0;

	for (int i = 0; i < jobs.size(); i++) {
		// Try to place job in latest possible free slot
		for (int j = min(maxDeadline, jobs[i].deadline) - 1; j >= 0; j--) {
			if (slot[j] == -1) {
				slot[j] = i;
				totalProfit += jobs[i].profit;
				break;
			}
		}
	}

	cout << "Maximum Profit Job Sequence:\n";
	for (int i = 0; i < maxDeadline; i++) {
		if (slot[i] != -1)
			cout << jobs[slot[i]].id << " ";
	}

	cout << "\nTotal Profit: " << totalProfit << endl;
}

int main() {

	vector<Job> jobs = {
		{'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27}, {'d', 1, 25}, {'e', 3, 15}};

	jobScheduling(jobs);

	return 0;
}