#include "pch.h"
#include "CLevel_Start.h"
#include "CLevelMgr.h"

#include "CEngine.h"
#include "CPlayer.h"
#include "CForce.h"

#include "CEnemy.h"
#include "CEnemy1.h"

#include "CPlatform.h"
#include "CTile.h"
#include "CAssetMgr.h"
#include "CSound.h"

#include "CPauseMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"

#include "CMap.h"
#include "CCam.h"


#include "CLogMgr.h"
#include "CUIMgr.h"

#include "CEnemySpawner.h"


#include "CItemSpawner.h"
#include "CItem.h"

#include "CMissileSpawner.h"
#include "CSpawner_Crown.h"
#include "CSpawner_Modernia.h"
#include "CSpawner_Snow.h"
#include "CSpawner_Lapun.h"
#include "CSpawner_Gren.h"
#include "CSpawner_Killo.h"
#include "CSpawner_Indi.h"

#include "CMissile.h"
#include "CModernia.h"
#include "CSnow.h"
#include "CLapunzel.h"
#include "CGren.h"
#include "CKillo.h"

#include "CDig_Missile.h"
#include "CBasic_Missile.h"
#include "CTrace_Missile.h"
#include "CThunder_Missile.h"
#include "CTail.h"

#include "UI_Header.h"
#include "time.h"

#include "CBoss.h"
#include "CBossSpawner.h"

#include "CEffectSpawner.h"
#include "CEffect_Dead.h"


#include "CSound.h"
#include "CBtnBust_UI.h"
#include "CDarkUI.h"




CLevel_Start::CLevel_Start()
	: m_PauseMenu(nullptr)
	, m_SkillMenu(nullptr)
	, m_ResultMenu(nullptr)
	, m_DarkFilter(nullptr)
	, m_ChoosePassive{}
	, m_ChooseWeapon{}
	, m_IsWeapon{}
	, m_Seed(0)
{
}

CLevel_Start::~CLevel_Start()
{
}




