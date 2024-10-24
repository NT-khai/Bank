#pragma once
#include"Account.h"
#include"Transaction.h"
#include<iostream>
#include<string>
#include<cctype>
#include<vector>
using namespace std;

class Bank
{
private:
	// danh sach luu tai khoan
	vector<Account>listAccount;
	// danh sach luu tat ca cac giao dich
	vector<Transaction> listTransaction;

public:
	// ham khoi tao
	Bank();
	// them tai khoan moi vao ngan hang
	void addAccount();
	// xoa tai khoan trong ngan hang bang ID
	void removeAccount(string accountID);
	// tim tai khoan
	void findAccount( const string accountID);
//	// xuat tat ca cac giao dich
//	void showAllTransactions();
	// dang nhap vao ngan hang
	void login();
	//
	void interface_login(Account& temp);
	//
	void display() {
		for (auto x : listAccount) {
			x.showAccountInfo();
		}
	}
};

