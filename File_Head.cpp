#include "File_Head.h"

//字符串转换;
LPCWSTR str2Lpcwstr(string org)
{
	size_t origSize = org.length()+1;
	const size_t newSize = 100;
	size_t convertedChars = 0;
	wchar_t * wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(org.length()-1));
	mbstowcs_s(&convertedChars,wcstring,origSize,org.c_str(),_TRUNCATE);
	return wcstring;
}
//宽字符串转化为单字节字符串
char * wchar2char(wchar_t * wstr)
{
	const size_t newSize = wcslen(wstr)+1;
	size_t converted = 0;
	char * CStr;
	CStr = (char *)malloc(newSize*sizeof(char));
	wcstombs_s(&converted,CStr,newSize,wstr,_TRUNCATE);
	return CStr;
}
//创建文件夹,如果文件夹已经存在就算了
void createDir(string NewDir_Path)
{
	WIN32_FIND_DATA wfd;
	bool rValue = false;
	HANDLE hFind = FindFirstFile(str2Lpcwstr(NewDir_Path.c_str()), &wfd);
	if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		cout << "该文件夹已经存在！" << endl;
	}	
	else
	{
		cout << "文件夹不存在！" << endl;

		int ERROR_File = mkdir(NewDir_Path.c_str());
		if (ERROR_File == 0)
		{
			cout<<"NewDir_Path创建成功！"<<endl;
		} 
		else
		{
			cout<<"NewDir_Path创建失败！"<<endl;
			FindClose(hFind);
			exit(0);
		}
	}
	FindClose(hFind);


}
//清空当前文件夹;
BOOL EmptyDirectory(string szPath)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	string sFullPath;
	string sFindFilter;
	DWORD dwAttributes = 0;
	sFindFilter = szPath;

	sFindFilter += "\\*.*";
	if ((hFind = FindFirstFile(str2Lpcwstr(sFindFilter), &wfd)) == INVALID_HANDLE_VALUE)
		return FALSE;
	do
	{
		if (wfd.cFileName[0] == '.')
			continue;
		sFullPath = szPath;
		sFullPath += '\\';


		sFullPath += wchar2char(wfd.cFileName);
		//去掉只读属性
		dwAttributes = GetFileAttributes(str2Lpcwstr(sFullPath));//.c_str());
		if (dwAttributes & FILE_ATTRIBUTE_READONLY)
		{
			dwAttributes &= ~FILE_ATTRIBUTE_READONLY;
			SetFileAttributes(str2Lpcwstr(sFullPath), dwAttributes);
		}
		//是个目录
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			EmptyDirectory(sFullPath.c_str());
			//This function deletes an existing empty directory
			RemoveDirectory(str2Lpcwstr(sFullPath));//.c_str());
		}
		else
		{
			DeleteFile(str2Lpcwstr(sFullPath));//.c_str());
		}
	}
	while (FindNextFile(hFind, &wfd));
	FindClose(hFind);
	return TRUE;
}
//获得当前目录下所有的文件;而不是子文件夹;
vector<string> getSubFile( string path) 
{ 
	//文件句柄 
	long  hFile  =  0; 
	//文件信息 
	struct _finddata_t fileinfo; 
	string p; 
	vector<string> files;
	
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1) 
	{ 
		do
		{  

			if((fileinfo.attrib & _A_SUBDIR)) 
			{ 
				;
			} 
			else
			{ 
				files.push_back(fileinfo.name);
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name) ); 
			}  
		}
		while(_findnext(hFile, &fileinfo) == 0); 
		_findclose(hFile); 
	} 
	return files;
} 
//获得当前目录下所有的子文件夹;而不是文件;
vector<string> getSubDir( string path) 
{ 
	//文件句柄 
	long  hFile  =  0; 
	//文件信息 
	struct _finddata_t fileinfo; 
	string p; 
	vector<string> files;

	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1) 
	{ 
		
		do
		{  
			if((fileinfo.attrib & _A_SUBDIR && fileinfo.name[0]!='.')) //是个子文件夹
			{ 
				files.push_back(fileinfo.name);
			} 
			else
			{ 
				continue;
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name) ); 
			}  
		}
		while(_findnext(hFile, &fileinfo) == 0); 
		_findclose(hFile); 
	} 
	return files;
} 