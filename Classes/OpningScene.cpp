//
//  OpningScene.cpp
//  tatatanTest
//
//  Created by yasutomo on 2014/11/05.
//
//
#include "OpningScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "NendModule.h"
#include "GameCenterBridge.h"
//#include "AppCCloudPlugin.h"


USING_NS_CC;
#define selfFrame Director::getInstance() -> getWinSize()

Scene* OpningScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = OpningScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool OpningScene::init(){
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //背景色のグラデーション
    auto bgGradient = LayerGradient::create(Color4B(255,255,255,255), Color4B(255,255,255,255));
    this -> addChild(bgGradient);

    //ドーンのスプライト
    Sprite *topSprite = Sprite::create("done.png");

    topSprite -> setPosition(Vec2(selfFrame.width/2 , selfFrame.height/3*2 ));
    topSprite -> setScale(0.2f);
    
    this -> addChild(topSprite);
    
    auto action1 = ScaleBy::create(0.4,1.3);
    auto action2 = ScaleBy::create(0.4,0.76923077);
    auto sequence = Sequence::create(action1,action2,NULL);
    
    auto repeatForever = RepeatForever::create(sequence);
    
    topSprite -> runAction(repeatForever);
    
    
    //スタートボタン
    start = Sprite::create();
    start -> setTextureRect(cocos2d::Rect(0, 0, selfFrame.width/1.8, selfFrame.width/4));
    start -> setColor(Color3B::WHITE);
    start -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/5*2));
    
    //ラベル作成
    Label *startLabel = Label::createWithSystemFont("開始!","KouzanBrushFont",80);
    startLabel -> setPosition(Vec2(start->getContentSize().width / 2, start->getContentSize().height / 2));
    startLabel ->setColor(Color3B::BLACK);
    
    start -> addChild(startLabel);
    
    this->addChild(start);

    //ゲームセンターへのログイン
    GameCenterBridge::loginGameCenter();
    
    
    //ランキング
    ranking = Sprite::create();
    ranking -> setTextureRect(cocos2d::Rect(0, 0, selfFrame.width/1.8, selfFrame.width/4));
    ranking -> setColor(Color3B::WHITE);
    ranking -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/5));
    
    //ラベル作成
    Label *rankingLabel = Label::createWithSystemFont("序列!","KouzanBrushFont",80);
    rankingLabel -> setPosition(Vec2(ranking->getContentSize().width / 2, ranking->getContentSize().height / 2));
    rankingLabel ->setColor(Color3B::BLACK);
    
    ranking -> addChild(rankingLabel);
    
    this->addChild(ranking);
    
    /**************　ドッチイベント設定  ******************/
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    //listener -> setSwallowTouches(_swallowsTouches);

    //各イベントの割り当て
    listener -> onTouchBegan = CC_CALLBACK_2(OpningScene::onTouchBegan,this);
    listener -> onTouchEnded = CC_CALLBACK_2(OpningScene::onTouchEnded,this);
    listener -> onTouchMoved = CC_CALLBACK_2(OpningScene::onTouchMoved,this);

    
    //イベントディスパッチャようにリスナーを追加する
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
    
    /*************　　ドッチイベント設定  終 ****************/
    
    
    //エフェクトプリロード
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("SOIYA.mp3");
    
    //BGM再生
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("hueloop.mp3",true);
    
    //nend(本番用)
    char apiKey[] = "33f7cda082e680f88ea5537bb4f24d3f16818379";
    char spotID[] = "264071";

    //nend(テスト用)
//char apiKey[] = "a6eca9dd074372c898dd1df549301f277c53f2b9";
//char spotID[] = "3172";
    
    
    NendModule::createNADViewBottom(apiKey, spotID);
    
    //appCloud
//    AppCCloudPlugin::Ad::showSimpleView(AppCCloudPlugin::BOTTOM);
    
    
    //ハイスコアを取る
    //初回は表示させないようにする
    
    UserDefault *userDef = UserDefault::getInstance();

    if(userDef->getIntegerForKey("score") != 0){
        
        auto score = userDef->getIntegerForKey("score");
        
        //秒数を取り出す
        unsigned long sec = score / 100;
        //ミリ秒を取り出す
        unsigned long mSec = (score % 100);
        //分を作る
        unsigned long min = (int)sec / 60;


        auto scoreLabel = Label::createWithSystemFont(StringUtils::format("最速演舞：%02lu:%02lu:%02lu",min,sec,mSec), "KouzanBrushFont", 35);
        
        scoreLabel->setColor(Color3B::BLACK);
        
        scoreLabel->setPosition(Vec2(0+scoreLabel->getContentSize().width/2,selfFrame.height-scoreLabel->getContentSize().height));
                                
                                this->addChild(scoreLabel);

    }
    

    
    return true;
}

