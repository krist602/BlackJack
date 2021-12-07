#include "BlackJack.h"

bool comp(const pair<pair<string, string>, int>& a, const pair<pair<string, string>, int>& b)
{
	return a.second < b.second;
}

void BlackJack::Setting()
{
	bool boolean = true;
	Player.ShowInfo(); // Player�� ������ ����Ѵ�.
	Casino.ShowInfo(); // Casino�� ������ ����Ѵ�.
	system("pause");
	Shuffle(); // ī�带 ���´�.
	Start(); // ������ �����Ѵ�.
}

void BlackJack::Start()
{
	system("cls");
	while (Player.GetMoney() && Casino.GetMoney()) // �⺻������ ������ �Ѹ��� �Ļ��� ������ �����Ѵ�.
	{
		sum[0] = 0;
		sum[1] = 0;
		playercard.erase(playercard.begin(), playercard.end());
		dealercard.erase(dealercard.begin(), dealercard.end());
		Round(Betting()); // ���� ����
		if (card.empty())
		{
			cout << "���� ī�尡 �����ϴ�." << endl;
			break;
		}
				
		if (Player.GetMoney() < 1) // �÷��̾� �Ļ��
		{
			cout << "���� �����ϴ�. �й��ϼ̽��ϴ�." << endl;
			break;
		}
		else if (Casino.GetMoney() < 1) // ī���� �Ļ��
		{
			cout << "Casino�� ���� �ݾ��� �����ϴ�. �¸��ϼ̽��ϴ�." << endl;
			break;
		}

		cout << "������ ��� �Ͻðڽ��ϱ�?\t";
		if (!YorN())
			break;
	}
	cout << "������ �����մϴ�." << endl;
	cout << endl << endl;
	cout << Player.GetName() << "���� ���� ���� �ݾ� " << Player.GetMoney();
	cout << endl;
	return;
}

void BlackJack::Shuffle()
{
	srand((unsigned int)time(NULL));
	int seed = -1;
	for (int i = 1; i < 14; i++) //vector<> card�� ����� ����, �׸��� ������ ���ʴ�� ����ִ´�. ���� ������ �������� �����Ѵ�.
	{
		seed = rand();
		switch (i)
		{
		case 1:
			card.push_back(make_pair(make_pair("��", "A"), seed));
			break;
		case 11:
			card.push_back(make_pair(make_pair("��", "J"), seed));
			break;
		case 12:
			card.push_back(make_pair(make_pair("��", "Q"), seed));
			break;
		case 13:
			card.push_back(make_pair(make_pair("��", "K"), seed));
			break;
		default:
			card.push_back(make_pair(make_pair("��", (to_string)(i)), seed));
			break;
		}
	}
	for (int i = 1; i < 14; i++)
	{
		seed = rand();
		switch (i)
		{
		case 1:
			card.push_back(make_pair(make_pair("��", "A"), seed));
			break;
		case 11:
			card.push_back(make_pair(make_pair("��", "J"), seed));
			break;
		case 12:
			card.push_back(make_pair(make_pair("��", "Q"), seed));
			break;
		case 13:
			card.push_back(make_pair(make_pair("��", "K"), seed));
			break;
		default:
			card.push_back(make_pair(make_pair("��", (to_string)(i)), seed));
			break;
		}
	}
	for (int i = 1; i < 14; i++)
	{
		seed = rand();
		switch (i)
		{
		case 1:
			card.push_back(make_pair(make_pair("��", "A"), seed));
			break;
		case 11:
			card.push_back(make_pair(make_pair("��", "J"), seed));
			break;
		case 12:
			card.push_back(make_pair(make_pair("��", "Q"), seed));
			break;
		case 13:
			card.push_back(make_pair(make_pair("��", "K"), seed));
			break;
		default:
			card.push_back(make_pair(make_pair("��", (to_string)(i)), seed));
			break;
		}
	}
	for (int i = 1; i < 14; i++)
	{
		seed = rand();
		switch (i)
		{
		case 1:
			card.push_back(make_pair(make_pair("��", "A"), seed));
			break;
		case 11:
			card.push_back(make_pair(make_pair("��", "J"), seed));
			break;
		case 12:
			card.push_back(make_pair(make_pair("��", "Q"), seed));
			break;
		case 13:
			card.push_back(make_pair(make_pair("��", "K"), seed));
			break;
		default:
			card.push_back(make_pair(make_pair("��", (to_string)(i)), seed));
			break;
		}
	}

	sort(card.begin(), card.end(), comp); // seed���� �������� �������ش�.
}

