#include "stdafx.h"

#include "MapInfo_Types.h"
#include "..\formats\FmtTerrain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//RMGC - random map generator constants
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int RMGC_INVALID_LINK_ID_VALUE = 0;		//0
const int RMGC_INVALID_SCRIPT_ID_VALUE = -1;	//0
const int RMGC_DEFAULT_SCRIPT_ID_VALUE = 0;	//0
const int RMGC_INVALID_FRAME_INDEX_VALUE = -1;

const char *RMGC_TEMPLATES_XML_NAME = "Templates";
const char *RMGC_TEMPLATES_FILE_NAME = "editor\\templates";

const char *RMGC_MINIMAP_XML_NAME = "MiniMapCreationParameters";
const char *RMGC_MINIMAP_FILE_NAME = "minimap";

const char *RMGC_TILESET_FILE_NAME = "tileset";
const char *RMGC_CROSSSET_FILE_NAME = "crosset";
const char *RMGC_ROADSET_FILE_NAME = "roadset";
const char *RMGC_NOISE_FILE_NAME = "noise";

const char *RMGC_QUICK_LOAD_MAP_INFO_NAME = "QuickLoadMapInfo";
const int RMGC_QUICK_LOAD_MAP_INFO_CHUNK_NUMBER = 2;

const char *RMGC_DEFAULT_ANGLE_MASK = "NESW";

const int RMGC_CREATE_RANDOM_MAP_STEP_COUNT = 19;
const int RMGC_CREATE_MINIMAP_IMAGE_STEP_COUNT = 10;

//////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
const int CMapInfo::REAL_SEASONS[CMapInfo::SEASON_COUNT] = { 0, 1, 2, 0 };
const int CMapInfo::MOST_COMMON_TILES[CMapInfo::SEASON_COUNT] = { 3, 9, 12, 2 }; 

