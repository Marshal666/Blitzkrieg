#include "StdAfx.h"
#include "TerrainGenerator.h"
#include "PNoise.h"
#include "..\StreamIO\RandomGen.h"

const SfBmValues CHField::fBmDefVals[TG_MAX_ALG] =
{
  SfBmValues( TG_FBM, 1.0f, 2.0f, 7.0f, 0.0f, 0.0f, 1.0f, 0.0f, HF_SCALE ),
  SfBmValues( TG_MULTI, 0.5f, 2.0f, 4.0f, 1.0f, 0.0f, 1.0f, 0.0f, HF_SCALE ),
  SfBmValues( TG_HETERO, 0.5f, 2.0f, 7.0f, 0.0f, 0.0f, 1.0f, 0.0f, HF_SCALE ),
  SfBmValues( TG_HYBRID, 0.25f, 2.0f, 7.0f, 0.7f, 0.0f, 1.0f, 0.0f, HF_SCALE ),
  SfBmValues( TG_RIDGED, 1.0f, 2.0f, 4.0f, 1.0f, 2.0f, 1.0f, 0.0f, HF_SCALE ),
};

CHField::CHField() : dwDimX(0), dwDimY(0), bChanged(true), fGridStep(DEF_GRID_STEP)
{
}

CHField::CHField( int width, int height, float fGridStep, float val ) : bChanged(true)
{
  smoothFunc.Init( 1.0f, 0.0f );
  Init( width, height, fGridStep, val );
}

CHField::~CHField()
{
}

