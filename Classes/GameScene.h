//
//  GameScene.h
//  GameForStudy
//
//  Created by YOUNG IL CHUNG on 2017. 1. 13..
//
//

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene * createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    
    cocos2d::Label *_labelScore;
    void onClickBack(Ref *object);
    cocos2d::Sprite *_targetBack;
    void setTarget();
    cocos2d::LayerColor *_imagesBack;
    void setImages();
    
    bool _isCountDown;
    void setCountDown();
    void setCountDownEnd(Ref *object);
    
    int _targetNo;
    void onClickCard(Ref *object);
    
    cocos2d::Sprite *_timerBG;
    cocos2d::ProgressTimer *_progressBar;
    void setTimer();
    
    cocos2d::Label *_labelCountDown;
    float _countDownTimer;
    void updateTimer(float time);
    
    int _score;
    void gameOver();
    
    int _stage;
    void nextStage();
    
};


#endif /* GameScene_h */
