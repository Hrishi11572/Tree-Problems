#include<bits/stdc++.h>
using namespace std;
using lli = long long ;
#define endl '\n'
#define MOD 1000000007

int n;
vector<int> g[100100]; 
int parent[100100]; 
int dep[100100]; 
int cnt; 
int D; 
vector<int>ans; 

void dfs(int node, int par, int depth){
    dep[node]=depth; 
    if(dep[node] == D) cnt++; 
    parent[node]=par; 

    for(auto v: g[node]){
        if(v != par){
            dfs(v,node,depth+1);
        }
    }
}

void __dfs__(int node, int par, int depth){
    dep[node]=depth; 
    if(dep[node] == D) cnt++; 
    parent[node]=par; 

    for(auto v: g[node]){
        if(v != par){
            cnt=0; 
            dfs(v,node,depth+1);
            ans.push_back(cnt); 
        }
    }
}

void solve() {
   cin >> n ; 
   for(int i=1 ;i<=n-1; i++){
       int a , b;
       cin >> a >> b; 
       g[a].push_back(b); 
       g[b].push_back(a);
   }

   // Finding the diameter of a tree; 
   dfs(1,0,0); // start dfs from 1 

   int maxDepth=-1; 
   int nodeAtMaxDepth=1; 

   for(int i=1; i<=n ; i++){
      if(dep[i] > maxDepth){
        maxDepth = dep[i]; 
        nodeAtMaxDepth = i; 
      }
   }

   // nodeAtMaxDepth is one end point of diameter
   dfs(nodeAtMaxDepth, 0, 0); // perform dfs from this node 

   int diameter=-1; 
   int lastNode = nodeAtMaxDepth; 
   for(int i=1 ; i<=n ; i++){
       if(diameter < dep[i]){
            diameter = dep[i]; 
            lastNode=i; 
       } 
   }

   cout << diameter << endl ;

   D = diameter/2; 
   // lastNode and nodeAtMaxDepth are the two end-points of diameter


   // from here onwars we solve for the centers 
   if(diameter%2){
        //two centers 
        int center1,center2,currentNode; 
        currentNode = lastNode; 

        while(dep[currentNode]!=(diameter/2)-1){
            if(dep[currentNode] == (diameter/2)+1){
                center1 = currentNode; 
                center2 = parent[center1]; 
                break ; 
            }
            currentNode = parent[currentNode]; 
        }

        vector<int>groups; 
        cnt=0; 

        dfs(center1 , center2, 0); 
        groups.push_back(cnt);

        cnt=0; 
        dfs(center2 , center1, 0); 
        groups.push_back(cnt); 


        cout << "\nNumber of Diameters \n"; 
        cout << groups[0] * groups[1] << endl; 

   }else{
        // one center 
        int currentNode = lastNode; 
        int center; 
        while(dep[currentNode]!=(diameter/2)-1){
            if(dep[currentNode] == diameter/2) center = currentNode; 
            currentNode = parent[currentNode];
        }

        ans.clear(); 
        cnt=0;
        __dfs__(center, 0, 0);

        // all pair product in O(n) 
        lli sum = 0;
        lli total = 0;
        for(auto x : ans) total += x;
        for(auto x : ans){
            total -= x;
            sum += 1LL * x * total;
        }

        cout << "\nThe Number of Diameters\n";
        cout << sum << endl ; 
   }
}

signed main() {
 ios::sync_with_stdio(0);
 cin.tie(0);
 cout.tie(0);
 solve();
}


/*

 THIS IS AN IMPORTANT HIGHLIGHT !!! 

    To compute : Sigma(i=0 , n) Sigma(j=i+1 , n) ans[i] * ans[j]; 

    one method is a nested for loop like : 

    for(int i=0 ; i<n ; i++){
        for(int j=i+1; j<n ; j++){
            sum += ans[i]*ans[j];
        }
    }

    example : [3 , 5 , 7] - 
    => sum = 3 * 5 + 3 * 7  + 5 * 7 
    => sum = 3 * ( 5 + 7 ) + 5 * 7 

    another way is this : 
    sum = 3 * ( 5 + 7 + 3 - 3) + 5 * ( 3 + 5 + 7 - (3 + 5)) + 7 * ( 3 + 5 + 7 - (3 + 5 + 7)); 

    int total = 0; 
    for(int i=0; i<n ; i++) total += arr[i];

    int ans= 0; 
    for(int i=0 ; i<n ; i++){
        total = total - arr[i]; 
        ans += arr[i] * (total - arr[i]); 
    }

    this is a linear time algo !! 
*/