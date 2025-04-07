#if !defined(__ImageEdge__)
#define __ImageEdge__
struct SImageEdge
{
  //original (defragmented) image LeftTop corner position
  CTPoint<int> originalLeftTop;
  //if true - filled per string else filled per colums
  bool isHorizontal;
  //filled per string or per colums
  CVarArray2D<short, char> edges;

  SImageEdge() : isHorizontal ( true ) { }
  int operator&( IStructureSaver &ss )
  {
    CSaverAccessor saver = &ss;
	  saver.Add( 1, &originalLeftTop );
	  saver.Add( 2, &isHorizontal );
	  saver.Add( 3, &edges );
    return 0;
  }

  //is point in edges?
  //method check bounds!
  bool In( const CTPoint<int> &rPoint );
  
  //fill edges
  bool CreateImageEdge( IImage *pImage,
                        const CTPoint<int> &rOriginalLeftTop,
                        DWORD alpha );

#ifdef _DEBUG
  //for test only, set edge pixels to white
  //mark all edge points as white
  bool MarkEdge( IImage *pImage );
  bool MarkInEdge( IImage *pImage );
  //mark all points with alpha in rAlpha bounds as white
  bool MarkAlpha( IImage *pImage , DWORD dwMinAlpha, DWORD dwMaxAlpha );
#endif //#ifdef _DEBUG
};
#endif // !defined(__ImageEdge__)
