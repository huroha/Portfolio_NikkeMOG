#include "pch.h"
#include "CBtnBust_UI.h"
#include "CTexture.h"
#include "CEngine.h"
#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CAssetMgr.h"
#include "CSound.h"

CBtnBust_UI::CBtnBust_UI()
	: m_Texture(nullptr)
	, m_StartWidth(0)
	, m_StartHeight(0)
	, m_Time(0.f)
	, m_IsCool(true)
	, m_CutSize(1)

{
}

CBtnBust_UI::~CBtnBust_UI()
{
}


void CBtnBust_UI::Tick_UI()
{
	m_IsCool = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->IsSkillCool();

	if (m_IsCool)
	{
		m_Time += DT;
	}
	else
	{
		m_Count = 0;
	}

	if (m_Time > 0.1f && m_IsCool)
	{
		if (!CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->IsAccess())
		{
			m_Count += 1;
			m_Time = 0;
		}

	}

	if (m_Count == 100)
	{
		CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->AccessSkill(true);

	}




}

void CBtnBust_UI::Render_UI()
{


	Vec2 vPos = GetFinalPos();
	UINT width = m_Texture->GetWidth() / m_CutSize;
	float height = m_Texture->GetHeight();


	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	// ÁÂ»ó´Ü x, ÁÂ»ó´Ü y , x±æÀÌ, y±æÀÌ
	AlphaBlend(BackDC, (int)vPos.x , (int)vPos.y - (height / 100) * m_Count,
							width , (height / 100) * m_Count,
		m_Texture->GetDC(), width * m_StartWidth, height - (height / 100) * m_Count, width, (height / 100) * m_Count, blend);

	//(height - (height / 10) * m_Count)
}
