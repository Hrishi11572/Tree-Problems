/*
  
    TASK : 
    
    isLeaf ?? 
    depth ?? 
    Subtree Size ?? 
    Parent ?? 
    Number of Child ?? 
*/
#include<bits/stdc++.h>
using namespace std; 
using lli = long long ; 

vector<int> g[100100]; 
int dep[100100]; 
int par[100100]; 
int NumberofChild[100100]; 
int SubtreeSz[100100]; 
int isLeaf[100100] ; 

void dfs(int node , int parent , int depth){
    dep[node] = depth; 
    par[node] = parent; 
    
    SubtreeSz[node] = 1; 
    for(auto v : g[node]){
        if(v != parent){
            NumberofChild[node]++;  
            dfs(v , node , depth+1); 
            SubtreeSz[node] += SubtreeSz[v]; 
        }
    }
    
    if(NumberofChild[node] == 0){
        isLeaf[node] = 1; 
    }
}

signed main(){
    int n; 
    cin >> n ; 
    
    for(int i=1 ; i<n ; i++){
        int a , b ;
        cin >> a >> b ; 
        g[a].push_back(b); 
        g[b].push_back(a); 
    }
    
    dfs(1,0,0); 
    
    for(int i=1 ; i<=n ; i++){
        cout << "is leaf node ? " << i << " " << bool(isLeaf[i]) << endl ; 
        cout << "parent of " << i << " "  << par[i] << endl; 
        cout << "Number of Children of " << i << " " << NumberofChild[i] << endl ;
        cout << "Depth of node " << i << " " << dep[i] << endl; 
    }
    
    return 0; 
}