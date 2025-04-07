#if !defined(__RoadPoints__Types__)
#define __RoadPoints__Types__

#include "LA_Types.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//����� �������� ������ - ����� �������� ������
//����� ������������ � ����������� �� �������:
//  | |...| |...| |A    A Y
//   .     .     . |    |
//   .     .     . b    |
//   .     .     . |    |
// A| |...|x|...| |V    |(0,0)     X
// | .     .     .			|---------->
// a .     .     .
// | .     .     .
// V| |   | |...| |
//   <-a->   <-b->
//
//a = (int)( ( nWidth - 0.5f ) / 2.0f )
//b = (int)( ( nWidth + 0.5f ) / 2.0f )
//
//����� �� �����������: [SRoadPoint.x - a, ... , SRoadPoint.x + b]
//����� �� ���������:   [SRoadPoint.y - a, ... , SRoadPoint.y + b]
//
// �������: ������ 1, ����� - (2, 2) a = 0, b = 0, ����������� - ( 2, 2, 2, 2 ) 
// �������: ������ 2, ����� - (2, 2) a = 0, b = 1, ����������� - ( 2, 2, 3, 3 ) 
// �������: ������ 3, ����� - (2, 2) a = 1, b = 1, ����������� - ( 1, 1, 3, 3 ) 
// �������: ������ 4, ����� - (2, 2) a = 1, b = 2, ����������� - ( 1, 1, 4, 4 ) 
// �������: ������ 5, ����� - (2, 2) a = 2, b = 2, ����������� - ( 0, 0, 4, 4 )
// � ��� �����...
struct SRoadPoint : public CTPoint<int>
{
	static const int INVALID_WIDTH;

	BYTE nDirection;
	int nWidth;
	int nRoadType;

	SRoadPoint()
		: CTPoint<int>( 0, 0 ), nDirection( RMGC_INVALID_DIRECTION ), nWidth( INVALID_WIDTH ), nRoadType( 0 ) {}
	SRoadPoint( int nXPisition, int nYPosition, BYTE _nDirection, int _nWidth, int _nRoadType )
		: CTPoint<int>( nXPisition, nYPosition ), nDirection( _nDirection ), nWidth( _nWidth ), nRoadType( _nRoadType ) {}
	SRoadPoint( const CTPoint<int> &rPoint, BYTE _nDirection, int _nWidth, int _nRoadType )
		: CTPoint<int>( rPoint ), nDirection( _nDirection ), nWidth( _nWidth ), nRoadType( _nRoadType ) {}
	SRoadPoint( const SRoadPoint &rPoint )
		: CTPoint<int>( rPoint.x, rPoint.y ), nDirection( rPoint.nDirection ), nWidth( rPoint.nWidth ), nRoadType( rPoint.nRoadType ) {}
	SRoadPoint& operator=( const SRoadPoint &rPoint )
	{
		if( &rPoint != this )
		{
			x = rPoint.x;
			y = rPoint.y;
			nDirection = rPoint.nDirection;
			nWidth = rPoint.nWidth;
			nRoadType =  rPoint.nRoadType;
		}
		return *this;
	}

	// serializing...
	virtual int STDCALL operator&( IStructureSaver &ss );
	virtual int STDCALL operator&( IDataTree &ss );

	//��� c������� ����� ����� - �����������
	inline bool HasHorizontalDirection() const
	{
		NI_ASSERT_T( ( nDirection >= RMGC_HORIZONTAL_TO_ZERO ) &&
								 ( nDirection <= RMGC_VERTICAL_FROM_ZERO ),
								 NStr::Format( "Road point direction not set!" ) );
		return ( ( nDirection == RMGC_HORIZONTAL_TO_ZERO ) || ( nDirection == RMGC_HORIZONTAL_FROM_ZERO ) );
	}
	//���������� ����� �� ����� �� ������ ( ����������� ����������� )
	//���������� ���������� ����� �������, ������������� ���� ����������� ���������������
	bool IsRoadPoint( const SRoadPoint &rRoadPoint, int *pnLength ) const;
	//�������� ����� �������� �� ��� ������ ����������� �����������
	//nLength - ���������� ����� ������� ��������
	inline SRoadPoint GetRoadPoint( int nLength ) const
	{
		NI_ASSERT_T( ( nDirection >= RMGC_HORIZONTAL_TO_ZERO ) &&
								 ( nDirection <= RMGC_VERTICAL_FROM_ZERO ),
								 NStr::Format( "Road point direction not set!" ) );
		SRoadPoint roadPoint( *this );
		roadPoint += RMGC_SHIFT_POINTS[nDirection - RMGC_HORIZONTAL_TO_ZERO] * nLength;
		return roadPoint;
	}
	//������������� �����������
	//���������� ���� ����������� � ����������� ������������ �� X ��� �� Y ����� ��������
	//���� ������������� ������
	inline CTRect<int> GetCrossRect() const
	{
		NI_ASSERT_T( nWidth > INVALID_WIDTH,
								 NStr::Format( "Road point has invalid width!" ) );
		CTRect<int> crossRect( x - GetMinorWidth(),
													 y - GetMinorWidth(),
													 x + GetMajorWidth(),
													 y + GetMajorWidth() );
		crossRect.Normalize();
		return crossRect;
	}
	//������������� ������ �� ����� �������� �� ��� ������ �� ��������� nLength
	inline CTRect<int> GetRoadRect( int nLength ) const
	{
		CTRect<int> roadRect = GetCrossRect();
		roadRect.Union(	GetRoadPoint( nLength ).GetCrossRect() );
		roadRect.Normalize();
		return roadRect;
	}
	//��������� �� ����� ������ � ����������� �� �����������
	inline int GetMinorWidth() const { return static_cast<int>( ( nWidth - 0.5f ) / 2.0f ); }
	inline int GetMajorWidth() const { return static_cast<int>( ( nWidth + 0.5f ) / 2.0f ); }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRoadMakeParameter
{
	//����������� ���������� ����� ������������� �������� (� VIS ������)
	int nMinMiddleDistance;
	//���������� �������������� (���������������� �����) (� VIS ������)
	std::vector<CTRect<int> > lockedRects;

	SRoadMakeParameter()
		: nMinMiddleDistance( 1 ){}
	SRoadMakeParameter( int _nMinMiddleDistance, const std::vector<CTRect<int> > &rLockedRects )
		: nMinMiddleDistance( _nMinMiddleDistance ), lockedRects( rLockedRects ) {}
	SRoadMakeParameter( const SRoadMakeParameter &rParameter )
		: nMinMiddleDistance( rParameter.nMinMiddleDistance ),  lockedRects( rParameter.lockedRects ) {} 
	SRoadMakeParameter& operator=( const SRoadMakeParameter &rParameter )
	{
		if( &rParameter != this )
		{
			nMinMiddleDistance = rParameter.nMinMiddleDistance;
			lockedRects = rParameter.lockedRects;
		}
		return *this;
	}

	// serializing...
	virtual int STDCALL operator&( IStructureSaver &ss );
	virtual int STDCALL operator&( IDataTree &ss );
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // #if !defined(__RoadPoints__Types__)
