#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "OpningScene.h"
#include "NendModule.h"
#include "GameCenterBridge.h"
#include "NendInterstitialModule.h"
#include <stdio.h>
#include "AppCCloudPlugin.h"




USING_NS_CC;
#define selfFrame Director::getInstance() -> getWinSize()
//表示文字数
#define maxPoint  10
//文字のフォントサイズ
#define fontSize 50


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    

    //背景色のグラデーション
    auto bgGradient = LayerGradient::create(Color4B(255,255,255,255), Color4B(255,255,255,255));
    this -> addChild(bgGradient);

    tatatanButton = Sprite::create("black_ring.png");
    tatatanButton->setScale(0.1f);
    tatatanButton->setColor(Color3B::BLACK);
    tatatanButton -> setPosition(Vec2(selfFrame.width/2, selfFrame.height*1/5));
    addChild(tatatanButton,10);
    
    //ラベル
    Label *tatatanLabel = Label::createWithSystemFont("ド","KouzanBrushFont",700);
    tatatanLabel->setColor(Color3B::BLACK);
    tatatanLabel -> setPosition(Vec2(tatatanButton->getContentSize().width / 2, tatatanButton->getContentSize().height / 2));
    tatatanButton->addChild(tatatanLabel,10);
    
    
    //装飾ラベル
    Label *sousyokuLabel1 = Label::createWithSystemFont("↑リズムに合わせて","KouzanBrushFont",35);
    sousyokuLabel1->setColor(Color3B::BLACK);
    sousyokuLabel1->setPosition(Vec2(0 + selfFrame.width/30 + sousyokuLabel1->getContentSize().width/2, selfFrame.height*3/5));
    sousyokuLabel1->setName("soushoku1");

    this->addChild(sousyokuLabel1);

    //装飾ラベル2
    Label *sousyokuLabel2 = Label::createWithSystemFont("↓ドを叩け！！","KouzanBrushFont",35);
    sousyokuLabel2->setColor(Color3B::BLACK);
    sousyokuLabel2->setPosition(Vec2(0 + selfFrame.width/5*3, selfFrame.height*2.5/5));
    sousyokuLabel2->setName("soushoku2");
    this->addChild(sousyokuLabel2);
    
    
    //スコア用装飾ラベル
    Label *scoreSousyokuLabel1 = Label::createWithSystemFont("残り","KouzanBrushFont",50);
    scoreSousyokuLabel1->setColor(Color3B::BLACK);
    scoreSousyokuLabel1->setPosition(Vec2(0 + selfFrame.width/30 + scoreSousyokuLabel1->getContentSize().width/2, selfFrame.height*4.3/5));
    scoreSousyokuLabel1->setName("score1");
    this->addChild(scoreSousyokuLabel1);
    
    //スコア用装飾ラベル2
    Label *scoreSousyokuLabel2 = Label::createWithSystemFont("ｿｲﾔｯ!!","KouzanBrushFont",50);
    scoreSousyokuLabel2->setColor(Color3B::BLACK);
    scoreSousyokuLabel2->setPosition(Vec2(selfFrame.width - scoreSousyokuLabel2->getContentSize().width/2, selfFrame.height*4.3/5));
    scoreSousyokuLabel2->setName("score2");
    this->addChild(scoreSousyokuLabel2);
    
    //装飾ラベルの中間を計算
    float center = scoreSousyokuLabel2->getPosition().x - scoreSousyokuLabel2->getContentSize().width/2;
    center = center - (scoreSousyokuLabel1->getPosition().x + scoreSousyokuLabel1->getContentSize().width/2);
    
    //スコアラベル
    scoreLabel = Label::createWithSystemFont(std::to_string(clearPoint),"KouzanBrushFont",70);
    scoreLabel->setColor(Color3B::BLACK);
    scoreLabel->setPosition(Vec2(scoreSousyokuLabel1->getPosition().x + scoreSousyokuLabel1->getContentSize().width/2 + (center / 2)  /*+ scoreLabel->getContentSize().width/2*/, selfFrame.height*4.3/5));
    scoreLabel->setName("score3");
    this->addChild(scoreLabel);
    
    
    
    //リトライボタン
    retryButton = Sprite::create();
    retryButton -> setTextureRect(cocos2d::Rect(0, 0, selfFrame.width/3, selfFrame.width/7));
    retryButton -> setColor(Color3B::WHITE);
    retryButton -> setPosition(Vec2(0 + retryButton->getContentSize().width/2, selfFrame.height - retryButton->getContentSize().height/2));
    
    //ラベル作成
    Label *retryLabel = Label::createWithSystemFont("再戦","KouzanBrushFont",40);
    retryLabel -> setPosition(Vec2(retryButton->getContentSize().width / 2, retryButton->getContentSize().height / 2));
    retryLabel ->setColor(Color3B::BLACK);
    
    retryButton -> addChild(retryLabel);
    
    this->addChild(retryButton);
    
    
    //トップボタン
    topButton = Sprite::create();
    topButton -> setTextureRect(cocos2d::Rect(0, 0, selfFrame.width/3, selfFrame.width/7));
    topButton -> setColor(Color3B::WHITE);
    topButton -> setPosition(Vec2(selfFrame.width - topButton->getContentSize().width/2, selfFrame.height - topButton->getContentSize().height/2));
    
    //ラベル作成
    Label *topLabel = Label::createWithSystemFont("敗走","KouzanBrushFont",40);
    topLabel -> setPosition(Vec2(topButton->getContentSize().width / 2, topButton->getContentSize().height / 2));
    topLabel ->setColor(Color3B::BLACK);
    
    topButton -> addChild(topLabel);
    
    this->addChild(topButton);
    
    
    
    //appCloud(3分の1で出現)
    if(arc4random_uniform(3) == 0){
    AppCCloudPlugin::Ad::showCutin();
    }




    
    
    
    
    //解答文字の表示用スプライトを作成して配列に入れる。
    for(int tmp = 0 ; tmp < maxPoint ; tmp++){

        Sprite *tantan = Sprite::create();
        tantan->setTextureRect(cocos2d::Rect(0, 0, visibleSize.width/10, visibleSize.width/10));
        tantan->setColor(Color3B::WHITE);
        
        if(tmp == 0){
            
            tantan->setPosition(Vec2(0 + tantan->getContentSize().width,selfFrame.height/8*3));
            
        }else{
            //一つ前のオブジェクトの位置から次のオブジェクトの位置を置く。
            Sprite *preTantan = tatatans.at(tmp - 1);
            Vec2 prePosition = preTantan->getPosition();
            
            tantan->setPosition(Vec2(prePosition.x + (preTantan->getContentSize().width),prePosition.y));
            
        }
        
        tatatans.pushBack(tantan);
        
        this->addChild(tantan);
        
        
    }

    //出題文字の表示用スプライトを作成して配列に入れる。
    for(int tmp = 0 ; tmp < maxPoint ; tmp++){
        
        Sprite *tantan = Sprite::create();
        tantan->setTextureRect(cocos2d::Rect(0, 0, visibleSize.width/10, visibleSize.width/10));
        tantan->setColor(Color3B::WHITE);
        
        if(tmp == 0){
            
            tantan->setPosition(Vec2(0 + tantan->getContentSize().width,selfFrame.height/8*6));
            
        }else{
            //一つ前のオブジェクトの位置から次のオブジェクトの位置を置く。
            Sprite *preTantan = questTatatans.at(tmp - 1);
            Vec2 prePosition = preTantan->getPosition();
            
            tantan->setPosition(Vec2(prePosition.x + (preTantan->getContentSize().width),prePosition.y));
            
        }
        
        questTatatans.pushBack(tantan);
        
        this->addChild(tantan);
        
        
    }

    
    

    
    /**************　ドッチイベント設定  ******************/
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    //listener -> setSwallowTouches(_swallowsTouches);
    
    
    //各イベントの割り当て
    listener -> onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
    listener -> onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded,this);
    
    //イベントディスパッチャようにリスナーを追加する
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
    
    /*************　　ドッチイベント設定  終 ****************/
    
    
    //エフェクトプリロード
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("SOIYA.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("taiko.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("hue.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("hueloop.mp3");
    
    
    //最初の笛
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("hue.mp3", false);
 
    //初期化
    frameCount = 0;
    tatatanPoint = 0;
    nobasiFlag = false;
    doubleFrag = false;
    score = clearPoint;
    clearFlag = false;

    //最初の文字を出す
    this->creatQuestion();
    
    //nend(インタースティシャル)本番用

    char interstitialAppKey[] = "962fcab0cd5070fa7fa2dcd024b7111c83b00f92";
    char interstitialSpotID[] = "263142";

    //nend(インタースティシャル)テスト用
//    char interstitialAppKey[] = "308c2499c75c4a192f03c02b2fcebd16dcb45cc9";
//    char interstitialSpotID[] = "213208";

    NendInterstitialModule::createNADInterstitial(interstitialAppKey, interstitialSpotID);
    
    //ランダム係数の更新
 //   srand((unsigned int)time(NULL));

    return true;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event){
    

    //ポイントの取得
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);

    //再戦ボタン
    if(retryButton->getBoundingBox().containsPoint(touchPoint)){
        
        //画面遷移
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, HelloWorld::createScene(), Color3B::BLACK));
        
    }
    
    //敗戦ボタン
    if(topButton->getBoundingBox().containsPoint(touchPoint)){
     
        //画面遷移
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, OpningScene::createScene(), Color3B::BLACK));
        
    }



    
    
    if(tatatanButton->getBoundingBox().containsPoint(touchPoint)){
        
    
    //クリア時のみ動く処理
        if(clearFlag == true){

            return true;
            
        }
        


    //最初に動く処理
        if(this->getChildByName("soushoku1")){
            
        //中央の文字部分を削除
            //スコア1の削除
            Node *Label1 = this->getChildByName("soushoku1");
            Label1->removeFromParent();
            //スコア2の削除
            Node *Label2 = this->getChildByName("soushoku2");
            Label2->removeFromParent();
            
        //BGMを鳴らしていく
            //BGM再生
            CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1);
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("hueloop.mp3",true);
            

            //開始時間の記録
            struct timeval time;
            gettimeofday(&time, NULL);
            startTime = time.tv_sec * 1000ull + time.tv_usec / 1000ull;
                
                
                
            //時間の計測
            struct timeval time2;
            gettimeofday(&time2, NULL);
            unsigned long long currentTime = time2.tv_sec * 1000ull + time2.tv_usec / 1000ull;
            currentTime = currentTime - startTime;
                
            //秒数を取り出す
            unsigned long sec = currentTime / 1000;
            //ミリ秒を取り出す
            unsigned long mSec = (currentTime % 1000) / 10;

            //分を作る
            unsigned long min = (int)sec / 60;
            
            //分の量だけ秒から削る
            sec = sec - (min * 60);
            
        
            //Objective-cにおけるStringWithFormatみたいなメソッド
            std::string timeString = StringUtils::format("時間 %02lu:%02lu:%02lu",min,sec,mSec);
        
            //ラベル作成
            timeLabel = Label::createWithSystemFont(timeString,"KouzanBrushFont",35);
            timeLabel->setColor(Color3B::BLACK);
            timeLabel->setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
            timeLabel->setName("timeLabel");
            
            this->addChild(timeLabel,10);;

            
        
            
            //フレームのフラグをオフにする
            frameFlag = false;

            //フレーム毎の監視を開始する。
            this->scheduleUpdate();

            
        }

        
        
        
    
        //ドを入れる
        this->creatAnswer(1);
        //BGM再生
        // EFFECT
