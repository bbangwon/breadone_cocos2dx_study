//
//  TextPopup.h
//  GameForStudy
//
//  Created by YOUNG IL CHUNG on 2016. 12. 16..
//
//

#ifndef TextPopup_h
#define TextPopup_h

#include "cocos2d.h"

USING_NS_CC;

typedef std::function<void()> textPopupCallback;

class TextPopup : public Layer
{
public:
    TextPopup();
    ~TextPopup();
    
    static TextPopup* create(std::string text, bool isCancelBT, const textPopupCallback &callback);
    bool init(std::string text, bool isCancelBT, const textPopupCallback &callback);
    
    void onEnter();
    
    void onClickOk(Ref *object);
    void onClickCancel(Ref *object);
protected:
    textPopupCallback _callback;
};


#endif /* TextPopup_h */
