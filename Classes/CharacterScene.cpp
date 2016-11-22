#include "CharacterScene.h"
#include "DatabaseManager.h"
#include "DevConf.h"

CharacterScene::CharacterScene(){
    _face = nullptr;
    _hair1 = nullptr;
    _hair2 = nullptr;
    _eye = nullptr;
    _mouth = nullptr;
    _etc = nullptr;
    _bgStyle = nullptr;
}

CharacterScene::~CharacterScene(){
    
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
    
    setImage("TB_FACE", -1);
    setImage("TB_HAIR1", -1);
    setImage("TB_HAIR2", -1);
    setImage("TB_EYE", -1);
    setImage("TB_MOUTH", -1);
    setImage("TB_ETC", -1);
    setImage("TB_BG", -1);
   
    return true;
}

void CharacterScene::setImage(std::string tableName, int rowNo){
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
    }
    else if (tableName == "TB_HAIR1"){
        if(_hair1 != nullptr){
            _hair1->removeFromParentAndCleanup(true);
        }
        zOrder = 4;
        _hair1 = Sprite::create(head->image);
        _hair1->setPosition(head->position);
        _characterBg->addChild(_hair1, zOrder);
    }
    else if (tableName == "TB_HAIR2"){
        if (_hair2 != nullptr) {
            _hair2->removeFromParentAndCleanup(true);
        }
        zOrder = 1;
        _hair2 = Sprite::create(head->image);
        _hair2->setPosition(head->position);
        _characterBg->addChild(_hair2, zOrder);
    }
    else if (tableName == "TB_EYE"){
        if (_eye != nullptr) {
            _eye->removeFromParentAndCleanup(true);
        }
        zOrder = 3;
        _eye = Sprite::create(head->image);
        _eye->setPosition(head->position);
        _characterBg->addChild(_eye, zOrder);
    }
    else if (tableName == "TB_MOUTH"){
        if (_mouth != nullptr) {
            _mouth->removeFromParentAndCleanup(true);
        }
        zOrder = 3;
        _mouth = Sprite::create(head->image);
        _mouth->setPosition(head->position);
        _characterBg->addChild(_mouth, zOrder);
    }
    else if (tableName == "TB_ETC"){
        if(_etc != nullptr){
            _etc->removeFromParentAndCleanup(true);
        }
        zOrder = 5;
        _etc = Sprite::create(head->image);
        _etc->setPosition(head->position);
        _characterBg->addChild(_etc, zOrder);
    }
    else if (tableName == "TB_BG"){
        if(_bgStyle != nullptr){
            _bgStyle->removeFromParentAndCleanup(true);
        }
        zOrder = 0;
        _bgStyle = Sprite::create(head->image);
        _bgStyle->setPosition(head->position);
        _characterBg->addChild(_bgStyle, zOrder);
    }
}

void CharacterScene::onClickMenu(Ref *object){
    log("onClickMenu");
}

void CharacterScene::onClickHome(Ref *object){
    log("onClickHome");
}

void CharacterScene::onClickRandom(Ref *object){
    log("onClickRandom");
}

void CharacterScene::onClickSave(Ref *object){
    log("onClickSave");
}

void CharacterScene::onClickGallery(Ref *object){
    log("onClickGallery");
}
