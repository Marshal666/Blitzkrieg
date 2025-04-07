#include "StdAfx.h"
#include "editor.h"
#include "frames.h"
#include "EffectFrm.h"
#include "EffTreeItem.h"
#include "RefDlg.h"

void CEffectTreeRootItem::InitDefaultValues()
{
	defaultValues.clear();
	values = defaultValues;
	
	defaultChilds.clear();
	SChildItem child;
	
	child.nChildItemType = E_EFFECT_COMMON_PROPS_ITEM;
	child.szDefaultName = "Basic Info";
	child.szDisplayName = "Basic Info";
	defaultChilds.push_back( child );
	
	child.nChildItemType = E_EFFECT_ANIMATIONS_ITEM;
	child.szDefaultName = "Animations";
	child.szDisplayName = "Animations";
	defaultChilds.push_back( child );
	
	/*child.nChildItemType = E_EFFECT_MESHES_ITEM;
	child.szDefaultName = "Meshes";
	child.szDisplayName = "Meshes";
	defaultChilds.push_back( child );*/
	
	child.nChildItemType = E_EFFECT_FUNC_PARTICLES_ITEM;
	child.szDefaultName = "Function Particles";
	child.szDisplayName = "Function Particles";
	defaultChilds.push_back( child );
	
	/*child.nChildItemType = E_EFFECT_MAYA_PARTICLES_ITEM;
	child.szDefaultName = "Maya Particles";
	child.szDisplayName = "Maya Particles";
	defaultChilds.push_back( child );
	
	child.nChildItemType = E_EFFECT_LIGHTS_ITEM;
	child.szDefaultName = "Lights";
	child.szDisplayName = "Lights";
	defaultChilds.push_back( child );*/
}

void CEffectCommonPropsItem::InitDefaultValues()
{
	defaultValues.clear();
	SProp prop;
	prop.nId = 1;
	prop.nDomenType = DT_STR;
	prop.szDefaultName = "Name";
	prop.szDisplayName = "Name";
	prop.value = "Unknown effect";
	defaultValues.push_back( prop );
	
	prop.nId = 2;
	prop.nDomenType = DT_SOUND_REF;
	prop.szDefaultName = "Ambient sound";
	prop.szDisplayName = "Sound";
	prop.value = "";
	defaultValues.push_back( prop );
	
	values = defaultValues;
}

void CEffectAnimationsItem::InitDefaultValues()
{
	defaultValues.clear();
	values = defaultValues;
}

void CEffectAnimationsItem::MyKeyDown( int nChar )
{
	switch ( nChar )
	{
		case VK_INSERT:
			DisplayInsertChildDialog();
			break;
	}
}

void CEffectAnimationsItem::MyRButtonClick()
{
	int nRes = g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->DisplayInsertMenu();
	if ( nRes == ID_INSERT_TREE_ITEM )
		DisplayInsertChildDialog();
}

void CEffectAnimationsItem::DisplayInsertChildDialog()
{
	CReferenceDialog refDlg;
	refDlg.Init( E_ANIMATIONS_REF );
	if ( refDlg.DoModal() == IDOK )
	{
		string szAnim = refDlg.GetValue();
		if ( szAnim.size() > 0 )
		{
			CEffectAnimationPropsItem *pAnimProps = new CEffectAnimationPropsItem();
			pAnimProps->SetItemName( szAnim.c_str() );
			AddChild( pAnimProps );
			g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->SetChangedFlag( true );
		}
	}
	
	pTreeCtrl->SetFocus();
}

void CEffectMeshesItem::InitDefaultValues()
{
	defaultValues.clear();
	values = defaultValues;
}

void CEffectMeshesItem::MyKeyDown( int nChar )
{
	switch ( nChar )
	{
		case VK_INSERT:
			DisplayInsertChildDialog();
			break;
	}
}

void CEffectMeshesItem::MyRButtonClick()
{
	int nRes = g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->DisplayInsertMenu();
	if ( nRes == ID_INSERT_TREE_ITEM )
		DisplayInsertChildDialog();
}

void CEffectMeshesItem::DisplayInsertChildDialog()
{
}

void CEffectFuncParticlesItem::InitDefaultValues()
{
	defaultValues.clear();
	values = defaultValues;
}

void CEffectFuncParticlesItem::MyKeyDown( int nChar )
{
	switch ( nChar )
	{
		case VK_INSERT:
			DisplayInsertChildDialog();
			break;
	}
}

