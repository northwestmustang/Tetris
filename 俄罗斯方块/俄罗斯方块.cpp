#include"main.h"
#include"Logic.h"
#include"graph.h"
#include"GameControl.h"
using namespace std;
// 控制台输出句柄
HANDLE g_hConsoleOutput;
// =============================================================================
// 主函数
int main()
{
	TetrisManager tetrisManager;
	TetrisControl tetrisControl;
	GameControl gamecontrol;
	Logic logic;
	Graph graph;
	gamecontrol.initGame(&tetrisManager, &tetrisControl); // 初始化游戏
	do
	{
		graph.printPrompting(); // 显示提示信息
		graph.printPoolBorder(); // 显示游戏池边界
		gamecontrol.runGame(&tetrisManager, &tetrisControl); // 运行游戏
		if (gamecontrol.ifPlayAgain()) // 再来一次
		{
			SetConsoleTextAttribute(g_hConsoleOutput, 0x7);
			system("cls"); // 清屏
			gamecontrol.restartGame(&tetrisManager, &tetrisControl); // 重新开始游戏
		}
		else
		{
			break;
		}
	} while (1);
	logic.gotoxyWithFullwidth(0, 0);
	CloseHandle(g_hConsoleOutput);
	return 0;
}


