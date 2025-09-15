#pragma once


enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	MAGENTA,
	TURQUOISE,
	WHITE,
	END,
};


enum class BRUSH_TYPE
{
	RED,
	BLUE,
	GREEN,
	GRAY,
	TURQUOISE,
	WHITE,
	HOLLOW,	
	END,
};

enum class LEVEL_TYPE
{
	START,
	STAGE_01,
	STAGE_02,
	STAGE_03,
	EIDTOR,
	END,
};


enum class LAYER_TYPE
{
	DEFAULT,
	BACKGROUND,
	TILE,
	SPAWNER,
	PLATFORM,
	ITEM,
	ENEMY,
	EFFECT_DEAD,
	PLAYER_PROJECTILE,
	PLAYER,
	TAIL,
	ENEMY_PROJECTILE,
	CAMERA,

	UI = 31,
	END = 32,
};


enum class TASK_TYPE
{
	CREATE_OBJECT, // Param0 : Object Adress, Param1 : LayerType
	DELETE_OBJECT, // Param0 : Object Adress
	CHANGE_LEVEL,  // Param0 : LEVEL_TYPE
};


enum class COMPONENT_TYPE
{
	COLLIDER,
	ANIMATOR,
	RIGIDBODY,
	TILEMAP,
	STATE_MACHINE,
	WEAPON
};

enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,
	CROSS,
	LINE,
};

enum class LOG_LEVEL
{
	LOG,
	WARNING,
	BUG,
};

enum class PREV_MOVE
{
	LEFT_UP,
	UP,
	RIGHT_UP,
	LEFT,
	RIGHT,
	LEFT_DOWN,
	DOWN,
	RIGHT_DOWN,
	NONE,

};


enum class PlayerWeapon
{
	CROWN,
	MODERNIA,
	SNOWWHITE,
	LAPUNGEL,
	GREN,
	KILLO,
	NONE,
};

enum class PlayerPassive
{
	ATK,
	DEF,
	SPEED,
	HP,
	MAGNET,
	ALLPOWER,
	NONE,

};

enum class PlayerVoice
{
	HIT,
	BUST,
	CLEAR,
	FAIL,
	RELOAD,
	END,
};