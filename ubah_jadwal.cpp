
#include <iostream>
#include <string>
using namespace std;

struct Jadwal {
    string hari;
    string jam;
    string mapel;
    string ruangan;
};

struct Ruangan {
    string nama;
    bool tersedia;
};

Jadwal jadwalku[100] = {
    {"Senin", "08:00-10:00", "Algoritma", "Lab 1"},
    {"Selasa", "10:00-12:00", "Basis Data", "Lab 2"}
};

int jumlahJadwal = 2;

Ruangan ketersediaan[] = {
    {"Lab 1", true},
    {"Lab 2", true},
    {"Ruang 101", true},
    {"Ruang 102", true}
};

int jumlahRuangan = 4;

void tampilkanJadwal() {
    cout << "\n=== DAFTAR JADWAL ===\n";

    for (int i = 0; i < jumlahJadwal; i++) {
        cout << i + 1 << ". "
             << jadwalku[i].mapel << " | "
             << jadwalku[i].hari << " | "
             << jadwalku[i].jam << " | "
             << jadwalku[i].ruangan << endl;
    }
}

void ubahJadwal() {
    tampilkanJadwal();

    int pilih;

    cout << "\nPilih jadwal yang ingin diubah: ";
    cin >> pilih;

    if (pilih < 1 || pilih > jumlahJadwal) {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    int index = pilih - 1;

    Jadwal lama = jadwalku[index];
    Jadwal baru;

    cout << "\n=== INPUT JADWAL BARU ===\n";

    cout << "Hari baru: ";
    cin >> baru.hari;

    cout << "Jam baru: ";
    cin >> baru.jam;

    cin.ignore();

    cout << "Mata kuliah baru: ";
    getline(cin, baru.mapel);

    // Periksa ketersediaan ruangan berdasarkan
    // hari, jam, dan ruangan yang digunakan

    cout << "\n=== PILIH RUANGAN ===\n";

    for (int i = 0; i < jumlahRuangan; i++) {
        bool tersedia = true;

        for (int j = 0; j < jumlahJadwal; j++) {
            if (j != index &&
                jadwalku[j].hari == baru.hari &&
                jadwalku[j].jam == baru.jam &&
                jadwalku[j].ruangan == ketersediaan[i].nama) {

                tersedia = false;
                break;
            }
        }

        if (tersedia) {
            cout << i + 1 << ". "
                 << ketersediaan[i].nama << endl;
        }
    }

    int pilihRuangan;

    cout << "Pilih nomor ruangan: ";
    cin >> pilihRuangan;

    if (pilihRuangan < 1 || pilihRuangan > jumlahRuangan) {
        cout << "Pilihan ruangan tidak valid!\n";
        return;
    }

    string ruanganDipilih =
        ketersediaan[pilihRuangan - 1].nama;

    // Validasi ulang agar tidak terjadi bentrok

    for (int i = 0; i < jumlahJadwal; i++) {
        if (i != index &&
            jadwalku[i].hari == baru.hari &&
            jadwalku[i].jam == baru.jam &&
            jadwalku[i].ruangan == ruanganDipilih) {

            cout << "Ruangan sudah digunakan pada waktu tersebut!\n";
            return;
        }
    }

    baru.ruangan = ruanganDipilih;

    // Update data jadwal
    jadwalku[index] = baru;

    cout << "\nJadwal berhasil diubah!\n";

    tampilkanJadwal();
}

int main() {
    int pilihan;

    do {
        cout << "\n=== MENU UBAH JADWAL ===\n";
        cout << "1. Lihat Jadwal\n";
        cout << "2. Ubah Jadwal\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanJadwal();
                break;

            case 2:
                ubahJadwal();
                break;

            case 0:
                cout << "Program selesai.\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 0);

    return 0;
}