bool OpningScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){

    //ポイントの取得
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
    //スタート処理
    if(start->getBoundingBox().containsPoint(touchPoint)){
        
        auto action1 = ScaleBy::create(0.2,1.3);
        auto action2 = ScaleBy::create(0.2,0.76923077);
        auto sequence = Sequence::create(action1,action2,NULL);
        
        auto repeatForever = RepeatForever::create(sequence);
        
        start -> runAction(repeatForever);

        
        //そいや！
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("SOIYA.mp3", false);

        
        return true;
    }
    
    //ランキング処理
    if(ranking->getBoundingBox().containsPoint(touchPoint)){
        
        auto action1 = ScaleBy::create(0.2,1.3);
        auto action2 = ScaleBy::create(0.2,0.76923077);
        auto sequence = Sequence::create(action1,action2,NULL);
        
        auto repeatForever = RepeatForever::create(sequence);
        
        ranking -> runAction(repeatForever);


        //そいや！
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("SOIYA.mp3", false);
        
        
        return true;

    }

    
    
    return true;
}

void OpningScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){

    //ポイントの取得
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);

    if(start -> getNumberOfRunningActions() > 0){
        
        if(start->getBoundingBox().containsPoint(touchPoint)){
            return;
        }else{
            start -> stopAllActions();
            
            //リンクを切る
            start->removeFromParent();
            //removeAllChildrenすると何故か落ちるのでコメント化
            //start->removeAllChildren();
            
            //スタートボタン
            start = Sprite::create();
            start -> setTextureRect(cocos2d::Rect(0, 0, selfFrame.width/1.8, selfFrame.width/4));
            start -> setColor(Color3B::WHITE);
            start -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/5*2));
            
            //ラベル作成
            Label *startLabel = Label::createWithSystemFont("開始!","KouzanBrushFont",80);
            startLabel -> setPosition(Vec2(start->getContentSize().width / 2, start->getContentSize().height / 2));
            startLabel ->setColor(Color3B::BLACK);
            
            start -> addChild(startLabel);
            
            this->addChild(start);

            
            
            return;
        }

        
    }
    
    if(ranking -> getNumberOfRunningActions() > 0){
        
        if(ranking->getBoundingBox().containsPoint(touchPoint)){
            return;
        }else{
            ranking -> stopAllActions();

            //リンクを切る
            ranking->removeFromParent();
            
            //removeAllChildrenすると何故か落ちるのでコメント化
            //ranking->removeAllChildren();

            
            //ランキング
            ranking = Sprite::create();
            ranking -> setTextureRect(cocos2d::Rect(0, 0, selfFrame.width/1.8, selfFrame.width/4));
            ranking -> setColor(Color3B::WHITE);
            ranking -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/5));
            
            //ラベル作成
            Label *rankingLabel = Label::createWithSystemFont("序列!","KouzanBrushFont",80);
            rankingLabel -> setPosition(Vec2(ranking->getContentSize().width / 2, ranking->getContentSize().height / 2));
            rankingLabel ->setColor(Color3B::BLACK);
            
            ranking -> addChild(rankingLabel);
            
            this->addChild(ranking);

            return;
        }

        
    }

    
    
}



void OpningScene::onTouchEnded(Touch *touch, Event *unused_event){
    
    

    
    //ポイントの取得
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    

    
    //ゲームスタートの処理
    if(start -> getNumberOfRunningActions() > 0){
        
        if(start->getBoundingBox().containsPoint(touchPoint)){
            
            start -> stopAllActions();
            
            //リンクを切る
            start->removeFromParent();
            //removeAllChildrenすると何故か落ちるのでコメント化
            //start->removeAllChildren();
            
            //スタートボタン
            start = Sprite::create();
            start -> setTextureRect(cocos2d::Rect(0, 0, selfFrame.width/1.8, selfFrame.width/4));
            start -> setColor(Color3B::WHITE);
            start -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/5*2));
            
            //ラベル作成
            Label *startLabel = Label::createWithSystemFont("開始!","KouzanBrushFont",80);
            startLabel -> setPosition(Vec2(start->getContentSize().width / 2, start->getContentSize().height / 2));
            startLabel ->setColor(Color3B::BLACK);
            
            start -> addChild(startLabel);
            
            this->addChild(start);

            
            
            //画面遷移
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, HelloWorld::createScene(), Color3B::BLACK));
            return;
        }
        
    }
    
    //ランキングの処理
    if(ranking -> getNumberOfRunningActions() > 0){
        
        if(ranking->getBoundingBox().containsPoint(touchPoint)){
            //ランキング処理へ
            ranking -> stopAllActions();
            
            //リンクを切る
            ranking->removeFromParent();
            
            //removeAllChildrenすると何故か落ちるのでコメント化
            //ranking->removeAllChildren();
            
            
            //ランキング
            ranking = Sprite::create();
            ranking -> setTextureRect(cocos2d::Rect(0, 0, selfFrame.width/1.8, selfFrame.width/4));
            ranking -> setColor(Color3B::WHITE);
            ranking -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/5));
            
            //ラベル作成
            Label *rankingLabel = Label::createWithSystemFont("序列!","KouzanBrushFont",80);
            rankingLabel -> setPosition(Vec2(ranking->getContentSize().width / 2, ranking->getContentSize().height / 2));
            rankingLabel ->setColor(Color3B::BLACK);
            
            ranking -> addChild(rankingLabel);
            
            this->addChild(ranking);

            
            //ラキング画面の表示
            GameCenterBridge::openRanking();
            return;
        }
        
    }

    
    
    

}


void OpningScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
