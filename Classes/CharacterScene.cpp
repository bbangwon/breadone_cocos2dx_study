#include "CharacterScene.h"
#include "DatabaseManager.h"
#include "DevConf.h"
#include "ColorPopup.h"
#include "TextPopup.h"


CharacterScene::CharacterScene(){
    _face = nullptr;
    _hair1 = nullptr;
    _hair2 = nullptr;
    _eye = nullptr;
    _mouth = nullptr;
    _etc = nullptr;
    _bgStyle = nullptr;
    _balloon = nullptr;
    _arrow = nullptr;
    _scrollView = nullptr;
    
    _characterInfo = new character;
}

CharacterScene::~CharacterScene(){
    delete _characterInfo;
}

Scene* CharacterScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CharacterScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CharacterScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

		auto UserDefault = UserDefault::getInstance();
		bool isFirst = UserDefault->getBoolForKey("isFirst", true);

		if (isFirst || DB_INIT) {
			DatabaseManager::getInstance()->createDB();
			DatabaseManager::getInstance()->insertDB();

			UserDefault->setBoolForKey("isFirst", false);
			UserDefault->flush();
		}
    
    auto director = Director::getInstance();
    auto glView = director->getOpenGLView();
    auto winSize = glView->getDesignResolutionSize();
    
    auto back = Sprite::create("bg_main.png");
    back->setPosition(Point(winSize.width / 2, winSize.height / 2));
    this->addChild(back);
    
    _characterBg = Sprite::create("bg_1.png");
    _characterBg->setAnchorPoint(Point(0.5f, 1));
    _characterBg->setPosition(Point(winSize.width / 2, winSize.height - 15));
    back->addChild(_characterBg);
    
    auto menu1Face = MenuItemImage::create("btn_face.png", "btn_face_on.png", CC_CALLBACK_1(CharacterScene::onClickMenu, this));
    menu1Face->setPosition(Point(25, 125));
    
    auto menu1Hair1 = MenuItemImage::create("btn_hair1.png", "btn_hair1_on.png", CC_CALLBACK_1(CharacterScene::onClickMenu, this));
    menu1Hair1->setPosition(Point(70, 125));
    
    auto menu1Hair2 = MenuItemImage::create("btn_hair2.png","btn_hair2_on.png", CC_CALLBACK_1(CharacterScene::onClickMenu, this));
    menu1Hair2->setPosition(Point(115, 125));
    
    auto menu1Eye = MenuItemImage::create("btn_eye.png", "btn_eye_on.png", CC_CALLBACK_1(CharacterScene::onClickMenu, this));
    menu1Eye->setPosition(Point(160, 125));
    
    auto menu1Mouth = MenuItemImage::create("btn_mouth.png", "btn_mouth_on.png", CC_CALLBACK_1(CharacterScene::onClickMenu, this));
    menu1Mouth->setPosition(Point(205, 125));
    
    auto menu1Etc = MenuItemImage::create("btn_etc.png", "btn_etc_on.png", CC_CALLBACK_1(CharacterScene::onClickMenu, this));
    menu1Etc->setPosition(Point(250, 125));
    
    auto menu1Bg = MenuItemImage::create("btn_bg.png", "btn_bg_on.png", CC_CALLBACK_1(CharacterScene::onClickMenu, this));
    menu1Bg->setPosition(Point(295, 125));
    
    
    auto menu1 = Menu::create(menu1Face, menu1Hair1, menu1Hair2, menu1Eye, menu1Mouth, menu1Etc, menu1Bg, nullptr);
    menu1->setPosition(Point::ZERO);
    this->addChild(menu1);
    
    menu1Face->setTag(1);
    menu1Hair1->setTag(2);
    menu1Hair2->setTag(3);
    menu1Eye->setTag(4);
    menu1Mouth->setTag(5);
    menu1Etc->setTag(6);
    menu1Bg->setTag(7);
    
    float x;
    float y;
    float width;
    float height;
    
    auto menu2Home = MenuItemImage::create("menu_home.png", "menu_home_on.png", CC_CALLBACK_1(CharacterScene::onClickHome, this));
    width = menu2Home->getContentSize().width;
    height = menu2Home->getContentSize().height;
    x = width / 2;
    y = height / 2;
    menu2Home->setPosition(Point(x,y));
    
    auto menu2Random = MenuItemImage::create("menu_random.png", "menu_random_on.png", CC_CALLBACK_1(CharacterScene::onClickRandom, this));
    x = menu2Home->getPositionX() + width;
    menu2Random->setPosition(Point(x,y));
    
    auto menu2Save = MenuItemImage::create("menu_save.png", "menu_save_on.png", CC_CALLBACK_1(CharacterScene::onClickSave, this));
    x = menu2Random->getPositionX() + width;
    menu2Save->setPosition(Point(x,y));
    
    auto menu2Gallery = MenuItemImage::create("menu_gallary.png","menu_gallary_on.png", CC_CALLBACK_1(CharacterScene::onClickGallery, this));
    x = menu2Save->getPositionX() + width;
    menu2Gallery->setPosition(Point(x,y));
    
    auto menu2 = Menu::create(menu2Home, menu2Random, menu2Save, menu2Gallery, nullptr);
    menu2->setPosition(Point::ZERO);
    this->addChild(menu2);
    
    setImage("TB_FACE", -1, -1);
    setImage("TB_HAIR1", -1, -1);
    setImage("TB_HAIR2", -1, -1);
    setImage("TB_EYE", -1, -1);
    setImage("TB_MOUTH", -1, -1);
    setImage("TB_ETC", -1, -1);
    setImage("TB_BG", -1, -1);
    
    setBalloon(1);
   
    return true;
}

