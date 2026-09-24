#include <iostream>
#include <string>
#include <cctype>
using namespace std;

#define MAX 100

// ==========================================
// HÀM HỖ TRỢ XỬ LÝ CHUỖI (STRINGS HELPER)
// ==========================================

// Hàm chuyển toàn bộ chuỗi về chữ thường (dùng cho so sánh không phân biệt hoa/thường)
string toLowerString(string str) {
    for (char &c : str) {
        c = tolower(c);
    }
    return str;
}

// STRINGS 2: Chuẩn hóa tên món ăn (Viết hoa chữ cái đầu, bỏ khoảng trắng thừa)
string formatFoodName(string name) {
    string result = "";
    int n = name.length();
    int i = 0;

    // Bỏ khoảng trắng thừa ở đầu
    while (i < n && isspace(name[i])) i++;

    bool newWord = true;
    while (i < n) {
        // Bỏ khoảng trắng thừa ở giữa
        if (isspace(name[i])) {
            while (i < n && isspace(name[i])) i++;
            if (i < n) result += " ";
            newWord = true;
        } else {
            if (newWord) {
                result += toupper(name[i]);
                newWord = false;
            } else {
                result += tolower(name[i]);
            }
            i++;
        }
    }
    return result;
}


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

        // STRINGS 2: Chuẩn hóa tên món ăn ngay sau khi nhập
        name = formatFoodName(name);

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

    // STRINGS 3: Tạo mã đơn hàng theo quy tắc (Tên + Số điện thoại)
    void generateOrderID(string phone) {
        string shortName = "";
        for (char c : customerName) {
            if (!isspace(c)) shortName += toupper(c);
        }
        string shortPhone = (phone.length() >= 4) ? phone.substr(phone.length() - 4) : phone;
        id = "DH_" + shortName + "_" + shortPhone;
        cout << " --> Auto generated Order ID: " << id << endl;
    }

    void inputInfo (FOOD availableFood[], int availableCount, string resPhone = ""){ // Nhập thông tin order

        cin.ignore();

        cout << "Enter the Customer Name: ";
        getline (cin, customerName);

        // STRINGS 3: Tự động tạo mã đơn hàng từ tên khách + SĐT
        generateOrderID(resPhone);

        cout << "Enter the address: ";
        getline (cin, address);

        // Chức năng 4: Tìm món ăn theo mã hoặc tên
        string foodSearch;
        cout << "Enter the ID or Name of the food u wanna search: ";
        getline (cin, foodSearch);

        bool found = false;
        for (int i = 0; i < availableCount; i++){
            if (foodSearch == availableFood[i].id || foodSearch == availableFood[i].name){
                food = availableFood[i];
                found = true;
                break;
            }
        }

        if (!found){
            cout << "Sorry the ID/Name of the food does not exist" << endl;
            food.inputInfo();
        }

        cout << "Enter the quantity: ";
        cin >> quantity;

        cin.ignore();

        cout << "Enter the order status (Completed / Pending / Cancelled): ";
        getline (cin, status);

        // STRINGS 10: In thông báo giao hàng ngay sau khi tạo đơn thành công
        displayDeliveryNotification();
    }

    // STRINGS 10: Tạo và in thông báo giao hàng
    void displayDeliveryNotification() {
        cout << "\n[DELIVERY NOTIFICATION]: Don hang [" << id << "] cua "
             << customerName << " dang duoc giao den [" << address 
             << "]. Cam on ban!" << endl;
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
    int foodCount = 0;
    ORDER orders[MAX];      // Danh sách đơn hàng
    int orderCount = 0;          

    // Chức năng 1: Nhập thông tin của cửa hàng
    void inputRestaurantInfo(){
        cout << "***********************************" << endl;

        cout << "Enter the name of the restaurant: ";
        getline (cin, name);

        // STRINGS 1: Nhập và hiển thị tên cửa hàng 
        cout << "Chao mung den voi " << name << "!" << endl;

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

    // Chức năng 4 (hỗ trợ): Tìm món ăn theo id hoặc name (Cập nhật hỗ trợ STRINGS 4)
    int findFoodIdex(string key){
        string lowerKey = toLowerString(key);
        for (int i = 0; i < foodCount; i++){
            if (toLowerString(foods[i].id) == lowerKey || toLowerString(foods[i].name) == lowerKey){
                return i;
            }
        }
        return -1;
    }

    // STRINGS 4: Kiểm tra món ăn xem có tồn tại trong cửa hàng hay không
    void checkFoodExists(string key) {
        int idx = findFoodIdex(key);
        if (idx != -1) {
            cout << " --> Mon an [" << foods[idx].name << "] CO TRONG MENU cua cua hang." << endl;
            foods[idx].outputInfo();
        } else {
            cout << " --> Mon an [" << key << "] KHONG TON TAI trong cua hang!" << endl;
        }
    }

    // Chức năng 5: Cập nhật giá hoặc số lượng món ăn
    void updateFoodIndex (string key){
        int idx = findFoodIdex(key);
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
    void createOrder() {
        if (orderCount < MAX) {
            cout << "\n=== CREATE NEW ORDER ===" << endl;
            ORDER newOrder;
            newOrder.inputInfo(foods, foodCount, phone);

            // Kiểm tra số lượng tồn kho trước khi duyệt đơn
            int idx = findFoodIdex(newOrder.food.id);
            if (idx != -1) {
                if (foods[idx].quantity >= newOrder.quantity) {
                    foods[idx].quantity -= newOrder.quantity; // Trừ bớt hàng trong kho
                    orders[orderCount] = newOrder;
                    orderCount++;
                    cout << " --> Order created successfully!" << endl;
                } else {
                    cout << " --> Order failed: Not enough quantity in stock!" << endl;
                }
            } else {
                orders[orderCount] = newOrder;
                orderCount++;
                cout << " --> Order created with custom food entry!" << endl;
            }
        } else {
            cout << " --> Order list is full!" << endl;
        }
    }

    // Chức năng 7: Kiểm tra món ăn có tồn tại và đủ số lượng
    bool isFoodAvailable (string key, int reqQuantity){
        int idx = findFoodIdex(key);
        if (idx != -1){
            return foods[idx].quantity >= reqQuantity;
        }
        return false;
    }

    // Chức năng 9: Hiển thị danh sách các đơn hàng
    void displayOrders() {
        cout << "\n<<<<<<<<<<<< ORDERS LIST >>>>>>>>>>>>" << endl;
        if (orderCount == 0) {
            cout << "No orders created yet." << endl;
            return;
        }
        for (int i = 0; i < orderCount; i++) {
            orders[i].outputInfo();
        }
    }

    // Chức năng 10: Tìm đơn hàng theo mã 
    void findOrderbyID (string orderID){
        for (int i = 0; i < orderCount; i++){
            if (orders[i].id == orderID){
                cout << "\n --> Found order: " << endl;
                orders[i].outputInfo();
                return;
            }
        }
        cout << "--> Order ID: " << orderID << " not found!" << endl;
    }

    // STRINGS 6 / Chức năng 11: Thay đổi / Cập nhật trạng thái đơn hàng
    void updateOrderStatus (string orderID, string newStatus){
        for (int i = 0; i < orderCount; i++){
            if (orders[i].id == orderID){
                orders[i].status = newStatus;
                cout << " --> Updated order status successfully to [" << newStatus << "]!" << endl;
                return;
            }
        }
        cout << " --> Order ID " << orderID << " not found!" << endl;
    }

    // STRINGS 7: Tìm các đơn hàng theo tên khách hàng (Không phân biệt hoa/thường)
    void searchOrdersByCustomerName(string keyword) {
        cout << "\n========== TIM KIEM DON HANG THEO TEN KHACH ==========" << endl;
        string lowerKey = toLowerString(keyword);
        bool found = false;

        for (int i = 0; i < orderCount; i++) {
            if (toLowerString(orders[i].customerName).find(lowerKey) != string::npos) {
                orders[i].outputInfo();
                found = true;
            }
        }

        if (!found) {
            cout << "Khong tim thay don hang nao cua khach hang chua tu khoa: " << keyword << endl;
        }
    }

    // STRINGS 9: Thống kê món ăn bán chạy (Đếm xem xuất hiện trong bao nhiêu đơn hàng)
    void countFoodOccurrences(string foodName) {
        string lowerFood = toLowerString(foodName);
        int count = 0;

        for (int i = 0; i < orderCount; i++) {
            if (toLowerString(orders[i].food.name) == lowerFood || toLowerString(orders[i].food.id) == lowerFood) {
                count++;
            }
        }

        cout << "\n --> Mon an [" << foodName << "] da xuat hien trong " << count << " don hang." << endl;
    }

    // Chức năng 12: Thống kê tổng doanh thu của các đơn hàng đã hoàn thành
    double calculateCompletedReveue(){
        double totalRevenue = 0;
        for (int i = 0; i < orderCount; i++){
            if (orders[i].status == "Completed" || orders[i].status == "Hoàn thành"){
                totalRevenue += orders[i].getTotalPrice();
            }
        }
        return totalRevenue;
    }
};

int main(){

    RESTAURANT myrestaurant;

    cout << "========================================" << endl;
    cout << "===== WELCOME TO RESTAURANT SYSTEM =====" << endl;
    cout << "========================================" << endl;

    // STRINGS 1 / Chức năng 1: Nhập thông tin của cửa hàng
    myrestaurant.inputRestaurantInfo();
    
    // Vòng lặp menu chính 
    while (true){
        cout << "\n========== MENU QUAN LY NHA HANG ==========" << endl;
        cout << "1. Them mon an moi (Tu dong chuan hoa ten)" << endl;
        cout << "2. Hien thi danh sach mon an (Menu)" << endl;
        cout << "3. Cap nhat gia hoac so luong mon an" << endl;
        cout << "4. Kiem tra mon an co trong menu" << endl;
        cout << "5. Tao don hang moi (Tu dong tao ma DH & thong bao)" << endl;
        cout << "6. Hien thi danh sach don hang" << endl;
        cout << "7. Tim don hang theo ma ID" << endl;
        cout << "8. Tim don hang theo ten khach hang" << endl;
        cout << "9. Thay doi trang thai don hang" << endl;
        cout << "10. Thong ke mon an da xuat hien bao nhieu don" << endl;
        cout << "11. Thong ke doanh thu (Don 'Completed')" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon chuc nang: ";

        int choice;
        cin >> choice;

        if (choice == 0 ){
            cout << "Existing program ..." << endl;
            break;
        }

        if (choice  == 1){
            myrestaurant.addFood();
        }
        else if (choice == 2){
            myrestaurant.displatMenu();
        }
        else if (choice == 3){
            cin.ignore();
            string key;
            cout << "Enter the ID or Name of the food u wanna update: ";
            getline (cin, key);
            myrestaurant.updateFoodIndex(key);
        }
        else if (choice == 4){
            // STRINGS 4: Kiểm tra món ăn
            cin.ignore();
            string foodName;
            cout << "Nhap ten/ma mon an can kiem tra: ";
            getline(cin, foodName);
            myrestaurant.checkFoodExists(foodName);
        }
        else if (choice == 5){
            // STRINGS 3 & 10: Tạo đơn hàng
            myrestaurant.createOrder();
        }
        else if (choice == 6){
            myrestaurant.displayOrders();
        }
        else if (choice == 7){
            cin.ignore();
            string id;
            cout << "Enter ID u wanna search: ";
            getline (cin, id);
            myrestaurant.findOrderbyID(id);
        }
        else if (choice == 8){
            // STRINGS 7: Tìm các đơn hàng theo tên khách
            cin.ignore();
            string customerName;
            cout << "Nhap ten khach hang can tim: ";
            getline(cin, customerName);
            myrestaurant.searchOrdersByCustomerName(customerName);
        }
        else if (choice == 9){
            // STRINGS 6: Thay đổi trạng thái đơn hàng
            cin.ignore();
            string id, status;
            cout << "Enter the id of the order: ";
            getline (cin, id);
            cout << "Enter new status (Dang chuan bi / Dang giao / Hoan thanh / Da huy): ";
            getline (cin, status);
            myrestaurant.updateOrderStatus(id, status);
        }
        else if (choice == 10){
            // STRINGS 9: Thống kê món ăn bán chạy
            cin.ignore();
            string foodName;
            cout << "Nhap ten mon an can thong ke: ";
            getline(cin, foodName);
            myrestaurant.countFoodOccurrences(foodName);
        }
        else if (choice == 11){
            cout << "\n --> Tong doanh thu don hang: " << myrestaurant.calculateCompletedReveue() << endl;
        }
        else {
            cout << "Lua chon khong hop le. Vui long nhap lai" << endl;
        }
    }

    return 0;
}