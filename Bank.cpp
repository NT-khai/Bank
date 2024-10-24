#include "Bank.h"
#include<algorithm>


Bank::Bank() {
	listAccount = {};
	listTransaction = {};
}
// them tai khoan moi vao ngan hang
void Bank::addAccount() {
    Account dang_ki_;
    dang_ki_.dang_ki();

    if (listAccount.empty()) {
        listAccount.push_back(dang_ki_);
        return;
    }

    while (true) {
        // Tìm xem ID đã tồn tại trong listAccount chưa
        auto ID = std::find_if(listAccount.begin(), listAccount.end(),
            [&dang_ki_](const Account& acc) {
                return acc.get_accountID() == dang_ki_.get_accountID();
            });

        if (ID == listAccount.end()) {
            // Nếu không tìm thấy ID, thêm tài khoản mới và thoát khỏi vòng lặp
            listAccount.push_back(dang_ki_);
            break;
        }
        else {
            // Nếu ID đã tồn tại, thay đổi ID và lặp lại quá trình
            dang_ki_.set_AccountID();
        }
    }
}

// xoa tai khoan trong ngan hang bang ID
void Bank::removeAccount(string accountID) {
    auto iter = listAccount.begin();  // Khởi tạo iterator
    while (iter != listAccount.end()) { // Duyệt qua toàn bộ danh sách
        if (iter->get_accountID() == accountID) { // So sánh ID
            iter = listAccount.erase(iter); // Xóa và cập nhật iterator
            cout << "Hoan thanh\n";
            return; // Thoát khỏi hàm sau khi xóa
        }
        else {
            ++iter; // Di chuyển tới phần tử tiếp theo
        }
    }
    cout << "Tai khoan khong ton tai\n"; // Thông báo nếu không tìm thấy tài khoản
}

// tim tai khoan
void Bank::findAccount(const string accountID) {
    auto iter = find_if(listAccount.begin(), listAccount.end(), [&accountID](const Account temp) {
        return temp.get_accountID() == accountID;
     });

    if (iter != listAccount.end()) {
        iter->showAccountInfo();
    }
    else {
        cout << "Tai khoan khong ton tai";
    }
}

// giao dien khi dang nhap thanh cong
void Bank::interface_login(Account& temp) {
    while (true) { // Sử dụng vòng lặp để thay thế cho goto
        cout << "1. Thong tin ca nhan\n";
        cout << "2. Rut tien\n";
        cout << "3. Gui tien\n";
        cout << "4. Chuyen khoan\n";
        cout << "5. Lich su giao dich\n";
        cout << "6. Thoat\n"; // Thêm tùy chọn thoát
        cout << "Lua chon: ";

        char chose;
        cin >> chose;
        cin.ignore(); // Bỏ qua ký tự newline
        if (chose=='1')
        {
            cout << "Thong tin tai khoan\n";
            temp.showAccountInfo();
        }
        else if (chose == '2') {
            cout << "So tien can rut: ";
            double amount;
            cin >> amount;
            temp.withdraw(amount);
        }
        else if (chose == '3') {
            cout << "So tien ban muon gui: ";
            double amount;
            cin >> amount;
            temp.deposit(amount);
        }
        else if (chose == '4') {
            string toaccountID;
            cout << "Ma so the nguoi nhan: ";
            getline(cin, toaccountID);
            // luu tam tai khoan de giao dich
            // tim tai khoan dua tren ID
            auto iter = find_if(listAccount.begin(), listAccount.end(), [&toaccountID](const Account temp) {
                return temp.get_accountID() == toaccountID;
            });
            // lay tai khoan gui
            Account &toAccount = *iter;
            cout << "So tien muon chuyen: ";
            double amount;
            cin >> amount;
            temp.transfer(toAccount, amount);          
            
        }
        else if (chose == '5') {
            temp.showTransaction();
        }
        else if(chose == '6') {
            return;
        }
    }
}

//// dang nhap vao ngan hang
void Bank::login() {
    cout << "Dang nhap tai khoan\n";
    cout << "Ma so tai khoan: ";
    string id;
    getline(cin, id);
    // tim tai khoan trong Bank
    auto account = find_if(listAccount.begin(), listAccount.end(), [&id](const Account &temp) {
        return temp.get_accountID() == id;
    });
    
    if (account == listAccount.end()) {
        cout << "\nTai khoan khong ton tai\n";
    }
    else {
        // luu tam tai khoan trong danh sach bank
        Account &temp_ = *account;
        int so_lan = 5;
        do
        {
            cout << "Mat khau: ";
            string pass;
            getline(cin, pass);
            if (pass == temp_.getPass()) {
                cout << "Dang nhap thanh cong\n";
                interface_login(temp_);
                break;
            }
            else {
                cout << "Ban con " << so_lan << " nhap\n";
                so_lan--;
            }
        } while (so_lan>=0);
    }
}