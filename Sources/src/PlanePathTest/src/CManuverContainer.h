/* Generated by Together */

#ifndef CMANUVERCONTAINER_H
#define CMANUVERCONTAINER_H

#include "..\..\AILogic\AIClassesID.h"

/////////////////////////////////////////////////////////////////////////////
enum EPlanesAttitude
{
	EPA_ATTACK							= 0,
	EPA_RETREAT							= 1,
};
/////////////////////////////////////////////////////////////////////////////
enum EManuverDestination
{
	EMD_PREDICTED_POINT,										// 
	EMD_MANUVER_DEPENDENT,									// manuver desides the plane's end point
};
/////////////////////////////////////////////////////////////////////////////
enum EManuverID
{
	//ASSIGN REAL IDS FROM OBJECT FACTORY
	EMID_GENERIC									= AI_PLANE_MANUVER_GENERIC,
	EMID_GORKA										= AI_PLANE_MANUVER_GORKA,
};
/////////////////////////////////////////////////////////////////////////////
enum EParameterID
{
	EPID_ENEMY_DIRECTION		= 0,										// to enemy form plane's front direction
	EPID_PLANE_DIRECTION		= 1,										// to plane from enemy's front direction
	EPID_DIRS_DIFFERENCE		= 2,										// speeds dirs difference

	EPID_DISTANCE						= 3,										// (In self turn radius)

	EPID_SELF_HEIGHT				= 4,										// IN TURN RADIUSES (ABOVE plane_min_heght
	EPID_HEIGHT_DIFF				= 5,										// IN SELF TURN RADIUS
	
	EPID_SELF_SPEED					= 6,
	EPID_ENEMY_SPEED				= 7,										// with respect to it's maximum
	
	_EPID_COUNT							,
};
/////////////////////////////////////////////////////////////////////////////
enum ESpeedRelation
{
	ESR_NEAR_STALL,
	ESR_SMALL,
	ESR_NORMAL,
	ESR_MAXIMUM,
	
