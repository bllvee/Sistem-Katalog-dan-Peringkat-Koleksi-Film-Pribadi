#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

struct Film {
    string judul;
    string sutradara;
    int tahun;
    float rating;
};

// ---------------------------
// Load data dari films.json
// ---------------------------
void loadData(vector<Film> &koleksi) {
    ifstream file("films.json");
    if (!file.is_open()) return; // kalau belum ada file, biarkan kosong

    json data;
    file >> data;

    for (auto &f : data) {
        koleksi.push_back({
            f["judul"],
            f["sutradara"],
            f["tahun"],
            f["rating"]
        });
    }
}

// ---------------------------
// Simpan ke films.json
// ---------------------------
void saveData(vector<Film> &koleksi) {
    json data = json::array();

    for (auto &f : koleksi) {
        data.push_back({
            {"judul", f.judul},
            {"sutradara", f.sutradara},
            {"tahun", f.tahun},
            {"rating", f.rating}
        });
    }

    ofstream file("films.json");
    file << data.dump(4); // indent 4 agar rapi
}

// ---------------------------
// Tambah film baru
// ---------------------------
void tambahFilmBaru(vector<Film> &koleksi) {
    Film f;
    cin.ignore();
    cout << "Masukkan Judul: ";
    getline(cin, f.judul);
    cout << "Masukkan Sutradara: ";
    getline(cin, f.sutradara);
    cout << "Masukkan Tahun Rilis: ";
    cin >> f.tahun;
    cout << "Masukkan Rating: ";
    cin >> f.rating;

    koleksi.push_back(f);
    saveData(koleksi);

    cout << "\nFilm berhasil ditambahkan & disimpan!\n";
}

// ---------------------------
// Bubble Sort berdasarkan rating (descending)
// ---------------------------
void urutkanRating(vector<Film> &koleksi) {
    for (int i = 0; i < koleksi.size() - 1; i++) {
        for (int j = 0; j < koleksi.size() - i - 1; j++) {
            if (koleksi[j].rating < koleksi[j + 1].rating) {
                swap(koleksi[j], koleksi[j + 1]);
            }
        }
    }
}

// ---------------------------
// Tampilkan 10 film terbaik
// ---------------------------
void tampilkanFilmTerbaik(vector<Film> koleksi) {
    if (koleksi.empty()) {
        cout << "Belum ada data film.\n";
        return;
    }

    urutkanRating(koleksi);
    cout << "\n=== 10 Film Terbaik ===\n";

    int batas = min(10, (int)koleksi.size());
    for (int i = 0; i < batas; i++) {
        cout << i + 1 << ". " << koleksi[i].judul
             << " (" << koleksi[i].rating << ")\n";
    }
}

// ---------------------------
// Cari detail film (sequential search)
// ---------------------------
void cariDetailFilm(vector<Film> &koleksi) {
    cin.ignore();
    string key;
    cout << "Masukkan judul film yang dicari: ";
    getline(cin, key);

    for (auto &f : koleksi) {
        if (f.judul == key) {
            cout << "\n=== Detail Film ===\n";
            cout << "Judul     : " << f.judul << endl;
            cout << "Sutradara : " << f.sutradara << endl;
            cout << "Tahun     : " << f.tahun << endl;
            cout << "Rating    : " << f.rating << endl;
            return;
        }
    }

    cout << "\nFilm tidak ditemukan.\n";
}

// ---------------------------
// Main Menu
// ---------------------------
int main() {
    vector<Film> koleksi;

    // Load otomatis ketika program mulai
    loadData(koleksi);

    int pilihan;

    do {
        cout << "\n=== Aplikasi Katalog Film Pribadi ===\n";
        cout << "1. Tambah Film Baru\n";
        cout << "2. Tampilkan Film Terbaik\n";
        cout << "3. Cari Detail Film\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahFilmBaru(koleksi);
                break;
            case 2:
                tampilkanFilmTerbaik(koleksi);
                break;
            case 3:
                cariDetailFilm(koleksi);
                break;
            case 0:
                cout << "Keluar...\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    return 0;
}