//        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("SOUND_EFFECT.mp3",false);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("taiko.mp3",false);
//        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kodaiko.mp3",false);

        

    }

    
    return true;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event){
    
    //クリア時のみ動く処理
    if(clearFlag == true){
        return;
    }
    
    
    //ーで間違えて入力していた場合、指を離した時にンが入力されてしまう。
    //なのでフラグ管理をして防いでいます
    //また、伸ばし棒フラグをオフにします
    if(nFlag == true){
        nFlag = false;
        //伸ばし棒フラグをオフ
        nobasiFlag = false;
        //フレーム毎の監視を終了する。
        frameFlag = false;
        return;
    }
    

    //デバッグ用
    if(!this->debugMethod()){return;}

    //二連続タップか判定する用の処理を開始
    if(frameCount <= 6){
        doubleFrag = true;
        frameCount = 0;
        return;
    }
    
    //ンの処理
    //7フレーム以上、4文字以上の場合、二連続ドップの受付時間が超えた場合、ンを表示して終了
    if((frameCount >= 7 && nobasiFlag == true )|| tatatanPoint >= maxPoint || doubleFrag == true){
        
        

        this->creatAnswer(3);
        
        
        
        //フレーム毎の監視を終了する。
        frameFlag = false;

    }
    

}

void HelloWorld::update( float frame )
{
    
    //時間の計測
    if(this->getChildByName("timeLabel")){
    
        //時間の計測
        struct timeval time2;
        gettimeofday(&time2, NULL);
        unsigned long long currentTime = time2.tv_sec * 1000ull + time2.tv_usec / 1000ull;
        currentTime = currentTime - startTime;
        
        //秒数を取り出す
        unsigned long sec = currentTime / 1000;
        //ミリ秒を取り出す
        unsigned long mSec = (currentTime % 1000) / 10;
        
        //分を作る
        unsigned long min = (int)sec / 60;
        
        //分の量だけ秒から削る
        sec = sec - (min * 60);
        
        
        //Objective-cにおけるStringWithFormatみたいなメソッド
        std::string timeString = StringUtils::format("時間 %02lu:%02lu:%02lu",min,sec,mSec);
        
        //ラベルの文字に設定

        timeLabel -> setString(timeString);
        
        

    }

    
    
    if(frameFlag == false){return;}
    
    //フレームのカウント
    frameCount++;
    
    //二連続ドップの判定時に入る処理
    if(doubleFrag == true){
        
        //7フレーム以上入力なしでンを挿入(ドンというリズムと判定)
        if(frameCount >= 7){
            
            //メソッド呼び出しで手抜き
            this->onTouchEnded(NULL, NULL);
            // EFFECTの場合
            CocosDenshion::SimpleAudioEngine::getInstance()
            ->stopEffect(true);

            
            //ダブルドップ検知用のフラグをオフに
            doubleFrag = false;
        }
        

        
        
        return;
        
    }
    
    
    //伸ばしの処理(伸ばし棒が表示済か判定。ドーーンとなるのを防ぐ)
    if(nobasiFlag == false){
        
        //7フレーム以上か判定(ドーというリズムと判定)
        if(frameCount >= 7){

            //ンを表示
            this->creatAnswer(2);
            
            return;
 
        }
        
    }
}

