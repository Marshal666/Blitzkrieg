#include "StdAfx.h"

#include "..\Scene\Scene.h"
#include "..\Anim\Animation.h"

#include "editor.h"
#include "TreeDockWnd.h"
#include "SpriteCompose.h"
#include "MainFrm.h"
#include "PropView.h"
#include "TreeItem.h"
#include "BridgeTreeItem.h"
#include "BridgeFrm.h"
#include "BridgeView.h"
#include "GameWnd.h"
#include "frames.h"

static const int MIN_OPACITY = 120;
static const int MAX_OPACITY = 255;

static const int LINE_LENGTH = 100;			//����� �����, ������������ ��� ������� ������ ��������
static const int EDGE_LENGTH = 200;			//����� ����� ������
static const int SHOOT_PICTURE_SIZE = 8;


void CBridgeFrame::SetActiveFirePoint( SFirePoint *pFirePoint )
{
	if ( pActiveFirePoint )
	{
		//������������� ���������� �������� fire point � ���������� ���������
		pActiveFirePoint->pSprite->SetOpacity( MIN_OPACITY );
		if ( pActiveFirePoint->pHLine )
			pActiveFirePoint->pHLine->SetOpacity( 0 );
	}
	pActiveFirePoint = pFirePoint;
	if ( !pFirePoint )
		return;
	
	pActiveFirePoint->pSprite->SetOpacity( MAX_OPACITY );
	if ( pActiveFirePoint->pHLine )
		pActiveFirePoint->pHLine->SetOpacity( MAX_OPACITY );
	
	if ( pActiveSpansItem != 0 )
	{
		if ( eActiveSubMode == E_SUB_MOVE || eActiveSubMode == E_SUB_HOR )
			ComputeMaxAndMinPositions( pActiveFirePoint->pSprite->GetPosition() );
		else if ( eActiveSubMode == E_SUB_DIR )
			ComputeFireDirectionLines();
	}
}

void CBridgeFrame::SetFireDirection( float fVal )
{
	NI_ASSERT( pActiveFirePoint != 0 );
	
	pActiveFirePoint->fDirection = fVal;
	ComputeFireDirectionLines();
}

void CBridgeFrame::DeleteFirePoint( CTreeItem *pFire )
{
	for ( CListOfFirePoints::iterator it=firePoints.begin(); it!=firePoints.end(); ++it )
	{
		if ( it->pFirePoint == pFire )
		{
			IScene *pSG = GetSingleton<IScene>();
			pSG->RemoveObject( it->pSprite );
			if ( it->pHLine )
				pSG->RemoveObject( it->pHLine );
			firePoints.erase( it );
			pActiveFirePoint = 0;
			SetChangedFlag( true );
			GFXDraw();
			break;
		}
	}
}

void CBridgeFrame::SelectFirePoint( CTreeItem *pFire )
{
	for ( CListOfFirePoints::iterator it=firePoints.begin(); it!=firePoints.end(); ++it )
	{
		if ( it->pFirePoint == pFire )
		{
//			static_cast
//			it->fDirection = pFire->GetDirection();
			SetActiveFirePoint( &(*it) );
			GFXDraw();
			break;
		}
	}
}

