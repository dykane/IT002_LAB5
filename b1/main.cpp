#include "congty.h"

int main() {
    CongTy cty;

    // 1. Nhập danh sách
    cty.nhapDanhSach();

    // 2. Tính lương cho từng nhân viên
    cty.tinhLuongTatCa();

    // 3. Xuất thông tin danh sách
    cty.xuatDanhSach();

    // 4. Tính tổng lương
    double tongLuong = cty.tinhTongLuong();
    cout << "\n========== TONG LUONG CTY PHAI TRA ==========\n";
    cout << tongLuong << " VND\n";

    // 5. Nhân viên sản xuất có lương thấp nhất
    cty.timNVSXLuongThapNhat();

    // 6. Nhân viên văn phòng tuổi cao nhất
    cty.timNVVPTuoiCaoNhat();
    return 0;
}
