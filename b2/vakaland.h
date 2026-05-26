#ifndef VAKALAND_H
#define VAKALAND_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Cấu trúc ngày tháng
struct Date {
    int ngay, thang, nam;
};

// Các hàm tiện ích hỗ trợ nhập liệu an toàn
int nhapSoNguyenToan();
double nhapSoThucToan();

// ============================================
// Lớp cơ sở GiaoDich
// ============================================
class GiaoDich {
protected:
    string maGD;
    Date ngayGD;
    double donGia;
    double dienTich;
    double thanhTien;
public:
    GiaoDich();
    virtual ~GiaoDich() {}

    virtual void nhap();
    virtual void xuat();
    virtual void tinhThanhTien() = 0; // Đa hình

    int getLoaiGD() const; // 1: Đất, 2: Nhà phố, 3: Chung cư (dùng hờ để dễ quản lý, hoặc dùng dynamic_cast)
    double getThanhTien() const;
    Date getNgayGD() const;
};

// ============================================
// Lớp Giao Dịch Đất
// ============================================
class GiaoDichDat : public GiaoDich {
private:
    char loaiDat; // 'A', 'B', 'C'
public:
    void nhap() override;
    void xuat() override;
    void tinhThanhTien() override;
};

// ============================================
// Lớp Giao Dịch Nhà Phố
// ============================================
class GiaoDichNhaPho : public GiaoDich {
private:
    string loaiNha; // "cao cap" hoặc "thuong"
    string diaChi;
public:
    void nhap() override;
    void xuat() override;
    void tinhThanhTien() override;
};

// ============================================
// Lớp Giao Dịch Căn Hộ Chung Cư
// ============================================
class GiaoDichChungCu : public GiaoDich {
private:
    string maCan;
    int viTriTang;
public:
    void nhap() override;
    void xuat() override;
    void tinhThanhTien() override;
};

// ============================================
// Lớp Quản Lý Công Ty VAKALAND
// ============================================
class Vakaland {
private:
    vector<GiaoDich*> danhSachGD;
public:
    ~Vakaland();
    void nhapDanhSach();
    void tinhTongSoLuongTungLoai();
    void tinhTrungBinhGDChungCu();
    void timNhaPhoTriGiaCaoNhat();
    void xuatGDThang12Nam2024();
};

#endif