	_ESR_COUNT,
};
/////////////////////////////////////////////////////////////////////////////
typedef std::pair<float/*lower bound*/,float/*higher bound*/> CParameterRange;
typedef std::vector<float> CParameters;
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//	CManuverStateDescriptor
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class CManuverStateDescriptor
{
	CParameters parameters;
	enum EPlanesAttitude att;
public:	

	CManuverStateDescriptor() : parameters( _EPID_COUNT ) {  }
	/*enum EPlanesAttitude*/ const int GetAtt() const { return att; }

	float Get( const /*enum EParameterID*/ int id ) const { return parameters[id]; }
	
	// fill parameters according plane's & enemy's state
	void Init( const enum EPlanesAttitude _att, interface IPlane *pPos, interface IPlane *pEnemy );
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//	CManuverDescriptor
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
struct SManuverDescriptorForLoad
{
	std::vector<CParameterRange> parameters;

	std::string szID;												// for load from string
	std::string szPoint;
	std::string szAtt;

	int operator&( IDataTree &ss )
	{
		CTreeAccessor tree = &ss;
		tree.Add( "ManuverID", &szID );
		tree.Add( "Point", &szPoint );
		tree.Add( "Attitude", &szAtt );
		tree.Add( "Parameters", &parameters );
		return 0;
	}	
};
/////////////////////////////////////////////////////////////////////////////
class CManuverDescriptor
{
	DECLARE_SERIALIZE;
	std::vector<CParameterRange> parameters;
	
	EManuverID id;													// id of manuver to create
	enum EManuverDestination point;					// point of manuver
	enum EPlanesAttitude att;
public:
	
	void Init( const /*EManuverID*/int _id, const /*enum EManuverDestination*/ int _point, const /*enum EPlanesAttitude*/ int _att, const std::vector<CParameterRange> &_parameters )
	{
		id = EManuverID(_id);
		point = EManuverDestination(_point);
		att = EPlanesAttitude(_att);
		parameters = _parameters;
	}
	CManuverDescriptor() : parameters( _EPID_COUNT ) {  }
	
	const enum EManuverID GetManuverID() const { return id; }
	enum EManuverDestination GetDestination() const { return point; }

	const CParameterRange & Get( const enum EParameterID id ) const { return parameters[id]; }
	/*enum EPlanesAttitude*/ const int GetAtt() const { return att; }

	const float & GetLO( const /*enum EParameterID*/ int id ) const { return parameters[id].first; }
	const float & GetHI( const /*enum EParameterID*/ int id ) const { return parameters[id].second; }

	bool CheckSuitable( const CManuverStateDescriptor &desc ) const
	{
		for ( int i = 0; i < _EPID_COUNT; ++i )
		{
			if ( GetLO(i) != GetHI(i) && (GetLO(i) > desc.Get(i) || GetHI(i) < desc.Get(i)) )
				return false;
		}
		return true;
	}
};
/*
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//	namespace NAttitude
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
namespace NAttitude
{
// attitude table
struct SAttitude
{
	EPlanesAttitude atts;
	std::string forLoad;
	
	void Convert( const std::hash_map<std::string,int> &loadHelper )
	{
		std::hash_map<std::string,int>::const_iterator it = loadHelper.find( forLoad );
		NI_ASSERT_T( it != loadHelper.end(), NStr::Format( "cannot find value for \"%s\"", forLoad.c_str() ) );
		atts = EPlanesAttitude(it->second);
		forLoad.clear();
	}
	int operator&( IDataTree &ss )
	{
		CTreeAccessor tree = &ss;
		tree.Add( "Attitude", &forLoad );
		return 0;
	}
};
struct SSingleHeightSingleOurSpeedAttitude
{
	std::vector<SAttitude> atts;
	void Convert( const std::hash_map<std::string,int> &loadHelper )
	{
		for ( int i = 0; i < atts.size(); ++i )
			atts[i].Convert( loadHelper );
	}
	int operator&( IDataTree &ss )
	{
		CTreeAccessor tree = &ss;
		tree.Add( "Atts", &atts );
		return 0;
	}
};
struct SSingleHeightAttitude
{
	std::vector<SSingleHeightSingleOurSpeedAttitude> atts;
	CParameterRange range;
	
	void Convert( const std::hash_map<std::string,int> &loadHelper )
	{
		for ( int i = 0; i < atts.size(); ++i )
			atts[i].Convert( loadHelper );
	}
	int operator&( IDataTree &ss )
	{
		CTreeAccessor tree = &ss;
		tree.Add( "Speeds", &atts );
		tree.Add( "Height", &range );
		return 0;
	}
};
typedef std::vector<SSingleHeightAttitude> CAttitudes;
};
*/
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//	CManuverContainer ::
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class CManuverContainer 
{
	static std::vector<int> suitableIndeces;
	static CManuverStateDescriptor state;				// temprorary value, used inside CreateManuver()

	// all manuvers descriptors
	typedef std::vector<CManuverDescriptor> CDescriptors;
	CDescriptors descriptors;

	// manuvers
	typedef std::list<int> CManuverIndeces;
	typedef std::hash_map<int/*EPlanesAttitude*/, CManuverIndeces> CManuvers;
	CManuvers manuvers;

	// choose manuver to perform. return 0 if none chousen
	const CManuverDescriptor * Choose( const CManuverStateDescriptor &current ) const;

	// default plane's behaviour. _must_ always return non null IManuver
	interface IManuver * CreateDefaultManuver( const enum EPlanesAttitude att, interface IPlane *pPos, interface IPlane *pEnemy ) const;
	
	enum EPlanesAttitude GetAttitude( interface IPlane *pPlane, interface IPlane *pEnemy ) const;

public:

	void Init();

	// manuvers for air fight.
	interface IManuver* CreateManuver ( interface IPlane *pPos, interface IPlane *pEnemy ) const;

	// for travel to point. suitable for fighter patrol, bombers, etc.
	interface IManuver* CreatePointManuver ( interface IPlane *pPos, const CVec3 &vPoint ) const;

	
};
/////////////////////////////////////////////////////////////////////////////
#endif //CMANUVERCONTAINER_H