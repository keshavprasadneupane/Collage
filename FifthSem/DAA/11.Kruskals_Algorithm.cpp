#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
	int u, v, w;
};

class DisjointSet {
	vector<int> parent, rank;

  public:
	DisjointSet(int n) {
		parent.resize(n);
		rank.resize(n, 0);

		for (int i = 0; i < n; i++)
			parent[i] = i;
	}

	int find(int x) {
		if (parent[x] != x)
			parent[x] = find(parent[x]);
		return parent[x];
	}

	bool unite(int x, int y) {
		x = find(x);
		y = find(y);

		if (x == y)
			return false;

		// Union by Rank
		if (rank[x] < rank[y])
			parent[x] = y;
		else if (rank[x] > rank[y])
			parent[y] = x;
		else {
			parent[y] = x;
			rank[x]++;
		}
		return true;
	}
};

class Graph {
	int V;
	vector<Edge> edges;

  public:
	Graph(int V) : V(V) { edges.reserve(V); }

	void addEdge(Edge e) { edges.push_back(e); }

	int kruskalMST() {
		sort(edges.begin(), edges.end(),
			 [](const Edge &a, const Edge &b) { return a.w < b.w; });

		DisjointSet ds(V);
		int mst_wt = 0;

		cout << "Edges of MST:\n";

		for (const auto &e : edges) {
			if (ds.unite(e.u, e.v)) {
				cout << e.u << " - " << e.v << " (Weight=" << e.w << ")\n";
				mst_wt += e.w;
			}
		}

		return mst_wt;
	}
};

int getRW() { return rand() % 20 + 1; }

int main() {
	int size = 12;
	Graph g(size);
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			g.addEdge({i, j, getRW()});
		}
	}
	int mst_wt = g.kruskalMST();
	cout << "\nTotal Weight of MST: " << mst_wt << endl;
	return 0;
}