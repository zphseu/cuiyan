/**************************************************************
 *  Filename:    fgmap.h
 *  Copyright:   Shanghai Baosight Software Co., Ltd.
 *
 *  Description: fast gmap implementation file.
 *
 *  @author:     cuiyan
 *  @version     03/08/2004  cuiyan  Initial Version
**************************************************************/


#pragma warning(disable : 4786)

#include "fgmap.h"
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;


V _fgmap::getshortpath(char *nds, ids &lids, ids &nids)
{
	ids nods;
	str2ids(nds, nods);
	
	if (nods.size() < 2)
		return 0;
	
	V len = 0;
	lids.clear();
	nids.clear();
	nids.push_back(nods[0]);
	for (int i = 0; i < nods.size() - 1; i++)
	{
		_fgmap::ids lk, nd;
		int l = getshortpath(nods[i], nods[i+1], lk, nd);
		len += l;
		
		if (l == 0 || len > max_v) {
			lids.clear();
			nids.clear();
			len = 0;
			break;
		}
		
		copy (lk.begin(), lk.end(), back_inserter( lids ) );
		copy (nd.begin() + 1, nd.end(), back_inserter( nids ) );
	}
	
	return len;
}

V _fgmap::getshortpath(I o, I d, ids &lids, ids &nids, vs *pnv)
{
	if (o == d) 
		return 0;

	typedef map<I, _ghf> nodeghfs;
	nodeghfs open, close;
	V len = 0;
	
	open[o] = _ghf(0, h(o, o));
	
	while (!open.empty())
	{
		nodeghfs::iterator _x = open.begin();	//_x->first 为最先考虑的节点
		for (nodeghfs::iterator _y = open.begin(); _y != open.end(); _y++)	{
			if (_y->second.f < _x->second.f)
				_x = _y;
		}
		
		_ghf orgghf = open[_x->first];
		I curNd = _x->first;
		open.erase(_x->first);
		
		if (curNd != d) {
			_tnode &ndls = nds[curNd];
			for (int i = 0; i < ndls.lk.size(); i++)
			{
				I linkId = ndls.lk[i];
				
				if (nrlk.find(I2TOII(orgghf.sl, linkId)) != nrlk.end())
					break;
				
				_tlink &link = lks[linkId];	// 当前出向边
				nodeghfs::iterator _topen = open.find(link.dp);
				nodeghfs::iterator _tclose = close.find(link.dp);
				
				_ghf ghf(orgghf.g + lw[linkId], h(o, link.dp), linkId);//当前节点估价信息
				
				if ( _topen != open.end() )	{
					if (ghf.f < _topen->second.f) {
						open[_topen->first] = ghf;
					}
					
				} else if (_tclose != close.end()) {
					if (ghf.f < _tclose->second.f) {
						close.erase(link.dp);
						open[link.dp] = ghf;
					}
				} else {
					open[link.dp] = ghf;
				}
				
				close[curNd] = orgghf;
			}
		}	else	{
			nids.clear();
			lids.clear();
			nids.push_back(d);
			I l = orgghf.sl;
			I p = o + 1;
			while (p != o)	{
				p = lks[l].op;
				nids.push_back(p);
				lids.push_back(l);
				len += lw[l];
				l = close[p].sl;
			}

			if (len > max_v) {
				nids.clear();
				lids.clear();
				len = 0;
			}	else	{
				reverse(nids.begin(), nids.end());
				reverse(lids.begin(), lids.end());
				if (pnv)	{
					vs& v = *pnv;
					v.clear();
					v.push_back(0);
					for (int i = 0; i < lids.size(); i++)
						v.push_back(v[i] + lw[lids[i]]);
				}
			}
			break;
		}
	}
	
	return len;
}

void _fgmap::set_ilink(I aIndex, V aOp, V aDp, V aW)
{
	lks[aIndex] = _tlink(aOp, aDp, aW);
	lw[aIndex] = aW;
	ids &ndlk = nds[lks[aIndex].op].lk;
	if (find(ndlk.begin(), ndlk.end(), aIndex) == ndlk.end())
		ndlk.push_back(aIndex);
}

void _fgmap::set_inode(I aIndex, V aX, V aY, V aZ)
{
	nds[aIndex] = _tnode(aX, aY, aZ);
}

