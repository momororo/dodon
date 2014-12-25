#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
protected:
    
    cocos2d::Sprite *tatatanButton;
    
    /***************** タッチイベント用変数 ***********************/
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
//    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
//    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    /***************** タッチイベント用変数 終***********************/
    
    //二連続タップ用判定フラグ
    bool doubleFrag;
    //フレームカウント
    int frameCount;
    //文字出現回数
    int tatatanPoint;
    //伸ばし棒のフラグ
    int nobasiFlag;
    //解答用の配列を作る
    cocos2d::Vector<cocos2d::Sprite*>tatatans = cocos2d::Vector<cocos2d::Sprite*>();
    
    //見本用の配列を作る
    cocos2d::Vector<cocos2d::Sprite*>questTatatans = cocos2d::Vector<cocos2d::Sprite*>();
    //出題文字数の管理
    int questCount;
    //スコア
    int score;
    //ンの文字を入れるかどうか判定するフラグ
    bool nFlag;
    //スコア用ラベル
    cocos2d::Label *scoreLabel;
    //クリアまでのポイント
    int clearPoint = 10;
    //スタート時間
    unsigned long long startTime;
    //クリア時間
    unsigned long long endTime;
    //クリアのフラグ
    bool clearFlag;
    //リトライボタン
    cocos2d::Sprite *retryButton;
    //トップボタン
    cocos2d::Sprite *topButton;
    
    //タイムラベル
    cocos2d::Label *timeLabel;
    
    //フレームの処理を行うか判断するフラグ
    bool frameFlag;
    
    
    
    //1フレームごとに呼ばれる。
    void update(float frame );
    
    //出題文を生成する(コントローラー)
    void creatQuestion();
    //文字を生成する(コントローラー)(正解かどうか判定してtrue、falseを返す)
    bool creatAnswer(int characterNumber);
    //文字を生成する(問題作成用)
    void createCharacter(int number ,cocos2d::Sprite *tantan);
    //文字の正誤を確認する。
    bool check();
    //クリア処理
    void gameClear();

    //デバッグ用メソッド
    bool debugMethod();

    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    //アプリの終了時に呼ばれる処理
    void TerminateAppMenuCallback(cocos2d::Ref* pSender);

    
    
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
