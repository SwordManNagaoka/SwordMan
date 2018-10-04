/**
* @file StageLoader.hpp
* @brief csvファイル等からマップデータと敵データの読み込みをします。
* @author tonarinohito
* @date 2018/9/15
* @par History
- 2018/09/21 feveleK5563
-# 「マップパラメータファイル」から必要なデータを全て取得できるようにした
*/
#pragma once
#include <sstream>
#include <fstream>
#include "DXFilieRead.hpp"
#include "StageData.hpp"
#include "../ResourceManager/ResourceManager.hpp"

class StageLoader
{
private:
	StageParam	mapParam;
	StageArrayData	mapData;
	StageArrayData	enemyData;
public:
	StageLoader(const std::string& mapParamPath)
	{
		//ファイルを開く
		std::ifstream fin(DXFilieRead().GetPath(mapParamPath, "/mapData.txt"));
		if (fin.is_open() == 0)
		{
			printfDx("Error!!!");
		}

		//各種パラメーターを読み込む
		fin >>	mapParam.mapImage >>
				mapParam.mapDataPath >>
				mapParam.enemyConstitutionPath >>
				mapParam.mapWidth >> mapParam.mapHeight >>
				mapParam.chipSize >>
				mapParam.xSpeed >>
				mapParam.backImagePath[0] >> mapParam.backImagePath[1] >> mapParam.backImagePath[2] >>
				mapParam.chipImagePath >>
				mapParam.enemyDataPath[0] >>
				mapParam.enemyDataPath[1] >>
				mapParam.enemyDataPath[2] >>
				mapParam.enemyDataPath[3] >>
				mapParam.enemyDataPath[4];

		fin.close();

		//ここで使用するリソースを読み込む
		for (int i = 0; i < 3; ++i)
		{
			//背景
			//std::stringstream ss;
			//ss << i;
			//ResourceManager::GetGraph().Load(mapParam.backImagePath[i], mapParam.mapName + "back" + ss.str());
		}
		//マップチップ
		ResourceManager::GetGraph().Load(mapParam.chipImagePath, mapParam.mapImage);
	}

	//マップと敵配置の構成、敵種類データを読み込む
	void LoadStageConstitution()
	{
		mapData.resize(mapParam.mapHeight);	//1次元目
		enemyData.resize(mapParam.mapHeight);
		for (auto i(0u); i < mapParam.mapHeight; ++i)
		{
			mapData[i].resize(mapParam.mapWidth);	//2次元目
			enemyData[i].resize(mapParam.mapWidth);
		}

		//マップ構成ファイルを開く
		std::ifstream mapfin(DXFilieRead().GetPath(mapParam.mapDataPath, "/map.txt"));
		std::ifstream enemyfin(DXFilieRead().GetPath(mapParam.enemyConstitutionPath, "/enemy.txt"));
		if ((mapfin.is_open() == 0) ||
			(enemyfin.is_open() == 0))
		{
			printfDx("Error!!!");
		}

		//チップIDの読み込み
		for (size_t y = 0; y < mapParam.mapHeight; ++y)
		{
			for (size_t x = 0; x < mapParam.mapWidth; ++x)
			{
				mapfin >> mapData[y][x];
				enemyfin >> enemyData[y][x];
			}
		}
		mapfin.close();
		enemyfin.close();

		//敵種類データの読み込み
		for (size_t i = 0; i < mapParam.enemyDataPath.size(); ++i)
		{
			std::ifstream enemyfin(DXFilieRead().GetPath(mapParam.enemyDataPath[i], "/enemyData.txt"));
			enemyfin >> mapParam.enemyData[i].size.x >> mapParam.enemyData[i].size.y >>
						mapParam.enemyData[i].imageName >>
						mapParam.enemyData[i].animNum >>
						mapParam.enemyData[i].changeAnimFrameTime >>
						mapParam.enemyData[i].moveSpeed >>
						mapParam.enemyData[i].jumpPower;
			enemyfin.close();
		}
	}

	const StageParam& GetStageParam()
	{
		return mapParam;
	}
	const StageArrayData& GetStageData()
	{
		return mapData;
	}
	const StageArrayData& GetEnemyData()
	{
		return enemyData;
	}
};

