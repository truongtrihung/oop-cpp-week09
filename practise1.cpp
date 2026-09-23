#include <iostream>
#include <string>
using namespace std;

#define MAX 10

struct FOOD{
    string id;      // mã món
    string name;    // tên món  
    double price;   // đơn giá
    int quantity;   // số lượng còn lại 

};

struct ORDER{
    string id;              // mã đơn hàng
    string customerName;    // tên khách hàng
    string address;         // địa chỉ giao hàng
    FOOD food;              // món ăn được đặt
    int quantity;           // số lượng
    string status;          // trạng thái
};

struct RESTAURANT{
    string name;            // Tên cửa hàng 
    string address;         // Địa chỉ
    string phone;           //  Số điện thoại
    FOOD foods[MAX];        // Danh sách món ăn
    int foodCount;
    ORDER orders[MAX];      // Danh sách đơn hàng
    int orderCount;          

    // Chức năng 1: Nhập thông tin của cửa hàng
    // Chức năng 2: Thêm món ăn mới
    // Chức năng 3: Hiển thị danh sách món ăn
    // Chức năng 4: Tìm món ăn theo mã hoặc tên
    // Chức năng 5: Cập nhật giá hoặc số lượng món ăn
    // Chức năng 6: Tạo đơn hàng mới
    // Chức năng 7: Kiểm tra món ăn có tồn tại và đủ số lượng
    // Chức năng 8: Tính tổng tiền của đơn hàng
    // Chức năng 9: Hiển thị danh sách các đơn hàng
    // Chức năng 10: Tìm đơn hàng theo mã
    // Chức năng 11: Cập nhật trạng thái đơn hàng
    // Chức năng 12: Thống kê tổng doanh thu của các đơn đã hoàn thành 
};

int main(){

    return 0;
}