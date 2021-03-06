// Copyright (C) 1999-2016
// Smithsonian Astrophysical Observatory, Cambridge, MA, USA
// For conditions of distribution and use, see copyright notice in "copyright"

#ifndef __framebase_h__
#define __framebase_h__

#include "base.h"

class FrameBase : public Base {
protected:
  XImage* rotateSrcXM;       // rotate src ximage
  XImage* rotateDestXM;      // rotate dest ximage
  Pixmap rotatePM;           // rotate pixmap

  XImage* colormapXM;      // rotate dest ximage
  Pixmap colormapPM;       // rotate pixmap
  GC colormapGCXOR;        // GC for interactive rotation

  Vector iisLastCursor;      // iis cursor state info
				  
protected:
  double calcZoomPanner();
  void cancelDetach() {};

  void rotateMotion();

  void saveFitsResampleFits(OutFitsStream&);
  void saveFitsResampleKeyword(OutFitsStream&, FitsHead&);
  void setBinCursor();

  virtual void updateBin(const Matrix&);
  void updatePanner();

  void x11MagnifierCursor(const Vector&);

public:
  FrameBase(Tcl_Interp*, Tk_Canvas, Tk_Item*);
  virtual ~FrameBase();

  void setSlice(int,int);

  Vector mapFromRef(const Vector&, Coord::InternalSystem);
  Vector3d mapFromRef3d(const Vector& vv, Coord::InternalSystem sys) 
  {return mapFromRef(vv,sys);}
  Vector mapToRef(const Vector&, Coord::InternalSystem);
  Vector3d mapToRef3d(const Vector& vv, Coord::InternalSystem sys) 
  {return mapToRef(vv,sys);}

  // Bin Commands
  void binToFitCmd();

  // Block Commands
  void blockToFitCmd();

  // Coordinate Commands
  void getCursorCmd(Coord::InternalSystem);
  void getCursorCmd(Coord::CoordSystem, Coord::SkyFrame, Coord::SkyFormat);

  // Grid Commands
  void gridCmd(Coord::CoordSystem, Coord::SkyFrame, Coord::SkyFormat, 
	       Grid::GridType, const char*, const char*);

  // Fits Commands
  void saveFitsResample(OutFitsStream&);
  void saveFitsResampleFileCmd(const char*);
  void saveFitsResampleChannelCmd(const char*);
  void saveFitsResampleSocketCmd(int);

  // IIS Commands
  void iisCursorModeCmd(int);
  void iisGetCursorCmd();
  void iisGetFileNameCmd();
  void iisGetFileNameCmd(int);
  void iisGetFileNameCmd(const Vector&);
  void iisMessageCmd(const char*);
  void iisSetCursorCmd(const Vector&, Coord::InternalSystem);
  void iisSetCursorCmd(const Vector&, Coord::CoordSystem);
  void iisSetFileNameCmd(const char*);
  void iisSetFileNameCmd(const char*,int);
  void iisUpdateCmd() {updateNow(MATRIX);}

  // Pan Zoom Rotate Orient Commands
  void panCmd(const Vector&);
  void panCmd(const Vector&, const Vector&);
  void panCmd(const Vector&, Coord::CoordSystem, Coord::SkyFrame);
  void panToCmd(const Vector&);
  void panToCmd(const Vector&, Coord::CoordSystem, Coord::SkyFrame);
  void panBBoxCmd(const Vector&);
  void panEndCmd(const Vector&);
  void rotateBeginCmd();
  void rotateMotionCmd(double);
  void rotateEndCmd();
  void zoomAboutCmd(const Vector&, const Vector&);
  void zoomAboutCmd(const Vector&, const Vector&, Coord::CoordSystem, Coord::SkyFrame);
  void zoomToAboutCmd(const Vector&, const Vector&);
  void zoomToAboutCmd(const Vector&, const Vector&, Coord::CoordSystem, Coord::SkyFrame);
  void zoomToFitCmd(double);

  // 3d
  void get3dBorderCmd();
  void get3dBorderColorCmd();
  void get3dCompassCmd();
  void get3dCompassColorCmd();
  void get3dHighliteCmd();
  void get3dHighliteColorCmd();
  void get3dScaleCmd();
  void get3dViewCmd();
  void get3dViewPointCmd();
  void get3dRenderMethodCmd();
  void get3dRenderBackgroundCmd();
};

#endif
