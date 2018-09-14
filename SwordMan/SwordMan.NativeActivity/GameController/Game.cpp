﻿#include "Game.h"
#include "../ResourceManager/ResourceManager.hpp"
#include "../../Components/BasicComponents.hpp"
#include "../../Components/Renderer.hpp"
#include "../../Components/Collider.hpp"
void Game::EventUpDate()
{

}

void Game::ResourceLoad()
{
	ResourceManager::GetGraph().Load("image/a.png","a");
}

Game::Game()
{
	ResourceLoad();
	pManager = &ECS::EcsSystem::GetManager();
	auto& e = pManager->AddEntity();
	e.AddComponent<ECS::Position>(100.f,100.f);
	e.AddComponent<ECS::CircleColiider>(20.f);
	e.AddComponent<ECS::SimpleDraw>("a");
}

void Game::ResetGame()
{

}

void Game::Update()
{
	pManager->Refresh();
	pManager->Update();


	if (touchInput.Press(0))
	{
		DrawFormatString(touchInput.GetTouchIDPos(0).x, touchInput.GetTouchIDPos(0).y, GetColor(0,255,0),"タップ0番が押されています");
	}
	touchInput.Run();
}

void Game::Draw()
{
	pManager->Draw2D();
}
