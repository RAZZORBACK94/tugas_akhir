#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Struktur ketersediaan ruangan
struct ketersediaan
{
    int hariId;
    int jamPel;
    int ruangId;
};

// Struktur jadwal kuliah
struct jadwal
{
    int hariId;
    int jamPel;
    int ruangId;
    string mapel;
};

void tampilkanJadwal(const string hari[], int jumlahHari,
                     const jadwal* jadwalKu, int jumlahJadwal,
                     int lebarHari, int lebarJam)
{
    cout << "\nJADWAL SAYA" << endl;
    cout << string(30, '=') << endl;

    cout << left << setw(lebarHari) << "HARI/JAM" << " || ";

    // list jam
    for (int i = 1; i <= 10; i++)
    {
        stringstream jam;
        jam << setfill('0') << setw(2) << (6 + i)
            << ":00 - "
            << setw(2) << (7 + i) << ":00";

        cout << left << setfill(' ') << setw(lebarJam)
             << jam.str() << " || ";
    }

    cout << endl;
    cout << string(181, '=') << endl;

    // list hari
    for (int i = 0; i < jumlahHari; i++)
    {
        cout << left << setw(lebarHari) << hari[i] << " || ";

        // menampilkan jadwal jika ada di tiap jam
        for (int j = 1; j <= 10; j++)
        {
            bool ditemukan = false;

            for (int k = 0; k < jumlahJadwal; k++)
            {
                if (jadwalKu[k].hariId == i &&
                    jadwalKu[k].jamPel == j)
                {
                    cout << left << setw(lebarJam)
                         << jadwalKu[k].mapel << " || ";

                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan)
            {
                cout << left << setw(lebarJam)
                     << " " << " || ";
            }
        }

        cout << endl;
    }
}

void tampilkanDaftarJadwal(const string hari[], const string ruangan[],
                           const jadwal* jadwalKu, int jumlahJadwal)
{
    cout << "\n=== DAFTAR JADWAL ===" << endl;
    for (int i = 0; i < jumlahJadwal; i++)
    {
        cout << i + 1 << ". "
             << jadwalKu[i].mapel << " | "
             << hari[jadwalKu[i].hariId] << " | jam ke-"
             << jadwalKu[i].jamPel << " | ruang "
             << ruangan[jadwalKu[i].ruangId] << endl;
    }
}

bool isRuanganTersedia(const ketersediaan* ruangDipakai, int jumlahTerpakai,
                       int hariId, int jamPel, int ruangId,
                       int abaikanHari = -1, int abaikanJam = -1, int abaikanRuang = -1)
{
    for (int i = 0; i < jumlahTerpakai; i++)
    {
        if (ruangDipakai[i].hariId == abaikanHari &&
            ruangDipakai[i].jamPel == abaikanJam &&
            ruangDipakai[i].ruangId == abaikanRuang)
        {
            continue;
        }

        if (ruangDipakai[i].hariId == hariId &&
            ruangDipakai[i].jamPel == jamPel &&
            ruangDipakai[i].ruangId == ruangId)
        {
            return false;
        }
    }
    return true;
}

bool inputDetailJadwal(const string hari[], int jumlahHari,
                       const string ruangan[], int jumlahRuangan,
                       const ketersediaan* ruangDipakai, int jumlahTerpakai,
                       int& pilihHari, int& jamPel, int& pilihRuang, string& mapel,
                       int abaikanHari = -1, int abaikanJam = -1, int abaikanRuang = -1)
{
    cout << "Pilih Hari:" << endl;
    for (int i = 0; i < jumlahHari; i++)
    {
        cout << i << ". " << hari[i] << endl;
    }
    cout << "Masukkan ID Hari (0-" << (jumlahHari - 1) << "): ";
    cin >> pilihHari;

    if (cin.fail() || pilihHari < 0 || pilihHari >= jumlahHari)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Input hari tidak valid!" << endl;
        return false;
    }

    cout << "Pilih Jam Pelajaran (1-10): ";
    cin >> jamPel;

    if (cin.fail() || jamPel < 1 || jamPel > 10)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Input jam pelajaran tidak valid!" << endl;
        return false;
    }

    cin.ignore(1000, '\n'); // bersihkan newline sebelum getline
    cout << "Masukkan Nama Mapel: ";
    getline(cin, mapel);

    if (mapel.empty())
    {
        cout << "Nama mapel tidak boleh kosong!" << endl;
        return false;
    }

    // Tampilkan ruangan yang tersedia pada hari dan jam tersebut
    cout << "\nRuangan tersedia pada hari " << hari[pilihHari]
         << " jam ke-" << jamPel << ":" << endl;

    bool adaRuangan = false;
    for (int r = 0; r < jumlahRuangan; r++)
    {
        if (isRuanganTersedia(ruangDipakai, jumlahTerpakai, pilihHari, jamPel, r,
                              abaikanHari, abaikanJam, abaikanRuang))
        {
            cout << " - ID " << r << " : " << ruangan[r] << endl;
            adaRuangan = true;
        }
    }

    if (!adaRuangan)
    {
        cout << "Tidak ada ruangan yang tersedia pada waktu tersebut!" << endl;
        return false;
    }

    cout << "Masukkan ID Ruangan yang dipilih: ";
    cin >> pilihRuang;

    if (cin.fail() || pilihRuang < 0 || pilihRuang >= jumlahRuangan ||
        !isRuanganTersedia(ruangDipakai, jumlahTerpakai, pilihHari, jamPel, pilihRuang,
                           abaikanHari, abaikanJam, abaikanRuang))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Pilihan ruangan tidak valid atau sudah terpakai!" << endl;
        return false;
    }

    return true;
}

