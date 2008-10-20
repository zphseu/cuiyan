/**************************************************************
 *  Filename:    gmap.h
 *  Copyright:   Shanghai Baosight Software Co., Ltd.
 *
 *  Description: short path algorithm template file.
 *
 *  @author:     cuiyan
 *  @version     03/02/2004  cuiyan  Initial Version
**************************************************************/

#if !defined(_short_links_h_)
#define _short_links_h_

#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

#ifdef DEBUG
	#include <time.h>
	#include <iostream>
#endif

template<class INDEX, INDEX max_i, class VALUE=INDEX, VALUE max_v=max_i>
class _gmap
{
public:
	typedef INDEX INDEX;
	typedef std::vector<INDEX> node_ids;	//节点集合
	typedef std::vector<INDEX> link_ids;	//边集合
	typedef std::vector<link_ids> shortpaths;	//一个OD对的路径（以边表示）集合

private:
	struct _tnodes {
		_tnodes(VALUE ax = max_v, VALUE ay = max_v, VALUE az = max_v) {	x = ax;	y = ay;	z = az;	}
		VALUE x, y, z;
	};

	struct _tlink {
		_tlink(INDEX aOp = max_i, INDEX aDp = max_i, VALUE aW = max_v) { op = aOp;	dp = aDp; w = aW; }
		INDEX	op, dp;
		VALUE	w;
	};
	
	struct _ghf {
		VALUE g, h, f;
		INDEX sl;
		_ghf(VALUE ag = max_v, VALUE ah = max_v, INDEX asl = max_i) { g =  ag;	h = ah;	f = g + h; sl = asl; }
	};
	
	typedef std::map<INDEX, link_ids>ndlks;	//节点对应的边的关联集合
	typedef std::map<INDEX, _tlink>	links;	//边信息
	typedef std::map<INDEX, _tnodes>	nodes;	//节点信息
	typedef std::map<INDEX, VALUE>	linkws;	//修改了边权重边信息 
	
	ndlks nls;	// 节点信息
	links lks;	// 边信息
	nodes nds;

	bool buseh;
	bool bset;

private:
	static INDEX h(INDEX o, INDEX p) { return 0; }
	void getlinkws(linkws& lw);
	int getshortpath(INDEX o, INDEX d, linkws &lw, link_ids &lids, node_ids &nids);
	
public:
	_gmap() { bset = false; buseh = false; }
	bool setdata(const int ln, const INDEX lv[][4], const int nn = 0, const INDEX nv[][4] = NULL);
	int setdata(const char* fn);
	int getlinks(node_ids &p, shortpaths &lk, shortpaths &nd, int n = 1);
};

/**
 *  set map data.
 *  data file format:
 *  ============================================
 *	link number
 *  l1_index, l1_op, l1_dp, l1_w
 *	l2_index, l2_op, l2_dp, l2_w
 *	... ...
 *	ln_index, ln_op, ln_dp, ln_w
 *	n1_index, n1_x,  n1_y,  n1_z
 *	n2_index, n2_x,  n2_y,  n2_z
 *	... ...
 *	nn_index, nn_x,  nn_y,  nn_z
 *  ============================================
 *  @param  -[in]  const char *fn: [data file name.]
 *  @return true, success; false, failed.
 *
 *  @version  03/01/2004  cuiyan  Initial Version.
 */
template<class INDEX, INDEX max_i, class VALUE, VALUE max_v>
int _gmap<INDEX, max_i, VALUE, max_v>::setdata(const char *fn)
{
	lks.clear();
	nds.clear();
	nls.clear();

	try	{
		int linknum;
		ifstream iof(fn);
		INDEX aOp, aDp, aIndex;
		VALUE aW;
		iof >> linknum;
		for (int i = 0; i < linknum && !iof.eof(); i++) {
			iof >> aIndex >> aOp >> aDp >> aW;
			_tlink t(aOp, aDp, aW);
			lks[aIndex] = t;
		}
		
		for (links::iterator _l = lks.begin(); _l != lks.end(); _l++)	{
			ndlks::iterator _t = nls.find( _l->second.op );	
			
			if (_t == nls.end() )	{// add
				link_ids _x;
				_x.push_back(_l->first);
				nls[_l->second.op] = _x;
			}	else	//modify
				_t->second.push_back(_l->first);
		}
		
		if (lks.size() <= 0)
			throw 1;
		
		buseh = !iof.eof();
			
		if (buseh)	{
			INDEX aIndex;
			VALUE ax, ay, az;
			while(!iof.eof())	{
				iof >> aIndex >> ax >> ay >> az;
				_tnodes t(ax, ay, az);
				nds[aIndex] = t;					
			}			
			
			// 检查是否读到了所有点的坐标信息。
			for (links::iterator _t = lks.begin(); _t != lks.end(); _t++)	{
				if (nds.find(_t->second.op) == nds.end() || nds.find(_t->second.dp) == nds.end())
					throw 1;
			}
		}
		
		iof.close();
		bset = true;
	}
	catch (...) {
		bset = false;
	}
	
	return bset;	
}

