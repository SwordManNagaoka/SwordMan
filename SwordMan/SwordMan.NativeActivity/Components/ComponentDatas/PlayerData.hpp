#pragma once
#include "../../ECS/ECS.hpp"
#include "../../Utility/Vec.hpp"
#include "../../ResourceManager/ResourceManager.hpp"
#include "../../Utility/Counter.hpp"


struct PlayerData
{
	enum class State
	{
		Walk,
		Jump,
		Attack,
		JumpAttack,
		Damage,
		Death
	};
	State	state;
};


struct Health : public ECS::ComponentData
{
	Counter value;
};