void tambahJadwal(const string hari[], int jumlahHari,
                  const string ruangan[], int jumlahRuangan,
                  jadwal*& jadwalKu, int& jumlahJadwal,
                  ketersediaan*& ruangDipakai, int& jumlahTerpakai)
{
    int pilihHari = -1;
    int jamPel = 0;
    int pilihRuang = -1;
    string mapel;

    cout << "\n=== TAMBAH JADWAL ===" << endl;
    if (!inputDetailJadwal(hari, jumlahHari, ruangan, jumlahRuangan,
                           ruangDipakai, jumlahTerpakai,
                           pilihHari, jamPel, pilihRuang, mapel))
    {
        return;
    }

    // 1. Perbesar array jadwalKu dan tambahkan jadwal baru
    jadwal* jadwalBaru = new jadwal[jumlahJadwal + 1];
    for (int i = 0; i < jumlahJadwal; i++)
    {
        jadwalBaru[i] = jadwalKu[i];
    }
    jadwalBaru[jumlahJadwal] = { pilihHari, jamPel, pilihRuang, mapel };

    delete[] jadwalKu;
    jadwalKu = jadwalBaru;
    jumlahJadwal++;

    // 2. Perbesar array ruangDipakai dan tandai ruangan terpakai
    ketersediaan* ruangBaru = new ketersediaan[jumlahTerpakai + 1];
    for (int i = 0; i < jumlahTerpakai; i++)
    {
        ruangBaru[i] = ruangDipakai[i];
    }
    ruangBaru[jumlahTerpakai] = { pilihHari, jamPel, pilihRuang };

    delete[] ruangDipakai;
    ruangDipakai = ruangBaru;
    jumlahTerpakai++;

    cout << "\nJadwal [" << mapel << "] berhasil ditambahkan pada hari "
         << hari[pilihHari] << ", jam ke-" << jamPel
         << ", di ruang " << ruangan[pilihRuang] << "!" << endl;
}

