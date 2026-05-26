#include "truong.h"
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
// Lớp SinhVien
// ============================================
SinhVien::SinhVien() : tongTinChi(0), diemTB(0.0) {}

void SinhVien::nhap() {
    cout << "Nhap MSSV: ";
    getline(cin, mssv);

    cout << "Nhap ho ten: ";
    getline(cin, hoTen);

    cout << "Nhap dia chi: ";
    getline(cin, diaChi);

    cout << "Nhap tong so tin chi: ";
    tongTinChi = nhapSoNguyenToan();

    cout << "Nhap diem trung binh: ";
    diemTB = nhapSoThucToan();
}

void SinhVien::xuat() {
    cout << "MSSV: " << mssv
         << " | Ho ten: " << hoTen
         << " | Dia chi: " << diaChi
         << " | Tin chi: " << tongTinChi
         << " | DTB: " << fixed << setprecision(2) << diemTB;
}

double SinhVien::getDiemTB() const { return diemTB; }
string SinhVien::getHoTen() const { return hoTen; }

// ============================================
// Lớp SVCaoDang
// ============================================
SVCaoDang::SVCaoDang() : diemThiTotNghiep(0.0) {}

void SVCaoDang::nhap() {
    SinhVien::nhap();
    cout << "Nhap diem thi tot nghiep: ";
    diemThiTotNghiep = nhapSoThucToan();
}

void SVCaoDang::xuat() {
    cout << "[SV Cao Dang] ";
    SinhVien::xuat();
    cout << " | Diem thi TN: " << diemThiTotNghiep << endl;
}

bool SVCaoDang::kiemTraTotNghiep() {
    return (tongTinChi >= 120 && diemTB >= 5.0 && diemThiTotNghiep >= 5.0);
}

// ============================================
// Lớp SVDaiHoc
// ============================================
SVDaiHoc::SVDaiHoc() : diemLuanVan(0.0) {}

void SVDaiHoc::nhap() {
    SinhVien::nhap();
    cout << "Nhap ten luan van: ";
    getline(cin, tenLuanVan);
    cout << "Nhap diem luan van: ";
    diemLuanVan = nhapSoThucToan();
}

void SVDaiHoc::xuat() {
    cout << "[SV Dai Hoc]  ";
    SinhVien::xuat();
    cout << " | Luan van: " << tenLuanVan
         << " | Diem LV: " << diemLuanVan << endl;
}

bool SVDaiHoc::kiemTraTotNghiep() {
    return (tongTinChi >= 170 && diemTB >= 5.0 && diemLuanVan >= 5.0);
}

// ============================================
// Lớp TruongDH
// ============================================
TruongDH::~TruongDH() {
    for (SinhVien* sv : danhSachSV) {
        delete sv;
    }
    danhSachSV.clear();
}

void TruongDH::nhapDanhSach() {
    int soLuong, loai;
    cout << "Nhap so luong sinh vien: ";
    soLuong = nhapSoNguyenToan();

    for (int i = 0; i < soLuong; i++) {
        cout << "\n> Chon he dao tao (1: Cao Dang, 2: Dai Hoc): ";
        while(true) {
            loai = nhapSoNguyenToan();
            if (loai == 1 || loai == 2) break;
            cout << ">>> Khong hop le! Vui long chon 1 hoac 2: ";
        }

        SinhVien* sv = nullptr;
        if (loai == 1) {
            sv = new SVCaoDang();
        } else {
            sv = new SVDaiHoc();
        }

        cout << "--- Nhap thong tin cho sinh vien thu " << i + 1 << " ---\n";
        sv->nhap();
        danhSachSV.push_back(sv);
    }
}

void TruongDH::xuatDanhSach() {
    cout << "\n========== DANH SACH TAT CA SINH VIEN ==========\n";
    for (SinhVien* sv : danhSachSV) {
        sv->xuat();
    }
}

void TruongDH::xuatSVTotNghiep() {
    cout << "\n========== DANH SACH SV DU DIEU KIEN TOT NGHIEP ==========\n";
    bool coSV = false;
    for (SinhVien* sv : danhSachSV) {
        if (sv->kiemTraTotNghiep()) {
            sv->xuat();
            coSV = true;
        }
    }
    if (!coSV) cout << "Khong co sinh vien nao du dieu kien tot nghiep.\n";
}

void TruongDH::xuatSVKhongTotNghiep() {
    cout << "\n========== DANH SACH SV KHONG DU DIEU KIEN TOT NGHIEP ==========\n";
    bool coSV = false;
    for (SinhVien* sv : danhSachSV) {
        if (!sv->kiemTraTotNghiep()) {
            sv->xuat();
            coSV = true;
        }
    }
    if (!coSV) cout << "Tat ca sinh vien deu du dieu kien tot nghiep.\n";
}

void TruongDH::timSVDaiHocMaxDTB() {
    double maxDTB = -1;
    SinhVien* svMax = nullptr;

    for (SinhVien* sv : danhSachSV) {
        SVDaiHoc* svdh = dynamic_cast<SVDaiHoc*>(sv);
        if (svdh != nullptr) {
            if (svdh->getDiemTB() > maxDTB) {
                maxDTB = svdh->getDiemTB();
                svMax = svdh;
            }
        }
    }

    cout << "\n========== SV DAI HOC CO DIEM TB CAO NHAT ==========\n";
    if (svMax != nullptr) {
        svMax->xuat();
    } else {
        cout << "Khong co sinh vien dai hoc nao trong danh sach.\n";
    }
}

void TruongDH::timSVCaoDangMaxDTB() {
    double maxDTB = -1;
    SinhVien* svMax = nullptr;

    for (SinhVien* sv : danhSachSV) {
        SVCaoDang* svcd = dynamic_cast<SVCaoDang*>(sv);
        if (svcd != nullptr) {
            if (svcd->getDiemTB() > maxDTB) {
                maxDTB = svcd->getDiemTB();
                svMax = svcd;
            }
        }
    }

    cout << "\n========== SV CAO DANG CO DIEM TB CAO NHAT ==========\n";
    if (svMax != nullptr) {
        svMax->xuat();
    } else {
        cout << "Khong co sinh vien cao dang nao trong danh sach.\n";
    }
}

void TruongDH::thongKeKhongTotNghiep() {
    int countCD = 0, countDH = 0;

    for (SinhVien* sv : danhSachSV) {
        if (!sv->kiemTraTotNghiep()) {
            if (dynamic_cast<SVCaoDang*>(sv)) {
                countCD++;
            } else if (dynamic_cast<SVDaiHoc*>(sv)) {
                countDH++;
            }
        }
    }

    cout << "\n========== THONG KE SV KHONG TOT NGHIEP ==========\n";
    cout << "- So luong SV Cao Dang khong tot nghiep: " << countCD << "\n";
    cout << "- So luong SV Dai Hoc khong tot nghiep: " << countDH << "\n";
}