void CEffectFuncParticlesItem::MyRButtonClick()
{
	int nRes = g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->DisplayInsertMenu();
	if ( nRes == ID_INSERT_TREE_ITEM )
		DisplayInsertChildDialog();
}

void CEffectFuncParticlesItem::DisplayInsertChildDialog()
{
	CReferenceDialog refDlg;
	refDlg.Init( E_FUNC_PARTICLES_REF );
	if ( refDlg.DoModal() == IDOK )
	{
		string szFunc = refDlg.GetValue();
		if ( szFunc.size() > 0 )
		{
			CEffectFuncPropsItem *pFuncProps = new CEffectFuncPropsItem();
			pFuncProps->SetItemName( szFunc.c_str() );
			AddChild( pFuncProps );
			g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->SetChangedFlag( true );

			CEffectFrame *pFrame = static_cast<CEffectFrame *> ( g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME ) );
			int nLifeTime = pFrame->GetLastParticleEffectLifeTime();
			pFuncProps->SetDuration( nLifeTime );
		}
	}

	pTreeCtrl->SetFocus();
}

void CEffectMayaParticlesItem::InitDefaultValues()
{
	defaultValues.clear();
	values = defaultValues;
}

void CEffectMayaParticlesItem::MyKeyDown( int nChar )
{
	switch ( nChar )
	{
		case VK_INSERT:
			DisplayInsertChildDialog();
			break;
	}
}

void CEffectMayaParticlesItem::MyRButtonClick()
{
	int nRes = g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->DisplayInsertMenu();
	if ( nRes == ID_INSERT_TREE_ITEM )
		DisplayInsertChildDialog();
}

void CEffectMayaParticlesItem::DisplayInsertChildDialog()
{
}

void CEffectLightsItem::InitDefaultValues()
{
	defaultValues.clear();
	values = defaultValues;
}

void CEffectAnimationPropsItem::InitDefaultValues()
{
	defaultValues.clear();
	SProp prop;
	prop.nId = 1;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "Begin time";
	prop.szDisplayName = "Begin time";
	prop.value = 0;
	defaultValues.push_back( prop );

	prop.nId = 3;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "X position";
	prop.szDisplayName = "X position";
	prop.value = 0;
	defaultValues.push_back( prop );

	prop.nId = 4;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "Y position";
	prop.szDisplayName = "Y position";
	prop.value = 0;
	defaultValues.push_back( prop );

	prop.nId = 5;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "Z position";
	prop.szDisplayName = "Z position";
	prop.value = 0;
	defaultValues.push_back( prop );

	prop.nId = 6;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "Repeat Count";
	prop.szDisplayName = "Repeat Count";
	prop.value = 1;
	defaultValues.push_back( prop );

	values = defaultValues;
}

int CEffectAnimationPropsItem::GetBeginTime()
{
	return values[0].value;
}

CVec3 CEffectAnimationPropsItem::GetPosition()
{
	CVec3 pos;
	pos.x = values[1].value;
	pos.y = values[2].value;
	pos.z = values[3].value;
	return pos;
}

int CEffectAnimationPropsItem::GetRepeatCount()
{
	return values[4].value;
}

void CEffectAnimationPropsItem::MyKeyDown( int nChar )
{
	switch ( nChar )
	{
		case VK_DELETE:
			g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->ClearPropView();
			DeleteMeInParentTreeItem();
			g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->SetChangedFlag( true );
			break;
	}
}

void CEffectAnimationPropsItem::MyRButtonClick()
{
	int nRes = g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->DisplayDeleteMenu();
	if ( nRes == ID_MENU_DELETE_TREE_ITEM )
	{
		g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->ClearPropView();
		DeleteMeInParentTreeItem();
		g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->SetChangedFlag( true );
	}
}

void CEffectMeshPropsItem::InitDefaultValues()
{
	defaultValues.clear();
	SProp prop;
	prop.nId = 1;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "Begin time";
	prop.szDisplayName = "Begin time";
	prop.value = 0;
	defaultValues.push_back( prop );
	
	prop.nId = 2;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "Duration";
	prop.szDisplayName = "Duration";
	prop.value = 5000;
	defaultValues.push_back( prop );
	
	prop.nId = 3;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "X position";
	prop.szDisplayName = "X position";
	prop.value = 0;
	defaultValues.push_back( prop );
	
	prop.nId = 4;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "Y position";
	prop.szDisplayName = "Y position";
	prop.value = 0;
	defaultValues.push_back( prop );
	
	prop.nId = 5;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "Z position";
	prop.szDisplayName = "Z position";
	prop.value = 0;
	defaultValues.push_back( prop );

	values = defaultValues;
}

