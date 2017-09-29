/*================================================================
*   Copyright (C) 2017 GDUT. All rights reserved.
*   
*   文件名称：TicTacToe.cpp
*   创 建 者：zhaohuizhen
*   创建日期：2017年09月28日
*   描    述：
*
================================================================*/


#include "TicTacToe.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

CountFuncMap g_map[] = {
	1, &Count1, 
	0.1,  &Count0_1, 
	0, 0
};

double Chess::GameBoard[9] = {0.0};
int Chess::GamePieces[6] = {0};
double Chess::Gameweight[6];
double Chess::Gameboardweight[9];
pExperiences Chess::GamepHead = 0;

//
Chess::Chess(double n, string name)
{
	player = name;
	value = n;
	srand((int)time(0));
	if(Gameweight[0] == 0)
	{
		for(int i = 0; i < 6; ++i)
		{
			weight[i] = rand()%10 / 10.0 + 0.1;
			Pieces[i] = 0;
		}
		for(int i = 0; i < 9; ++i)
		{
			boardweight[i] = rand()%10 / 10.0 + 0.1;
		}
	}
	else
	{
		for(int i = 0; i < 6; ++i)
		{
			weight[i] = Gameweight[i];
		}
		for(int i = 0; i < 9; ++i)
		{
			boardweight[i] = Gameboardweight[i];
		}
	}


	for(int i = 0; i < 9; ++i)
	{
		Board[i] = 0;
	}

	rate = 0.1;
	error = 0.000001;
	pHead = 0;
}

void Chess::restart() //static 將GameBoard GamePieces 设置为0
{
	for(int i = 0; i < 9; ++i)
	{
		GameBoard[i] = 0;
	}
	for(int i = 0; i < 6; ++i)
	{
		GamePieces[i] = 0;
	}
}

double Chess::score()
{
	double sum = 0.0;
	for(int i = 0; i < 6; ++i)
	{
		sum += Pieces[i] * weight[i];
	}
	for(int i = 0; i < 9; ++i)
	{
		if(Board[i] != 0)
		{
			sum += boardweight[i];
		}
	}
	return sum;
}

void Chess::getBoardStatus()
{
	for(int i = 0; i < 9; ++i)
	{
		Board[i] = GameBoard[i];
	}

/*	for(int i = 0; i < 6; ++i)
	{
		Pieces[i] = GamePieces[i];
	}*/
}

void Chess::setBoardStatus()
{

	for(int i = 0; i < 9; ++i)
	{
		GameBoard[i] = Board[i];
	}

/*	for(int i = 0; i < 6; ++i)
	{
		GamePieces[i] = Pieces[i];
	}*/
}

void Chess::setpieces()//成员函数，计算并设置棋子分布情况
{
	Count1(Board, Pieces);
	Count0_1(Board, Pieces);
}

void Chess::play()//下棋
{
	int locate = -1;
	double max = -100000000;
	double sum = 0.0;
	int i = 0;

	getBoardStatus();//获得棋盘状态

	for(i = 0; i < 9; ++i)
	{
		if(Board[i] == 0)
		{
			Board[i] = value;
			setpieces();
			sum = score(); 

			if(max < sum)
			{
				max = sum;
				locate = i;
			}
			Board[i] = 0;
		}
	}


	if(-1 != locate)
	{
		GameBoard[locate] = value;
	}

	if(0 == pHead)
	{
		pHead = new Experiences;
		pHead->plast = 0;
		pHead->pnext = 0;
		pHead->label = 0.0;

		for(int i = 0; i < 9; ++i)
		{
			pHead->board[i] = GameBoard[i];
		}
	}
	else
	{
		pExperiences pCur = pHead;
		while(pCur->pnext != 0)
		{
			pCur = pCur->pnext;
		}
		pCur->pnext = new Experiences;
		pCur->pnext->plast = pCur;
		pCur = pCur->pnext;
		pCur->pnext = 0;
		pCur->label = 0.0;

		for(int i = 0; i < 9; ++i)
		{
			pCur->board[i] = GameBoard[i];
		}
	}
}

