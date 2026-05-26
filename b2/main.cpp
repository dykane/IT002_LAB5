#include "vakaland.h"

int main() {
    Vakaland cty;

    // 1. Nhập danh sách giao dịch
    cty.nhapDanhSach();

    // 2. Tính tổng số lượng cho từng loại
    cty.tinhTongSoLuongTungLoai();

    // 3. Tính trung bình thành tiền của Căn hộ chung cư
    cty.tinhTrungBinhGDChungCu();

    // 4. Cho biết giao dịch nhà phố có trị giá cao nhất
    cty.timNhaPhoTriGiaCaoNhat();

    // 5. Xuất các giao dịch của tháng 12 năm 2024
    cty.xuatGDThang12Nam2024();

    return 0;
}