void _fgmap::set_link(long isize, V *pOp, V *pDp, V* pW)
{
	if (pOp != NULL && pDp != NULL && pW != NULL)
		for (int i = 0; i < isize; i++, pOp++, pDp++, pW++)
			set_ilink(i, *pOp, *pDp, *pW);
}

void _fgmap::set_node(long isize, V *pX, V *pY, V* pZ)
{
	if (pX != NULL && pY != NULL && pZ != NULL)
		for (int i = 0; i < isize; i++, pX++, pY++, pZ++)
			set_ilink(i, *pX, *pY, *pZ);
}

void _fgmap::set_w(long isize, V* pw) 
{	
	if (pw != NULL)
		for (int i = 0; i < isize; i++, pw++) 
			lw[i] = *pw;
}

void _fgmap::set_iw(I index, V w) 
{
	lw[index] = w;
}

bool _fgmap::str2ids(char *str, ids &aids)
{
	stringstream sout(str);
	istream_iterator <I> is (sout);
	istream_iterator <I> eof;
	copy (is, eof, back_inserter( aids ) );
	return true;
}

string _fgmap::mids2str(mids& sp)
{
	string s ("");
	for (_fgmap::mids::iterator _x = sp.begin(); _x != sp.end(); _x++)	{
		stringstream sout;
		ostream_iterator <I> os (sout, " ");
		copy(_x->begin (), _x->end(), os);
		s += sout.str();
		s += ';';
	}
	return s;
}

string _fgmap::ids2str(ids& sp)
{
	stringstream sout;
	ostream_iterator <I> os (sout, " ");
	copy(sp.begin (), sp.end(), os);
	return sout.str();
}

string _fgmap::vs2str(vs& v)
{
	stringstream sout;
	ostream_iterator <V> os (sout, " ");
	copy(v.begin (), v.end(), os);
	return sout.str();
}

void _fgmap::set_inrlk(I l1, I l2)	
{ 
	if (lks[l1].dp == lks[l2].op)
		nrlk.insert(I2TOII(l1, l2));
}

void _fgmap::set_nrlk(long isize, I *p1, I *p2)
{ 
	for (int i = 0; i < isize; i++, p1++, p2++) 
		set_inrlk(*p1, *p2);
}

// #include <fstream>
// bool _fgmap::getmshortpath(I o, I d, int n, mids &mlids, mids &mnids)
// {	
// 	pC pc;
// 	QQ Q;
// 	V len = getshortpath(o, d, pc.l, pc.n, &pc.vn);
// 	if (len == 0) return false;
// 	Q.insert(pair<V, pC>(len, pc));
// 
// 	ofstream of("E:\\temp\\tmp\\mspath.cal"); //cycy
// 	ostream_iterator<I> sout(of, " ");	//cycy
// 
// 	for (int i = 0; i < n && !Q.empty(); i++) {
// 		pC curpc = Q.begin()->second;
// 
// 		of << "path  " << i << "\nlength=" << Q.begin()->first << " nodes:"; //cycy
// 		copy(curpc.n.begin(), curpc.n.end(), sout);	//cycy
//  		of << "in link: ";
//  		copy(curpc.e1.begin(), curpc.e1.end(), sout);
//  		of << "out link: ";
//  		copy(curpc.e2.begin(), curpc.e2.end(), sout);
// 		of << "vn :";
// 		copy(pc.vn.begin(), pc.vn.end(), sout);
// 		Q.erase(Q.begin());
// 		mnids.push_back(curpc.n);
// 		mlids.push_back(curpc.l);
// 		ids &curNP = *mnids.rbegin();
// 		ids &curLP = *mlids.rbegin();
// 
// 		ids::reverse_iterator _b = curLP.rbegin();
// 		ids::reverse_iterator _nb = curNP.rbegin(), _nt = _nb;
// 		vs::reverse_iterator _vb = curpc.vn.rbegin(), _vt = _vb;
// 		for (ids::reverse_iterator _t = _b; _t != curLP.rend(); _t++, _vt++, _nt++) {
// 			pc = curpc;
// 			if (find(pc.e1.begin(), pc.e1.end(), *_t) != pc.e1.end())
// 				continue;
// 
// 			copy(_b, _t, back_inserter(pc.e1));
// 			pc.e2.push_back(*_t);
// 
// 			pc.v2.clear();
// 			for (int j = 0; j < pc.e2.size(); j++) {
// 				pc.v2.push_back(lw[pc.e2[j]]);
// 				lw[pc.e2[j]] = max_v;
// 			}
// 
// 			I d = lks[*_t].dp; //cycy
// 			len = getshortpath(o, lks[*_t].dp, pc.l, pc.n, &pc.vn);
// 			
// 			for (j = 0; j < pc.e2.size(); j++)
// 				lw[pc.e2[j]] = pc.v2[j];
// 		
// 			if (len != 0 && len < max_v) {
// 				if (_t != _b)	{
// 					len += (*_vb - *_vt);
// 					for (ids::reverse_iterator _i = _nt; _i != _nb; _i--)
// 						pc.n.push_back(*(_i-1));
// 					for (_i = _t; _i != _b; _i--)
// 						pc.l.push_back(*(_i-1));
// 					
// 					V l = *pc.vn.rbegin();				
// 					for (vs::reverse_iterator _j = _vt; _j != _vb; _j--) {
// 						V b = *(_j-1);
// 						V c = *_vt;
// 						V a = 0;
// 						pc.vn.push_back(a = l + *(_j-1) - *_vt );
// 					}
// 				}
// 				
// 				Q.insert(pair<V, pC>(len, pc));
// 				of << "\nlength=" << len<< " nodes:"; //cycy
// 				copy(pc.n.begin(), pc.n.end(), sout);	//cycy
// 				of << " links:";
// 				copy(pc.l.begin(), pc.l.end(), sout);	//cycy
//  				of << "in link: ";
//  				copy(pc.e1.begin(), pc.e1.end(), sout);
//  				of << "out link: ";
//  				copy(pc.e2.begin(), pc.e2.end(), sout);
// 				of << "vn :";
// 				copy(pc.vn.begin(), pc.vn.end(), sout);
// 			}
// 		}
// 		of << "\n\n";
// 	}
// 	
// 	return true;
// }

