// Copyright (C) 1999-2016
// Smithsonian Astrophysical Observatory, Cambridge, MA, USA
// For conditions of distribution and use, see copyright notice in "copyright"

#include <tk.h>

#include "circle.h"
#include "fitsimage.h"

Circle::Circle(Base* p, const Vector& ctr, double r)
  : BaseEllipse(p, ctr, 0)
{
  numAnnuli_ = 1;
  annuli_ = new Vector[1];
  annuli_[0] = Vector(r,r);

  strcpy(type_, "circle");
  numHandle = 4;

  updateBBox();
}

Circle::Circle(Base* p, const Vector& ctr,
	       double r, 
	       const char* clr, int* dsh, 
	       int wth, const char* fnt, const char* txt, 
	       unsigned short prop, const char* cmt,
	       const List<Tag>& tg, const List<CallBack>& cb)
  : BaseEllipse(p, ctr, 0, clr, dsh, wth, fnt, txt, prop, cmt, tg, cb)
{
  numAnnuli_ = 1;
  annuli_ = new Vector[numAnnuli_];
  annuli_[0] = Vector(r,r);

  strcpy(type_, "circle");
  numHandle = 4;

  updateBBox();
}

Circle::Circle(const Circle& a) : BaseEllipse(a) {}

void Circle::edit(const Vector& v, int h)
{
  Matrix mm = bckMatrix();

  // calc dist between edge of circle and handle
  double d = annuli_[0].length() - annuli_[0][0];
  double r = (v * mm).length() - d;
  annuli_[0] = Vector(r,r);
  
  updateBBox();
  doCallBack(CallBack::EDITCB);
}

void Circle::analysis(AnalysisTask mm, int which)
{
  switch (mm) {
  case HISTOGRAM:
    if (!analysisHistogram_ && which) {
      addCallBack(CallBack::MOVECB, analysisHistogramCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::EDITCB, analysisHistogramCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::DELETECB, analysisHistogramCB_[1], 
		  parent->options->cmdName);
    }
    if (analysisHistogram_ && !which) {
      deleteCallBack(CallBack::MOVECB, analysisHistogramCB_[0]);
      deleteCallBack(CallBack::EDITCB, analysisHistogramCB_[0]);
      deleteCallBack(CallBack::DELETECB, analysisHistogramCB_[1]);
    }

    analysisHistogram_ = which;
    break;
  case PLOT3D:
    if (!analysisPlot3d_ && which) {
      addCallBack(CallBack::MOVECB, analysisPlot3dCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::EDITCB, analysisPlot3dCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::DELETECB, analysisPlot3dCB_[1], 
		  parent->options->cmdName);
    }
    if (analysisPlot3d_ && !which) {
      deleteCallBack(CallBack::MOVECB, analysisPlot3dCB_[0]);
      deleteCallBack(CallBack::EDITCB, analysisPlot3dCB_[0]);
      deleteCallBack(CallBack::DELETECB, analysisPlot3dCB_[1]);
    }

    analysisPlot3d_ = which;
    break;
  case STATS:
    if (!analysisStats_ && which) {
      addCallBack(CallBack::MOVECB, analysisStatsCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::EDITCB, analysisStatsCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::UPDATECB, analysisStatsCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::DELETECB, analysisStatsCB_[1], 
		  parent->options->cmdName);
    }
    if (analysisStats_ && !which) {
      deleteCallBack(CallBack::MOVECB, analysisStatsCB_[0]);
      deleteCallBack(CallBack::EDITCB, analysisStatsCB_[0]);
      deleteCallBack(CallBack::UPDATECB, analysisStatsCB_[0]);
      deleteCallBack(CallBack::DELETECB, analysisStatsCB_[1]);
    }

    analysisStats_ = which;
    break;
  default:
    // na
    break;
  }
}

void Circle::analysisHistogram(char* xname, char* yname, int num)
{
  double* x;
  double* y;
  Vector ll = -annuli_[0] * Translate(center);
  Vector ur =  annuli_[0] * Translate(center);
  BBox bb(ll,ur) ;
  parent->markerAnalysisHistogram(this, &x, &y, bb, num);
  analysisXYResult(xname, yname, x, y, num+1);
}