//出題文字を生成する
void HelloWorld::creatQuestion(){

    //お掃除
    for (int tmp = 0; tmp < maxPoint; tmp++) {
        //文字格納スプライトを取り出してラベルを削除
        Sprite *tantan = questTatatans.at(tmp);
        tantan->removeAllChildren();
    }
    
    //カウント0でゲーム終了の処理へ
    if(clearPoint == 0){
        this->gameClear();
        return;
    }


    //カウント
    int count = 0;
    
    
    //9文字以上で終了する
    while(count < maxPoint - 1){
        //文字の種類を指示する変数
        int number;
        //ランダムの変数
        int tmp;
        
//残りの字数で出る文字に制限を加える
        //カウント8の時はドンで終
        if(count == 8){
            tmp = 0;
        }
        
        //カウント7の時はドン、ドーン、ドドンの三択
        if(count == 7){
        		tmp = arc4random_uniform(3);
        }
        
        //カウント6の時はドンドドンドーンドドドン
        if(count == 6){

                tmp = arc4random_uniform(4);

        }
        
        //カウント5の時はドンドドンドーンドドドンドドドドドンドドドドドン
        if(count == 5){
        		//tmp = 0 + (int)(rand()*(4-0+1.0)/(1.0+RAND_MAX));

                tmp = arc4random_uniform(5);

        }
        //カウント4以下はすべて出る
        if(count <= 4){
        		//tmp = 0 + (int)(rand()*(5-0+1.0)/(1.0+RAND_MAX));

                tmp = arc4random_uniform(6);

        }

        

        
//ランダムででた数によって生成する文字列を指示する値を変える。
        switch (tmp) {
            case 0:
                number = 13;
                break;
            case 1:
                number = 113;
                break;
            case 2:
                number = 123;
                break;
            case 3:
                number = 1113;
                break;
            case 4:
                number = 11113;
                break;
            case 5:
                number = 111113;
                break;
            default:
                break;
        }

        
        //面倒なのでループ
        int idx = 100000;
        while(idx != 0){
            switch (number / idx) {
                case 0:
                    //何もしない
                    break;
                case 1:
                        //ド
                        this->createCharacter(1, questTatatans.at(count));
                        //カウントアップ
                        count++;

                        break;
                case 2:
                        //ー
                        this->createCharacter(2, questTatatans.at(count));
                        //カウントアップ
                        count++;
                        break;
                case 3:
                        //ン
                        this->createCharacter(3, questTatatans.at(count));
                        //カウントアップ
                        count++;
                        break;
                default:
                    break;
                    
                    
            }
            
            number = number % idx;
            idx = idx / 10;
            
            
        }
        
        
        
    }
    
    
}

