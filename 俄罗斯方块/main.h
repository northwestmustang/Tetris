#pragma once

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>


#define COL_BEGIN 2
#define COL_END 14
#define ROW_BEGIN 4
#define ROW_END 26

// ����̨������
extern HANDLE g_hConsoleOutput;
// =============================================================================
// 7�ַ����4��ת״̬��4λΪһ�У�
static const uint16_t gs_uTetrisTable[7][4] =
{
	{ 0x00F0U, 0x2222U, 0x00F0U, 0x2222U }, // I��
	{ 0x0072U, 0x0262U, 0x0270U, 0x0232U }, // T��
	{ 0x0223U, 0x0074U, 0x0622U, 0x0170U }, // L��
	{ 0x0226U, 0x0470U, 0x0322U, 0x0071U }, // J��
	{ 0x0063U, 0x0264U, 0x0063U, 0x0264U }, // Z��
	{ 0x006CU, 0x0462U, 0x006CU, 0x0462U }, // S��
	{ 0x0660U, 0x0660U, 0x0660U, 0x0660U }  // O��
};
// =============================================================================
// ��ʼ״̬����Ϸ��
// ÿ��Ԫ�ر�ʾ��Ϸ�ص�һ�У��±�������Ϸ�صײ�
// ���˸���2��1���ײ�2ȫ��Ϊ1�����ڽ�����ײ���
// ����һ����Ϸ�صĿ��Ϊ12��
// �����Ҫ��ͳ��10�У�ֻ���������1���ɣ�0xE007������Ȼ��ʾ��ز���ҲҪ��֮�Ķ�
// ��ĳ��Ԫ��Ϊ0xFFFFUʱ��˵�������ѱ�����
// ����4�����ڸ����飬����ʾ����
// �ٳ�ȥ�ײ�2�У���ʾ��������Ϸ�ظ߶�Ϊ22��
static const uint16_t gs_uInitialTetrisPool[28] =
{
	0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U,
	0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U,
	0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U,
	0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xFFFFU, 0xFFFFU
};
// =============================================================================
typedef struct TetrisManager // ����ṹ��洢��Ϸ�������
{
	uint16_t pool[28]; // ��Ϸ��
	int8_t x; // ��ǰ����x���꣬�˴�����Ϊ�������Ͻ�����
	int8_t y; // ��ǰ����y����
	int8_t type[3]; // ��ǰ����һ��������һ����������
	int8_t orientation[3]; // ��ǰ����һ��������һ��������ת״̬
	unsigned score; // �÷�
	unsigned erasedCount[4]; // ������
	unsigned erasedTotal; // ��������
	unsigned tetrisCount[7]; // ��������
	unsigned tetrisTotal; // ��������
	bool dead; // ��
} TetrisManager;

// =============================================================================
typedef struct TetrisControl // ����ṹ��洢�����������
{
	bool pause; // ��ͣ
	bool clockwise; // ��ת����˳ʱ��Ϊtrue
	int8_t direction; // �ƶ�����0�����ƶ� 1�����ƶ�
	// ��Ϸ����ÿ�����ɫ
	// ���ڴ˰汾�ǲ�ɫ�ģ�������Ϸ�������޷��洢��ɫ��Ϣ
	// ���ֻʵ�ֵ�ɫ��ģ���û��Ҫ�����������
	int8_t color[28][16];
} TetrisControl;
