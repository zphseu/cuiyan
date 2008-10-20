#if !defined(__PIE_H__)
#define __PIE_H__

#include <string>
using namespace std;
#include "BarLine.h"

template <class T> 
class CPie : public CBarLine<T>
{
public:
    void CutPie(T percentvalues[], int numvalues, string *labels, string* names, bool offsetflag = true);
    void CutPies(T percentvalues[], int numvalues, string *labels, string* names, int npie, bool offsetflag = true);
	void CutPie3D(T percentvalues[], int numvalues, string *labels, bool offsetflag = true){ ; }
protected:
	virtual void Legend(COLORREF cr, int Index, const char* Name);
	void PieceOfPie(double x, double y, double radius, double showpercentage,
		            double AngleS, double AngleE, bool offsetflag, bool bHalf);
};

template <class T> 
void CPie<T>::CutPie(T percentvalues[], int numvalues, string* labels, string* names, bool offsetflag)
{
    double x, y, radius;

	double* sum = new double[numvalues + 1];
    sum[0] = 0.0;
    for(int i = 0; i < numvalues; i++)
		sum[i+1] = sum[i] + percentvalues[i];

    x = PX / 2.;
    y = PY / 2.; 
    radius = ((x > y) ? y : x) * 0.75; 
//	x = (GL + GR) / 2. - m_lM / 4.;
	x = (GL + GR) / 2. - m_lM;
    y = (GT + GB + m_bM) / 2.; 
    HBRUSH  hBrush, hBrold;
	HPEN hPen,hPold;
	double offset = 2*3.14159*(sum[0]/sum[numvalues] + sum[1]/sum[numvalues]) / 2; 
	m_LogFont.lfHeight = (int)(m_Size.cx / -30.0);
	if (m_LogFont.lfHeight > -10) m_LogFont.lfHeight = -10;
	m_LogFont.lfWeight     = 500;
	m_LogFont.lfOrientation= 0;
	m_LogFont.lfEscapement = 0;
	m_Font = ::CreateFontIndirect(&m_LogFont);
//	offset = 0.0;
	if (m_Font)
	{
		HFONT hOldFont = (HFONT)::SelectObject(m_hDC, m_Font);
		int bm = ::SetBkMode(m_hDC, TRANSPARENT);

		if (sum[numvalues] < 0.00001)
		{
			if (m_bEnableLegend)
			{
				for(i = 0; i<numvalues; i++)
				{
					hBrush = ::CreateSolidBrush(crTable[i + 1]);
					hBrold = (HBRUSH)::SelectObject(m_hDC, hBrush);
					hPen = ::CreatePen(0,0,crTable[i + 1]);
					hPold = (HPEN)::SelectObject(m_hDC,hPen);
					
					Legend(crTable[i + 1], i + 1, labels[i].c_str());
				
					::SelectObject(m_hDC,hPold);
					::SelectObject(m_hDC, hBrold);
					::DeleteObject(hBrush);
					::DeleteObject(hPen);
				}
			}

			
			m_LogFont.lfHeight *= 3;
			m_LogFont.lfHeight /= 2;
			::DeleteObject(m_Font);
			m_Font = ::CreateFontIndirect(&m_LogFont);
			HFONT hOldFont1 = (HFONT)::SelectObject(m_hDC, m_Font);
			::SetTextColor(m_hDC, RGB(0,0,0));
			SetStringAlign(CENTER, LEFT);
			PrintString(int(x), int(y), 0, "数据总和为零！");
			PrintString(int(x), int(y + int(radius * 1.4)), 0, names->c_str());
			::SetBkMode(m_hDC, bm);
			::SelectObject(m_hDC, hOldFont);
			::DeleteObject(m_Font);
			delete[] sum;
			return;
		}

		bool bMoreHalf;
		for(i = 0; i<numvalues; i++)
		{    
			hBrush = ::CreateSolidBrush(crTable[i + 1]);
			hBrold = (HBRUSH)::SelectObject(m_hDC, hBrush);
			hPen = ::CreatePen(0,0,crTable[i + 1]);
			hPold = (HPEN)::SelectObject(m_hDC,hPen);
			::SetTextColor(m_hDC, crTable[i + 1] );          
			double AngleS = 2*3.14159*sum[i]/sum[numvalues] - offset;
			double AngleE = 2*3.14159*sum[i+1]/sum[numvalues] - offset;

			while ((AngleE - AngleS) > 2*3.14159*0.99)
				AngleE -= 2*3.14159;
			
			//bMoreHalf = (sum[i+1] > sum[i]);
			bMoreHalf = percentvalues[i] / sum[numvalues] > 0.01;
			PieceOfPie(x, y, radius, 100 * percentvalues[i] / sum[numvalues],
					   AngleS, AngleE, offsetflag, bMoreHalf);

			if (m_bEnableLegend)
				Legend(crTable[i + 1], i + 1, labels[i].c_str());
			::SelectObject(m_hDC,hPold);
			::SelectObject(m_hDC, hBrold);
			::DeleteObject(hBrush);
			::DeleteObject(hPen);
		}
		m_LogFont.lfHeight *= 3;
		m_LogFont.lfHeight /= 2;
		::DeleteObject(m_Font);
		m_Font = ::CreateFontIndirect(&m_LogFont);
		HFONT hOldFont1 = (HFONT)::SelectObject(m_hDC, m_Font);
		::SetTextColor(m_hDC, RGB(0,0,0));
		SetStringAlign(CENTER, LEFT);
		PrintString(int(x), int(y + int(radius * 1.4)), 0, names->c_str());
		::SetBkMode(m_hDC, bm);
		::SelectObject(m_hDC, hOldFont);
		::DeleteObject(m_Font);
	}
	delete []sum;
}

