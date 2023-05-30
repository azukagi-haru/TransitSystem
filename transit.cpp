#include "KRL_init.h"       // Inisialisasi untuk sistem transit KRL
using namespace std;

// Di sini, graph merepresentasikan suatu sistem transit, 
// Node merepresentasikan suatu stasiun/halte, 
// dan edge merepresentasikan koneksi antara dua stasiun.

// === BEBERAPA FUNGSI ===
// Untuk keperluan algoritma deteksi transit

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

// === KODE UTAMA ===
int main() {
    
    // Inisialisasi KRL dengan KRL_init.h
    Graph KRL = initializeKRLGraph();

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
    cout << "Masukan Stasiun Asal Anda: "; getline(cin, a);         // Baca keseluruhan baris karena ada nama stasiun yang ada spasi-nya
    cout << "<><><><><><><><><><><><><><><><><>" << endl;
    cout << "Masukan Stasiun Tujuan Anda: "; getline(cin, b);
    cout << ("\n");

    // Cari rute terpendek dengan BFS
    Node st_awal = KRL.getNodeByName(a);
    Node st_akhir = KRL.getNodeByName(b);

    vector<Node> path = KRL.bfs(st_awal, st_akhir);
    
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
