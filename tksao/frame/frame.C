// Copyright (C) 1999-2016
// Smithsonian Astrophysical Observatory, Cambridge, MA, USA
// For conditions of distribution and use, see copyright notice in "copyright"

#include <tkInt.h>

#include "frame.h"
#include "fitsimage.h"
#include "ps.h"

#include "sigbus.h"

// Frame Member Functions

Frame::Frame(Tcl_Interp* i, Tk_Canvas c, Tk_Item* item) 
  : FrameBase(i,c,item)
{
  context = new Context();
  context->parent(this);

  currentContext = context;
  keyContext = context;
  keyContextSet =1;
  
  colormapData =NULL;

  cmapID = 1;
  bias = 0.5;
  contrast = 1.0;

  colorCount = 0;
  colorScale = NULL;
  colorCells = NULL;
}

Frame::~Frame()
{
  if (context)
    delete context;

  if (colorScale)
    delete colorScale;

  if (colorCells)
    delete [] colorCells;

  if (colormapData)
    delete [] colormapData;
}

unsigned char* Frame::blend(unsigned char* src, unsigned char* msk,
			    int width, int height)
{
  unsigned char* sptr = src; // 3 component
  unsigned char* mptr = msk; // 4 component, premultiplied

  for (int jj=0; jj<height; jj++)
    for (int ii=0; ii<width; ii++) {
      if (*(mptr+3)) {
	float aa = 1-maskAlpha;
	*sptr = *mptr++ + *sptr * aa;
	sptr++;
	*sptr = *mptr++ + *sptr * aa;
	sptr++;
	*sptr = *mptr++ + *sptr * aa;
	sptr++;
	mptr++;
      }
      else {
	mptr+=4;
	sptr+=3;
      }
    }

  return src;
}

unsigned char* Frame::fillImage(int width, int height, 
				Coord::InternalSystem sys)
{
  // img
  unsigned char* img = new unsigned char[width*height*3];
  {
    unsigned char* ptr = img;
    for (int jj=0; jj<height; jj++)
      for (int ii=0; ii<width; ii++) {
	*ptr++ = (unsigned char)bgColor->red;
	*ptr++ = (unsigned char)bgColor->green;
	*ptr++ = (unsigned char)bgColor->blue;
      }	
  }

  if (!context->cfits)
    return img;

  // basics
  int length = colorScale->size() - 1;
  const unsigned char* table = colorScale->psColors();

  FitsImage* sptr = context->cfits;
  int mosaic = isMosaic();

  // variable
  double* mm = sptr->matrixToData(sys).mm();
  FitsBound* params = sptr->getDataParams(context->secMode());
  int srcw = sptr->width();

  double ll = sptr->low();
  double hh = sptr->high();
  double diff = hh - ll;

  // main loop
  unsigned char* dest = img;

  SETSIGBUS
  for (long jj=0; jj<height; jj++) {
    for (long ii=0; ii<width; ii++, dest+=3) {
      if (mosaic) {
	sptr = context->cfits;

	mm = sptr->matrixToData(sys).mm();
	params = sptr->getDataParams(context->secMode());
	srcw = sptr->width();

	ll = sptr->low();
	hh = sptr->high();
	diff = hh - ll;
      }

      do {
	double xx = ii*mm[0] + jj*mm[3] + mm[6];
	double yy = ii*mm[1] + jj*mm[4] + mm[7];

	if (xx>=params->xmin && xx<params->xmax && 
	    yy>=params->ymin && yy<params->ymax) {
	  double value = sptr->getValueDouble(long(yy)*srcw + long(xx));

	  if (isfinite(diff) && isfinite(value)) {
	    if (value <= ll) {
	      *(dest+2) = table[0];
	      *(dest+1) = table[1];
	      *dest = table[2];
	    }
	    else if (value >= hh) {
	      *(dest+2) = table[length*3];
	      *(dest+1) = table[length*3+1];
	      *dest = table[length*3+2];
	    }
	    else {
	      int l = (int)(((value - ll)/diff * length) + .5);
	      *(dest+2) = table[l*3];
	      *(dest+1) = table[l*3+1];
	      *dest = table[l*3+2];
	    }
	  }
	  else {
	    *(dest+2) = nanColor->blue;
	    *(dest+1) = nanColor->green;
	    *dest = nanColor->red;
	  }

	  break;
	}
	else {
	  if (mosaic) {
	    sptr = sptr->nextMosaic();

	    if (sptr) {
	      mm = sptr->matrixToData(sys).mm();
	      params = sptr->getDataParams(context->secMode());
	      srcw = sptr->width();

	      ll = sptr->low();
	      hh = sptr->high();
	      diff = hh - ll;
	    }
	  }
	}
      }
      while (mosaic && sptr);
    }
  }
  CLEARSIGBUS

  if (img) {
    if (context->mask.head()) {
      FitsMask* mptr = context->mask.tail();
      while (mptr) {
	unsigned char* msk = fillMask(mptr, width, height, sys);
	blend(img,msk,width,height);
	delete [] msk;
	mptr = mptr->previous();
      }
    }
  }

  return img;
}

