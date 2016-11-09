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
    
    auto menu1Face = MenuItemImage::create("btn_face.png", "btn_face_on.png");
    menu1Face->setPosition(Point(25, 125));
    
    auto menu1Hair1 = MenuItemImage::create("btn_hair1.png", "btn_hair1_on.png");
    menu1Hair1->setPosition(Point(70, 125));
    
    auto menu1Hair2 = MenuItemImage::create("btn_hair2.png","btn_hair2_on.png");
    menu1Hair2->setPosition(Point(115, 125));
    
    auto menu1Eye = MenuItemImage::create("btn_eye.png", "btn_eye_on.png");
    menu1Eye->setPosition(Point(160, 125));
    
    auto menu1Mouth = MenuItemImage::create("btn_mouth.png", "btn_mouth_on.png");
    menu1Mouth->setPosition(Point(205, 125));
    
    auto menu1Etc = MenuItemImage::create("btn_etc.png", "btn_etc_on.png");
    menu1Etc->setPosition(Point(250, 125));
    
    auto menu1Bg = MenuItemImage::create("btn_bg.png", "btn_bg_on.png");
    menu1Bg->setPosition(Point(295, 125));
    
    
    auto menu1 = Menu::create(menu1Face, menu1Hair1, menu1Hair2, menu1Eye, menu1Mouth, menu1Etc, menu1Bg, nullptr);
    menu1->setPosition(Point::ZERO);
    this->addChild(menu1);
   
    return true;
}