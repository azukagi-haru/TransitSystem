
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <unordered_map>
#include <string>

using namespace std;

// Di sini, graph merepresentasikan suatu sistem transit, 
// Node merepresentasikan suatu stasiun/halte, 
// dan edge merepresentasikan koneksi antara dua stasiun.

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

            // initialize visited array and queue for BFS
            unordered_map<string, bool> visited;
            queue<string> q;

            // find the start and end nodes in the nodes vector
            Node startNode, endNode;
            for (auto node : nodes) {
                if (node.getID() == start.getID())
                    startNode = node;
                if (node.getID() == end.getID())
                    endNode = node;
            }

            // push the start node onto the queue and mark as visited
            q.push(startNode.getID());
            visited[startNode.getID()] = true;

            // initialize path map and add start node
            unordered_map<string, string> path;
            for (auto node : nodes)
                path[node.getID()] = "";
            path[startNode.getID()] = startNode.getID();

            while (!q.empty()) {
                // get the front node from the queue
                string current = q.front();
                q.pop();

                // iterate over the neighbors of the current node
                for (auto neighbor : adj[current]) {
                    // if neighbor has not been visited, mark as visited, add to queue, and update path
                    if (!visited[neighbor]) {
                        q.push(neighbor);
                        visited[neighbor] = true;
                        path[neighbor] = current;
                    }
                }

                // if we have reached the end node, backtrack to find the path and return it
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
                        
                        // if nodeID != prevNodeID --> prevNodeID --> switch == true
                        
                        shortestPath.push_back(getNodeById(nodeId));

                        // for (auto node : nodes) {
                        //     if (node.getID() == nodeId) {
                        //         shortestPath.push_back(node);
                        //         break;
                        //     }
                        // }

                        s.pop();
                    }
                    return shortestPath;
                }
            }

            // if we have not reached the end node, return an empty array
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

// Diberikan dua set berisi string, return subset yang common dari kedua set
set<string> findCommonSubset(const set<string>& set1, const set<string>& set2) {
    set<string> commonSubset;
    for (const string& str : set1) {
        if (set2.count(str) > 0) {
            commonSubset.insert(str);
        }
    }
    return commonSubset;
}

// Cek dari dua set berisi string, apakah ada setidaknya satu elemen yang common?
bool hasCommonSubset(const set<string>& set1, const set<string>& set2) {
    for (const string& str : set1) {
        if (set2.count(str) > 0) {
            return true;
        }
    }
    return false;
}