void Circle::analysisPlot3d(char* xname, char* yname, 
			    Coord::CoordSystem sys, 
			    Marker::AnalysisMethod method)
{
  double* x;
  double* y;
  Vector ll = -annuli_[0] * Translate(center);
  Vector ur =  annuli_[0] * Translate(center);
  BBox bb(ll,ur) ;
  int num = parent->markerAnalysisPlot3d(this, &x, &y, bb, sys, method);
  analysisXYResult(xname, yname, x, y, num);
}

void Circle::analysisStats(Coord::CoordSystem sys, Coord::SkyFrame sky)
{
  ostringstream str;
  Vector ll = -annuli_[0] * Translate(center);
  Vector ur =  annuli_[0] * Translate(center);
  BBox bb(ll,ur) ;
  parent->markerAnalysisStats(this, str, bb, sys, sky);
  str << ends;
  Tcl_AppendResult(parent->interp, str.str().c_str(), NULL);
}

// list

void Circle::list(ostream& str, Coord::CoordSystem sys, Coord::SkyFrame sky,
		  Coord::SkyFormat format, int conj, int strip)
{
  FitsImage* ptr = parent->findFits(sys,center);
  listPre(str, sys, sky, ptr, strip, 0);
  
  switch (sys) {
  case Coord::IMAGE:
  case Coord::PHYSICAL:
  case Coord::DETECTOR:
  case Coord::AMPLIFIER:
    listNonCel(ptr, str, sys);
    break;
  default:
    if (ptr->hasWCSCel(sys)) {
      double rr = ptr->mapLenFromRef(annuli_[0][0],sys,Coord::ARCSEC);
      switch (format) {
      case Coord::DEGREES:
	{
	  Vector vv = ptr->mapFromRef(center,sys,sky);
	  str << type_ << '(' 
	      << setprecision(10) << vv << ',' 
	      << setprecision(3) << fixed << rr << '"' << ')';
	  str.unsetf(ios_base::floatfield);
	}
	break;
      case Coord::SEXAGESIMAL:
	listRADEC(ptr,center,sys,sky,format);
	str << type_ << '(' 
	    << ra << ',' << dec << ',' 
	    << setprecision(3) << fixed << rr << '"' << ')';
	str.unsetf(ios_base::floatfield);
	break;
      }
    }
    else
      listNonCel(ptr, str, sys);
  }

  listPost(str, conj, strip);
}

void Circle::listNonCel(FitsImage* ptr, ostream& str, Coord::CoordSystem sys)
{
  Vector vv = ptr->mapFromRef(center,sys);
  double rr = ptr->mapLenFromRef(annuli_[0][0],sys);
  str << type_ << '(' << setprecision(8) << vv << ',' << rr <<  ')';
}

void Circle::listXML(ostream& str, Coord::CoordSystem sys, Coord::SkyFrame sky, 
		     Coord::SkyFormat format)
{
  FitsImage* ptr = parent->findFits(sys,center);

  XMLRowInit();
  XMLRow(XMLSHAPE,type_);

  XMLRowCenter(ptr,sys,sky,format);
  XMLRowRadiusX(ptr,sys,annuli_[0]);

  XMLRowProps(ptr,sys);
  XMLRowEnd(str);
}

void Circle::listCiao(ostream& str, Coord::CoordSystem sys, int strip)
{
  FitsImage* ptr = parent->findFits();
  listCiaoPre(str);

  switch (sys) {
  case Coord::IMAGE:
  case Coord::PHYSICAL:
  case Coord::DETECTOR:
  case Coord::AMPLIFIER:
    {
      Vector vv = ptr->mapFromRef(center,Coord::PHYSICAL);
      double rr = ptr->mapLenFromRef(annuli_[0][0],Coord::PHYSICAL);
      str << type_ << '(' << setprecision(8) << vv << ',' << rr << ')';
    }
    break;
  default:
    if (ptr->hasWCSCel(sys)) {
      listRADEC(ptr,center,sys,Coord::FK5,Coord::SEXAGESIMAL);
      double rr = ptr->mapLenFromRef(annuli_[0][0],sys,Coord::ARCMIN);
      str << type_ << '(' 
	  << ra << ',' << dec << ',' 
	  << setprecision(5) << fixed << rr << '\'' << ')';
      str.unsetf(ios_base::floatfield);
    }
  }

  listCiaoPost(str, strip);
}

