#include "File_Head.h"

//�ַ���ת��;
LPCWSTR str2Lpcwstr(string org)
{
	size_t origSize = org.length()+1;
	const size_t newSize = 100;
	size_t convertedChars = 0;
	wchar_t * wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(org.length()-1));
	mbstowcs_s(&convertedChars,wcstring,origSize,org.c_str(),_TRUNCATE);
	return wcstring;
}
//���ַ���ת��Ϊ���ֽ��ַ���
char * wchar2char(wchar_t * wstr)
{
	const size_t newSize = wcslen(wstr)+1;
	size_t converted = 0;
	char * CStr;
	CStr = (char *)malloc(newSize*sizeof(char));
	wcstombs_s(&converted,CStr,newSize,wstr,_TRUNCATE);
	return CStr;
}
//�����ļ���,����ļ����Ѿ����ھ�����
void createDir(string NewDir_Path)
{
	WIN32_FIND_DATA wfd;
	bool rValue = false;
	HANDLE hFind = FindFirstFile(str2Lpcwstr(NewDir_Path.c_str()), &wfd);
	if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		cout << "���ļ����Ѿ����ڣ�" << endl;
	}	
	else
	{
		cout << "�ļ��в����ڣ�" << endl;

		int ERROR_File = mkdir(NewDir_Path.c_str());
		if (ERROR_File == 0)
		{
			cout<<"NewDir_Path�����ɹ���"<<endl;
		} 
		else
		{
			cout<<"NewDir_Path����ʧ�ܣ�"<<endl;
			FindClose(hFind);
			exit(0);
		}
	}
	FindClose(hFind);


}
//��յ�ǰ�ļ���;
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
		//ȥ��ֻ������
		dwAttributes = GetFileAttributes(str2Lpcwstr(sFullPath));//.c_str());
		if (dwAttributes & FILE_ATTRIBUTE_READONLY)
		{
			dwAttributes &= ~FILE_ATTRIBUTE_READONLY;
			SetFileAttributes(str2Lpcwstr(sFullPath), dwAttributes);
		}
		//�Ǹ�Ŀ¼
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
//��õ�ǰĿ¼�����е��ļ�;���������ļ���;
vector<string> getSubFile( string path) 
{ 
	//�ļ���� 
	long  hFile  =  0; 
	//�ļ���Ϣ 
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
//��õ�ǰĿ¼�����е����ļ���;�������ļ�;
vector<string> getSubDir( string path) 
{ 
	//�ļ���� 
	long  hFile  =  0; 
	//�ļ���Ϣ 
	struct _finddata_t fileinfo; 
	string p; 
	vector<string> files;

	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1) 
	{ 
		
		do
		{  
			if((fileinfo.attrib & _A_SUBDIR && fileinfo.name[0]!='.')) //�Ǹ����ļ���
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