// KODE UTAMA
int main() {

    int V = 50;         // Jumlah node/stasiun
    Graph g(V);         // Sistem transit KRL

    // ###################
    // INISIALISASI GRAPH
    // ###################

    // Kode Line/Rute
    // B    -->     Jakarta Kota - Bogor
    // CM   -->     Kampung Bandan - Cikarang via Manggarai
    // CP   -->     Kampung Bandan - Cikarang via Pasar Senen

    // Add stasiun untuk Bogor Line
    vector<Node> bogor_line = {
		{"B00", "Jakarta Kota", {"B"}},
		{"B01", "Jayakarta", {"B"}},
		{"B02", "Mangga Besar", {"B"}},
		{"B03", "Sawah Besar", {"B"}},
		{"B04", "Juanda", {"B"}},
		{"B05", "Gondangdia", {"B"}},
		{"B06", "Cikini", {"B"}},
		{"B07", "Manggarai", {"B", "CM"}},
		{"B08", "Tebet", {"B"}},
		{"B09", "Cawang", {"B"}},
		{"B10", "Duren Kalibata", {"B"}},
		{"B11", "Pasar Minggu Baru", {"B"}},
		{"B12", "Pasar Minggu", {"B"}},
		{"B13", "Tanjung Barat", {"B"}},
		{"B14", "Lenteng Agung", {"B"}},
		{"B15", "Univ. Pancasila", {"B"}},
		{"B16", "Univ. Indonesia", {"B"}},
		{"B17", "Pondok Cina", {"B"}},
		{"B18", "Depok Baru", {"B"}},
		{"B19", "Depok", {"B"}},
		{"B20", "Citayam", {"B"}},
		{"B21", "Bojong Gede", {"B"}},
		{"B22", "Cilebut", {"B"}},
		{"B23", "Bogor", {"B"}}
    };

    for (const Node& node : bogor_line) {
        g.addNode(node);
    }

    // Add koneksi untuk Bogor Line
    g.addEdge("B00", "B01");
    g.addEdge("B01", "B02");
    g.addEdge("B02", "B03");
    g.addEdge("B03", "B04");
    g.addEdge("B04", "B05");
    g.addEdge("B05", "B06");
    g.addEdge("B06", "B07");    // Manggarai
    g.addEdge("B07", "B08");    // Manggarai
    g.addEdge("B08", "B09");
    g.addEdge("B09", "B10");
    g.addEdge("B10", "B11");
    g.addEdge("B11", "B12");
    g.addEdge("B12", "B13");
    g.addEdge("B13", "B14");
    g.addEdge("B14", "B15");
    g.addEdge("B15", "B16");
    g.addEdge("B16", "B17");
    g.addEdge("B17", "B18");
    g.addEdge("B18", "B19");
    g.addEdge("B19", "B20");
    g.addEdge("B20", "B21");
    g.addEdge("B21", "B22");
    g.addEdge("B22", "B23");

    // Add stasiun untuk Cikarang Line
    vector<Node> cikarang_line = {
		{"C00", "Kampung Bandan", {"CM", "CP"}},
		{"C01", "Rajawali", {"CP"}},
		{"C02", "Kemayoran", {"CP"}},
		{"C03", "Pasar Senen", {"CP"}},
		{"C04", "Gang Sentiong", {"CP"}},
		{"C05", "Kramat", {"CP"}},
		{"C06", "Pondok Jati", {"CP"}},
		{"C07", "Angke", {"CM"}},
		{"C08", "Duri", {"CM"}},
		{"C09", "Tanah Abang", {"CM"}},
		{"C10", "Karet", {"CM"}},
		{"C11", "BNI City", {"CM"}},
		{"C12", "Sudirman", {"CM"}},
		{"C13", "Matraman", {"CM"}},
		{"C14", "Jatinegara", {"CM", "CP"}},
		{"C15", "Klender", {"CM", "CP"}},
		{"C16", "Buaran", {"CM", "CP"}},
		{"C17", "Klender Baru", {"CM", "CP"}},
		{"C18", "Cakung", {"CM", "CP"}},
		{"C19", "Kranji", {"CM", "CP"}},
		{"C20", "Bekasi", {"CM", "CP"}},
		{"C21", "Bekasi Timur", {"CM", "CP"}},
		{"C22", "Tambun", {"CM", "CP"}},
		{"C23", "Cibitung", {"CM", "CP"}},
		{"C24", "Metland Telaga Murni", {"CM", "CP"}},
		{"C25", "Cikarang", {"CM", "CP"}}
    };

    for (const Node& node : cikarang_line) {
        g.addNode(node);
    }

    // Add koneksi untuk Cikarang Line
    // Kampung Bandan via Pasar Senen
	g.addEdge("C00", "C01");
    g.addEdge("C01", "C02");
    g.addEdge("C02", "C03");
    g.addEdge("C03", "C04");
    g.addEdge("C04", "C05");
    g.addEdge("C05", "C06");
    g.addEdge("C06", "C14");	// Jatinegara

    // Kampung Bandan via Manggarai
    g.addEdge("C00", "C07");
    g.addEdge("C07", "C08");
    g.addEdge("C08", "C09");
    g.addEdge("C09", "C10");
    g.addEdge("C10", "C11");
    g.addEdge("C11", "C12");
    g.addEdge("C12", "B07");	// Manggarai
    g.addEdge("B07", "C13");
    g.addEdge("C13", "C14");	// Jatinegara

    // Jatinegara - Cikarang
    g.addEdge("C14", "C15");
    g.addEdge("C15", "C16");
    g.addEdge("C16", "C17");
    g.addEdge("C17", "C18");
    g.addEdge("C18", "C19");
    g.addEdge("C19", "C20");
    g.addEdge("C20", "C21");
    g.addEdge("C21", "C22");
    g.addEdge("C22", "C23");
    g.addEdge("C23", "C24");
    g.addEdge("C24", "C25");


    // ###################
    // USER INTERFACE
    // ###################
    
    // Ambil stasiun awal dan akhir
    string a,b;
    cout << ("\n");
    cout << ("<><><><><><><><><><><><><><><><><>\n");
    cout << ("<>  SELAMAT DATANG PADA PROGRAM <>\n");
    cout << ("<>          KRL TRANSIT         <>\n");
    cout << ("<> 'teman perjalanan krl anda'  <>\n");
    cout << ("<><><><><><><><><><><><><><><><><>\n");
    cout << ("\n");
    cout << "Pencarian Rute KRL" << endl;
    cout << "Masukan Stasiun Asal Anda: "; getline(cin, a);         // Baca keseluruhan line karena ada nama stasiun yang ada spasi-nya
    cout << "<><><><><><><><><><><><><><><><><>" << endl;
    cout << "Masukan Stasiun Tujuan Anda: "; getline(cin, b);
    cout << ("\n");

    // Cari rute terpendek dengan BFS
    Node st_awal = g.getNodeByName(a);
    Node st_akhir = g.getNodeByName(b);

    vector<Node> path = g.bfs(st_awal, st_akhir);
    
    // Print Hasil dengan mempertimbangkan di mana stasiun transit
    if (path.empty())
        cout << "Error! Tidak ada rute yang ditemukan antara dua stasiun tersebut!" << endl;
    else {
        cout << "==========RUTE PERJALANAN==========" << endl; 

        Node node, nextNode;
        set<string> commonlines;
        set<string> prev_commonlines = path[0].getLines();

        for (int i=0; i<path.size()-1; i++) {

            node = path[i];
            nextNode = path[i+1];

            // ALGORITMA deteksi transit:
            // Baca node dan nextNode, ambil line_served dari kedua node, bandingkan, subset yang sama masuk ke "commonlines"
            // "commonlines" dibandingkan dengan "prev_commonlines"
            // Stasiun TRANSIT adalah ketika antara "commonlines" dan "prev_commonlines" tidak memiliki common subset

            commonlines =  findCommonSubset(node.getLines(), nextNode.getLines());
            if (!hasCommonSubset(commonlines, prev_commonlines)) {
                cout << "===================================" << endl; 
                cout << "        TRANSIT DI STASIUN: " << endl;          // print indikasi bahwa transit telah terjadi
                cout << "                |" << endl; 
                cout << "============";
                cout << node.getName();     // print nama stasiun transit
                cout << "============" << endl;
                cout << "                |" << endl; 
                cout << "    NAIK KEMBALI DARI STASIUN: " << endl;   
                cout << "===================================" << endl;    

            }
            prev_commonlines = commonlines;

            // Print nama stasiun [NOTE: Stasiun TRANSIT namanya di-print dua kali]
            cout << node.getName() << endl;
        }

        // Print stasiun terakhir
        cout << path[path.size()-1].getName() << endl;
        cout << "========ANDA TIBA DI TUJUAN========" << endl;
    }

    return 0;
}
