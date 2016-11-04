#include "CharacterScene.h"

Scene* CharacterScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CharacterScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CharacterScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto director = Director::getInstance();
    auto glView = director->getOpenGLView();
    auto winSize = glView->getDesignResolutionSize();
    
    auto back = Sprite::create("bg_main.png");
    back->setPosition(Point(winSize.width / 2, winSize.height / 2));
    this->addChild(back);
    
    _characterBg = Sprite::create("bg_1.png");
    _characterBg->setAnchorPoint(Point(0.5f, 1));
    _characterBg->setPosition(Point(winSize.width / 2, winSize.height - 15));
    back->addChild(_characterBg);
   
    return true;
}