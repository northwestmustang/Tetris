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

// 控制台输出句柄
extern HANDLE g_hConsoleOutput;
// =============================================================================
// 7种方块的4旋转状态（4位为一行）
static const uint16_t gs_uTetrisTable[7][4] =
{
	{ 0x00F0U, 0x2222U, 0x00F0U, 0x2222U }, // I型
	{ 0x0072U, 0x0262U, 0x0270U, 0x0232U }, // T型
	{ 0x0223U, 0x0074U, 0x0622U, 0x0170U }, // L型
	{ 0x0226U, 0x0470U, 0x0322U, 0x0071U }, // J型
	{ 0x0063U, 0x0264U, 0x0063U, 0x0264U }, // Z型
	{ 0x006CU, 0x0462U, 0x006CU, 0x0462U }, // S型
	{ 0x0660U, 0x0660U, 0x0660U, 0x0660U }  // O型
};
// =============================================================================
// 初始状态的游戏池
// 每个元素表示游戏池的一行，下标大的是游戏池底部
// 两端各置2个1，底部2全置为1，便于进行碰撞检测
// 这样一来游戏池的宽度为12列
// 如果想要传统的10列，只需多填两个1即可（0xE007），当然显示相关部分也要随之改动
// 当某个元素为0xFFFFU时，说明该行已被填满
// 顶部4行用于给方块，不显示出来
// 再除去底部2行，显示出来的游戏池高度为22行
static const uint16_t gs_uInitialTetrisPool[28] =
{
	0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U,
	0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U,
	0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U,
	0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xC003U, 0xFFFFU, 0xFFFFU
};
// =============================================================================
typedef struct TetrisManager // 这个结构体存储游戏相关数据
{
	uint16_t pool[28]; // 游戏池
	int8_t x; // 当前方块x坐标，此处坐标为方块左上角坐标
	int8_t y; // 当前方块y坐标
	int8_t type[3]; // 当前、下一个和下下一个方块类型
	int8_t orientation[3]; // 当前、下一个和下下一个方块旋转状态
	unsigned score; // 得分
	unsigned erasedCount[4]; // 消行数
	unsigned erasedTotal; // 消行总数
	unsigned tetrisCount[7]; // 各方块数
	unsigned tetrisTotal; // 方块总数
	bool dead; // 挂
} TetrisManager;

// =============================================================================
typedef struct TetrisControl // 这个结构体存储控制相关数据
{
	bool pause; // 暂停
	bool clockwise; // 旋转方向：顺时针为true
	int8_t direction; // 移动方向：0向左移动 1向右移动
	// 游戏池内每格的颜色
	// 由于此版本是彩色的，仅用游戏池数据无法存储颜色信息
	// 如果只实现单色版的，就没必要用这个数组了
	int8_t color[28][16];
} TetrisControl;
