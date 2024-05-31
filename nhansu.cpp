#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <exception>
#include <iomanip> // For setting output width
#include <windows.h>
#include <algorithm>
using namespace std;

void SetColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

class nhanvien
{
private:
    int id;
    string hovaten;
    int tuoi;
    string quequan;
    float giolamviec;
    float luongtheogio;
    double luonghangnam;
    float phucap;

public:
    int get_id()
    {
        return id;
    }

    string get_hovaten()
    {
        return hovaten;
    }

    int get_tuoi()
    {
        return tuoi;
    }

    string get_quequan()
    {
        return quequan;
    }

    float get_giolamviec()
    {
        return giolamviec;
    }

    float get_luongtheogio()
    {
        return luongtheogio;
    }

    float get_phucap()
    {
        return phucap;
    }

    double get_luonghangnam()
    {
        luonghangnam = (giolamviec * luongtheogio * 52) + phucap;
        return (luonghangnam <= 0) ? 0.0 : luonghangnam;
    }

    void set_id(int id)
    {
        this->id = id;
    }

    void set_hovaten(string hovaten)
    {
        this->hovaten = hovaten;
    }

    void set_tuoi(int tuoi)
    {
        this->tuoi = tuoi;
    }

    void set_quequan(string quequan)
    {
        this->quequan = quequan;
    }

    void set_giolamviec(float gio)
    {
        this->giolamviec = gio;
    }

    void set_luongtheogio(float luong)
    {
        this->luongtheogio = luong;
    }

    void set_phucap(float pc)
    {
        this->phucap = pc;
    }
};

class quanlinhanvien
{
private:
    vector<nhanvien> danhSachNhanVien;

public:
    void docfile()
    {
        ifstream fs("nhanvien.txt");
        if (!fs.is_open())
        {
            cerr << "Khong the mo file" << endl;
            return;
        }

        danhSachNhanVien.clear();
        string line;

        while (getline(fs, line))
        {
            stringstream ss(line);
            string id, ten, tuoi, que, giolamviec, luongtheogio, phucap;

            getline(ss, id, ',');
            getline(ss, ten, ',');
            getline(ss, tuoi, ',');
            getline(ss, que, ',');
            getline(ss, giolamviec, ',');
            getline(ss, luongtheogio, ',');
            getline(ss, phucap, '\n');

            nhanvien nv;
            nv.set_id(stoi(id));
            nv.set_hovaten(ten);
            nv.set_tuoi(stoi(tuoi));
            nv.set_quequan(que);
            nv.set_giolamviec(stof(giolamviec));
            nv.set_luongtheogio(stof(luongtheogio));
            nv.set_phucap(stof(phucap));

            danhSachNhanVien.push_back(nv);
        }
        fs.close();
    }

    void themnhanvien()
    {
        char yn;
        do
        {
            nhanvien E;
            string name;
            string quequan;
            int tuoi;
            int id;

            cout << "Nhap id cua nhan vien: ";
            cin >> id;
            E.set_id(id);

            cout << "Nhap ten cua nhan vien: ";
            cin.ignore();
            getline(cin, name);
            E.set_hovaten(name);

            cout << "Nhap tuoi cua nhan vien: ";
            cin >> tuoi;
            E.set_tuoi(tuoi);

            cout << "Nhap que quan: ";
            cin.ignore();
            getline(cin, quequan);
            E.set_quequan(quequan);

            float giolamviec, luongtheogio, phucap;

            cout << "So tieng lam viec trong 1 tuan: ";
            cin >> giolamviec;
            while (giolamviec < 1 || giolamviec > 60)
            {
                cout << "Vui long nhap so tu 1 den 60: ";
                cin >> giolamviec;
            }
            E.set_giolamviec(giolamviec);

            cout << "Luong theo gio cua nhan vien la: ";
            cin >> luongtheogio;
            while (luongtheogio < 0)
            {
                cout << "Vui long nhap lai: ";
                cin >> luongtheogio;
            }
            E.set_luongtheogio(luongtheogio);

            cout << "Nhap so tien phu cap: ";
            cin >> phucap;
            while (phucap < 0)
            {
                cout << "Vui long nhap lai: ";
                cin >> phucap;
            }
            E.set_phucap(phucap);

            danhSachNhanVien.push_back(E);

            cout << "Nhan vien co thong tin sau da duoc them vao: " << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
            cout << "|  Id   |  Ho va ten            |  Tuoi  |  Que quan         |  Luong hang nam  |" << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
            cout << "    ";
            cout << setw(6) << left << E.get_id()
                << setw(25) << E.get_hovaten()
                << setw(10) << E.get_tuoi()
                << setw(20) << E.get_quequan()
                << setw(22) << fixed << setprecision(2) << E.get_luonghangnam() << endl;

            cout << "Ban co muon them nhan vien khac (y/n)? ";
            cin >> yn;
        } while (yn == 'y' || yn == 'Y');
    }