void BlackJack::Hit(bool dealer, bool * ace) //ī�带 �����´�. bool dealer�� true�̸� dealer�� ī�嵦��, false�̸� player�� ī�嵦�� ī�带 �ִ´�.
{
	int num = 0; 
	//bool * ace ::  ���迡�� Aī��� 1 Ȥ�� 11�� ���ο��� �����ϰ� ����� �� �ֱ⶧���� Aī�尡 �ִٸ� true�� �ٲ㼭 ���.
	if (card.empty())
	{
		cout << "ī�嵦�� �� �������� ������ ������ �����մϴ�." << endl;
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
		else if (card.back().first.second == "J" || card.back().first.second == "Q" || card.back().first.second == "K") // JQK�� 10���� ���.
		{
			num = 10;
		}
		else
			num = (stoi)(card.back().first.second);
		card.pop_back();
		sum[0] += num;
		if (sum[0]>21 && *ace) // ����Ʈ(21�� �Ѿ�)���� Aī�尡 �ֱ� ������ �ջ꿡�� 10�� ����, bool���� false�� �����ش�.
		{
			*ace = false;
			sum[0] -= 10;
		}
		PrintCard(dealer); // ī�� �μ�
	}
	else //���� ���� Hit�Լ��� ����ϳ�, �׷������� ��ҿ� ī�尪 �ջ궧���� if������ ����
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

void BlackJack::PrintCard(bool dealer) // �׷������� ��� ���
{
	unsigned int i = 0;
	system("cls");
	cout << "====================================================" << endl;
	cout << " �÷��̾��� ī��\t�÷��̾��� ī�� �� : " << sum[0] << "\t\t\t�÷��̾��� ���� �ݾ� : " << Player.GetMoney() << endl;
	for (i = 0; i < playercard.size(); i++)
	{
		cout << "����������" << " ";
	}
	cout << endl;
	for (i = 0; i < playercard.size(); i++)
	{
		cout << "�� " << playercard[i].first << "��" << " ";
	}
	cout << endl;
	for (i = 0; i < playercard.size(); i++)
	{
		if (playercard[i].second == "10")
		{
			cout << "�� " << playercard[i].second << "��" << " ";
		}
		else
			cout << "��  " << playercard[i].second << "��" << " ";
	}
	if (playercard.size()==2 && sum[0]==21)
		cout << "BLACK JACK ! ! !";
	cout << endl;
	
	for (i = 0; i < playercard.size(); i++)
	{
		cout << "����������" << " ";
	}
	cout << endl;

	if (dealer)
	{

		for (i = 0; i < dealercard.size(); i++)
		{
			cout << "����������" << " ";
		}
		cout << endl;
		for (i = 0; i < dealercard.size(); i++)
		{
			cout << "�� " << dealercard[i].first << "��" << " ";
		}
		cout << endl;
		for (i = 0; i < dealercard.size(); i++)
		{
			if (dealercard[i].second == "10")
			{
				cout << "�� " << dealercard[i].second << "��" << " ";
			}
			else
				cout << "��  " << dealercard[i].second << "��" << " ";
		}
		if (dealercard.size()==2 && sum[1]==21)
			cout << "BLACK JACK ! ! !";
		cout << endl;
		for (i = 0; i < dealercard.size(); i++)
		{
			cout << "����������" << " ";
		}
		cout << endl;
		cout << " ������ ī��\t\t������ ī�� �� : " << sum[1] << "\t\t\t������ ���� �ݾ� : " << Casino.GetMoney() << endl;
	}

	cout << "====================================================" << endl;
}

int BlackJack::Betting() //�ǵ� �Է�.
{
	int bet = -1;
	while (1)
	{
		cout << "====================================================" << endl;
		cout << "�̹� ���忡 �� �ǵ��� �Է����ּ���.\t\t�� ���� �ݾ� : " << Player.GetMoney() << "\t" << "ī������ ���� �ݾ� : " << Casino.GetMoney() << endl;
		cin >> bet;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (bet <= 0)
		{
			cout << "��ȿ�� ���ڰ� �ƴմϴ�." << endl;
			continue;
		}
		else if (bet > Player.GetMoney() || bet > Casino.GetMoney()) //�Է��� �ǵ����� ��� �� ����� ���� ���ٸ�
		{
			if (Player.GetMoney() < Casino.GetMoney()) // �÷��̾��� ���� ������ ���� ���θ� ����
			{
				cout << "�Է��Ͻ� �ݾ׺��� �����Ͻ� �ݾ��� �����ϴ�. �����Ͻðڽ��ϱ�?\t";
				if (YorN())
				{
					return Player.GetMoney();
				}
				else
					continue;
			}
			else // ī���� ���� ���� ������ ī���밡 ������ ������ �Է�
			{
				cout << "�Է��Ͻ� �ݾ׺��� ī�������� ������ �ݾ��� �����ϴ�. �ִ�ݾ����� �Է��մϴ�." << endl;
				system("pause");
				return Casino.GetMoney();
			}
		}
		cout << bet << "���� �����մϴ�." << endl;
		system("pause");
		return bet;
	}
}

void BlackJack::PlayerTurn()
{
	if (card.empty())
		return;
	bool ace = false;
	Hit(false,&ace); //Player�� ���̸� false�� �������.
	if (card.empty())
		return;
	Hit(false,&ace);
	if (card.empty())
		return;
	if (sum[0] == 21) // �⺻ 2���� 21�� �޼��� �����̹Ƿ� ���̻� ī�带 ���� �ʴ´�.
		return;
	else
	{
		int select = -1;
		while (1)
		{
			cout << "���� ���� ī���� �� : " << sum[0] << endl;
			cout << "ī�带 �� ���ðڽ��ϱ�?\t";

			if (YorN())
				Hit(false,&ace);
			else
				break;
			if (sum[0] >= 21) //21�̰ų� 21�� ������ �� �̻� ī�带 ������ �ʿ䰡 ����.
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
	Hit(true,&ace); //Dealer�� ���̸� true���� �������.
	if (card.empty())
		return;
	Hit(true,&ace);
	if (card.empty())
		return;
	if (playercard.size()==2 && sum[0] == 21) //�÷��̾��� ī�尡 2���̸鼭 ���� 21�� ���� ������ ���ۿ� ���⶧���� ������ ī�带 �� ���� �ʴ´�.
		return;

	while (sum[1] < 17) // ������ ������ ī�尡 ���� 17 �̸��̸� ī�带 �߰��Ѵ�.
	{
		Hit(true,&ace);
	}
}

bool BlackJack::YorN() // Yes or No�� ���� �� �ݺ��ϴ� ���� �ϳ��� �������.
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
			cout << "��ȿ�� ������ �ƴմϴ�." << endl;
			break;
		}
	}
}

