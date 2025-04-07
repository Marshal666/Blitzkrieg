#ifndef __BASICOBJECTFACTORY_H__
#define __BASICOBJECTFACTORY_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CBasicObjectFactory : public IObjectFactory
{
	typedef std::hash_map<int, ObjectFactoryNewFunc> CNewFuncsMap;
	typedef std::hash_map<const type_info*, int, SDefaultPtrHash> CRTTIMap;
	// ������� ������� ��� �������� ����� ��������
	CNewFuncsMap newfuncs;
	CRTTIMap rttis;
private:
	// ���������� ����������
	void RegisterType( int nObjectTypeID, const type_info *pObjectTypeInfo, ObjectFactoryNewFunc newFunc );
public:
	// ������� ������ �� ��� typeID
	virtual IRefCount* STDCALL CreateObject( int nTypeID );
	// ���������������� ���
	virtual void STDCALL RegisterType( int nObjectTypeID, ObjectFactoryNewFunc newFunc );
	// ������������� ������ factory ������ ���� (������������������ � ������� �� ��� �������)
	virtual void STDCALL Aggregate( IObjectFactory *pFactory );
	// �������� ���������� ����� ��������, ������� ��� ������� (+ ��� ��������������� � ��) ����� �������
	virtual int STDCALL GetNumKnownTypes() { return newfuncs.size(); }
	// �������� type info ��������, ������� ��� ������� (+ ��� ��������������� � ��) ����� �������
	virtual void STDCALL GetKnownTypes( SObjectFactoryTypeInfo *pInfoBuffer, int nBufferSize );
	// �������� typeID ������� �� ��������� �� ����
	virtual int STDCALL GetObjectTypeID( IRefCount *pObj ) const
	{
		NI_ASSERT_T( pObj != 0, "can't get object type ID from NULL pointer" );
		const type_info &rtti = typeid( *pObj );
		CRTTIMap::const_iterator pos = rttis.find( &rtti );
		return pos != rttis.end() ? pos->second : -1;
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define REGISTER_CLASS( pFactory, nTypeID, className ) pFactory->RegisterType( nTypeID, reinterpret_cast<ObjectFactoryNewFunc>( className##::CreateNewClassInstanceInternal ) );
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __BASICOBJECTFACTORY_H__
