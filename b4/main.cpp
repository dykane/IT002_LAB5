#include "hoancau.h"

int main() {
    CongTy hoanCau;

    // a. Nhập vào danh sách nhân viên
    hoanCau.nhapDanhSach();

    // b. Xuất danh sách nhân viên
    hoanCau.xuatDanhSach();

    // c. Xuất danh sách các nhân viên có lương thấp hơn mức lương trung bình
    hoanCau.xuatNVLuongThapHonTB();

    // d. Xuất thông tin nhân viên có lương cao nhất
    hoanCau.xuatNVLuongCaoNhat();

    // e. Xuất thông tin nhân viên có lương thấp nhất
    hoanCau.xuatNVLuongThapNhat();

    // f. Xuất thông tin lập trình viên có lương cao nhất
    hoanCau.xuatLTVLuongCaoNhat();

    // g. Xuất thông tin kiểm chứng viên có lương thấp nhất
    hoanCau.xuatKCVLuongThapNhat();

    return 0;
}
