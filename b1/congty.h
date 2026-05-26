#ifndef CONGTY_H
#define CONGTY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Cấu trúc ngày tháng năm sinh
struct Date {
    int ngay, thang, nam;
};

// Hàm tiện ích hỗ trợ nhập liệu an toàn (tránh trôi lệnh, lỗi kiểu dữ liệu)
int nhapSoNguyenToan();
double nhapSoThucToan();


class NhanVien {
protected:
    string hoTen;
    Date ngaySinh;
    double luong;
public:
    NhanVien();
    virtual ~NhanVien() {}

    virtual void nhap();
    virtual void xuat();
    virtual void tinhLuong() = 0; // Phương thức thuần ảo (Đa hình)

    double getLuong() const;
    int getNamSinh() const;
    string getHoTen() const;
};

class NVSanXuat : public NhanVien {
private:
    double luongCanBan;
    int soSanPham;
public:
    NVSanXuat();
    void nhap() override;
    void xuat() override;
    void tinhLuong() override;
};


class NVVanPhong : public NhanVien {
private:
    int soNgayLamViec;
public:
    NVVanPhong();
    void nhap() override;
    void xuat() override;
    void tinhLuong() override;
};


class CongTy {
private:
    vector<NhanVien*> danhSachNV;
public:
    ~CongTy();
    void nhapDanhSach();
    void tinhLuongTatCa();
    void xuatDanhSach();
    double tinhTongLuong();
    void timNVSXLuongThapNhat();
    void timNVVPTuoiCaoNhat();
};

#endif
