/**
* @file MapLoader.hpp
* @brief csvファイル等からマップデータの読み込みをします。
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
		std::ifstream fin(DXFilieRead().GetPath(mapParamPath));
		if (fin.is_open() == 0)
		{
			printfDx("Error!!!");
		}

		//各種パラメーターを読み込む
		fin >>	mapParam.mapImage >>
				mapParam.mapDataPath >>
				mapParam.enemyDataPath >>
				mapParam.mapWidth >> mapParam.mapHeight >>
				mapParam.chipSize >>
				mapParam.xSpeed >>
				mapParam.backImagePath[0] >> mapParam.backImagePath[1] >> mapParam.backImagePath[2] >>
				mapParam.chipImagePath;

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

	//マップと敵配置の構成を読み込む
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
		std::ifstream mapfin(DXFilieRead().GetPath(mapParam.mapDataPath));
		std::ifstream enemyfin(DXFilieRead().GetPath(mapParam.enemyDataPath));
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

