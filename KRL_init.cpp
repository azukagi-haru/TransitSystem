#include "KRL_init.h"

// ###################
// INISIALISASI GRAPH
// ###################

// Kode Line/Rute
// B    -->     Jakarta Kota - Bogor
// CM   -->     Kampung Bandan - Cikarang via Manggarai
// CP   -->     Kampung Bandan - Cikarang via Pasar Senen
// TP   -->     Jakarta Kota - Tanjung Priok
// T    -->     Duri - Tangerang
// R    -->     Tanah Abang - Rangkasbitung
// N    -->     Citayam - Nambo

// Jika mau menambah line baru, perhatikan:
// 1. Tambahkan vector baru vector<Node> nama_line, isi dengan kode line
// 2. Update kode line pada stasiun-stasiun transit
// 3. Tambahkan loop untuk memasukkan ke graph
// 4. Tambahkan koneksi dengan .addEdge()

// Add stasiun untuk Bogor Line
vector<Node> bogor_line = {
    {"B00", "Jakarta Kota", {"B", "TP"}},
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
    {"B20", "Citayam", {"B", "N"}},
    {"B21", "Bojong Gede", {"B"}},
    {"B22", "Cilebut", {"B"}},
    {"B23", "Bogor", {"B"}}
};

// Add stasiun untuk Cikarang Line
vector<Node> cikarang_line = {
    {"C00", "Kampung Bandan", {"CM", "CP", "TP"}},
    {"C01", "Rajawali", {"CP"}},
    {"C02", "Kemayoran", {"CP"}},
    {"C03", "Pasar Senen", {"CP"}},
    {"C04", "Gang Sentiong", {"CP"}},
    {"C05", "Kramat", {"CP"}},
    {"C06", "Pondok Jati", {"CP"}},
    {"C07", "Angke", {"CM"}},
    {"C08", "Duri", {"CM", "T"}},
    {"C09", "Tanah Abang", {"CM", "R"}},
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

// Add stasiun untuk Tanjung Priok Line
vector<Node> tanjung_priok_line = {
    {"TP00", "Ancol", {"TP"}},
    {"TP01", "Tanjung Priok", {"TP"}},
};

// Add stasiun untuk Nambo Line
vector<Node> nambo_line = {
    {"N00", "Cibinong", {"N"}},
    {"N01", "Nambo", {"N"}},
};

// Add stasiun untuk Tangerang Line
vector<Node> tangerang_line = {
    {"T00", "Grogol", {"T"}},
    {"T01", "Pesing", {"T"}},
    {"T02", "Taman Kota", {"T"}},
    {"T03", "Bojong Indah", {"T"}},
    {"T04", "Rawa Buaya", {"T"}},
    {"T05", "Kalideres", {"T"}},
    {"T06", "Poris", {"T"}},
    {"T07", "Batu Ceper", {"T"}},
    {"T08", "Tanah Tinggi", {"T"}},
    {"T09", "Tangerang", {"T"}}, 
};

// Add stasiun untuk Rangkasbitung Line
vector<Node> rangkasbitung_line = {
    {"R00", "Palmerah", {"R"}},
    {"R01", "Kebayoran", {"R"}},
    {"R02", "Pondok Ranji", {"R"}},
    {"R03", "Jurangmangu", {"R"}},
    {"R04", "Sudimara", {"R"}},
    {"R05", "Rawa Buntu", {"R"}},
    {"R06", "Serpong", {"R"}},
    {"R07", "Cisauk", {"R"}},
    {"R08", "Cicayur", {"R"}},
    {"R09", "Parung Panjang", {"R"}}, 
    {"R10", "Cilejit", {"R"}},
    {"R11", "Daru", {"R"}},
    {"R12", "Tenjo", {"R"}}, 
    {"R13", "Tigaraksa", {"R"}},
    {"R14", "Cikoya", {"R"}}, 
    {"R15", "Maja", {"R"}},
    {"R16", "Citeras", {"R"}}, 
    {"R17", "Rangkasbitung", {"R"}}, 
};

// Menambahkan stasiun yang ada ke dalam graph, serta
// Menambahkan koneksi antar stasiun
Graph initializeKRLGraph() {
    int V = 100;        // Jumlah node/stasiun
    Graph KRL(V);       // Sistem transit KRL

    // Add stasiun dari stations.h ke dalam graph KRL
    for (const Node& node : bogor_line) {
        KRL.addNode(node);
    }

    for (const Node& node : cikarang_line) {
        KRL.addNode(node);
    }

    for (const Node& node : tanjung_priok_line) {
        KRL.addNode(node);
    }

    for (const Node& node : nambo_line) {
        KRL.addNode(node);
    }

    for (const Node& node : tangerang_line) {
        KRL.addNode(node);
    }

    for (const Node& node : rangkasbitung_line) {
        KRL.addNode(node);
    }

    /* === BOGOR LINE === */
    KRL.addEdge("B00", "B01");
    KRL.addEdge("B01", "B02");
    KRL.addEdge("B02", "B03");
    KRL.addEdge("B03", "B04");
    KRL.addEdge("B04", "B05");
    KRL.addEdge("B05", "B06");
    KRL.addEdge("B06", "B07");    // Manggarai
    KRL.addEdge("B07", "B08");
    KRL.addEdge("B08", "B09");
    KRL.addEdge("B09", "B10");
    KRL.addEdge("B10", "B11");
    KRL.addEdge("B11", "B12");
    KRL.addEdge("B12", "B13");
    KRL.addEdge("B13", "B14");
    KRL.addEdge("B14", "B15");
    KRL.addEdge("B15", "B16");
    KRL.addEdge("B16", "B17");
    KRL.addEdge("B17", "B18");
    KRL.addEdge("B18", "B19");
    KRL.addEdge("B19", "B20");
    KRL.addEdge("B20", "B21");
    KRL.addEdge("B21", "B22");
    KRL.addEdge("B22", "B23");


    /* === CIKARANG LINE === */
    KRL.addEdge("C00", "C01");  // Kampung Bandan
    KRL.addEdge("C01", "C02");
    KRL.addEdge("C02", "C03");  // Pasar Senen
    KRL.addEdge("C03", "C04");
    KRL.addEdge("C04", "C05");
    KRL.addEdge("C05", "C06");
    KRL.addEdge("C06", "C14");	// Jatinegara

    KRL.addEdge("C00", "C07");  // Kampung Bandan
    KRL.addEdge("C07", "C08");
    KRL.addEdge("C08", "C09");
    KRL.addEdge("C09", "C10");
    KRL.addEdge("C10", "C11");
    KRL.addEdge("C11", "C12");
    KRL.addEdge("C12", "B07");	// Manggarai
    KRL.addEdge("B07", "C13");
    KRL.addEdge("C13", "C14");	// Jatinegara

    KRL.addEdge("C14", "C15");  // Jatinegara
    KRL.addEdge("C15", "C16");
    KRL.addEdge("C16", "C17");
    KRL.addEdge("C17", "C18");
    KRL.addEdge("C18", "C19");
    KRL.addEdge("C19", "C20");
    KRL.addEdge("C20", "C21");
    KRL.addEdge("C21", "C22");
    KRL.addEdge("C22", "C23");
    KRL.addEdge("C23", "C24");
    KRL.addEdge("C24", "C25");  // Cikarang


    /* === TANJUNG PRIOK LINE === */
    KRL.addEdge("B00", "C00");  // Jakarta Kota
    KRL.addEdge("C00", "TP00"); // Kampung Bandan
    KRL.addEdge("TP00", "TP01");

    /* === NAMBO LINE === */
    KRL.addEdge("B20", "N00");  // Citayam
    KRL.addEdge("N00", "N01");

    /* === TANGERANG LINE === */
    KRL.addEdge("C08", "T00");  // Duri
    KRL.addEdge("T00", "T01");
    KRL.addEdge("T01", "T02");
    KRL.addEdge("T02", "T03");
    KRL.addEdge("T03", "T04");
    KRL.addEdge("T04", "T05");
    KRL.addEdge("T05", "T06");
    KRL.addEdge("T06", "T07");
    KRL.addEdge("T07", "T08");
    KRL.addEdge("T08", "T09");

    /* === RANGKASBITUNG LINE === */
    KRL.addEdge("C09", "R00");  // Tanah Abang
    KRL.addEdge("R00", "R01");
    KRL.addEdge("R01", "R02");
    KRL.addEdge("R02", "R03");
    KRL.addEdge("R03", "R04");
    KRL.addEdge("R04", "R05");
    KRL.addEdge("R05", "R06");
    KRL.addEdge("R06", "R07");
    KRL.addEdge("R07", "R08");
    KRL.addEdge("R08", "R09");
    KRL.addEdge("R09", "R10");
    KRL.addEdge("R10", "R11");
    KRL.addEdge("R11", "R12");
    KRL.addEdge("R12", "R13");
    KRL.addEdge("R13", "R14");
    KRL.addEdge("R14", "R15");
    KRL.addEdge("R15", "R16");
    KRL.addEdge("R16", "R17");

    return KRL;
}
