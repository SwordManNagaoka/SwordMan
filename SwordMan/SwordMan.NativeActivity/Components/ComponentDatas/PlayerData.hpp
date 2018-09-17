#pragma once
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
	Counter	health;
	State	state;
};