/**
 *  set map data.
 *
 *  @param  -[in]  const INDEX  ln: [link number]
 *  @param  -[in]  const INDEX  lv[][4]: [link data, 0-3 is index, op, dp, w]
 *  @param  -[in]  const INDEX  nn: [node number]
 *  @param  -[in]  const INDEX  nv[][4]: [node data, 0-3 is index, x, y, z]
 *  @return true, success; false, failed.
 *
 *  @version  03/01/2004  cuiyan  Initial Version.
 */
template<class INDEX, INDEX max_i, class VALUE, VALUE max_v>
bool _gmap<INDEX, max_i, VALUE, max_v>::setdata(const int ln, const INDEX lv[][4], const int nn, const INDEX nv[][4])
{
	lks.clear();
	nds.clear();
	nls.clear();

	try	{
		for (INDEX i = 0; i < ln; i++) {
			_tlink t(lv[i][1],lv[i][2], lv[i][3]);
			lks[lv[i][0]] = t;
		}
		
		for (links::iterator _l = lks.begin(); _l != lks.end(); _l++)	{
			ndlks::iterator _t = nls.find( _l->second.op );	
			
			if (_t == nls.end() )	{// add
				link_ids _x;
				_x.push_back(_l->first);
				nls[_l->second.op] = _x;
			}	else	//modify
				_t->second.push_back(_l->first);
		}
		
		if (lks.size() <= 0)
			throw 1;
		
		buseh = (nn != 0 && nv != NULL);
		
		if (buseh)	{
			for (i = 0; i < nn; i++) {
				_tnodes t(nv[i][1],nv[i][2], nv[i][3]);
				nds[nv[i][0]] = t;					
			}
			
			// 检查是否读到了所有点的坐标信息。
			for (links::iterator _t = lks.begin(); _t != lks.end(); _t++)	{
				if (nds.find(_t->second.op) == nds.end() || nds.find(_t->second.dp) == nds.end())
					throw 1;
			}
		}
		
		bset = true;
	} catch (...) {
		bset = false;
	}
	
	return bset;
}

template<class INDEX, INDEX max_i, class VALUE, VALUE max_v>
inline void _gmap<INDEX, max_i, VALUE, max_v>::getlinkws(linkws &lw)
{
	for (links::iterator t = lks.begin(); t != lks.end(); t++)
		lw[t->first] = t->second.w;
}

template<class INDEX, INDEX max_i, class VALUE, VALUE max_v>
inline int _gmap<INDEX, max_i, VALUE, max_v>::getshortpath(INDEX o, INDEX d, linkws &lw, link_ids &lids, node_ids &nids)
{
	if (lw.size() == 0)
		getlinkws(lw);
	
	typedef map<INDEX, _ghf> nodeghfs;
	nodeghfs open, close; //map<nodeid, g(n)/h(n)/f(n)>
	open[o] = _ghf(0, buseh ? h(o, o) : 0);
	
	while (!open.empty())	{
		nodeghfs::iterator _x = open.begin();	//_x->first 为最先考虑的节点
		for (nodeghfs::iterator _y = open.begin(); _y != open.end(); _y++)	{
			if (_y->second.f < _x->second.f)
				_x = _y;
		}
		
		_ghf orgghf = open[_x->first];
		INDEX curNd = _x->first;
		open.erase(_x->first);
		
		if (curNd != d) {
			link_ids &ndls = nls[curNd];
			for (link_ids::iterator _t = ndls.begin(); _t != ndls.end(); _t++)	{// *_t为出向边ID
				_tlink &link = lks[*_t];	// 当前出向边
				nodeghfs::iterator _topen = open.find(link.dp);
				nodeghfs::iterator _tclose = close.find(link.dp);
				
				_ghf ghf (orgghf.g + lw[*_t], h(o, link.dp), *_t);//当前节点估价信息
				
				if ( _topen != open.end() )	{
					if (ghf.f < _topen->second.f)
						open[_topen->first] = ghf;
				} else if (_tclose != close.end()) {
					if (ghf.f < _tclose->second.f)	{
						close.erase(link.dp);
						open[link.dp] = ghf;
					}
				} else
					open[link.dp] = ghf;

				close[curNd] = orgghf;
			}
		}	else	{
			nids.clear();
			lids.clear();
			nids.push_back(d);
			INDEX l = orgghf.sl;
			INDEX p = max_i - 1;
			while (p != o && p != max_i)	{
				p = lks[l].op;
				nids.push_back(p);
				lids.push_back(l);
				l = close[p].sl;
			}
			reverse(nids.begin(), nids.end());
			reverse(lids.begin(), lids.end());
			break;
		}
	}

	return 0;
}

template<class INDEX, INDEX max_i, class VALUE, VALUE max_v>
int _gmap<INDEX, max_i, VALUE, max_v>::getlinks(node_ids &p, shortpaths &lk, shortpaths &nd, int n)
{
	INDEX o, d;
	int pnum = p.size();
	
	if (!bset)
		return 1;
	
	if (pnum < 2)
		return 2; //节点个数错误
	
	// 现在只算最短路
	o = p[0];
	d = p[pnum - 1];
	
	linkws lw;
	link_ids lids;
	node_ids nids;
	getshortpath(o, d, lw, lids, nids);
	
	lk.clear();
	lk.push_back(lids);
	nd.clear();
	nd.push_back(nids);
	
	return 0;
}

#endif // !defined(_short_links_h_)