    void Menu()
    {
        SetColor(FOREGROUND_RED);
        cout << "               DUT Staffwise System               " << endl;
        SetColor(FOREGROUND_BLUE);
        cout << "__________________________________________________" << endl;
        cout << "| 1. Them thong tin nhan vien                    |" << endl;
        cout << "| 2. Xoa thong tin nhan vien                     |" << endl;
        cout << "| 3. Sua thong tin nhan vien                     |" << endl;
        cout << "| 4. Tim kiem nhan vien                          |" << endl;
        cout << "| 5. Hien thi danh sach nhan vien                |" << endl;
        cout << "| 6. Cap nhat du lieu nhan vien                  |" << endl;
        cout << "| 7. Sap xep nhan vien                           |" << endl;
        cout << "| 8. Thoat                                       |" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Lua chon cua ban la: ";
    }

    void hienThiDanhSachNhanVien()
    {
        if (danhSachNhanVien.empty())
        {
            cout << "Danh sach nhan vien rong." << endl;
        }
        else
        {
            cout << "Danh sach nhan vien: " << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
            cout << "|  Id   |  Ho va ten            |  Tuoi  |  Que quan         |  Luong hang nam |" << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
            for (auto& E : danhSachNhanVien)
            {
                cout << "    ";
                cout << setw(6) << left << E.get_id()
                    << setw(25) << E.get_hovaten()
                    << setw(10) << E.get_tuoi()
                    << setw(20) << E.get_quequan()
                    << setw(22) << fixed << setprecision(2) << E.get_luonghangnam() << endl;
            }
        }
    }

    void timkiemnhanvien(int id)
    {
        bool found = false;
        for (auto& E : danhSachNhanVien)
        {
            if (E.get_id() == id)
            {
                found = true;
                cout << "Thong tin nhan vien: " << endl;
                cout << "ID: " << E.get_id() << endl;
                cout << "Ho va ten: " << E.get_hovaten() << endl;
                cout << "Tuoi: " << E.get_tuoi() << endl;
                cout << "Que quan: " << E.get_quequan() << endl;
                cout << "Luong hang nam: " << E.get_luonghangnam() << endl;
                break;
            }
        }
        if (!found)
        {
            cout << "Khong tim thay nhan vien" << endl;
        }
    }

