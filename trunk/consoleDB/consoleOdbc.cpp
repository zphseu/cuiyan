#include "stdafx.h"
#include "aset.h"

int main(int argc, char* argv[])
{
	int nRecordNumber = 0;

	CASet m_rt;
	cout<<"Console ODBC test, Get ODBC; School; [Student], Author: Edson" << endl;
	m_rt.Open();
	while(! m_rt.IsEOF())
	{
		nRecordNumber ++;
		cout<< m_rt.m_DEPTNO << "    "
			<< m_rt.m_DNAME << "    "
			<< m_rt.m_LOC << endl;
		m_rt.MoveNext();
	}
	m_rt.Close();

	return 0;
}
