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
    
    cocos2d::LabelTTF *_labelScore;
    void onClickBack(Ref *object);
    cocos2d::Sprite *_targetBack;
    void setTarget();
};


#endif /* GameScene_h */
