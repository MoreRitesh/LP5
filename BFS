#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

const int MAX = 100000;
vector<int> graph_bfs[MAX];
bool visited_seq_bfs[MAX], visited_par_bfs[MAX];

void bfs_sequential(int start) {
    queue<int> q;
    q.push(start);
    visited_seq_bfs[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        cout << node << " ";

        for (int i = 0; i < graph_bfs[node].size(); i++) {
            int adj = graph_bfs[node][i];
            if (!visited_seq_bfs[adj]) {
                visited_seq_bfs[adj] = true;
                q.push(adj);
            }
        }
    }
}

void bfs_parallel(int start, int n) {
    queue<int> q;
    q.push(start);
    visited_par_bfs[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        cout << node << " ";

        #pragma omp parallel
        {
            #pragma omp for
            for (int i = 0; i < graph_bfs[node].size(); i++) {
                int adj = graph_bfs[node][i];
                #pragma omp critical
                {
                    if (!visited_par_bfs[adj]) {
                        visited_par_bfs[adj] = true;
                        q.push(adj);
                    }
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
        graph_bfs[u].push_back(v);
        graph_bfs[v].push_back(u); // Undirected graph
    }

    // Initialize visited arrays to false
    for (int i = 0; i < n; i++) visited_seq_bfs[i] = visited_par_bfs[i] = false;

    double start_time, end_time;

    // Sequential BFS
    start_time = omp_get_wtime();
    cout << "\nSequential BFS: ";
    bfs_sequential(start);
    end_time = omp_get_wtime();
    cout << "\nTime taken for Sequential BFS: " << (end_time - start_time) * 1000 << " ms\n";

    // Parallel BFS
    fill(visited_par_bfs, visited_par_bfs + n, false);  // Reset visited array for parallel BFS
    start_time = omp_get_wtime();
    cout << "\nParallel BFS: ";
    bfs_parallel(start, n);
    end_time = omp_get_wtime();
    cout << "\nTime taken for Parallel BFS: " << (end_time - start_time) * 1000 << " ms\n";

    return 0;
}