//スプライトを受け取って文字を入れる。
void HelloWorld::createCharacter(int number,Sprite *tantan){
    
    Label *text;
    
    //スプライトに文字入れる。
    switch (number) {
        case 1:
            
            text = Label::createWithSystemFont("ド","KouzanBrushFont",fontSize);
            text->setTag(1);

            break;
            
        case 2:
            
            text = Label::createWithSystemFont("ー","KouzanBrushFont",fontSize);
            text->setTag(2);
            break;
            
        case 3:
            
            text = Label::createWithSystemFont("ン","KouzanBrushFont",fontSize);
            text->setTag(3);
            break;
            
        default:
            
            break;
            
    }
    
    text->setName("ラベル");
    text->setColor(Color3B::BLACK);
    tantan->addChild(text);
    


    return;
    
}

//正解の文字を入力していくコントローラ
bool HelloWorld::creatAnswer(int characterNumber){
    
    //配列から取り出す
    Sprite *tantan = tatatans.at(tatatanPoint);

    //スプライトに文字入れる。
    this->createCharacter(characterNumber, tantan);
    
    if(!this->check()){
        
        //取り消しの処理
        tatatans.at(tatatanPoint) ->removeAllChildren();
        
        CCLOG("%d",questTatatans.at(tatatanPoint)->getChildByName("ラベル")->getTag());
        

        //正解がーかンの場合は更に遡って削除
        if(questTatatans.at(tatatanPoint)->getChildByName("ラベル")->getTag() != 1 ){
        
            //ポイントを1減らして調整
            tatatanPoint--;
            tatatans.at(tatatanPoint) ->removeAllChildren();
            
            

        }
        
        if(tatatanPoint != 0){
            
            //ドを消し尽くす
            while (questTatatans.at(tatatanPoint - 1)->getChildByName("ラベル")->getTag() == 1 ) {
                //ポイントを1減らして調整
                tatatanPoint--;
                tatatans.at(tatatanPoint) ->removeAllChildren();
                
                //0文字まで消えた場合はwhileから抜け出すように小細工
                if(tatatanPoint == 0){
                    break;
                }
                
            }
            
        }


        
        //不正解の文字によってフラグを整理
        //ドの時は何もしない
        if(characterNumber == 1){
            doubleFrag = false;
        }
        //ーの時は伸ばし棒フラグをオフにしておく
        if(characterNumber == 2){
            //伸ばし棒の表示済フラグをオンにしてご作動の防止
            nobasiFlag = true;
            nFlag = true;
        }
        //ンの時は伸ばし棒フラグをオフにしておく
        if(characterNumber == 3){
            nobasiFlag = false;
        }
        
        
        return false;
    }

    //どの文字かで挙動を変える。
    switch (characterNumber) {
        case 1:

            //ダブルドップ検知のフラグをオフに
            doubleFrag = false;
            
            //フレームカウントを初期化
            frameCount = 0;
            
            //フレーム毎の監視を開始する。
            frameFlag = true;

            break;
            
        case 2:
            
            //伸ばし棒の表示済フラグをオンに
            nobasiFlag = true;
            break;
            
        case 3:
            
            //伸ばし棒フラグをオフ
            nobasiFlag = false;
            break;
        default:
            break;
    }
    
    
    tatatanPoint++;
    
    //ポイントがマックスで初期化
    if(tatatanPoint == questTatatans.size() - 1){
        
        //文字数0の際は、前回入れた文字ラベルを削除する
        
            //問題文と正解の文字を削除
            for (int tmp = 0; tmp < questTatatans.size(); tmp++) {
                //文字格納スプライトを取り出してラベルを削除
                Sprite *tantan = tatatans.at(tmp);
                tantan->removeAllChildren();
                Sprite *questTantan = questTatatans.at(tmp);
                questTantan->removeAllChildren();
            }
        
            //カウントを下げる
            clearPoint--;
            //表示文字を変更する
            scoreLabel->setString(std::to_string(clearPoint));
        
            tatatanPoint = 0;
        
            //次の問題を生成
            this->creatQuestion();
        
            //そいや！！
            // EFFECT
            CocosDenshion::SimpleAudioEngine::getInstance()
            ->playEffect("SOIYA.mp3",false);


        
    }
    
    return true;
}