bool _fgmap::getmshortpath(I o, I d, int n, mids &mlids, mids &mnids, vs &v)
{	
	pC pc;
	QQ Q;
	v.clear();
	V len = getshortpath(o, d, pc.l, pc.n, &pc.vn);
	if (len == 0) return false;
	Q.insert(pair<V, pC>(len, pc));

	for (int i = 0; !Q.empty(); ) {
		pC curpc = Q.begin()->second;
		v.push_back(Q.begin()->first);
		Q.erase(Q.begin());
		mnids.push_back(curpc.n);
		mlids.push_back(curpc.l);
		ids &curNP = *mnids.rbegin();
		ids &curLP = *mlids.rbegin();
		if (++i >= n)
			break;
		
		ids::reverse_iterator _b = curLP.rbegin();
		ids::reverse_iterator _nb = curNP.rbegin(), _nt = _nb;
		vs::reverse_iterator _vb = curpc.vn.rbegin(), _vt = _vb;
		for (ids::reverse_iterator _t = _b; _t != curLP.rend(); _t++, _vt++, _nt++) {
			pc = curpc;
			if (find(pc.e1.begin(), pc.e1.end(), *_t) != pc.e1.end())
				continue;

			copy(_b, _t, back_inserter(pc.e1));
			pc.e2.push_back(*_t);
			pc.v2.clear();
			for (int j = 0; j < pc.e2.size(); j++) {
				pc.v2.push_back(lw[pc.e2[j]]);
				lw[pc.e2[j]] = max_v;
			}

			len = getshortpath(o, lks[*_t].dp, pc.l, pc.n, &pc.vn);
			
			for (j = 0; j < pc.e2.size(); j++)
				lw[pc.e2[j]] = pc.v2[j];
		
			if (len != 0 && len < max_v) {
				if (_t != _b)	{
					len += (*_vb - *_vt);
					for (ids::reverse_iterator _i = _nt; _i != _nb; _i--)
						pc.n.push_back(*(_i-1));
					for (_i = _t; _i != _b; _i--)
						pc.l.push_back(*(_i-1));
					
					V l = *pc.vn.rbegin();				
					for (vs::reverse_iterator _j = _vt; _j != _vb; _j--)
						pc.vn.push_back(l + *(_j-1) - *_vt );
				}
				
				Q.insert(pair<V, pC>(len, pc));
			}
		}
	}
	
	return true;
}

bool _fgmap::getmshortpath(char *nds, int n, mids &mlids, mids &mnids)
{
	
	return true;
}
