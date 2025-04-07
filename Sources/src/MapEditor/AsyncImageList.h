#if !defined(__AsyncImageList__)
#define __AsyncImageList__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CRAP{переделаь на более надежный и быстрый способ индексирования
class CIndicesHolder
{
	CTPoint<int> bounds;
	BYTE* pIndices;

	int nCurrentIndex;

	int ProceedIndex( int nStartIndex )
	{
		while ( ( nStartIndex < bounds.max ) && ( pIndices[nStartIndex - bounds.min] > 0 ) )
		{
			++nStartIndex;
		}

		if ( nStartIndex >= bounds.max ) 
		{
			return INVALID_INDEX;
		}
		return nStartIndex;
	}
public:
	static const int INVALID_INDEX;

	CIndicesHolder()
		: bounds( CTPoint<int>( 0, 0 ) ), nCurrentIndex( INVALID_INDEX ), pIndices( 0 ) {}
	~CIndicesHolder()
	{
		Clear();
	}

	void Create( const CTPoint<int> &rBounds )
	{
		NI_ASSERT_T( rBounds.min < rBounds.max,
								 NStr::Format("Invalid bounds: (%d, %d)\n", rBounds.min, rBounds.max ) );
		Clear();
		bounds = rBounds;
		pIndices = new BYTE[bounds.max - bounds.min];
		::ZeroMemory( pIndices, ( bounds.max - bounds.min ) * sizeof( BYTE ) );
	}

	void Clear()
	{
		if ( pIndices )
		{
			delete[] pIndices;
			pIndices = 0;
		}
		bounds = CTPoint<int>( 0, 0 );
		nCurrentIndex = INVALID_INDEX;
	}

	int CIndicesHolder::GetStartIndex( int nStartIndex )
	{
		NI_ASSERT_T( pIndices != 0,
								 NStr::Format( "Not created." ) );

		if ( ( nStartIndex < bounds.min ) || ( nStartIndex >= bounds.max ) ) 
		{
			return INVALID_INDEX;
		}
		nCurrentIndex = ProceedIndex( nStartIndex );
		if ( nCurrentIndex == INVALID_INDEX ) 
		{
			nCurrentIndex = ProceedIndex( bounds.min );
		}		
		return nCurrentIndex;
	}

	int CIndicesHolder::GetNextIndex()
	{
		NI_ASSERT_T( pIndices != 0,
								 NStr::Format( "Not created." ) );
		
		if ( ( nCurrentIndex < bounds.min ) || ( nCurrentIndex >= bounds.max ) ) 
		{
			nCurrentIndex = bounds.min;
		}
		else
		{
			pIndices[nCurrentIndex - bounds.min] = 1;
			nCurrentIndex = ProceedIndex( ++nCurrentIndex );
		}
		if ( nCurrentIndex == INVALID_INDEX ) 
		{
			nCurrentIndex = ProceedIndex( bounds.min );
		}		
		return nCurrentIndex;
	}
};
//CRAP}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//pvParam - указатель на обьект класса CAsyncImageList, преобразованный к PVOID
DWORD WINAPI AsyncImageListThreadFunc( PVOID pvParam );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
interface IAsyncImageListCallback
{
	//выполняется в критической секции
	virtual DWORD Callback( int nImageIndex, DWORD dwResult ) = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAsyncImageList
{
	static const int DEFAULT_ICON_NUMBER;

	int nForceStartImageIndex;
	HIMAGELIST hImageList;
	HIMAGELIST hSmallImageList;

	CRITICAL_SECTION criticalSection;
	HANDLE hThread;
	HANDLE hExitEvent;
	HANDLE hForceStartEvent;

	std::hash_map<int, IAsyncImageListCallback* > callbackHashMap;
	CIndicesHolder indicesHolder;

	void Clear();
	//потоковая функция вызываемая из AsyncFill
	DWORD Fill();
	//ее переопределяем, заполняем картинку по указанному номеру
	//к HIMAGELIST обращаться через критическую секцию, функция вызывается в другом потоке
	virtual DWORD Fill( int nImageIndex ) = 0;
	
	friend DWORD WINAPI AsyncImageListThreadFunc( PVOID pvParam );
public:
	CAsyncImageList();
	~CAsyncImageList();

	//обращаться через критическую секцию
	HIMAGELIST GetImageList() { return hImageList; }
	HIMAGELIST GetSmallImageList() { return hSmallImageList; }
	//критическая секция
	CRITICAL_SECTION* GetCriticalSection() { return &criticalSection; }

	//создать imageList заданной длинны, заданного размера
	bool Create( int nImageCount, const CTPoint<int> &rImageSize );
	//старт асинхронного заполнения imageList
	bool AsyncFill();
	//проверка на завершенность процесса заполнения
	bool IsFilling();
	//принудительное завершение процесса заполнения
	bool StopFilling();

	//добавление callback функции
	int AddCallback( IAsyncImageListCallback *pCallback );
	//удаление callback функции по ключу
	void RemoveCallback( int nKey );

	//продолжить заполнение с указанного значения
	bool ForceFillFrom( int nImageIndex );
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // !defined(__AsyncImageList__)
