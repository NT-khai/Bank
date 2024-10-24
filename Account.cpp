#include "Account.h"
#include<ctime>
#include<random>
#include<iomanip>

//kiem tra ten khong chua so - ki tu dac biet
bool check_name(string name) {
	for (char x : name) {
		if (!isalpha(x) && !isspace(x)) {
			throw invalid_argument("Ten khong chua so va cac ki tu dac biet");
			return false;
		}
	}
	return true;
}
//chuan hoa ten
string chuan_hoa_ten(string& name) {
	for (char& x : name) {
		x = towlower(x);
	}
	name[0] = toupper(name[0]);
	for (int i = 1; i < name.size(); i++) {
		if (isspace(name[i - 1])) {
			name[i] = toupper(name[i]);
		}
	}
	return name;
}
// kiem tra tin dung dan cua dien thoai
bool checkNumberPhone(string Phone) {
	for (char x : Phone) {
		if (!isdigit(x)) {
			throw invalid_argument("khong chua cac ki tu chu, cac ki tu dac biet !");
			return false;
		}
		else {
			if (Phone.size() != 10) {
				throw invalid_argument("So dien thoai chua chinh xac");
				return false;
			}
		}
	}
	return true;
}

// kiem tra mat khau
bool check_pass(string pass) {
	// kiem tra do dai
	bool size = false;
	// kiem tra ki tu
	bool ki_tu = false;
	// kiem tra chu hoa
	bool chu_hoa = false;
	// kiem tra chu thuong
	bool chu_thuong = false;
	// kiem tra so
	bool so = false;
	// kiem tra khoan cach 
	bool khoan_cach = true;

	// check do dai
	if (pass.size() < 8) {
		throw invalid_argument("Mat khau qua ngan !");
	}
	else {
		size = true;
	}
	// kiem tra nhung thu con lai
	for (char x : pass) {
		if (islower(x)) {
			chu_thuong = true;
		}
		else if (isupper(x)) {
			chu_hoa = true;
		}
		else if (isdigit(x)) {
			so = true;
		}
		else if (isspace(x)) {
			khoan_cach = false;
		}
		else {
			ki_tu = true;
		}
	}
	if (!size || !chu_hoa || !chu_thuong || !so || !ki_tu || !khoan_cach) {
		throw invalid_argument("Mat khau phai bao gom chu hoa chu thuong ki tu so khong chua khoang cach");
	}
	return true;
}

string random_accountID(string &id) {
	id += "NTK";
	srand(time(0));
	// tao so tai khoan
	int temp = (rand() % 99999999) +10000000;
	// chuyen chuoi so sang dang string
	id += to_string(temp);
	return id;
}

// dang ki tai khoan moi
void Account::dang_ki() {
	cout << "Dang ki tai khoan ngan hang: \n";
	name:
	cout << "Ho va ten: ";
	try
	{
		getline(cin, accountName);
		// kiem tra ten nguoi dung
		check_name(accountName);

		//chuau hoa lai ten nguoi dung
		chuan_hoa_ten(accountName);
	Phone:
		cout << "So dien thoai: ";
		try
		{
			getline(cin, numberPhone);
			// kiem tra so dien thoai nguoi dung
			checkNumberPhone(numberPhone);
			// tao so tai khoan - he thong tu tao
			random_accountID(accountID);
			cout << "Ma so tai khoan: " << accountID << endl;

			// tao mat khau - yeu cau nhieu hon 8 ki tu
			//co chu hoa, thuong, ki tu, so - khong co dau cach
			pass:
			cout << "Mat khau: ";
			getline(cin, password);
			try
			{
				check_pass(password);
				// dam bao nguoi dung con nho mat khau
				string check_pass_1;
				cout << "Nhap lai mat khau: ";
				getline(cin, check_pass_1);
				if (check_pass_1 == password) {
					// số tiền trong tài khoản hiện tại
					balance = 0.0;
					cout << "Dang ki tai khoan thanh cong";
					cout << "\nThong tin tai khoan nguoi dung\n";
					showAccountInfo();
				}
				else {
					cout << "Ban nhap sai\n";
					cout << "Nhap lai\n";
					goto pass;
				}
			}
			catch (const invalid_argument &e)
			{
				cout << "Loi: " << e.what() << endl;
				goto pass;
			}
		}
		catch (const invalid_argument &e)
		{
			cout << "Loi: " << e.what() << endl;
			goto Phone;
		}

	}
	catch (const invalid_argument &e)
	{
		cout << "Loi: " << e.what() << endl;
		goto name;
	}
}

// dang nhap vao tai khoan
void  Account::dang_nhap() {
	cout << "Dang nhap tai khoan\n";
	cout << "Ma so tai khoan: ";
	string id;
	getline(cin, id);
	int i = 5;
	do
	{
		cout << "Mat khau: ";
		string pass;
		getline(cin, pass);
		if (id == accountID && pass == password) {
			cout << "Dang nhap thanh cong\n";
			return;
		}
		else {
			if (id != accountID) {
				cout << "Tai khoan khong ton tai\n";
				return;
			}
			else if (pass != password) {
				cout << "Mat khau khong chinh xac\n";
				cout << "Ban con " << i << " lan nhap\n";
			}
			i--;
		}
	} while (i>=0);
	cout << "Tai khoan da bi khoa\n";
}

