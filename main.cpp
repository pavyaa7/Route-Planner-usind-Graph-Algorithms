#include <bits/stdc++.h>

using namespace std;

class graph {
    int n;
    vector<vector<pair<int, int>>> adj;
public:
    graph(int node) {
        n=node;
        adj.resize(n);
    }
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    //Algorithms
    vector<int> dfs(int s, int d) {
        int n = adj.size();
        vector<bool> vis(n, false);
        vector<int> parent(n, -1);
        stack<int> st;
        st.push(s);
        vis[s] = true;
        while (!st.empty()) {
            int node = st.top();
            st.pop();
            if (node == d) break;
            for (auto neigh : adj[node]) {
                if (!vis[neigh.first]) {
                    vis[neigh.first] = true;
                    parent[neigh.first] = node;
                    st.push(neigh.first);
                }
            }
        }
        if (!vis[d]) return {};
        vector<int> path;
        for (int c = d; c != -1; c = parent[c]) path.push_back(c);
        reverse(path.begin(), path.end());
        return path;
    }

    vector<int> bfs(int s, int d) {
        int n = adj.size();
        vector<bool> vis(n, false);
        vector<int> parent(n, -1);
        queue<int> q;
        q.push(s);
        vis[s] = true;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            if (node == d) break;
            for (auto neigh : adj[node]) {
                if (!vis[neigh.first]) {
                    vis[neigh.first] = true;
                    parent[neigh.first] = node;
                    q.push(neigh.first);
                }
            }
        }
        if (!vis[d]) return {};
        vector<int> path;
        for (int c = d; c != -1; c = parent[c]) path.push_back(c);
        reverse(path.begin(), path.end());
        return path;
    }
    
    vector<int> dijkstra(int s, int d) {
        int n = adj.size();
        vector<int> dist(n, INT_MAX);
        vector<int> parent(n, -1);
        priority_queue<pair<int,int>, vector<pair<int,int>>,  greater<pair<int,int>>> pq;
        dist[s] = 0;
        pq.push({0, s});
        while (!pq.empty()) {
            auto [d, node] = pq.top();
            pq.pop();
            if (d>dist[node]) continue;
            for (auto [neigh, wt] : adj[node]) {
                if (dist[node]+wt<dist[neigh]) {
                    dist[neigh]=dist[node]+wt;
                    parent[neigh]=node;
                    pq.push({dist[neigh], neigh});
                }
            }
        }
        if (dist[d]==INT_MAX) return {};
        vector<int> path;
        for (int c=d; c!=-1; c=parent[c]) path.push_back(c);
        reverse(path.begin(), path.end());
        return path;
    }

    //Printing the path
    int pathCost(vector<int>& path) {
        int len=0;
        for(int i=0; i+1<path.size(); i++) {
            for(int j=0; j<adj[path[i]].size(); j++) {
                if(path[i+1]==adj[path[i]][j].first) {
                    len+=adj[path[i]][j].second;
                    break;
                }
            }
        }
        return len;
    }

    void printPath(vector<int> path) {
        int n=path.size();
        cout << "Path: ";
        for(int i=0; i<n; i++) {
            cout << path[i];
            if(i==n-1) break;
            cout << " -> ";
        }
        cout << endl << "Path length: " << pathCost(path) << endl << endl;
    }

    //Visualization 
    void generateDOT() {
        ofstream fout("graph.dot");
        fout << "graph G {\n";
        for(int u=0; u<n; u++) {
            for(auto [v,w] : adj[u]) {
                if(u<v) fout << u << " -- "  << v << " [label=\""  << w << "\"];\n";
            }
        }
        fout << "}\n";
        fout.close();
    }
    void generateDOT_DFS(vector<int>& path) {
        ofstream fout("graphDFS.dot");
        fout << "graph G {\n";
        for(int u=0; u<n; u++) {
            for(auto [v,w] : adj[u]) {
                bool onPath = false;
                for(int i=0; i+1<path.size(); i++) {
                    if((path[i]==u && path[i+1]==v)||(path[i]==v && path[i+1]==u)) {
                        onPath = true;
                        break;
                    }
                }
                if(u<v&&onPath) {
                    fout << u << " -- " << v << " [label=\"" << w << "\", color=\"red\", penwidth=4];\n";
                } 
                else if(u<v) fout << u << " -- "  << v << " [label=\""  << w << "\"];\n";
            }
        }
        fout << "}\n";
        fout.close();
    }
    void generateDOT_BFS(vector<int>& path) {
        ofstream fout("graphBFS.dot");
        fout << "graph G {\n";
        for(int u=0; u<n; u++) {
            for(auto [v,w] : adj[u]) {
                bool onPath = false;
                for(int i=0; i+1<path.size(); i++) {
                    if((path[i]==u && path[i+1]==v)||(path[i]==v && path[i+1]==u)) {
                        onPath = true;
                        break;
                    }
                }
                if(u<v&&onPath) {
                    fout << u << " -- " << v << " [label=\"" << w << "\", color=\"red\", penwidth=4];\n";
                } 
                else if(u<v) fout << u << " -- "  << v << " [label=\""  << w << "\"];\n";
            }
        }
        fout << "}\n";
        fout.close();
    }
    void generateDOT_Dijkstra(vector<int>& path) {
        ofstream fout("graphDijkstra.dot");
        fout << "graph G {\n";
        for(int u=0; u<n; u++) {
            for(auto [v,w] : adj[u]) {
                bool onPath = false;
                for(int i=0; i+1<path.size(); i++) {
                    if((path[i]==u && path[i+1]==v)||(path[i]==v && path[i+1]==u)) {
                        onPath = true;
                        break;
                    }
                }
                if(u<v&&onPath) {
                    fout << u << " -- " << v << " [label=\"" << w << "\", color=\"red\", penwidth=4];\n";
                } 
                else if(u<v) fout << u << " -- "  << v << " [label=\""  << w << "\"];\n";
            }
        }
        fout << "}\n";
        fout.close();
    }

    void generateRandomGraph(int edges) {
        srand(time(0));
        for(int i=0; i<edges; i++) {
            int u=rand()%n;
            int v=rand()%n;
            while(v==u) v=rand()%n;
            int w=1+rand()%100;
            addEdge(u,v,w);
        }
    }

    //Benchmark
    long long benchmarkDijkstra(graph &g, int s, int d) {
        auto start=chrono::high_resolution_clock::now();
        g.dijkstra(s,d);
        auto end=chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::microseconds>(end-start).count();
    }
    long long benchmarkDFS(graph &g, int s, int d) {
        auto start=chrono::high_resolution_clock::now();
        g.dfs(s,d);
        auto end=chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::microseconds>(end-start).count();
    }
    long long benchmarkBFS(graph &g, int s, int d) {
        auto start=chrono::high_resolution_clock::now();
        g.bfs(s,d);
        auto end=chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::microseconds>(end-start).count();
    }

};

int main() { 
    graph g1(6);
    g1.addEdge(0,1,4);
    g1.addEdge(0,2,2);
    g1.addEdge(1,3,5);
    g1.addEdge(2,3,1);
    g1.addEdge(3,4,3);
    g1.addEdge(4,5,2);
    vector<int> path = g1.dfs(0,5);
    g1.generateDOT_DFS(path);
    g1.printPath(path);
    vector<int> sizes = {10,100,1000,2000};
    for(int sz : sizes) {
        graph g(sz);   
        g.generateRandomGraph(sz * 5);
        cout<<"Nodes = "<<sz<<'\n';
        cout<<"DFS = " <<g.benchmarkDFS(g,0,sz-1) <<" us\n";
        cout<<"BFS = " <<g.benchmarkBFS(g,0,sz-1) <<" us\n";
        cout<<"Dijkstra = " <<g.benchmarkDijkstra(g,0,sz-1) <<" us\n";
        cout<<'\n';
    }
}