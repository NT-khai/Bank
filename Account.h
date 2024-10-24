#pragma once
#include<iostream>
#include<string>
#include<cctype>
#include<map>
#include"Transaction.h"
#include<vector>

using namespace std;

// lop tai khoan nguoi dung
class Account
{
private:
	// ma so tai khoan la duy nhat
	string accountID;
	// ten chu so huu tai khoan
	string accountName;
	// so du trong tai khoan
	double balance;
	// mat khau vao tai khoan
	string password;
	// so dien thoai
	string numberPhone;
	// lich su giao dich
	map<string, vector<Transaction>> transactionHistory;

public:
	// dang ki tai khoan moi
	void dang_ki();
	// dang nhap vao tai khoan
	void dang_nhap();
	// chuyen tien vao tai khoan
	void deposit(double amount);
	// rut tien trong tai khoan - kiem tra so du truoc khi rut
	void withdraw(double amount);
	// so du hien tai
	double getBalance()const;
	// hien thi thong tin tai khoan
	void showAccountInfo();
	// Giao dich
	void transfer(Account& toAccount, double amount);
	// xuat cac giao dich
	void showTransaction();
	string get_accountID()const {
		return accountID;
	}
	// tao ID cho Account
	void set_AccountID();

	bool operator==(const std::string& id) const {
		return accountID == id;
	}

	string getPass()const {
		return password;
	}
};

