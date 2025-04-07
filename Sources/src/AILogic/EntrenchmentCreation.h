#ifndef _ENTRENCHMENT_CREATION_INTERNAL_
#define _ENTRENCHMENT_CREATION_INTERNAL_

#pragma ONCE
#include "RectTiles.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CEntrenchmentPart;
class CCommonStaticObject;
class CEntrenchment;
class CAIUnit;
class CFence;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CLongObjectCreation : public IRefCount
{
	DECLARE_SERIALIZE;
	float fWorkAccumulated;

public:
	CLongObjectCreation() : fWorkAccumulated( 0.0f ) {  }
	virtual bool PreCreate( const CVec2 &vFrom, const CVec2 &vTo ) = 0;
	
	// ������������ ������ �����
	virtual const int GetMaxIndex() const = 0;
	
	// ������� ��������� �������������
	virtual const int GetCurIndex() const = 0;

	// �����, ��� ����� ������ ���������
	virtual const CVec2 GetNextPoint( const int nPlace, const int nMaxPlace ) const = 0;

	// ������ ��������� ������� � ��������� ����������
	// ��� ������� �������� ������ ��������� ����������
	virtual void BuildNext() { fWorkAccumulated = 0.0f; }

	// ������� ������, ������� ������ ����������� �������������
	virtual void GetUnitsPreventing( std::list< CPtr<CAIUnit> > * units ) = 0;
	
	// ���� �� ���� 1 ����, ������� ������
	virtual bool IsAnyUnitPrevent() const = 0;

	// ����� �� ��������� ������� ���� �������� ( ��� ����� ������ )
	virtual bool CanBuildNext() const = 0;

	// ����� ������ ��� �� ���������
	virtual void LockCannotBuild() = 0;

	// ���������� ��� ���������, ����� ����� �� ����� ������
	virtual void LockNext() = 0;

	// �����, � ������� ����� ������ ������
	virtual CLine2 GetCurLine() = 0;
	
	virtual float GetPrice() = 0;

	virtual float GetBuildSpeed() = 0;

	// ����� �� ������, ����� ����� �� �������� � ��������
	virtual bool IsCheatPath() const { return false; }
	
	//when work finished, engineers must say that furter building impossible
	virtual bool CannotFinish() const { return false; }