unsigned char* Frame::fillMask(FitsMask* msk, int width, int height,
			       Coord::InternalSystem sys)
{
  FitsImage* currentMsk = msk->current();
  XColor* maskColor = msk->color();
  int mark = msk->mark();

  // img
  unsigned char* img = new unsigned char[width*height*4];
  memset(img,0,width*height*4);

  if (!currentMsk)
    return img;

  // basics
  FitsImage* sptr = currentMsk;
  int mosaic = isMosaic();

  // variable
  double* mm = sptr->matrixToData(sys).mm();
  FitsBound* params = sptr->getDataParams(context->secMode());
  int srcw = sptr->width();

  // main loop
  unsigned char* dest = img;

  SETSIGBUS
  for (long jj=0; jj<height; jj++) {
    for (long ii=0; ii<width; ii++, dest+=4) {

      if (mosaic) {
	sptr = currentMsk;

	mm = sptr->matrixToData(sys).mm();
	params = sptr->getDataParams(context->secMode());
	srcw = sptr->width();
      }

      do {
	double xx = ii*mm[0] + jj*mm[3] + mm[6];
	double yy = ii*mm[1] + jj*mm[4] + mm[7];

	if (xx>=params->xmin && xx<params->xmax && 
	    yy>=params->ymin && yy<params->ymax) {
	  int value = sptr->getValueMask(long(yy)*srcw + long(xx));
       
	  if ((mark && value) || (!mark && !value)) {
	    *dest = ((unsigned char)maskColor->red)*maskAlpha;
	    *(dest+1) = ((unsigned char)maskColor->green)*maskAlpha;
	    *(dest+2) = ((unsigned char)maskColor->blue)*maskAlpha;
	    *(dest+3) = 1;
	  }

	  break;
	}
	else {
	  if (mosaic) {
	    sptr = sptr->nextMosaic();

	    if (sptr) {
	      mm = sptr->matrixToData(sys).mm();
	      params = sptr->getDataParams(context->secMode());
	      srcw = sptr->width();
	    }
	  }
	}
      }
      while (mosaic && sptr);
    }
  }
  CLEARSIGBUS

  return img;
}

int Frame::isIIS() 
{
  return context->cfits && context->cfits->isIIS();
}

void Frame::pushMatrices()
{
  Base::pushMatrices();

  // alway identity
  Matrix rgbToRef; 

  // now any masks
  FitsMask* msk = currentContext->mask.tail();
  while (msk) {
    FitsImage* mskimg = msk->mask();
    while (mskimg) {
      FitsImage* sptr = mskimg;
      while (sptr) {
	sptr->updateMatrices(rgbToRef, refToUser, userToWidget, 
			     widgetToCanvas, canvasToWindow);
	sptr = sptr->nextSlice();
      }
      mskimg = mskimg->nextMosaic();
    }

    msk = msk->previous();
  }
}

void Frame::pushMagnifierMatrices()
{
  Base::pushMagnifierMatrices();

  FitsMask* msk = context->mask.tail();
  while (msk) {
    FitsImage* mskimg = msk->mask();
    while (mskimg) {
      FitsImage* sptr = mskimg;
      while (sptr) {
	sptr->updateMagnifierMatrices(refToMagnifier);
	sptr = sptr->nextSlice();
      }
      mskimg = mskimg->nextMosaic();
    }
    msk = msk->previous();
  }
}

