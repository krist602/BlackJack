#include "BlackJack.h"

bool comp(const pair<pair<string, string>, int>& a, const pair<pair<string, string>, int>& b)
{
	return a.second < b.second;
}

void BlackJack::Setting()
{
	bool boolean = true;
	Player.ShowInfo(); // Player의 정보를 출력한다.
	Casino.ShowInfo(); // Casino의 정보를 출력한다.
	system("pause");
	Shuffle(); // 카드를 섞는다.
	Start(); // 게임을 시작한다.
}

void BlackJack::Start()
{
	system("cls");
	while (Player.GetMoney() && Casino.GetMoney()) // 기본적으로 누군가 한명이 파산할 때까지 게임한다.
	{
		sum[0] = 0;
		sum[1] = 0;
		playercard.erase(playercard.begin(), playercard.end());
		dealercard.erase(dealercard.begin(), dealercard.end());
		Round(Betting()); // 라운드 시작
		if (card.empty())
		{
			cout << "덱에 카드가 없습니다." << endl;
			break;
		}
				
		if (Player.GetMoney() < 1) // 플레이어 파산시
		{
			cout << "돈이 없습니다. 패배하셨습니다." << endl;
			break;
		}
		else if (Casino.GetMoney() < 1) // 카지노 파산시
		{
			cout << "Casino의 보유 금액이 없습니다. 승리하셨습니다." << endl;
			break;
		}

		cout << "게임을 계속 하시겠습니까?\t";
		if (!YorN())
			break;
	}
	cout << "게임을 종료합니다." << endl;
	cout << endl << endl;
	cout << Player.GetName() << "님의 최종 보유 금액 " << Player.GetMoney();
	cout << endl;
	return;
}

void BlackJack::Shuffle()
{
	srand((unsigned int)time(NULL));
	int seed = -1;
	for (int i = 1; i < 14; i++) //vector<> card에 문양과 숫자, 그리고 난수를 차례대로 집어넣는다. 이후 난수를 기준으로 정렬한다.
	{
		seed = rand();
		switch (i)
		{
		case 1:
			card.push_back(make_pair(make_pair("♠", "A"), seed));
			break;
		case 11:
			card.push_back(make_pair(make_pair("♠", "J"), seed));
			break;
		case 12:
			card.push_back(make_pair(make_pair("♠", "Q"), seed));
			break;
		case 13:
			card.push_back(make_pair(make_pair("♠", "K"), seed));
			break;
		default:
			card.push_back(make_pair(make_pair("♠", (to_string)(i)), seed));
			break;
		}
	}
	for (int i = 1; i < 14; i++)
	{
		seed = rand();
		switch (i)
		{
		case 1:
			card.push_back(make_pair(make_pair("♣", "A"), seed));
			break;
		case 11:
			card.push_back(make_pair(make_pair("♣", "J"), seed));
			break;
		case 12:
			card.push_back(make_pair(make_pair("♣", "Q"), seed));
			break;
		case 13:
			card.push_back(make_pair(make_pair("♣", "K"), seed));
			break;
		default:
			card.push_back(make_pair(make_pair("♣", (to_string)(i)), seed));
			break;
		}
	}
	for (int i = 1; i < 14; i++)
	{
		seed = rand();
		switch (i)
		{
		case 1:
			card.push_back(make_pair(make_pair("◇", "A"), seed));
			break;
		case 11:
			card.push_back(make_pair(make_pair("◇", "J"), seed));
			break;
		case 12:
			card.push_back(make_pair(make_pair("◇", "Q"), seed));
			break;
		case 13:
			card.push_back(make_pair(make_pair("◇", "K"), seed));
			break;
		default:
			card.push_back(make_pair(make_pair("◇", (to_string)(i)), seed));
			break;
		}
	}
	for (int i = 1; i < 14; i++)
	{
		seed = rand();
		switch (i)
		{
		case 1:
			card.push_back(make_pair(make_pair("♡", "A"), seed));
			break;
		case 11:
			card.push_back(make_pair(make_pair("♡", "J"), seed));
			break;
		case 12:
			card.push_back(make_pair(make_pair("♡", "Q"), seed));
			break;
		case 13:
			card.push_back(make_pair(make_pair("♡", "K"), seed));
			break;
		default:
			card.push_back(make_pair(make_pair("♡", (to_string)(i)), seed));
			break;
		}
	}

	sort(card.begin(), card.end(), comp); // seed값을 기준으로 정렬해준다.
}

