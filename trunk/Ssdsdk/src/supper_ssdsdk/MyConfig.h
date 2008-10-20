#ifndef _MY_CONFIG_
#define _MY_CONFIG_

// 如果在产品资源中有这些信息，使用资源中的，如果没有则必须定义有效值
#define theProductName		_T("");
#define theProductVersion	_T("");
#define theProductBuild		_T("");

// 如果定义了该宏，则使用该宏的注册表路径名
// 如果没有定义该宏，则使用_T("Software\\[ProductName]\\")这个路径，其中的[ProductName]
// 将使用theProductName对应的有效定义。
//#define theRegPath			_T("Software\\");
#endif //_MY_CONFIG_