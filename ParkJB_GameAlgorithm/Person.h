#pragma once
#include <string>
#include <iostream>
using namespace std;

class Person
{
private:
	string name; // 이름
	int money; // 잔액
public:
	Person(string name, int num) : name(name),money(num)
	{
		// empty;
	}
	void Win(int money) // 승리
	{
		this->money += money;
	}
	void Lose(int money) // 패배
	{
		if (this->money <= money) // 보유 금액보다 잃어야 하는 금액이 같거나 큰 경우
		{
			this->money = 0;
			cout << " " << name << "님이 파산하였습니다." << endl;
			return;
		}
		this->money -= money;
		return;
			
	}
	void ShowInfo() // 정보 출력
	{
		cout << "====================================================" << endl;
		cout << "Name : " << name << endl << "Money : " << money << endl;
		cout << "====================================================" << endl;
	}
	int GetMoney() // 게임을 속행할 수 있는지 판단한다.
	{
		return money;
	}
	string GetName() // 쓸 일이 있을까 해서 만들어놨지만 사용하지않음.
	{
		return name;
	}
};
