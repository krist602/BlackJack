BLACK JACK ! !

1. 작성자 : 박종빈
2. 실행 방법 : exe파일 실행 혹은 sln파일 실행 후 시작.
3. 추가사항
	- system("cls")를 이용. 최대한 사용안하려고 했지만, 카드를 인쇄하려면 모든 것을 지운 상태에서 인쇄하는 것이 가장 깔끔했음
	- card덱은 vector<>를 이용했음
	- card덱은 time과 rand를 이용해 무작위로 섞어준다.
	- 기본적으론 플레이어의 돈 혹은 카지노의 돈이 떨어지면 게임이 끝난다.
	- 카드 덱이 다 떨어지면 게임이 끝나도록 설정해놨다.
	- 후에 간단한 게임을 더 추가하고 싶다면 추가할 수 있도록 BlackJack.h와 BlackJack.cpp를 따로 구성해놨다.
	- cin은 잘못된 포맷을 입력하면 오류가 나는 현상이 있기 때문에 오류가 나면 버퍼를 비우도록 다시 설정.
4. 가이드
	- 간단한 게임이기에 치트키는 없다.
