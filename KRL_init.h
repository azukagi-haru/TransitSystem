#ifndef KRL_INIT_H
#define KRL_INIT_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

// Definisi dari node pada graph (untuk merepresentasikan stasiun, dsb)
class Node {
    private:
        string id;
        string name;
        set<string> lines_served;
    public:
        Node(string i="", string n="", set<string> lines={}) { id=i; name=n; lines_served=lines; } 
        string getID() { return id; }
        string getName() { return name; }
        set<string> getLines() { return lines_served; }
};

// Definisi graph dengan representasi adjacency list
class Graph {
    private:
        int V;                                      // jumlah node pada graph
        vector<Node> nodes;                         // vector yang berisi semua node pada graph
        unordered_map<string, Node> node_ids; 
        unordered_map<string, Node> node_names;     // map untuk translate dari "nama" node ke node-nya itu sendiri
        unordered_map<string, vector<string>> adj;  // map untuk adjacency list

    public:
        // constructor
        Graph(int V) { this->V = V; adj.clear(); }

        // tambahkan node pada graph
        void addNode(Node node) {
            nodes.push_back(node);              // tambah node ke vector "nodes"
            node_names[node.getName()] = node;  // tambah node dan id-nya ke map "node_names"
            node_ids[node.getID()] = node;
        }

        // tambahkan edge pada graph (untuk masuk ke adjacency list)
        void addEdge(string u, string v) {
            adj[u].push_back(v);                // tambah v ke list-nya u
            adj[v].push_back(u);                // tambah u ke list-nya v --> dengan begini, kedua node saling terkoneksi
        }

        // fungsi untuk return node jika nama-nya diketahui >>> Kalo ga ketemu, kasih error message
        Node getNodeByName(string name) {
            return node_names.at(name);
        }

        Node getNodeById(string id) {
            return node_ids.at(id);
        }

        // mencari path paling pendek dalam graph antara dua node dengan BFS
        vector<Node> bfs(Node start, Node end) {

            // insialisasi array dan queue untuk BFS
            unordered_map<string, bool> visited;
            queue<string> q;

            // cari start node dan end node
            Node startNode, endNode;
            for (auto node : nodes) {
                if (node.getID() == start.getID())
                    startNode = node;
                if (node.getID() == end.getID())
                    endNode = node;
            }

            // push start node ke queue dan tandai sebagai "visited"
            q.push(startNode.getID());
            visited[startNode.getID()] = true;

            // inisialisasi map untuk path
            unordered_map<string, string> path;
            for (auto node : nodes)
                path[node.getID()] = "";
            path[startNode.getID()] = startNode.getID();

            while (!q.empty()) {
                // ambil node terdepan dari queue
                string current = q.front();
                q.pop();

                // iterasi ke seluruh neighbor dari node saat ini
                for (auto neighbor : adj[current]) {
                    //jika belum "visited", tandai sebagai "visited", add ke queue, dan update path
                    if (!visited[neighbor]) {
                        q.push(neighbor);
                        visited[neighbor] = true;
                        path[neighbor] = current;
                    }
                }

                // jika sudah sampai end node, backtrack untuk mendapatkan path dan return path tersebut
                if (current == endNode.getID()) {
                    stack<string> s;
                    string node = endNode.getID();
                    while (node != startNode.getID()) {
                        s.push(node);
                        node = path[node];
                    }
                    s.push(startNode.getID());

                    vector<Node> shortestPath;

                    while (!s.empty()) {
                        string nodeId = s.top();
                        shortestPath.push_back(getNodeById(nodeId));
                        s.pop();
                    }
                    return shortestPath;
                }
            }

            // jika belum mencapai end node, return array kosong
            return {};
        }

        // print adjacency list dari graph
        void printList() {
            for (auto i : nodes) {
                string id = i.getID();
                cout << id << ": ";
                for (auto j : adj.at(id))
                    cout << j << " ";
                cout << endl;
            }
        }
};

// Instansiasi Graph untuk KRL
Graph initializeKRLGraph();

#endif