void CBridgeFrame::ComputeFireDirectionLines()
{
	NI_ASSERT( pActiveFirePoint != 0 );
	if ( !pActiveFirePoint->pHLine )
		return;

	IScene *pSG = GetSingleton<IScene>();
	CVec3 vCenter3 = pActiveFirePoint->pHLine->GetPosition();		//��������� ������ �����
	CVec2 vCenter2;
	pSG->GetPos2( &vCenter2, vCenter3 );
	
	float fA;
	fA = ToRadian( pActiveFirePoint->fDirection );

	CVec3 vPos3;
	vPos3.x = vCenter3.x - (float) EDGE_LENGTH * sin( fA );
	vPos3.y = vCenter3.y + (float) EDGE_LENGTH * cos( fA );
	vPos3.z = 0;
	CVec2 vPos2;
	pSG->GetPos2( &vPos2, vPos3 );

	CVec3 vLine1, vLine2;			//�����, ������������ ������� ���������
	vLine1.z = vLine2.z = 0;
	float fTemp = ToRadian( 5.0f );
	vLine1.x = vCenter3.x - (float) (EDGE_LENGTH - 20) * sin( fA - fTemp );
	vLine1.y = vCenter3.y + (float) (EDGE_LENGTH - 20) * cos( fA - fTemp );
	vLine2.x = vCenter3.x - (float) (EDGE_LENGTH - 20) * sin( fA + fTemp );
	vLine2.y = vCenter3.y + (float) (EDGE_LENGTH - 20) * cos( fA + fTemp );
	
	//������ �� ����� ����� v1, v2, ������� 2D ���������� ��� ���������� �����
	{
		CVerticesLock<SGFXTLVertex> vertices( pFireDirectionVertices );
		
		CVec2 v;
		
		//0xffff60e6 == (255, 96, 230) ������� ����
		DWORD dwColor = 0xffffff00;
		vertices[0].Setup( vCenter2.x, vCenter2.y, 1, 1, dwColor, 0xff000000, 0, 0 );
		vertices[1].Setup( vPos2.x, vPos2.y, 1, 1, dwColor, 0xff000000, 0, 0 );
		
		pSG->GetPos2( &v, vLine1 );
		vertices[2].Setup( v.x, v.y, 1, 1, 0xffff0000, 0xff000000, 0, 0 );
		vertices[3].Setup( vPos2.x, vPos2.y, 1, 1, 0xffff0000, 0xff000000, 0, 0 );
		
		pSG->GetPos2( &v, vLine2 );
		vertices[4].Setup( v.x, v.y, 1, 1, 0xffff0000, 0xff000000, 0, 0 );
		vertices[5].Setup( vPos2.x, vPos2.y, 1, 1, 0xffff0000, 0xff000000, 0, 0 );
	}
	
	pActiveFirePoint->pFirePoint->SetDirection( pActiveFirePoint->fDirection );
	pOIDockBar->SetItemProperty( pActiveFirePoint->pFirePoint->GetItemName(), pActiveFirePoint->pFirePoint );
	
	GFXDraw();
}

