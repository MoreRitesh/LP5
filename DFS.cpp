#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];
bool visited_seq[MAX], visited_par[MAX];

void dfs_sequential(int start) {
    stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited_seq[node]) {
            visited_seq[node] = true;
            cout << node << " ";

            for (int i = graph[node].size() - 1; i >= 0; i--) {
                int adj = graph[node][i];
                if (!visited_seq[adj])
                    s.push(adj);
            }
        }
    }
}

void dfs_parallel(int start) {
    stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited_par[node]) {
            visited_par[node] = true;
            cout << node << " ";

            #pragma omp parallel for
            for (int i = 0; i < graph[node].size(); i++) {
                int adj = graph[node][i];
                if (!visited_par[adj]) {
                    #pragma omp critical
                    s.push(adj);
                }
            }
        }
    }
}

int main() {
    int n, m, start;
    cout << "Enter number of nodes, edges, and start node: ";
    cin >> n >> m >> start;

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);  // undirected graph
    }

    for (int i = 0; i < n; i++) visited_seq[i] = visited_par[i] = false;

    double start_time, end_time;

    // Sequential DFS
    start_time = omp_get_wtime();
    cout << "\nSequential DFS: ";
    dfs_sequential(start);
    end_time = omp_get_wtime();
    cout << "\nTime taken for Sequential DFS: " << (end_time - start_time) * 1000 << " ms\n";

    // Reset visited for parallel DFS
    fill(visited_par, visited_par + n, false);

    // Parallel DFS
    start_time = omp_get_wtime();
    cout << "\nParallel DFS: ";
    dfs_parallel(start);
    end_time = omp_get_wtime();
    cout << "\nTime taken for Parallel DFS: " << (end_time - start_time) * 1000 << " ms\n";

    return 0;
}