int Chess::status()
{
	Count1(GameBoard, GamePieces);
	Count0_1(GameBoard, GamePieces);

	if(GamePieces[4] == 1)
	{
		return 1;
	}
	else if(GamePieces[5] == 1)
	{
		return -1;
	}
	else
	{
		int i = 0;
		for(i = 0; i < 9; ++i)
		{
			if(GameBoard[i] == 0) break;
		}

		if(i < 9)
		{
			return 0;
		}
		else
		{
			return 2;//tied
		}
	}
}

void Chess::free()
{
	if(pHead != 0)
	{
		pExperiences pCur = pHead;
		do
		{
			pCur = pHead;
			pHead = pHead->pnext;
			delete pCur;
		}while(pHead);
	}
}

void Chess::showweight()
{
	for(int i = 0; i < 6; ++i)
	{
		printf("%-20.6f", weight[i]);
		if(i == 2 || i == 5 || i == 8) printf("\n");
	}

}

void Chess::judge(int stat)
{
	if(1 == stat)
	{
		cout << "player1 win" << endl;
		Chess::showboard();
	}
	else if(-1 == stat)
	{
		cout << "player2 win" << endl;
		Chess::showboard();
	}
	else if(2 == stat)
	{
		
		cout << "tied" << endl;
		Chess::showboard();
	}
}

void Chess::getexperience()
{
	if(pHead != 0 && 0 != pHead->pnext)
	{
		pExperiences pCur = pHead;
		double esco = 0.0;

		while(pCur->pnext != 0) pCur = pCur->pnext;
		do
		{
			for(int i = 0; i < 9; ++i)
			{
				Board[i] = pCur->board[i];
			}
			setpieces();	
			esco = score();
			if(pCur->plast != 0)
			{
				pCur->plast->label = esco;
			}
			pCur = pCur->plast;
		
		}while(pCur);
	}
	showexper();
}

void Chess::upgrade()
{
	int times = 1000;
	double actual;// = 0.0;
	pExperiences pCur;// = pHead;

	for(int i = 0; i < times; ++i)
	{
		for(pCur = pHead; pCur != 0; pCur = pCur->pnext)
		{
			if(pCur->label == 0)
			{
				continue;
			}

			for(int j = 0; j < 9; ++j)
			{
				Board[j] = pCur->board[j];
			}
			setpieces();
			actual = score();
			if(pCur->label - actual < error)
			{
				free();
				return;
			}

			for(int j = 0; j < 6; ++j)
			{
				weight[j] += rate * (pCur->label - actual) * Pieces[j];
			}

			for(int j = 0; j < 9; ++j)
			{
				if(Board[j] != 0)
				{
					boardweight[j] += rate * (pCur->label - actual);
				}
			}
		}
	}
	free();
}

void Count1(double *pBoard, int *pPies)//修改pPies 0 2 4位置的值
{
	for(int i = 0; i < 6; i += 2)
	{
		pPies[i] = 0;
	}

	for(int i = 0; i < 9; ++i)
	{
		if(1 == (pBoard[i]))
		{
			++pPies[0];
		}
	}

	int nCount = 0;

	nCount = (int)SUM3(pBoard[0], pBoard[1], pBoard[2]);
	if(2 == nCount)
	{
		++pPies[2];
	}
	else if(3 == nCount)
	{
		++pPies[4];
	}
	
	nCount = (int)SUM3(pBoard[3], pBoard[4], pBoard[5]);
	if(2 == nCount)
	{
		++pPies[2];
	}
	else if(3 == nCount)
	{
		++pPies[4];
	}

	nCount = (int)SUM3(pBoard[6], pBoard[7], pBoard[8]);
	if(2 == nCount)
	{
		++pPies[2];
	}
	else if(3 == nCount)
	{
		++pPies[4];
	}

	nCount = (int)SUM3(pBoard[0], pBoard[3], pBoard[6]);
	if(2 == nCount)
	{
		++pPies[2];
	}
	else if(3 == nCount)
	{
		++pPies[4];
	}

	nCount = (int)SUM3(pBoard[1], pBoard[4], pBoard[7]);
	if(2 == nCount)
	{
		++pPies[2];
	}
	else if(3 == nCount)
	{
		++pPies[4];
	}

	nCount = (int)SUM3(pBoard[2], pBoard[5], pBoard[8]);
	if(2 == nCount)
	{
		++pPies[2];
	}
	else if(3 == nCount)
	{
		++pPies[4];
	}

	nCount = (int)SUM3(pBoard[0], pBoard[4], pBoard[8]);
	if(2 == nCount)
	{
		++pPies[2];
	}
	else if(3 == nCount)
	{
		++pPies[4];
	}

	nCount = (int)SUM3(pBoard[2], pBoard[4], pBoard[6]);
	if(2 == nCount)
	{
		++pPies[2];
	}
	else if(3 == nCount)
	{
		++pPies[4];
	}
	pPies[0] -= 2 * pPies[2];
	pPies[0] -= 3 * pPies[4];
}


