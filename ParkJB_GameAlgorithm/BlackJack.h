#pragma once

#include "Person.h"
#include <vector>
#include <iostream>
#include <algorithm>

class BlackJack
{
private:
	Person Player; // �÷��̾�
	Person Casino; // ī������. ������ ī������ ���� �Ļ����� �ʰ�����, �����̱� ������ �¸� ������ ���� ī������ ���� �����ϰ� ����.
	vector<pair<pair<string, string>, int>> card; // 52���� ī�带 ��� ���徿 �̱� ���� ī�� ��
	vector<pair<string,string>> playercard; // �׷��� ��Ҹ� ���� ���
	vector<pair<string, string>> dealercard; // �׷��� ��Ҹ� ���� ���
	int sum[2]; // �� ���帶�� ������ �÷��̾��� ī�� ��
public:
	BlackJack(string name, int balance, string dealer, int money) : Player(name, balance), Casino(dealer, money), sum{ 0 }
	{
		// empty;
	}
	void Setting(); // �⺻ ���� ����
	void Shuffle(); // ī�带 ���´�
	void Start(); // ���� ���� �Լ�
	void Hit(bool dealer, bool * ace); // ī�带 �޴´�.
	void PrintCard(bool dealer); // �׷������� ���
	int Betting(); // �ǵ� ���ÿ� ���� �Լ�
	void PlayerTurn(); // �÷��̾��� ���ʿ� ����� ���� �־����.
	void DealerTurn(); // ���� ���� ���ʿ� ����� ���� �־����.
	bool YorN(); // (Yes : 1, No : 2)�� ���� ���� �ʹ� ���� �Լ��� �������
	void Round(int bet); // �� ���带 �����Ѵ�.
	void WhoisWin(int bet,bool win); // ���尡 ������ ���ڸ� �Ǻ��Ͽ� ���� �����Ѵ�.
};

