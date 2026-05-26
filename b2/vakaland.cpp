#include "vakaland.h"
#include <limits>
#include <iomanip>

// ============================================
// Hàm tiện ích chặn lỗi nhập liệu
// ============================================
int nhapSoNguyenToan() {
    int n;
    while (true) {
        if (cin >> n) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return n;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ">>> Loi! Ban phai nhap so nguyen. Nhap lai: ";
        }
    }
}

double nhapSoThucToan() {
    double n;
    while (true) {
        if (cin >> n) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return n;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ">>> Loi! Ban phai nhap so thuc. Nhap lai: ";
        }
    }
}

// ============================================
// Lớp GiaoDich
// ============================================
GiaoDich::GiaoDich() : donGia(0), dienTich(0), thanhTien(0) {
    ngayGD = {1, 1, 2024};
}

void GiaoDich::nhap() {
    cout << "Nhap ma giao dich: ";
    getline(cin, maGD);

    cout << "Nhap ngay giao dich: ";
    ngayGD.ngay = nhapSoNguyenToan();
    cout << "Nhap thang giao dich: ";
    ngayGD.thang = nhapSoNguyenToan();
    cout << "Nhap nam giao dich: ";
    ngayGD.nam = nhapSoNguyenToan();

    cout << "Nhap don gia: ";
    donGia = nhapSoThucToan();

    cout << "Nhap dien tich: ";
    dienTich = nhapSoThucToan();
}

void GiaoDich::xuat() {
    cout << "Ma GD: " << maGD
         << " | Ngay: " << ngayGD.ngay << "/" << ngayGD.thang << "/" << ngayGD.nam
         << " | Dien tich: " << dienTich
         << " | Don gia: " << fixed << setprecision(0) << donGia
         << " | Thanh tien: " << thanhTien;
}

double GiaoDich::getThanhTien() const { return thanhTien; }
Date GiaoDich::getNgayGD() const { return ngayGD; }

// ============================================
// Lớp GiaoDichDat
// ============================================
void GiaoDichDat::nhap() {
    GiaoDich::nhap();
    int chon;
    cout << "Chon loai dat (1: Loai A, 2: Loai B, 3: Loai C): ";
    while(true) {
        chon = nhapSoNguyenToan();
        if (chon == 1) { loaiDat = 'A'; break; }
        else if (chon == 2) { loaiDat = 'B'; break; }
        else if (chon == 3) { loaiDat = 'C'; break; }
        else cout << ">>> Khong hop le! Vui long chon 1, 2 hoac 3: ";
    }
    tinhThanhTien();
}

void GiaoDichDat::tinhThanhTien() {
    if (loaiDat == 'A') {
        thanhTien = dienTich * donGia * 1.5;
    } else {
        thanhTien = dienTich * donGia;
    }
}

void GiaoDichDat::xuat() {
    cout << "[GD DAT] ";
    GiaoDich::xuat();
    cout << " | Loai dat: " << loaiDat << endl;
}

// ============================================
// Lớp GiaoDichNhaPho
// ============================================
void GiaoDichNhaPho::nhap() {
    GiaoDich::nhap();
    int chon;
    cout << "Chon loai nha (1: Cao cap, 2: Thuong): ";
    while(true) {
        chon = nhapSoNguyenToan();
        if (chon == 1) { loaiNha = "cao cap"; break; }
        else if (chon == 2) { loaiNha = "thuong"; break; }
        else cout << ">>> Khong hop le! Vui long chon 1 hoac 2: ";
    }
    cout << "Nhap dia chi: ";
    getline(cin, diaChi);
    tinhThanhTien();
}

void GiaoDichNhaPho::tinhThanhTien() {
    if (loaiNha == "cao cap") {
        thanhTien = dienTich * donGia;
    } else {
        thanhTien = dienTich * donGia * 0.9;
    }
}

void GiaoDichNhaPho::xuat() {
    cout << "[GD NHA PHO] ";
    GiaoDich::xuat();
    cout << " | Loai nha: " << loaiNha << " | Dia chi: " << diaChi << endl;
}

// ============================================
// Lớp GiaoDichChungCu
// ============================================
void GiaoDichChungCu::nhap() {
    GiaoDich::nhap();
    cout << "Nhap ma can ho: ";
    getline(cin, maCan);
    cout << "Nhap vi tri tang: ";
    viTriTang = nhapSoNguyenToan();
    tinhThanhTien();
}