void BlackJack::Hit(bool dealer, bool * ace) //카드를 가져온다. bool dealer가 true이면 dealer의 카드덱에, false이면 player의 카드덱에 카드를 넣는다.
{
	int num = 0; 
	//bool * ace ::  블랙잭에서 A카드는 1 혹은 11로 본인에게 유리하게 사용할 수 있기때문에 A카드가 있다면 true로 바꿔서 사용.
	if (card.empty())
	{
		cout << "카드덱이 다 떨어졌기 때문에 게임을 종료합니다." << endl;
		return;
	}
	if (!dealer)
	{
		playercard.push_back(make_pair(card.back().first.first, card.back().first.second));
		if (card.back().first.second == "A")
		{
			*ace = true;
			num = 11;
		}
		else if (card.back().first.second == "J" || card.back().first.second == "Q" || card.back().first.second == "K") // JQK는 10으로 계산.
		{
			num = 10;
		}
		else
			num = (stoi)(card.back().first.second);
		card.pop_back();
		sum[0] += num;
		if (sum[0]>21 && *ace) // 버스트(21이 넘었)지만 A카드가 있기 때문에 합산에서 10을 빼고, bool값을 false로 돌려준다.
		{
			*ace = false;
			sum[0] -= 10;
		}
		PrintCard(dealer); // 카드 인쇄
	}
	else //딜러 역시 Hit함수는 비슷하나, 그래픽적인 요소와 카드값 합산때문에 if문으로 구분
	{
		dealercard.push_back(make_pair(card.back().first.first, card.back().first.second));
		if (card.back().first.second == "A")
		{
			*ace = true;
			num = 11;
		}
		else if (card.back().first.second == "J" || card.back().first.second == "Q" || card.back().first.second == "K")
		{
			num = 10;
		}
		else
			num = (stoi)(card.back().first.second);
		card.pop_back();
		sum[1] += num;
		if (sum[1] > 21 && *ace)
		{
			*ace = false;
			sum[1] -= 10;
		}
		PrintCard(dealer);
	}
	return;
}

void BlackJack::PrintCard(bool dealer) // 그래픽적인 요소 사용
{
	unsigned int i = 0;
	system("cls");
	cout << "====================================================" << endl;
	cout << " 플레이어의 카드\t플레이어의 카드 합 : " << sum[0] << "\t\t\t플레이어의 보유 금액 : " << Player.GetMoney() << endl;
	for (i = 0; i < playercard.size(); i++)
	{
		cout << "┌───┐" << " ";
	}
	cout << endl;
	for (i = 0; i < playercard.size(); i++)
	{
		cout << "│ " << playercard[i].first << "│" << " ";
	}
	cout << endl;
	for (i = 0; i < playercard.size(); i++)
	{
		if (playercard[i].second == "10")
		{
			cout << "│ " << playercard[i].second << "│" << " ";
		}
		else
			cout << "│  " << playercard[i].second << "│" << " ";
	}
	if (playercard.size()==2 && sum[0]==21)
		cout << "BLACK JACK ! ! !";
	cout << endl;
	
	for (i = 0; i < playercard.size(); i++)
	{
		cout << "└───┘" << " ";
	}
	cout << endl;

	if (dealer)
	{

		for (i = 0; i < dealercard.size(); i++)
		{
			cout << "┌───┐" << " ";
		}
		cout << endl;
		for (i = 0; i < dealercard.size(); i++)
		{
			cout << "│ " << dealercard[i].first << "│" << " ";
		}
		cout << endl;
		for (i = 0; i < dealercard.size(); i++)
		{
			if (dealercard[i].second == "10")
			{
				cout << "│ " << dealercard[i].second << "│" << " ";
			}
			else
				cout << "│  " << dealercard[i].second << "│" << " ";
		}
		if (dealercard.size()==2 && sum[1]==21)
			cout << "BLACK JACK ! ! !";
		cout << endl;
		for (i = 0; i < dealercard.size(); i++)
		{
			cout << "└───┘" << " ";
		}
		cout << endl;
		cout << " 딜러의 카드\t\t딜러의 카드 합 : " << sum[1] << "\t\t\t딜러의 보유 금액 : " << Casino.GetMoney() << endl;
	}

	cout << "====================================================" << endl;
}

