#pragma once

//#pragma warning(disable:4996)
//
//#include <opencv2/imgproc/imgproc.hpp>	// Gaussian Blur
//#include <opencv2/core/core.hpp>		// Basic OpenCV structures (cv::Mat, Scalar)
//#include <opencv2/highgui/highgui.hpp>	// OpenCV window I/O
//#include <UrlHist.h>
#include <Windows.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <direct.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>



using namespace std;

//这个文件是windows下对文件夹进行增删查的操作函数集合;


vector<string> getSubFile( string path);
vector<string> getSubDir( string path) ;
BOOL EmptyDirectory(string szPath);
LPCWSTR str2Lpcwstr(string org);
void createDir(string NewDir_Path);