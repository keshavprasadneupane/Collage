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
			parent[x] = find(parent[x]); // Path Compression
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
	Graph(int V) : V(V) {
		edges.reserve(V); // small optimization
	}

	void addEdge(int u, int v, int w) { edges.push_back({u, v, w}); }

	int kruskalMST() {
		sort(edges.begin(), edges.end(),
			 [](const Edge &a, const Edge &b) { return a.w < b.w; });

		DisjointSet ds(V);
		int mst_wt = 0;

		cout << "Edges of MST:\n";

		for (const auto &e : edges) {
			if (ds.unite(e.u, e.v)) {
				cout << e.u << " - " << e.v << " (Weight " << e.w << ")\n";
				mst_wt += e.w;
			}
		}

		return mst_wt;
	}
};

int main() {

	Graph g(9);

	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);

	int mst_wt = g.kruskalMST();

	cout << "\nTotal Weight of MST: " << mst_wt << endl;

	return 0;
}