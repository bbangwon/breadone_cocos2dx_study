#ifndef __CHARACTER_SCENE_H__
#define __CHARACTER_SCENE_H__

#include "cocos2d.h"
#include "ui/cocosGUI.h"
#include "DatabaseManager.h"

USING_NS_CC;

class CharacterScene : public cocos2d::Layer
{
public:
    CharacterScene();
    ~CharacterScene();
    
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(CharacterScene);
    
    Sprite *_characterBg;
    
    void onClickMenu(Ref *object);
    void onClickHome(Ref *object);
    void onClickRandom(Ref *object);
    void onClickSave(Ref *object);
    void onClickGallery(Ref *object);
    
    void setImage(std::string tableName, int rowNo, int colorNo);
    
    Sprite *_face;
    Sprite *_hair1;
    Sprite *_hair2;
    Sprite *_eye;
    Sprite *_mouth;
    Sprite *_etc;
    Sprite *_bgStyle;
    
    void setBalloon(int position);
    Sprite *_arrow;
    Sprite *_balloon;
    
    ui::ScrollView *_scrollView;
    void setSubMenuItem(int position);
    
    std::string _currentTableName;
    void showColorPopup(Ref *object, ui::Widget::TouchEventType type);
    
    character *_characterInfo;
};

#endif // __CHARACTERSCENE_H__
