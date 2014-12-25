//
//  OpningScene.h
//  tatatanTest
//
//  Created by yasutomo on 2014/11/05.
//
//

#ifndef __tatatanTest__OpningScene__
#define __tatatanTest__OpningScene__

#include <stdio.h>
#include "cocos2d.h"


class OpningScene : public cocos2d::Layer
{
    
protected:
    
    
    //スタートスプライト
    cocos2d::Sprite *start;
    //ランキング
    cocos2d::Sprite *ranking;
    
    /***************** タッチイベント用変数 ***********************/
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    //    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    /***************** タッチイベント用変数 終***********************/

    
    
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(OpningScene);

    
    
};

#endif /* defined(__tatatanTest__OpningScene__) */
