#include "Logic.h"
void Logic::giveTetris(TetrisManager* manager)
{
	Graph graph_L;
	uint16_t tetris;

	manager->type[0] = manager->type[1]; // ��һ��������Ϊ��ǰ
	manager->orientation[0] = manager->orientation[1];

	manager->type[1] = manager->type[2];// ����һ���÷���Ϊ��һ��
	manager->orientation[1] = manager->orientation[2];

	manager->type[2] = rand() % 7;// �����������һ������
	manager->orientation[2] = rand() & 3;

	tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]]; // ��ǰ����

	// ���õ�ǰ����y���꣬��֤�ո���ʱֻ��ʾ����������һ��
	// ����ʵ��ʹ����ҿ����Ժܿ���ٶȽ��������ڲ���ʾ�����Ķ���4����
	if (tetris & 0xF000)
	{
		manager->y = 0;
	}
	else
	{
		manager->y = (tetris & 0xFF00) ? 1 : 2;
	}
	manager->x = 6; // ���õ�ǰ����x����

	if (checkCollision(manager)) // ��⵽��ײ
	{
		manager->dead = true; // �����Ϸ����
	}
	else // δ��⵽��ײ
	{
		insertTetris(manager); // ����ǰ���������Ϸ��
	}

	++manager->tetrisTotal; // ��������
	++manager->tetrisCount[manager->type[0]]; // ��Ӧ������

	graph_L.printNextTetris(manager); // ��ʾ��һ������
	graph_L.printScore(manager); // ��ʾ�÷���Ϣ
}

// =============================================================================
// ��ײ���
bool Logic::checkCollision(const TetrisManager* manager)
{
	// ��ǰ����
	uint16_t tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];
	uint16_t dest = 0;

	// ��ȡ��ǰ��������Ϸ���е�����
	// ��Ϸ������x y��С������Ϣ�����͵��ߴ����16λ�޷�������
	dest |= (((manager->pool[manager->y + 0] >> manager->x) << 0x0) & 0x000F);
	dest |= (((manager->pool[manager->y + 1] >> manager->x) << 0x4) & 0x00F0);
	dest |= (((manager->pool[manager->y + 2] >> manager->x) << 0x8) & 0x0F00);
	dest |= (((manager->pool[manager->y + 3] >> manager->x) << 0xC) & 0xF000);

	// ����ǰ������Ŀ����������ص�����ײ������λ��Ľ����Ϊ0
	return ((dest & tetris) != 0);
}

// =============================================================================
// ���뷽��
void Logic::insertTetris(TetrisManager* manager)
{
	// ��ǰ����
	uint16_t tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];

	// ��ǰ����ÿ4λȡ����λ����Ϸ����Ӧλ�ã�����ɲ��뷽��
	manager->pool[manager->y + 0] |= (((tetris >> 0x0) & 0x000F) << manager->x);
	manager->pool[manager->y + 1] |= (((tetris >> 0x4) & 0x000F) << manager->x);
	manager->pool[manager->y + 2] |= (((tetris >> 0x8) & 0x000F) << manager->x);
	manager->pool[manager->y + 3] |= (((tetris >> 0xC) & 0x000F) << manager->x);
}

// =============================================================================
// �Ƴ�����
void Logic::removeTetris(TetrisManager* manager)
{
	// ��ǰ����
	uint16_t tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];

	// ��ǰ����ÿ4λȡ������λȡ����λ�뵽��Ϸ����Ӧλ�ã�������Ƴ�����
	manager->pool[manager->y + 0] &= ~(((tetris >> 0x0) & 0x000F) << manager->x);
	manager->pool[manager->y + 1] &= ~(((tetris >> 0x4) & 0x000F) << manager->x);
	manager->pool[manager->y + 2] &= ~(((tetris >> 0x8) & 0x000F) << manager->x);
	manager->pool[manager->y + 3] &= ~(((tetris >> 0xC) & 0x000F) << manager->x);
}
bool Logic::checkErasing(TetrisManager* manager, TetrisControl* control)
{
	Graph graph_L;
	static const unsigned scores[5] = { 0, 10, 30, 90, 150 }; // ���е÷�
	int8_t count = 0;
	int8_t k = 0, y = manager->y + 3; // �������ϼ��

	do
	{
		if (y < ROW_END && manager->pool[y] == 0xFFFFU) // ��Ч��������һ��������
		{
			++count;
			// ����һ�з���
			memmove(manager->pool + 1, manager->pool, sizeof(uint16_t) * y);
			// ��ɫ�����Ԫ����֮�ƶ�
			memmove(control->color[1], control->color[0], sizeof(int8_t[16]) * y);
		}
		else
		{
			--y;
			++k;
		}
	} while (y >= manager->y && k < 4);

	manager->erasedTotal += count; // ��������
	manager->score += scores[count]; // �÷�

	if (count > 0)
	{
		++manager->erasedCount[count - 1]; // ����
	}

	giveTetris(manager); // ����һ������
	graph_L.setPoolColor(manager, control); // ������ɫ

	return (count > 0);
}
void Logic::gotoxyWithFullwidth(short x, short y)
{
	static COORD cd;

	cd.X = (short)(x << 1);
	cd.Y = y;
	SetConsoleCursorPosition(g_hConsoleOutput, cd);
}
