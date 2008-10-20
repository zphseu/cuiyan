// version.h
///////////////////////////////////////////////////////////////////////////
//
// Author : James M. Curran         27-Feb-1997 
/////////////////////////////////////////////////////////////////////////// 
//
//  Class MSKVersionInfo
//
//
//  Handles accessing the VERSIONINFO resource, which is particularly poorly
//  documented by Microsoft, but does define it's items as follows:
//

class MSKVersionInfo
{
public:
    MSKVersionInfo(LPCTSTR pModName = NULL); 
    ~MSKVersionInfo();
     
    CString ProductName()     {return GetValue("ProductName");} 
    CString ProductVersion()  {return GetValue("ProductVersion");} 
    CString SpecialBuild()    {return GetValue("SpecialBuild");} 
    CString GetValue(CString const sSubBlock);
    BOOL	IsError() { return m_isError; } 

private:
    CString     m_sSubBlockHead;
    void *      m_VerData;
	BOOL		m_isError;     
};
