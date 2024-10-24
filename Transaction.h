#pragma once
#include<iostream>
#include<string>
#include<ctime>

using namespace std;

class Transaction
{
private:
	// so luot gia dich
	static int n;
	// ma giao dich
	 string trancsactionID;
	 // tai khoan gui
	 string fromAccount;
	 // tai khoan nhan
	 string toAccount;
	 // so tien giao dich
	 double amount;
	 // thoi gian giao dich
	 char timestamp[26];

public:
	// lưu giao dich file txt
	Transaction(string fromAccountID="", string toAccountID="", double amount=0.0);
	// hien thi chi tiet giao dich chuyen khoan
	void showTransaction();
	// hien thi rut-gui tien
	void showTransaction_deposit_withdraw();
};

