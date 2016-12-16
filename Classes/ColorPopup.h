#ifndef __COLORPOPUP_H__
#define __COLORPOPUP_H__

#include "cocos2d.h"

USING_NS_CC;

class ColorPopup : public Layer
{
public:
    ColorPopup();
    ~ColorPopup();
    
    static ColorPopup *create(std::string tableName, int no);
    bool init(std::string tableName, int no);
    
    void onEnter();
    
    std::string _tableName;
    int _no;
    
    void onClickColor(Ref *object);
};

#endif //__COLORPOPUP_H__