void ubahJadwal(const string hari[], int jumlahHari,
                const string ruangan[], int jumlahRuangan,
                jadwal* jadwalKu, int jumlahJadwal,
                ketersediaan*& ruangDipakai, int& jumlahTerpakai)
{
    if (jumlahJadwal == 0)
    {
        cout << "\nBelum ada jadwal yang dapat diubah!" << endl;
        return;
    }

    tampilkanDaftarJadwal(hari, ruangan, jadwalKu, jumlahJadwal);

    int pilih = 0;
    cout << "\nPilih nomor jadwal yang ingin diubah (1-" << jumlahJadwal << "): ";
    cin >> pilih;

    if (cin.fail() || pilih < 1 || pilih > jumlahJadwal)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Pilihan tidak valid!" << endl;
        return;
    }

    int index = pilih - 1;
    jadwal lama = jadwalKu[index];

    int pilihHari = -1;
    int jamPel = 0;
    int pilihRuang = -1;
    string mapel;

    cout << "\n=== INPUT JADWAL BARU ===" << endl;
    if (!inputDetailJadwal(hari, jumlahHari, ruangan, jumlahRuangan,
                           ruangDipakai, jumlahTerpakai,
                           pilihHari, jamPel, pilihRuang, mapel,
                           lama.hariId, lama.jamPel, lama.ruangId))
    {
        return;
    }

    // Update data jadwal
    jadwalKu[index] = { pilihHari, jamPel, pilihRuang, mapel };

    // Update data ketersediaan ruangan (ganti slot lama dengan slot baru)
    bool diperbarui = false;
    for (int i = 0; i < jumlahTerpakai; i++)
    {
        if (ruangDipakai[i].hariId == lama.hariId &&
            ruangDipakai[i].jamPel == lama.jamPel &&
            ruangDipakai[i].ruangId == lama.ruangId)
        {
            ruangDipakai[i] = { pilihHari, jamPel, pilihRuang };
            diperbarui = true;
            break;
        }
    }

    if (!diperbarui)
    {
        ketersediaan* ruangBaru = new ketersediaan[jumlahTerpakai + 1];
        for (int i = 0; i < jumlahTerpakai; i++)
        {
            ruangBaru[i] = ruangDipakai[i];
        }
        ruangBaru[jumlahTerpakai] = { pilihHari, jamPel, pilihRuang };

        delete[] ruangDipakai;
        ruangDipakai = ruangBaru;
        jumlahTerpakai++;
    }

    cout << "\nJadwal berhasil diubah menjadi [" << mapel << "] pada hari "
         << hari[pilihHari] << ", jam ke-" << jamPel
         << ", di ruang " << ruangan[pilihRuang] << "!" << endl;
}

void hapusJadwal(const string hari[], const string ruangan[],
                 jadwal*& jadwalKu, int& jumlahJadwal,
                 ketersediaan*& ruangDipakai, int& jumlahTerpakai)
{
    if (jumlahJadwal == 0)
    {
        cout << "\nBelum ada jadwal yang dapat dihapus!" << endl;
        return;
    }

    tampilkanDaftarJadwal(hari, ruangan, jadwalKu, jumlahJadwal);

    int pilih = 0;
    cout << "\nPilih nomor jadwal yang ingin dihapus (1-" << jumlahJadwal << "): ";
    cin >> pilih;

    if (cin.fail() || pilih < 1 || pilih > jumlahJadwal)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Pilihan tidak valid!" << endl;
        return;
    }

    int index = pilih - 1;
    jadwal terhapus = jadwalKu[index];

    // 1. Hapus elemen dari jadwalKu
    jadwal* jadwalBaru = (jumlahJadwal - 1 > 0) ? new jadwal[jumlahJadwal - 1] : nullptr;
    for (int i = 0, j = 0; i < jumlahJadwal; i++)
    {
        if (i != index)
        {
            jadwalBaru[j++] = jadwalKu[i];
        }
    }
    delete[] jadwalKu;
    jadwalKu = jadwalBaru;
    jumlahJadwal--;

    // 2. Bebaskan ruangan pada ruangDipakai
    int idxRuang = -1;
    for (int i = 0; i < jumlahTerpakai; i++)
    {
        if (ruangDipakai[i].hariId == terhapus.hariId &&
            ruangDipakai[i].jamPel == terhapus.jamPel &&
            ruangDipakai[i].ruangId == terhapus.ruangId)
        {
            idxRuang = i;
            break;
        }
    }

    if (idxRuang != -1)
    {
        ketersediaan* ruangBaru = (jumlahTerpakai - 1 > 0) ? new ketersediaan[jumlahTerpakai - 1] : nullptr;
        for (int i = 0, j = 0; i < jumlahTerpakai; i++)
        {
            if (i != idxRuang)
            {
                ruangBaru[j++] = ruangDipakai[i];
            }
        }
        delete[] ruangDipakai;
        ruangDipakai = ruangBaru;
        jumlahTerpakai--;
    }

    cout << "\nJadwal [" << terhapus.mapel << "] pada hari "
         << hari[terhapus.hariId] << ", jam ke-" << terhapus.jamPel
         << ", di ruang " << ruangan[terhapus.ruangId] << " berhasil dihapus!" << endl;
}

