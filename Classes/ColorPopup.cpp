//
//  ColorPopup.cpp
//  GameForStudy
//
//  Created by YOUNG IL CHUNG on 2016. 11. 30..
//
//

#include "ColorPopup.h"

ColorPopup::ColorPopup()
{
    
}

ColorPopup::~ColorPopup()
{
    
}

ColorPopup * ColorPopup::create(std::string tableName, int no){
    ColorPopup *ret = new ColorPopup();
    if(ret && ret->init(tableName, no)){
        ret->autorelease();
    }else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool ColorPopup::init(std::string tableName, int no){
    log("%s, %d", tableName.c_str(), no);
    
    auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    
    auto fadeBack = LayerColor::create(Color4B(0,0,0,0), winSize.width, winSize.height);
    this->addChild(fadeBack);
    fadeBack->runAction(FadeTo::create(0.5f, 200));
    
    auto back = Sprite::create("bg_color_box.png");
    back->setPosition(Point(winSize.width / 2, winSize.height / 2));
    this->addChild(back);
    
    return true;
}

void ColorPopup::onEnter(){
    Layer::onEnter();
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);

    listener1->onTouchBegan = [](Touch *touch, Event *event){
        return true;
    };
    
    _touchListener = listener1;
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}