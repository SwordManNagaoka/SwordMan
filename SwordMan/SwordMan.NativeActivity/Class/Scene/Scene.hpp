/**
* @file Scene.hpp
* @brief シーンの管理を行います
* @author tonarinohito
* @date 2018/9/17
*/
#pragma once
#include "../../ECS/ECS.hpp"
#include "../../GameController/GameController.h"
#include "../../Utility/Utility.hpp"
#include "Title.hpp"
#include "Menu.hpp"
#include "Pause.hpp"
#include "Game.hpp"
#include "Result.hpp"
namespace Scene
{
	class ISceneBase
	{
		//!Entityの初期化、生成を記述します
		virtual void Initialize() = 0;
		//!Entityのイベント処理を記述します
		virtual void EventUpdate() = 0;
		//!Entityの更新をまとめます
		virtual void Update() = 0;
		//!Entityの描画をまとめます
		virtual void Draw() = 0;
		//!Entityの削除を行います
		virtual void CleanUp() = 0;
	};

	//ミニマルなゲームなためまとめて管理
	class SceneManager final
	{
	private:
		enum class State
		{
			Title,
			Menu,
			Pause,
			Game,
			Result,
		};
		State state;
		Title* title;
		Menu* menu;
		Pause* pause;
		Game* game;
		Result* result;

	public:
		SceneManager()
		{
			title = new Title();
			menu = new Menu();
			pause = new Pause();
			game = new Game();
			result = new Result();

		}
		~SceneManager()
		{
			Memory::SafeDelete(title);
			Memory::SafeDelete(menu);
			Memory::SafeDelete(pause);
			Memory::SafeDelete(game);
			Memory::SafeDelete(result);
		}
		void ChangeScene(const State& sceneName)
		{
			state = sceneName;
		}
		void EventUpdate()
		{
			switch (state)
			{
			case State::Title:  title->EventUpdate();  break;
			case State::Menu:   menu->EventUpdate();   break;
			case State::Game:   game->EventUpdate();   break;
			case State::Pause:  pause->EventUpdate();  break;
			case State::Result: result->EventUpdate(); break;
			}
		}
		void Update()
		{
			switch (state)
			{
			case State::Title:  title->Update();  break;
			case State::Menu:   menu->Update();   break;
			case State::Game:   game->Update();   break;
			case State::Pause:  pause->Update();  break;
			case State::Result: result->Update(); break;
			}
		}

		void Draw()
		{
			switch (state)
			{
			case State::Title:  title->Draw();  break;
			case State::Menu:   menu->Draw();   break;
			case State::Game:   game->Draw();   break;
			case State::Pause:  pause->Draw();
			case State::Result: result->Draw(); break;
			}
		}
	};
}