void CHField::Init( int width, int height, float _fGridStep, float val )
{
  fGridStep = _fGridStep;
  if ( width == dwDimX && height == dwDimY )
    return;
  dwDimX = width;
  dwDimY = height;
  hf.resize( width * height );
  memset( &hf[0], val, hf.size() * sizeof(float) );
  bChanged = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CHField::operator= ( const CHField &val )
{
  if ( dwDimX != val.dwDimX || dwDimY != val.dwDimY )
    Init( val.dwDimX, val.dwDimY, val.fGridStep, 0 );
  memcpy( &hf[0], &val.hf[0], hf.size() * sizeof(float) );
  bChanged = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedural fBm evaluated at "pt"
// Parameters:
//   lacunarity -  is the gap between successive frequencies
//   octaves    -  is the number of frequencies in the fBm
float CHField::FBm( CVec3 pt, float lacunarity, float octaves )
{
  int   i;
  float value = 0.0f;
  
  // inner loop of spectral construction
  for( i = 0; i < octaves; ++i )
  {
    value += NPerlinNoise::Noise3( pt ) * fBmExponents[i];
    pt *= lacunarity;
  }
  
  float remainder = octaves - (int)octaves;
  if ( remainder != 0.0f )
  {
    // add in ``octaves''  remainder
    // ``i''  and spatial freq. are preset in loop above
    value += remainder * NPerlinNoise::Noise3( pt ) * fBmExponents[i];
  }
  return value;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedural multifractal evaluated at "pt"
// Parameters:
//   lacunarity -  is the gap between successive frequencies
//   octaves    -  is the number of frequencies in the fBm
//   offset     -  is the zero offset, which determines multifractality
//
// Note: this tends to yield very small values, so the results need
//       to be scaled appropriately.
float CHField::Multifractal( CVec3 pt, float lacunarity, float octaves, float offset )
{
  int   i;
  float value = 1.0f;
  float frequency = 1.0f;
  
  // inner loop of multifractal construction
  for( i = 0; i < octaves; ++i )
  {
    value *= offset * frequency * NPerlinNoise::Noise3( pt );
    pt *= lacunarity;
  }
  
  float remainder = octaves - (int)octaves;
  if ( remainder != 0.0 )
    value += remainder * NPerlinNoise::Noise3( pt ) * fBmExponents[i];
  return value;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Heterogeneous procedural terrain function: stats by altitude method.
// Parameters:
//   lacunarity -  is the gap between successive frequencies
//   octaves    -  is the number of frequencies in the fBm
//   offset     -  raises the terrain from `sea level'
float CHField::HeteroTerrain( CVec3 pt, float lacunarity, float octaves, float offset )
{
  int   i;
  float increment;
  // first unscaled octave of function; later octaves are scaled
  float value = offset + NPerlinNoise::Noise3( pt );
  pt *= lacunarity;
  
  // spectral construction inner loop, where the fractal is built
  for( i = 1; i < octaves; ++i )
  {
    // obtain displaced noise value
    increment = NPerlinNoise::Noise3( pt ) + offset;
    // scale amplitude appropriately for this frequency
    increment *= fBmExponents[i];
    // scale increment by current `altitude' of function 
    increment *= value;
    // add increment to ``value''
    value += increment;
    // raise spatial frequency
    pt *= lacunarity;
  }
  
  float remainder = octaves - (int)octaves;
  if ( remainder != 0.0f )
  {
    increment = (NPerlinNoise::Noise3( pt ) + offset) * fBmExponents[i];
    value += remainder * increment * value;
  }
  
  return value;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Hybrid additive/multiplicative multifractal terrain model
// Some good parameter values to start with:
//   H:           0.25
//   offset:      0.7
float CHField::HybridMultifractal( CVec3 pt, float lacunarity, float octaves, float offset )
{
  int i;
  // get first octave of function 
  float ret = ( NPerlinNoise::Noise3( pt ) + offset ) * fBmExponents[0];
  float weight = ret;
  // increase frequency
  pt *= lacunarity;
  
  for( i = 1; i < octaves; ++i )
  {
    // prevent divergence
    weight = Min( weight, 1.0f );
    
    // get next higher frequency
    float signal = ( NPerlinNoise::Noise3( pt ) + offset ) * fBmExponents[i];
    // add it in, weighted by previous freq's local value
    ret += weight * signal;
    // update the (monotonically decreasing) weighting value
    // (this is why H must specify a high fractal dimension)
    weight *= signal;
    
    pt *= lacunarity;
  }
  
  float remainder = octaves - (int)octaves;
  if ( remainder != 0.0f )
    ret += remainder * NPerlinNoise::Noise3( pt ) * fBmExponents[i];
  
  return( ret/2.0f - 1.0f );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ridged multifractal terrain model.
// Some good parameter values to start with:
//     H:           1.0
//     offset:      1.0
//     gain:        2.0
float CHField::RidgedMultifractal( CVec3 pt, float lacunarity, float octaves, float offset, float gain )
{
  int i;
  // get absolute value of signal (this creates the ridges)
  float signal = fabs( NPerlinNoise::Noise3( pt ) );
  // invert and translate (note that "offset" should be ~= 1.0)
  signal = offset - signal;
  // square the signal, to increase "sharpness" of ridges
  signal *= signal;
  
  float ret = signal;
  float weight = 1.0;
  
  for( i = 1; i < octaves; ++i )
  {
    pt *= lacunarity;
    
    // weight successive contributions by previous signal
    weight = signal * gain;
    weight = Min( weight, 1.0f );
    weight = Max( weight, 0.0f );
    signal = fabs( NPerlinNoise::Noise3( pt ) );
    signal = offset - signal;
    signal *= signal;

    // weight the contribution
    signal *= weight;
    ret += signal * fBmExponents[i];
  }
  return( (ret-1.0)/2.0 );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CHField::InitFBmExp( float H, float lacunarity, float octaves )
{
  fBmExponents.resize( (int)octaves+1 );
  float frequency = 1.0;
  for(int i = 0; i <= octaves; ++i )
  {
		  // compute weight for each frequency
		  fBmExponents[i] = pow( frequency, -H );
      frequency *= lacunarity;
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CHField::GenTest( )
{
  int i, j, n = 0;
  CVec3 pt( 1.0f, 1.0f, 0.5f );
  float dl = 1.0f / Max( dwDimX, dwDimY );

  for( j = 0; j < dwDimY; ++j )
  {
    pt.x = 0;
    for( i = 0; i < dwDimX; ++i )
    {
      hf[n] = NPerlinNoise::Noise3( pt );
      pt.x += dl;
      ++n;
    }
    pt.y += dl;
  }
  bChanged = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Parameters:
//   H          -  fractal dim
//   lacunarity -  is the gap between successive frequencies
//   octaves    -  is the number of frequencies in the fBm
//   scale      -  влияет на характерный размер особенностей
void CHField::GenFBm( float H, float lacunarity, float octaves, float scale )
{
  InitFBmExp( H, lacunarity, octaves );
  int i, j, n = 0;
  CVec3 pt( 1.0f, 1.0f, 0.5f );
  float dl = 1.0f / (scale * Max( dwDimX, dwDimY ));

  for( j = 0; j < dwDimY; ++j )
  {
    pt.x = 1.0;
    for( i = 0; i < dwDimX; ++i )
    {
      hf[n] = FBm( pt, lacunarity, octaves );
      pt.x += dl;
      ++n;
    }
    pt.y += dl;
  }
  bChanged = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CHField::GenMultifractal( float H, float lacunarity, float octaves, float offset, float scale )
{
  InitFBmExp( H, lacunarity, octaves );
  int i, j, n = 0;
  CVec3 pt( 1.0f, 1.0f, 0.5f );
  float dl = 1.0f / (scale * Max( dwDimX, dwDimY ));

  for( j = 0; j < dwDimY; ++j )
  {
    pt.x = 1.0;
    for( i = 0; i < dwDimX; ++i )
    {
      hf[n] = Multifractal( pt, lacunarity, octaves, offset );
      pt.x += dl;
      ++n;
    }
    pt.y += dl;
  }
  bChanged = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CHField::GenHeteroTerrain( float H, float lacunarity, float octaves, float offset, float scale )
{
  InitFBmExp( H, lacunarity, octaves );
  int i, j, n = 0;
  CVec3 pt( 1.0f, 1.0f, 0.5f );
  float dl = 1.0f / (scale * Max( dwDimX, dwDimY ));

  for( j = 0; j < dwDimY; ++j )
  {
    pt.x = 1.0;
    for( i = 0; i < dwDimX; ++i )
    {
      hf[n] = HeteroTerrain( pt, lacunarity, octaves, offset );
      pt.x += dl;
      ++n;
    }
    pt.y += dl;
  }
  bChanged = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CHField::GenHybridMultifractal( float H, float lacunarity, float octaves, float offset, float scale )
{
  InitFBmExp( H, lacunarity, octaves );
  int i, j, n = 0;
  CVec3 pt( 1.0f, 1.0f, 0.5f );
  float dl = 1.0f / (scale * Max( dwDimX, dwDimY ));

  for( j = 0; j < dwDimY; ++j )
  {
    pt.x = 1.0;
    for( i = 0; i < dwDimX; ++i )
    {
      hf[n] = HybridMultifractal( pt, lacunarity, octaves, offset );
      pt.x += dl;
      ++n;
    }
    pt.y += dl;
  }
  bChanged = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CHField::GenRidgedMultifractal( float H, float lacunarity, float octaves, float offset, float gain, float scale )
{
  InitFBmExp( H, lacunarity, octaves );
  int i, j, n = 0;
  CVec3 pt( 1.0f, 1.0f, 0.5f );
  float dl = 1.0f / (scale * Max( dwDimX, dwDimY ));

  for( j = 0; j < dwDimY; ++j )
  {
    pt.x = 1.0;
    for( i = 0; i < dwDimX; ++i )
    {
      hf[n] = RidgedMultifractal( pt, lacunarity, octaves, offset, gain );
      pt.x += dl;
      ++n;
    }
    pt.y += dl;
  }
  bChanged = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CHField::Generate( const SfBmValues &vals )
{
  switch( vals.alg )
  {
  case TG_FBM:
    GenFBm( vals.h, vals.lacunarity, vals.octaves, vals.featSize );
    break;
  case TG_MULTI:
    GenMultifractal( vals.h, vals.lacunarity, vals.octaves, vals.offset, vals.featSize );
    break;
  case TG_HETERO:
    GenHeteroTerrain( vals.h, vals.lacunarity, vals.octaves, vals.offset, vals.featSize );
    break;
  case TG_HYBRID:
    GenHybridMultifractal( vals.h, vals.lacunarity, vals.octaves, vals.offset, vals.featSize );
    break;
  case TG_RIDGED:
    GenRidgedMultifractal( vals.h, vals.lacunarity, vals.octaves, vals.offset, vals.gain, vals.featSize );
    break;
  case TG_NULL:
    hf.assign( hf.size(), 0.0f );
    break;
  }
  float dh = MaxHeight() - MinHeight();
  if ( dh > FP_EPSILON )
    Scale( vals.fRange / dh );
  Translate( vals.fBaseHeight - AveHeight() );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Изменить масштаб высот
void CHField::Scale( float scale )
{
  for( int i = 0; i < hf.size(); ++i )
    hf[i] *= scale;
  bChanged = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
  float grfSigma  = 1;
  float grfInvSig = 1;
  float grv1, grv2, grs;
  bool  grphase = false;
};

void InitGR( float sigma )
{
  grfSigma  = sigma;
  grfInvSig = 1.0f / sigma;
  grphase   = false;
}

float GaussRand()
{
  float x;
  
  if( !grphase ) {
    do {
      float u1 = Random( 0.0f, 1.0f );
      float u2 = Random( 0.0f, 1.0f );
      grv1 = 2 * u1 - 1;
      grv2 = 2 * u2 - 1;
      grs = grv1 * grv1 + grv2 * grv2;
    }
    while( grs >= 1 || grs == 0);
    x = grv1 * sqrt( -2 * log( grs ) / grs );
  } 
  else
    x = grv2 * sqrt( -2 * log( grs ) / grs );
  grphase = !grphase;

  return grfSigma * x;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float CHField::AveHeight() const
{
  float ret = 0;

  for( int i = 0; i < hf.size(); ++i )
    ret += hf[i];

  return ret / hf.size();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CHField::Translate( float shift )
{
  for( int i = 0; i < hf.size(); ++i )
    hf[i] += shift;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float CHField::MinHeight() const
{
  if ( hf.empty() )
    return 0;
  float ret = hf[0];

  for( int i = 1; i < hf.size(); ++i )
    ret = Min( ret, hf[i] );

  return ret;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float CHField::MaxHeight() const
{
  if ( hf.empty() )
    return 0;
  float ret = hf[0];

  for( int i = 1; i < hf.size(); ++i )
    ret = Max( ret, hf[i] );

  return ret;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Объект является суммой op1, op2
// сам объект может быть одним из операндов
void CHField::Sum( const CHField &op1, const CHField &op2 )
{
  DWORD w = Min( op1.Width(), op2.Width() );
  DWORD h = Min( op1.Height(), op2.Height() );

  Init( w, h, op1.fGridStep );
  int i, j, n = 0;

  for( j = 0; j < h; ++j )
    for( i = 0; i < w; ++i )
    {
      hf[n] = op1.H( i, j ) + op2.H( i, j );
      ++n;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float CHField::Volume()
{
  float vol = 0;
  for( int i = 0; i < hf.size(); ++i )
    vol += H( i );

  return vol;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CHField::Pow( float exp )
{
  if ( hf.empty() )
    return;
  float range = AltitudeRange( 0, 0 );
  float min = MinHeight();

  Translate( -min );
  for( int i = 0; i < hf.size(); ++i )
    H( i ) = pow( H( i ), exp );
  Scale( range / AltitudeRange( 0, 0 ) );
  Translate( min );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float CHField::AltitudeRange( float *pMin, float *pMax ) const
{
  if ( hf.empty() )
    return 0;

  float min, max;
  min = max = hf[0];

  for( int i = 1; i < hf.size(); ++i )
  {
    min = Min( min, hf[i] );
    max = Max( max, hf[i] );
  }
	//
	if ( pMin ) *pMin = min;
	if ( pMax ) *pMax = max;
	//
  return max - min;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CHField& CHField::operator- ()
{
  for( int i = 0; i < hf.size(); ++i )
    hf[i] = -hf[i];
  return *this;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Возвращает нормаль в точке (х, у)
// карта высот всегда начинается в точке (0, 0), расстояние между
// узловыми точками - fGridStep
// интерполяция между ними с помощью бета-сплайнов
CVec3 CHField::GetNormal( float x, float y ) const
{
  float invStep = 1.0f / fGridStep;
  int nx = int(x * invStep);
  int ny = int(y * invStep);
  float u = (x - nx * fGridStep) * invStep;
  float v = (y - ny * fGridStep) * invStep;

  nx -= 1;
  ny -= 1;
  CVec3 pts[16];

  int i, j, n = 0;
  float fy = ny * fGridStep;

  // Если область интерполяции вылазит за пределы массива получаем высоту с проверкой
  if ( nx < 0 || ny < 0 || nx + 4 > dwDimX || ny + 4 > dwDimY )
  {
    for( j = 0; j < 4; ++j )
    {
      float fx = nx * fGridStep;
      for( i = 0; i < 4; ++i )
      {
        pts[n] = CVec3( fx, fy, HCheck( nx + i, ny + j ));
        ++n;
        fx += fGridStep;
      }
      fy += fGridStep;
    }
  }
  else
  {
    int ind;
    for( j = 0; j < 4; ++j )
    {
      ind = (ny + j) * dwDimX + nx;
      float fx = nx * fGridStep;
      for( i = 0; i < 4; ++i )
      {
        pts[n] = CVec3( fx, fy, H( ind ));
        fx += fGridStep;
        ++n;
        ++ind;
      }
      fy += fGridStep;
    }
  }
  CVec3 ptDx, ptDy;
  smoothFunc.Derivative( ptDx, ptDy, u, v, pts );
  CVec3 norm = ptDx ^ ptDy;
  Normalize( &norm );

  return norm;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float CHField::GetHApprox( float x, float y ) const
{
  float invStep = 1.0f / fGridStep;
  int nx = int(x * invStep);
  int ny = int(y * invStep);
  float u = (x - nx * fGridStep) * invStep;
  float v = (y - ny * fGridStep) * invStep;

  nx -= 1;
  ny -= 1;
  CVec3 pts[16];

  int i, j, n = 0;
  float fy = ny * fGridStep;

  // Если область интерполяции вылазит за пределы массива получаем высоту с проверкой
  if ( nx < 0 || ny < 0 || nx + 4 > dwDimX || ny + 4 > dwDimY )
  {
    for( j = 0; j < 4; ++j )
    {
      float fx = nx * fGridStep;
      for( i = 0; i < 4; ++i )
      {
        pts[n] = CVec3( fx, fy, HCheck( nx + i, ny + j ));
        ++n;
        fx += fGridStep;
      }
      fy += fGridStep;
    }
  }
  else
  {
    int ind;
    for( j = 0; j < 4; ++j )
    {
      ind = (ny + j) * dwDimX + nx;
      float fx = nx * fGridStep;
      for( i = 0; i < 4; ++i )
      {
        pts[n] = CVec3( fx, fy, H( ind ));
        fx += fGridStep;
        ++n;
        ++ind;
      }
      fy += fGridStep;
    }
  }
  return smoothFunc.Value( u, v, pts ).z;
}