template <class T> 
void CPie<T>::PieceOfPie(double x, double y, double radius, double showpercentage,
		                 double AngleS, double AngleE, bool offsetflag, bool bMoreHalf)
{
	int xoffset, yoffset;
    double labelloc, lradius;
    char buffer[10];                     
    const double PIE_OFFSET = m_Size.cx / 20.;

    //Offset lable radius by a factor of 1.2. This value
    //is dependent on the size of charaters you are using.
    if( offsetflag )
      lradius = radius * 1.15;
    else
      lradius = radius * 1.1; 
    labelloc = ( AngleS+AngleE ) / 2;
    int x1 = (int)(x-radius);
    int y1 = (int)(y-radius);
    int x2 = (int)(x+radius);
    int y2 = (int)(y+radius);
    int x3 = (int)(x+radius*cos(AngleS));
    int y3 = (int)(y-radius*sin(AngleS));
    int x4 = (int)(x+radius*cos(AngleE));
    int y4 = (int)(y-radius*sin(AngleE));
	CPoint Point[2];
	Point[0].x=(int)x;
	Point[0].y=(int)y;
/*	if(x3==x4)
		x4-=((sin(AngleS)>0)? 1:-1);
	if(y3==y4)
		y4-=((cos(AngleS)>0)? 1:-1);
*/   if(offsetflag)
      {
        xoffset = (int)(cos(labelloc)*PIE_OFFSET);
        yoffset = (int)(sin(labelloc)*PIE_OFFSET);
		if(x3 == x4 && y3 == y4 && !bMoreHalf)
		{
			::MoveToEx(m_hDC,Point[0].x+xoffset,Point[0].y-yoffset,&Point[0]);
			::LineTo(m_hDC,x3+xoffset,y3-yoffset);
		}
		else
		Pie(m_hDC, x1+xoffset, y1-yoffset, x2+xoffset, y2-yoffset,
            x3+xoffset, y3-yoffset, x4+xoffset, y4-yoffset);
      }
    else if(x3 == x4 && y3 == y4 && !bMoreHalf)
		{
			::MoveToEx(m_hDC,Point[0].x,Point[0].y,&Point[0]);
			::LineTo(m_hDC,x3,y3);
		}
	else
      Pie(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4 );
 
	x += cos(labelloc) * lradius;
    y -= sin(labelloc) * lradius;
	labelloc = labelloc / PiV / 2;
    //Set text justification depending upon location of pieslice
    if(labelloc >= 5./6 || labelloc < 1./6)
      SetStringAlign(LEFT, CENTER);
    else if(labelloc >= 1./6 && labelloc < 1./3)
      SetStringAlign(CENTER, BOTTOM);
    else if(labelloc >= 1./3 && labelloc <2./3)
      SetStringAlign(RIGHT, CENTER);
    else
      SetStringAlign(CENTER, TOP);
    sprintf(buffer, "%3.1lf%%", showpercentage);

	PrintString((int)x, (int)y, 0, buffer);
}

template<class T>
void CPie<T>::Legend(COLORREF cr, int Index, const char* Name)
{
	int n  = (m_Rect.right - GR) / 20 + 1;
	int xb = GR - m_rM / 2 - 20;
	int xe = GR - 20;
	int y  = GT - 2 * Index * m_LogFont.lfHeight / 2;
	int y1 = y + m_LogFont.lfHeight / 3;
	int y2 = y - m_LogFont.lfHeight / 3;
	::Rectangle(m_hDC, xb, y1, xe, y2);
	::SetTextColor(m_hDC, cr); 
	int bm  = ::SetBkMode(m_hDC, TRANSPARENT);
	SetStringAlign(LEFT, CENTER);
	PrintString(xe + n, y, 0, Name);
	::SetBkMode(m_hDC, bm);
}

template<class T>
void CPie<T>::CutPies(T percentvalues[], int numvalues, string* labels, string* names, int npie, bool offsetflag)
{
	int width;
	width = m_Rect.right / npie;
	CRect rect;
	rect.left = width / 8;
	rect.top = 0;
	rect.bottom = m_Rect.bottom;
	rect.right = rect.left + width;
	RecalcRects(rect);
	bool bLegend = m_bEnableLegend;
	T* pPer = percentvalues;
	string* pname = names;
	for(int i = 0; i < npie - 1; i++)
	{
		m_bEnableLegend = false;
		CutPie(pPer,numvalues,labels,pname,offsetflag);
		rect.left = (i + 1) * width + (npie - i - 1) * width / 32;
		rect.right = rect.left + width;
		RecalcRects(rect);
		pPer += numvalues;
		pname++;
	}

	m_bEnableLegend = bLegend;
	CutPie(pPer,numvalues,labels,pname,offsetflag);
}
#endif
