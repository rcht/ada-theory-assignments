#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 1;

vector<vector<int>> adj(N);
vector<vector<int>> adjrev(N);
vector<int> toposorted;

int vis1[N];
int vis2[N];
int incident[N];

void initvis(){
    for(int i = 0; i < N; ++i){
        vis1[i] = 0;
        vis2[i] = 0;
        incident[i] = 0;
    }
}

void dfs1(int s){
    vis1[s] = 1;
    for(const auto &v: adj[s]){
        if(vis1[v] == 0)
            dfs1(v);
        ++incident[v];
    }
    toposorted.push_back(s);
}

void dfs2(int t){ 
    vis2[t] = 1;
    for(const auto &v: adjrev[t]){
        if(vis2[v] == 0)
            dfs2(v);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    initvis();

    int n,m; cin >> n >> m;
    int s,t; cin >> s >> t;

    for(int i = 0; i < m; ++i){
        int fst, snd;
        cin >> fst >> snd;

        adj[fst].push_back(snd);
        adjrev[snd].push_back(fst);
    }

    dfs1(s);
    dfs2(t);

    if(!vis1[t]){
        cout << "No cut vertices\n";
        return 0;
    }

    reverse(toposorted.begin(), toposorted.end());

    int cnt = 0;
    vector<int> ans;

    for(const auto &node: toposorted){
        if(vis2[node] == 0){
            continue;
        }
        cnt -= incident[node];
        if(cnt == 0){
            ans.push_back(node);
        }
        for(const auto &edge: adj[node]){
            if(vis2[edge])
                ++cnt;
        }
    }

    for(const auto &item: ans){
        cout << item << ' ';
    }
    cout << '\n';
}
