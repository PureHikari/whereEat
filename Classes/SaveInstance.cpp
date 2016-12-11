#include "SaveInstance.h"
#include <fstream>

using namespace std;
USING_NS_CC;

SaveInstance* SaveInstance::_myself = nullptr;

SaveInstance* SaveInstance::getInstance()
{
	if (!_myself)
	{
		_myself = new SaveInstance();
		_myself->readData();
	}

	return _myself;
}

void SaveInstance::readData()
{
	_myData.clear();

	auto path = cocos2d::FileUtils::getInstance()->getWritablePath() + "data";

	std::ifstream file;

	file.open(path.c_str());

	if (file)
	{
		int num;

		file >> num;

		for (int i = 0; i < num; i++)
		{
			std::string temp;

			file >> temp;

			_myData.push_back(temp);
		}
	}

	file.close();
}

void SaveInstance::saveData()
{
	auto path = FileUtils::getInstance()->getWritablePath() + "data";

	ofstream file;

	file.open(path.c_str());

	if (file)
	{
		auto num = _myData.size();

		file << num << endl;

		for (int i = 0; i < num; i++)
		{
			file << _myData[i] << endl;
		}
	}

	file.close();
}

string SaveInstance::getRandomData()
{
	if (_myData.size() == 0)
	{
		return "No Any Name";
	}
	else
	{
		int index = 0;

		index = random(0, (int)(_myData.size() - 1));
		return _myData[index];
	}
}

void SaveInstance::addData(std::string content)
{
	_myData.push_back(content);

	this->saveData();
}

void SaveInstance::removeData(std::string index)
{
	for (auto i = _myData.begin(); i != _myData.end(); i++)
	{
		if (*i == index)
		{
			_myData.erase(i);
			break;
		}
	}
}