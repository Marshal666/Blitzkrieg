#ifndef __SQUADVISOBJ_H__
#define __SQUADVISOBJ_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSquadVisObj : public CTRefCount<ISquadVisObj>
{
	OBJECT_SERVICE_METHODS( CSquadVisObj );
	DECLARE_SERIALIZE;
	//
	std::vector<ISquadVisObj::SData> units;							// units in this squad
	CPtr<IGFXTexture> pIcon;														// icon texture
	CVec2 vPos;																					// position on the screen
	bool bSelected;																			// is this squad selected
	//
	CSquadVisObj();
public:
	void SetIcon( IGFXTexture *_pIcon ) { pIcon = _pIcon; }
	// update object
	virtual bool STDCALL Update( const NTimer::STime &time, bool bForced = false ) { return false; }
	// drawing
	virtual bool STDCALL Draw( interface IGFX *pGFX );
	// visiting
	virtual void STDCALL Visit( interface ISceneVisitor *pVisitor, int nType = -1 );
	// set screen position
	virtual void STDCALL SetPosition( const CVec2 &_vPos ) { vPos = _vPos; }
	// data update
	virtual bool STDCALL UpdateData( ISquadVisObj::SData *pObjects, int nNumObjects );
	// toggle selection - select/unselect
	virtual bool STDCALL ToggleSelection() { bSelected = !bSelected; return bSelected; }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __SQUADVISOBJ_H__
