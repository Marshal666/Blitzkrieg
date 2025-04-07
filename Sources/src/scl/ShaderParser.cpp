#include "StdAfx.h"

#include <comdef.h>
#include <d3d8types.h>

#include "ShaderParser.h"
#include "Shader.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParseTechnique( _ReductionPtr reduction, STechnique *pTechnique );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CShaderParser::CShaderParser()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CShaderParser::Init()
{
	return CParser::Init( "shader.cgt" );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CShaderParser::ErrorLexical( const int nLineNumber )
{
	printf( "ERROR in the line %d:\n", nLineNumber );
	printf( "lexical error - unrecognized token \"%s\"\n", (const char*)(GetParser()->CurrentToken()->Name) );
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CShaderParser::ErrorSyntax( const int nLineNumber )
{
	printf( "ERROR in the line %d:\n", nLineNumber );
	printf( "Syntax error - unexpected token readed\n" );
	printf( "The next tokens were expected:\n" );
	//
	_GOLDParserPtr parser = GetParser();
	for ( short i = 0; i < parser->TokenCount(); ++i )
	{
		_TokenPtr token = parser->Tokens( i );
		printf( "\t%s\n", (const char*)(token->Name) );
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CShaderParser::ErrorComment( const int nLineNumber )
{
	printf( "ERROR in the line %d:\n", nLineNumber );
	printf( "The end of the input was reached while reading a comment.\n" );
	printf( "This is caused by a comment that was not terminated\n" );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CShaderParser::ErrorInternal( const int nLineNumber )
{
	printf( "ERROR in the line %d:\n", nLineNumber );
	printf( "Internal compiler error!\n" );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CShaderParser::ErrorNotLoaded( const int nLineNumber )
{
	printf( "ERROR in the line %d:\n", nLineNumber );
	printf( "ERROR: Compiled grammar tables not loaded - load it first\n" );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DumpReduction( _ReductionPtr reduction, const int nLevel )
{
	const short nTag = reduction->GetTag();
	_bstr_t strRule = reduction->ParentRule->GetText();
	printf( "********** %s **********\n", (const char*)strRule );
	const int nTableIndex = reduction->ParentRule->GetTableIndex();
	STechnique technique;
	if ( nTableIndex == 3 ) 
		ParseTechnique( reduction, &technique );
	for ( short i = 0; i < reduction->TokenCount; ++i )
	{
		//_bstr_t str = parser->GetCurrentReduction()->
		_TokenPtr token = reduction->GetTokens( &i );
		_bstr_t strName = token->GetName();
		printf( "token %s", (const char*)strName );
		
		SymbolPtr symbol = token->GetParentSymbol();
		const short nSymbolTableIndex = symbol->TableIndex;

		variant_t var = token->GetData();
		switch ( var.vt ) 
		{
			case VT_DISPATCH:
				printf( "\n" );
				DumpReduction( var.pdispVal, nLevel + 1 );
				break;
			case VT_BSTR:
				{
					_bstr_t str = var.bstrVal;
					printf( "( %s )\n", (const char*)str );
				}
				break;
			default:
				{
					int a = 1;
				}
				break;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CShaderParser::DoneParsing( _ReductionPtr reduction )
{
	const int nTableIndex = reduction->ParentRule->GetTableIndex();
	if ( nTableIndex == 3 ) 
	{
		techniques.resize( techniques.size() + 1 );
		ParseTechnique( reduction, &(techniques.back()) );
	}
	else
	{
		for ( short i = 0; i < reduction->TokenCount; ++i )
		{
			_TokenPtr token = reduction->GetTokens( &i );
			variant_t var = token->GetData();
			if ( var.vt == VT_DISPATCH ) 
				DoneParsing( var.pdispVal );
		}
	}
	return true;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class TTokenVisitor>
void VisitTokens( _ReductionPtr reduction, TTokenVisitor &visitor )
{
	for ( short i = 0; i < reduction->TokenCount; ++i )
	{
		_TokenPtr token = reduction->GetTokens( &i );
		// CRAP{ for testing
		_bstr_t strName = token->GetName();
		printf( "token %s", (const char*)strName );
		// CRAP}
		variant_t var = token->GetData();
		if ( var.vt == VT_DISPATCH ) 
		{
			_ReductionPtr rule = var.pdispVal;
			const int nRuleIndex = rule->ParentRule->GetTableIndex();
			printf( " - rule (index = %d)\n", nRuleIndex );
			visitor( rule, nRuleIndex );
		}
		else
		{
			const int nSymbolIndex = token->GetTableIndex();
			printf( " - symbol (index = %d)\n", nSymbolIndex );
			visitor( token, nSymbolIndex );
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GetIntValue( _ReductionPtr reduction )
{
	for ( short i = 0; i < reduction->TokenCount; ++i )
	{
		_TokenPtr token = reduction->GetTokens( &i );
		const short nTableIndex = token->TableIndex;
		if ( (nTableIndex == SYMBOL_DECIMALLITERAL) || (nTableIndex == SYMBOL_HEXLITERAL) ) 
		{
			variant_t varTokenData = token->GetData();
			if ( varTokenData.vt == VT_BSTR ) 
			{
				int nNumber = 0;
				sscanf( (const char*)(bstr_t)varTokenData, "%i", &nNumber );
				return nNumber;
			}
			else
				return (long)varTokenData;
		}
	}
	return -1;
}
int GetIntValueFromRule( _ReductionPtr rule )
{
	for ( short j = 0; j < rule->TokenCount; ++j )
	{
		_TokenPtr token = rule->GetTokens( &j );
		variant_t var = token->GetData();
		if ( var.vt == VT_DISPATCH ) 
			return GetIntValue( var.pdispVal );
	}
	return -1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GetBoolValue( _ReductionPtr reduction )
{
	for ( short i = 0; i < reduction->TokenCount; ++i )
	{
		_TokenPtr token = reduction->GetTokens( &i );
		const short nTableIndex = token->TableIndex;
		switch ( nTableIndex ) 
		{
			case SYMBOL_FALSE:
				return false;
			case SYMBOL_TRUE:
				return true;
		}
	}
	return false;
}
bool GetBoolValueFromRule( _ReductionPtr rule )
{
	for ( short j = 0; j < rule->TokenCount; ++j )
	{
		_TokenPtr token = rule->GetTokens( &j );
		variant_t var = token->GetData();
		if ( var.vt == VT_DISPATCH ) 
			return GetBoolValue( var.pdispVal );
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** 
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SPair
{
	DWORD first, second;
};
DWORD FindVal( const DWORD dwVal, const SPair *pPair )
{
	while ( pPair->first != 0 ) 
	{
		if ( pPair->first == dwVal ) 
			return pPair->second;
		++pPair;
	}
	return -1;
}
int GetRuleIndex( _ReductionPtr rule )
{
	return rule->GetParentRule()->GetTableIndex();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** render states and stage props
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const SPair stencilActions[] = 
{
	{ RULE_STENCILACTION_KEEP			,	D3DSTENCILOP_KEEP			},
	{ RULE_STENCILACTION_ZERO			,	D3DSTENCILOP_ZERO			},
	{ RULE_STENCILACTION_REPLACE	,	D3DSTENCILOP_REPLACE  },
	{ RULE_STENCILACTION_INC			, D3DSTENCILOP_INCR			},
	{ RULE_STENCILACTION_DEC			, D3DSTENCILOP_DECR			},
	{ RULE_STENCILACTION_INCSAT		,	D3DSTENCILOP_INCRSAT	},
	{ RULE_STENCILACTION_DECSAT		,	D3DSTENCILOP_DECRSAT	},
	{ RULE_STENCILACTION_INVERT		,	D3DSTENCILOP_INVERT		},
	{ 0, 0 }
};
DWORD GetStencilAction( _ReductionPtr rule )
{
	const DWORD dwTableIndex = rule->GetParentRule()->GetTableIndex();
	return FindVal( dwTableIndex, stencilActions );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const SPair cullModes[] = 
{
	{ RULE_CULLMODE_NONE	, D3DCULL_NONE	},
	{ RULE_CULLMODE_CW		, D3DCULL_CW 		},
	{ RULE_CULLMODE_CCW		, D3DCULL_CCW		},
	{ 0, 0 }
};
DWORD GetCullModeFromRule( _ReductionPtr rule )
{
	const DWORD dwTableIndex = rule->GetParentRule()->GetTableIndex();
	for ( short j = 0; j < rule->TokenCount; ++j )
	{
		_TokenPtr token = rule->GetTokens( &j );
		variant_t var = token->GetData();
		if ( var.vt == VT_DISPATCH ) 
		{
			_ReductionPtr rule2 = var.pdispVal;
			const DWORD dwRule2Index = rule2->GetParentRule()->GetTableIndex();
			return FindVal( dwRule2Index, cullModes );
		}
	}
	return -1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const SPair cpmFuncs[] = 
{
	{ RULE_CMPFUNCCMP_LESS					, D3DCMP_LESS					},
	{ RULE_CMPFUNCCMP_LESSEQUAL			, D3DCMP_LESSEQUAL		},
	{ RULE_CMPFUNCCMP_GREATER				, D3DCMP_GREATER			},
	{ RULE_CMPFUNCCMP_GREATEREQUAL	, D3DCMP_GREATEREQUAL },
	{ RULE_CMPFUNCCMP_EQUAL					, D3DCMP_EQUAL				},
	{ RULE_CMPFUNCCMP_NOTEQUAL			, D3DCMP_NOTEQUAL			},
	{ RULE_CMPFUNCNOCMP_NEVER				, D3DCMP_NEVER				},
	{ RULE_CMPFUNCNOCMP_ALWAYS			, D3DCMP_ALWAYS				},
	{ 0, 0 }
};
DWORD GetCmpFunc( _ReductionPtr rule )
{
	const DWORD dwTableIndex = rule->GetParentRule()->GetTableIndex();
	return FindVal( dwTableIndex, cpmFuncs );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const SPair blendModes[] = 
{
	{ RULE_BLENDOP_ADD						, D3DBLENDOP_ADD					},
	{ RULE_BLENDOP_SUB						, D3DBLENDOP_SUBTRACT			},
	{ RULE_BLENDOP_REVSUB					, D3DBLENDOP_REVSUBTRACT	},
	{ RULE_BLENDOP_MIN						,	D3DBLENDOP_MIN					},
	{ RULE_BLENDOP_MAX						, D3DBLENDOP_MAX					},
	//
	{ RULE_BLENDMODES_ZERO				, D3DBLEND_ZERO						},
	{ RULE_BLENDMODES_ONE					, D3DBLEND_ONE						},
	{ RULE_BLENDMODES_SRCCOLOR		, D3DBLEND_SRCCOLOR				},
	{ RULE_BLENDMODES_INVSRCCOLOR	, D3DBLEND_INVSRCCOLOR		},
	{ RULE_BLENDMODES_SRCALPHA		, D3DBLEND_SRCALPHA				},
	{ RULE_BLENDMODES_INVSRCALPHA	, D3DBLEND_INVSRCALPHA		},
	{ RULE_BLENDMODES_DSTALPHA		, D3DBLEND_DESTALPHA			},
	{ RULE_BLENDMODES_INVDSTALPHA	, D3DBLEND_INVDESTALPHA		},
	{ RULE_BLENDMODES_DSTCOLOR		, D3DBLEND_DESTCOLOR			},
	{ RULE_BLENDMODES_INVDSTCOLOR	,	D3DBLEND_INVDESTCOLOR		},
	{ RULE_BLENDMODES_SRCALPHASAT	, D3DBLEND_SRCALPHASAT		},
	//
	{ 0, 0 }
};
DWORD GetBlendVal( _ReductionPtr rule )
{
	const DWORD dwTableIndex = rule->GetParentRule()->GetTableIndex();
	return FindVal( dwTableIndex, blendModes );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const SPair wrapModes[] = 
{
	{ RULE_TEXWRAPMODE_WRAP				, D3DTADDRESS_WRAP 			},
	{ RULE_TEXWRAPMODE_MIRROR			, D3DTADDRESS_MIRROR 		},
	{ RULE_TEXWRAPMODE_CLAMP			, D3DTADDRESS_CLAMP 		},
	{ RULE_TEXWRAPMODE_BORDER			, D3DTADDRESS_BORDER 		},
	{ RULE_TEXWRAPMODE_MIRRORONCE	, D3DTADDRESS_MIRRORONCE},
	{ 0, 0 }
};
DWORD GetWrapMode( _ReductionPtr rule )
{
	const DWORD dwTableIndex = rule->GetParentRule()->GetTableIndex();
	return FindVal( dwTableIndex, wrapModes );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const SPair filterModes[] = 
{
	{ RULE_TEXFILTERMODE_NONE						, D3DTEXF_NONE					},
	{ RULE_TEXFILTERMODE_POINT					, D3DTEXF_POINT					},
	{ RULE_TEXFILTERMODE_LINEAR					, D3DTEXF_LINEAR				},
	{ RULE_TEXFILTERMODE_ANISOTROPIC		, D3DTEXF_ANISOTROPIC		},
	{ RULE_TEXFILTERMODE_FLATCUBIC			, D3DTEXF_FLATCUBIC			},
	{ RULE_TEXFILTERMODE_GAUSSIANCUBIC	, D3DTEXF_GAUSSIANCUBIC },
	{ 0, 0 }
};
DWORD GetFilterMode( _ReductionPtr rule )
{
	const DWORD dwTableIndex = rule->GetParentRule()->GetTableIndex();
	return FindVal( dwTableIndex, filterModes );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const SPair transformFlagModes[] = 
{
	{ RULE_TRANSFORMFLAGS_DISABLE					, D3DTTFF_DISABLE 										},
	{ RULE_TRANSFORMFLAGS_COUNT1					, D3DTTFF_COUNT1 											},
	{ RULE_TRANSFORMFLAGS_COUNT2					, D3DTTFF_COUNT2 											},
	{ RULE_TRANSFORMFLAGS_COUNT3					, D3DTTFF_COUNT3 											},
	{ RULE_TRANSFORMFLAGS_COUNT4					, D3DTTFF_COUNT4 											},
	{ RULE_TRANSFORMFLAGS_PROJECTEDCOUNT1	, D3DTTFF_COUNT1 | D3DTTFF_PROJECTED	},
	{ RULE_TRANSFORMFLAGS_PROJECTEDCOUNT2	, D3DTTFF_COUNT2 | D3DTTFF_PROJECTED	},
	{ RULE_TRANSFORMFLAGS_PROJECTEDCOUNT3	, D3DTTFF_COUNT3 | D3DTTFF_PROJECTED	},
	{ RULE_TRANSFORMFLAGS_PROJECTEDCOUNT4	, D3DTTFF_COUNT4 | D3DTTFF_PROJECTED	},
	{ 0, 0 }
};
DWORD GetTransformFlagMode( _ReductionPtr rule )
{
	const DWORD dwTableIndex = rule->GetParentRule()->GetTableIndex();
	return FindVal( dwTableIndex, transformFlagModes );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const SPair texGenModes[] = 
{
	{ RULE_TEXGEN_CAMERASPACENORMAL						, D3DTSS_TCI_CAMERASPACENORMAL  				},
	{ RULE_TEXGEN_CAMERASPACEPOSITION					, D3DTSS_TCI_CAMERASPACEPOSITION  			},
	{ RULE_TEXGEN_CAMERASPACEREFLECTIONVECTOR	, D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR},
	{ 0, 0 }
};
DWORD GetTexGenMode( _ReductionPtr rule )
{
	const DWORD dwTableIndex = rule->GetParentRule()->GetTableIndex();
	return FindVal( dwTableIndex, texGenModes );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParseTexPropList( _ReductionPtr rule, std::vector<SShadeValue> &props )
{
	const int nRuleIndex = rule->GetParentRule()->GetTableIndex();
	if ( (nRuleIndex == RULE_TEXPROPLIST) || (nRuleIndex == RULE_TEXPROPLIST2) ) 
	{
		for ( short j = 0; j < rule->TokenCount; ++j )
		{
			_TokenPtr token = rule->GetTokens( &j );
			variant_t var = token->GetData();
			const int nTableIndex = token->GetTableIndex();
			switch ( nTableIndex ) 
			{
				case SYMBOL_TEXPROPLIST:
				case SYMBOL_TEXSINGLEPROP:
					ParseTexPropList( var.pdispVal, props );
					break;
			}
		}
		return;
	}
	//
	switch ( nRuleIndex )
	{
		case RULE_TEXSINGLEPROP_FILTER_LPARAN_COMMA_COMMA_RPARAN_SEMI:	// filter 3 args
		case RULE_TEXSINGLEPROP_FILTER_LPARAN_COMMA_RPARAN_SEMI:				// filter 2 args
			{
				DWORD dwArgs[3] = { -1, -1, -1 };
				int nCount = 0;
				const int nNumArgs = nRuleIndex == RULE_TEXSINGLEPROP_FILTER_LPARAN_COMMA_COMMA_RPARAN_SEMI ? 3 : 2;
				for ( short j = 0; j < rule->TokenCount; ++j )
				{
					_TokenPtr token = rule->GetTokens( &j );
					variant_t var = token->GetData();
					if ( var.vt == VT_DISPATCH ) 
						dwArgs[nCount++] = GetFilterMode( var.pdispVal );
				}
				//
				props.push_back( SShadeValue(D3DTSS_MINFILTER, dwArgs[0]) );
				props.push_back( SShadeValue(D3DTSS_MAGFILTER, dwArgs[1]) );
				if ( nNumArgs == 3 ) 
					props.push_back( SShadeValue(D3DTSS_MIPFILTER, dwArgs[2]) );
			}
			break;

		case RULE_TEXSINGLEPROP_ADDRESS_LPARAN_COMMA_COMMA_RPARAN_SEMI:	// wrap mode 3 args
		case RULE_TEXSINGLEPROP_ADDRESS_LPARAN_COMMA_RPARAN_SEMI:				// wrap mode 2 args
			{
				DWORD dwArgs[3] = { -1, -1, -1 };
				int nCount = 0;
				const int nNumArgs = nRuleIndex == RULE_TEXSINGLEPROP_FILTER_LPARAN_COMMA_COMMA_RPARAN_SEMI ? 3 : 2;
				for ( short j = 0; j < rule->TokenCount; ++j )
				{
					_TokenPtr token = rule->GetTokens( &j );
					variant_t var = token->GetData();
					if ( var.vt == VT_DISPATCH ) 
						dwArgs[nCount++] = GetWrapMode( var.pdispVal );
				}
				//
				props.push_back( SShadeValue(D3DTSS_ADDRESSU, dwArgs[0]) );
				props.push_back( SShadeValue(D3DTSS_ADDRESSV, dwArgs[1]) );
				if ( nNumArgs == 3 ) 
					props.push_back( SShadeValue(D3DTSS_ADDRESSW, dwArgs[2]) );
			}
			break;
		case RULE_TEXSINGLEPROP_TEXCOORDS_LPARAN_RPARAN_SEMI:				// <TexSingleProp> ::= texcoords '(' <Tex Gen> ')' ;
			props.push_back( SShadeValue(D3DTSS_TEXCOORDINDEX, GetIntValueFromRule(rule)) );
			props.push_back( SShadeValue(D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE) );
			break;
		case RULE_TEXSINGLEPROP_TEXCOORDS_LPARAN_COMMA_RPARAN_SEMI:	// <TexSingleProp> ::= texcoords '(' <Tex Gen> , <Transform Flags> ')' ;
			{
				for ( short j = 0; j < rule->TokenCount; ++j )
				{
					_TokenPtr token = rule->GetTokens( &j );
					variant_t var = token->GetData();
					if ( var.vt == VT_DISPATCH ) 
					{
						_ReductionPtr rule2 = var.pdispVal;
						const int nRule2Index = rule2->GetParentRule()->GetTableIndex();
						switch ( nRule2Index ) 
						{
							case RULE_TRANSFORMFLAGS_DISABLE:									// <Transform Flags> ::= Disable
							case RULE_TRANSFORMFLAGS_COUNT1:                  // <Transform Flags> ::= Count1
							case RULE_TRANSFORMFLAGS_COUNT2:                  // <Transform Flags> ::= Count2
							case RULE_TRANSFORMFLAGS_COUNT3:                  // <Transform Flags> ::= Count3
							case RULE_TRANSFORMFLAGS_COUNT4:                  // <Transform Flags> ::= Count4
							case RULE_TRANSFORMFLAGS_PROJECTEDCOUNT1:         // <Transform Flags> ::= ProjectedCount1
							case RULE_TRANSFORMFLAGS_PROJECTEDCOUNT2:         // <Transform Flags> ::= ProjectedCount2
							case RULE_TRANSFORMFLAGS_PROJECTEDCOUNT3:         // <Transform Flags> ::= ProjectedCount3
							case RULE_TRANSFORMFLAGS_PROJECTEDCOUNT4:         // <Transform Flags> ::= ProjectedCount4
								props.push_back( SShadeValue(D3DTSS_TEXTURETRANSFORMFLAGS, GetTransformFlagMode(rule2)) );
								break;
							case RULE_INTVAL_HEXLITERAL:
							case RULE_INTVAL_DECIMALLITERAL:
								props.push_back( SShadeValue(D3DTSS_TEXCOORDINDEX, GetIntValue(rule2)) );
								break;
							case RULE_TEXGEN_CAMERASPACENORMAL:								// <Tex Gen> ::= CameraSpaceNormal
							case RULE_TEXGEN_CAMERASPACEPOSITION:							// <Tex Gen> ::= CameraSpacePosition
							case RULE_TEXGEN_CAMERASPACEREFLECTIONVECTOR:			// <Tex Gen> ::= CameraSpaceReflectionVector
								props.push_back( SShadeValue(D3DTSS_TEXCOORDINDEX, GetTexGenMode(rule2)) );
								break;
						}
					}
				}
			}
			break;
	}
	//
}
class CParsePropertiesTokenVisitor
{ 
	std::vector< std::vector<SShadeValue> > &stages;
	std::vector<SShadeValue> &renderstates;
	bool bHasAlphaBlend;
	bool bHasStencil;
	//
	void ReadStencilArgs( _ReductionPtr &rule, const int nRuleIndex )
	{
		bHasStencil = true;
		int nCurrArg = 0;
		switch ( nRuleIndex ) 
		{
			case RULE_STENCILARGS_LPARAN_COMMA_RPARAN:	// <Stencil Args> ::= <Cmp Func Cmp> '(' <Stencil Ref Val> , <Stencil Mask> ')'
			case RULE_STENCILARGS_LPARAN_RPARAN:				// <Stencil Args> ::= <Cmp Func Cmp> '(' <Stencil Ref Val> ')'
				{
					for ( short j = 0; j < rule->TokenCount; ++j )
					{
						_TokenPtr token = rule->GetTokens( &j );
						variant_t var = token->GetData();
						if ( var.vt == VT_DISPATCH ) 
						{
							switch ( nCurrArg )
							{
								case 0:	// <Cmp Func Cmp>
									{
										const DWORD dwFunc = GetCmpFunc( var.pdispVal );
										renderstates.push_back( SShadeValue(D3DRS_STENCILFUNC, dwFunc) );
										++nCurrArg;
									}
									break;
								case 1:	// <Stencil Ref Val>
									{
										const DWORD dwVal = GetIntValue( var.pdispVal );
										renderstates.push_back( SShadeValue(D3DRS_STENCILREF, dwVal) );
										++nCurrArg;
									}
									break;
								case 2:	// <Stencil Mask>
									{
										const DWORD dwVal = GetIntValue( var.pdispVal );
										renderstates.push_back( SShadeValue(D3DRS_STENCILMASK, dwVal) );
										++nCurrArg;
									}
									break;
							}
						}
					}
				}
				break;
			case RULE_STENCILARGS:											// <Stencil Args> ::= <Cmp Func NoCmp>
				break;
			case RULE_STENCILARGS_NONE:									// <Stencil Args> ::= None
				bHasStencil = false;
				break;
		}
	}
	//
	void ReadStencilActions( _ReductionPtr &rule, const int nRuleTableIndex )
	{
		const DWORD dwOp[3] = { D3DRS_STENCILPASS, D3DRS_STENCILZFAIL, D3DRS_STENCILFAIL };
		for ( short j = 0, nCurrArg = 0; (j < rule->TokenCount) && (nCurrArg < 3); ++j )
		{
			_TokenPtr token = rule->GetTokens( &j );
			variant_t var = token->GetData();
			const int nTableIndex = token->GetTableIndex();
			if ( var.vt == VT_DISPATCH ) 
			{
				const DWORD dwVal = GetStencilAction( var.pdispVal );
				renderstates.push_back( SShadeValue(dwOp[nCurrArg++], dwVal) );
			}
		}
	}
public:
	CParsePropertiesTokenVisitor( SShaderDesc::SDefsBlock &_defsBlock )
		: stages( _defsBlock.tsses ), renderstates( _defsBlock.rses ), bHasAlphaBlend( false ), bHasStencil( false ) {  }
	~CParsePropertiesTokenVisitor()
	{
		renderstates.push_back( SShadeValue(D3DRS_ALPHABLENDENABLE, bHasAlphaBlend) );
		renderstates.push_back( SShadeValue(D3DRS_STENCILENABLE, bHasStencil) );
	}
	//
	void operator()( _ReductionPtr &rule, const int nRuleIndex )
	{
		switch ( nRuleIndex ) 
		{
			case RULE_TEXTUREPROPSBLOCK:							// <Texture Props Block> ::= <TexStageProps>
			case RULE_TEXTUREPROPSBLOCK2:							// <Texture Props Block> ::= <TexStageProps> <Texture Props Block>
			case RULE_PROPSBLOCK_PROPS_LBRACE_RBRACE:	// <Props Block> ::= props '{' <PropsList> '}'
			case RULE_PROPSLIST:											// <PropsList> ::= <PropSingle>
			case RULE_PROPSLIST2:											// <PropsList> ::= <PropSingle> <PropsList>
				VisitTokens( rule, *this );
				break;
			case RULE_TEXSTAGEPROPS_STAGEPROPS_LPARAN_RPARAN_LBRACE_RBRACE:	// <TexStageProps> ::= stageprops '(' <Int Val> ')' '{' <TexPropList> '}'
				{
					int nStage = -1;
					for ( short j = 0; j < rule->TokenCount; ++j )
					{
						_TokenPtr token = rule->GetTokens( &j );
						variant_t var = token->GetData();
						const int nTableIndex = token->GetTableIndex();
						switch ( nTableIndex ) 
						{
							case SYMBOL_INTVAL:
								nStage = GetIntValue( var.pdispVal );
								stages.resize( Max(int(stages.size()), nStage + 1) );
								break;
							case SYMBOL_TEXPROPLIST:
								ParseTexPropList( var.pdispVal, stages[nStage] );
								break;
						}
					}
				}
				break;

			case RULE_PROPBLEND_BLEND_EQ_LPARAN_COMMA_RPARAN_SEMI: // <Prop Blend> ::= blend = <Blend Op> '(' <Src Blend> , <Dst Blend> ')' ;
				{
					DWORD dwVals[3] = { -1, -1, -1 };
					int nCurrVal = 0;
					for ( short j = 0; j < rule->TokenCount; ++j )
					{
						_TokenPtr token = rule->GetTokens( &j );
						variant_t var = token->GetData();
						const int nTableIndex = token->GetTableIndex();
						if ( var.vt == VT_DISPATCH ) 
							dwVals[nCurrVal++] = GetBlendVal( var.pdispVal );
					}
					//
					renderstates.push_back( SShadeValue(D3DRS_BLENDOP, dwVals[0]) );
					renderstates.push_back( SShadeValue(D3DRS_SRCBLEND, dwVals[1]) );
					renderstates.push_back( SShadeValue(D3DRS_DESTBLEND, dwVals[2]) );
					bHasAlphaBlend = true;
				}
				break;

			case RULE_PROPDEPTH_DEPTH_EQ_SEMI:	// <Prop Depth> ::= depth = <Depth Func> ;
				{
					for ( short j = 0; j < rule->TokenCount; ++j )
					{
						_TokenPtr token = rule->GetTokens( &j );
						variant_t var = token->GetData();
						const int nTableIndex = token->GetTableIndex();
						if ( var.vt == VT_DISPATCH ) 
						{
							const DWORD dwDepthMode = GetCmpFunc( var.pdispVal );
							if ( dwDepthMode == -1 ) 
							{
								switch ( GetRuleIndex(var.pdispVal) )
								{
									case RULE_DEPTHFUNC_NOWRITE:	// <Depth Func> ::= NoWrite
										renderstates.push_back( SShadeValue(D3DRS_ZWRITEENABLE, false) );
										break;
									case RULE_DEPTHFUNC_NONE:			// <Depth Func> ::= None
										renderstates.push_back( SShadeValue(D3DRS_ZENABLE, D3DZB_FALSE) );
										break;
								}
							}
							else
							{
								renderstates.push_back( SShadeValue(D3DRS_ZWRITEENABLE, true) );
								renderstates.push_back( SShadeValue(D3DRS_ZENABLE, D3DZB_TRUE) );
								renderstates.push_back( SShadeValue(D3DRS_ZFUNC, dwDepthMode) );
							}
						}
					}
				}
				break;
				
			case RULE_PROPSPECULAR_SPECULAR_EQ_SEMI:	// <Prop Specular> ::= specular = <Bool Val> ;
				{
					const bool bEnable = GetBoolValueFromRule( rule );
					renderstates.push_back( SShadeValue(D3DRS_SPECULARENABLE, bEnable) );
				};
				break;
			case RULE_PROPLIGHTING_LIGHTING_EQ_SEMI:	// <Prop Lighting> ::= lighting = <Bool Val> ;
				{
					const bool bEnable = GetBoolValueFromRule( rule );
					renderstates.push_back( SShadeValue(D3DRS_LIGHTING, bEnable) );
				};
				break;
			case RULE_PROPCLIPPING_CLIPPING_EQ_SEMI:  // <Prop Clipping> ::= clipping = <Bool Val> ;
				{
					const bool bEnable = GetBoolValueFromRule( rule );
					renderstates.push_back( SShadeValue(D3DRS_LIGHTING, bEnable) );
				};
				break;
			case RULE_PROPTFACTOR_TFACTOR_EQ_SEMI:    // <Prop TFactor> ::= tfactor = <Int Val> ;
				{
					const int nVal = GetIntValueFromRule( rule );
					renderstates.push_back( SShadeValue(D3DRS_TEXTUREFACTOR, nVal) );
				}
				break;
			case RULE_PROPAMBIENT_AMBIENT_EQ_SEMI:    // <Prop Ambient> ::= ambient = <Int Val> ;
				{
					const int nVal = GetIntValueFromRule( rule );
					renderstates.push_back( SShadeValue(D3DRS_AMBIENT, nVal) );
				}
				break;
			case RULE_PROPCULL_CULL_EQ_SEMI:					// <Prop Cull> ::= cull = <Cull Mode> ;
				{
					const DWORD dwCullMode = GetCullModeFromRule( rule );
					renderstates.push_back( SShadeValue(D3DRS_CULLMODE, dwCullMode) );
				}
				break;
			case RULE_PROPSTENCIL_STENCIL_EQ_SEMI:									// <Prop Stencil> ::= stencil = <Stencil Args> ;
			case RULE_PROPSTENCIL_STENCIL_EQ_DO_LPARAN_RPARAN_SEMI: // <Prop Stencil> ::= stencil = <Stencil Args> do '(' <Stencil Actions> ')' ;
				for ( short j = 0; j < rule->TokenCount; ++j )
				{
					bHasStencil = true;
					_TokenPtr token = rule->GetTokens( &j );
					variant_t var = token->GetData();
					const int nTableIndex = token->GetTableIndex();
					if ( var.vt == VT_DISPATCH ) 
					{
						_ReductionPtr rule2 = var.pdispVal;
						const int nRule2TableIndex = rule2->GetParentRule()->GetTableIndex();
						switch ( nRule2TableIndex ) 
						{
							case RULE_STENCILARGS_LPARAN_COMMA_RPARAN:	// <Stencil Args> ::= <Cmp Func Cmp> '(' <Stencil Ref Val> , <Stencil Mask> ')'
							case RULE_STENCILARGS_LPARAN_RPARAN:				// <Stencil Args> ::= <Cmp Func Cmp> '(' <Stencil Ref Val> ')'
								ReadStencilArgs( rule2, nRule2TableIndex );
								break;
							case RULE_STENCILACTIONS_COMMA_COMMA:				// <Stencil Actions> ::= <Stencil Action> , <Stencil Action> , <Stencil Action>
								ReadStencilActions( rule2, nRule2TableIndex );
								break;
							case RULE_CMPFUNCNOCMP_ALWAYS:
							case RULE_CMPFUNCNOCMP_NEVER:
								{
									const DWORD dwFunc = GetCmpFunc( rule2 );
									renderstates.push_back( SShadeValue(D3DRS_STENCILFUNC, dwFunc) );
								}
								break;
						}
					}
				}
				break;
		}
	}
	void operator()( _TokenPtr &rule, const int nTokenIndex )
	{
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** color and alpha expression parsing
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//typedef std::pair<SYMBOL_CONSTANTS, D3DTEXTUREOP> SOpPair;
static const SPair ruleColorOperations[] = 
{
	{ RULE_EXP2_ADD								, D3DTOP_ADD								},
	{ RULE_EXP2_ADDSMOOTH					, D3DTOP_ADDSMOOTH					},
	{ RULE_EXP2_ADDSIGNED					, D3DTOP_ADDSIGNED					},
	{ RULE_EXP2_ADDSIGNED2X				, D3DTOP_ADDSIGNED2X				},
	{ RULE_EXP2_SUB								, D3DTOP_SUBTRACT						},
	{ RULE_EXP2_MUL								,	D3DTOP_MODULATE						},
	{ RULE_EXP2_MUL2X							, D3DTOP_MODULATE2X					},
	{ RULE_EXP2_MUL4X							, D3DTOP_MODULATE4X					},
	{ RULE_EXP2_BLENDCURRENTALPHA	, D3DTOP_BLENDCURRENTALPHA	},
	{ RULE_EXP2_BLENDTEXTUREALPHA	, D3DTOP_BLENDDIFFUSEALPHA	},
	{ RULE_EXP2_BLENDDIFFUSEALPHA	, D3DTOP_BLENDFACTORALPHA		},
	{ RULE_EXP2_BLENDFACTORALPHA	, D3DTOP_BLENDTEXTUREALPHA	},
	{ RULE_EXP2_DP3								, D3DTOP_DOTPRODUCT3				},
	{ RULE_EXP3_LERP							, D3DTOP_LERP								},
	{ RULE_EXP3_MAD								, D3DTOP_MULTIPLYADD				},
	{ 0, 0 }
};
DWORD GetD3DTOP( const DWORD dwOp )
{
	const SPair *pPair = ruleColorOperations;
	while ( pPair->first != 0 ) 
	{
		if ( pPair->first == dwOp ) 
			return pPair->second;
		++pPair;
	}
	return 0xffffffff;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DWORD GetArg( _ReductionPtr rule )
{
	for ( short i = 0; i < rule->TokenCount; ++i )
	{
		_TokenPtr token = rule->GetTokens( &i );
		const int nTableIndex = token->GetTableIndex();
		switch ( nTableIndex ) 
		{
			case SYMBOL_TEMP:
				return D3DTA_TEMP;
			case SYMBOL_TEX:
				return D3DTA_TEXTURE;
			case SYMBOL_TFACTOR:
				return D3DTA_TFACTOR;
			case SYMBOL_CDF:
				return D3DTA_DIFFUSE;
			case SYMBOL_CSP:
				return D3DTA_SPECULAR;
			case SYMBOL_CURR:
				return D3DTA_CURRENT;
		}
	}
	return -1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DWORD GetRuleSimpleArg( const int nTableIndex )
{
	switch ( nTableIndex ) 
	{
		case RULE_SIMPLEARG_CDF:
			return D3DTA_DIFFUSE;
		case RULE_SIMPLEARG_CSP:
			return D3DTA_SPECULAR;
		case RULE_SIMPLEARG_TFACTOR:
			return D3DTA_TFACTOR;
		case RULE_SIMPLEARG_CURR:
			return D3DTA_CURRENT;
		case RULE_SIMPLEARG_TEMP:
			return D3DTA_TEMP;
		case RULE_SIMPLEARG_TEX:
			return D3DTA_TEXTURE;
	}
	return D3DTA_CURRENT;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DWORD GetRuleComplexArg( _ReductionPtr &rule2, const int nRule2Index )
{
	const DWORD dwModifier = nRule2Index == RULE_ARG_REPLICATE_LPARAN_RPARAN ? D3DTA_ALPHAREPLICATE : D3DTA_COMPLEMENT;
	//
	for ( short j = 0; j < rule2->TokenCount; ++j )
	{
		_TokenPtr token2 = rule2->GetTokens( &j );
		variant_t var2 = token2->GetData();
		const int nTableIndex = token2->GetTableIndex();
		if ( (nTableIndex == SYMBOL_SIMPLEARG) && (var2.vt == VT_DISPATCH) )
			return GetArg( var2.pdispVal ) | dwModifier;
	}
	return -1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CParseColorAlphaTokenVisitor
{
	const bool bColor;
	std::vector< std::vector<SShadeValue> > &stages;
	int nCurrStage;
	DWORD dwOpFlags;
	//
	void GetFuncArgs( _ReductionPtr &rule, DWORD *dwArgs, const int nNumArgs )
	{
		for ( short i = 0, nCurrArg = 0; (i < rule->TokenCount) && (nCurrArg < nNumArgs); ++i )
		{
			_TokenPtr token = rule->GetTokens( &i );
			const int nTableIndex = token->GetTableIndex();
			switch ( nTableIndex ) 
			{
				case SYMBOL_ARG:
					{
						variant_t var = token->GetData();
						if ( var.vt == VT_DISPATCH ) 
						{
							_ReductionPtr rule2 = var.pdispVal;
							const int nRule2Index = rule2->ParentRule->GetTableIndex();
							switch ( nRule2Index )
							{
								case RULE_ARG_REPLICATE_LPARAN_RPARAN:	// replicate
								case RULE_ARG_COMPLEMENT_LPARAN_RPARAN:	// complement
									dwArgs[nCurrArg++] = GetRuleComplexArg( rule2, nRule2Index );
									break;
								case RULE_SIMPLEARG_CDF:
								case RULE_SIMPLEARG_CSP:
								case RULE_SIMPLEARG_TFACTOR:
								case RULE_SIMPLEARG_CURR:
								case RULE_SIMPLEARG_TEMP:
								case RULE_SIMPLEARG_TEX:
									dwArgs[nCurrArg++] = GetRuleSimpleArg( nRule2Index );
									break;
							}
						}
					}
					break;
				case SYMBOL_SIMPLEARG:
					{
						variant_t var = token->GetData();
						if ( var.vt == VT_DISPATCH ) 
						{
							_ReductionPtr rule2 = var.pdispVal;
								const int nRule2Index = rule2->ParentRule->GetTableIndex();
						}
					}
					break;
			}
		}
	}
	//
	void GetFunctionToken( _ReductionPtr &rule, std::vector<SShadeValue> &tokens )
	{
		DWORD dwOp = 0;
		// function
		{
			short i = 0;
			_TokenPtr token = rule->GetTokens( &i );
			variant_t var = token->GetData();
			if ( var.vt == VT_DISPATCH ) 
			{
				_ReductionPtr rule2 = var.pdispVal;
				const int nRule2Index = rule2->ParentRule->GetTableIndex();
				dwOp = GetD3DTOP( nRule2Index );
			}
		}
		// arguments
		DWORD dwArgs[3] = { -1, -1, -1 };
		int nNumArgs = 0;
		{
			short i = 1;
			_TokenPtr token = rule->GetTokens( &i );
			variant_t var = token->GetData();
			if ( var.vt == VT_DISPATCH ) 
			{
				_ReductionPtr rule2 = var.pdispVal;
				const int nRule2Index = rule2->ParentRule->GetTableIndex();
				switch ( nRule2Index ) 
				{
					case RULE_FUNCARGS2_LPARAN_COMMA_RPARAN:
						nNumArgs = 2;
						GetFuncArgs( rule2, dwArgs, nNumArgs );
						break;
					case RULE_FUNCARGS3_LPARAN_COMMA_COMMA_RPARAN:
						nNumArgs = 3;
						GetFuncArgs( rule2, dwArgs, nNumArgs );
						break;
				}
			}
		}
		// build D3D texture stage states
		tokens.reserve( tokens.size() + 1 + nNumArgs );
		tokens.push_back( SShadeValue(bColor ? D3DTSS_COLOROP : D3DTSS_ALPHAOP, dwOp) );
		//
		tokens.push_back( SShadeValue(bColor ? D3DTSS_COLORARG1 : D3DTSS_ALPHAARG1, dwArgs[0]) );
		tokens.push_back( SShadeValue(bColor ? D3DTSS_COLORARG2 : D3DTSS_ALPHAARG2, dwArgs[1]) );
		if ( nNumArgs == 3 ) 
			tokens.push_back( SShadeValue(bColor ? D3DTSS_COLORARG0 : D3DTSS_ALPHAARG0, dwArgs[2]) );
	}
public:
	CParseColorAlphaTokenVisitor( const bool _bColor, std::vector< std::vector<SShadeValue> > &_stages ) 
		: bColor( _bColor ), stages( _stages )
	{  
		stages.reserve( 8 );
		nCurrStage = 0;
		dwOpFlags = 0;
	}
	//
	const DWORD GetOpFlags() const { return dwOpFlags; }
	//
	void operator()( _ReductionPtr &rule, const int nRuleIndex )
	{
		switch ( nRuleIndex ) 
		{
			case RULE_EXPRESSION:
			case RULE_EXPRESSION_PIPE:
				VisitTokens( rule, *this );
				break;
			case RULE_EXP:	// 2 argument function
			case RULE_EXP2:	// 3 argument function
				dwOpFlags |= ( 1 << nCurrStage );
				// retrieve function
				stages.resize( Max(int(stages.size()), nCurrStage + 1) );
				GetFunctionToken( rule, stages[nCurrStage] );
				++nCurrStage;
				break;
			case RULE_SIMPLEARG_CDF:
			case RULE_SIMPLEARG_CSP:
			case RULE_SIMPLEARG_TFACTOR:
			case RULE_SIMPLEARG_CURR:
			case RULE_SIMPLEARG_TEMP:
			case RULE_SIMPLEARG_TEX:
				dwOpFlags |= ( 1 << nCurrStage );
				{
					const DWORD dwArg = GetRuleSimpleArg( nRuleIndex );
					stages.resize( Max(int(stages.size()), nCurrStage + 1) );
					stages[nCurrStage].push_back( SShadeValue(bColor ? D3DTSS_COLOROP : D3DTSS_ALPHAOP, D3DTOP_SELECTARG1) );
					stages[nCurrStage].push_back( SShadeValue(bColor ? D3DTSS_COLORARG1 : D3DTSS_ALPHAARG1, dwArg) );
					++nCurrStage;
				}
				break;
			case RULE_ARG_COMPLEMENT_LPARAN_RPARAN:
			case RULE_ARG_REPLICATE_LPARAN_RPARAN:
				dwOpFlags |= ( 1 << nCurrStage );
				{
					const DWORD dwArg = GetRuleComplexArg( rule, nRuleIndex );
					stages.resize( Max(int(stages.size()), nCurrStage + 1) );
					stages[nCurrStage].push_back( SShadeValue(bColor ? D3DTSS_COLOROP : D3DTSS_ALPHAOP, D3DTOP_SELECTARG1) );
					stages[nCurrStage].push_back( SShadeValue(bColor ? D3DTSS_COLORARG1 : D3DTSS_ALPHAARG1, dwArg) );
					++nCurrStage;
				}
				break;
		}
	}
	void operator()( _TokenPtr &rule, const int nTokenIndex )
	{
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** defs block parsing
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CParseDefsBlockTokenVisitor
{
	SShaderDesc::SDefsBlock &defsBlock;
	DWORD dwColorOpsFilled;								// flags for color ops stages
	DWORD dwAlphaOpsFilled;								// 
	//
	bool HasColorOp( const int nStage ) const { return ( dwColorOpsFilled & (1 << nStage) ) != 0; }
	bool HasAlphaOp( const int nStage ) const { return ( dwAlphaOpsFilled & (1 << nStage) ) != 0; }
public:
	CParseDefsBlockTokenVisitor( SShaderDesc::SDefsBlock &_defsBlock )
		: defsBlock( _defsBlock ), dwColorOpsFilled( 0 ), dwAlphaOpsFilled( 0 ) {  }
	~CParseDefsBlockTokenVisitor()
	{
		// fill 'intermediate' alpha and color stages
		if ( dwColorOpsFilled != dwAlphaOpsFilled ) 
		{
			for ( int i = 0; i < 32; ++i )
			{
				if ( HasColorOp(i) && !HasAlphaOp(i) ) 
					defsBlock.tsses[i].push_back( SShadeValue(D3DTSS_ALPHAOP, D3DTOP_SELECTARG1) );
				else if ( !HasColorOp(i) && HasAlphaOp(i) ) 
					defsBlock.tsses[i].push_back( SShadeValue(D3DTSS_COLOROP, D3DTOP_SELECTARG1) );
				else if ( !HasColorOp(i) && !HasAlphaOp(i) ) 
					break;
			}
		}
		// disable last stage
		if ( (dwColorOpsFilled | dwAlphaOpsFilled) != 0 ) 
		{
			const int nMSB = GetMSB( dwColorOpsFilled | dwAlphaOpsFilled ) + 1;
			defsBlock.tsses.resize( Max(int(defsBlock.tsses.size()), nMSB + 1) );
			defsBlock.tsses[nMSB].push_back( SShadeValue(D3DTSS_COLOROP, D3DTOP_DISABLE) );
			defsBlock.tsses[nMSB].push_back( SShadeValue(D3DTSS_ALPHAOP, D3DTOP_DISABLE) );
		}
	}
	//
	void operator()( _ReductionPtr &rule, const int nRuleIndex )
	{
		switch ( nRuleIndex ) 
		{
			case RULE_COLOROPS_COLOR_EQ_SEMI:	// color ops
			case RULE_ALPHAOPS_ALPHA_EQ_SEMI:	// alpha ops
				{
					CParseColorAlphaTokenVisitor visitor( nRuleIndex == RULE_COLOROPS_COLOR_EQ_SEMI, defsBlock.tsses );
					VisitTokens( rule, visitor );
					if ( nRuleIndex == RULE_COLOROPS_COLOR_EQ_SEMI ) 
						dwColorOpsFilled |= visitor.GetOpFlags();
					else
						dwAlphaOpsFilled |= visitor.GetOpFlags();
				}
				break;
			case RULE_PROPERTIES:
			case RULE_PROPERTIES2:
			case RULE_PROPERTIES3:
			case RULE_PROPERTIES4:
				VisitTokens( rule, CParsePropertiesTokenVisitor(defsBlock) );
				break;
		}
	}
	void operator()( _TokenPtr &rule, const int nTokenIndex )
	{
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CParseSetRestoreTokenVisitor
{
	SShaderDesc::SDefsBlock &defsBlock;
public:
	CParseSetRestoreTokenVisitor( SShaderDesc::SDefsBlock &_defsBlock )
		: defsBlock( _defsBlock ) {  }
	//
	void operator()( _ReductionPtr &rule, const int nRuleIndex )
	{
		//
		switch ( nRuleIndex ) 
		{
			case RULE_DEFSBLOCK:
			case RULE_DEFSBLOCK2:
				VisitTokens( rule, CParseDefsBlockTokenVisitor(defsBlock) );
				break;
		}
	}
	void operator()( _TokenPtr &rule, const int nTokenIndex )
	{
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** 
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CParseTechniqueTokenVisitor
{
	STechnique *pTechnique;
public:
	CParseTechniqueTokenVisitor( STechnique *_pTechnique )
		: pTechnique( _pTechnique ) 
	{  
		pTechnique->nNumStages = 0;
		pTechnique->nNumTextures = 0;
		pTechnique->nStencilDepth = 0;
	}
	//
	void operator()( _ReductionPtr &rule, const int nRuleIndex )
	{
		switch ( nRuleIndex ) 
		{
			case RULE_NUMTEXTURES_DECIMALLITERAL:	// <Num Textures> ::= DecimalLiteral
				pTechnique->nNumTextures = GetIntValue( rule );
				break;
			case RULE_NUMSTAGES_DECIMALLITERAL:		// <Num Stages> ::= DecimalLiteral
				pTechnique->nNumStages = GetIntValue( rule );
				break;
			case RULE_STENCIL_DECIMALLITERAL:			// <Stencil> ::= DecimalLiteral
				pTechnique->nStencilDepth = GetIntValue( rule );
				break;
			case RULE_TECHNIQUEDEF2:							// <Technique Def> ::= <Set Block> <Restore Block>
				VisitTokens( rule, *this );
				break;
			case RULE_SETBLOCK_SET_LBRACE_RBRACE:	// <Set Block> ::= set '{' <Defs Block> '}'
				VisitTokens( rule, CParseSetRestoreTokenVisitor(pTechnique->shader.blockSet) );
				break;
			case RULE_RESTOREBLOCK_RESTORE_LBRACE_RBRACE:	// <Restore Block> ::= restore '{' <Defs Block> '}'
				VisitTokens( rule, CParseSetRestoreTokenVisitor(pTechnique->shader.blockRestore) );
				break;
		}
	}
	void operator()( _TokenPtr &rule, const int nTokenIndex )
	{
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParseTechnique( _ReductionPtr reduction, STechnique *pTechnique )
{
	CParseTechniqueTokenVisitor visitor( pTechnique );
	VisitTokens( reduction, visitor );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** 
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CShaderParser::Save( const char *pszFileName )
{
	CPtr<IDataStream> pStream = CreateFileStream( pszFileName, STREAM_ACCESS_WRITE );
	if ( pStream == 0 ) 
		return false;
	CPtr<IStructureSaver> pSS = CreateStructureSaver( pStream, IStructureSaver::WRITE );
	if ( pSS == 0 ) 
		return false;
	CSaverAccessor saver = pSS;
	SShaderFileHeader header;
	saver.Add( 1, &header );
	saver.Add( 2, &techniques );
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