const int CMapInfo::REAL_SEASONS_COUNT = 3;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* CMapInfo::SEASON_NAMES[CMapInfo::SEASON_COUNT] =
{
	"Summer",
	"Winter",
	"Africa",	
	"Spring",
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* CMapInfo::SEASON_FOLDERS[CMapInfo::SEASON_COUNT] =
{
	"terrain\\sets\\1\\",
	"terrain\\sets\\2\\",
	"terrain\\sets\\3\\",
	"terrain\\sets\\4\\",
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const DWORD CMapInfo::SOUND_TYPE_BITS_RIVERS		= 1;
const DWORD CMapInfo::SOUND_TYPE_BITS_BUILDINGS	= 2;
const DWORD CMapInfo::SOUND_TYPE_BITS_FORESTS		= 4;
const DWORD CMapInfo::SOUND_TYPE_BITS_ALL				= 0xFFffFFff;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* CMapInfo::TYPE_NAMES[CMapInfo::TYPE_COUNT] =
{
	"Single Player",
	"Flag Control",
	"Assault",
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//obsolete
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//HORIZONTAL: 1-8-5
//       0
//    1     7
// 2     8     6
//    3     5
//       4
//
//VERTICAL: 16-17-12
//			 9
//	  10	  16
// 11		 17		 15  			
//    12    14
//       13 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
const DWORD CMapInfo::ROAD_BITS_NULL_VALUE = 0x0L;
const DWORD CMapInfo::ROAD_BITS[32] = 
{
	//����������� �����
	0x1UL,				//0
	0x2UL,				//1
	0x4UL,				//2
	0x8UL,				//3
	0x10UL,				//4
	0x20UL,				//5
	0x40UL,				//6
	0x80UL,				//7
	0x100UL,			//8
	0x200UL,			//9
	0x400UL,			//10
	0x800UL,			//11
	0x1000UL,			//12
	0x2000UL,			//13
	0x4000UL,			//14
	0x8000UL,			//15
	0x10000UL,		//16
	0x20000UL,		//17

	//���������� �����
	0x40000UL,		//18
	0x80000UL,		//19
	0x100000UL,		//20
	0x200000UL,		//21
	0x400000UL,		//22
	0x800000UL,		//23
	0x1000000UL,	//24
	0x2000000UL,	//25
	0x4000000UL,	//26
	0x8000000UL,	//27
	0x10000000UL,	//28
	0x20000000UL,	//29
	0x40000000UL,	//30
	0x80000000UL,	//31
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const DWORD CMapInfo::ROAD_CROSS_TILE_INDICES[31] = 
{
	// cross
	SRoadDesc::RDTT_CROSS_CENTER,							//0
	// T-junction
	SRoadDesc::RDTT_LEFT_T_JUNCTION_CENTER,		//1
	SRoadDesc::RDTT_RIGHT_T_JUNCTION_CENTER,	//2
	SRoadDesc::RDTT_UP_T_JUNCTION_CENTER,			//3
	SRoadDesc::RDTT_DOWN_T_JUNCTION_CENTER,		//4
	// center tiles
	SRoadDesc::RDTT_RIGHT_CENTER_CENTER,			//5
	SRoadDesc::RDTT_UP_CENTER_CENTER,					//6
	// cross
	SRoadDesc::RDTT_LEFT_CROSS_BORDER,				//7
	SRoadDesc::RDTT_RIGHT_CROSS_BORDER,				//8
	SRoadDesc::RDTT_UP_CROSS_BORDER,					//9
	SRoadDesc::RDTT_DOWN_CROSS_BORDER,				//10
	// center tiles
	SRoadDesc::RDTT_RIGHT_CENTER_FAR,					//11
	SRoadDesc::RDTT_RIGHT_CENTER_NEAR,				//12
	SRoadDesc::RDTT_UP_CENTER_FAR,						//13
	SRoadDesc::RDTT_UP_CENTER_NEAR,						//14
	// bend
	SRoadDesc::RDTT_LEFT_BEND_CENTER,					//15
	SRoadDesc::RDTT_RIGHT_BEND_CENTER,				//16
	SRoadDesc::RDTT_UP_BEND_CENTER,						//17
	SRoadDesc::RDTT_DOWN_BEND_CENTER,					//18
	// end
	SRoadDesc::RDTT_LEFT_END_CENTER,					//19
	SRoadDesc::RDTT_RIGHT_END_CENTER,					//20
	SRoadDesc::RDTT_UP_END_CENTER,						//21
	SRoadDesc::RDTT_DOWN_END_CENTER,					//22
	SRoadDesc::RDTT_LEFT_END_FAR,							//23
	SRoadDesc::RDTT_LEFT_END_NEAR,						//24
	SRoadDesc::RDTT_RIGHT_END_FAR,						//25
	SRoadDesc::RDTT_RIGHT_END_NEAR,						//26
	SRoadDesc::RDTT_UP_END_FAR,								//27
	SRoadDesc::RDTT_UP_END_NEAR,							//28
	SRoadDesc::RDTT_DOWN_END_FAR,							//29
	SRoadDesc::RDTT_DOWN_END_NEAR,						//30
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const DWORD CMapInfo::ROAD_EDGE_MAP_CROSS_TILE_INDICES[31] =
{
	// cross
	SRoadDesc::RDTT_CROSS_CENTER,							//0
	// T-junction
	SRoadDesc::RDTT_LEFT_T_JUNCTION_CENTER,		//1
	SRoadDesc::RDTT_RIGHT_T_JUNCTION_CENTER,	//2
	SRoadDesc::RDTT_UP_T_JUNCTION_CENTER,			//3
	SRoadDesc::RDTT_DOWN_T_JUNCTION_CENTER,		//4
	// center tiles
	SRoadDesc::RDTT_RIGHT_CENTER_CENTER,			//5
	SRoadDesc::RDTT_UP_CENTER_CENTER,					//6
	// cross
	SRoadDesc::RDTT_LEFT_CROSS_BORDER,				//7
	SRoadDesc::RDTT_RIGHT_CROSS_BORDER,				//8
	SRoadDesc::RDTT_UP_CROSS_BORDER,					//9
	SRoadDesc::RDTT_DOWN_CROSS_BORDER,				//10
	// center tiles
	SRoadDesc::RDTT_RIGHT_CENTER_FAR,					//11
	SRoadDesc::RDTT_RIGHT_CENTER_NEAR,				//12
	SRoadDesc::RDTT_UP_CENTER_FAR,						//13
	SRoadDesc::RDTT_UP_CENTER_NEAR,						//14
	// bend
	SRoadDesc::RDTT_LEFT_BEND_CENTER,					//15
	SRoadDesc::RDTT_RIGHT_BEND_CENTER,				//16
	SRoadDesc::RDTT_UP_BEND_CENTER,						//17
	SRoadDesc::RDTT_DOWN_BEND_CENTER,					//18
	// end
	SRoadDesc::RDTT_RIGHT_CENTER_CENTER,			//SRoadDesc::RDTT_LEFT_END_CENTER,					//19
	SRoadDesc::RDTT_RIGHT_CENTER_CENTER,			//SRoadDesc::RDTT_RIGHT_END_CENTER,					//20
	SRoadDesc::RDTT_UP_CENTER_CENTER,					//SRoadDesc::RDTT_UP_END_CENTER,						//21
	SRoadDesc::RDTT_UP_CENTER_CENTER,					//SRoadDesc::RDTT_DOWN_END_CENTER,					//22
	SRoadDesc::RDTT_RIGHT_CENTER_FAR,					//SRoadDesc::RDTT_LEFT_END_FAR,							//23
	SRoadDesc::RDTT_RIGHT_CENTER_NEAR,				//SRoadDesc::RDTT_LEFT_END_NEAR,						//24
	SRoadDesc::RDTT_RIGHT_CENTER_FAR,					//SRoadDesc::RDTT_RIGHT_END_FAR,						//25
	SRoadDesc::RDTT_RIGHT_CENTER_NEAR,				//SRoadDesc::RDTT_RIGHT_END_NEAR,						//26
	SRoadDesc::RDTT_UP_CENTER_FAR,						//SRoadDesc::RDTT_UP_END_FAR,								//27
	SRoadDesc::RDTT_UP_CENTER_NEAR,						//SRoadDesc::RDTT_UP_END_NEAR,							//28
	SRoadDesc::RDTT_UP_CENTER_FAR,						//SRoadDesc::RDTT_DOWN_END_FAR,							//29
	SRoadDesc::RDTT_UP_CENTER_NEAR,						//SRoadDesc::RDTT_DOWN_END_NEAR,						//30
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const DWORD CMapInfo::ROAD_CROSS_BITS[31][11] = 
{
	// cross
	//0, SRoadDesc::RDTT_CROSS_CENTER
	{
		ROAD_BITS[8] + ROAD_BITS[17],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	// T-junction
	//1, SRoadDesc::RDTT_LEFT_T_JUNCTION_CENTER,
	{
		ROAD_BITS[8] + ROAD_BITS[12],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//2, SRoadDesc::RDTT_RIGHT_T_JUNCTION_CENTER,
	{
		ROAD_BITS[8] + ROAD_BITS[16],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//3, SRoadDesc::RDTT_UP_T_JUNCTION_CENTER,
	{
		ROAD_BITS[2] + ROAD_BITS[17],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//4, SRoadDesc::RDTT_DOWN_T_JUNCTION_CENTER,
	{
		ROAD_BITS[5] + ROAD_BITS[17],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	// center tiles
	//5, SRoadDesc::RDTT_RIGHT_CENTER_CENTER,
	{
		ROAD_BITS[0] + ROAD_BITS[17],
		ROAD_BITS[7] + ROAD_BITS[17],
		ROAD_BITS[6] + ROAD_BITS[17],
		ROAD_BITS[2] + ROAD_BITS[17],
		ROAD_BITS[3] + ROAD_BITS[17],
		ROAD_BITS[4] + ROAD_BITS[17],
		ROAD_BITS[3] + ROAD_BITS[16],
		ROAD_BITS[7] + ROAD_BITS[12],
		ROAD_BITS[17],
		ROAD_BITS[12] + ROAD_BITS[16],
		ROAD_BITS[10] + ROAD_BITS[14],
	},
	//6, SRoadDesc::RDTT_UP_CENTER_CENTER,
	{
		ROAD_BITS[8] + ROAD_BITS[9],
		ROAD_BITS[8] + ROAD_BITS[10],
		ROAD_BITS[8] + ROAD_BITS[11],
		ROAD_BITS[8] + ROAD_BITS[13],
		ROAD_BITS[8] + ROAD_BITS[14],
		ROAD_BITS[8] + ROAD_BITS[15],
		ROAD_BITS[1] + ROAD_BITS[14],
		ROAD_BITS[5] + ROAD_BITS[10],
		ROAD_BITS[8],
		ROAD_BITS[1] + ROAD_BITS[5],
		ROAD_BITS[3] + ROAD_BITS[7],
	},
	// cross
	//7, SRoadDesc::RDTT_LEFT_CROSS_BORDER,
	{
		ROAD_BITS[3] + ROAD_BITS[10],
		ROAD_BITS[4] + ROAD_BITS[10],
		ROAD_BITS[3] + ROAD_BITS[9],
		ROAD_BITS[2] + ROAD_BITS[9],
		ROAD_BITS[4] + ROAD_BITS[11],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//8, SRoadDesc::RDTT_RIGHT_CROSS_BORDER,
	{
		ROAD_BITS[7] + ROAD_BITS[14],
		ROAD_BITS[0] + ROAD_BITS[14],
		ROAD_BITS[7] + ROAD_BITS[13],
		ROAD_BITS[6] + ROAD_BITS[13],
		ROAD_BITS[0] + ROAD_BITS[15],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//9, 	SRoadDesc::RDTT_UP_CROSS_BORDER,
	{
		ROAD_BITS[7] + ROAD_BITS[10],
		ROAD_BITS[6] + ROAD_BITS[10],
		ROAD_BITS[7] + ROAD_BITS[11],
		ROAD_BITS[6] + ROAD_BITS[9],
		ROAD_BITS[0] + ROAD_BITS[11],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//10, SRoadDesc::RDTT_DOWN_CROSS_BORDER,
	{
		ROAD_BITS[3] + ROAD_BITS[14],
		ROAD_BITS[2] + ROAD_BITS[14],
		ROAD_BITS[3] + ROAD_BITS[15],
		ROAD_BITS[4] + ROAD_BITS[15],
		ROAD_BITS[2] + ROAD_BITS[13],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	// center tiles
	//11, SRoadDesc::RDTT_RIGHT_CENTER_FAR,
	{
		ROAD_BITS[0] + ROAD_BITS[10],
		ROAD_BITS[1] + ROAD_BITS[10],
		ROAD_BITS[2] + ROAD_BITS[10],
		ROAD_BITS[10],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//12, SRoadDesc::RDTT_RIGHT_CENTER_NEAR,
	{
		ROAD_BITS[4] + ROAD_BITS[14],
		ROAD_BITS[5] + ROAD_BITS[14],
		ROAD_BITS[6] + ROAD_BITS[14],
		ROAD_BITS[14],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//13, SRoadDesc::RDTT_UP_CENTER_FAR,
	{
		ROAD_BITS[7] + ROAD_BITS[15],
		ROAD_BITS[7] + ROAD_BITS[16],
		ROAD_BITS[7] + ROAD_BITS[9],
		ROAD_BITS[7],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//14, SRoadDesc::RDTT_UP_CENTER_NEAR,
	{
		ROAD_BITS[3] + ROAD_BITS[11],
		ROAD_BITS[3] + ROAD_BITS[12],
		ROAD_BITS[3] + ROAD_BITS[13],
		ROAD_BITS[3],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//15, SRoadDesc::RDTT_LEFT_BEND_CENTER,
	{
		ROAD_BITS[2] + ROAD_BITS[11],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//16, SRoadDesc::RDTT_RIGHT_BEND_CENTER,
	{
		ROAD_BITS[6] + ROAD_BITS[15],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//17, SRoadDesc::RDTT_UP_BEND_CENTER,
	{
		ROAD_BITS[0] + ROAD_BITS[9],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//18, SRoadDesc::RDTT_DOWN_BEND_CENTER,
	{
		ROAD_BITS[4] + ROAD_BITS[13],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//19, SRoadDesc::RDTT_LEFT_END_CENTER,
	{
		ROAD_BITS[11] + ROAD_BITS[13],
		ROAD_BITS[12],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//20, SRoadDesc::RDTT_RIGHT_END_CENTER,
	{
		ROAD_BITS[9] + ROAD_BITS[15],
		ROAD_BITS[16],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//21, SRoadDesc::RDTT_UP_END_CENTER,
	{
		ROAD_BITS[0] + ROAD_BITS[2],
		ROAD_BITS[1],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//22, SRoadDesc::RDTT_DOWN_END_CENTER,
	{
		ROAD_BITS[4] + ROAD_BITS[6],
		ROAD_BITS[5],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//23, SRoadDesc::RDTT_LEFT_END_FAR,
	{
		ROAD_BITS[11],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//24, SRoadDesc::RDTT_LEFT_END_NEAR,
	{
		ROAD_BITS[13],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//25, SRoadDesc::RDTT_RIGHT_END_FAR,
	{
		ROAD_BITS[9],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//26, SRoadDesc::RDTT_RIGHT_END_NEAR,	
	{
		ROAD_BITS[15],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//27, SRoadDesc::RDTT_UP_END_FAR,
	{
		ROAD_BITS[0],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//28, SRoadDesc::RDTT_UP_END_NEAR,
	{
		ROAD_BITS[2],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//29, SRoadDesc::RDTT_DOWN_END_FAR,
	{
		ROAD_BITS[6],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
	//30, SRoadDesc::RDTT_DOWN_END_NEAR,
	{
		ROAD_BITS[4],
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
		ROAD_BITS_NULL_VALUE,
	},
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const DWORD CMapInfo::ROAD_BITS_DIMENSION = 32;
const DWORD CMapInfo::ROAD_CROSS_BITS_DIMENSION = 31;
const DWORD CMapInfo::ROAD_CROSS_BITS_CASES = 11;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**/