void CLevel_Start::Init()
{
	// 메뉴 제거
	SetMenu(CEngine::Get()->GetMainHwnd(), nullptr);

	// 메뉴가 제거되었으니, 윈도우 크기 다시 계산
	UINT width = CEngine::Get()->GetResolution().x;
	UINT height = CEngine::Get()->GetResolution().y;
	CEngine::Get()->ChangeWindowResolution(width, height);

	CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Stage_1", L"sound\\Front of the Castle.wav");

	pBGM->PlayToBGM(true);
	pBGM->SetVolume(40.f);

	Vec2 vResol = CEngine::Get()->GetResolution();

	// 오브젝트 위치 설정
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(vResol / 2.f);

	// 플레이어를 현재 레벨에 등록
	RegisterPlayer(pPlayer);

	// 플레이어를 레벨에 추가
	AddObject(pPlayer, LAYER_TYPE::PLAYER);

	//Enemy 미리 생성
	CEnemy1* pObj = new CEnemy1;
	pObj->SetName(L"Enemy1");
	pObj->SetPos(vResol.x / 2.f + 300.f, vResol.y / 4.f - 100.f);
	pObj->SetDead(true);
	AddObject(pObj, LAYER_TYPE::ENEMY);

	for (int i = 0; i < 100; ++i)
	{
		CEnemy1* pCloneEnemy = pObj->Clone();
		pCloneEnemy->SetPos(Vec2(100.f, 100.f));
		pCloneEnemy->SetDead(true);
		if (i % 2 == 0)
		{
			pCloneEnemy->ChangeEnemy();
			pCloneEnemy->SetEnemy2Collider();
		}

		AddObject(pCloneEnemy, LAYER_TYPE::ENEMY);

	}




	// Item 미리 생성
	CItem* pItem = new CItem;
	pItem->SetName(L"Item_HP");
	pItem->SetPos(Vec2(0.f, 0.f));
	pItem->SetDead(true);
	pItem->ChooseItem(0);
	pItem->SetTexture(CAssetMgr::Get()->LoadTexture(L"Item", L"texture\\Item.png"));
	AddObject(pItem, LAYER_TYPE::ITEM);

	for (int i = 1; i < 5; ++i)
	{
		CItem* pCloneItem = pItem->Clone();
		pCloneItem->SetName(L"Item_HP");
		pCloneItem->SetPos(Vec2(0.f,0.f));
		pCloneItem->SetDead(true);
		pCloneItem->ChooseItem(0);
		pCloneItem->SetTexture(CAssetMgr::Get()->LoadTexture(L"Item", L"texture\\Item.png"));
		AddObject(pCloneItem, LAYER_TYPE::ITEM);
	}
	for (int i = 5; i < 305; ++i)
	{
		CItem* pCloneItem = pItem->Clone();
		pCloneItem->SetName(L"Item_Coin");
		pCloneItem->SetPos(Vec2(0.f, 0.f));
		pCloneItem->SetDead(true);
		pCloneItem->ChooseItem(1);
		pCloneItem->SetTexture(CAssetMgr::Get()->LoadTexture(L"Item", L"texture\\Item.png"));
		AddObject(pCloneItem, LAYER_TYPE::ITEM);
	}
	for (int i = 305; i < 605; ++i)
	{
		CItem* pCloneItem = pItem->Clone();
		pCloneItem->SetName(L"Item_Exp");
		pCloneItem->SetPos(Vec2(0.f, 0.f));
		pCloneItem->SetDead(true);
		pCloneItem->ChooseItem(2);
		pCloneItem->SetTexture(CAssetMgr::Get()->LoadTexture(L"Item", L"texture\\Item.png"));
		AddObject(pCloneItem, LAYER_TYPE::ITEM);
	}
	for (int i = 605; i < 705; ++i)
	{
		CItem* pCloneItem = pItem->Clone();
		pCloneItem->SetName(L"Item_Exp2");
		pCloneItem->SetPos(Vec2(0.f, 0.f));
		pCloneItem->SetDead(true);
		pCloneItem->ChooseItem(3);
		pCloneItem->SetTexture(CAssetMgr::Get()->LoadTexture(L"Item", L"texture\\Item.png"));
		AddObject(pCloneItem, LAYER_TYPE::ITEM);
	}

	for (int i = 705; i < 750; ++i)
	{
		CItem* pCloneItem = pItem->Clone();
		pCloneItem->SetName(L"Item_Exp3");
		pCloneItem->SetPos(Vec2(0.f, 0.f));
		pCloneItem->SetDead(true);
		pCloneItem->ChooseItem(4);
		pCloneItem->SetTexture(CAssetMgr::Get()->LoadTexture(L"Item", L"texture\\Item.png"));
		AddObject(pCloneItem, LAYER_TYPE::ITEM);
	}

	//for (int i = 640; i < 650; ++i)
	//{
	//	CItem* pCloneItem = pItem->Clone();
	//	pCloneItem->SetName(L"Item_bust");
	//	pCloneItem->SetPos(Vec2(0.f, 0.f));
	//	pCloneItem->SetDead(true);
	//	pCloneItem->ChooseItem(5);
	//	pCloneItem->SetTexture(CAssetMgr::Get()->LoadTexture(L"Item", L"texture\\Item.png"));
	//	AddObject(pCloneItem, LAYER_TYPE::ITEM);
	//}


	// Missile 미리 스폰
	// 크라운 미사일
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Weapon_Crown");
	pMissile->SetDead(true);
	pMissile->SetTexture(CAssetMgr::Get()->LoadTexture(L"crown_bullet", L"texture\\crownmFix.png"));
	AddObject(pMissile, LAYER_TYPE::PLAYER_PROJECTILE);

	for (int i = 1; i < 200; ++i)
	{
		CMissile* pCloneMissile = pMissile->Clone();
		pCloneMissile->SetDead(true);
		AddObject(pCloneMissile, LAYER_TYPE::PLAYER_PROJECTILE);
	}

	// 모더니아 미사일
	CModernia* pModer = new CModernia;
	pModer->SetName(L"Weapon_Modernia");
	pModer->SetDead(true);
	AddObject(pModer, LAYER_TYPE::PLAYER_PROJECTILE);

	// 스화 미사일
	CSnow* pSnow = new CSnow;
	pSnow->SetName(L"Weapon_Snow");
	pSnow->SetDead(true);
	pSnow->SetTexture(CAssetMgr::Get()->LoadTexture(L"snow_bullet", L"texture\\snow_lv0.png"));
	AddObject(pSnow, LAYER_TYPE::PLAYER_PROJECTILE);

	for (int i = 1; i < 20; ++i)
	{
		pSnow = new CSnow;
		pSnow->SetName(L"Weapon_Snow");
		pSnow->SetDead(true);
		pSnow->SetTexture(CAssetMgr::Get()->LoadTexture(L"snow_bullet", L"texture\\snow_lv0.png"));
		AddObject(pSnow, LAYER_TYPE::PLAYER_PROJECTILE);
	}

	// 라푼젤 미사일
	CLapunzel* pLapun = new CLapunzel;
	pLapun->SetName(L"Weapon_Lapunzel");
	pLapun->SetDead(true);
	pLapun->SetTexture(CAssetMgr::Get()->LoadTexture(L"Skill_Lapunzel", L"texture\\Skill_Lapunzel.png"));
	AddObject(pLapun, LAYER_TYPE::PLAYER_PROJECTILE);

	for (int i = 1; i < 19; ++i)
	{
		pLapun = new CLapunzel;
		pLapun->SetName(L"Weapon_Lapunzel");
		pLapun->SetDead(true);
		pLapun->SetTexture(CAssetMgr::Get()->LoadTexture(L"Skill_Lapunzel", L"texture\\Skill_Lapunzel.png"));
		AddObject(pLapun, LAYER_TYPE::PLAYER_PROJECTILE);
	}
	

	// 홍련 미사일
	CGren* pGren = new CGren;
	pGren->SetName(L"Weapon_Gren");
	pGren->SetDead(true);
	AddObject(pGren, LAYER_TYPE::PLAYER_PROJECTILE);

	for (int i = 1; i < 10; ++i)
	{
		pGren = new CGren;
		pGren->SetName(L"Weapon_Gren");
		pGren->SetDead(true);
		AddObject(pGren, LAYER_TYPE::PLAYER_PROJECTILE);
	}


	// 킬로 무기
	CKillo* pKillo = new CKillo;
	pKillo->SetName(L"Weapon_Killo");
	pKillo->SetDead(true);
	AddObject(pKillo, LAYER_TYPE::PLAYER_PROJECTILE);

	// Boss 미사일
	// Basic Missile
	CBasic_Missile* pBossBasic = new CBasic_Missile;
	pBossBasic->SetName(L"BasicAttack");
	pBossBasic->SetDead(true);
	AddObject(pBossBasic, LAYER_TYPE::ENEMY_PROJECTILE);

	for (int i = 1; i < 50; ++i)
	{
		pBossBasic = new CBasic_Missile;
		pBossBasic->SetName(L"BasicAttack");
		pBossBasic->SetDead(true);
		AddObject(pBossBasic, LAYER_TYPE::ENEMY_PROJECTILE);
	}

	// Trace Missile
	CTrace_Missile* pBossTrace = new CTrace_Missile;
	pBossTrace->SetName(L"TraceAttack");
	pBossTrace->SetDead(true);
	AddObject(pBossTrace, LAYER_TYPE::ENEMY_PROJECTILE);

	for (int i = 1; i < 10; ++i)
	{
		pBossTrace = new CTrace_Missile;
		pBossTrace->SetName(L"TraceAttack");
		pBossTrace->SetDead(true);
		AddObject(pBossTrace, LAYER_TYPE::ENEMY_PROJECTILE);
	}


	// Thunder Missile
	CThunder_Missile* pThunder = new CThunder_Missile;
	pThunder->SetName(L"ThunderAttack");
	pThunder->SetTexture(CAssetMgr::Get()->LoadTexture(L"Thunder_Attack", L"texture\\dangerrr.png"));
	pThunder->SetDead(true);
	AddObject(pThunder, LAYER_TYPE::ENEMY_PROJECTILE);

	for (int i = 1; i < 10; ++i)
	{
		pThunder = new CThunder_Missile;
		pThunder->SetName(L"ThunderAttack");
		pThunder->SetTexture(CAssetMgr::Get()->LoadTexture(L"Thunder_Attack", L"texture\\dangerrr.png"));
		pThunder->SetDead(true);
		AddObject(pThunder, LAYER_TYPE::ENEMY_PROJECTILE);
	}



	// 땅속에서 솟구침
	CDig_Missile* pDigAtk = new CDig_Missile;
	pDigAtk->SetName(L"DigAttack");
	pDigAtk->SetDead(true);
	AddObject(pDigAtk, LAYER_TYPE::ENEMY_PROJECTILE);


	// 이펙트 오브젝트 생성
	CEffect_Dead* pEffect = new CEffect_Dead;
	pEffect->SetName(L"Dead_Effect");
	pEffect->SetTexture(CAssetMgr::Get()->LoadTexture(L"Dead_Effect", L"texture\\Dead_Effect_tex.png"));
	pEffect->SetDead(true);
	AddObject(pEffect, LAYER_TYPE::EFFECT_DEAD);




	for (int i = 1; i < 40; ++i)
	{
		pEffect = new CEffect_Dead;
		pEffect->SetName(L"Dead_Effect");
		pEffect->SetTexture(CAssetMgr::Get()->LoadTexture(L"Dead_Effect", L"texture\\Dead_Effect_tex.png"));
		pEffect->SetDead(true);
		AddObject(pEffect, LAYER_TYPE::EFFECT_DEAD);

	}

	// Tail Effect
	CEffect_Dead* pEffectTail = new CEffect_Dead;
	pEffectTail->SetName(L"Dead_Effect_Tail");
	pEffectTail->SetTexture(CAssetMgr::Get()->LoadTexture(L"Dead_Effect_Tail", L"texture\\TailExplosion.png"));
	pEffectTail->SetDead(true);
	pEffectTail->ChangeAnim();
	pEffectTail->SetLimitTime(0.8f);
	AddObject(pEffectTail, LAYER_TYPE::EFFECT_DEAD);
	



	// ItemSpawner
	CItemSpawner* pItemSpawn = new CItemSpawner;
	AddObject(pItemSpawn, LAYER_TYPE::SPAWNER);

	// EnemySpawner
	CEnemySpawner* pSpawn = new CEnemySpawner;
	AddObject(pSpawn, LAYER_TYPE::SPAWNER);

	// Boss_Spawner
	CBossSpawner* pSpawnBoss = new CBossSpawner;
	AddObject(pSpawnBoss, LAYER_TYPE::SPAWNER);


	// 무기군 관리 스포너  아이템이랑 보스 스포너 인덱스로 접근중
	CMissileSpawner* pMissileSpawn = new CMissileSpawner;
	AddObject(pMissileSpawn, LAYER_TYPE::SPAWNER);

	CSpawner_Crown* pSpawnCrown = new CSpawner_Crown;
	AddObject(pSpawnCrown, LAYER_TYPE::SPAWNER);

	CSpawner_Modernia* pSpawnModer = new CSpawner_Modernia;
	AddObject(pSpawnModer, LAYER_TYPE::SPAWNER);

	CSpawner_Snow* pSpawnSnow = new CSpawner_Snow;
	AddObject(pSpawnSnow, LAYER_TYPE::SPAWNER);

	CSpawner_Lapun* pSpawnLapun = new CSpawner_Lapun;
	AddObject(pSpawnLapun, LAYER_TYPE::SPAWNER);

	CSpawner_Gren* pSpawnGren = new CSpawner_Gren;
	AddObject(pSpawnGren, LAYER_TYPE::SPAWNER);

	CSpawner_Killo* pSpawnKillo = new CSpawner_Killo;
	AddObject(pSpawnKillo, LAYER_TYPE::SPAWNER);

	CSpawner_Indi* pSpawnIndiMissile = new CSpawner_Indi;
	pSpawnIndiMissile->SetName(L"Indi_Missile_Spawn");
	AddObject(pSpawnIndiMissile, LAYER_TYPE::SPAWNER);

	// 11번째는 이펙트 담당
	CEffectSpawner* pSpawnEffect = new CEffectSpawner;
	AddObject(pSpawnEffect, LAYER_TYPE::SPAWNER);


	// 보스 생성
	CBoss* pBoss = new CBoss;
	pBoss->SetName(L"Boss_Indivilia");
	pBoss->SetPos(400.f, 500.f);				// 임시 설정용 소환될때 위치 조정할 것.
	pBoss->SetDead(true);						// true 하기전에 작동하는지 확인을 위함.
	AddObject(pBoss, LAYER_TYPE::ENEMY);

	// 보스 등록
	RegisterBoss(pBoss);
	
	CTail* pTail = new CTail;
	pTail->SetName(L"Boss_Tail");
	pTail->SetDead(false);
	AddObject(pTail, LAYER_TYPE::TAIL);



	// Cam
	CCam* pCam = new CCam;
	pCam->SetName(L"Cam");
	pCam->SetPos(0.f,0.f);
	AddObject(pCam, LAYER_TYPE::CAMERA);


	// Map
	CMap* pMap = new CMap;
	pMap->SetName(L"Map1");
	pMap->SetPos(0.f, 0.f);
	pMap->SetScale(2560.f, 2560.f);
	pMap->SetColliderScale();
	pMap->SetTexture(CAssetMgr::Get()->LoadTexture(L"Tile", L"texture\\Back2.png"));
	AddObject(pMap, LAYER_TYPE::TILE);
	


	CMap* pCloneMap = pMap->Clone();
	pCloneMap->SetPos(pMap->GetPos() + Vec2(1280.f, 1280.f));
	pCloneMap->SetName(L"Map3");
	pMap->SetColliderScale();
	pMap->SetTexture(CAssetMgr::Get()->LoadTexture(L"Tile", L"texture\\Back2.png"));
	AddObject(pCloneMap, LAYER_TYPE::TILE);


	pMap = new CMap;
	pMap->SetName(L"Map2");
	pMap->SetPos(1280.f, 0.f);
	pMap->SetScale(2560.f, 2560.f);
	pMap->SetColliderScale();
	pMap->SetTexture(CAssetMgr::Get()->LoadTexture(L"Tile", L"texture\\Back2.png"));
	AddObject(pMap, LAYER_TYPE::TILE);

	pMap = new CMap;
	pMap->SetName(L"Map4");
	pMap->SetPos(0.f, 1280.f);
	pMap->SetScale(2560.f, 2560.f);
	pMap->SetColliderScale();
	pMap->SetTexture(CAssetMgr::Get()->LoadTexture(L"Tile", L"texture\\Back2.png"));
	AddObject(pMap, LAYER_TYPE::TILE);


	// LEVEL GAUGE 
	CGauge* pUI = new CGauge;
	pUI->SetPos(Vec2(571.f, 40.f));
	pUI->SetName(L"LevelGauge");
	AddObject(pUI, LAYER_TYPE::UI);


	CPanel_Tex* pTestbust = new CPanel_Tex;
	pTestbust->SetName(L"Bust");
	pTestbust->SetTexture(CAssetMgr::Get()->LoadTexture(L"testbust", L"texture\\bustskill.png"));
	pTestbust->SetPos(Vec2(vResol.x / 2.f, vResol.y / 2.f));
	pPlayer->RegistBustUI(pTestbust);
	pTestbust->SetVisibleState(false);
	AddObject(pTestbust, LAYER_TYPE::UI);


	CPanel_Tex* pTexBust = new CPanel_Tex;
	pTexBust->SetName(L"BlackBustBtn");
	pTexBust->SetTexture(CAssetMgr::Get()->LoadTexture(L"bustBtn", L"texture\\bust.png"));
	pTexBust->SetCutSize(2);
	pTexBust->SetStartWidth(1);
	pTexBust->SetPos(Vec2(vResol.x - 18.f, vResol.y / 2.f  - 20.f));
	AddObject(pTexBust, LAYER_TYPE::UI);



	CBtnBust_UI* pBustUI = new CBtnBust_UI;
	pBustUI->SetName(L"BustBtn");
	pBustUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"bustBtn", L"texture\\bust.png"));
	pBustUI->SetPos(Vec2(vResol.x -35.f, vResol.y / 2.f + 20.f));
	pBustUI->SetCutSize(2);
	AddObject(pBustUI, LAYER_TYPE::UI);



	/// 상단 UI
	CPanel_Tex* pPanel = new CPanel_Tex;
	pPanel->SetName(L"Top Panel");
	pPanel->SetTexture(CAssetMgr::Get()->LoadTexture(L"IG_TOP_UI", L"texture\\IG_TopUI.png"));
	pPanel->SetPos(Vec2(vResol.x / 2.f, 60.f));
	AddObject(pPanel, LAYER_TYPE::UI);

	// 상단 LEVEL UI
	CLevel_UI* pLUI = new CLevel_UI;
	pLUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"Level_UI", L"texture\\Level_Num.png"));
	pLUI->SetPos(Vec2(-144.f, 4.f));
	pLUI->SetName(L"Level_UI_one");
	pPanel->AddChildUI(pLUI);

	pLUI = new CLevel_UI;
	pLUI->SetName(L"Level_UI_ten");
	pLUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"Level_UI", L"texture\\Level_Num.png"));
	pLUI->SetPos(Vec2(-160.f, 4.f));
	pPanel->AddChildUI(pLUI);


	// Coin CountUI
	CCount_UI* pCoin = new CCount_UI;
	pCoin->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pCoin->SetTextColor(2);
	pCoin->SetName(L"Coin_one");
	pPanel->AddChildUI(pCoin);

	pCoin = new CCount_UI;
	pCoin->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pCoin->SetTextColor(2);
	pCoin->SetName(L"Coin_ten");
	pPanel->AddChildUI(pCoin);

	pCoin = new CCount_UI;
	pCoin->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pCoin->SetTextColor(2);
	pCoin->SetName(L"Coin_hun");
	pPanel->AddChildUI(pCoin);

	pCoin = new CCount_UI;
	pCoin->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pCoin->SetTextColor(2);
	pCoin->SetName(L"Coin_chun");
	pPanel->AddChildUI(pCoin);



	// Slay CountUI
	CCount_UI* pSlay = new CCount_UI;
	pSlay->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pSlay->SetTextColor(1);
	pSlay->SetName(L"Slay_one");
	pPanel->AddChildUI(pSlay);

	pSlay = new CCount_UI;
	pSlay->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pSlay->SetTextColor(1);
	pSlay->SetName(L"Slay_ten");
	pPanel->AddChildUI(pSlay);

	pSlay = new CCount_UI;
	pSlay->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pSlay->SetTextColor(1);
	pSlay->SetName(L"Slay_hun");
	pPanel->AddChildUI(pSlay);


	pSlay = new CCount_UI;
	pSlay->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pSlay->SetTextColor(1);
	pSlay->SetName(L"Slay_chun");
	pPanel->AddChildUI(pSlay);


	// ESC Btn UI
	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"ESC btn");
	pBtnUI->SetScale(Vec2(50.f, 50.f));
	pBtnUI->SetPos(Vec2(140.f, -30.f));
	pBtnUI->SetDelegate(this,(BaseFunc)&CLevel_Start::PasueMenu);
	pPanel->AddChildUI(pBtnUI);


	// 하단 UI
	CPanel_Tex* pPanel2 = new CPanel_Tex;
	pPanel2->SetName(L"Bottom Panel");
	pPanel2->SetTexture(CAssetMgr::Get()->LoadTexture(L"IG_BOT_UI", L"texture\\IG_BottomUI.png"));
	pPanel2->SetPos(Vec2(vResol.x/2.f, 710.f));
	AddObject(pPanel2, LAYER_TYPE::UI);

	// 하단 지닌 무기
	CPanel_Tex* pChildPanel = new CPanel_Tex;
	pChildPanel->SetName(L"crown_weapon");
	pChildPanel->SetTexture(CAssetMgr::Get()->LoadTexture(L"weapon1", L"texture\\crown_weapon.png"));
	pChildPanel->SetPos(Vec2(-172.f, -15.f));
	pPanel2->AddChildUI(pChildPanel);

	// 하단 보유 무기 연동
	CWeapon_UI* pWeaponBot = new CWeapon_UI;
	pWeaponBot->SetTexture(CAssetMgr::Get()->LoadTexture(L"Weapon_Bot", L"texture\\weapon_s_35_20.png"));
	pWeaponBot->SetName(L"Weapon_2");
	pWeaponBot->SetPos(-129.f, -15.f);
	pPanel2->AddChildUI(pWeaponBot);

	pWeaponBot = new CWeapon_UI;
	pWeaponBot->SetTexture(CAssetMgr::Get()->LoadTexture(L"Weapon_Bot", L"texture\\weapon_s_35_20.png"));
	pWeaponBot->SetName(L"Weapon_3");
	pWeaponBot->SetPos(-85.f, -15.f);
	pPanel2->AddChildUI(pWeaponBot);

	pWeaponBot = new CWeapon_UI;
	pWeaponBot->SetTexture(CAssetMgr::Get()->LoadTexture(L"Weapon_Bot", L"texture\\weapon_s_35_20.png"));
	pWeaponBot->SetName(L"Weapon_4");
	pWeaponBot->SetPos(-171.f, 17.f);
	pPanel2->AddChildUI(pWeaponBot);

	pWeaponBot = new CWeapon_UI;
	pWeaponBot->SetTexture(CAssetMgr::Get()->LoadTexture(L"Weapon_Bot", L"texture\\weapon_s_35_20.png"));
	pWeaponBot->SetName(L"Weapon_5");
	pWeaponBot->SetPos(-129.f, 17.f);
	pPanel2->AddChildUI(pWeaponBot);

	pWeaponBot = new CWeapon_UI;
	pWeaponBot->SetTexture(CAssetMgr::Get()->LoadTexture(L"Weapon_Bot", L"texture\\weapon_s_35_20.png"));
	pWeaponBot->SetName(L"Weapon_6");
	pWeaponBot->SetPos(-85.f, 17.f);
	pPanel2->AddChildUI(pWeaponBot);




	// 하단 보유 패시브 표기
	CPassive_UI* pPassiveBot = new CPassive_UI;
	pPassiveBot->SetTexture(CAssetMgr::Get()->LoadTexture(L"Passive_Bot", L"texture\\passive210_25.png"));
	pPassiveBot->SetName(L"Passive_1");
	pPassiveBot->SetPos(85.f, -16.f);
	pPanel2->AddChildUI(pPassiveBot);

	pPassiveBot = new CPassive_UI;
	pPassiveBot->SetTexture(CAssetMgr::Get()->LoadTexture(L"Passive_Bot", L"texture\\passive210_25.png"));
	pPassiveBot->SetName(L"Passive_2");
	pPassiveBot->SetPos(128.f, -16.f);
	pPanel2->AddChildUI(pPassiveBot);

	pPassiveBot = new CPassive_UI;
	pPassiveBot->SetTexture(CAssetMgr::Get()->LoadTexture(L"Passive_Bot", L"texture\\passive210_25.png"));
	pPassiveBot->SetName(L"Passive_3");
	pPassiveBot->SetPos(171.f, -16.f);
	pPanel2->AddChildUI(pPassiveBot);

	pPassiveBot = new CPassive_UI;
	pPassiveBot->SetTexture(CAssetMgr::Get()->LoadTexture(L"Passive_Bot", L"texture\\passive210_25.png"));
	pPassiveBot->SetName(L"Passive_4");
	pPassiveBot->SetPos(85.f, 17.f);
	pPanel2->AddChildUI(pPassiveBot);

	pPassiveBot = new CPassive_UI;
	pPassiveBot->SetTexture(CAssetMgr::Get()->LoadTexture(L"Passive_Bot", L"texture\\passive210_25.png"));
	pPassiveBot->SetName(L"Passive_5");
	pPassiveBot->SetPos(128.f, 17.f);
	pPanel2->AddChildUI(pPassiveBot);

	pPassiveBot = new CPassive_UI;
	pPassiveBot->SetTexture(CAssetMgr::Get()->LoadTexture(L"Passive_Bot", L"texture\\passive210_25.png"));
	pPassiveBot->SetName(L"Passive_6");
	pPassiveBot->SetPos(171.f, 17.f);
	pPanel2->AddChildUI(pPassiveBot);





	// HP BAR
	CPanel_Tex* pHPbar = new CPanel_Tex;
	pHPbar->SetName(L"HP BAR");
	pHPbar->SetPos(Vec2(vResol.x / 2.f+2.f, vResol.y /2.f -40.f));
	pHPbar->SetTexture(CAssetMgr::Get()->LoadTexture(L"HPbar", L"texture\\HPbar.png"));
	AddObject(pHPbar, LAYER_TYPE::UI);

	// HP Gauge
	CHP_bar* pHP = new CHP_bar;
	pHP->SetPos(Vec2(vResol.x / 2.f -27.f, vResol.y / 2.f - 42.f));
	pHP->SetName(L"HPGauge");
	AddObject(pHP, LAYER_TYPE::UI);
	

	// 일시 정지 Dark Filter 추가
	m_DarkFilter = new CDarkUI;
	m_DarkFilter->SetName(L"DarkFilterUI");
	m_DarkFilter->SetTexture(CAssetMgr::Get()->LoadTexture(L"DarkFilter", L"texture\\Dark.png"));
	m_DarkFilter->SetPos(Vec2(vResol.x / 2.f, vResol.y / 2.f));
	AddObject(m_DarkFilter, LAYER_TYPE::UI);


	// Pasue Menu UI
	m_PauseMenu = new CPanel_Tex;
	m_PauseMenu->SetName(L"Pause Menu");
	m_PauseMenu->SetTexture(CAssetMgr::Get()->LoadTexture(L"Pasue Menu", L"texture\\PauseMenu.png"));
	m_PauseMenu->SetPos(Vec2(vResol.x / 2.f, vResol.y /2.f));
	m_PauseMenu->ChangeVisibleState();
	AddObject(m_PauseMenu, LAYER_TYPE::UI);






	// Pasue Menu Btn
	CBtnUI_Tex* pBtn = new CBtnUI_Tex;
	pBtn->SetName(L"ContinueBtn");
	pBtn->SetTexture(CAssetMgr::Get()->LoadTexture(L"Continue Btn", L"texture\\btn_continue.png"));
	pBtn->SetPos(Vec2(-140.f, 235.f));
	pBtn->SetScale(Vec2(100.f, 44.f));
	pBtn->SetCutSizeW(2);
	pBtn->SetChangeWidth(true);
	pBtn->SetDelegate(this, (BaseFunc)&CLevel_Start::PasueMenu);
	m_PauseMenu->AddChildUI(pBtn);

	pBtn = new CBtnUI_Tex;
	pBtn->SetName(L"QuitBtn");
	pBtn->SetTexture(CAssetMgr::Get()->LoadTexture(L"Quit Btn", L"texture\\btn_quit.png"));
	pBtn->SetPos(Vec2(40.f, 235.f));
	pBtn->SetScale(Vec2(100.f, 44.f));
	pBtn->SetCutSizeW(2);
	pBtn->SetChangeWidth(true);
	pBtn->SetDelegate(this, (BaseFunc)&CLevel_Start::QuitGame);
	m_PauseMenu->AddChildUI(pBtn);
	

	CPanel_Anim* pPanelAnim = new CPanel_Anim;
	pPanelAnim->SetName(L"PasuePalyer");
	pPanelAnim->SetPos(Vec2(vResol.x / 2.f - 124.f, vResol.y / 2.f - 205.f));
	m_PauseMenu->AddChildUI(pPanelAnim);

	// Coin CountUI
	CCount_UI* pPauseCoin = new CCount_UI;
	pPauseCoin->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pPauseCoin->SetName(L"Coin_one");
	pPauseCoin->SetStartPos(132.f, -194.f);
	m_PauseMenu->AddChildUI(pPauseCoin);

	pPauseCoin = new CCount_UI;
	pPauseCoin->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pPauseCoin->SetName(L"Coin_ten");
	pPauseCoin->SetStartPos(132.f, -194.f);
	m_PauseMenu->AddChildUI(pPauseCoin);

	pPauseCoin = new CCount_UI;
	pPauseCoin->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pPauseCoin->SetName(L"Coin_hun");
	pPauseCoin->SetStartPos(132.f, -194.f);
	m_PauseMenu->AddChildUI(pPauseCoin);

	pPauseCoin = new CCount_UI;
	pPauseCoin->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pPauseCoin->SetName(L"Coin_chun");
	pPauseCoin->SetStartPos(132.f, -194.f);
	m_PauseMenu->AddChildUI(pPauseCoin);


	// Slay CountUI
	CCount_UI* pPauseSlay = new CCount_UI;
	pPauseSlay->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pPauseSlay->SetName(L"Slay_one");
	pPauseSlay->SetStartPos(70.f, -170.f);
	m_PauseMenu->AddChildUI(pPauseSlay);

	pPauseSlay = new CCount_UI;
	pPauseSlay->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pPauseSlay->SetName(L"Slay_ten");
	pPauseSlay->SetStartPos(70.f, -170.f);
	m_PauseMenu->AddChildUI(pPauseSlay);

	pPauseSlay = new CCount_UI;
	pPauseSlay->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pPauseSlay->SetName(L"Slay_hun");
	pPauseSlay->SetStartPos(70.f, -170.f);
	m_PauseMenu->AddChildUI(pPauseSlay);

	pPauseSlay = new CCount_UI;
	pPauseSlay->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pPauseSlay->SetName(L"Slay_chun");
	pPauseSlay->SetStartPos(70.f, -170.f);
	m_PauseMenu->AddChildUI(pPauseSlay);



	// MaxHP CountUI
	CCount_MaxHP* pMaxUI = new CCount_MaxHP;
	pMaxUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pMaxUI->SetName(L"MaxHP_hun");
	pMaxUI->SetPos(-35.f, -97.f);
	m_PauseMenu->AddChildUI(pMaxUI);

	pMaxUI = new CCount_MaxHP;
	pMaxUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pMaxUI->SetName(L"MaxHP_ten");
	pMaxUI->SetPos(-27.f, -97.f);
	m_PauseMenu->AddChildUI(pMaxUI);

	pMaxUI = new CCount_MaxHP;
	pMaxUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pMaxUI->SetName(L"MaxHP_one");
	pMaxUI->SetPos(-19.f, -97.f);
	m_PauseMenu->AddChildUI(pMaxUI);



	// Atk CountUI
	CCount_Atk* pAtkUI = new CCount_Atk;
	pAtkUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pAtkUI->SetName(L"Atk_one");
	pAtkUI->SetPos(128.f, -97.f);
	m_PauseMenu->AddChildUI(pAtkUI);

	pAtkUI = new CCount_Atk;
	pAtkUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pAtkUI->SetName(L"Atk_ten");
	pAtkUI->SetPos(120.f, -97.f);
	m_PauseMenu->AddChildUI(pAtkUI);


	// Def CountUI
	CCount_Def* pDefUI = new CCount_Def;
	pDefUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pDefUI->SetName(L"Def_one");
	pDefUI->SetPos(53.f, -97.f);
	m_PauseMenu->AddChildUI(pDefUI);

	pDefUI = new CCount_Def;
	pDefUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pDefUI->SetName(L"Def_ten");
	pDefUI->SetPos(45.f, -97.f);
	m_PauseMenu->AddChildUI(pDefUI);


	// Spd CountUI
	CCount_Spd* pSpdUI = new CCount_Spd;
	pSpdUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pSpdUI->SetName(L"Spd_one");
	pSpdUI->SetPos(-95.f, -97.f);
	m_PauseMenu->AddChildUI(pSpdUI);

	pSpdUI = new CCount_Spd;
	pSpdUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pSpdUI->SetName(L"Spd_ten");
	pSpdUI->SetPos(-103.f, -97.f);
	m_PauseMenu->AddChildUI(pSpdUI);

	pSpdUI = new CCount_Spd;
	pSpdUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pSpdUI->SetName(L"Spd_hun");
	pSpdUI->SetPos(-111.f, -97.f);
	m_PauseMenu->AddChildUI(pSpdUI);


	// 무기 이미지 추가 5개 (pause)
	CWeapon_UI* pWeapon = new CWeapon_UI;
	pWeapon->SetTexture(CAssetMgr::Get()->LoadTexture(L"Weapon_pause", L"texture\\weapon_M_80_40.png"));
	pWeapon->SetName(L"Weapon_2");
	pWeapon->SetPos(-2.f,20.f);
	m_PauseMenu->AddChildUI(pWeapon);


	pWeapon = new CWeapon_UI;
	pWeapon->SetTexture(CAssetMgr::Get()->LoadTexture(L"Weapon_pause", L"texture\\weapon_M_80_40.png"));
	pWeapon->SetName(L"Weapon_3");
	pWeapon->SetPos(110.f, 20.f);
	m_PauseMenu->AddChildUI(pWeapon);

	pWeapon = new CWeapon_UI;
	pWeapon->SetTexture(CAssetMgr::Get()->LoadTexture(L"Weapon_pause", L"texture\\weapon_M_80_40.png"));
	pWeapon->SetName(L"Weapon_4");
	pWeapon->SetPos(-118.f, 84.f);
	m_PauseMenu->AddChildUI(pWeapon);

	pWeapon = new CWeapon_UI;
	pWeapon->SetTexture(CAssetMgr::Get()->LoadTexture(L"Weapon_pause", L"texture\\weapon_M_80_40.png"));
	pWeapon->SetName(L"Weapon_5");
	pWeapon->SetPos(-2.f, 84.f);
	m_PauseMenu->AddChildUI(pWeapon);


	pWeapon = new CWeapon_UI;
	pWeapon->SetTexture(CAssetMgr::Get()->LoadTexture(L"Weapon_pause", L"texture\\weapon_M_80_40.png"));
	pWeapon->SetName(L"Weapon_6");
	pWeapon->SetPos(110.f, 84.f);
	m_PauseMenu->AddChildUI(pWeapon);


	// 패시브 이미지 추가. 6개
	CPassive_UI* pPassive = new CPassive_UI;
	pPassive->SetTexture(CAssetMgr::Get()->LoadTexture(L"Passive_pause", L"texture\\448_64_Passive.png"));
	pPassive->SetName(L"Passive_1");
	pPassive->SetPos(-146.f, 185.f);
	m_PauseMenu->AddChildUI(pPassive);

	pPassive = new CPassive_UI;
	pPassive->SetTexture(CAssetMgr::Get()->LoadTexture(L"Passive_pause", L"texture\\448_64_Passive.png"));
	pPassive->SetName(L"Passive_2");
	pPassive->SetPos(-88.f, 185.f);
	m_PauseMenu->AddChildUI(pPassive);

	pPassive = new CPassive_UI;
	pPassive->SetTexture(CAssetMgr::Get()->LoadTexture(L"Passive_pause", L"texture\\448_64_Passive.png"));
	pPassive->SetName(L"Passive_3");
	pPassive->SetPos(-30.f, 185.f);
	m_PauseMenu->AddChildUI(pPassive);

	pPassive = new CPassive_UI;
	pPassive->SetTexture(CAssetMgr::Get()->LoadTexture(L"Passive_pause", L"texture\\448_64_Passive.png"));
	pPassive->SetName(L"Passive_4");
	pPassive->SetPos(28.f, 185.f);
	m_PauseMenu->AddChildUI(pPassive);

	pPassive = new CPassive_UI;
	pPassive->SetTexture(CAssetMgr::Get()->LoadTexture(L"Passive_pause", L"texture\\448_64_Passive.png"));
	pPassive->SetName(L"Passive_5");
	pPassive->SetPos(86.f, 185.f);
	m_PauseMenu->AddChildUI(pPassive);

	pPassive = new CPassive_UI;
	pPassive->SetTexture(CAssetMgr::Get()->LoadTexture(L"Passive_pause", L"texture\\448_64_Passive.png"));
	pPassive->SetName(L"Passive_6");
	pPassive->SetPos(144.f, 185.f);
	m_PauseMenu->AddChildUI(pPassive);




	// 결과 창 UI
	m_ResultMenu = new CPanel_Tex;
	m_ResultMenu->SetName(L"ResultUI");
	m_ResultMenu->SetTexture(CAssetMgr::Get()->LoadTexture(L"Result UI", L"texture\\clearfail.png"));
	m_ResultMenu->SetCutSize(2);
	m_ResultMenu->SetPos(Vec2(vResol.x / 2, vResol.y / 2 + 20));
	m_ResultMenu->SetVisibleState(false);
	AddObject(m_ResultMenu, LAYER_TYPE::UI);


	// 결과창 확인 버튼
	CBtnUI_Tex* pLoby = new CBtnUI_Tex;
	pLoby->SetName(L"ReRoll");
	pLoby->SetTexture(CAssetMgr::Get()->LoadTexture(L"Lobby button", L"texture\\okButton.png"));
	pLoby->SetPos(Vec2(-50.f, 145.f));
	pLoby->SetScale(Vec2(100.f, 44.f));
	pLoby->SetCutSizeW(2);
	pLoby->SetChangeWidth(true);
	pLoby->SetDelegate(this, (BaseFunc)&CLevel_Start::ReStartLobby);
	m_ResultMenu->AddChildUI(pLoby);


	// 결과창 Animation
	CPanel_Anim* pResultAnim = new CPanel_Anim;
	pResultAnim->SetName(L"ResultPlayer");
	pResultAnim->SetPos(Vec2(vResol.x/2 - 114.f, vResol.y / 2.f +74.f));
	
	m_ResultMenu->AddChildUI(pResultAnim);



	// Coin Count Result
	CCount_UI* pResultCoin = new CCount_UI;
	pResultCoin->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pResultCoin->SetName(L"Coin_one");
	pResultCoin->SetStartPos(126.f, 53.f);
	m_ResultMenu->AddChildUI(pResultCoin);


	pResultCoin = new CCount_UI;
	pResultCoin->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pResultCoin->SetName(L"Coin_ten");
	pResultCoin->SetStartPos(126.f, 53.f);
	m_ResultMenu->AddChildUI(pResultCoin);

	pResultCoin = new CCount_UI;
	pResultCoin->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pResultCoin->SetName(L"Coin_hun");
	pResultCoin->SetStartPos(126.f, 53.f);
	m_ResultMenu->AddChildUI(pResultCoin);


	pResultCoin = new CCount_UI;
	pResultCoin->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pResultCoin->SetName(L"Coin_chun");
	pResultCoin->SetStartPos(126.f, 53.f);
	m_ResultMenu->AddChildUI(pResultCoin);


	// Slay Count Result
	CCount_UI* pResultSlay = new CCount_UI;
	pResultSlay->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pResultSlay->SetName(L"Slay_one");
	pResultSlay->SetStartPos(64.f, 79.f);
	m_ResultMenu->AddChildUI(pResultSlay);


	pResultSlay = new CCount_UI;
	pResultSlay->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pResultSlay->SetName(L"Slay_ten");
	pResultSlay->SetStartPos(64.f, 79.f);
	m_ResultMenu->AddChildUI(pResultSlay);

	pResultSlay = new CCount_UI;
	pResultSlay->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pResultSlay->SetName(L"Slay_hun");
	pResultSlay->SetStartPos(64.f, 79.f);
	m_ResultMenu->AddChildUI(pResultSlay);

	pResultSlay = new CCount_UI;
	pResultSlay->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pResultSlay->SetName(L"Slay_chun");
	pResultSlay->SetStartPos(64.f, 79.f);
	m_ResultMenu->AddChildUI(pResultSlay);



	// 스킬업 메인 뒷UI
	m_SkillMenu = new CPanel_Tex;
	m_SkillMenu->SetName(L"SkillBG");
	m_SkillMenu->SetTexture(CAssetMgr::Get()->LoadTexture(L"SkillBG", L"texture\\skillup_bg.png"));
	m_SkillMenu->SetPos(640.f, 344.f);
	m_SkillMenu->ChangeVisibleState();
	AddObject(m_SkillMenu, LAYER_TYPE::UI);


	// 스킬업 버튼
	CBtnUI_Tex* pChooseSkill = new CBtnUI_Tex;
	pChooseSkill->SetName(L"Skill_1");
	pChooseSkill->SetTexture(CAssetMgr::Get()->LoadTexture(L"Skill_Slot", L"texture\\skill_complete.png"));
	pChooseSkill->SetPos(-220.f, -110.f);
	pChooseSkill->SetScale(Vec2(140.f, 220.f));
	pChooseSkill->SetCutSizeH(12);
	pChooseSkill->SetCutSizeW(6);
	pChooseSkill->SetDelegate(this, (BaseFunc)&CLevel_Start::LevelUP_1);
	m_SkillMenu->AddChildUI(pChooseSkill);

	pChooseSkill = new CBtnUI_Tex;
	pChooseSkill->SetName(L"Skill_2");
	pChooseSkill->SetTexture(CAssetMgr::Get()->LoadTexture(L"Skill_Slot", L"texture\\skill_complete.png"));
	pChooseSkill->SetPos(-60, -110.f);
	pChooseSkill->SetScale(Vec2(140.f, 220.f));
	pChooseSkill->SetCutSizeH(12);
	pChooseSkill->SetCutSizeW(6);
	pChooseSkill->SetDelegate(this, (BaseFunc)&CLevel_Start::LevelUP_2);
	m_SkillMenu->AddChildUI(pChooseSkill);

	pChooseSkill = new CBtnUI_Tex;
	pChooseSkill->SetName(L"Skill_3");
	pChooseSkill->SetTexture(CAssetMgr::Get()->LoadTexture(L"Skill_Slot", L"texture\\skill_complete.png"));
	pChooseSkill->SetPos(100.f, -110.f);
	pChooseSkill->SetScale(Vec2(140.f, 220.f));
	pChooseSkill->SetCutSizeH(12);
	pChooseSkill->SetCutSizeW(6);
	pChooseSkill->SetDelegate(this, (BaseFunc)&CLevel_Start::LevelUP_3);
	m_SkillMenu->AddChildUI(pChooseSkill);
	
	// 스킬 버튼 숫자UI
	CCount_Skill* pSkillnumUI = new CCount_Skill;
	pSkillnumUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pSkillnumUI->SetName(L"first");
	pSkillnumUI->SetPos(-150.f, 98.f);
	m_SkillMenu->AddChildUI(pSkillnumUI);

	pSkillnumUI = new CCount_Skill;
	pSkillnumUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pSkillnumUI->SetName(L"Second");
	pSkillnumUI->SetPos(10.f, 98.f);
	pSkillnumUI->SetStartWidth(2);
	m_SkillMenu->AddChildUI(pSkillnumUI);

	pSkillnumUI = new CCount_Skill;
	pSkillnumUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"Count_num", L"texture\\Num_s_8_10.png"));
	pSkillnumUI->SetName(L"third");
	pSkillnumUI->SetPos(170.f, 98.f);
	pSkillnumUI->SetStartWidth(3);
	m_SkillMenu->AddChildUI(pSkillnumUI);

	// 리롤 버튼
	CBtnUI_Tex* pReRollBtn = new CBtnUI_Tex;
	pReRollBtn->SetName(L"ReRoll");
	pReRollBtn->SetTexture(CAssetMgr::Get()->LoadTexture(L"Reroll Btn", L"texture\\Reroll.png"));
	pReRollBtn->SetPos(Vec2(-40.f, 120.f));
	pReRollBtn->SetScale(Vec2(100.f, 44.f));
	pReRollBtn->SetCutSizeW(2);
	pReRollBtn->SetChangeWidth(true);
	pReRollBtn->SetDelegate(this, (BaseFunc)&CLevel_Start::ReRoll);
	m_SkillMenu->AddChildUI(pReRollBtn);


	



	CCamera::Get()->Init();
	// 충돌 지정

	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER_PROJECTILE, (UINT)LAYER_TYPE::ENEMY, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER_PROJECTILE, (UINT)LAYER_TYPE::ENEMY_PROJECTILE, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::ENEMY, (UINT)LAYER_TYPE::ENEMY, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER, (UINT)LAYER_TYPE::ENEMY_PROJECTILE, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER, (UINT)LAYER_TYPE::ENEMY, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::CAMERA, (UINT)LAYER_TYPE::TILE, true);

}

