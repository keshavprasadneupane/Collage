#include <climits>
using namespace std;
#include <iostream>
const int V = 4;
const int INF = INT_MAX;
int count = 0;

void printSolution(int dist[][V]) {
	cout << "The following matrix shows the shortest distances between every "
			"pair of vertices \n";
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (dist[i][j] == INF)
				cout << "INF"
					 << " ";
			else
				cout << dist[i][j] << " ";
		}
		cout << endl;
	}
}

void floydWarshall(int dist[][V]) {
	count = 0; // fresh count for each call
	for (int k = 0; k < V; k++) {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				if (dist[i][j] > (dist[i][k] + dist[k][j]) &&
					(dist[k][j] != INF && dist[i][k] != INF)) {
					dist[i][j] = dist[i][k] + dist[k][j];
					count += 6;
				}
				count += 4;
			}
			count += 4;
		}
		count += 4;
	}
	printSolution(dist);
}

int main() {

	int graph[V][V] = {
		{0, 5, INF, 10}, {INF, 0, 3, INF}, {5, INF, 0, 1}, {INF, INF, 3, 0}};

	floydWarshall(graph);
	cout << "Required No of steps : " << count;
	return 0;
}