void Frame::pushPannerMatrices()
{
  Base::pushPannerMatrices();

  FitsMask* msk = context->mask.tail();
  while (msk) {
    FitsImage* mskimg = msk->mask();
    while (mskimg) {
      FitsImage* sptr = mskimg;
      while (sptr) {
	sptr->updatePannerMatrices(refToPanner);
	sptr = sptr->nextSlice();
      }
      mskimg = mskimg->nextMosaic();
    }
    msk = msk->previous();
  }
}

void Frame::pushPSMatrices(float scale, int width, int height)
{
  Base::pushPSMatrices(scale, width, height);

  Matrix mx = psMatrix(scale, width, height);
  FitsMask* msk = context->mask.tail();
  while (msk) {
    FitsImage* ptr = msk->current();
    while (ptr) {
      ptr->updatePS(mx);
      ptr = ptr->nextMosaic();
    }
    msk = msk->previous();
  }
}

void Frame::reset()
{
  cmapID = 1;
  bias = 0.5;
  contrast = 1.0;
  context->resetSecMode();
  context->updateClip();
  
  Base::reset();
}

void Frame::updateColorCells(unsigned char* cells, int cnt)
{
  colorCount = cnt;
  if (colorCells)
    delete [] colorCells;
  colorCells = new unsigned char[cnt*3];
  if (!colorCells) {
    internalError("Unable to Alloc colorCells");
    return;
  }
  memcpy(colorCells, cells, cnt*3);
}

void Frame::unloadFits()
{
  if (DebugPerf)
    cerr << "Frame::unloadFits()" << endl;

  // clean up from iis if needed
  if (isIIS())
    context->resetIIS();

  context->unload();

  FrameBase::unloadFits();
}

// Commands

void Frame::colormapCmd(int id, float b, float c, int i, 
				 unsigned char* cells, int cnt)
{
  cmapID = id;
  bias = b;
  contrast = c;
  invert = i;

  updateColorCells(cells, cnt);
  updateColorScale();
  update(BASE);
}

void Frame::colormapBeginCmd()
{
  // we need a colorScale before we can render
  if (!validColorScale())
    return;

  // we need some fits data
  // we assume the colorScale length will not change during motion calls
  if (!context->cfits)
    return;

  int width = options->width;
  int height = options->height;

  // Create XImage
  if (!(colormapXM = XGetImage(display, pixmap, 0, 0, 
			       width, height, AllPlanes, ZPixmap))) {
    internalError("Unable to Create Colormap XImage");
    return;
  }

  // Create Pixmap
  colormapPM = 
    Tk_GetPixmap(display, Tk_WindowId(tkwin), width, height, depth);
  if (!colormapPM) {
    internalError("Unable to Create Colormap Pixmap");
    return;
  }

  // colormapGCXOR
  colormapGCXOR = XCreateGC(display, Tk_WindowId(tkwin), 0, NULL);

  // Create table index array
  if (colormapData)
    delete [] colormapData;
  colormapData = new long[width*height];
  if (!colormapData) {
    internalError("Unable to alloc tmp data array");
    return;
  }

  // fill data array
  // basics
  int bytesPerPixel = colormapXM->bits_per_pixel/8;

  int length = colorScale->size() - 1;
  int last = length * bytesPerPixel;

  FitsImage* sptr = context->cfits;
  int mosaic = isMosaic();

  long* dest = colormapData;

  // variable
  double* mm = sptr->matrixToData(Coord::WIDGET).mm();
  FitsBound* params = sptr->getDataParams(context->secMode());
  int srcw = sptr->width();

  double ll = sptr->low();
  double hh = sptr->high();
  double diff = hh - ll;

  // main loop

  SETSIGBUS
  for (long jj=0; jj<height; jj++) {
    for (long ii=0; ii<width; ii++, dest++) {
      // default is bg
      *dest = -2; 

      if (mosaic) {
	sptr = context->cfits;

	mm = sptr->matrixToData(Coord::WIDGET).mm();
	params = sptr->getDataParams(context->secMode());
	srcw = sptr->width();

	ll = sptr->low();
	hh = sptr->high();
	diff = hh - ll;
      }

      do {
	double xx = ii*mm[0] + jj*mm[3] + mm[6];
	double yy = ii*mm[1] + jj*mm[4] + mm[7];

	if (xx>=params->xmin && xx<params->xmax && 
	    yy>=params->ymin && yy<params->ymax) {
	  double value = sptr->getValueDouble(long(yy)*srcw + long(xx));
       
	  if (isfinite(diff) && isfinite(value)) {
	    if (value <= ll)
	      *dest = 0;
	    else if (value >= hh)
	      *dest = last;
	    else
	      *dest = (int)(((value - ll)/diff * length) + .5)*bytesPerPixel;
	  }
	  else
	    *dest = -1;

	  break;
	}
	else {
	  if (mosaic) {
	    sptr = sptr->nextMosaic();

	    if (sptr) {
	      mm = sptr->matrixToData(Coord::WIDGET).mm();
	      params = sptr->getDataParams(context->secMode());
	      srcw = sptr->width();

	      ll = sptr->low();
	      hh = sptr->high();
	      diff = hh - ll;
	    }
	  }
	}
      }
      while (mosaic && sptr);
    }
  }
  CLEARSIGBUS
}

