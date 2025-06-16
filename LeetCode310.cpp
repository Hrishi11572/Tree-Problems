// idea of center finding in tree!! 

class Solution {
  public:
    int N; 
    vector<int>parent ,dep ; 

    void dfs(int node, int par, int depth, vector<vector<int>>& adj){
        parent[node] = par; 
        dep[node]=depth; 
        for(auto v : adj[node]){
            if(v != par){
                dfs(v,node,depth+1,adj); 
            }
        }
    }

    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        N = n; 
        dep.resize(N); 
        parent.resize(N); 

        vector<vector<int>>adj(n); 
        for(auto& e : edges){
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        dfs(0,-1,0,adj); 
        int firstnode = 0; 
        int maxdepth=-1;

        for(int i=0 ; i<n ; i++){
            if(maxdepth <= dep[i]){
                maxdepth = dep[i]; 
                firstnode = i; 
            }
        }

        dfs(firstnode,-1,0,adj); 
        int diameter=-1; 
        int lastnode=firstnode;

        for(int i=0; i<n ; i++){
            if(diameter <= dep[i]){
                diameter = dep[i]; 
                lastnode = i; 
            }
        } 

        // cout << diameter << endl ; 
        vector<int>ans ; 

        int currNode=lastnode; 
        for(int i=1; i<=diameter/2 ; i++){
            currNode = parent[currNode];
        }

        ans.push_back(currNode); 
        
        // cout << currNode << endl ; 
        if(diameter%2){
            // two centers 
            ans.push_back(parent[currNode]); 
        }

        return ans; 
    }
};