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
#include "TextPopup.h"
#include "SimpleAudioEngine.h"

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
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Pixel Peeker Polka - slower.mp3", true);
    
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
    
    _labelScore = Label::createWithSystemFont("0", "Arial", 20);
    _labelScore->setPosition(Point(score->getContentSize().width / 2, 22));
    score->addChild(_labelScore);
    
    _targetBack = nullptr;
    setTarget();
    
    _imagesBack = LayerColor::create(Color4B(0, 0, 0, 0), winSize.width, 340);
    _imagesBack->setPosition(Point(0,0));
    this->addChild(_imagesBack);
    
    setImages();
    setCountDown();
    
    _timerBG = Sprite::create("gage_bg.png");
    _timerBG->setPosition(Point(winSize.width / 2, 365));
    this->addChild(_timerBG);
    
    auto progress_sprite = Sprite::create("gage_bar.png");
    _progressBar = ProgressTimer::create(progress_sprite);
    _progressBar->setPosition(Point(_timerBG->getContentSize().width / 2, _timerBG->getContentSize().height / 2));
    
    _progressBar->setType(ProgressTimer::Type::BAR);
    _progressBar->setBarChangeRate(Point(1, 0));
    _progressBar->setMidpoint(Point(0, 0.5f));
    _progressBar->setPercentage(100);
    
    _timerBG->addChild(_progressBar);
    
    _labelCountDown = Label::createWithSystemFont("5.0", "Arial", 20);
    _labelCountDown->setAnchorPoint(Point(0.5f, 0.5f));
    _labelCountDown->setPosition(Point(_timerBG->getContentSize().width / 2, _timerBG->getContentSize().height / 2));
    _timerBG->addChild(_labelCountDown);
    
    _score = 0;
    _stage = 1;
    
    return true;
}

void GameScene::onClickBack(cocos2d::Ref *object)
{
    if(_isCountDown)
        return;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    log("onClickBack");
    Director::getInstance()->popScene();
}