void Frame::colormapMotionCmd(int id, float b, float c, int i, 
				       unsigned char* cells, int cnt)
{
  // we need a colorScale before we can render
  if (!validColorScale())
    return;

  // first check for change
  if (cmapID == id && bias == b && contrast == c && invert == i && colorCells)
    return;

  // we got a change
  cmapID = id;
  bias = b;
  contrast = c;
  invert = i;

  updateColorCells(cells, cnt);
  updateColorScale();

  // if we have no data, stop now
  if (!context->cfits) 
    return;

  // clear ximage
  int& width = colormapXM->width;
  int& height = colormapXM->height;
  char* data = colormapXM->data;
  int bytesPerPixel = colormapXM->bits_per_pixel/8;
  int& bytesPerLine = colormapXM->bytes_per_line;

  const unsigned char* table = colorScale->colors();

  long* src = colormapData;
  for (long jj=0; jj<height; jj++) {
    // line may be padded at end
    char* dest = data + jj*bytesPerLine;

    for (long ii=0; ii<width; ii++, src++, dest+=bytesPerPixel)
      switch (*src) {
      case -1:
	memcpy(dest, nanTrueColor_, bytesPerPixel);
	break;
      case -2:
	memcpy(dest, bgTrueColor_, bytesPerPixel);
	break;
      default:
	memcpy(dest, table+(*src), bytesPerPixel);
	break;
      }
  }

  // XImage to Pixmap
  TkPutImage(NULL, 0, display, colormapPM, widgetGC, colormapXM, 
	     0, 0, 0, 0, width, height);

  // Display Pixmap
  Vector dd = Vector() * widgetToWindow;
  XCopyArea(display, colormapPM, Tk_WindowId(tkwin), colormapGCXOR, 0, 0, 
	    width, height, dd[0], dd[1]);

  // update panner
  updatePanner();
}

void Frame::colormapEndCmd()
{
  if (colormapXM) {
    XDestroyImage(colormapXM);
    colormapXM = NULL;
  }

  if (colormapPM) {
    Tk_FreePixmap(display, colormapPM);
    colormapPM = 0;
  }

  if (colormapGCXOR) {
    XFreeGC(display, colormapGCXOR);
    colormapGCXOR = 0;
  }

  if (colormapData) {
    delete [] colormapData;
    colormapData = NULL;
  }

  update(BASE); // always update
}

void Frame::getColorbarCmd()
{
  ostringstream str;
  str << cmapID << ' ' << bias << ' ' << contrast << ' ' << invert << ends;
  Tcl_AppendResult(interp, str.str().c_str(), NULL);
}

void Frame::getRGBChannelCmd()
{
  Tcl_AppendResult(interp, "red", NULL);
}

void Frame::getRGBViewCmd()
{
  Tcl_AppendResult(interp, "1 1 1", NULL);
}

void Frame::getRGBSystemCmd()
{
  Tcl_AppendResult(interp, "image", NULL);
}

void Frame::getTypeCmd()
{
  Tcl_AppendResult(interp, "base", NULL);
}