void GiaoDichChungCu::tinhThanhTien() {
    if (viTriTang == 1) {
        thanhTien = dienTich * donGia * 2.0;
    } else if (viTriTang >= 15) {
        thanhTien = dienTich * donGia * 1.2;
    } else {
        thanhTien = dienTich * donGia;
    }
}

void GiaoDichChungCu::xuat() {
    cout << "[GD CHUNG CU] ";
    GiaoDich::xuat();
    cout << " | Ma can: " << maCan << " | Tang: " << viTriTang << endl;
}

// ============================================
// Lớp Vakaland (Quản lý)
// ============================================
Vakaland::~Vakaland() {
    for (GiaoDich* gd : danhSachGD) {
        delete gd;
    }
    danhSachGD.clear();
}

void Vakaland::nhapDanhSach() {
    int soLuong, loaiGD;
    cout << "Nhap tong so luong giao dich can quan ly: ";
    soLuong = nhapSoNguyenToan();

    for (int i = 0; i < soLuong; i++) {
        cout << "\n> Chon loai giao dich (1: Dat, 2: Nha Pho, 3: Chung Cu): ";
        while(true) {
            loaiGD = nhapSoNguyenToan();
            if (loaiGD >= 1 && loaiGD <= 3) break;
            cout << ">>> Khong hop le! Vui long chon 1, 2 hoac 3: ";
        }

        GiaoDich* gd = nullptr;
        if (loaiGD == 1) gd = new GiaoDichDat();
        else if (loaiGD == 2) gd = new GiaoDichNhaPho();
        else if (loaiGD == 3) gd = new GiaoDichChungCu();

        cout << "--- Nhap thong tin cho giao dich thu " << i + 1 << " ---\n";
        gd->nhap();
        danhSachGD.push_back(gd);
    }
}

void Vakaland::tinhTongSoLuongTungLoai() {
    int soDat = 0, soNha = 0, soChungCu = 0;
    for (GiaoDich* gd : danhSachGD) {
        if (dynamic_cast<GiaoDichDat*>(gd)) soDat++;
        else if (dynamic_cast<GiaoDichNhaPho*>(gd)) soNha++;
        else if (dynamic_cast<GiaoDichChungCu*>(gd)) soChungCu++;
    }
    cout << "\n========== TONG SO LUONG TUNG LOAI ==========\n";
    cout << "- Giao dich Dat: " << soDat << "\n";
    cout << "- Giao dich Nha Pho: " << soNha << "\n";
    cout << "- Giao dich Chung Cu: " << soChungCu << "\n";
}

void Vakaland::tinhTrungBinhGDChungCu() {
    double tongTien = 0;
    int count = 0;
    for (GiaoDich* gd : danhSachGD) {
        if (dynamic_cast<GiaoDichChungCu*>(gd)) {
            tongTien += gd->getThanhTien();
            count++;
        }
    }
    cout << "\n========== TRUNG BINH THANH TIEN CHUNG CU ==========\n";
    if (count > 0) {
        cout << fixed << setprecision(0) << (tongTien / count) << " VND\n";
    } else {
        cout << "Khong co giao dich chung cu nao.\n";
    }
}

void Vakaland::timNhaPhoTriGiaCaoNhat() {
    double maxTien = -1;
    GiaoDich* gdMax = nullptr;

    for (GiaoDich* gd : danhSachGD) {
        GiaoDichNhaPho* np = dynamic_cast<GiaoDichNhaPho*>(gd);
        if (np != nullptr) {
            if (np->getThanhTien() > maxTien) {
                maxTien = np->getThanhTien();
                gdMax = np;
            }
        }
    }

    cout << "\n========== GIAO DICH NHA PHO CO TRI GIA CAO NHAT ==========\n";
    if (gdMax != nullptr) {
        gdMax->xuat();
    } else {
        cout << "Khong co giao dich nha pho nao trong danh sach.\n";
    }
}

void Vakaland::xuatGDThang12Nam2024() {
    cout << "\n========== GIAO DICH THANG 12 NAM 2024 ==========\n";
    bool timThay = false;
    for (GiaoDich* gd : danhSachGD) {
        Date d = gd->getNgayGD();
        if (d.thang == 12 && d.nam == 2024) {
            gd->xuat();
            timThay = true;
        }
    }
    if (!timThay) {
        cout << "Khong co giao dich nao trong Thang 12 Nam 2024.\n";
    }
}
