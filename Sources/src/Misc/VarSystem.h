#ifndef __VARSSYSTEM_H__
#define __VARSSYSTEM_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
interface IVarIterator : public IRefCount
{
	// go to the next var
	virtual bool STDCALL Next() = 0;
	// was all vars already iterated?
	virtual bool STDCALL IsEnd() const = 0;
	// get current var
	virtual bool STDCALL Get( variant_t *pVarName, variant_t *pVar ) const = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
interface IVarSystem : public IRefCount
{
	// get/set variable by name
	virtual bool STDCALL Get( const std::string &szVarName, variant_t *pVar ) const = 0;
	virtual bool STDCALL Set( const std::string &szVarName, const variant_t &var ) = 0;
	// remove variable by name or by match
	virtual bool STDCALL Remove( const std::string &szVarName ) = 0;
	virtual bool STDCALL RemoveByMatch( const std::string &szVarMatch ) = 0;
	// include/exclude variable by match to serialize
	virtual bool STDCALL ChangeSerialize( const std::string &szVarMatch, bool bInclude ) = 0;
	virtual bool STDCALL IsChanged() const = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __VARSSYSTEM_H__
