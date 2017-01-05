//
//  GalleryScene.cpp
//  GameForStudy
//
//  Created by YOUNG IL CHUNG on 2016. 12. 26..
//
//

#include "GalleryScene.h"
#include "StartScene.h"
#include "DatabaseManager.h"

USING_NS_CC;

Scene* GalleryScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GalleryScene::create();
    scene->addChild(layer);
    return scene;
}

bool GalleryScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    auto back = Sprite::create("bg_gallery.png");
    back->setPosition(Point(winSize.width / 2, winSize.height / 2));
    this->addChild(back);
    
    auto home = MenuItemImage::create("menu_home2.png", "menu_home2_on.png", CC_CALLBACK_1(GalleryScene::onClickHome, this));
    home->setAnchorPoint(Point(0,0));
    home->setPosition(Point(0,0));
    
    auto make = MenuItemImage::create("menu_make.png", "menu_make_on.png", CC_CALLBACK_1(GalleryScene::onClickMake, this));
    make->setAnchorPoint(Point(1,0));
    make->setPosition(Point(winSize.width, 0));
    
    auto menu2 = Menu::create(home, make, nullptr);
    menu2->setPosition(Point::ZERO);
    this->addChild(menu2);
    
    auto galleryLayer = LayerColor::create(Color4B(255, 0, 0, 255), winSize.width, 422);
    galleryLayer->setPosition(Point(0, 48));
    this->addChild(galleryLayer, 0, 1);
    
    setItems();
    
    return true;
}

void GalleryScene::setItems()
{
    auto galleryLayer = (LayerColor *)this->getChildByTag(1);
    galleryLayer->removeAllChildrenWithCleanup(true);
    
    std::list<character *> galleryList = DatabaseManager::getInstance()->selectGalleryDB();
    int size = galleryList.size();
    
    Vector<MenuItem *> itemArray;
    for(int i=1;i <= size; i++){
        character *item = galleryList.front();
        
        auto back = Sprite::create("s_bg_1.png");
        auto head = getImage("TB_FACE", item->headNo, item->headColorNo);
        auto hair1 = getImage("TB_HAIR1", item->hair1No, item->hair1ColorNo);
        auto hair2 = getImage("TB_HAIR2", item->hair2No, item->hair2ColorNo);
        auto eye = getImage("TB_EYE", item->eyeNo, item->eyeColorNo);
        auto mouth = getImage("TB_MOUTH", item->mouthNo, item->mouthColorNo);
        auto etc = getImage("TB_ETC", item->etcNo, item->etcColorNo);
        auto bg = getImage("TB_BG", item->bgNo, item->bgColorNo);
        
        back->addChild(bg, 0);
        back->addChild(hair2, 1);
        back->addChild(head, 2);
        back->addChild(eye, 3);
        back->addChild(mouth, 3);
        back->addChild(hair1, 4);
        back->addChild(etc, 5);
        
        auto frame = Sprite::create("box_gallery.png");
        frame->setPosition(Point(back->getContentSize().width / 2, back->getContentSize().height / 2));
        back->addChild(frame, 6);
        
        auto MenuItem = MenuItemSprite::create(back, nullptr);
        MenuItem->setTag(item->no);
        
        float scale = 55 / back->getContentSize().width;
        
        MenuItem->setScale(scale);
        
        int row = (i-1)/4;
        int col = (i-1)%4;
        
        MenuItem->setAnchorPoint(Point(0,1));
        float x = col * MenuItem->getContentSize().width * scale + (col + 1) * 20;
        float y = galleryLayer->getContentSize().height - (row * MenuItem->getContentSize().height * scale + (row + 1) * 15);
        
        MenuItem->setPosition(Point(x,y));
        itemArray.pushBack(MenuItem);
        galleryList.pop_front();
        
    }
    auto menu = Menu::createWithArray(itemArray);
    menu->setPosition(Point::ZERO);
    galleryLayer->addChild(menu);
    
}

Sprite* GalleryScene::getImage(std::string tableName, int rowNo, int colorNo)
{
    std::list<head *>headList = DatabaseManager::getInstance()->selectDB(tableName, rowNo);
    head* head = headList.front();
    
    char smallImg[100];
    sprintf(smallImg, "s_%s", head->image);
    auto sprite = Sprite::create(smallImg);
    
    if(head->isColor){
        Color3B color;
        
        switch (colorNo) {
            case 1:
                color = head->color1;
                break;
            case 2:
                color = head->color2;
                break;
            case 3:
                color = head->color3;
                break;
            case 4:
                color = head->color4;
                break;
        }
        sprite->setColor(color);
    }
    sprite->setPosition(Point(head->position.x * 0.2f, head->position.y * 0.2f));
    
    return sprite;
}

void GalleryScene::onClickItemCallback(cocos2d::Ref *object)
{
    auto MenuItem = (MenuItemSprite*)object;
    log("tag : %d", MenuItem->getTag());
}
void GalleryScene::removeItem()
{
    
}

void GalleryScene::onClickHome(cocos2d::Ref *object)
{
    log("onClickHome");
    auto Scene = StartScene::createScene();
    Director::getInstance()->replaceScene(Scene);
}

void GalleryScene::onClickMake(cocos2d::Ref *object)
{
    log("onClickMake");
    Director::getInstance()->popScene();
}
