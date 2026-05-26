#include "hoancau.h"
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
            cout << ">>> Loi! Ban phai nhap so nguyen. Vui long nhap lai: ";
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
            cout << ">>> Loi! Ban phai nhap so thuc. Vui long nhap lai: ";
        }
    }
}

// ============================================
// Lớp NhanVien
// ============================================
NhanVien::NhanVien() : tuoi(0), luongCoBan(0), luong(0) {}

void NhanVien::nhap() {
    cout << "Nhap ma NV: ";
    getline(cin, maNV);

    cout << "Nhap ho ten: ";
    getline(cin, hoTen);

    cout << "Nhap tuoi: ";
    tuoi = nhapSoNguyenToan();

    cout << "Nhap so dien thoai: ";
    getline(cin, sdt);

    cout << "Nhap email: ";
    getline(cin, email);

    cout << "Nhap luong co ban: ";
    luongCoBan = nhapSoThucToan();
}

void NhanVien::xuat() {
    cout << "Ma NV: " << maNV
         << " | Ho ten: " << hoTen
         << " | Tuoi: " << tuoi
         << " | SDT: " << sdt
         << " | Email: " << email
         << " | Luong CB: " << fixed << setprecision(0) << luongCoBan
         << " | Luong thuc nhan: " << luong;
}

double NhanVien::getLuong() const {
    return luong;
}

// ============================================
// Lớp LapTrinhVien
// ============================================
LapTrinhVien::LapTrinhVien() : soGioOvertime(0) {}

void LapTrinhVien::nhap() {
    NhanVien::nhap();
    cout << "Nhap so gio overtime: ";
    soGioOvertime = nhapSoNguyenToan();
    tinhLuong(); // Tính luôn lương khi vừa nhập xong
}

void LapTrinhVien::tinhLuong() {
    luong = luongCoBan + (soGioOvertime * 200000);
}

void LapTrinhVien::xuat() {
    cout << "[Lap trinh vien] ";
    NhanVien::xuat();
    cout << " | OT: " << soGioOvertime << " gio" << endl;
}

// ============================================
// Lớp KiemChungVien
// ============================================
KiemChungVien::KiemChungVien() : soLoi(0) {}

void KiemChungVien::nhap() {
    NhanVien::nhap();
    cout << "Nhap so loi phat hien: ";
    soLoi = nhapSoNguyenToan();
    tinhLuong(); // Tính luôn lương khi vừa nhập xong
}

void KiemChungVien::tinhLuong() {
    luong = luongCoBan + (soLoi * 50000);
}

void KiemChungVien::xuat() {
    cout << "[Kiem chung vien] ";
    NhanVien::xuat();
    cout << " | So loi: " << soLoi << endl;
}

// ============================================
// Lớp CongTy
// ============================================
CongTy::~CongTy() {
    for (NhanVien* nv : danhSachNV) {
        delete nv;
    }
    danhSachNV.clear();
}

void CongTy::nhapDanhSach() {
    int soLuong, loai;
    cout << "Nhap so luong nhan vien can quan ly: ";
    soLuong = nhapSoNguyenToan();

    for (int i = 0; i < soLuong; i++) {
        cout << "\n> Chon loai NV (1: Lap Trinh Vien, 2: Kiem Chung Vien): ";
        while(true) {
            loai = nhapSoNguyenToan();
            if (loai == 1 || loai == 2) break;
            cout << ">>> Khong hop le! Vui long chon 1 hoac 2: ";
        }

        NhanVien* nv = nullptr;
        if (loai == 1) {
            nv = new LapTrinhVien();
        } else {
            nv = new KiemChungVien();
        }

        cout << "--- Nhap thong tin nhan vien thu " << i + 1 << " ---\n";
        nv->nhap();
        danhSachNV.push_back(nv);
    }
}

void CongTy::xuatDanhSach() {
    cout << "\n========== DANH SACH NHAN VIEN CONG TY ==========\n";
    for (NhanVien* nv : danhSachNV) {
        nv->xuat();
    }
}

void CongTy::xuatNVLuongThapHonTB() {
    if (danhSachNV.empty()) return;

    double tongLuong = 0;
    for (NhanVien* nv : danhSachNV) {
        tongLuong += nv->getLuong();
    }
    double luongTB = tongLuong / danhSachNV.size();

    cout << "\n========== NV CO LUONG THAP HON TRUNG BINH ("
         << fixed << setprecision(0) << luongTB << " VND) ==========\n";

    bool timThay = false;
    for (NhanVien* nv : danhSachNV) {
        if (nv->getLuong() < luongTB) {
            nv->xuat();
            timThay = true;
        }
    }
    if (!timThay) cout << "Khong co nhan vien nao co luong thap hon trung binh.\n";
}

void CongTy::xuatNVLuongCaoNhat() {
    if (danhSachNV.empty()) return;

    double maxLuong = danhSachNV[0]->getLuong();
    for (NhanVien* nv : danhSachNV) {
        if (nv->getLuong() > maxLuong) {
            maxLuong = nv->getLuong();
        }
    }

    cout << "\n========== NHAN VIEN CO LUONG CAO NHAT ==========\n";
    for (NhanVien* nv : danhSachNV) {
        if (nv->getLuong() == maxLuong) {
            nv->xuat();
        }
    }
}

void CongTy::xuatNVLuongThapNhat() {
    if (danhSachNV.empty()) return;

    double minLuong = danhSachNV[0]->getLuong();
    for (NhanVien* nv : danhSachNV) {
        if (nv->getLuong() < minLuong) {
            minLuong = nv->getLuong();
        }
    }

    cout << "\n========== NHAN VIEN CO LUONG THAP NHAT ==========\n";
    for (NhanVien* nv : danhSachNV) {
        if (nv->getLuong() == minLuong) {
            nv->xuat();
        }
    }
}

void CongTy::xuatLTVLuongCaoNhat() {
    double maxLuong = -1;
    for (NhanVien* nv : danhSachNV) {
        LapTrinhVien* ltv = dynamic_cast<LapTrinhVien*>(nv);
        if (ltv != nullptr) {
            if (maxLuong == -1 || ltv->getLuong() > maxLuong) {
                maxLuong = ltv->getLuong();
            }
        }
    }

    cout << "\n========== LAP TRINH VIEN CO LUONG CAO NHAT ==========\n";
    if (maxLuong == -1) {
        cout << "Khong co lap trinh vien nao trong danh sach.\n";
    } else {
        for (NhanVien* nv : danhSachNV) {
            LapTrinhVien* ltv = dynamic_cast<LapTrinhVien*>(nv);
            if (ltv != nullptr && ltv->getLuong() == maxLuong) {
                ltv->xuat();
            }
        }
    }
}

void CongTy::xuatKCVLuongThapNhat() {
    double minLuong = -1;
    for (NhanVien* nv : danhSachNV) {
        KiemChungVien* kcv = dynamic_cast<KiemChungVien*>(nv);
        if (kcv != nullptr) {
            if (minLuong == -1 || kcv->getLuong() < minLuong) {
                minLuong = kcv->getLuong();
            }
        }
    }

    cout << "\n========== KIEM CHUNG VIEN CO LUONG THAP NHAT ==========\n";
    if (minLuong == -1) {
        cout << "Khong co kiem chung vien nao trong danh sach.\n";
    } else {
        for (NhanVien* nv : danhSachNV) {
            KiemChungVien* kcv = dynamic_cast<KiemChungVien*>(nv);
            if (kcv != nullptr && kcv->getLuong() == minLuong) {
                kcv->xuat();
            }
        }
    }
}
