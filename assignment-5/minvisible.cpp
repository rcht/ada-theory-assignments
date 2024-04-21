#include <bits/stdc++.h>

using namespace std;

// checking whether dimensions fit inside
bool ismore(vector<int>& mr, vector<int>& ls){
    for(int i = 0; i < 3; ++i){
        if(mr[i] <= ls[i])
            return false;
    }
    return true;
}

// Ford-Fulkerson algorithm implementation from cp-algorithms.com

int bfs(int source, int target, vector<int>& parent, vector<vector<int>>& edgeWeight, vector<vector<int>>& adjacencyList) {
    fill(parent.begin(), parent.end(), -1);
    parent[source] = -2;
    queue<pair<int, int>> q;
    q.push({source, INT_MAX});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adjacencyList[cur]) {
            if (parent[next] == -1 && edgeWeight[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, edgeWeight[cur][next]);
                if (next == target)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int fordFulkerson(int source, int target, int n, vector<vector<int>>& edgeWeight, vector<vector<int>>& adjacencyList) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(source, target, parent, edgeWeight, adjacencyList)) {
        flow += new_flow;
        int cur = target;
        while (cur != source) {
            int prev = parent[cur];
            edgeWeight[prev][cur] -= new_flow;
            edgeWeight[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main(){
    int n;
    cin >> n;

    vector<vector<int>> d(n+1);

    for(int i = 0; i < n; ++i){
        d[i+1] = vector<int>(3,0);
        // inputting every dimension
        cin >> d[i+1][0] >> d[i+1][1] >> d[i+1][2];
        // sorting them because order doesn't matter
        sort(d[i+1].begin(), d[i+1].end());
    }

    // 0 is s
    // 1, 2, .... n are W
    // n+1, n+2, ... 2n are I 
    // 2n + 1 is t
    

    vector<vector<int>> adjacencyList(2*n + 2);
    vector<vector<int>> capacity(2*n + 2, vector<int>(2*n + 2, 0));

    // adding all source edges and edges to target

    for(int i = 1; i <= n; ++i){
        adjacencyList[0].push_back(i);
        capacity[0][i] = 1;
        adjacencyList[n + i].push_back(2*n + 1);
        capacity[n+i][2*n + 1] = 1;
    }

    // adding all dimension edges
    
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            if(ismore(d[i], d[j])){
                adjacencyList[i].push_back(n + j);
                capacity[i][n+j] = 1;
            }
        }
    }

    cout << n - fordFulkerson(0, 2*n + 1, 2*n + 2, capacity, adjacencyList) << '\n';

}
