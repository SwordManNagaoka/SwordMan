//----------------------------------------------------
//!@file	EnemyData.hpp
//!@brief	敵のデータを作成します
//!@author	日比野　真聖
//!@date	2018/9/30
//----------------------------------------------------
#pragma once
#include "../../ECS/ECS.hpp"
#include "../../Utility/Vec.hpp"
#include "../../Components/ComponentDatas/CollisionData.hpp"


namespace ECS
{
	//共通
	struct EnemyCommonData
	{
		std::string imageName;
		Vec2 pos;
		int id;
		int animNum;
		int changeAnimFrameTime;
	};
	//ノーマル(青鎧・水色羽)
	struct NormalEnemyData
	{
		EnemyCommonData commonData;
		BoxCollisionData collisionData;
	};
	//赤車輪
	struct LeftMoveEnemyData
	{
		EnemyCommonData commonData;
		BoxCollisionData collisionData;
		float moveSpeed;
	};
	//緑バネ
	struct JumpMoveEnemyData
	{
		EnemyCommonData commonData;
		BoxCollisionData collisionData;
		float jumpPow;
	};
	//ゴール
	struct GoalData
	{
		EnemyCommonData commonData;
		BoxCollisionData collisionData;
	};
}