void CBridgeFrame::AddOrSelectFirePoint( const POINT &point )
{
	CVec2 firePos2;
	firePos2.x = point.x;
	firePos2.y = point.y;
	CVec3 firePos3;
	IScene *pSG = GetSingleton<IScene>();
	pSG->GetPos3( &firePos3, firePos2 );

	objShift = VNULL2;
	zeroShift = VNULL2;

	//���������, ����� fire point � ������ ������������ ��� ����������
	CListOfFirePoints::iterator it=firePoints.begin();
	for ( ; it!=firePoints.end(); ++it )
	{
		CVec3 vPos3 = it->pSprite->GetPosition();
		CVec2 vPos2;
		pSG->GetPos2( &vPos2, vPos3 );

		if ( point.x >= vPos2.x - SHOOT_PICTURE_SIZE && point.x <= vPos2.x + SHOOT_PICTURE_SIZE &&
			point.y >= vPos2.y - SHOOT_PICTURE_SIZE && point.y <= vPos2.y + SHOOT_PICTURE_SIZE )
		{
			//�������� ���� shoot point
			SetActiveFirePoint( &(*it) );
			it->pFirePoint->SelectMeInTheTree();

			//�������� ������������� ���� ���������
			SetChangedFlag( true );
			objShift.x = vPos2.x - point.x;
			objShift.y = vPos2.y - point.y;

			vPos3 = it->pHLine->GetPosition();
			pSG->GetPos2( &vPos2, vPos3 );
			zeroShift.x = vPos2.x - point.x;
			zeroShift.y = vPos2.y - point.y;

			m_mode = E_SET_FIRE_POINT;
			//pTreeDockBar->SetFocus();
			g_frameManager.GetGameWnd()->SetCapture();
			return;
		}
	}
	
	if ( !ComputeMaxAndMinPositions( firePos3 ) )
	{
		//�� ����� ����������� � ����������� �������, �� �������� �����
		return;
	}
	
	//��������� ������ '����� ����' � ������ ������������
	IVisObjBuilder *pVOB = GetSingleton<IVisObjBuilder>();
	CPtr<IObjVisObj> pObject = static_cast<IObjVisObj *> ( pVOB->BuildObject( "editor\\shoot\\1", 0, SGVOT_SPRITE ) );
	NI_ASSERT( pObject != 0 );
	if ( !pObject )
	{
		return;
	}
	
	pObject->SetPosition( firePos3 );
	pObject->SetDirection( 0 );
	pObject->SetAnimation( 0 );
	pSG->AddObject( pObject, SGVOGT_OBJECT );
	pObject->SetOpacity( MAX_OPACITY );
	
	//��������� ����� ���� � ������
	CETreeCtrl *pTree = pTreeDockBar->GetTreeWithIndex( 0 );
	CTreeItem *pRoot = pTree->GetRootItem();
	CTreeItem *pFiresItem = pRoot->GetChildItem( E_BRIDGE_FIRE_POINTS_ITEM );
	CBridgeFirePointPropsItem *pNewPoint = new CBridgeFirePointPropsItem;
	pNewPoint->SetItemName( "Fire point" );
	pFiresItem->AddChild( pNewPoint );
	pNewPoint->SelectMeInTheTree();
	
	SFirePoint fire;
	fire.pFirePoint = pNewPoint;
	fire.pSprite = pObject;
	
	//�������� � ����� fire point ���������� �� �������
	if ( pActiveFirePoint )
	{
		//��������� ����� �������� �� ����������� shoot point
		fire.fDirection = pActiveFirePoint->fDirection;
		fire.pFirePoint->SetDirection( fire.fDirection );
		fire.pFirePoint->SetEffectName( pActiveFirePoint->pFirePoint->GetEffectName() );
	}
	else
	{
		//�������� ����� �������� �� ���������
		fire.fDirection = 0;
		fire.pFirePoint->SetDirection( fire.fDirection );
	}
	
	//����� ����� �����������
	CVec3 vHPos3 = firePos3;
	if ( pActiveFirePoint )
	{
		CVec2 vHPos2, vSprite2;
		pSG->GetPos2( &vHPos2, pActiveFirePoint->pHLine->GetPosition() );
		pSG->GetPos2( &vSprite2, pActiveFirePoint->pSprite->GetPosition() );
		
		CVec2 vNewSpritePos2;
		pSG->GetPos2( &vNewSpritePos2, firePos3 );
		vNewSpritePos2.y += vHPos2.y - vSprite2.y;
		if ( vNewSpritePos2.y < m_fMinY )
			vNewSpritePos2.y = m_fMinY;
		if ( vNewSpritePos2.y > m_fMaxY )
			vNewSpritePos2.y = m_fMaxY;
		pSG->GetPos3( &vHPos3, vNewSpritePos2 );
	}
	else
	{
		CVec2 vPos2;
		pSG->GetPos2( &vPos2, firePos3 );
		vPos2.y = m_fMaxY;
		pSG->GetPos3( &vHPos3, vPos2 );
	}

	//������� ������ - �������������� �����
	pObject = static_cast<IObjVisObj *> ( pVOB->BuildObject( "editor\\shoot_horizontal\\1", 0, SGVOT_SPRITE ) );
	NI_ASSERT( pObject != 0 );
	
	pObject->SetDirection( 0 );
	pObject->SetAnimation( 0 );
	pObject->SetPosition( vHPos3 );
	pSG->AddObject( pObject, SGVOGT_OBJECT );
	pObject->Update( GetSingleton<IGameTimer>()->GetGameTime() );
	pObject->SetOpacity( MAX_OPACITY );
	fire.pHLine = pObject;

	firePoints.push_back( fire );
	SetActiveFirePoint( &(firePoints.back()) );
	pOIDockBar->SetItemProperty( pActiveFirePoint->pFirePoint->GetItemName(), pActiveFirePoint->pFirePoint );
	SetChangedFlag( true );
	GFXDraw();
}