//文字の正誤を確認する。
bool HelloWorld::check(){
    
    Sprite *answerSprite = tatatans.at(tatatanPoint);
    Sprite *questionSprite = questTatatans.at(tatatanPoint);
    
    Node *answerLabel = answerSprite->getChildByName("ラベル");
    Node *questionLabel = questionSprite->getChildByName("ラベル");
    
    if(answerLabel->getTag() == questionLabel->getTag()){
    
        //正解
        return true;
        
    }
    
    //不正解
    return false;
    
}

void HelloWorld::gameClear(){
    
//広告呼び出し
   NendInterstitialModule::showNADInterstitialView();
//クリアフラグをtrueに
    clearFlag = true;
    
//毎フレームの監視を停止
    this->unscheduleUpdate();
    
//BGMの終了
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();


//クリア時間を記録
    struct timeval time2;
    gettimeofday(&time2, NULL);
    endTime = time2.tv_sec * 1000ull + time2.tv_usec / 1000ull;
    endTime = endTime - startTime;
    CCLOG("%d",(int)endTime/10);
    
//クリア時間の表示
    //秒数を取り出す
    unsigned long sec = endTime / 1000;
    //ミリ秒を取り出す
    unsigned long mSec = (endTime % 1000) / 10;
    
    //分を作る
    unsigned long min = (int)sec / 60;
    
    //分の量だけ秒から削る
    sec = sec - (min * 60);
    
    
    //Objective-cにおけるStringWithFormatみたいなメソッド
    std::string timeString = StringUtils::format("時間 %02lu:%02lu:%02lu",min,sec,mSec);
    
    //ラベルの文字に設定
    timeLabel -> setString(timeString);
    
//ラベルの削除
    this->getChildByName("score1")->removeFromParent();
    this->getChildByName("score2")->removeFromParent();
    this->getChildByName("score3")->removeFromParent();

    
//ハイスコアか確認
    //ユーザーデフォルトの作成
    UserDefault *userDef = UserDefault::getInstance();
    //数をならす
    int score = (int)endTime / 10;
    
    int highScore;
    
    //初回のみハイスコアになるように小細工
    if(userDef->getIntegerForKey("score") == 0){
        highScore = 99999999;
    }else{
        highScore = userDef->getIntegerForKey("score");
    }
    
    
    
    //ハイスコアかどうか確認
    if(score < highScore){
        //ハイスコア表示
        Sprite *highScoreSprite = Sprite::create();
        highScoreSprite -> setTextureRect(cocos2d::Rect(0, 0, selfFrame.width/1.2, selfFrame.width/2));
        highScoreSprite ->setColor(Color3B::WHITE);
        highScoreSprite -> setPosition(Vec2(selfFrame.width/2 , selfFrame.height/3*2 ));
        this -> addChild(highScoreSprite);
        
        //ラベル表示
        auto highScoreLabel = Label::createWithSystemFont("ハイスコア！","KouzanBrushFont",50);
        highScoreLabel -> setPosition(Vec2(highScoreSprite->getContentSize().width / 2, highScoreSprite->getContentSize().height / 2));
        highScoreLabel ->setColor(Color3B::BLACK);
        highScoreSprite -> addChild(highScoreLabel);
        
        //動きをつける
        auto action1 = ScaleBy::create(0.4,1.3);
        auto action2 = ScaleBy::create(0.4,0.76923077);
        auto sequence = Sequence::create(action1,action2,NULL);
        
        auto repeatForever = RepeatForever::create(sequence);
        
        highScoreSprite -> runAction(repeatForever);

        
        //ハイスコアを登録する処理
        userDef->setIntegerForKey("score", score);
        //保存
        userDef->flush();
        
        //GameCenterへ送信
        GameCenterBridge::postHighScore("grp.ranking", score);
    }
    

    
}

//デバッグ用メソッド
bool HelloWorld::debugMethod(){
    
    if(tatatanPoint >= maxPoint){
        
        //ポイントの初期化
        tatatanPoint = 0;
        
        //カウントの初期化
        frameCount = 0;
        
        //フレーム毎の監視を終了する。
        this->unscheduleUpdate();
        
        //伸ばし棒フラグをオフにする。
        nobasiFlag = false;
        
        return false;
    }
    
    return true;

}


void HelloWorld::menuCloseCallback(Ref* pSender)
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

// 任意のイベント
void HelloWorld::TerminateAppMenuCallback(cocos2d::Ref* pSender)
{
    // アプリケーションを終了する前に呼び出してください。
    // appC cloud 終了
    AppCCloudPlugin::finish();
    
}
