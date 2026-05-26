#ifndef TRUONG_H
#define TRUONG_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Các hàm tiện ích hỗ trợ nhập liệu an toàn
int nhapSoNguyenToan();
double nhapSoThucToan();

// ============================================
// Lớp cơ sở Sinh Viên
// ============================================
class SinhVien {
protected:
    string mssv;
    string hoTen;
    string diaChi;
    int tongTinChi;
    double diemTB;
public:
    SinhVien();
    virtual ~SinhVien() {}

    virtual void nhap();
    virtual void xuat();
    virtual bool kiemTraTotNghiep() = 0; // Phương thức thuần ảo (Đa hình)

    double getDiemTB() const;
    string getHoTen() const;
};

// ============================================
// Lớp Sinh Viên Cao Đẳng
// ============================================
class SVCaoDang : public SinhVien {
private:
    double diemThiTotNghiep;
public:
    SVCaoDang();
    void nhap() override;
    void xuat() override;
    bool kiemTraTotNghiep() override;
};

// ============================================
// Lớp Sinh Viên Đại Học
// ============================================
class SVDaiHoc : public SinhVien {
private:
    string tenLuanVan;
    double diemLuanVan;
public:
    SVDaiHoc();
    void nhap() override;
    void xuat() override;
    bool kiemTraTotNghiep() override;
};

// ============================================
// Lớp Quản lý Trường Đại Học
// ============================================
class TruongDH {
private:
    vector<SinhVien*> danhSachSV;
public:
    ~TruongDH();
    void nhapDanhSach();
    void xuatDanhSach();
    void xuatSVTotNghiep();
    void xuatSVKhongTotNghiep();
    void timSVDaiHocMaxDTB();
    void timSVCaoDangMaxDTB();
    void thongKeKhongTotNghiep();
};

#endif
