#include "StartScene.h"
#include "CharacterScene.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StartScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    
    auto winSize = glview->getDesignResolutionSize();
    
    auto back = Sprite::create("title_bg.png");
    back->setPosition(Point(winSize.width / 2, winSize.height / 2));
    
    this->addChild(back);
    
    auto title = Sprite::create("title_text.png");
    title->setPosition(Point(winSize.width / 2, winSize.height - 70));
    
    this->addChild(title);
    
    auto character = Sprite::create("title_character.png");
    character->setPosition(Point(winSize.width / 2, winSize.height / 2));
    this->addChild(character);
    
    auto button1 = MenuItemImage::create("title_btn_1.png","title_btn_1_on.png","title_btn_1_dis.png",[&](Ref *sender){
        log("onClickButton1");
        auto scene = TransitionCrossFade::create(0.5f, CharacterScene::createScene());
        Director::getInstance()->pushScene(scene);
    });
    button1->setPosition(Point(winSize.width / 2, 100));
    
    auto button2 = MenuItemImage::create("title_btn_2.png", "title_btn_2_on.png", CC_CALLBACK_1(StartScene::onClickButton2, this));
    button2->setPosition(Point(winSize.width / 2, 40));
    
    auto menu = Menu::create(button1, button2, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    auto to = title->getPosition();
    auto from = Point(to.x, to.y + 100);
    
    title->setPosition(from);
    
    auto action = Sequence::create(MoveTo::create(0.5f, to), RotateTo::create(0.5f, 720), nullptr);
    title->runAction(action);
    
    return true;
}

void StartScene::onClickButton2(Ref *object)
{
    log("onClickButton2");
}

