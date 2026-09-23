#include <iostream>
#include <string>
using namespace std;

#define MAX 10


struct FOOD{
    string id;      // mã món
    string name;    // tên món  
    double price;   // đơn giá
    int quantity;   // số lượng còn lại 

    void inputInfo(){           // Nhập thông tin đồ ăn 
        cout << "Enter the ID of the food: ";
        cin >> id;

        cin.ignore();

        cout << "Enter the name of the food: ";
        getline (cin, name);

        cout << "Enter the price of the food: ";
        cin >> price;

        cout << "Enter the quantity of the food: ";
        cin >> quantity;

    }

    void outputInfo(){          // In thông tin đồ ăn 
        cout << "===========================" << endl;
        cout << "   | ID        : " << id << endl;
        cout << "   | Name      : " << name << endl;
        cout << "   | Price     : " << price << endl;
        cout << "   | Quantity  : " << quantity << endl;
    }

};

struct ORDER{
    string id;              // mã đơn hàng
    string customerName;    // tên khách hàng
    string address;         // địa chỉ giao hàng
    FOOD food;              // món ăn được đặt
    int quantity;           // số lượng
    string status;          // trạng thái   (Completed, Pending, Cancelled)

    void inputInfo (FOOD availableFood[], int availableCount){ // Nhập thông tin order

        cin.ignore();

        cout << "Enter the order ID: ";
        getline (cin, id);

        cout << "Enter the Customer Name: ";
        getline (cin, customerName);

        cout << "Enter the address: ";
        getline (cin, address);

        // Chức năng 4: Tìm món ăn theo mã hoặc tên
        string foodSearch;
        cout << "Enter the ID or Name of the food u wanna search: ";
        getline (cin, foodSearch);

        for (int i = 0; i < availableCount; i++){
            bool found = false;
            if (foodSearch == availableFood[i].id && foodSearch == availableFood[i].name){
                food = availableFood[i];
                found = true;
                break;
            }

            if (!found){
                cout << "Sorry the ID/Name of the food are not exist" << endl;
                food.inputInfo();
            }
        }

        cout << "Enter the quantity: ";
        cin >> quantity;

        cin.ignore();

        cout << "Enter the order status (Completed / Pending / Cancelled): ";
        getline (cin, status);
    }

    // Chức năng 8: Tính tổng tiền của đơn hàng
    double getTotalPrice(){
        return food.price * quantity;
    }

    void outputInfo(){      // In thông tin order
        cout << "==================================" << endl;
        cout << "   | Order ID          : " << id << endl;
        cout << "   | Customer Name     : " << customerName << endl;
        cout << "   | Address           : " << address << endl;
        cout << "   | Item order        : " << food.name << " (ID: " << food.id << ")" << endl;
        cout << "   | Quantity          : " << quantity << endl;
        cout << "   | Total price       : " << getTotalPrice() << endl;
        cout << "   | Status            : " << status << endl;
        cout << "==================================" << endl;
    }
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
    void inputRestaurantInfo(){
        cout << "***********************************" << endl;

        cout << "Enter the name of the restaurant: ";
        getline (cin, name);

        cout << "Enter the address: ";
        getline (cin, address);

        cout << "Enter the phone number: ";
        getline (cin, phone);

        cout << "Enter the initial number of food: ";
        cin >> foodCount;

        for (int i = 0; i < foodCount; i++){
            cout << "\n --> Input food " << i + 1 << " --" << endl;
            foods[i].inputInfo();
        }
        cout << "***********************************" << endl;
    }
    // Chức năng 2: Thêm món ăn mới
    void addFood(){
        if (foodCount < MAX){
            cout << " ==> ADD NEW FOOD <==" << endl;
            foods[foodCount].inputInfo();
            foodCount++;
            cout << " --> Add food successfully!" << endl;
        }
        else {
            cout << " --> The Menu is full!" << endl;
        }
    }
    // Chức năng 3: Hiển thị danh sách món ăn
    void displatMenu(){
        cout << "<<<<<<<<<< MENU <<<<<<<<<<" << endl;
        if (foodCount == 0 ){
            cout << "No food available!" << endl;
            return;
        }
        for (int i = 0; i < foodCount; i++){
            foods[i].outputInfo();
        }
        
    }

    // Chức năng 4 (hỗ trợ): Tìm món ăn theo id hoặc name
    int findFoorIdex(string key){
        for (int i = 0; i < foodCount; i++){
            if (foods[i].id == key || foods[i].name == key){
                return i;
            }
        }
        return -1;
    }

    // Chức năng 5: Cập nhật giá hoặc số lượng món ăn
    void updateFoodIndex (string key){
        int idx = findFoorIdex(key);
        if (idx != -1){
            cout << "\n --> Food found: " << foods[idx].name << endl;
            
            cout << "Enter new price: ";
            cin >> foods[idx].price;

            cout << "Enter new quantity: ";
            cin >> foods[idx].quantity;

            cout << " --> Updated food infos successfully!" << endl;
        }
        else{
            cout << " --> Food not found" << endl;
        }
    }
    // Chức năng 6: Tạo đơn hàng mới
    // Chức năng 7: Kiểm tra món ăn có tồn tại và đủ số lượng
    // Chức năng 9: Hiển thị danh sách các đơn hàng
    // Chức năng 10: Tìm đơn hàng theo mã
    // Chức năng 11: Cập nhật trạng thái đơn hàng
    // Chức năng 12: Thống kê tổng doanh thu của các đơn đã hoàn thành 
};

int main(){

    RESTAURANT myrestaurant;

    cout << "========================================" << endl;
    cout << "===== WELCOME TO RESTAURANT SYSTEM =====" << endl;
    cout << "========================================" << endl;

    // Chức năng 1: Nhập thông tin của cửa hàng
    myrestaurant.inputRestaurantInfo();

    return 0;
}