void Circle::listSAOtng(ostream& str, 
			Coord::CoordSystem sys, Coord::SkyFrame sky,
			Coord::SkyFormat format, int strip)
{
  FitsImage* ptr = parent->findFits();
  listSAOtngPre(str, strip);

  switch (sys) {
  case Coord::IMAGE:
  case Coord::PHYSICAL:
  case Coord::DETECTOR:
  case Coord::AMPLIFIER:
    {
      Vector vv = ptr->mapFromRef(center,Coord::IMAGE);
      double rr = ptr->mapLenFromRef(annuli_[0][0],Coord::IMAGE);
      str << type_ << '(' << setprecision(8) << vv << ',' << rr << ')';
    }
    break;
  default:
    if (ptr->hasWCSCel(sys)) {
      double rr = ptr->mapLenFromRef(annuli_[0][0],Coord::IMAGE);
      switch (format) {
      case Coord::DEGREES:
	{
	  Vector vv = ptr->mapFromRef(center,sys,sky);
	  str << type_ << '(' 
	      << setprecision(10) << vv << ',' 
	      << setprecision(8) << rr << ')';
	}
	break;
      case Coord::SEXAGESIMAL:
	listRADEC(ptr,center,sys,sky,format);
	str << type_ << '(' 
	    << ra << ',' << dec << ',' 
	    << setprecision(8) << rr << ')';
	break;
      }
    }
  }

  listSAOtngPost(str,strip);
}

void Circle::listPros(ostream& str, Coord::CoordSystem sys, Coord::SkyFrame sky,
		      Coord::SkyFormat format, int strip)
{
  FitsImage* ptr = parent->findFits();

  switch (sys) {
  case Coord::IMAGE:
  case Coord::DETECTOR:
  case Coord::AMPLIFIER:
    sys = Coord::IMAGE;
  case Coord::PHYSICAL:
    {
      Vector vv = ptr->mapFromRef(center,sys);
      double rr = ptr->mapLenFromRef(annuli_[0][0],Coord::IMAGE);
      coord.listProsCoordSystem(str,sys,sky);
      str << "; " << type_ << ' ' << setprecision(8) << vv << ' ' << rr;
    }
    break;
  default:
    if (ptr->hasWCSCel(sys)) {
      double rr = ptr->mapLenFromRef(annuli_[0][0],sys,Coord::ARCSEC);
      switch (format) {
      case Coord::DEGREES:
	{
	  Vector vv = ptr->mapFromRef(center,sys,sky);
	  coord.listProsCoordSystem(str,sys,sky);
	  str << "; " << type_ << ' ' 
	      << setprecision(10) << setunit('d') << vv << ' ' 
	      << setprecision(3) << fixed << rr << '"';
	  str.unsetf(ios_base::floatfield);
	}
	break;
      case Coord::SEXAGESIMAL:
	listRADECPros(ptr,center,sys,sky,format);
	coord.listProsCoordSystem(str,sys,sky);
	str << "; " << type_ << ' ' 
	    << ra << ' ' << dec << ' ' 
	    << setprecision(3) << fixed << rr << '"';
	str.unsetf(ios_base::floatfield);
	break;
      }
    }
  }

  listProsPost(str, strip);
}

void Circle::listSAOimage(ostream& str, int strip)
{
  FitsImage* ptr = parent->findFits();
  listSAOimagePre(str);

  Vector vv = ptr->mapFromRef(center,Coord::IMAGE);
  str << type_ << '(' << setprecision(8) << vv << ',' << annuli_[0][0] << ')';

  listSAOimagePost(str, strip);
}

// special composite funtionallity

void Circle::setComposite(const Matrix& mx, double aa)
{
  center *= mx;
  updateBBox();
}

