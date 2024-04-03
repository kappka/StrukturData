#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Struct untuk menu
struct Menu {
    int nomor;
    string nama;
    int harga;
};

// Struct untuk node dalam linked list pesanan
struct Node {
    int nomorMenu;
    string namaMenu;
    int harga;
    int jumlah;  // Tambahkan ini
    string catatan;
    Node* next;
};

// Fungsi untuk menambah node ke linked list
void tambahPesanan(Node*& head, int nomorMenu, string namaMenu, int harga, int jumlah) {
    Node* newNode = new Node{nomorMenu, namaMenu, harga, jumlah, "", nullptr};
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Fungsi untuk menghapus pesanan dari linked list
void hapusPesanan(Node*& head, int nomorMenu) {
    Node *temp = head, *prev = nullptr;
    if (temp != nullptr && temp->nomorMenu == nomorMenu) {
        head = temp->next;
        delete temp;
        return;
    }
    while (temp != nullptr && temp->nomorMenu != nomorMenu) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr) return;
    prev->next = temp->next;
    delete temp;
}

// Fungsi untuk menambahkan catatan ke pesanan tertentu
void tambahCatatan(Node* head, int nomorMenu, string catatan) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->nomorMenu == nomorMenu) {
            temp->catatan = catatan;
            break;
        }
        temp = temp->next;
    }
}

// Fungsi untuk menampilkan pesanan
void tampilkanPesanan(Node* head) {
    cout << "\nDaftar Pesanan Anda:\n";
    cout << left << setw(5) << "No" << setw(20) << "Nama Menu" << setw(10) << "Harga" << setw(10) << "Jumlah" << "Catatan" << endl;
    Node* temp = head;
    while (temp != nullptr) {
        cout << setw(5) << temp->nomorMenu << setw(20) << temp->namaMenu << setw(10) << temp->harga << setw(10) << temp->jumlah << temp->catatan << endl;
        temp = temp->next;
    }
}

// Array menu makanan dan minuman
Menu makanan[10] = {{1, "Nasi Goreng", 15000}, {2, "Mie Goreng", 12000}, {3, "Ayam Goreng", 20000}, {4, "Nasi Padang", 25000}, {5, "Sate Ayam", 18000}, {6, "Soto Ayam", 17000}, {7, "Bakso", 15000}, {8, "Rawon", 20000}, {9, "Gado-Gado", 16000}, {10, "Rendang", 30000}};
Menu minuman[6] = {{11, "Air Mineral", 3000}, {12, "Es Teh", 5000}, {13, "Es Jeruk", 6000}, {14, "Es Cincau", 7000}, {15, "Es Campur", 10000}, {16, "Es Kopi", 8000}};

// Fungsi untuk menampilkan menu
void tampilkanMenu() {
    cout << "Menu Makanan:\n";
    cout << left << setw(5) << "No" << setw(20) << "Nama" << "Harga" << endl;
    for (const auto& item : makanan) {
        cout << setw(5) << item.nomor << setw(20) << item.nama << item.harga << endl;
    }
    cout << "\nMenu Minuman:\n";
    for (const auto& item : minuman) {
        cout << setw(5) << item.nomor << setw(20) << item.nama << item.harga << endl;
    }
}

int main() {
    Node* head = nullptr; // Linked list untuk pesanan
    int pilihan;
    tampilkanMenu();

    do {
        cout << "\n1. Tambah Pesanan\n2. Hapus Pesanan\n3. Tambahkan Catatan\n4. Selesai\nPilih menu: ";
        cin >> pilihan;
        if (pilihan == 1) {
            int nomorMenu, jumlah;
            cout << "Masukkan nomor menu: ";
            cin >> nomorMenu;
            cout << "Masukkan jumlah pesanan: ";
            cin >> jumlah;
            bool found = false;
            for (const auto& item : makanan) {
                if (item.nomor == nomorMenu) {
                    tambahPesanan(head, item.nomor, item.nama, item.harga, jumlah);
                    found = true;
                    break;
                }
            }
            if (!found) {
                for (const auto& item : minuman) {
                    if (item.nomor == nomorMenu) {
                        tambahPesanan(head, item.nomor, item.nama, item.harga, jumlah);
                        break;
                    }
                }
            }
        } else if (pilihan == 2) {
            int nomorMenu;
            cout << "Masukkan nomor menu yang ingin dihapus: ";
            cin >> nomorMenu;
            hapusPesanan(head, nomorMenu);
        } else if (pilihan == 3) {
            int nomorMenu;
            string catatan;
            cout << "Masukkan nomor menu untuk menambahkan catatan: ";
            cin >> nomorMenu;
            cin.ignore(); // Mengabaikan newline yang tersisa
            cout << "Masukkan catatan: ";
            getline(cin, catatan);
            tambahCatatan(head, nomorMenu, catatan);
        } else if (pilihan == 4) {
            int totalHarga = 0; // Menyimpan total harga pesanan
            // Hitung total harga pesanan sebelum menampilkan pesanan
            Node* temp = head;
            while (temp != nullptr) {
                totalHarga += temp->harga * temp->jumlah;
                temp = temp->next;
            }

            // Tampilkan pesanan dan total harga
            tampilkanPesanan(head);
            cout << "Total Harga: Rp" << totalHarga << endl;
            cout << "\nTerima kasih telah memesan di Rumah Makan KALAA. Selamat menikmati!\n";
            break;
        }
    } while (true);

    // Cleanup memory
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}