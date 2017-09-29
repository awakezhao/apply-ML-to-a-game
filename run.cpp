/*************************************************************************
    > File Name: run.cpp
    > Author: zhaohuizhen
    > Mail: 1534612574@qq.com 
    > Created Time: 2017年09月24日 星期日 13时39分44秒
 ************************************************************************/

#include "run.h"
#include "TicTacToe.h"
#include <iostream>
#include <stdio.h>
using namespace std;

int run()
{
	//INFO(run);
	Chess player1(1, "alpha"), player2(0.1, "beta");
	int result = -2;
	while(true)
	{
	//	cout << "begin!" << endl;
		getchar();

		Chess::restart();
		
		while(true)
		{

			player1.play();//下棋 记录棋盘
			result = Chess::status();
			if(0 != result)
			{
				Chess::judge(result);
				player1.showweight();
				player1.showexper();
				player2.showweight();
				player2.showexper();
				break;
			}

			player2.play();
			result = Chess::status();
			if(0 != result)
			{
				Chess::judge(result);
				player1.showweight();
				player1.showexper();
				player2.showweight();
				player2.showexper();
				break;
			}
		}
		player1.getexperience();
		player2.getexperience();

		player1.upgrade();
		player2.upgrade();
		player1.showweight();
		player2.showweight();

	}
    return 0;
}
