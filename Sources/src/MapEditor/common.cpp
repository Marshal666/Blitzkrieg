#include "StdAfx.h"
//#include "..\GFX\gfx.h"
//#include "..\GFX\GFXHelper.h"
//#include "..\Formats\fmtTerrain.h"
//#include "..\Formats\fmtMap.h"
//#include "..\Terrain\builders.h"

#include "common.h"

/**
void FillTileMaps( int nSizeX, int nSizeY, vector<STileMapsDesc> &tileMaps, bool bGenerateInverse )
{
	//Заполняем массив maps в зависимости от размера текстуры
	int nNumColumn = 0;
	for ( int i=0; i<nSizeY-32; i+=32 )
	{
		CVec2 maps[4];
		STileMapsDesc tileMap;
		
		//Primary maps
		for ( int k=0; k<4; k++ )
		{
			GetPrimaryMaps( k, nNumColumn, false, maps, nSizeX, nSizeY );
			tileMap = STileMapsDesc( maps[0], maps[1], maps[2], maps[3] );
			tileMaps.push_back( tileMap );
			
			if ( bGenerateInverse )
			{
				GetPrimaryMaps( k, nNumColumn, true, maps, nSizeX, nSizeY );
				tileMap = STileMapsDesc( maps[0], maps[1], maps[2], maps[3] );
				tileMaps.push_back( tileMap );
			}
		}
		
		//Secondary maps
		for ( int k=0; k<3; k++ )
		{
			GetSecondaryMaps( k, nNumColumn, false, maps, nSizeX, nSizeY );
			tileMap = STileMapsDesc( maps[0], maps[1], maps[2], maps[3] );
			tileMaps.push_back( tileMap );
			
			if ( bGenerateInverse )
			{
				GetSecondaryMaps( k, nNumColumn, true, maps, nSizeX, nSizeY );
				tileMap = STileMapsDesc( maps[0], maps[1], maps[2], maps[3] );
				tileMaps.push_back( tileMap );
			}
		}

		nNumColumn++;
	}
	
	{
		CVec2 maps[4];
		STileMapsDesc tileMap;
		
		//Primary maps
		for ( int k=0; k<4; k++ )
		{
			GetPrimaryMaps( k, nNumColumn, false, maps, nSizeX, nSizeY );
			tileMap = STileMapsDesc( maps[0], maps[1], maps[2], maps[3] );
			tileMaps.push_back( tileMap );
			
			if ( bGenerateInverse )
			{
				GetPrimaryMaps( k, nNumColumn, true, maps, nSizeX, nSizeY );
				tileMap = STileMapsDesc( maps[0], maps[1], maps[2], maps[3] );
				tileMaps.push_back( tileMap );
			}
		}
	}
}
/**/