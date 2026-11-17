#include <iostream>
using namespace std;

struct nodeQueue
{
    int kode;
    string nama;
    nodeQueue *next;
};

struct nodeStack
{
    int kode;
    string nama;
    nodeStack *next;
};

struct nodeTree
{
    int kode;
    string nama;
    nodeTree *kiri;
    nodeTree *kanan;
};

nodeQueue *front = NULL;
nodeQueue *last = NULL;
nodeStack *top = NULL;
nodeTree *root = NULL;

nodeTree *tambah_tree(nodeTree *akar, int kode, string nama)
{
    if (akar == NULL)
    {
        return new nodeTree{kode, nama, NULL};
    }
    if (kode < akar->kode)
    {
        akar->kiri = tambah_tree(akar->kiri, kode, nama);
    }
    if (kode > akar->kode)
    {
        akar->kanan = tambah_tree(akar->kanan, kode, nama);
    }
    return akar;
}

nodeTree *cari_tree(nodeTree *akar, int kode)
{
    if (akar == NULL || akar->kode == kode)
    {
        return akar;
    }
    if (kode < akar->kode)
    {
        return cari_tree(akar->kanan, kode);
    }
    return cari_tree(akar->kanan, kode);
}

nodeTree *hapus_tree(nodeTree *akar, int kode)
{
    if (akar == NULL)
    {
        return NULL;
    }
    if (kode < akar->kode)
    {
        akar->kiri = hapus_tree(akar->kiri, kode);
    }
    else if (kode > akar->kode)
    {
        akar->kanan = hapus_tree(akar->kanan, kode);
    }
    else if (akar->kiri == NULL)
    {
        nodeTree *bantu = akar->kanan;
        delete akar;
        return bantu;
    }
    else if (akar->kanan == NULL)
    {
        nodeTree *bantu = akar->kiri;
        delete akar;
        return bantu;
    }
    else
    {
        nodeTree *pengganti = akar->kanan;
        while (pengganti->kiri != NULL)
        {
            pengganti = pengganti->kiri;
        }
        akar->kode = pengganti->kode;
        akar->nama = pengganti->nama;
        akar->kanan = hapus_tree(akar->kanan, pengganti->kode);
    }
    return akar;
}

void preorder(nodeTree *akar, int &no)
{
    if (akar == NULL)
    {
        return;
    }
    cout << no << ". [" << akar->kode << "] " << akar->nama << endl;
    no++;
    preorder(akar->kiri, no);
    preorder(akar->kanan, no);
}

void inorder(nodeTree *akar, int &no)
{
    if (akar == NULL)
    {
        return;
    }
    inorder(akar->kiri, no);
    cout << no << ". [" << akar->kode << "] " << akar->nama << endl;
    no++;

    inorder(akar->kanan, no);
}
void postorder(nodeTree *akar, int &no)
{
    if (akar == NULL)
    {
        return;
    }
    postorder(akar->kiri, no);
    postorder(akar->kanan, no);
    cout << no << ". [" << akar->kode << "] " << akar->nama << endl;
    no++;
}

void tambah_energi()
{
    int kode;
    string nama;
    cout << "Masukkan kode energi: ";
    cin >> kode;
    if (cin.fail() || kode <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Kode harus berupa angka lebih dari 0!" << endl
             << endl;
        return;
    }

    nodeQueue *q = front;
    while (q != NULL)
    {
        if (q->kode == kode)
        {
            cout << "Kode sudah ada!" << endl
                 << endl;
            return;
        }
        q = q->next;
    }

    nodeStack *s = top;
    while (s != NULL)
    {
        if (s->kode == kode)
        {
            cout << "Kode sudah ada!" << endl
                 << endl;
            return;
        }
        s = s->next;
    }

    cout << "Masukkan nama energi: ";
    cin >> nama;
    if (nama.empty())
    {
        cout << "Nama energi tidak boleh kosong!" << endl
             << endl;
        return;
    }

    nodeQueue *n = new nodeQueue{kode, nama, NULL};
    if (front == NULL)
    {
        front = last = n;
    }
    else
    {
        last->next = n;
        last = n;
    }
    cout << "Berhasil memasukkan energi!" << endl
         << endl;
}

void lihat_antrean()
{
    if (front == NULL)
    {
        cout << "Antrean masih kosong!" << endl
             << endl;
        return;
    }
    cout << "=== Energi Dalam Antrean ===" << endl
         << endl;
    nodeQueue *n = front;
    int no = 1;
    while (n != NULL)
    {
        cout << no << ". [" << n->kode << "] " << n->nama << endl;
        n = n->next;
        no++;
    }
    cout << endl;
}

void hapus_riwayat()
{
    if (top == NULL)
    {
        cout << "Belum ada energi yang terserap!" << endl
             << endl;
        return;
    }
    nodeStack *bantu = top;
    top = top->next;
    cout << "Riwayat energi " << bantu->nama << " telah dihapus!" << endl
         << endl;
    delete bantu;
}