void CharacterScene::setImage(std::string tableName, int rowNo, int colorNo){
    auto headList = DatabaseManager::getInstance()->selectDB(tableName, rowNo);
    auto head = headList.front();
    int zOrder = 0;
    if(tableName == "TB_FACE"){
        if (_face != nullptr) {
            _face->removeFromParentAndCleanup(true);
        }
        zOrder = 2;
        _face = Sprite::create(head->image);
        _face->setPosition(head->position);
        _characterBg->addChild(_face, zOrder);
        
        _characterInfo->headNo = head->no;
    }
    else if (tableName == "TB_HAIR1"){
        if(_hair1 != nullptr){
            _hair1->removeFromParentAndCleanup(true);
        }
        zOrder = 4;
        _hair1 = Sprite::create(head->image);
        _hair1->setPosition(head->position);
        _characterBg->addChild(_hair1, zOrder);
        
        _characterInfo->hair1No = head->no;
    }
    else if (tableName == "TB_HAIR2"){
        if (_hair2 != nullptr) {
            _hair2->removeFromParentAndCleanup(true);
        }
        zOrder = 1;
        _hair2 = Sprite::create(head->image);
        _hair2->setPosition(head->position);
        _characterBg->addChild(_hair2, zOrder);
        
        _characterInfo->hair2No = head->no;
    }
    else if (tableName == "TB_EYE"){
        if (_eye != nullptr) {
            _eye->removeFromParentAndCleanup(true);
        }
        zOrder = 3;
        _eye = Sprite::create(head->image);
        _eye->setPosition(head->position);
        _characterBg->addChild(_eye, zOrder);
        
        _characterInfo->eyeNo = head->no;
    }
    else if (tableName == "TB_MOUTH"){
        if (_mouth != nullptr) {
            _mouth->removeFromParentAndCleanup(true);
        }
        zOrder = 3;
        _mouth = Sprite::create(head->image);
        _mouth->setPosition(head->position);
        _characterBg->addChild(_mouth, zOrder);
        
        _characterInfo->mouthNo = head->no;
    }
    else if (tableName == "TB_ETC"){
        if(_etc != nullptr){
            _etc->removeFromParentAndCleanup(true);
        }
        zOrder = 5;
        _etc = Sprite::create(head->image);
        _etc->setPosition(head->position);
        _characterBg->addChild(_etc, zOrder);
        
        _characterInfo->etcNo = head->no;
    }
    else if (tableName == "TB_BG"){
        if(_bgStyle != nullptr){
            _bgStyle->removeFromParentAndCleanup(true);
        }
        zOrder = 0;
        _bgStyle = Sprite::create(head->image);
        _bgStyle->setPosition(head->position);
        _characterBg->addChild(_bgStyle, zOrder);
        
        _characterInfo->bgNo = head->no;
    }
    if(head->isColor){
        Color3B color;
        if(colorNo < 0){
            srand(time(nullptr));
            colorNo = rand() % 4 + 1;
        }
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
        if(tableName == "TB_FACE"){
            _face->setColor(color);
            _characterInfo->headColorNo = colorNo;
        }
        else if (tableName == "TB_HAIR1"){
            _hair1->setColor(color);
            _characterInfo->hair1ColorNo = colorNo;
        }
        else if (tableName == "TB_HAIR2"){
            _hair2->setColor(color);
            _characterInfo->hair2ColorNo = colorNo;
        }
        else if (tableName == "TB_EYE"){
            _eye->setColor(color);
            _characterInfo->eyeColorNo = colorNo;
        }
        else if (tableName == "TB_MOUTH"){
            _mouth->setColor(color);
            _characterInfo->mouthColorNo = colorNo;
        }
        else if (tableName == "TB_ETC"){
            _etc->setColor(color);
            _characterInfo->etcColorNo = colorNo;
        }
        else if (tableName == "TB_BG"){
            _bgStyle->setColor(color);
            _characterInfo->bgColorNo = colorNo;
        }
        
    }
    
}

void CharacterScene::onClickMenu(Ref *object){
    log("onClickMenu");
    setBalloon(((Node *)object)->getTag());
}

