#include "pch.h"
#include "CCount_Skill.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CEngine.h"
#include "CPanel_Tex.h"

CCount_Skill::CCount_Skill()
	: m_StartWidth(1)
{
}

CCount_Skill::~CCount_Skill()
{
}


void CCount_Skill::Tick_UI()
{
}

void CCount_Skill::Render_UI()
{

	CPanel_Tex* pParent = dynamic_cast<CPanel_Tex*>(GetParentUI());
	if (pParent->GetVisible())
	{

		Vec2 vPos = GetFinalPos();
		UINT width = GetTexture()->GetWidth() / 10;
		UINT height = GetTexture()->GetHeight() / 3;


		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
			, width, height, GetTexture()->GetDC(), m_StartWidth * width, 0, width, height, blend);
	}
}
