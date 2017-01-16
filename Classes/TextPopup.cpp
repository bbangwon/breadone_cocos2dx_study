//
//  TextPopup.cpp
//  GameForStudy
//
//  Created by YOUNG IL CHUNG on 2016. 12. 16..
//
//

#include "TextPopup.h"

TextPopup::TextPopup() : _callback(nullptr){
    
}

TextPopup::~TextPopup(){
    
}

void TextPopup::onEnter(){
    Layer::onEnter();
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    
    listener1->onTouchBegan = [](Touch *touch, Event *event){
        return true;
    };
    
    _touchListener = listener1;
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}

TextPopup* TextPopup::create(std::string text, bool isCancelBT, const textPopupCallback &callback){
    TextPopup *ret = new TextPopup();
    if(ret && ret->init(text, isCancelBT, callback))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool TextPopup::init(std::string text, bool isCancelBT, const textPopupCallback &callback)
{
    _callback = callback;
    
    auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    auto fadeBack = LayerColor::create(Color4B(0,0,0,0), winSize.width, winSize.height);
    this->addChild(fadeBack);
    
    fadeBack->runAction(FadeTo::create(0.5f, 200));
    
    auto back = Sprite::create("pop_up_bg.png");
    back->setPosition(Point(winSize.width / 2, winSize.height / 2));
    this->addChild(back);
    
    auto labelSize = Size(back->getContentSize().width, back->getContentSize().height - 50);
    auto label = Label::createWithSystemFont(text.c_str(), "Arial", 20, labelSize, TextHAlignment::CENTER);
    label->setPosition(Point(back->getContentSize().width / 2, back->getContentSize().height / 2));
    label->setColor(Color3B::BLACK);
    back->addChild(label);
    
    Vector<MenuItem*> itemArray;
    auto okBT = MenuItemImage::create("btn_ok.png", "btn_ok_on.png", CC_CALLBACK_1(TextPopup::onClickOk, this));
    itemArray.pushBack(okBT);
    
    if(!isCancelBT){
        okBT->setPosition(Point(back->getContentSize().width / 2, 25));
    }
    else
    {
        okBT->setPosition(Point(back->getContentSize().width / 2 - 50, 25));
        auto cancelBT = MenuItemImage::create("btn_cancel.png", "btn_cancel_on.png", CC_CALLBACK_1(TextPopup::onClickCancel, this));
        itemArray.pushBack(cancelBT);
        cancelBT->setPosition(Point(back->getContentSize().width / 2 + 50, 25));
    }
    
    auto menu = Menu::createWithArray(itemArray);
    menu->setPosition(Point::ZERO);
    back->addChild(menu);
    
    return true;
}

void TextPopup::onClickOk(cocos2d::Ref *object){
    if(_callback != nullptr)
        _callback();
    
    onClickCancel(nullptr);
}

void TextPopup::onClickCancel(cocos2d::Ref *object){
    this->removeFromParentAndCleanup(true);
}