void proses_energi()
{
    if (front == NULL)
    {
        cout << "Antrean masih kosong!" << endl
             << endl;
        return;
    }
    nodeQueue *hapus = front;
    nodeStack *n = new nodeStack{hapus->kode, hapus->nama, top};
    top = n;
    root = tambah_tree(root, hapus->kode, hapus->nama);
    cout << "Berhasil memproses energi!" << endl
         << endl;
    front = hapus->next;
    if (front == NULL)
    {
        last = NULL;
    }
    delete hapus;
}

void lihat_riwayat()
{
    if (front == NULL)
    {
        cout << "Belum ada energi yang terserap!" << endl
             << endl;
        return;
    }
    cout << "=== Energi Yang Sudah Terserap ===" << endl
         << endl;
    nodeStack *n = top;
    int no = 1;
    while (n != NULL)
    {
        cout << no << ". [" << n->kode << "] " << n->nama << endl;
        n = n->next;
        no++;
    }
    cout << endl;
}

void cari_energi()
{
    if (root == NULL)
    {
        cout << "Organ masih kosong!" << endl
             << endl;
        return;
    }
    int kode;
    cout << "Masukkan kode energi: ";
    cin >> kode;
    if (cin.fail() || kode <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Kode harus berupa angka lebih dari 0!" << endl
             << endl;
        return;
    }
    nodeTree *cari = cari_tree(root, kode);
    if (cari == NULL)
    {
        cout << "Energi dengan kode " << kode << " tidak ditemukan!" << endl
             << endl;
        return;
    }
    cout << "Ditemukan: [" << cari->kode << "] " << cari->nama << endl
         << endl;
}

void lihat_organ()
{
    if (root == NULL)
    {
        cout << "Organ masih kosong!" << endl
             << endl;
        return;
    }
    char pilihan;
    int no = 1;
    cout << "=== Isi Kristal Organ ===" << endl
         << endl;
    cout << "1. Pre-order" << endl;
    cout << "2. In-order" << endl;
    cout << "3. Post-order" << endl;
    cout << "Masukkan pilihan Anda: ";
    cin >> pilihan;
    cout << endl;
    switch (pilihan)
    {
    case '1':
        preorder(root, no);
        break;
    case '2':
        inorder(root, no);
        break;
    case '3':
        postorder(root, no);
        break;
    default:
        cout << "Pilihan tidak valid!";
        break;
    }
    cout << endl;
}

void gunakan_energi()
{
    if (root == NULL)
    {
        cout << "Organ masih kosong!" << endl
             << endl;
        return;
    }
    int kode;
    cout << "Masukkan kode energi: ";
    cin >> kode;
    if (cin.fail() || kode <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Kode harus berupa angka lebih dari 0!" << endl
             << endl;
        return;
    }
    nodeTree *hasil = cari_tree(root, kode);
    if (hasil == NULL)
    {
        cout << "Energi dengan kode " << kode << " tidak ditemukan!" << endl
             << endl;
        return;
    }
    cout << "Energi " << hasil->nama << " telah digunakan!" << endl
         << endl;
    root = hapus_tree(root, kode);
}

int main()
{
    char pilihan = '0';
    while (pilihan != '9')
    {
        cout << "=== Sistem Organ Inti Nirwana ===" << endl
             << endl;
        cout << "1. Tambah Energi" << endl;
        cout << "2. Lihat Energi Dalam Antrean" << endl;
        cout << "3. Proses Energi" << endl;
        cout << "4. Lihat Energi Yang Sudah Terserap" << endl;
        cout << "5. Hapus Riwayat Energi Teratas" << endl;
        cout << "6. Cari Energi Di Organ" << endl;
        cout << "7. Lihat Isi Organ" << endl;
        cout << "8. Gunakan Energi" << endl;
        cout << "9. Keluar" << endl;
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;
        switch (pilihan)
        {
        case '1':
        {
            char pilihan_tambah = 'y';
            while (pilihan_tambah == 'y' || pilihan_tambah == 'Y')
            {
                tambah_energi();
                cout << "Apakah Anda ingin menambahkan energi lagi? (y/n): ";
                cin >> pilihan_tambah;
            }
            break;
        }
        case '2':
        {
            lihat_antrean();
            break;
        }
        case '3':
        {
            proses_energi();
            break;
        }
        case '4':
        {
            lihat_riwayat();
            break;
        }
        case '5':
        {
            hapus_riwayat();
            break;
        }
        case '6':
        {
            cari_energi();
            break;
        }
        case '7':
        {
            lihat_organ();
            break;
        }
        case '8':
        {
            gunakan_energi();
            break;
        }
        case '9':
        {
            cout << "Program akan dikeluarkan." << endl;
            exit(0);
            break;
        }
        default:
        {
            cout << "Pilihan tidak valid!" << endl;
            cout << "Silakan coba lagi." << endl
                 << endl;
            break;
        }
        }
    }
}