// chuyen tien vao tai khoan
void  Account::deposit(double amount) {
	if (amount < 0) {
		cout << "So tien khong hop le\n";
	}
	else {
		
		
		int so_lan_nhap = 3;
		do
		{
			cout << "Vui long nhap ma OTP de hoan thanh: ";
			// tao ma OTP ngau nhien
			srand(time(0));
			int OTP = (rand() % 9999) + 1000;
			cout << OTP<<endl;
			// ma kiem tra
			int temp_OTP;
			cout << "Nhap: ";
			// so lan nhap OTP
			cin >> temp_OTP;
			if (temp_OTP == OTP) {
				balance += amount;
				// tien hanh luu giao dich
				Transaction luu_giao_dich(this->get_accountID(), "", amount);
				transactionHistory["Nap tien"].push_back(luu_giao_dich);

				cout << "Giao dich thanh cong" << endl;
				return;
			}
			else {
				cout << "Ban con " << so_lan_nhap << " nhap\n";
			}
			--so_lan_nhap;
		} while (so_lan_nhap >= 0);
	}
	cout << "Giao dich that bai";
}

// rut tien trong tai khoan - kiem tra so du truoc khi rut
void  Account::withdraw(double amount) {
	if (amount < 0) {
		throw invalid_argument("So tien khong hop le\n");
	}
	else if (balance - amount < 1000000) {
		throw invalid_argument("So du khong du de rut\n");
	}
	else {
		int i = 3;
		do
		{
			srand(time(0));
			int OTP = (rand() % 9999) + 1000;
			cout << "Nhap ma xac thuc: " << OTP << endl;
			cout << "Nhap: ";
			int check_temp;
			cin >> check_temp;
			if (check_temp == OTP) {
				balance -= amount;
				// tien hanh luu giao dich
				Transaction luu_giao_dich(this->accountID, "", amount);
				transactionHistory["Rut tien"].push_back(luu_giao_dich);
				cout << "Giao dich thanh cong\n";
				return;
			}
			cout << "Ma xac thuc khong chinh xac ban con: " << i << " lan giao dich\n";
			i--;
		} while (i >= 0);

	}
	cout << "Giao dich that bai";
}

// so du hien tai
double  Account::getBalance()const {
	return balance;
}

// hien thi thong tin tai khoan
void  Account::showAccountInfo() {
	cout << fixed << setprecision(0);
	cout << "Ten nguoi dung: " << accountName << endl;
	cout << "So dien thoai: " << numberPhone << endl;
	cout << "Ma so tai khoai: " << accountID << endl;
	cout << "So du: " << balance << endl;
}

void Account::transfer(Account& toAccount, double amount) {
	if (amount < 0) {
		throw invalid_argument("So tien khong hop le!\n");
	}
	else if (this->balance - amount < 1000000) {
		throw invalid_argument("Tien trong tai khoan khong du\n");
	}
	else {
		int i = 3;
		do
		{
			srand(time(0));
			int OTP = (rand() % 9999) + 1000;
			cout << "Nhap ma xac thuc: " << OTP << endl;
			cout << "Nhap: ";
			int check_temp;
			cin >> check_temp;
			if (check_temp == OTP) {
				toAccount.balance += amount;
				this->balance -= amount;
				// tien hanh luu giao dich ben gui
				Transaction luu_giao_dich(this->accountID,toAccount.accountID, amount);
				this->transactionHistory["Giao dich"].push_back(luu_giao_dich);
				// tien hanh luu giao dich ben nhan
				toAccount.transactionHistory["Giao dich"].push_back(luu_giao_dich);
				cout << "Giao dich thanh cong\n";
				return;
			}
			cout << "Ma xac thuc khong chinh xac ban con: " << i << " lan giao dich\n";
			i--;
		} while (i>=0);
	}
	cout << "Giao dich that bai";
}

void Account::showTransaction() {
	cout << "1. Nap tien\n";
	cout << "2. Rut tien\n";
	cout << "3. Chuyen khoan\n";
	cout << "4. Tat ca\n";
	cout << "Chon: ";
	char chosse;
	cin >> chosse;
	switch (chosse)
	{
	case '1':
		if (transactionHistory["Nap tien"].empty()) {
			cout << "Chua co giao dich\n";
		}
		else {
			for (auto x : transactionHistory["Nap tien"]) {
				x.showTransaction_deposit_withdraw();
				cout << "\n======================================\n";
			}
		}
		break;
	case '2':
		if (transactionHistory["Rut tien"].empty()) {
			cout << "Chua co giao dich\n";
		}
		else {
			for (auto x : transactionHistory["Rut tien"]) {
				x.showTransaction_deposit_withdraw();
				cout << "\n======================================\n";
			}
		}
		break;
	case '3':
		if (transactionHistory["Giao dich"].empty()) {
			cout << "Chua co giao dich\n";
		}
		else {
			for (auto x : transactionHistory["Giao dich"]) {
				x.showTransaction();
				cout << "\n======================================\n";
			}
		}
		break;
	default:
		for (auto x : transactionHistory["Nap tien"]) {
			x.showTransaction_deposit_withdraw();
			cout << "\n======================================\n";
		}
		for (auto x : transactionHistory["Rut tien"]) {
			x.showTransaction_deposit_withdraw();
			cout << "\n======================================\n";
		}
		for (auto x : transactionHistory["Giao dich"]) {
			x.showTransaction();
			cout << "\n======================================\n";
		}
		break;
	}
}
// tao ID cho Account
void Account::set_AccountID(){
	this->accountID = "";
	random_accountID(this->accountID);
};