    void xoanhanvien()
    {
        int id;
        cout << "Nhap ID cua nhan vien can xoa: ";
        cin >> id;
        bool found = false;
        for (auto it = danhSachNhanVien.begin(); it != danhSachNhanVien.end(); ++it)
        {
            if (it->get_id() == id)
            {
                danhSachNhanVien.erase(it);
                cout << "Nhan vien voi ID " << id << " da duoc xoa." << endl;
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Khong tim thay nhan vien voi id " << id << endl;
        }
    }

    void suanhanvien()
    {
        int id;
        cout << "Nhap ID cua nhan vien can sua: ";
        cin >> id;
        bool found = false;
        for (auto& E : danhSachNhanVien)
        {
            if (E.get_id() == id)
            {
                found = true;
                int choice;
                do
                {
                    cout << "Chon thong tin can sua: " << endl;
                    cout << "1. Ho va ten" << endl;
                    cout << "2. Tuoi" << endl;
                    cout << "3. Que quan" << endl;
                    cout << "4. Gio lam viec" << endl;
                    cout << "5. Luong theo gio" << endl;
                    cout << "6. Phu cap" << endl;
                    cout << "7. Thoat" << endl;
                    cout << "Lua chon cua ban la: ";
                    cin >> choice;
                    cin.ignore();
                    switch (choice)
                    {
                    case 1:
                    {
                        system("cls");
                        string hovaten;
                        cout << "Nhap ho va ten moi: ";
                        getline(cin, hovaten);
                        E.set_hovaten(hovaten);
                        break;
                    }
                    case 2:
                    {
                        system("cls");
                        int tuoi;
                        cout << "Nhap tuoi moi: ";
                        cin >> tuoi;
                        E.set_tuoi(tuoi);
                        break;
                    }
                    case 3:
                    {
                        system("cls");
                        string quequan;
                        cout << "Nhap que quan moi: ";
                        getline(cin, quequan);
                        E.set_quequan(quequan);
                        break;
                    }
                    case 4:
                    {
                        system("cls");
                        float giolamviec;
                        cout << "Nhap gio lam viec moi: ";
                        cin >> giolamviec;
                        E.set_giolamviec(giolamviec);
                        break;
                    }
                    case 5:
                    {
                        system("cls");
                        float luongtheogio;
                        cout << "Nhap luong theo gio moi: ";
                        cin >> luongtheogio;
                        E.set_luongtheogio(luongtheogio);
                        break;
                    }
                    case 6:
                    {
                        system("cls");
                        float phucap;
                        cout << "Nhap phu cap moi: ";
                        cin >> phucap;
                        E.set_phucap(phucap);
                        break;
                    }
                    case 7:
                    {
                        system("cls");
                        cout << "Thoat sua thong tin nhan vien." << endl;
                        break;
                    }
                    default:
                    {
                        cout << "Lua chon khong hop le. Vui long chon lai." << endl;
                        break;
                    }
                    }
                } while (choice != 7);
                break;
            }
        }
        if (!found)
        {
            cout << "Khong tim thay nhan vien voi ID " << id << "." << endl;
        }
    }

    void LuuDanhSachVaoFile()
    {
        ofstream fs("nhanvien.txt");

        if (!fs.is_open())
        {
            cerr << "Khong the mo file de ghi." << endl;
            return;
        }

        for (auto& nv : danhSachNhanVien)
        {
            fs << nv.get_id() << ","
                << nv.get_hovaten() << ","
                << nv.get_tuoi() << ","
                << nv.get_quequan() << ","
                << nv.get_giolamviec() << ","
                << nv.get_luongtheogio() << ","
                << nv.get_phucap() << endl;
        }

        fs.close();
    }
    void sapXepTheoLuongHangNam()
    {
        sort(danhSachNhanVien.begin(), danhSachNhanVien.end(), [](nhanvien& a, nhanvien& b)
            {
                return a.get_luonghangnam() > b.get_luonghangnam();
            });
        cout << "Danh sach nhan vien da duoc sap xep theo luong hang nam." << endl;
    }

    void sapXepTheoID()
    {
        sort(danhSachNhanVien.begin(), danhSachNhanVien.end(), [](nhanvien& a, nhanvien& b)
            {
                return a.get_id() < b.get_id();
            });
        cout << "Danh sach nhan vien da duoc sap xep theo ID." << endl;
    }

};

int main()
{
    quanlinhanvien qlnv;
    qlnv.docfile();
    int choice;
    do
    {
        qlnv.Menu();
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            system("cls");
            qlnv.themnhanvien();
            break;
        case 2:
            system("cls");
            qlnv.xoanhanvien();
            break;
        case 3:
            system("cls");
            qlnv.suanhanvien();
            break;
        case 4:
        {
            system("cls");
            int id;
            cout << "Nhap ID nhan vien can tim: ";
            cin >> id;
            qlnv.timkiemnhanvien(id);
            break;
        }
        case 5:
            system("cls");
            qlnv.hienThiDanhSachNhanVien();
            break;
        case 6:
            system("cls");
            qlnv.LuuDanhSachVaoFile();
            cout << "Danh sach nhan vien da duoc cap nhat." << endl;
            break;
        case 7:
            system("cls");
            int choice1;
            cout << "1. Sap xep theo id " << endl;
            cout << "2. Sap xep theo luong " << endl;
            cout << "Moi ban nhap lua chon :" << endl;
            cin >> choice1;
            switch (choice1)
            {
            case 1:
                system("cls");
                qlnv.sapXepTheoID();
                qlnv.hienThiDanhSachNhanVien();
                break;
            case 2:
                system("cls");
                qlnv.sapXepTheoLuongHangNam();
                qlnv.hienThiDanhSachNhanVien();
                break;
            }
            break;
        case 8:
            system("cls");
            cout << "                                                                o                   " << endl;
            cout << "                                                              o  o                  " << endl;
            cout << "                                                             o    o                 " << endl;
            cout << "ooooooooo     o          o       o            ooooooooo  o  oooooooo  ooooooooo     " << endl;
            cout << "    o        o o        o o     o o           o       o  o  o             o         " << endl;
            cout << "    o       ooooo      o   o   o   o          ooooooooo  o  oooooooo      o         " << endl;
            cout << "    o      o     o    o     o o     o         o       o  o  o             o         " << endl;
            cout << "    o     o       o  o       o       o        ooooooooo  o  oooooooo      o         " << endl;
            cout << "              o                                                 o                   ";
            break;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai." << endl;
            break;
        }
        if (choice != 8)
        {
            cout << "Nhan Enter de tiep tuc...";
            cin.ignore();
            cin.get();
            system("cls");
        }
    } while (choice != 8);

    return 0;
};