void GameScene::setTarget()
{
    if(_targetBack)
        _targetBack->removeFromParentAndCleanup(true);
    
    character *item = DatabaseManager::getInstance()->selectRandomGalleryDB();
    
    _targetNo = item->no;
    
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

void GameScene::setImages()
{
    _imagesBack->removeAllChildrenWithCleanup(true);
    
    auto galleryList = DatabaseManager::getInstance()->selectGalleryDB(true);
    int size = galleryList.size();
    
    Vector<MenuItem*> itemArray;
    for(int i=1;i<=size;i++){
        character *item = galleryList.front();
        
        auto back = Sprite::create("s_bg_1.png");
        auto head = GalleryScene::getImage("TB_FACE", item->headNo, item->headColorNo);
        auto hair1 = GalleryScene::getImage("TB_HAIR1", item->hair1No, item->hair1ColorNo);
        auto hair2 = GalleryScene::getImage("TB_HAIR2", item->hair2No, item->hair2ColorNo);
        auto eye = GalleryScene::getImage("TB_EYE", item->eyeNo, item->eyeColorNo);
        auto mouth = GalleryScene::getImage("TB_MOUTH", item->mouthNo, item->mouthColorNo);
        auto etc = GalleryScene::getImage("TB_ETC", item->etcNo, item->etcColorNo);
        auto bg = GalleryScene::getImage("TB_BG", item->bgNo, item->bgColorNo);
        
        back->addChild(bg, 0);
        back->addChild(hair2, 1);
        back->addChild(head, 2);
        back->addChild(eye, 3);
        back->addChild(mouth, 3);
        back->addChild(hair1, 4);
        back->addChild(etc, 5);
        
        auto frame = Sprite::create("box_face.png");
        frame->setPosition(Point(back->getContentSize().width / 2, back->getContentSize().height / 2));
        back->addChild(frame, 6);
        
        auto menuItem = MenuItemSprite::create(back, nullptr, CC_CALLBACK_1(GameScene::onClickCard, this));
        menuItem->setTag(item->no);
        
        float scale = 55 / back->getContentSize().width;
        menuItem->setScale(scale);
        
        int row = (i-1)/4;
        int col = (i-1)%4;
        menuItem->setAnchorPoint(Point(0,1));
        
        float x = col * menuItem->getContentSize().width * scale + (col + 1) * 20;
        float y = _imagesBack->getContentSize().height - (row * menuItem->getContentSize().height * scale + (row + 1) * 10);
        
        menuItem->setPosition(Point(x,y));
        itemArray.pushBack(menuItem);
        galleryList.pop_front();
        
        auto blindImg = Sprite::create("box_back.png");
        blindImg->setPosition(Point(menuItem->getContentSize().width / 2, menuItem->getContentSize().height / 2));
        menuItem->addChild(blindImg);
        
        back->setScaleX(0);
        back->setAnchorPoint(Point(0.5f, 0.5f));
        back->setPosition(Point(back->getContentSize().width / 2, back->getContentSize().height / 2));
        
        blindImg->runAction(Sequence::create(DelayTime::create(3), ScaleTo::create(0.2f, 0, 1), nullptr));
        back->runAction(Sequence::create(DelayTime::create(3 + 0.2f), ScaleTo::create(0.2f, 1, 1), nullptr));
        
    }
    auto menu = Menu::createWithArray(itemArray);
    menu->setPosition(Point::ZERO);
    _imagesBack->addChild(menu);
}

void GameScene::setCountDown(){
    _isCountDown = true;
    Size winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    
    auto CountDownLayer = LayerColor::create(Color4B(0, 0, 0, 180), winSize.width, winSize.height);
    this->addChild(CountDownLayer, 10);
    
    auto count3 = Label::createWithSystemFont("3", "Arial", 60);
    auto count2 = Label::createWithSystemFont("2", "Arial", 60);
    auto count1 = Label::createWithSystemFont("1", "Arial", 60);
    
    count3->setOpacity(0);
    count2->setOpacity(0);
    count1->setOpacity(0);
    
    count3->setPosition(Point(winSize.width/2, winSize.height / 2));
    count2->setPosition(count3->getPosition());
    count1->setPosition(count3->getPosition());
    
    CountDownLayer->addChild(count3);
    CountDownLayer->addChild(count2);
    CountDownLayer->addChild(count1);
    
    auto action = Sequence::create(FadeIn::create(0), FadeOut::create(1), nullptr);
    
    count3->runAction(action);
    count2->runAction(Sequence::create(DelayTime::create(1), action->clone(), nullptr));
    count1->runAction(Sequence::create(DelayTime::create(2), action->clone(), nullptr));
    
    CountDownLayer->runAction(Sequence::create(DelayTime::create(3), CallFuncN::create(CC_CALLBACK_1(GameScene::setCountDownEnd, this)), nullptr));
}

void GameScene::setCountDownEnd(cocos2d::Ref *object){
    _isCountDown = false;
    ((Node*)object)->removeFromParentAndCleanup(true);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/flip_sound.wav");
    setTimer();
}

void GameScene::onClickCard(cocos2d::Ref *object){
    if(_isCountDown)
        return;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/click_sound.wav");
    auto selectImg = (MenuItemSprite *)object;
    int clickNo = selectImg->getTag();
    
    unschedule(CC_SCHEDULE_SELECTOR(GameScene::updateTimer));
    _progressBar->stopAllActions();
    
    if(_targetNo == clickNo)
    {
        _score = _score + (_countDownTimer / 5.0f) * 10000;
        char scoreChar[50];
        sprintf(scoreChar, "%d", _score);
        _labelScore->setString(scoreChar);
        
        char resultChar[100];
        sprintf(resultChar, "성공하였습니다.\n\n%d점을 획득하였습니다.", _score);
        
        
        if(_stage < 3){
            _stage++;
            this->addChild(TextPopup::create(resultChar, false, CC_CALLBACK_0(GameScene::nextStage, this)));
        }
        else
        {
            this->addChild(TextPopup::create(resultChar, false, CC_CALLBACK_0(GameScene::gameOver, this)));
        }
    }
    else
    {
        char resultChar[100];
        sprintf(resultChar, "실패하였습니다.\n\n%d점을 획득하였습니다.", _score);
        this->addChild(TextPopup::create(resultChar, false, CC_CALLBACK_0(GameScene::gameOver, this)));
    }
}

void GameScene::setTimer(){
    _progressBar->runAction(ProgressFromTo::create(5, 100, 0));
    
    _countDownTimer = 5.0f;
    schedule(CC_SCHEDULE_SELECTOR(GameScene::updateTimer));
}

void GameScene::updateTimer(float time){
    _countDownTimer -= time;
    if(_countDownTimer < 0){
        _countDownTimer = 0;
        unschedule(CC_SCHEDULE_SELECTOR(GameScene::updateTimer));
        _labelCountDown->setString("0.0");
        
        char resultChar[100];
        sprintf(resultChar, "실패하였습니다.\n\n%d점을 획득하였습니다.", _score);
        this->addChild(TextPopup::create(resultChar, false, CC_CALLBACK_0(GameScene::gameOver, this)));
    }
    
    log("_countDownTimer : %f", _countDownTimer);
    char str[10] = {0};
    sprintf(str, "%2.1f", _countDownTimer);
    _labelCountDown->setString(str);
}

void GameScene::gameOver() {
    onClickBack(nullptr);
}

void GameScene::nextStage() {
    setTarget();
    setImages();
    setCountDown();
    
    _progressBar->setPercentage(100);
    _labelCountDown->setString("5.0");
}