void Frame::iisCmd(int width, int height)
{
  unloadAllFits();

  context->setIIS();

  FitsImage* img = new FitsImageIIS(currentContext, interp, width, height);

  loadDone(currentContext->load(ALLOC, "", img, IMG),IMG);
}

void Frame::iisEraseCmd()
{
  if (context->cfits)
    ((FitsImageIIS*)context->cfits)->iisErase();
}

void Frame::iisGetCmd(char* dest, int xx, int yy, int dx, int dy)
{
  if (context->cfits) {
    char* buf = ((FitsImageIIS*)context->cfits)->iisGet(xx,yy,dx,dy);
    memcpy(dest, buf, dx*dy);
    delete [] buf;
  }
}

void Frame::iisSetCmd(const char* src, int xx, int yy, int dx, int dy)
{
  if (context->cfits)
    ((FitsImageIIS*)context->cfits)->iisSet(src, xx, yy, dx, dy);
}

void Frame::iisWCSCmd(const Matrix& mx, const Vector& z, int zt)
{
  if (context->cfits)
    ((FitsImageIIS*)context->cfits)->iisWCS(mx, z, zt);
}

void Frame::savePhotoCmd(const char* ph)
{
  FitsImage* fits = currentContext->cfits;
  if (!fits)
    return;

  // basics
  int length = colorScale->size() - 1;
  const unsigned char* table = colorScale->psColors();

  // variable
  FitsBound* params = fits->getDataParams(context->secMode());
  double ll = fits->low();
  double hh = fits->high();
  double diff = hh - ll;

  int width = params->xmax - params->xmin;
  int height = params->ymax - params->ymin;

  // photo
  if (*ph == '\0') {
    Tcl_AppendResult(interp, "bad image name ", NULL);
    return;
  }
  Tk_PhotoHandle photo = Tk_FindPhoto(interp, ph);
  if (!photo) {
    Tcl_AppendResult(interp, "bad image handle ", NULL);
    return;
  }
  if (Tk_PhotoSetSize(interp, photo, width, height) != TCL_OK) {
    Tcl_AppendResult(interp, "bad photo set size ", NULL);
    return;
  }    
  Tk_PhotoBlank(photo);
  Tk_PhotoImageBlock block;
  if (!Tk_PhotoGetImage(photo,&block)) {
    Tcl_AppendResult(interp, "bad image block ", NULL);
    return;
  }

  if (block.pixelSize<4) {
    Tcl_AppendResult(interp, "bad pixel size ", NULL);
    return;
  }

  // main loop
  SETSIGBUS
  unsigned char* dest = block.pixelPtr;
  for (long jj=params->ymax-1; jj>=params->ymin; jj--) {
    for (long ii=params->xmin; ii<params->xmax; ii++, dest += block.pixelSize) {
      double value = fits->getValueDouble(Vector(ii,jj));

      if (isfinite(diff) && isfinite(value)) {
	if (value <= ll) {
	  *(dest+block.offset[0]) = table[2];
	  *(dest+block.offset[1]) = table[1];
	  *(dest+block.offset[2]) = table[0];
	  *(dest+block.offset[3]) = 255;
	}
	else if (value >= hh) {
	  *(dest+block.offset[0]) = table[length*3+2];
	  *(dest+block.offset[1]) = table[length*3+1];
	  *(dest+block.offset[2]) = table[length*3];
	  *(dest+block.offset[3]) = 255;
	}
	else {
	  int l = (int)(((value - ll)/diff * length) + .5);
	  *(dest+block.offset[0]) = table[l*3+2];
	  *(dest+block.offset[1]) = table[l*3+1];
	  *(dest+block.offset[2]) = table[l*3];
	  *(dest+block.offset[3]) = 255;
	}
      }
      else {
	*(dest+block.offset[0]) = nanColor->red;
	*(dest+block.offset[1]) = nanColor->green;
	*(dest+block.offset[2]) = nanColor->blue;
	*(dest+block.offset[3]) = 255;
      }
    }
  }
  CLEARSIGBUS

  if (Tk_PhotoPutBlock(interp, photo, &block, 0, 0, width, height, 
			TK_PHOTO_COMPOSITE_SET) != TCL_OK) {
    Tcl_AppendResult(interp, "bad put block ", NULL);
    return;
  }
}



