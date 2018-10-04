﻿/**
* @file StageLoader.hpp
* @brief csvファイル等からマップデータと敵データの読み込みをします。
* @author feveleK5563
* @date 2018/10/4
*/

#pragma once
#include <functional>
#include "../ECS/ECS.hpp"
#include "../../Utility/Vec.hpp"
#include "../../Utility/Counter.hpp"
#include "StageData.hpp"
#include "../System/System.hpp"
#include "../../ArcheType/Map.hpp"
#include "../../ArcheType/Enemy.hpp"

class StageCreator
{
private:
	StageParam mapParam;
	Counter cntTime;
	Counter cntCreatMapNum;

public:
	//マップパラメータを設定
	void SetMapParam(const StageParam& setMapParam)
	{
		mapParam = setMapParam;
		cntTime.Reset();
		cntCreatMapNum.Reset();

		cntCreatMapNum.SetEndTime(mapParam.mapWidth - 1, 0);
	}

	//平坦なマップで画面内を埋める
	void FillUpFlatMap(std::function<ECS::Entity*(const char*, const Vec2&, const Vec2&, const int, const int, const int)> tileMapArcheType)
	{
		int setNum = (System::SCREEN_WIDIH / mapParam.chipSize) + 1;
		int excess = (setNum * mapParam.chipSize) - System::SCREEN_WIDIH;

		int flatMap[8]{ -1, -1, -1, -1, -1, -1, 0, 1 };
		for (int i = 0; i < setNum; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				Vec2 pos(float((i * mapParam.chipSize) - excess), float(j * mapParam.chipSize));
				Vec2 velocity(float(mapParam.xSpeed), 0.f);
				tileMapArcheType(mapParam.mapImage.c_str(), pos, velocity, mapParam.chipSize, mapParam.chipSize, flatMap[j]);
			}
		}
	}

	//マップと敵の自動生成
	//マップ、敵データを指定しない場合はフラットな地形が生成される
	void Run(const StageArrayData* mapData = nullptr, const StageArrayData* enemyData = nullptr)
	{
		int setChipNum = GetSetMapChipNum();
		for (int i = 0; i < setChipNum; ++i)
		{
			if (mapData == nullptr || cntCreatMapNum.IsMax())
			{
				CreateFlatMap(i);
				continue;
			}
			else
			{
				CreateMap(i, *mapData);
			}

			if (enemyData != nullptr)
			{
				CreateEnemy(i, *enemyData);
			}
			cntCreatMapNum.Add();
		}
	}

private:
	//平坦なマップを生成する
	void CreateFlatMap(int i)
	{
		ECS::MapArcheType tileMapArcheType;
		int flatMap[8]{ -1, -1, -1, -1, -1, -1, 0, 1 };
		for (int y = 0; y < 8; ++y)
		{
			Vec2 pos(float(System::SCREEN_WIDIH + (i * mapParam.chipSize)), float(y * mapParam.chipSize));
			Vec2 velocity(float(mapParam.xSpeed), 0.f);
			tileMapArcheType(mapParam.mapImage.c_str(), pos, velocity, mapParam.chipSize, mapParam.chipSize, flatMap[y]);
		}
	}

	//マップデータを参照し、マップを生成する
	void CreateMap(int i, const StageArrayData& mapData)
	{
		ECS::MapArcheType tileMapArcheType;
		int x = cntCreatMapNum.GetCurrentCount();

		for (int y = 0; y < mapParam.mapHeight; ++y)
		{
			Vec2 pos(float(System::SCREEN_WIDIH + (i * mapParam.chipSize)), float(y * mapParam.chipSize));
			Vec2 velocity(float(mapParam.xSpeed), 0.f);
			tileMapArcheType(mapParam.mapImage.c_str(), pos, velocity, mapParam.chipSize, mapParam.chipSize, mapData[y][x]);
		}
	}

	//敵のデータを参照し、敵を生成する
	void CreateEnemy(int i, const StageArrayData& enemyConstitution)
	{
		ECS::EnemyCommonArcheType enemyArcheType;
		int x = cntCreatMapNum.GetCurrentCount();

		for (int y = 0; y < mapParam.mapHeight; ++y)
		{
			int en = enemyConstitution[y][x];
			if (en < 0)
				continue;

			Vec2 pos(float(System::SCREEN_WIDIH + (i * mapParam.chipSize)), float(y * mapParam.chipSize));
			mapParam.enemyData[en].pos = pos;
			enemyArcheType(mapParam.enemyData[en], en);
		}
	}

	//時間を計測し、配置できるマップチップの数を返す
	int GetSetMapChipNum()
	{
		int nowTime = cntTime.GetCurrentCount();
		int setChip = 0;

		if (mapParam.chipSize % mapParam.xSpeed)
		{
			if (nowTime % mapParam.chipSize == 0)
				setChip = mapParam.xSpeed;
		}
		else
		{
			if (nowTime % (mapParam.chipSize / mapParam.xSpeed) == 0)
				setChip = 1;
		}

		cntTime.Add();

		return setChip;
	}
};