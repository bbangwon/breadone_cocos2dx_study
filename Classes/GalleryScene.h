//
//  GalleryScene.h
//  GameForStudy
//
//  Created by YOUNG IL CHUNG on 2016. 12. 26..
//
//

#ifndef GalleryScene_h
#define GalleryScene_h

#include "cocos2d.h"

class GalleryScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    CREATE_FUNC(GalleryScene);
    
    void onClickHome(Ref *object);
    void onClickMake(Ref *object);
    
    void setItems();
    cocos2d::Sprite* getImage(std::string tableName, int rowNo, int colorNo);
    void onClickItemCallback(Ref *object);
    
    int _removeNo;
    void removeItem();
};

#endif /* GalleryScene_h */
