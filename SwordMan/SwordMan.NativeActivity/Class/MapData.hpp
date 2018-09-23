/**
* @file MapData.hpp
* @brief マップを形成する各種データの構造体
* @author feveleK5563
* @date 2018/9/20
*/
#pragma once
#include <string>
#include <array>
#include <vector>

//マップを構成する各種パラメータ
struct MapParam
{
	std::string		mapName;		//マップ名
	std::string		mapDataPath;	//マップ上のブロック配置データへのパス
	size_t	mapWidth, mapHeight;	//マップの広さ
	int		chipSize;				//マップチップ(ブロック)画像の大きさ(横幅)
	int		xSpeed;					//X方向への速度
	std::array<std::string, 3>	backImagePath;	//背景画像へのパス(3つ)
	std::string					chipImagePath;	//マップチップ画像へのパス
};

//マップ上のブロック配置データ
typedef std::vector<std::vector<int>> MapData;