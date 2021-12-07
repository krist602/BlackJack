#pragma once
#include <string>
#include <iostream>
using namespace std;

class Person
{
private:
	string name; // �̸�
	int money; // �ܾ�
public:
	Person(string name, int num) : name(name),money(num)
	{
		// empty;
	}
	void Win(int money) // �¸�
	{
		this->money += money;
	}
	void Lose(int money) // �й�
	{
		if (this->money <= money) // ���� �ݾ׺��� �Ҿ�� �ϴ� �ݾ��� ���ų� ū ���
		{
			this->money = 0;
			cout << " " << name << "���� �Ļ��Ͽ����ϴ�." << endl;
			return;
		}
		this->money -= money;
		return;
			
	}
	void ShowInfo() // ���� ���
	{
		cout << "====================================================" << endl;
		cout << "Name : " << name << endl << "Money : " << money << endl;
		cout << "====================================================" << endl;
	}
	int GetMoney() // ������ ������ �� �ִ��� �Ǵ��Ѵ�.
	{
		return money;
	}
	string GetName() // �� ���� ������ �ؼ� ���������� �����������.
	{
		return name;
	}
};
