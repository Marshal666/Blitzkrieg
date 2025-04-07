#ifndef __PROGRESSHOOK_H__
#define __PROGRESSHOOK_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** progress indicator hook
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
interface IProgressHook : public IRefCount
{
	// set total num steps
	virtual void STDCALL SetNumSteps( const int nRange, const float fPercentage = 1.0f ) = 0;
	// do one step
	virtual void STDCALL Step() = 0;
	// recover during loading
	virtual void STDCALL Recover() = 0;
	// get/set current position
	virtual void STDCALL SetCurrPos( const int nPos ) = 0;
	virtual int STDCALL GetCurrPos() const = 0;
	// initialization/deinitialization
	virtual void Stop() = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
interface IMovieProgressHook : public IProgressHook
{
	enum EProgressType
	{
		PT_MAPGEN = 1,
		PT_LOAD = 2,
		PT_NEWMISSION = 3,
		PT_MINIMAP = 4,
		PT_TOTAL_ENCYCLOPEDIA_LOAD = 5,
		PT_CONNECTING_TO_SERVER = 6,
	};
	virtual void Init( EProgressType eType ) = 0;
	virtual void Init( const std::string &szMovieName ) = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __PROGRESSHOOK_H__