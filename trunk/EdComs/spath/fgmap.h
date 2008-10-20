/**************************************************************
 *  Filename:    fgmap.h
 *  Copyright:   Shanghai Baosight Software Co., Ltd.
 *
 *  Description: fast gmap interface file.
 *
 *  @author:     cuiyan
 *  @version     03/08/2004  cuiyan  Initial Version
**************************************************************/
#ifndef _FAST_GMAP_
#define _FAST_GMAP_

#include <set>
#include <map>
#include <vector>

#pragma warning(disable : 4786)

using namespace std;

namespace fmap	{
	typedef long V;
	typedef unsigned short I;
	typedef long II;
	const V max_v = 1048576;	// max 2048 edges

#define I2TOII(a, b) ((II)(((I)(a)) | ((II)((I)(b))) << 16))
};

using namespace fmap;

class _fgmap
{
public:
	typedef vector<V> vs;
	typedef vector<I> ids;
	typedef vector<ids> mids;

private:
	struct pC {
		ids e1, e2, n, l;
		vs v1, v2, vn;
		void clear() { e1.clear(); e2.clear(); l.clear(); n.clear(); v1.clear(); v2.clear(); }
	};

	typedef multimap<V, pC> QQ;
	
	struct _ghf {
		V g, h, f;
		I sl;
		_ghf(V ag = max_v, V ah = max_v, I asl = 0) { g =  ag;	h = ah;	f = g + h; sl = asl; }
	};

	struct _tnode {
		_tnode(V ax = max_v, V ay = max_v, V az = max_v) {	x = ax;	y = ay;	z = az; }
		V x, y, z;
		ids lk;
	};

	struct _tlink {
		_tlink(I aOp = 0, I aDp = 0, V aW = max_v) {op = aOp;dp = aDp;w = aW; }
		I	op, dp;
		V	w;
	};
	
	map<I, _tnode>	nds;
	map<I, _tlink>	lks;
	map<I, V>		lw;
	set<II> nrlk;
	V h(I o, I p) { return 0; }

public:
	void set_link(long isize, V *pOp, V *pDp, V* pW);
	void set_ilink(I aIndex, V aOp, V aDp, V aW);
	void set_node(long isize, V *pX, V *pY, V *pZ);
	void set_inode(I aIndex, V aX, V aY, V aZ);
	void set_w(long isize, V* pw);
	void set_iw(I index, V w);
	void set_inrlk(I l1, I l2);
	void set_nrlk(long isize, I *p1, I *p2);
	void clear() { nrlk.clear(); nds.clear(); lks.clear(); lw.clear(); }
	
	static bool str2ids(char *str, ids &aids);
	static string ids2str(ids& sp);
	static string vs2str(vs& v);
	static string mids2str(mids& sp);

	V getshortpath(I o, I d, ids &lids, ids &nids, vs *pnv = NULL);
	V getshortpath(char* nds, ids & lids, ids &nids);
	bool getmshortpath(I o, I d, int n, mids &mlids, mids &mnids, vs &v);
	bool getmshortpath(char *nds, int n, mids &mlids, mids &mnids);
};

#endif