void CBridgeFrame::SetHorFirePoint( const POINT &point )
{
	if ( pActiveFirePoint == 0 )
		return;
	
	const int DELTA_X = 10;
	if ( point.x >= m_fX - DELTA_X && point.x <= m_fX + DELTA_X && point.y >= m_fMinY && point.y <= m_fMaxY )
	{
		CVec2 vPos2;
		vPos2.x = m_fX;
		vPos2.y = point.y;
		CVec3 vPos3;
		IScene *pSG = GetSingleton<IScene>();
		pSG->GetPos3( &vPos3, vPos2 );
		
		NI_ASSERT( pActiveFirePoint->pHLine != 0 );
		if ( pActiveFirePoint->pHLine )
		{
			pActiveFirePoint->pHLine->SetPosition( vPos3 );
			pSG->MoveObject( pActiveFirePoint->pHLine, vPos3 );
			IGameTimer *pTimer = GetSingleton<IGameTimer>();
			pActiveFirePoint->pHLine->Update( pTimer->GetGameTime() );
		}
		SetChangedFlag( true );
		GFXDraw();
	}
}

void CBridgeFrame::SetFirePointAngle( const POINT &point )
{
	if ( pActiveFirePoint == 0 || pActiveFirePoint->pHLine == 0 )
		return;
	IScene *pSG = GetSingleton<IScene>();
	
	CVec3 vCenter3 = pActiveFirePoint->pHLine->GetPosition();		//��������� ������ ������
	CVec2 vCenter2;
	pSG->GetPos2( &vCenter2, vCenter3 );
	float temp = (vCenter2.x - point.x)*(vCenter2.x - point.x) + (vCenter2.y - point.y)*(vCenter2.y - point.y);
	if ( sqrt( temp ) < 5 )
		return;				//���� ����� ��������� ����������, �� ����� ������ �������, �������� �������
	
	CVec2 vPos2;
	vPos2.x = point.x;
	vPos2.y = point.y;
	CVec3 vPos3;
	pSG->GetPos3( &vPos3, vPos2 );
	
	//����������� �� ��������� �� ��������� � �������� �����
	CVec3 vCone;
	vCone.x = vPos3.x - vCenter3.x;
	vCone.y = vPos3.y - vCenter3.y;
	float fA = -atan2( vCone.x, vCone.y );
	fA = ToDegree( fA );
	if ( fA < 0 )
		fA = 360 + fA;
	pActiveFirePoint->fDirection = fA;
	
	SetChangedFlag( true );
	SetCapture();
	ComputeFireDirectionLines();
}

void CBridgeFrame::MoveFirePoint( const POINT &point )
{
	IScene *pSG = GetSingleton<IScene>();
	IGameTimer *pTimer = GetSingleton<IGameTimer>();
	
	CVec2 pos2;
	CVec3 pos3;
	pos2.x = point.x + objShift.x;
	pos2.y = point.y + objShift.y;
	pSG->GetPos3( &pos3, pos2 );
	pSG->MoveObject( pActiveFirePoint->pSprite, pos3 );
	pActiveFirePoint->pSprite->Update( pTimer->GetGameTime() );
	
	pos2.x = point.x + zeroShift.x;
	pos2.y = point.y + zeroShift.y;
	pSG->GetPos3( &pos3, pos2 );
	pSG->MoveObject( pActiveFirePoint->pHLine, pos3 );
	pActiveFirePoint->pHLine->Update( pTimer->GetGameTime() );
	GFXDraw();
}

CTreeItem *CBridgeFrame::GetActiveFirePointItem()
{
	if ( pActiveFirePoint != 0 )
		return pActiveFirePoint->pFirePoint;
	return 0;
}

