#include "MainScene.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

MainScene::MainScene():
	_uiRoot(nullptr),
	_panelResult(nullptr),
	_addLayer(nullptr),
	_panelAdd(nullptr),
	_listView(nullptr),
	_panelItem(nullptr),
	_curName(""),
	_showPanel(false)
{

}

Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();

	scene->addChild(layer);
	return scene;
}

MainScene* MainScene::create()
{
	auto scene = new MainScene();
	if (scene && scene->init())
	{
		scene->autorelease();
		return scene;
	}

	CC_SAFE_DELETE(scene);
	return nullptr;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_uiRoot = CSLoader::createNode("csd/MainLayer.csb");
	this->addChild(_uiRoot);

	_panelResult = static_cast<Widget*>(_uiRoot->getChildByName("Panel_Result"));

	auto Button_Exit = static_cast<Button*>(_uiRoot->getChildByName("Button_Exit"));
	Button_Exit->addClickEventListener(CC_CALLBACK_1(MainScene::exitGame,this));

	auto Button_Random = static_cast<Button*>(_uiRoot->getChildByName("Button_Random"));
	Button_Random->addClickEventListener(CC_CALLBACK_1(MainScene::randomName, this));

	auto Button_Add = static_cast<Button*>(_uiRoot->getChildByName("Button_Add"));
	Button_Add->addClickEventListener(CC_CALLBACK_1(MainScene::addName, this));

	Button_Exit = static_cast<Button*>(_panelResult->getChildByName("Button_Exit"));
	Button_Exit->addClickEventListener([=](Ref*) {
		_panelResult->setVisible(false);
		_showPanel = false;

		_panelResult->setPositionX(-360);
	});

	return true;
}

void MainScene::exitGame(Ref* sender)
{
	if (_showPanel)
		return;

	Director::getInstance()->end();
}

void MainScene::randomName(Ref* sender)
{
	if (_showPanel)
		return;
	
	_panelResult->setVisible(true);
	_showPanel = true;

	_panelResult->setPositionX(360);

	auto Text_Result = static_cast<Text*>(_panelResult->getChildByName("Text_Result"));
	auto name = SaveInstance::getInstance()->getRandomData();
	Text_Result->setString(name);

	auto Button_RandomMore = static_cast<Button*>(_panelResult->getChildByName("Button_RandomMore"));
	Button_RandomMore->addClickEventListener([Text_Result](Ref*) {
		auto name = SaveInstance::getInstance()->getRandomData();
		Text_Result->setString(name);
	});
}

void MainScene::addName(Ref* sender)
{
	if (_showPanel)
		return;

	_showPanel = true;
	
	_addLayer = CSLoader::createNode("csd/AddLayer.csb");
	this->addChild(_addLayer,12450);

	auto panel = static_cast<Widget*>(_addLayer->getChildByName("Panel"));

	_listView = static_cast<ListView*>(panel->getChildByName("ListView"));
	_panelItem = static_cast<Widget*>(_listView->getChildByName("Panel_Item"));
	_panelItem->retain();
	_panelItem->removeFromParent();

	this->refreshList();

	auto children = panel->getChildren();

	for (auto child : children)
	{
		auto name = child->getName();
	}

	auto Button_Exit = static_cast<Button*>(panel->getChildByName("Button_Exit"));
	Button_Exit->addClickEventListener([&](Ref*) {
		_showPanel = false;
		_addLayer->removeFromParent();
	});

	auto Button_Add = static_cast<Button*>(panel->getChildByName("Button_Add"));

	Button_Add->addClickEventListener([=](Ref*) {
		if(!_panelAdd)
			showPanelAdd();
	});
}

void MainScene::showPanelAdd()
{
	_panelAdd = static_cast<Widget*>(_addLayer->getChildByName("Panel")->getChildByName("Panel_Add"));
	_panelAdd->setVisible(true);

	auto Button_Exit = static_cast<Button*>(_panelAdd->getChildByName("Button_Exit"));
	Button_Exit->addClickEventListener([=](Ref*) {
		_panelAdd->setVisible(false);
		_panelAdd = nullptr;
	});

	auto TextField_Name = static_cast<TextField*>(_panelAdd->getChildByName("TextField_Name"));
	
	auto Button_Ok = static_cast<Button*>(_panelAdd->getChildByName("Button_Ok"));
	Button_Ok->addClickEventListener([=](Ref*) {
		auto name = TextField_Name->getString();
		SaveInstance::getInstance()->addData(name);

		this->refreshList();

		_panelAdd->setVisible(false);
		_panelAdd = nullptr;
	});
}

void MainScene::refreshList()
{
	if (_listView && _panelItem)
	{
		_listView->removeAllChildrenWithCleanup(true);

		auto data = SaveInstance::getInstance()->getAllData();

		for (auto dt : data)
		{
			auto panel = _panelItem->clone();

			auto Text_Name = static_cast<Text*>(panel->getChildByName("Text_Name"));
			auto name = dt;

			Text_Name->setString(name);

			auto Button_Remove = static_cast<Button*>(panel->getChildByName("Button_Remove"));
			Button_Remove->addClickEventListener([=](Ref*) {
				SaveInstance::getInstance()->removeData(name);
				this->refreshList();
			});

			_listView->pushBackCustomItem(panel);
		}

		_listView->jumpToTop();
	}
}