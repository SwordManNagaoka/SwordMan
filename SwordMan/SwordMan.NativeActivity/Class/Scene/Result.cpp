#include "Result.h"

//アーキタイプ

//コンポーネント
#include "../../Components/ImageFontDraw.hpp"

namespace Scene
{
	Result::Result(IOnSceneChangeCallback* sceneTitleChange, const Parameter& parame)
		: AbstractScene(sceneTitleChange)
	{
		
	}

	Result::~Result()
	{
	}
	
	void Result::Update()
	{
	}
	void Result::Draw()
	{
	}
}