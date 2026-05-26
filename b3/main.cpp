#include "truong.h"

int main() {
    TruongDH truong;

    // a. Nhập danh sách sinh viên
    truong.nhapDanhSach();

    // b. Xuất danh sách các sinh viên
    truong.xuatDanhSach();

    // c. Xuất danh sách sinh viên đủ điều kiện tốt nghiệp
    truong.xuatSVTotNghiep();

    // d. Xuất danh sách sinh viên không đủ điều kiện tốt nghiệp
    truong.xuatSVKhongTotNghiep();

    // e. Cho biết SV Đại học có điểm trung bình cao nhất
    truong.timSVDaiHocMaxDTB();

    // f. Cho biết SV Cao đẳng có điểm trung bình cao nhất
    truong.timSVCaoDangMaxDTB();

    // g. Thống kê số sinh viên không đủ điều kiện tốt nghiệp theo hệ
    truong.thongKeKhongTotNghiep();

    return 0;
}
