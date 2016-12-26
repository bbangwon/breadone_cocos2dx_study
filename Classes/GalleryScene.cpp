//
//  GalleryScene.cpp
//  GameForStudy
//
//  Created by YOUNG IL CHUNG on 2016. 12. 26..
//
//

#include "GalleryScene.h"
#include "StartScene.h"

USING_NS_CC;

Scene* GalleryScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GalleryScene::create();
    scene->addChild(layer);
    return scene;
}

bool GalleryScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    auto back = Sprite::create("bg_gallery.png");
    back->setPosition(Point(winSize.width / 2, winSize.height / 2));
    this->addChild(back);
    
    auto home = MenuItemImage::create("menu_home2.png", "menu_home2_on.png", CC_CALLBACK_1(GalleryScene::onClickHome, this));
    home->setAnchorPoint(Point(0,0));
    home->setPosition(Point(0,0));
    
    auto make = MenuItemImage::create("menu_make.png", "menu_make_on.png", CC_CALLBACK_1(GalleryScene::onClickMake, this));
    make->setAnchorPoint(Point(1,0));
    make->setPosition(Point(winSize.width, 0));
    
    auto menu2 = Menu::create(home, make, nullptr);
    menu2->setPosition(Point::ZERO);
    this->addChild(menu2);
    
    return true;
}

void GalleryScene::onClickHome(cocos2d::Ref *object)
{
    log("onClickHome");
    auto Scene = StartScene::createScene();
    Director::getInstance()->replaceScene(Scene);
}

void GalleryScene::onClickMake(cocos2d::Ref *object)
{
    log("onClickMake");
    Director::getInstance()->popScene();
}