void CharacterScene::onClickHome(Ref *object){
    log("onClickHome");
    Director::getInstance()->popScene();
}

void CharacterScene::onClickRandom(Ref *object){
    log("onClickRandom");
    setImage("TB_FACE", -1, -1);
    setImage("TB_HAIR1", -1, -1);
    setImage("TB_HAIR2", -1, -1);
    setImage("TB_EYE", -1, -1);
    setImage("TB_MOUTH", -1, -1);
    setImage("TB_ETC", -1, -1);
    setImage("TB_BG", -1, -1);
}

void CharacterScene::onClickSave(Ref *object){
    log("onClickSave");
    DatabaseManager::getInstance()->insertCharacterDB(_characterInfo);
    this->addChild(TextPopup::create("저장이 완료되었습니다.", false, nullptr), 10);
}

void CharacterScene::onClickGallery(Ref *object){
    log("onClickGallery");
}

void CharacterScene::setBalloon(int position){
    if(_arrow == nullptr){
        auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
        _balloon = Sprite::create("box_list.png");
        _balloon->setPosition(Point(winSize.width / 2, 75));
        this->addChild(_balloon, 1);
        
        _arrow = Sprite::create("box_list2.png");
        _arrow->setAnchorPoint(Point(0.5, 0));
        _balloon->addChild(_arrow);
    }
    
    Point arrowPoint;
    switch (position) {
        case 1:
            arrowPoint = Point(22, _balloon->getContentSize().height);
            break;
        case 2:
            arrowPoint = Point(68, _balloon->getContentSize().height);
            break;
        case 3:
            arrowPoint = Point(113, _balloon->getContentSize().height);
            break;
        case 4:
            arrowPoint = Point(158, _balloon->getContentSize().height);
            break;
        case 5:
            arrowPoint = Point(203, _balloon->getContentSize().height);
            break;
        case 6:
            arrowPoint = Point(248, _balloon->getContentSize().height);
            break;
        case 7:
            arrowPoint = Point(293, _balloon->getContentSize().height);
            break;
    }
    _arrow->setPosition(arrowPoint);
    
    if(_scrollView != nullptr)
        _scrollView->removeFromParentAndCleanup(true);
    
    auto layer = LayerColor::create(Color4B(0, 0, 0, 0), 500, _balloon->getContentSize().height);
    _scrollView = ui::ScrollView::create();
    
    _scrollView->setContentSize(_balloon->getContentSize());
    _scrollView->setInnerContainerSize(layer->getContentSize());
    _scrollView->setScrollBarEnabled(false);
    
    _scrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);

    _balloon->addChild(_scrollView);
    setSubMenuItem(position);
}

void CharacterScene::setSubMenuItem(int position){
    std::string table;
    switch (position) {
        case 1:
            table = "TB_FACE";
            break;
        case 2:
            table = "TB_HAIR1";
            break;
        case 3:
            table = "TB_HAIR2";
            break;
        case 4:
            table = "TB_EYE";
            break;
        case 5:
            table = "TB_MOUTH" ;
            break;
        case 6:
            table = "TB_ETC";
            break;
        case 7:
            table = "TB_BG";
            break;
    }
    _currentTableName = table;
    auto headList = DatabaseManager::getInstance()->selectDB(table, 0);
    int listCnt = headList.size();
    float iconWidth = 0;
    
    for(int i=0;i<listCnt;i++){
        auto head = headList.front();
        char icon[50];
        sprintf(icon, "i_%s", head->image);
        
        auto item = ui::Button::create(icon);
        item->setFocused(false);
        iconWidth = item->getContentSize().width;
        item->addTouchEventListener(CC_CALLBACK_2(CharacterScene::showColorPopup, this));
        
        item->setTag(head->no);
        item->setAnchorPoint(Point(0, 0.5));
        item->setPosition(Point(i * iconWidth + 5 * i, _scrollView->getInnerContainerSize().height / 2));
        _scrollView->addChild(item);
        headList.pop_front();
    }
    
    auto ContainerSize = Size(listCnt * iconWidth + 5 * (listCnt - 1), _scrollView->getInnerContainerSize().height);
    _scrollView->setInnerContainerSize(ContainerSize);
}

void CharacterScene::showColorPopup(Ref *object, ui::Widget::TouchEventType type){
    if(type == ui::Widget::TouchEventType::ENDED)
    {
        auto node = ((Node *)object);
        log("tableName : %s, tag : %d", _currentTableName.c_str(), node->getTag());
        
        auto headList = DatabaseManager::getInstance()->selectDB(_currentTableName, node->getTag());
        auto head = headList.front();
        
        if(!head->isColor){
            setImage(_currentTableName, head->no, -1);
            return;
        }
            
        auto popup = ColorPopup::create(_currentTableName, node->getTag());
        this->addChild(popup, 10);
    }
}
