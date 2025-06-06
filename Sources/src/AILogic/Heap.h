#ifndef __HEAP_H__
#define __HEAP_H__

#pragma ONCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �� ������� ���� ��������� ���������� �������
// bool Cmp::operator()(const T &a, const T &b) ������ ���������� true � ������ a < b
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct SVoidSwap
{
	void operator()( const T &a, const T &b, const int aIndex, const int bIndex ) { }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class TCmp, class TWillSwap = SVoidSwap<T> >
class CHeap
{
	DECLARE_SERIALIZE;
	
	TCmp cmp;
	TWillSwap WillSwap;
	
	// ��������� ��������� �� 1!
	std::vector<T> heap;
	int nEl;

	// ���������������, ������� � ��. k � �����
	int Balance( int k );
public:
	CHeap() : nEl( 0 ), heap( 1 ) { }
	CHeap( const int nSize ) : heap( nSize + 1 ), nEl( 0 ) { }

	void Reserve( const int nSize ) { if ( nSize + 1 > heap.size() ) heap.resize( nSize + 1 ); }

	const int Size() const { return nEl; }
	const int GetReserved() const { return heap.size() - 1; }

	bool IsEmpty() const { return nEl == 0; }

	void Erase( const int n );
	void Clear() { heap.clear(); nEl = 0; heap.resize( 1 ); }

	// ���������� ������, ���� ������� �����
	int Push( const T& el );
	const T Pop();

	// ����������������� ��� ���������� �������� �� ������� k
	int Increased( const int k );

	const T& GetMaxEl() const { return heap[1]; }
	T& GetMaxEl() { NI_ASSERT_T( nEl >= 1, "The heap is empty" );	return heap[1]; }

	const T& operator[]( const int n ) const { return heap[n + 1]; }
	T& operator[]( const int n ) { return heap[n + 1]; }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class TCmp, class TWillSwap>
int CHeap<T, TCmp, TWillSwap>::Balance( int k )
{
	while ( k > 1 && cmp( heap[k / 2], heap[k] ) )
	{
		WillSwap( heap[k], heap[k/2], k-1, k/2-1 );
		std::swap( heap[k], heap[k/2] );
		k /= 2;
	}

	return k-1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class TCmp, class TWillSwap>
int CHeap<T, TCmp, TWillSwap>::Push( const T& el )
{
	heap[++nEl] = el;	

	return Balance( nEl );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class TCmp, class TWillSwap>
int CHeap<T, TCmp, TWillSwap>::Increased( const int k )
{
	return Balance( k + 1 );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class TCmp, class TWillSwap>
void CHeap<T, TCmp, TWillSwap>::Erase( const int n )
{
	int k = n + 1;
	NI_ASSERT_T( k >= 1 && k <= nEl, "Wrong element to erase from heap" );
	WillSwap( heap[k], heap[nEl], k-1, nEl-1 );
	heap[k] = heap[nEl];
	--nEl;

	while ( 2*k + 1 <= nEl && ( cmp( heap[k], heap[2*k] ) || cmp( heap[k], heap[2*k + 1] ) ) )
	{
		if ( cmp( heap[2*k], heap[2*k + 1 ] ) )
		{
			WillSwap( heap[k], heap[2*k + 1], k-1, 2*k );
			std::swap( heap[k], heap[2*k + 1] );
			k *= 2;
			++k;
		}
		else
		{
			WillSwap( heap[k], heap[2*k], k-1, 2*k-1 );
			std::swap( heap[k], heap[2*k] );
			k *= 2;
		}
	}

	if ( k > 0 && 2*k + 1 > nEl && 2 * k <= nEl && cmp( heap[k], heap[2*k] ) )
	{
		WillSwap( heap[k], heap[2*k], k-1, 2*k-1 );
		std::swap( heap[k], heap[2*k] );
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class TCmp, class TWillSwap>
const T CHeap<T, TCmp, TWillSwap>::Pop()
{
	const T result( heap[1] );
	Erase( 0 );
	return result;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class TCmp, class TWillSwap>
int CHeap<T, TCmp, TWillSwap>::operator&( IStructureSaver &ss )
{
	CSaverAccessor saver = &ss;

	saver.Add( 1, &heap );
	saver.Add( 2, &nEl );

	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __HEAP_H__
