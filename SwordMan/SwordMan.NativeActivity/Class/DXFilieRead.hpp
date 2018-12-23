﻿/**
* @file MapLoader.hpp
* @brief アンドロイドプログラミングでアクセスできるパスを取得します。
* @author tonarinohito
* @date 2018/9/18
*/
#pragma once
#include <DxLib.h>
#include <string>

class DXFilieRead final
{
private:
	char pathBuffer[1024];
public:
	const char* GetPath(const std::string& path, const char* tempFileName)
	{
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
		GetInternalDataPath(pathBuffer, sizeof(pathBuffer));
		//ディレクトリパスにディレクトリ区切りの『/』とテンポラリファイルの名前を追加する
		strcat(pathBuffer, tempFileName);
		//テンポラリファイルを書き込み用に開く
		FILE* fp = fopen(pathBuffer, "wb");
		if (fp != NULL)
		{
			//テンポラリファイルにcsvファイルの内容を書き出す
			fwrite(buffer, 1, fileSize, fp);
			//ファイルを閉じる
			fclose(fp);
		}
		//確保したメモリを解放
		free(buffer);
		return pathBuffer;
	}
};

class FileSystem final
{
public:
	const bool Save(const std::string& fileName, int* saveData) noexcept
	{
		char filePath[256];
		DxLib::GetInternalDataPath(filePath, sizeof(filePath));

		strcat(filePath, "/");
		strcat(filePath, fileName.c_str());

		//そのあと、既存のファイルに書き込む
		std::ofstream fon(filePath, std::ios::out);
		if (!fon.is_open())
		{
			printfDx("save file error : %s\n", fileName.c_str());
			return false;
		}
		fon << *saveData;
		fon.close();
		return true;
	}
	const bool Load(const std::string& fileName, int* loadData) noexcept
	{
		char filePath[256];
		DxLib::GetInternalDataPath(filePath, sizeof(filePath));

		strcat(filePath, "/");
		strcat(filePath, fileName.c_str());

		std::fstream inputFile(filePath);
		if (!inputFile.is_open())
		{
			printfDx("load file error : %s \n", fileName.c_str());
			return false;
		}
		inputFile >> *loadData;
		inputFile.close();

		//printfDx("load file : %s\n", filePath);
		//printfDx("load data : %d\n", *loadData);
		return true;
	}
	const bool HighScoreSave(const std::string& fileName, int* saveData) noexcept
	{
		int highScore = 0;
		if (!Load(fileName, &highScore)) { return false; }
		if (*saveData >= highScore)
		{
			if (!Save(fileName, saveData)) { return false; }
		}
		return true;
	}
};