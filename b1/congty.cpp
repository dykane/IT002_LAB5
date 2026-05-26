#include "congty.h"
#include <limits>
#include <iomanip>

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
            cout << ">>> Loi! Ban phai nhap so. Vui long nhap lai: ";
        }
    }
}

NhanVien::NhanVien() : luong(0) {
    ngaySinh = {1, 1, 1990};
}

void NhanVien::nhap() {
    cout << "Nhap ho ten: ";
    getline(cin, hoTen);

    cout << "Nhap ngay sinh: ";
    ngaySinh.ngay = nhapSoNguyenToan();
    cout << "Nhap thang sinh: ";
    ngaySinh.thang = nhapSoNguyenToan();
    cout << "Nhap nam sinh: ";
    ngaySinh.nam = nhapSoNguyenToan();
}

void NhanVien::xuat() {
    cout << "Ho ten: " << hoTen
         << " | Ngay sinh: " << ngaySinh.ngay << "/" << ngaySinh.thang << "/" << ngaySinh.nam
         << " | Luong: " << fixed << setprecision(0) << luong << " VND";
}

double NhanVien::getLuong() const { return luong; }
int NhanVien::getNamSinh() const { return ngaySinh.nam; }
string NhanVien::getHoTen() const { return hoTen; }

NVSanXuat::NVSanXuat() : luongCanBan(0), soSanPham(0) {}

void NVSanXuat::nhap() {
    NhanVien::nhap();
    cout << "Nhap luong can ban: ";
    luongCanBan = nhapSoThucToan();
    cout << "Nhap so san pham: ";
    soSanPham = nhapSoNguyenToan();
}

void NVSanXuat::xuat() {
    cout << "[Nhan vien San xuat] ";
    NhanVien::xuat();
    cout << " | Luong CB: " << luongCanBan
         << " | So SP: " << soSanPham << endl;
}

void NVSanXuat::tinhLuong() {
    luong = luongCanBan + (soSanPham * 5000);
}

NVVanPhong::NVVanPhong() : soNgayLamViec(0) {}

void NVVanPhong::nhap() {
    NhanVien::nhap();
    cout << "Nhap so ngay lam viec: ";
    soNgayLamViec = nhapSoNguyenToan();
}

void NVVanPhong::xuat() {
    cout << "[Nhan vien Van phong] ";
    NhanVien::xuat();
    cout << " | Ngay lam viec: " << soNgayLamViec << endl;
}

void NVVanPhong::tinhLuong() {
    luong = soNgayLamViec * 100000;
}

CongTy::~CongTy() {
    for (NhanVien* nv : danhSachNV) {
        delete nv;
    }
    danhSachNV.clear();
}

void CongTy::nhapDanhSach() {
    int soNVSX, soNVVP;

    cout << "--- NHAP DANH SACH NHAN VIEN SAN XUAT ---\n";
    cout << "Nhap so luong nhan vien san xuat: ";
    soNVSX = nhapSoNguyenToan();
    for (int i = 0; i < soNVSX; i++) {
        cout << "\n> Nhap thong tin NV San Xuat thu " << i + 1 << ":\n";
        NhanVien* nv = new NVSanXuat();
        nv->nhap();
        danhSachNV.push_back(nv);
    }

    cout << "\n--- NHAP DANH SACH NHAN VIEN VAN PHONG ---\n";
    cout << "Nhap so luong nhan vien van phong: ";
    soNVVP = nhapSoNguyenToan();
    for (int i = 0; i < soNVVP; i++) {
        cout << "\n> Nhap thong tin NV Van Phong thu " << i + 1 << ":\n";
        NhanVien* nv = new NVVanPhong();
        nv->nhap();
        danhSachNV.push_back(nv);
    }
}

void CongTy::tinhLuongTatCa() {
    for (NhanVien* nv : danhSachNV) {
        nv->tinhLuong();
    }
}

void CongTy::xuatDanhSach() {
    cout << "\n========== DANH SACH NHAN VIEN ==========\n";
    for (NhanVien* nv : danhSachNV) {
        nv->xuat();
    }
}

double CongTy::tinhTongLuong() {
    double tong = 0;
    for (NhanVien* nv : danhSachNV) {
        tong += nv->getLuong();
    }
    return tong;
}

void CongTy::timNVSXLuongThapNhat() {
    double minLuong = -1;
    NhanVien* nvMin = nullptr;

    for (NhanVien* nv : danhSachNV) {
        // Sử dụng dynamic_cast để kiểm tra xem nhân viên có phải là NVSanXuat không
        NVSanXuat* nvsx = dynamic_cast<NVSanXuat*>(nv);
        if (nvsx != nullptr) {
            if (minLuong == -1 || nvsx->getLuong() < minLuong) {
                minLuong = nvsx->getLuong();
                nvMin = nvsx;
            }
        }
    }

    cout << "\n========== NVSX CO LUONG THAP NHAT ==========\n";
    if (nvMin != nullptr) {
        nvMin->xuat();
    } else {
        cout << "Khong co nhan vien san xuat nao trong danh sach.\n";
    }
}

void CongTy::timNVVPTuoiCaoNhat() {
    int minNamSinh = 9999; // Năm sinh nhỏ nhất tương ứng với tuổi cao nhất
    NhanVien* nvOldest = nullptr;

    for (NhanVien* nv : danhSachNV) {
        // Sử dụng dynamic_cast để lấy ra NVVanPhong
        NVVanPhong* nvvp = dynamic_cast<NVVanPhong*>(nv);
        if (nvvp != nullptr) {
            if (nvvp->getNamSinh() < minNamSinh) {
                minNamSinh = nvvp->getNamSinh();
                nvOldest = nvvp;
            }
        }
    }

    cout << "\n========== NVVP CO TUOI CAO NHAT ==========\n";
    if (nvOldest != nullptr) {
        nvOldest->xuat();
    } else {
        cout << "Khong co nhan vien van phong nao trong danh sach.\n";
    }
}