void CBridgeFrame::GenerateFirePoints()
{
	IScene *pSG = GetSingleton<IScene>();
	IGameTimer *pTimer = GetSingleton<IGameTimer>();

	CETreeCtrl *pTree = pTreeDockBar->GetTreeWithIndex( 0 );
	CTreeItem *pRootItem = pTree->GetRootItem();
	CTreeItem *pFireItems = pRootItem->GetChildItem( E_BRIDGE_FIRE_POINTS_ITEM );
	NI_ASSERT( pFireItems != 0 );
	if ( pFireItems->GetChildsCount() > 0 )
	{
		int nRes = AfxMessageBox( "This action will remove all fire points, do you want to proceed?", MB_YESNO );
		if ( nRes == IDNO )
			return;

		for ( CTreeItem::CTreeItemList::const_iterator it = pFireItems->GetBegin(); it != pFireItems->GetEnd(); ++it )
		{
			DeleteFirePoint( (*it) );
		}

		pFireItems->RemoveAllChilds();
		pActiveFirePoint = 0;
	}
	
	//������ ������ ����������� � ������������ ���������� ������ � pActiveSpansItem->lockedTiles
	NI_ASSERT( !pActiveSpansItem->lockedTiles.empty() );
	int nTileMinX = pActiveSpansItem->lockedTiles.front().nTileX, nTileMaxX = pActiveSpansItem->lockedTiles.front().nTileX;
	int nTileMinY = pActiveSpansItem->lockedTiles.front().nTileY, nTileMaxY = pActiveSpansItem->lockedTiles.front().nTileY;
	CListOfTiles::iterator it=pActiveSpansItem->lockedTiles.begin();
	for ( ++it; it!=pActiveSpansItem->lockedTiles.end(); ++it )
	{
		if ( nTileMinX > it->nTileX )
			nTileMinX = it->nTileX;
		else if ( nTileMaxX < it->nTileX )
			nTileMaxX = it->nTileX;
		
		if ( nTileMinY > it->nTileY )
			nTileMinY = it->nTileY;
		else if ( nTileMaxY < it->nTileY )
			nTileMaxY = it->nTileY;
	}
	
	float fLeftX, fLeftY, fTopX, fTopY, fRightX, fRightY, fBottomX, fBottomY;
	float fX1, fY1, fX2, fY2, fX3, fY3, fX4, fY4;
	GetGameTileCoordinates( nTileMinX, nTileMinY, fX1, fY1, fX2, fY2, fX3, fY3, fX4, fY4 );
	fLeftX = fX2;
	fLeftY = fY2;
	
	GetGameTileCoordinates( nTileMinX, nTileMaxY, fX1, fY1, fX2, fY2, fX3, fY3, fX4, fY4 );
	fTopX = fX1;
	fTopY = fY1;
	
	GetGameTileCoordinates( nTileMaxX, nTileMaxY, fX1, fY1, fX2, fY2, fX3, fY3, fX4, fY4 );
	fRightX = fX4;
	fRightY = fY4;
	
	GetGameTileCoordinates( nTileMaxX, nTileMinY, fX1, fY1, fX2, fY2, fX3, fY3, fX4, fY4 );
	fBottomX = fX3;
	fBottomY = fY3;
	
	POINT v2;
	pTimer->Update( timeGetTime() );
	
	if ( m_bHorizontal )
	{
		//front left
		for ( int i=0; i<(nTileMaxX-nTileMinX+1)/2; i++ )
		{
			v2.x = fLeftX + i * fCellSizeX + fCellSizeX / 4;
			v2.y = fLeftY + i * fCellSizeY + fCellSizeY / 4;
			AddOrSelectFirePoint( v2 );
			
			SetFireDirection( 180 );
		}
		//back right
		for ( int i=0; i<(nTileMaxX-nTileMinX+1)/2; i++ )
		{
			v2.x = fRightX - i * fCellSizeX - fCellSizeX / 4;
			v2.y = fRightY - i * fCellSizeY - fCellSizeY / 4;
			AddOrSelectFirePoint( v2 );
			
			SetFireDirection( 0 );
		}
	}
	else
	{
		//front right
		for ( int i=0; i<(nTileMaxY-nTileMinY+1)/2; i++ )
		{
			v2.x = fBottomX + i * fCellSizeX + fCellSizeX / 4;
			v2.y = fBottomY - i * fCellSizeY - fCellSizeY / 4;
			AddOrSelectFirePoint( v2 );
			
			SetFireDirection( 270 );
		}
		//back left
		for ( int i=0; i<(nTileMaxY-nTileMinY+1)/2; i++ )
		{
			v2.x = fTopX - i * fCellSizeX - fCellSizeX / 4;
			v2.y = fTopY + i * fCellSizeY + fCellSizeY / 4;
			AddOrSelectFirePoint( v2 );
			
			SetFireDirection( 90 );
		}
	}	
	SetChangedFlag( true );
	GFXDraw();
}


