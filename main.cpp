#include "structures/graph/adjacency_list.hpp"
using namespace std;

/*
N E
u_1 v_1 
...
u_E v_E

nodes are u_1, .. u_E in [0,N-1]
*/

struct DisjoinSet {
    int N; // Number of sets
    vector<int> id;
    vector<int> rank;
    
    DisjoinSet() {;}
    DisjoinSet(int _N) {
        N = _N;
        id = vector<int>();
        rank = vector<int>();
        for (int i=0; i<N; i++) {
            id.push_back(i);
            rank.push_back(1);
        }
    }

    int Find(int i) {
        if (id[i]!=i) id[i] = Find(id[i]);
        return id[i];
    }
    
    void Union(int i, int j) {
        i = Find(i);
        j = Find(j);
        if (rank[i] > rank[j]) swap(i,j);
        // rank[i] <= rank[j]
        id[j] = i;
        rank[i]++;
    }
    
    bool AreConnected(int i, int j) {
        return Find(i) == Find(j);
    }
    
    void debug() {
        for (int i=0; i<N; i++) {
            cout << id[i] << " ";
        }
        cout << endl;
    }
};

int calcmincut(vector<Edge>& input, int N, int E, DisjoinSet& ds, int comp) {
    // Shuffle the array
    // https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
    // for i from 0 to n−2 do
    for (int i=0; i<E-1; i++) {
        // j ← random integer such that i ≤ j < n
        int j = (rand() % (E-i-1)) + i;
        if (i!=j)
            swap(input[i], input[j]);// exchange a[i] and a[j] 
    }
        
    // Run compression
    int components = N;
    
    for (int i=0; i<E && components>comp; i++) {
        if (ds.AreConnected(input[i].u, input[i].v)) continue;
        // not connected
        components--;
        ds.Union(input[i].u, input[i].v);
    }
    
    //components == comp
    int cut = 0;
    for (int i=0; i<E; i++) {
        if (ds.AreConnected(input[i].u, input[i].v)) continue;
        // not connected
        cut++;
    }
    
    return cut;
}

int calcmincutKargerStein(vector<Edge>& input, int N, int E, DisjoinSet& ds) {
    if (N < 6) {
        return calcmincut(input, N, E, ds, 2);
    }
    int ret = E+1;
    int t = 1 + (N * 100000 / 141421);
    DisjoinSet ds1 = ds;
    calcmincut(input, N, E, ds, t);
    ret = calcmincutKargerStein(input, t, E, ds1);
    ds1 = ds;
    calcmincut(input, N, E, ds, t);
    ret = min(ret,calcmincutKargerStein(input, t, E, ds1));
    return ret;
}


// n^2 m log n.
int kargers(vector<Edge>& input, int N, int E) {
    int mincut = E+1;
    
    int log = 1;
    int auxN = N;
    while (auxN != 0) {log++; auxN/=2;}
    
    int runs = (N * (N-1) * log) / 2 + 2;
    
    for (int i=0; i<runs; i++) {
        DisjoinSet ds = DisjoinSet(N);
        mincut = std::min(mincut, calcmincut(input, N, E, ds, 2));
    }
    
    return mincut;    
}

int kargerStein(vector<Edge>& input, int N, int E) {
    int mincut = E+1;
    
    int log = 1;
    int auxN = N;
    //change number of runs
    while (auxN != 0) {log++; auxN/=2;}
    
    int runs = log*log + 2;
    
    for (int i=0; i<runs; i++) {
        DisjoinSet ds = DisjoinSet(N);
        mincut = std::min(mincut, calcmincutKargerStein(input, N, E, ds));
    }
    
    return mincut;
}

int main() {
    int N, E;
    vector<Edge> input;
    cin >> N >> E;
    for (int i=0; i< E; i++) {
        Edge aux;
        cin >> aux.u >> aux.v;
        input.push_back(aux);
    }
    
    int mincut = kargerStein(input, N, E);
    
    cout << mincut << endl;
}