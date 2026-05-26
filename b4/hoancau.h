#ifndef HOANCAU_H
#define HOANCAU_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ============================================
// Các hàm tiện ích hỗ trợ nhập liệu an toàn
// ============================================
int nhapSoNguyenToan();
double nhapSoThucToan();

// ============================================
// Lớp cơ sở Nhân Viên
// ============================================
class NhanVien {
protected:
    string maNV;
    string hoTen;
    int tuoi;
    string sdt;
    string email;
    double luongCoBan;
    double luong;
public:
    NhanVien();
    virtual ~NhanVien() {}

    virtual void nhap();
    virtual void xuat();
    virtual void tinhLuong() = 0; // Đa hình

    double getLuong() const;
};

// ============================================
// Lớp Lập Trình Viên
// ============================================
class LapTrinhVien : public NhanVien {
private:
    int soGioOvertime;
public:
    LapTrinhVien();
    void nhap() override;
    void xuat() override;
    void tinhLuong() override;
};

// ============================================
// Lớp Kiểm Chứng Viên (Tester)
// ============================================
class KiemChungVien : public NhanVien {
private:
    int soLoi;
public:
    KiemChungVien();
    void nhap() override;
    void xuat() override;
    void tinhLuong() override;
};

// ============================================
// Lớp Quản lý Công Ty
// ============================================
class CongTy {
private:
    vector<NhanVien*> danhSachNV;
public:
    ~CongTy();
    void nhapDanhSach();
    void xuatDanhSach();
    void xuatNVLuongThapHonTB();
    void xuatNVLuongCaoNhat();
    void xuatNVLuongThapNhat();
    void xuatLTVLuongCaoNhat();
    void xuatKCVLuongThapNhat();
};

#endif
