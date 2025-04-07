#include "StdAfx.h"

#include "iMain.h"

#include "..\StreamIO\OptionSystem.h"
#include "..\GFX\GFX.h"
#include "..\GFX\GFXHelper.h"
#include "..\SFX\SFX.h"
#include "..\Input\Input.h"
#include "..\Anim\Animation.h"
#include "..\Scene\Scene.h"
#include "..\Scene\Terrain.h"
#include "..\Scene\PFX.h"
#include "..\AILogic\AILogic.h"
#include "..\AILogic\DifficultyLevel.h"
#include "..\UI\UI.h"
#include "..\Image\Image.h"
#include "..\Formats\fmtTerrain.h"
#include "..\Main\TextSystem.h"
#include "..\UI\MaskSystem.h"
#include "..\Main\Transceiver.h"
#include "..\GameTT\AckManager.h"
#include "..\Main\ScenarioTracker.h"
#include "..\GameTT\MultiplayerCommandManager.h"
#include "..\Common\PauseGame.h"
#include "..\Main\CommandsHistoryInterface.h"
#include "..\GameTT\MessageReaction.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NMain
{
	bool bInitialized = false;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float MakeGammaValue( const variant_t &var ) { return ( float(var) - 50.0f ) / 50.0f; }
bool STDCALL NMain::SwitchGame( bool bOn )
{
	if ( bOn ) 
	{
		if ( NMain::IsInitialized() )
		{
			if ( IMainLoop *pML = GetSingleton<IMainLoop>() )
				pML->Pause( false, PAUSE_TYPE_INACTIVE );
			// set game's gamma correction
			variant_t vtBrightness = 0.0f, vtContrast = 0.0f, vtGamma = 0.0f;
			GetSingleton<IOptionSystem>()->Get( "GFX.Gamma.Brightness", &vtBrightness );
			GetSingleton<IOptionSystem>()->Get( "GFX.Gamma.Contrast", &vtContrast );
			GetSingleton<IOptionSystem>()->Get( "GFX.Gamma.Gamma", &vtGamma );
			SetGammaCorrection( MakeGammaValue(vtBrightness), MakeGammaValue(vtContrast), 
				                  MakeGammaValue(vtGamma), GetSingleton<IGFX>(), true );
			GetSingleton<ICursor>()->Acquire( true );
			return true;
		}
	}
	else
	{
		if ( NMain::IsInitialized() )
		{
			if ( IMainLoop *pML = GetSingleton<IMainLoop>() )
				pML->Pause( true, PAUSE_TYPE_INACTIVE );
			// restore default gamma correction
			SetGammaCorrection( 0, 0, 0, GetSingleton<IGFX>(), true );
			GetSingleton<ICursor>()->Acquire( false );
			return true;
		}
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool STDCALL NMain::Initialize( HWND hWnd3D, HWND nWndInput, HWND hWndSound, bool bGame )
{
	// register main object factory
	GetSLS()->AddFactory( GetMainObjectFactory() );
	// files inspector
	{
		IFilesInspector *pFI = CreateObject<IFilesInspector>( MAIN_FILES_INSPECTOR );
		RegisterSingleton( IFilesInspector::tidTypeID, pFI );
	}
	// create and register image processing
	{
		const SModuleDescriptor *pDesc = NMain::GetModuleDesc( IMAGE_IMAGE );
		CPtr<IImageProcessor> pIP = CreateObject<IImageProcessor>( pDesc->pFactory, IMAGE_PROCESSOR );
		RegisterSingleton( IImageProcessor::tidTypeID, pIP );
	}
	// create and register game timer
	{
		IGameTimer *pTimer = CreateObject<IGameTimer>( MAIN_GAME_TIMER );//CreateGameTimer();
		RegisterSingleton( IGameTimer::tidTypeID, pTimer );
		pTimer->Init();
	}
	// create and init input
	{
		const SModuleDescriptor *pDesc = NMain::GetModuleDesc( INPUT_INPUT );
		CPtr<IInput> pInput = CreateObject<IInput>( pDesc->pFactory, INPUT_INPUT );
		RegisterSingleton( IInput::tidTypeID, pInput );
		pInput->Init( nWndInput );
	}
	// create and init graphics 
	{
		const SModuleDescriptor *pDesc = NMain::GetModuleDesc( GFX_GFX );
		IObjectFactory *pFactory = pDesc->pFactory;
		CPtr<IGFX> pGFX = CreateObject<IGFX>( pFactory, GFX_GFX );
		if ( pGFX->Init(0, hWnd3D) != true )
			return false;
		RegisterSingleton( IGFX::tidTypeID, pGFX );	// register GFX to singleton
		// GFX managers
		CPtr<ITextureManager> pTM = CreateObject<ITextureManager>( pFactory, GFX_TEXTURE_MANAGER );
		RegisterSingleton( ITextureManager::tidTypeID, pTM );	// register texture manager to singleton
		pTM->Init();
		CPtr<IMeshManager> pMM = CreateObject<IMeshManager>( pFactory, GFX_MESH_MANAGER );
		RegisterSingleton( IMeshManager::tidTypeID, pMM );	// register mesh manager to singleton
		pMM->Init();
		//
		CPtr<IFontManager> pFM = CreateObject<IFontManager>( pFactory, GFX_FONT_MANAGER );
		RegisterSingleton( IFontManager::tidTypeID, pFM );	// register font manager to singleton
		pFM->Init();
	}
	// create and init sound
	{
		const SModuleDescriptor *pDesc = NMain::GetModuleDesc( SFX_SFX );
		IObjectFactory *pFactory = pDesc->pFactory;
		CPtr<ISFX> pSFX = CreateObject<ISFX>( pFactory, SFX_SFX );
		RegisterSingleton( ISFX::tidTypeID, pSFX );	// register GFX to singleton
		pSFX->Init( hWndSound, 0, SFX_OUTPUT_DSOUND, 44100, 32 );
		pSFX->SetDistanceFactor( fWorldCellSize / 2.0f );
		pSFX->SetRolloffFactor( GetGlobalVar("Sound.RolloffFactor", 1.0f) );
		//
		CPtr<ISoundManager> pSM = CreateObject<ISoundManager>( pFactory, SFX_SOUND_MANAGER );
		RegisterSingleton( ISoundManager::tidTypeID, pSM );	// register mesh manager to singleton
		pSM->Init();
	}
	// create animation manager
	{
		const SModuleDescriptor *pDesc = NMain::GetModuleDesc( ANIM_ANIM );
		IObjectFactory *pFactory = pDesc->pFactory;
		CPtr<IAnimationManager> pAM = CreateObject<IAnimationManager>( pFactory, ANIM_ANIMATION_MANAGER );
		RegisterSingleton( IAnimationManager::tidTypeID, pAM ); // register animation manager to singleton
		pAM->Init();
	}
	// create camera & cursor
	{
		const SModuleDescriptor *pDesc = NMain::GetModuleDesc( SCENE_SCENE );
		// camera
		IObjectFactory *pFactory = pDesc->pFactory;
		CPtr<ICamera> pCamera = CreateObject<ICamera>( pFactory, SCENE_CAMERA );
		pCamera->Init( GetSingletonGlobal() );
		RegisterSingleton( ICamera::tidTypeID, pCamera ); // register camera to singleton
		// cursor
		CPtr<ICursor> pCursor = CreateObject<ICursor>( pFactory, SCENE_CURSOR );
		RegisterSingleton( ICursor::tidTypeID, pCursor ); // register cursor to singleton
		pCursor->Init( GetSingletonGlobal() );
		pCursor->SetPos( 0, 0 );
		// particles
		CPtr<IParticleManager> pPM = CreateObject<IParticleManager>( pFactory, PFX_MANAGER );
		RegisterSingleton( IParticleManager::tidTypeID, pPM );	// register ParticleManger to singleton
		pPM->Init();
	}
	// create AI part
	{
		const SModuleDescriptor *pDesc = NMain::GetModuleDesc( AI_AI );
		IObjectFactory *pFactory = pDesc->pFactory;
		CPtr<IAILogic> pAILogic = CreateObject<IAILogic>( pFactory, AI_LOGIC );
		RegisterSingleton( IAILogic::tidTypeID, pAILogic );
		const_cast<CDifficultyLevel*>( pAILogic->GetDifficultyLevel() )->Init();
		
		CPtr<IAIEditor> pAIEditor = CreateObject<IAIEditor>( pFactory, AI_EDITOR );
		RegisterSingleton( IAIEditor::tidTypeID, pAIEditor );
	}
	// create and init text managing system
	{
		CPtr<ITextManager> pTextMan = CreateObject<ITextManager>( TEXT_MANAGER );
		RegisterSingleton( ITextManager::tidTypeID, pTextMan );
		pTextMan->Init();
		pTextMan->AddTextFile( "textes\\strings.txt" );
		pTextMan->AddTextFile( "textes\\tooltips.txt" );
		pTextMan->AddTextFile( "textes\\acks.txt" );
	}
	//
	// create scene objects
	{
		const SModuleDescriptor *pDesc = NMain::GetModuleDesc( SCENE_SCENE );
		IObjectFactory *pFactory = pDesc->pFactory;
		// scene
		CPtr<IScene> pScene = CreateObject<IScene>( pFactory, SCENE_SCENE );
		pScene->Init( GetSingletonGlobal() );
		RegisterSingleton( IScene::tidTypeID, pScene ); // register scene graph to singleton
		// vis obj builder
		CPtr<IVisObjBuilder> pVOB = CreateObject<IVisObjBuilder>( pFactory, SCENE_VISOBJ_BUILDER );
		pVOB->Init( GetSingletonGlobal() );
		RegisterSingleton( IVisObjBuilder::tidTypeID, pVOB );
	}
	// create and init UI system
	{
		const SModuleDescriptor *pDesc = NMain::GetModuleDesc( UI_BASE_VALUE );
		CPtr<IMaskManager> pMM = CreateObject<IMaskManager>( MASK_MANAGER );
		RegisterSingleton( IMaskManager::tidTypeID, pMM );
		pMM->Init();
	}
	
	// create commands history object
	{		
		ICommandsHistory *pHistory = CreateObject<ICommandsHistory>( MAIN_COMMANDS_HISTORY_INTERNAL );
		RegisterSingleton( ICommandsHistory::tidTypeID, pHistory );
	}
	// create single-player transceiver
	{
		ITransceiver *pTransceiver = CreateObject<ITransceiver>( MAIN_SP_TRANSCEIVER );
		pTransceiver->Init( GetSingletonGlobal(), -1 );
		RegisterSingleton( ITransceiver::tidTypeID, pTransceiver );
	}
	// create mission objects
	{
		IClientAckManager *pAckMan = CreateObject<IClientAckManager>( IClientAckManager::tidTypeID );
		pAckMan->Init();
		RegisterSingleton( IClientAckManager::tidTypeID, pAckMan );
		IMPToUICommandManager *pMPToUI = CreateObject<IMPToUICommandManager>( IMPToUICommandManager::tidTypeID ); 
		RegisterSingleton( IMPToUICommandManager::tidTypeID, pMPToUI );
		
		IMessageLinkContainer * pMessageLink = CreateObject<IMessageLinkContainer>( IMessageLinkContainer::tidTypeID );
		pMessageLink->Init();
		RegisterSingleton( IMessageLinkContainer::tidTypeID, pMessageLink );
	}
	// scenario tracker
	{
		IScenarioTracker *pST = CreateObject<IScenarioTracker>( MAIN_SCENARIO_TRACKER );
		RegisterSingleton( IScenarioTracker::tidTypeID, pST );
		IUserProfile *pUserProfile = CreateObject<IUserProfile>( MAIN_USER_PROFILE );
		RegisterSingleton( IUserProfile::tidTypeID, pUserProfile );
	}
	bInitialized = true;
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool STDCALL NMain::IsInitialized()
{
	return NMain::bInitialized;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool STDCALL NMain::Finalize()
{
	GetSingleton<ISFX>()->Done();
	GetSingleton<ITransceiver>()->Done();

	UnloadAllModules();
	//
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool STDCALL NMain::CanLaunch()
{
#if defined(_DO_ASSERT) || defined(_DO_ASSERT_SLOW)
	// check for remote drive - not allowed to run from!
	char buffer[2048];
	GetModuleFileName( 0, buffer, 2048 );
	std::string szModuleDir = buffer;
	szModuleDir.erase( szModuleDir.find( '\\' ) );
	if ( szModuleDir.empty() )
		return true;
	if ( szModuleDir[szModuleDir.size() - 1] != '\\' )
		szModuleDir += '\\';
	//
	if ( GetDriveType( szModuleDir.c_str() ) == DRIVE_REMOTE )
	{
		MessageBox( 0, "Program can't be run from the remote drive!", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		//MessageBox( 0, "��� ��� ���!", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

#endif // defined(_DO_ASSERT) || defined(_DO_ASSERT_SLOW)
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
