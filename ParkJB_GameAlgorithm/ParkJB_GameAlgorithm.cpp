// ParkJB_GameAlgorithm.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <random>
#include "BlackJack.h"
using namespace std;

int main()
{
	string name = "";
	int level = -1; // level = 난이도 설정용 변수, balance = 내 돈, money = 내 돈과 난이도에 비례
	int money = -1;
	int balance = -1;
	cout << "이름을 입력해주세요." << endl;
	cin >> name;

	while (1)
	{
		cout << endl << "내 잔고를 입력해주세요." << endl;
		cin >> balance;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (balance <= 0)
			cout << "유효한 숫자가 아닙니다." << endl;
		else
			break;
	}

	while (1)
	{
		cout << endl << "난이도를 골라주세요.\t(easy : 1, normal : 2, hard : 3)" << endl;
		cin >> level;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (level < 4 && level > 0)
		{
			switch (level)
			{
			case 1:
				money = balance / 2;
				break;
			case 2:
				money = balance;
				break;
			case 3:
				money = balance * 2;
				break;
			default:
				// 사실 필요 없음
				break;
			}
			break;
		}
		else
			cout << "유효한 숫자가 아닙니다." << endl;
	}
	BlackJack Game(name, balance, "Casino", money);
	Game.Setting();
	
	system("pause");

	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
