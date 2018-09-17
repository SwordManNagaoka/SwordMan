#pragma once
#include "../ECS/ECS.hpp"
#include "../Utility/Vec.hpp"
#include "../ResourceManager/ResourceManager.hpp"
#include "../Components/BasicComponents.hpp"


namespace ECS
{
	class JumpMove : public Component
	{
	public:
		JumpMove()
			: MaxFallSpeed(15.0f)
		{}
		void	Initialize() override
		{
			jumpPow = -12.0f;
			flag = false;
			gravity = 9.8f / 60.0f / 60.0f;
			fallSpeed = 0.0f;
		}
		void	Update() override
		{
			//ジャンプフラグが立つと、ジャンプする
			if (flag)
			{
				fallSpeed = jumpPow;
			}
			fallSpeed += gravity;
			
			//位置に落下速度を加算
			if (entity->HasComponent<Position>())
			{
				Position& pos = entity->GetComponent<Position>();
				pos.val.y += fallSpeed;
			}

			//落下速度の制御
			if (fallSpeed >= MaxFallSpeed)
			{
				fallSpeed = MaxFallSpeed;
			}
		}
		void	Draw2D() override
		{

		}
		//!@brief	ジャンプフラグを設定
		void	SetJumpFlag(bool jumpFlag)
		{
			flag = jumpFlag;
		}
	private:
		void	Draw3D() override {}
	private:
		bool		flag;
		float		gravity;
		float		fallSpeed;
		float		jumpPow;
	private:
		const float	MaxFallSpeed;
	};
}


