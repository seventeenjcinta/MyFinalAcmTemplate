#include <iostream>
#include <cstring>
#include <queue>
#include <fstream>
using namespace std;

#define E 100005
#define V 1005
#define INF 1 << 30

int heads[V], r_heads[V];
int dists[V];
bool visits[V];

int nEdgeNum, nNodeNum, nEdgeCount;
int nEnd, nSrc, k;

struct Edge{
    int to_node;
    int next_edge;
    int edge_weight;
    int r_to_node;
    int r_next_edge;

    Edge(){}
    Edge(int from, int to, int weight){
        to_node = to;
        r_to_node = from;
        edge_weight = weight;
     }
}edges[E];

struct Node{
    int v;
    int src_to_v_dist;

    Node(){
        this->v = 0;
        this->src_to_v_dist = 0;
    }
    Node( int v, int d ){
        this->v = v;
        this->src_to_v_dist = d;
    }
    bool operator < ( const Node& other ) const{
        return src_to_v_dist + dists[v] > dists[other.v] + other.src_to_v_dist;
    }
};

void addEdge( int from, int to, int dist ){
    edges[nEdgeCount] = Edge( from, to, dist );
    edges[nEdgeCount].r_next_edge = r_heads[to];
    edges[nEdgeCount].next_edge = heads[from];
    heads[from] = nEdgeCount;
    r_heads[to] = nEdgeCount;
    nEdgeCount++;
}

void dijkstra( int src ){

    priority_queue< Node > que;

    for( int i = 1; i <= nNodeNum; i ++){
        dists[i] = INF;
    }
    dists[src] = 0;
    que.push(Node(src, 0));
    while(!que.empty()){
        Node cur = que.top();
        que.pop();
        if(visits[cur.v]){
            continue;
        }
        visits[cur.v] = true;
        for( int i = r_heads[cur.v]; ~i; i = edges[i].r_next_edge ){
            if( dists[edges[i].r_to_node] > dists[cur.v] + edges[i].edge_weight ){
                dists[edges[i].r_to_node] = dists[cur.v] + edges[i].edge_weight;
                que.push(Node(edges[i].r_to_node, 0));
            }
        }
    }
}

int AStar( int src ){
    priority_queue< Node > que;

    que.push(Node(src, 0));
    while(!que.empty()){
        Node cur = que.top();
        que.pop();
        if(cur.v == nEnd){
            if(k > 1){
                k--;
            }
            else{
                return cur.src_to_v_dist;
            }
        }
        for(int i = heads[cur.v]; ~i; i = edges[i].next_edge){
            que.push(Node(edges[i].to_node, cur.src_to_v_dist + edges[i].edge_weight));
        }
    }

    return -1;
}

void init(){
    memset(visits, false, sizeof(visits ));
    memset(heads, -1, sizeof(heads));
    memset(r_heads, -1, sizeof(r_heads));
    nEdgeCount = 0;
}

int main(){
    while(cin >> nNodeNum >> nEdgeNum){
        init();
        for(int i = 1; i <= nEdgeNum; i ++){
            int from, to, dist;

            cin >> from >> to >> dist;
            addEdge( from, to, dist );
        }
        cin >> nSrc >> nEnd >> k;
        dijkstra( nEnd );
        if(dists[nSrc] == INF){
            cout << "-1\n";

            continue;
        }

        if(nSrc == nEnd){
            k ++;
        }
        int ans = AStar(nSrc);
        cout << ans << endl;
    }

    return 0;
}