void CLevel_Start::Exit()
{
	// 모든 오브젝트를 삭제해둔다.
	DeleteAllObjects();
}



void CLevel_Start::PasueMenu()
{
	if (!m_SkillMenu->GetVisible())
	{
		if (!m_ResultMenu->GetVisible())

		{
			CPauseMgr::Get()->ChangePauseState();
			m_PauseMenu->ChangeVisibleState();
			m_DarkFilter->ChangeVisibleState();
		}
	}
}

void CLevel_Start::QuitGame()
{
	PostQuitMessage(0);

}





void CLevel_Start::VisibleSkill_BG(const tPlayerInfo& _Info, bool _Reroll)
{
	srand((UINT)time(nullptr)+m_Seed);
	if (!_Reroll)
	{
		m_SkillMenu->ChangeVisibleState();
		m_DarkFilter->ChangeVisibleState();
		
	}
	
	// 여기다가 인포 받아왔으니까 랜덤성으로 해서 텍스쳐 띄우는거 바꿔야될거같음.

	//  랜덤 -> 총 12가지 종류중에 어느것을 선택할지 총 세번 뽑아야된다. 중복 방지 적용

	int rand_second[3] = {};

	vector<int> numbers;
	for (int i = 0; i < 12; ++i) {
		numbers.push_back(i);
	}

	// 난수 생성기 초기화
	std::random_device rd;
	std::mt19937 g(rd());

	// 벡터를 무작위로 섞음
	std::shuffle(numbers.begin(), numbers.end(), g);

	// 앞에서부터 3개의 숫자를 선택
	vector<int> selected_numbers(numbers.begin(), numbers.begin() + 3);

	for (int i = 0; i < 3; ++i)
	{
		rand_second[i] = selected_numbers[i];
	}



	// 선택한 무기와 받아온 Info를 비교해서 StartWidth과 StartHeigth 정함.
 	for (int i = 0; i < 3; ++i)
	{
		CPlayer* player = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
		CBtnUI_Tex* UpBtn = dynamic_cast<CBtnUI_Tex*>(m_SkillMenu->GetChildUI()[i]);
		UpBtn->SetStartHeight(rand_second[i]);
		if (rand_second[i] > 5)
		{
			m_IsWeapon[i] = true;
			m_ChooseWeapon[i] = rand_second[i] - 6;
			int weaponLevel = player->GetWeaponLevel((PlayerWeapon)(rand_second[i]-6));

			if (weaponLevel == 6)
			{
				UpBtn->SetStartWidth(0);
			}
			else
			{
				UpBtn->SetStartWidth(weaponLevel);
			}
		
		}
		else
		{
			m_IsWeapon[i] = false;
			m_ChoosePassive[i] = rand_second[i];
			int passiveLevel = player->GetPassiveLevel((PlayerPassive)rand_second[i]);

			if (passiveLevel == 6)
			{
				UpBtn->SetStartWidth(0);
			}
			else
			{
				UpBtn->SetStartWidth(passiveLevel);
			}
			
		}

	}


}

