//
//  GameScene.cpp
//  GameForStudy
//
//  Created by YOUNG IL CHUNG on 2017. 1. 13..
//
//


#include "GameScene.h"
#include "DatabaseManager.h"
#include "GalleryScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    auto bg = Sprite::create("game_bg.png");
    bg->setPosition(Point(winSize.width / 2, winSize.height / 2));
    this->addChild(bg);
    
    auto title = Sprite::create("game_title.png");
    title->setPosition(Point(winSize.width / 2, winSize.height - 20));
    this->addChild(title);
    
    auto back = MenuItemImage::create("btn_back.png", "btn_back_on.png", CC_CALLBACK_1(GameScene::onClickBack, this));
    back->setPosition(Point(30, winSize.height - 20));
    
    auto menu = Menu::create(back, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    auto score = Sprite::create("box_score.png");
    score->setPosition(Point(250, 410));
    this->addChild(score);
    
    _labelScore = LabelTTF::create("0", "arial", 20);
    _labelScore->setPosition(Point(score->getContentSize().width / 2, 22));
    score->addChild(_labelScore);
    
    _targetBack = nullptr;
    setTarget();
    
    return true;
}

void GameScene::onClickBack(cocos2d::Ref *object)
{
    log("onClickBack");
    Director::getInstance()->popScene();
}

void GameScene::setTarget()
{
    if(_targetBack)
        _targetBack->removeFromParentAndCleanup(true);
    
    character *item = DatabaseManager::getInstance()->selectRandomGalleryDB();
    
    _targetBack = Sprite::create("s_bg_1.png");
    auto head = GalleryScene::getImage("TB_FACE", item->headNo, item->headColorNo);
    auto hair1 = GalleryScene::getImage("TB_HAIR1", item->hair1No, item->hair1ColorNo);
    auto hair2 = GalleryScene::getImage("TB_HAIR2", item->hair2No, item->hair2ColorNo);
    auto eye = GalleryScene::getImage("TB_EYE", item->eyeNo, item->eyeColorNo);
    auto mouth = GalleryScene::getImage("TB_MOUTH", item->mouthNo, item->mouthColorNo);
    auto etc = GalleryScene::getImage("TB_ETC", item->etcNo, item->etcColorNo);
    auto bg = GalleryScene::getImage("TB_BG", item->bgNo, item->bgColorNo);
    
    _targetBack->addChild(bg, 0);
    _targetBack->addChild(hair2, 1);
    _targetBack->addChild(head, 2);
    _targetBack->addChild(eye, 3);
    _targetBack->addChild(mouth, 3);
    _targetBack->addChild(hair1, 4);
    _targetBack->addChild(etc, 5);
    
    auto frame = Sprite::create("box_2.png");
    frame->setPosition(Point(_targetBack->getContentSize().width / 2, _targetBack->getContentSize().height / 2));
    _targetBack->addChild(frame, 6);
    
    float scale = 50 / _targetBack->getContentSize().width;
    _targetBack->setScale(scale);
    
    _targetBack->setPosition(Point(85, 410));
    this->addChild(_targetBack);
}
