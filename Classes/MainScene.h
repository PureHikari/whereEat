#pragma once
#include "cocos2d.h"
#include "SaveInstance.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class MainScene :public cocos2d::Layer
{
public:
	MainScene();

	static MainScene* create();
	static cocos2d::Scene* createScene();
	
	bool init();

	void exitGame(cocos2d::Ref* sender);
	void randomName(cocos2d::Ref* sender);
	void addName(cocos2d::Ref* sender);

	void refreshList();
	void showPanelAdd();
private:
	cocos2d::Node* _uiRoot;
	cocos2d::ui::Widget* _panelResult;
	cocos2d::ui::Widget* _panelAdd;

	cocos2d::ui::ListView* _listView;
	cocos2d::ui::Widget* _panelItem;

	cocos2d::Node* _addLayer;

	std::string _curName;

	bool _showPanel;
};