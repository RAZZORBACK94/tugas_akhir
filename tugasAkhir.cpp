
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

int main()
{
    string hari[5] = {
        "senin", "selasa", "rabu", "kamis", "jumat"
    };

    string ruangan[10] = {
        "A1", "A2", "A3", "A4", "A5",
        "B1", "B2", "B3", "B4", "B5"
    };

    ketersediaan* ruangDipakai = new ketersediaan[20] {
        {0, 2, 0}, // hari dipakai, jam pelajaran ke barapa, ruangan apa
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

    jadwal* jadwalKu = new jadwal[10] {
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

    // Garis pemisah
    cout << string(181, '=') << endl;

    // list hari
    for (int i = 0; i < 5; i++)
    {
        cout << left << setw(lebarHari) << hari[i] << " || ";

        //menampilkan jadwal jika ada di tiap jam
        for (int j = 1; j <= 10; j++)
        {
            bool ditemukan = false;

            // Mencari jadwal yang sesuai
            for (int k = 0; k < 10; k++)
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

            // Jika tidak ada jadwal
            if (!ditemukan)
            {
                cout << left << setw(lebarJam)
                     << " " << " || ";
            }
        }

        cout << endl;
    }


    delete[] jadwalKu;
    delete[] ruangDipakai;
    return 0;
}
