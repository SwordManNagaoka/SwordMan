/**
* @file SceneManager.hpp
* @brief Sceneオブジェクトを管理します
* @author tonarinohito
* @date 2018/9/21
*/
#pragma once
#include "../../ECS/ECS.hpp"
#include "../../Utility/Utility.hpp"
#include "Scene.hpp"
#include "Game.hpp"
#include "Title.hpp"
#include "Result.hpp"
#include "Pause.hpp"
#include "Menu.hpp"

namespace Scene
{
	class SceneManager final
	{
	public:
		enum class Scene
		{
			Title,
			Game,
			Menu,
			Pause,
			Result,
		};
	private:
		class Singleton final
		{
		private:
			ISceneBase* pScene = nullptr;
		public:
			~Singleton()
			{
				Memory::SafeDelete(pScene);
			}
			void ChangeScene(Scene scene)
			{
				Memory::SafeDelete(pScene);
				switch (scene)
				{
				case Scene::Title:	pScene = new Title();  break;
				case Scene::Game:	pScene = new Game();   break;
				case Scene::Menu:	pScene = new Menu();   break;
				case Scene::Pause:	pScene = new Pause();  break;
				case Scene::Result:	pScene = new Result(); break;	
				}
			}
			void Update()
			{
				pScene->Update();
			}
			void Draw()
			{
				pScene->Draw();
			}
		};
	public:
		inline static Singleton& Get()
		{
			static std::unique_ptr<Singleton> inst =
				std::make_unique<Singleton>();
			return *inst;
		}
	};

}