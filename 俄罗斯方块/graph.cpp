#include"graph.h"

// =============================================================================
// ������ɫ
void Graph::setPoolColor(const TetrisManager* manager, TetrisControl* control)
{
	// ������ʾ��Ϸ��ʱ����Ҫ����Ϸ�����ж�ĳһ�����з������ʾ��Ӧ�������ɫ
	// ����ֻ�����ü��ɣ�û��Ҫ���
	// ���ƶ�������һ������ʱ����

	int8_t i, x, y;

	// ��ǰ����
	uint16_t tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];

	for (i = 0; i < 16; ++i)
	{
		y = (i >> 2) + manager->y; // �����õ���
		if (y > ROW_END) // �����ײ�����
		{
			break;
		}
		x = (i & 3) + manager->x; // �����õ���
		if ((tetris >> i) & 1) // ���ĵ�С�������ڵ�ǰ��������
		{
			control->color[y][x] = (manager->type[0] | 8); // ������ɫ
		}
	}
}



// =============================================================================
// ��ʾ��Ϸ�ر߽�
void Graph::printPoolBorder()
{
	Logic logic_g;
	int8_t y;

	SetConsoleTextAttribute(g_hConsoleOutput, 0xF0);
	for (y = ROW_BEGIN; y < ROW_END; ++y) // ����ʾ����4�к͵ײ�2��
	{
		logic_g.gotoxyWithFullwidth(10, y - 3);
		printf("%2s", "");
		logic_g.gotoxyWithFullwidth(23, y - 3);
		printf("%2s", "");
	}

	logic_g.gotoxyWithFullwidth(10, y - 3); // �ײ��߽�
	printf("%28s", "");
}

// ��λ����Ϸ���еķ���
#define gotoxyInPool(x, y) gotoxyWithFullwidth(x + 9, y - 3)

// =============================================================================
// ��ʾ��Ϸ��
void Graph::printTetrisPool(const TetrisManager* manager, const TetrisControl* control)
{
	Logic logic_g;
	int8_t x, y;

	for (y = ROW_BEGIN; y < ROW_END; ++y) // ����ʾ����4�к͵ײ�2��
	{
		logic_g.gotoxyInPool(2, y); // ���㵽��Ϸ���еķ���
		for (x = COL_BEGIN; x < COL_END; ++x) // ����ʾ���ұ߽�
		{
			if ((manager->pool[y] >> x) & 1) // ��Ϸ�ظ÷����з���
			{
				// ����Ӧ��ɫ����ʾһ��ʵ�ķ���
				SetConsoleTextAttribute(g_hConsoleOutput, control->color[y][x]);
				printf("��");
			}
			else // û�з��飬��ʾ�հ�
			{
				SetConsoleTextAttribute(g_hConsoleOutput, 0);
				printf("%2s", "");
			}
		}
	}
}

// =============================================================================
// ��ʾ��ǰ����
void Graph::printCurrentTetris(const TetrisManager* manager, const TetrisControl* control)
{
	Logic logic_g;
	int8_t x, y;

	// ��ʾ��ǰ���������ƶ�����õģ�Ϊ��ȥ�ƶ�ǰ�ķ��飬��Ҫ��չ��ʾ����
	// ���ڲ����������ƶ����ʲ���Ҫ������չ
	y = (manager->y > ROW_BEGIN) ? (manager->y - 1) : ROW_BEGIN; // ������չһ��
	for (; y < ROW_END && y < manager->y + 4; ++y)
	{
		x = (manager->x > COL_BEGIN) ? (manager->x - 1) : COL_BEGIN; // ������չһ��
		for (; x < COL_END && x < manager->x + 5; ++x) // ������չһ��
		{
			logic_g.gotoxyInPool(x, y); // ���㵽��Ϸ���еķ���
			if ((manager->pool[y] >> x) & 1) // ��Ϸ�ظ÷����з���
			{
				// ����Ӧ��ɫ����ʾһ��ʵ�ķ���
				SetConsoleTextAttribute(g_hConsoleOutput, control->color[y][x]);
				printf("��");
			}
			else // û�з��飬��ʾ�հ�
			{
				SetConsoleTextAttribute(g_hConsoleOutput, 0);
				printf("%2s", "");
			}
		}
	}
}