void Count0_1(double *pBoard, int *pPies)//修改pPies 的 1 3 5 位置值
{
	for(int i = 1; i < 6; i += 2)
	{
		pPies[i] = 0;
	}

	for(int i = 0; i < 9; ++i)
	{
		if(0.1 == (pBoard[i]))
		{
			++pPies[1];
		}
	}

	double Count = 0;

	Count = SUM3(pBoard[0], pBoard[1], pBoard[2]);
	Count = ((int)(Count * 10)) % 10;

	if(2 == Count)
	{
		++pPies[3];
	}
	else if(3 == Count)
	{
		++pPies[5];
	}
	
	Count = (int)SUM3(pBoard[3], pBoard[4], pBoard[5]);
	Count = ((int)(Count * 10)) % 10;

	if(2 == Count)
	{
		++pPies[3];
	}
	else if(3 == Count)
	{
		++pPies[5];
	}

	Count = (int)SUM3(pBoard[6], pBoard[7], pBoard[8]);
	Count = ((int)(Count * 10)) % 10;

	if(2 == Count)
	{
		++pPies[3];
	}
	else if(3 == Count)
	{
		++pPies[5];
	}

	Count = (int)SUM3(pBoard[0], pBoard[3], pBoard[6]);
	Count = ((int)(Count * 10)) % 10;

	if(2 == Count)
	{
		++pPies[3];
	}
	else if(3 == Count)
	{
		++pPies[5];
	}

	Count = (int)SUM3(pBoard[1], pBoard[4], pBoard[7]);
	Count = ((int)(Count * 10)) % 10;

	if(2 == Count)
	{
		++pPies[3];
	}
	else if(3 == Count)
	{
		++pPies[5];
	}

	Count = (int)SUM3(pBoard[2], pBoard[5], pBoard[8]);
	Count = ((int)(Count * 10)) % 10;

	if(2 == Count)
	{
		++pPies[3];
	}
	else if(3 == Count)
	{
		++pPies[5];
	}

	Count = (int)SUM3(pBoard[0], pBoard[4], pBoard[8]);
	Count = ((int)(Count * 10)) % 10;

	if(2 == Count)
	{
		++pPies[3];
	}
	else if(3 == Count)
	{
		++pPies[5];
	}

	Count = (int)SUM3(pBoard[2], pBoard[4], pBoard[6]);
	Count = ((int)(Count * 10)) % 10;

	if(2 == Count)
	{
		++pPies[3];
	}
	else if(3 == Count)
	{
		++pPies[5];
	}

	pPies[1] -= 2 * pPies[3];
	pPies[1] -= 3 * pPies[5];
}

void Chess::showboard()
{
	for(int i = 0; i < 9; ++i)
	{
		printf("%-10.2f", GameBoard[i]);
		if(i == 2 || i == 5 || i == 8) printf("\n");
	}
}

void Chess::showexper()
{
	pExperiences pCur = pHead;
	while(pCur != 0)
	{
		cout << pCur->label << "     ";
		pCur = pCur->pnext;
	}
	cout << endl;
}
