#include "Transaction.h"
#include <chrono>
#include <ctime>
#include<iomanip>

// lay thoi gian thuc
void getCurrentTime(char a[26]) {
    // Khai báo biến thời gian hiện tại
    auto current_time = std::chrono::system_clock::now();

    // Chuyển đổi thời gian sang time_t
    std::time_t current_time_t = std::chrono::system_clock::to_time_t(current_time);

    // Sử dụng ctime_s để tránh lỗi C4996
    ctime_s(a, sizeof(char) * 26, &current_time_t);
}

// ham khoi tao doi tuong giao dich
Transaction::Transaction( string fromAccountID,string toAccountID, double amount) {
	// Tao ma giao dich
	trancsactionID = "NTK_";
	trancsactionID += to_string(n);
    // from Account
	this->fromAccount = fromAccountID;
    // to Account
	this->toAccount = toAccountID;
    // số tiền giao dịch
	this->amount = amount;
    // xác định thời gian chính xác thực hiện giao dịch
    getCurrentTime(timestamp);
    n++;

}
// hien thi chi tiet giao dich chuyen khoan
void Transaction::showTransaction() {
    cout << fixed << setprecision(0);
    cout << "Ma giao dich: " << trancsactionID << endl;
    cout << "So tai khoan thuc hien giao dich: " << fromAccount << endl;
    cout << "So tai khoan nhan giao dich: " << toAccount << endl;
    cout << "So tien trong giao dich: " << amount << endl;
    cout << "Thoi gian: " << timestamp << endl;
}
void Transaction::showTransaction_deposit_withdraw() {
    cout << fixed << setprecision(0);
    cout << "Ma giao dich: " << trancsactionID << endl;
    cout << "So tai khoan thuc hien giao dich: " << fromAccount << endl;
    cout << "So tien trong giao dich: " << amount << endl;
    cout << "Thoi gian: " << timestamp << endl;
}
int Transaction::n = 0;