// =============================================================================
// ��ʾ��һ��������һ������
void Graph::printNextTetris(const TetrisManager* manager)
{
	Logic logic_g;
	int8_t i;
	uint16_t tetris;

	// �߿�
	SetConsoleTextAttribute(g_hConsoleOutput, 0xF);
	logic_g.gotoxyWithFullwidth(26, 1);
	printf("�����������ש���������");
	logic_g.gotoxyWithFullwidth(26, 2);
	printf("��%8s��%8s��", "", "");
	logic_g.gotoxyWithFullwidth(26, 3);
	printf("��%8s��%8s��", "", "");
	logic_g.gotoxyWithFullwidth(26, 4);
	printf("��%8s��%8s��", "", "");
	logic_g.gotoxyWithFullwidth(26, 5);
	printf("��%8s��%8s��", "", "");
	logic_g.gotoxyWithFullwidth(26, 6);
	printf("�����������ߩ���������");

	// ��һ��������Ӧ��ɫ��ʾ
	tetris = gs_uTetrisTable[manager->type[1]][manager->orientation[1]];
	SetConsoleTextAttribute(g_hConsoleOutput, manager->type[1] | 8);
	for (i = 0; i < 16; ++i)
	{
		logic_g.gotoxyWithFullwidth((i & 3) + 27, (i >> 2) + 2);
		((tetris >> i) & 1) ? printf("��") : printf("%2s", "");
	}

	// ����һ��������ʾ��ɫ
	tetris = gs_uTetrisTable[manager->type[2]][manager->orientation[2]];
	SetConsoleTextAttribute(g_hConsoleOutput, 8);
	for (i = 0; i < 16; ++i)
	{
		logic_g.gotoxyWithFullwidth((i & 3) + 32, (i >> 2) + 2);
		((tetris >> i) & 1) ? printf("��") : printf("%2s", "");
	}
}

// =============================================================================
// ��ʾ�÷���Ϣ
void Graph::printScore(const TetrisManager* manager)
{
	Logic logic_g;
	static const char* tetrisName = "ITLJZSO";
	int8_t i;

	SetConsoleTextAttribute(g_hConsoleOutput, 0xE);

	logic_g.gotoxyWithFullwidth(2, 2);
	printf("���÷֣�%u", manager->score);

	logic_g.gotoxyWithFullwidth(1, 6);
	printf("������������%u", manager->erasedTotal);
	for (i = 0; i < 4; ++i)
	{
		logic_g.gotoxyWithFullwidth(2, 8 + i);
		printf("����%d��%u", i + 1, manager->erasedCount[i]);
	}

	logic_g.gotoxyWithFullwidth(1, 15);
	printf("������������%u", manager->tetrisTotal);

	for (i = 0; i < 7; ++i)
	{
		logic_g.gotoxyWithFullwidth(2, 17 + i);
		printf("��%c�Σ�%u", tetrisName[i], manager->tetrisCount[i]);
	}
}

// =============================================================================
// ��ʾ��ʾ��Ϣ
void Graph::printPrompting()
{
	Logic logic_g;
	SetConsoleTextAttribute(g_hConsoleOutput, 0xB);
	logic_g.gotoxyWithFullwidth(26, 10);
	printf("�����ƣ�");
	logic_g.gotoxyWithFullwidth(27, 12);
	printf("�������ƶ����� A 4");
	logic_g.gotoxyWithFullwidth(27, 13);
	printf("�������ƶ����� D 6");
	logic_g.gotoxyWithFullwidth(27, 14);
	printf("�������ƶ����� S 2");
	logic_g.gotoxyWithFullwidth(27, 15);
	printf("��˳ʱ��ת���� W 8");
	logic_g.gotoxyWithFullwidth(27, 16);
	printf("����ʱ��ת��0");
	logic_g.gotoxyWithFullwidth(27, 17);
	printf("��ֱ����أ��ո�");
	logic_g.gotoxyWithFullwidth(27, 18);
	printf("����ͣ��Ϸ���س�");
	logic_g.gotoxyWithFullwidth(25, 23);
}