void BlackJack::Round(int bet) // Round ����
{
	PlayerTurn(); // �÷��̾ ���� ������ ����

	if (sum[0] > 21) //ī���� ���� 21�� ������ ����Ʈ�̱⶧���� �ٷ� ���带 �����Ѵ�.
	{
		cout << "������ ���� 21�� �ʰ��Ͽ����ϴ�. ";
		WhoisWin(bet,false);
		return;
	}
	cout << "������ �����Դϴ�." << endl; // �÷��̾��� ī�� ���� 21�� ���� �ʾҴٸ� ������ ���� �����Ѵ�.
	DealerTurn();

	// ������ BLACK JACK�� �޼��ߴٸ�
	if(sum[0] == 21 && sum[1] == 21)
	{
		cout << "�����Դϴ�. �̹� ������ ���ڴ� �����ϴ�." << endl;
		return;
	}
	else if (sum[0] == 21 && playercard.size() == 2) // �÷��̾ ���� �޼�
	{
		cout << "BLACK JACK!" << endl;
		if (Casino.GetMoney() < (int)(bet * 1.5))
		{
			WhoisWin(Casino.GetMoney(), true);
		}
		WhoisWin((int)(bet * 1.5), true);
		return;
	}
	else if (sum[1] == 21 && dealercard.size() == 2) // ������ ���� �޼�
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
		cout << "�����Դϴ�. �̹� ������ ���ڴ� �����ϴ�." << endl;
	
	return;
}

void BlackJack::WhoisWin(int bet, bool win) //���ڸ� �Ǻ��Ͽ� ����
{
	if (win)
	{
		cout << "����� �¸��Դϴ�." << endl;
		Player.Win(bet);
		Casino.Lose(bet);
	}
	else
	{
		cout << "������ �¸��Դϴ�." << endl;
		Player.Lose(bet);
		Casino.Win(bet);
	}
}