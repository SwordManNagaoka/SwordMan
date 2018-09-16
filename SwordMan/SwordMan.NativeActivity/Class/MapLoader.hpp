/**
* @file MapLoader.hpp
* @brief csvファイル等からマップデータの読み込みをします。
* @author tonarinohito
* @date 2018/9/15
*/
#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <functional>
#include "../ECS/ECS.hpp"
class MapLoader
{
private:
	std::vector<std::vector<int>> mapArray;
	std::vector<size_t> posX;
	std::vector<size_t> posY;
public:
	MapLoader(const std::string& path, const std::string& mapName, const Vec2& velocity, const size_t xNum, const size_t yNum, const size_t size,
		std::function<ECS::Entity*(const char*, const Vec2&, const Vec2&, const int, const int, const int)> tileMapArcheType)
	{
		mapArray.resize(yNum);	//1次元目
		for (auto i(0u); i < yNum; ++i)
		{
			mapArray[i].resize(xNum);	//2次元目
		}
		//ファイルを開く
		int handle = FileRead_open(path.c_str());
		if (handle == 0)
		{
			printfDx("HandleError!!!\n");
		}
		//ファイルのサイズを取得する
		int64_t fileSize = FileRead_size(path.c_str());
		if (fileSize == -1)
		{
			printfDx("SizeError!!!\n");
		}
		//ファイルからデータを読み込む
		void *buffer = malloc(fileSize);
		int isRead = FileRead_read(buffer, fileSize, handle);
		if (isRead == -1)
		{
			printfDx("ReadError!!!\n");
		}
		//ファイルを閉じる
		FileRead_close(handle);
		//アプリのデータ保存用のディレクトリパスを取得する
		char pathBuffer[1024];
		GetInternalDataPath(pathBuffer, sizeof(pathBuffer));
		//ディレクトリパスにディレクトリ区切りの『/』とテンポラリファイルの名前を追加する
		strcat(pathBuffer, "/tempfile.txt");
		//テンポラリファイルを書き込み用に開く
		FILE* fp = fopen(pathBuffer,"wb");
		if (fp != NULL)
		{
			//テンポラリファイルにcsvファイルの内容を書き出す
			fwrite(buffer, 1, fileSize, fp);
			//ファイルを閉じる
			fclose(fp);
		}
		//確保したメモリを解放
		free(buffer);
		//テンポラリファイルを開く
		std::ifstream fin(pathBuffer);
		if (fin.is_open() == 0)
		{
			printfDx("Error!!!");
		}
		//チップIDの読み込み
		for (auto y(0u); y < yNum; ++y)
		{
			for (auto x(0u); x < xNum; ++x)
			{
				fin >> mapArray[y][x];
			}
		}
		fin.close();

		//配置するチップの座標
		posX.resize(xNum);
		posY.resize(yNum);
		for (auto y(0u); y < yNum; ++y)
		{
			posY[y] = y * size;
		}
		for (auto x(0u); x < xNum; ++x)
		{
			posX[x] = x * size;
		}

		for (auto y(0u); y < yNum; ++y)
		{
			for (auto x(0u); x < xNum; ++x)
			{
				tileMapArcheType(mapName.c_str(), Vec2((float)posX[x], (float)posY[y]), Vec2(velocity), int(size), int(size), mapArray[y][x]);
			}
		}
	}

};