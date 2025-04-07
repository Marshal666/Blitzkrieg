#include "StdAfx.h"

#include "ImageObjectFactory.h"

#include "ImageReal.h"
#include "ImageMMP.h"
#include "ImageProcessor.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CImageObjectFactory theImageObjectFactory;
CImageObjectFactory::CImageObjectFactory()
{
	REGISTER_CLASS( this, IMAGE_PROCESSOR, CImageProcessor );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** module descriptor and additional procedures
// **
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static SModuleDescriptor theModuleDescriptor( "Image", IMAGE_IMAGE, 0x0100, &theImageObjectFactory, 0 );
const SModuleDescriptor* STDCALL GetModuleDescriptor()
{
	return &theModuleDescriptor;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