int main()
{
    const int jumlahHari = 5;
    string hari[jumlahHari] = {
        "senin", "selasa", "rabu", "kamis", "jumat"
    };

    const int jumlahRuangan = 10;
    string ruangan[jumlahRuangan] = {
        "A1", "A2", "A3", "A4", "A5",
        "B1", "B2", "B3", "B4", "B5"
    };

    int jumlahTerpakai = 20;
    ketersediaan* ruangDipakai = new ketersediaan[jumlahTerpakai] {
        {0, 2, 0}, // hari dipakai, jam pelajaran ke berapa, ruangan apa
        {1, 3, 1},
        {1, 4, 1},
        {2, 5, 2},
        {2, 6, 2},
        {3, 7, 3},
        {3, 8, 3},
        {4, 9, 4},
        {4, 10, 4},
        {5, 1, 1},
        {0, 1, 0},
        {1, 2, 1},
        {2, 3, 2},
        {3, 4, 3},
        {4, 5, 4},
        {0, 2, 5},
        {1, 3, 6},
        {2, 4, 7},
        {3, 5, 8},
        {4, 6, 9}
    };

    int jumlahJadwal = 10;
    jadwal* jadwalKu = new jadwal[jumlahJadwal] {
        {0, 1, 0, "MAT"},
        {0, 2, 0, "MAT"},
        {1, 3, 1, "OAK"},
        {1, 4, 1, "OAK"},
        {2, 5, 2, "PTI"},
        {2, 6, 2, "PTI"},
        {3, 7, 3, "K3"},
        {3, 8, 3, "K3"},
        {4, 9, 4, "PAI"},
        {4, 10, 4, "PAI"}
    };

    const int lebarHari = 8;
    const int lebarJam = 13;

    int menu = 0;
    do
    {
        tampilkanJadwal(hari, jumlahHari, jadwalKu, jumlahJadwal, lebarHari, lebarJam);

        cout << "\n=== MENU JADWAL ===" << endl;
        cout << "1. Lihat Daftar Jadwal" << endl;
        cout << "2. Tambah Jadwal" << endl;
        cout << "3. Ubah Jadwal" << endl;
        cout << "4. Hapus Jadwal" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> menu;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            menu = -1;
            continue;
        }

        switch (menu)
        {
            case 1:
                tampilkanDaftarJadwal(hari, ruangan, jadwalKu, jumlahJadwal);
                break;

            case 2:
                tambahJadwal(hari, jumlahHari, ruangan, jumlahRuangan,
                             jadwalKu, jumlahJadwal, ruangDipakai, jumlahTerpakai);
                break;

            case 3:
                ubahJadwal(hari, jumlahHari, ruangan, jumlahRuangan,
                           jadwalKu, jumlahJadwal, ruangDipakai, jumlahTerpakai);
                break;

            case 4:
                hapusJadwal(hari, ruangan, jadwalKu, jumlahJadwal,
                            ruangDipakai, jumlahTerpakai);
                break;

            case 0:
                cout << "Program selesai." << endl;
                break;

            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (menu != 0);

    delete[] jadwalKu;
    delete[] ruangDipakai;
    return 0;
}