void CLevel_Start::ReStartLobby()
{

	ChangeLevel(LEVEL_TYPE::EIDTOR);
	CCamera::Get()->SetFilterEffect(FADE_IN, 0.3f);

}




void CLevel_Start::ReRoll()
{

		
	int Reroll_check = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->Reroll_Buy();

	if (Reroll_check == 1)
	{
		m_Seed += 35;
		CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Reroll", L"sound\\Reroll.wav");
		pBGM->Play();
		pBGM->SetVolume(40.f);
		VisibleSkill_BG(CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo(), true);
	}
	else
	{
		CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Reroll_fail", L"sound\\RerollFail.wav");
		pBGM->Play();
		pBGM->SetVolume(30.f);
	}
	


}


void CLevel_Start::Tick()
{
	CLevel::Tick();


	if (!m_SkillMenu->GetVisible())
	{

	
		if (KEY_TAP(KEY::ESCAPE))
		{
			LOG(LOG_LEVEL::LOG, L"Pressed Esc");

			if (!m_ResultMenu->GetVisible())
			{
				CPauseMgr::Get()->ChangePauseState();
				m_PauseMenu->ChangeVisibleState();
				m_DarkFilter->ChangeVisibleState();
				
			}

		}
	}
	else
	{
		if (KEY_TAP(KEY::KEY1) || KEY_TAP(KEY::NUM_1))
		{
			LOG(LOG_LEVEL::LOG, L"1번 누름");
			LevelUP_1();

			
		}

		if (KEY_TAP(KEY::KEY2) || KEY_TAP(KEY::NUM_2))
		{
			LOG(LOG_LEVEL::LOG, L"2번 누름");
			LevelUP_2();

		}

		if (KEY_TAP(KEY::KEY3) || KEY_TAP(KEY::NUM_3))
		{
			LOG(LOG_LEVEL::LOG, L"3번 누름");
			LevelUP_3();

		}

		if (KEY_TAP(KEY::SPACE))
		{
			ReRoll();
		}
	}

	


}




