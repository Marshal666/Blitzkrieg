#ifndef __GRAPH_H__
#define __GRAPH_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// неориентированный граф без петель с неотрицательными весами рёбер
class CGraph
{
	DECLARE_SERIALIZE;

	// расстояния от v1 до вершин для подсчитанного пути
	std::vector<float> dst;
	std::vector<int> pred;

	std::vector<int> graphComponent;

	int v1, v2;

	//
	void FindUpperComponent( const int v );
protected:
	// для каждой вершини список соседних
	std::vector< std::list<int> > nodes;
	int n;
public:
	CGraph() : n( 0 ), v1( -1 ), v2( -1 ) { }
	void Clear();

	const int GetNNodes() const { return n; }
	void AddEdge( const int v1, const int v2 );

	// подсчитать путь от v1 до v2
	void ComputePath( const int v1, const int v2 );
	// выдать длину подсчитанного в ComputePath пути
	// если путь не найден, то -1
	const float GetPathLength() const;
	void GetPath( std::list<int> *pPath ) const;

	// длина ребра между v1 и v2
	virtual const float GetEdgeLength( const int v1, const int v2 ) = 0;

	// в одной ли компоненте связности вершины v1 и v2
	bool IsInOneGraphComponent( const int v1, const int v2 );
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __GRAPH_H__