	// work accumulation
	virtual void AddWork( const float fAdd ) { fWorkAccumulated += fAdd; }
	virtual float GetWorkDone() const { return fWorkAccumulated; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CEntrenchmentCreation : public CLongObjectCreation
{
	DECLARE_SERIALIZE;
	OBJECT_COMPLETE_METHODS( CEntrenchmentCreation );

	WORD GetLineAngle( const CVec2 &vBegin, const CVec2 &vEnd ) const;
	float GetTrenchWidth( int nType );// 0 - ������ , 1 - �������
	
	void SplitLineToSegrments( std::vector<CVec2> *vPoints, CVec2 vBegin, CVec2 vEnd, float TRENCHWIDTH );
	
private:
	CObj<CEntrenchment> pFullEntrenchment;
	std::vector< CObj<CEntrenchmentPart> > parts;
	
	CObj<CEntrenchmentPart> pBeginTerminator;		//
	CObj<CEntrenchmentPart> pEndTerminator;			// ������� �������� ����������
	CObj<CEntrenchmentPart> pNewEndTerminator;	// ������� �������� ����������
	
	std::vector<CVec2> vPoints;						// ������ ������
	int nCurIndex;
	WORD wAngle;
	int nPlayer;
	CLine2 line;
	bool bCannot;
	bool bSayAck;

	CTilesSet tilesUnder;									// ����� ��� ��������� ���������

	//consts
	//CGDBPtr<SGDBObjectDesc> pDesc;
  //CGDBPtr<SEntrenchmentRPGStats> pRPG;
	//int dbID;
	//int nTermInd;
	
	//
	bool CanDig( const SEntrenchmentRPGStats *pRPG, int dbID, const CVec2 &pt, WORD angle, int nFrameIndex );
	CEntrenchmentPart * AddElement( const SEntrenchmentRPGStats *pRPG, int dbID, const CVec2 &pt, WORD angle, int nFrameIndex );
	void CreateNewEndTerminator();
	void CalcTilesUnder();
	
	void InitConsts();
public:
	CEntrenchmentCreation() { }
	CEntrenchmentCreation( const int nPlayer );
	
	static bool SearchTrenches( const CVec2 &vCenter, const SRect &rectToTest );


	bool PreCreate( const CVec2 &vFrom, const CVec2 &vTo );
	virtual CLine2 GetCurLine() { return line; }
	const int GetMaxIndex() const;
	const int GetCurIndex() const;
	const CVec2 GetNextPoint( const int nPlace, const int nMaxPlace ) const;
	void BuildNext();
	void GetUnitsPreventing( std::list< CPtr<CAIUnit> > * units );
	bool IsAnyUnitPrevent() const;
	bool CanBuildNext() const; 
	void LockNext();
	float GetPrice();
	void LockCannotBuild(){ bCannot = true; }
	float GetBuildSpeed() { return SConsts::ENGINEER_ENTRENCH_LENGHT_PER_QUANT ;}
	virtual bool CannotFinish() const { return bSayAck; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CFenceCreation : public CLongObjectCreation
{
	DECLARE_SERIALIZE;
	OBJECT_COMPLETE_METHODS( CFenceCreation );
	//���������� � �������
	struct APointHelper
	{
	 std::vector<CVec2> m_points;
	 APointHelper() {}
	 bool operator() ( long x, long y ) { m_points.push_back( CVec2( x, y ) ); return true; }
	};

	std::vector< CObj<CFence> > fenceSegements;	// ��������
	std::vector<CVec2> vPoints;					// �������
	
	int nCurIndex;
	int nPlayer;
	void InitConsts();
	CTilesSet tilesUnder;
	bool isXConst;												// ����� ���� �� x- ����������
	CLine2 line;
	bool bCannot;
	bool bSayAck;

	void CalcTilesUnder();
	bool IsCegmentToBeBuilt( class CFence *pObj ) const;
public:
	CFenceCreation()  {  }
	CFenceCreation( const int nPlayer );

	bool PreCreate( const CVec2 &vFrom, const CVec2 &vTo );
	virtual CLine2 GetCurLine() { return line; }
	const int GetMaxIndex() const;
	const int GetCurIndex() const;
	const CVec2 GetNextPoint( const int nPlace, const int nMaxPlace ) const;
	void BuildNext();
	void GetUnitsPreventing( std::list< CPtr<CAIUnit> > * units );
	bool IsAnyUnitPrevent() const;
	bool CanBuildNext() const; 
	void LockNext();
	float GetPrice();
	void LockCannotBuild(){ bCannot = true; }
	float GetBuildSpeed() { return SConsts::ENGINEER_FENCE_LENGHT_PER_QUANT; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CFullBridge;
class CBridgeSpan;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CBridgeCreation : public CLongObjectCreation
{
	DECLARE_SERIALIZE;
	OBJECT_COMPLETE_METHODS( CBridgeCreation );
	// ��� ����������
	struct SBridgeSpanSort
	{
		bool operator()( const CObj<CBridgeSpan> &s1, const CObj<CBridgeSpan> &s2 );
	};

	CObj<CFullBridge> pFullBridge;
	std::vector< CObj<CBridgeSpan> > spans;
	CVec2 vStartPoint;
	CLine2 line;
	int nCurIndex;
	WORD wDir;

	void UnlockTiles();
	void LockTiles();
public:
	CBridgeCreation() {  }
	CBridgeCreation( class CFullBridge *pBridge, class CCommonUnit *pUnit );

	static CVec2 SortBridgeSpans( std::vector< CObj<CBridgeSpan> > *spans, class CCommonUnit *pUnit );

	//specific
	const CVec2 & GetStartPoint() const;	// ���� �������� ��������
	bool IsFirstSegmentBuilt() const;

	// common
	CLine2 GetCurLine();
	const int GetMaxIndex() const;
	const int GetCurIndex() const;
	const CVec2 GetNextPoint( const int nPlace, const int nMaxPlace ) const;
	void BuildNext();
	float GetPrice();
	float GetBuildSpeed();

	//
	bool IsAnyUnitPrevent() const { return false; }
	bool CanBuildNext() const { return true; }
	void LockNext() { }
	void LockCannotBuild() { }
	bool PreCreate( const CVec2 &vFrom, const CVec2 &vTo ) { return true; } 
	void GetUnitsPreventing( std::list< CPtr<CAIUnit> > * units ){}
	virtual bool IsCheatPath() const { return true; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // _ENTRENCHMENT_CREATION_INTERNAL_
