#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class baseClass {
private:
	string name;
	baseClass* parent = nullptr;
	vector <baseClass*> children;
	int readyCode = 0;

public:
	baseClass(baseClass* parent, string name = "Object_Root");
	~baseClass();
	bool setName(string name);
	baseClass* getParent();
	string getName();
	void printNames(int countSpaces = 0);
	baseClass* getChild(string name);
	baseClass* goUpToTheObject(string name);
	baseClass* goDownToTheObject(string name);
	void setReadyCode(int code);
	void printReadyStatus(int countSpaces = 0);
	baseClass* findObjectByCoordinate(string coordinate);
	void removeChild(string name);
	bool changeNewParent(baseClass* newParent);
};