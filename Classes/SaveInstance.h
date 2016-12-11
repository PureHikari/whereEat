#pragma once
#include "cocos2d.h"

typedef std::vector<std::string> resData;

class SaveInstance
{
public:
	static SaveInstance* getInstance();

	void saveData();
	void readData();

	resData getAllData() { return _myData; }
	std::string getRandomData();
	void addData(std::string content);
	void removeData(std::string idx);
private:
	static SaveInstance* _myself;
	resData _myData;
};