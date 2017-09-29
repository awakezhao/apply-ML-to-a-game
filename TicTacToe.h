/*================================================================
*   Copyright (C) 2017 GDUT. All rights reserved.
*   
*   文件名称：TicTacToe.h
*   创 建 者：zhaohuizhen
*   创建日期：2017年09月28日
*   描    述：
*
================================================================*/


#pragma once
#include "origin.h"
#include <string>
using namespace std;

#define SUM3(x1, x2, x3) ((x1) + (x2) + (x3))

typedef void (*PFUNC)(double *, int *);

typedef struct CountFuncMap
{
	double value;
	PFUNC pfn;
}CountFuncMap;

typedef struct Experiences
{
	double board[9];
	double label;

	Experiences *plast;
	Experiences *pnext;
}Experiences, *pExperiences;

class Chess
{
	public:
		class Bad_chess{};
		Chess(double n = 0, string name = "zhaohuizhen");

		static void restart();
		void play();
		static int status();
		void getexperience();
		void upgrade();
		void showweight();
		void showexper();

		static void showboard();
		static void judge(int stat);

	private:
		int Pieces[6];
		double weight[6];
		string player;
		double Board[9];
		double value;		//棋手的棋子代表值
		double rate;
		double error;
		double boardweight[9];
		pExperiences pHead;


		double score();
		void getBoardStatus();
		void setBoardStatus();
		void free();
		void setpieces();

		static double GameBoard[9];//棋盘状态
		static int GamePieces[6];

		static double Gameweight[6];
		static double Gameboardweight[9];

		static pExperiences GamepHead;
};

void Count1(double *pBoard, int *pPies);
void Count0_1(double *pBoard, int *pPies);