void CLevel_Start::LevelUP_1()
{

	m_SkillMenu->ChangeVisibleState();
	m_DarkFilter->ChangeVisibleState();
	CPauseMgr::Get()->ChangePauseState();

	if (m_IsWeapon[0] == false)
		CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GainPassive((PlayerPassive)m_ChoosePassive[0]);
	else
		CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GainWeapon((PlayerWeapon)m_ChooseWeapon[0]);

}

void CLevel_Start::LevelUP_2()
{
	m_SkillMenu->ChangeVisibleState();
	m_DarkFilter->ChangeVisibleState();
	CPauseMgr::Get()->ChangePauseState();
	if (m_IsWeapon[1] == false)
		CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GainPassive((PlayerPassive)m_ChoosePassive[1]);
	else
		CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GainWeapon((PlayerWeapon)m_ChooseWeapon[1]);
}



void CLevel_Start::LevelUP_3()
{
	m_SkillMenu->ChangeVisibleState();
	m_DarkFilter->ChangeVisibleState();
	CPauseMgr::Get()->ChangePauseState();
	if (m_IsWeapon[2] == false)
		CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GainPassive((PlayerPassive)m_ChoosePassive[2]);
	else
		CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GainWeapon((PlayerWeapon)m_ChooseWeapon[2]);
}