int CEffectMeshPropsItem::GetBeginTime()
{
	return values[0].value;
}

CVec3 CEffectMeshPropsItem::GetPosition()
{
	CVec3 pos;
	pos.x = values[2].value;
	pos.y = values[3].value;
	pos.z = values[4].value;
	return pos;
}

void CEffectMeshPropsItem::MyKeyDown( int nChar )
{
	switch ( nChar )
	{
		case VK_DELETE:
			g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->ClearPropView();
			DeleteMeInParentTreeItem();
			g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->SetChangedFlag( true );
			break;
	}
}

void CEffectMayaPropsItem::InitDefaultValues()
{
	defaultValues.clear();
	SProp prop;
	prop.nId = 1;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "Begin time";
	prop.szDisplayName = "Begin time";
	prop.value = 0;
	defaultValues.push_back( prop );
	
	prop.nId = 2;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "Duration";
	prop.szDisplayName = "Duration";
	prop.value = 5000;
	defaultValues.push_back( prop );
	
	prop.nId = 3;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "X position";
	prop.szDisplayName = "X position";
	prop.value = 0;
	defaultValues.push_back( prop );
	
	prop.nId = 4;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "Y position";
	prop.szDisplayName = "Y position";
	prop.value = 0;
	defaultValues.push_back( prop );
	
	prop.nId = 5;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "Z position";
	prop.szDisplayName = "Z position";
	prop.value = 0;
	defaultValues.push_back( prop );

	values = defaultValues;
}

int CEffectMayaPropsItem::GetBeginTime()
{
	return values[0].value;
}

CVec3 CEffectMayaPropsItem::GetPosition()
{
	CVec3 pos;
	pos.x = values[2].value;
	pos.y = values[3].value;
	pos.z = values[4].value;
	return pos;
}

void CEffectMayaPropsItem::MyKeyDown( int nChar )
{
	switch ( nChar )
	{
		case VK_DELETE:
			g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->ClearPropView();
			DeleteMeInParentTreeItem();
			g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->SetChangedFlag( true );
			break;
	}
}


void CEffectFuncPropsItem::InitDefaultValues()
{
	defaultValues.clear();
	SProp prop;
	prop.nId = 1;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "Begin time";
	prop.szDisplayName = "Begin time";
	prop.value = 0;
	defaultValues.push_back( prop );
	
	prop.nId = 2;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "Duration";
	prop.szDisplayName = "Duration";
	prop.value = 15000;
	defaultValues.push_back( prop );
	
	prop.nId = 3;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "X position";
	prop.szDisplayName = "X position";
	prop.value = 0;
	defaultValues.push_back( prop );
	
	prop.nId = 4;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "Y position";
	prop.szDisplayName = "Y position";
	prop.value = 0;
	defaultValues.push_back( prop );
	
	prop.nId = 5;
	prop.nDomenType = DT_DEC;
	prop.szDefaultName = "Z position";
	prop.szDisplayName = "Z position";
	prop.value = 0;
	defaultValues.push_back( prop );
	
	prop.nId = 6;
	prop.nDomenType = DT_FLOAT;
	prop.szDefaultName = "Scale factor";
	prop.szDisplayName = "Scale factor";
	prop.value = 1.0f;
	defaultValues.push_back( prop );
	
	values = defaultValues;
}

int CEffectFuncPropsItem::GetBeginTime()
{
	return values[0].value;
}

CVec3 CEffectFuncPropsItem::GetPosition()
{
	CVec3 pos;
	pos.x = values[2].value;
	pos.y = values[3].value;
	pos.z = values[4].value;
	return pos;
}

int CEffectFuncPropsItem::GetDuration()
{
	return values[1].value;
}

void CEffectFuncPropsItem::MyKeyDown( int nChar )
{
	switch ( nChar )
	{
		case VK_DELETE:
			g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->ClearPropView();
			DeleteMeInParentTreeItem();
			g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->SetChangedFlag( true );
			break;
	}
}

void CEffectFuncPropsItem::MyRButtonClick()
{
	int nRes = g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->DisplayDeleteMenu();
	if ( nRes == ID_MENU_DELETE_TREE_ITEM )
	{
			g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->ClearPropView();
			DeleteMeInParentTreeItem();
			g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME )->SetChangedFlag( true );
	}
}
