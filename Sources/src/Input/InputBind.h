#ifndef __INPUTBIND_H__
#define __INPUTBIND_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CInputBind : public CTRefCount<IInputBind>
{
	OBJECT_SERVICE_METHODS( CInputBind );
	//
	std::string szCommand;
	EInputBindActivationType eType;
	std::vector<std::string> controls;
public:
	// clear all bind data
	virtual void Clear() { szCommand.clear(); controls.clear(); }
	// setup data
	// add control to bind
	virtual void STDCALL AddControl( const char *pszControl ) { controls.push_back( pszControl ); }
	// set command to bind
	virtual void STDCALL SetCommand( const char *pszCommand, const EInputBindActivationType _eType )
	{
		szCommand = pszCommand;
		eType = _eType;
	}

	// retrieve data
	//
	// retrieve number of controls in this bind
	virtual int STDCALL GetNumControls() const { return controls.size(); }
	// retrieve control name
	virtual const char* STDCALL GetControl( const int nIndex ) const { return controls[nIndex].c_str(); }
	// retrieve command name
	virtual const char* STDCALL GetCommand() const { return szCommand.c_str(); }
	// retrieve bind activation type
	virtual EInputBindActivationType STDCALL GetActivationType() const { return eType; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTBIND_H__
