#include "GameControl.h"
void GameControl::initGame(TetrisManager* manager, TetrisControl* control)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE }; // �����Ϣ

	g_hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ����̨������
	SetConsoleCursorInfo(g_hConsoleOutput, &cursorInfo); // ���ù������

	restartGame(manager, control);
}

// =============================================================================
// ���¿�ʼ��Ϸ
void GameControl::restartGame(TetrisManager* manager, TetrisControl* control)
{
	memset(manager, 0, sizeof(TetrisManager)); // ȫ����0

	// ��ʼ����Ϸ��
	memcpy(manager->pool, gs_uInitialTetrisPool, sizeof(uint16_t[28]));
	srand((unsigned)time(NULL)); // �����������

	manager->type[1] = rand() % 7; // ��һ��
	manager->orientation[1] = rand() & 3;

	manager->type[2] = rand() % 7; // ����һ��
	manager->orientation[2] = rand() & 3;

	memset(control, 0, sizeof(TetrisControl)); // ȫ����0

	logic_G.giveTetris(manager); // ����һ������
	graph_G.setPoolColor(manager, control); // ������ɫ
}
void GameControl::horzMoveTetris(TetrisManager* manager, TetrisControl* control)
{
	int x = manager->x; // ��¼ԭ��λ��

	logic_G.removeTetris(manager); // ���ߵ�ǰ����
	control->direction == 0 ? (--manager->x) : (++manager->x); // ��/���ƶ�

	if (logic_G.checkCollision(manager)) // ��⵽��ײ
	{
		manager->x = x; // �ָ�Ϊԭ��λ��
		logic_G.insertTetris(manager); // ���뵱ǰ���顣����λ��û�ı䣬����Ҫ������ɫ
	}
	else
	{
		logic_G.insertTetris(manager); // ���뵱ǰ����
		graph_G.setPoolColor(manager, control); // ������ɫ
		graph_G.printCurrentTetris(manager, control); // ��ʾ��ǰ����
	}
}

// =============================================================================
// �����ƶ�����
void GameControl::moveDownTetris(TetrisManager* manager, TetrisControl* control)
{
	int8_t y = manager->y; // ��¼ԭ��λ��

	logic_G.removeTetris(manager); // ���ߵ�ǰ����
	++manager->y; // �����ƶ�

	if (logic_G.checkCollision(manager)) // ��⵽��ײ
	{
		manager->y = y; // �ָ�Ϊԭ��λ��
		logic_G.insertTetris(manager); // ���뵱ǰ���顣����λ��û�ı䣬����Ҫ������ɫ
		if (logic_G.checkErasing(manager, control)) // ��⵽����
		{
			graph_G.printTetrisPool(manager, control); // ��ʾ��Ϸ��
		}
	}
	else
	{
		logic_G.insertTetris(manager); // ���뵱ǰ����
		graph_G.setPoolColor(manager, control); // ������ɫ
		graph_G.printCurrentTetris(manager, control); // ��ʾ��ǰ����
	}
}
void GameControl::rotateTetris(TetrisManager* manager, TetrisControl* control)
{
	int8_t ori = manager->orientation[0]; // ��¼ԭ��ת״̬

	logic_G.removeTetris(manager); // ���ߵ�ǰ����

	// ˳/��ʱ����ת
	manager->orientation[0] = (control->clockwise) ? ((ori + 1) & 3) : ((ori + 3) & 3);

	if (logic_G.checkCollision(manager)) // ��⵽��ײ
	{
		manager->orientation[0] = ori; // �ָ�Ϊԭ��ת״̬
		logic_G.insertTetris(manager); // ���뵱ǰ���顣����״̬û�ı䣬����Ҫ������ɫ
	}
	else
	{
		logic_G.insertTetris(manager); // ���뵱ǰ����
		graph_G.setPoolColor(manager, control); // ������ɫ
		graph_G.printCurrentTetris(manager, control); // ��ʾ��ǰ����
	}
}
// =============================================================================
// ����ֱ�����
void GameControl::dropDownTetris(TetrisManager* manager, TetrisControl* control)
{
	logic_G.removeTetris(manager); // ���ߵ�ǰ����
	for (; manager->y < ROW_END; ++manager->y) // ��������
	{
		if (logic_G.checkCollision(manager)) // ��⵽��ײ
		{
			break;
		}
	}
	--manager->y; // ����һ��Ȼû����ײ

	logic_G.insertTetris(manager); // ���뵱ǰ����
	graph_G.setPoolColor(manager, control); // ������ɫ

	logic_G.checkErasing(manager, control); // �������
	graph_G.printTetrisPool(manager, control); // ��ʾ��Ϸ��
}
void GameControl::keydownControl(TetrisManager* manager, TetrisControl* control, int key)
{
	if (key == 13) // ��ͣ/�����ͣ
	{
		control->pause = !control->pause;
	}

	if (control->pause) // ��ͣ״̬����������
	{
		return;
	}

	switch (key)
	{
	case 'w': case 'W': case '8': case 72: // ��
		control->clockwise = true; // ˳ʱ����ת
		rotateTetris(manager, control); // ��ת����
		break;
	case 'a': case 'A': case '4': case 75: // ��
		control->direction = 0; // �����ƶ�
		horzMoveTetris(manager, control); // ˮƽ�ƶ�����
		break;
	case 'd': case 'D': case '6': case 77: // ��
		control->direction = 1; // �����ƶ�
		horzMoveTetris(manager, control); // ˮƽ�ƶ�����
		break;
	case 's': case 'S': case '2': case 80: // ��
		moveDownTetris(manager, control); // �����ƶ�����
		break;
	case ' ': // ֱ�����
		dropDownTetris(manager, control);
		break;
	case '0': // ��ת
		control->clockwise = false; // ��ʱ����ת
		rotateTetris(manager, control); // ��ת����
		break;
	default:
		break;
	}
}
void GameControl::runGame(TetrisManager* manager, TetrisControl* control)
{
	clock_t clockLast, clockNow;

	clockLast = clock(); // ��ʱ
	graph_G.printTetrisPool(manager, control); // ��ʾ��Ϸ��

	while (!manager->dead) // û��
	{
		while (_kbhit()) // �м�����
		{
			keydownControl(manager, control, _getch()); // ������
		}

		if (!control->pause) // δ��ͣ
		{
			clockNow = clock(); // ��ʱ
			// ���μ�ʱ�ļ������0.45��
			if (clockNow - clockLast > 0.45F * CLOCKS_PER_SEC)
			{
				clockLast = clockNow;
				keydownControl(manager, control, 80); // ����������
			}
		}
	}
}

// =============================================================================
// ����һ��
bool GameControl::ifPlayAgain()
{
	int ch;

	SetConsoleTextAttribute(g_hConsoleOutput, 0xF0);
	logic_G.gotoxyWithFullwidth(15, 10);
	printf("��Ϸ����");
	logic_G.gotoxyWithFullwidth(13, 11);
	printf("��Y���棬��N�˳�");

	do
	{
		ch = _getch();
		if (ch == 'Y' || ch == 'y')
		{
			return true;
		}
		else if (ch == 'N' || ch == 'n')
		{
			return false;
		}
	} while (1);
}