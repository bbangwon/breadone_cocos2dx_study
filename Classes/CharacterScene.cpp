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
    
    auto menu1Face = MenuItemImage::create("btn_face.png", "btn_face_on.png", CC_CALLBACK_1(CharacterScene::onClickMenu, this));
    menu1Face->setPosition(Point(25, 125));
    
    auto menu1Hair1 = MenuItemImage::create("btn_hair1.png", "btn_hair1_on.png", CC_CALLBACK_1(CharacterScene::onClickMenu, this));
    menu1Hair1->setPosition(Point(70, 125));
    
    auto menu1Hair2 = MenuItemImage::create("btn_hair2.png","btn_hair2_on.png", CC_CALLBACK_1(CharacterScene::onClickMenu, this));
    menu1Hair2->setPosition(Point(115, 125));
    
    auto menu1Eye = MenuItemImage::create("btn_eye.png", "btn_eye_on.png", CC_CALLBACK_1(CharacterScene::onClickMenu, this));
    menu1Eye->setPosition(Point(160, 125));
    
    auto menu1Mouth = MenuItemImage::create("btn_mouth.png", "btn_mouth_on.png", CC_CALLBACK_1(CharacterScene::onClickMenu, this));
    menu1Mouth->setPosition(Point(205, 125));
    
    auto menu1Etc = MenuItemImage::create("btn_etc.png", "btn_etc_on.png", CC_CALLBACK_1(CharacterScene::onClickMenu, this));
    menu1Etc->setPosition(Point(250, 125));
    
    auto menu1Bg = MenuItemImage::create("btn_bg.png", "btn_bg_on.png", CC_CALLBACK_1(CharacterScene::onClickMenu, this));
    menu1Bg->setPosition(Point(295, 125));
    
    
    auto menu1 = Menu::create(menu1Face, menu1Hair1, menu1Hair2, menu1Eye, menu1Mouth, menu1Etc, menu1Bg, nullptr);
    menu1->setPosition(Point::ZERO);
    this->addChild(menu1);
    
    float x;
    float y;
    float width;
    float height;
    
    auto menu2Home = MenuItemImage::create("menu_home.png", "menu_home_on.png");
    width = menu2Home->getContentSize().width;
    height = menu2Home->getContentSize().height;
    x = width / 2;
    y = height / 2;
    menu2Home->setPosition(Point(x,y));
    
    auto menu2Random = MenuItemImage::create("menu_random.png", "menu_random_on.png");
    x = menu2Home->getPositionX() + width;
    menu2Random->setPosition(Point(x,y));
    
    auto menu2Save = MenuItemImage::create("menu_save.png", "menu_save_on.png");
    x = menu2Random->getPositionX() + width;
    menu2Save->setPosition(Point(x,y));
    
    auto menu2Gallery = MenuItemImage::create("menu_gallary.png","menu_gallary_on.png");
    x = menu2Save->getPositionX() + width;
    menu2Gallery->setPosition(Point(x,y));
    
    auto menu2 = Menu::create(menu2Home, menu2Random, menu2Save, menu2Gallery, nullptr);
    menu2->setPosition(Point::ZERO);
    this->addChild(menu2);
   
    return true;
}

void CharacterScene::onClickMenu(Ref *object)
{
    log("onClickMenu");
}