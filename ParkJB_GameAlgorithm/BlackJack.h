#pragma once

#include "Person.h"
#include <vector>
#include <iostream>
#include <algorithm>

class BlackJack
{
private:
	Person Player; // 플레이어
	Person Casino; // 카지노측. 실제론 카지노의 돈은 파산하지 않겠지만, 게임이기 때문에 승리 조건을 위해 카지노의 돈도 유한하게 설정.
	vector<pair<pair<string, string>, int>> card; // 52장의 카드를 섞어서 한장씩 뽑기 위한 카드 덱
	vector<pair<string,string>> playercard; // 그래픽 요소를 위해 사용
	vector<pair<string, string>> dealercard; // 그래픽 요소를 위해 사용
	int sum[2]; // 각 라운드마다 딜러와 플레이어의 카드 합
public:
	BlackJack(string name, int balance, string dealer, int money) : Player(name, balance), Casino(dealer, money), sum{ 0 }
	{
		// empty;
	}
	void Setting(); // 기본 게임 세팅
	void Shuffle(); // 카드를 섞는다
	void Start(); // 게임 시작 함수
	void Hit(bool dealer, bool * ace); // 카드를 받는다.
	void PrintCard(bool dealer); // 그래픽적인 요소
	int Betting(); // 판돈 배팅에 관한 함수
	void PlayerTurn(); // 플레이어의 차례에 경우의 수를 넣어놨다.
	void DealerTurn(); // 딜러 턴의 차례에 경우의 수를 넣어놨다.
	bool YorN(); // (Yes : 1, No : 2)를 묻는 것이 너무 많아 함수로 묶어놓음
	void Round(int bet); // 한 라운드를 진행한다.
	void WhoisWin(int bet,bool win); // 라운드가 끝나고 승자를 판별하여 돈을 지급한다.
};