int BlackJack::Betting() //판돈 입력.
{
	int bet = -1;
	while (1)
	{
		cout << "====================================================" << endl;
		cout << "이번 라운드에 걸 판돈을 입력해주세요.\t\t내 보유 금액 : " << Player.GetMoney() << "\t" << "카지노측 보유 금액 : " << Casino.GetMoney() << endl;
		cin >> bet;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (bet <= 0)
		{
			cout << "유효한 숫자가 아닙니다." << endl;
			continue;
		}
		else if (bet > Player.GetMoney() || bet > Casino.GetMoney()) //입력한 판돈보다 어느 한 사람의 돈이 적다면
		{
			if (Player.GetMoney() < Casino.GetMoney()) // 플레이어의 돈이 적으면 올인 여부를 질문
			{
				cout << "입력하신 금액보다 보유하신 금액이 적습니다. 올인하시겠습니까?\t";
				if (YorN())
				{
					return Player.GetMoney();
				}
				else
					continue;
			}
			else // 카지노 측의 돈이 적으면 카지노가 보유한 값으로 입력
			{
				cout << "입력하신 금액보다 카지노측이 보유한 금액이 적습니다. 최대금액으로 입력합니다." << endl;
				system("pause");
				return Casino.GetMoney();
			}
		}
		cout << bet << "원을 배팅합니다." << endl;
		system("pause");
		return bet;
	}
}

void BlackJack::PlayerTurn()
{
	if (card.empty())
		return;
	bool ace = false;
	Hit(false,&ace); //Player의 턴이면 false를 집어넣음.
	if (card.empty())
		return;
	Hit(false,&ace);
	if (card.empty())
		return;
	if (sum[0] == 21) // 기본 2장이 21을 달성시 블랙잭이므로 더이상 카드를 뽑지 않는다.
		return;
	else
	{
		int select = -1;
		while (1)
		{
			cout << "현재 열린 카드의 값 : " << sum[0] << endl;
			cout << "카드를 더 여시겠습니까?\t";

			if (YorN())
				Hit(false,&ace);
			else
				break;
			if (sum[0] >= 21) //21이거나 21이 넘으면 더 이상 카드를 가져올 필요가 없다.
			{
				break;
			}
		}
	}
	return;
}

void BlackJack::DealerTurn()
{
	if (card.empty())
		return;
	bool ace = false;
	Hit(true,&ace); //Dealer의 턴이면 true값을 집어넣음.
	if (card.empty())
		return;
	Hit(true,&ace);
	if (card.empty())
		return;
	if (playercard.size()==2 && sum[0] == 21) //플레이어의 카드가 2장이면서 합이 21인 경우는 블랙잭의 경우밖에 없기때문에 딜러는 카드를 더 뽑지 않는다.
		return;

	while (sum[1] < 17) // 딜러는 본인의 카드가 합이 17 미만이면 카드를 추가한다.
	{
		Hit(true,&ace);
	}
}

bool BlackJack::YorN() // Yes or No를 여러 번 반복하는 것을 하나로 묶어놨다.
{
	cout << "(Yes : 1 / No : 2)" << endl;
	while (1)
	{
		int select;
		cin >> select;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		switch (select)
		{
		case 1:
			return true;
		case 2:
			return false;
		default:
			cout << "유효한 선택이 아닙니다." << endl;
			break;
		}
	}
}

void BlackJack::Round(int bet) // Round 진행
{
	PlayerTurn(); // 플레이어가 먼저 게임을 진행

	if (sum[0] > 21) //카드의 합이 21을 넘으면 버스트이기때문에 바로 라운드를 종료한다.
	{
		cout << "숫자의 합이 21을 초과하였습니다. ";
		WhoisWin(bet,false);
		return;
	}
	cout << "딜러의 차례입니다." << endl; // 플레이어의 카드 합이 21이 넘지 않았다면 딜러의 턴을 진행한다.
	DealerTurn();

	// 누군가 BLACK JACK을 달성했다면
	if(sum[0] == 21 && sum[1] == 21)
	{
		cout << "동점입니다. 이번 라운드의 승자는 없습니다." << endl;
		return;
	}
	else if (sum[0] == 21 && playercard.size() == 2) // 플레이어가 블랙잭 달성
	{
		cout << "BLACK JACK!" << endl;
		if (Casino.GetMoney() < (int)(bet * 1.5))
		{
			WhoisWin(Casino.GetMoney(), true);
		}
		WhoisWin((int)(bet * 1.5), true);
		return;
	}
	else if (sum[1] == 21 && dealercard.size() == 2) // 딜러가 블랙잭 달성
	{
		cout << "BLACK JACK!" << endl;
		WhoisWin(bet, false);
		return;
	}

	if (sum[0] > sum[1] || sum[1] > 21)
		WhoisWin(bet, true);
	else if (sum[0] < sum[1])
		WhoisWin(bet, false);
	else
		cout << "동점입니다. 이번 라운드의 승자는 없습니다." << endl;
	
	return;
}

void BlackJack::WhoisWin(int bet, bool win) //승자를 판별하여 선언
{
	if (win)
	{
		cout << "당신의 승리입니다." << endl;
		Player.Win(bet);
		Casino.Lose(bet);
	}
	else
	{
		cout << "딜러의 승리입니다." << endl;
		Player.Lose(bet);
		Casino.Win(bet);
	}
}