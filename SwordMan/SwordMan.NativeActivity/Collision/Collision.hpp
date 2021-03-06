﻿/**
* @file Collision.hpp
* @brief Collisionの式をまとめたファイルです
* @author tonarinohito
* @date 2018/8/29
* @par History
- 2018/09/17 日比野　真聖
-# 円と点のコリジョン追加
*/
#pragma once
#include "../ECS/ECS.hpp"
#include "../Components/Collider.hpp"
struct Collision
{
	template<class T = ECS::HitBase, class TData = ECS::HitBase>
	inline static bool BoxAndBox(const ECS::Entity& b1, const ECS::Entity& b2)
	{
		if (!b1.HasComponent<T>() || !b2.HasComponent<TData>())
		{
			return false;
		}
		const auto& box1 = b1.GetComponent<T>();
		const auto& box2 = b2.GetComponent<TData>();
		if (box1.x() < box2.x() + box2.w() &&
			box2.x() < box1.x() + box1.w() &&
			box1.y() < box2.y() + box2.h() &&
			box2.y() < box1.y() + box1.h())
		{
			return true;
		}
		return false;
	}
	inline static bool BoxAndBox(const Vec2& b1Pos, const Vec2& b1Size, const Vec2& b2Pos, const Vec2& b2Size) noexcept
	{
		if (b1Pos.x < b2Pos.x + b2Size.x &&
			b2Pos.x < b1Pos.x + b1Size.x &&
			b1Pos.y < b2Pos.y + b2Size.y &&
			b2Pos.y < b1Pos.y + b1Size.y)
		{
			return true;
		}
		return false;
	}
	template<class T = ECS::CircleColiider, class TData = ECS::CircleColiider>
	inline static bool CircleAndCircle(const ECS::Entity& e1, const ECS::Entity& e2)
	{
		if (!e1.HasComponent<T>() || !e2.HasComponent<TData>())
		{
			return false;
		}
		const auto& c1 = e1.GetComponent<T>();
		const auto& c2 = e2.GetComponent<TData>();
		if (((c1.x() - c2.x()) *(c1.x() - c2.x())) + ((c1.y() - c2.y()) * (c1.y() - c2.y())) <=
			(c1.radius() + c2.radius()) * (c1.radius() + c2.radius()))
		{
			return true;
		}
		return false;
	}
	inline static bool CircleAndCircle(const Vec2& c1Pos, const float& c1r, const Vec2& c2Pos, const float& c2r) noexcept
	{
		if (((c1Pos.x - c2Pos.x) *(c1Pos.x - c2Pos.x)) + ((c1Pos.y - c2Pos.y) * (c1Pos.y - c2Pos.y)) <=
			(c1r + c2r) * (c1r + c2r))
		{
			return true;
		}
		return false;
	}

	//円と点の当たり判定
	template<class T = ECS::CircleColiider, class TData = ECS::Position>
	inline static bool CircleAndPoint(const ECS::Entity& b1, const ECS::Entity& b2)
	{
		if (!b1.HasComponent<T>() || !b2.HasComponent<TData>())
		{
			return false;
		}
		const auto& circle = b1.GetComponent<T>();
		const auto& point = b2.GetComponent<TData>();

		Vec2 buttonPos = Vec2(circle.x(), circle.y());
		Vec2 distance = buttonPos - point.val();
		if (distance.Length() <= circle.radius())
		{
			return true;
		}
		return false;
	}

	inline static bool CircleAndPoint(const Vec2& circlePos, const float& circleRadius, const Vec2& pointPos) noexcept
	{
		Vec2 distance = circlePos - pointPos;
		if (distance.Length() <= circleRadius)
		{
			return true;
		}
		return false;
	}
};
