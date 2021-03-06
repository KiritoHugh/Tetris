#ifndef _BACKGROUND_BOARD_H_
#define _BACKGROUND_BOARD_H_

#include "cocos2d.h"
#include "GlobalDefine.h"
#include "Tetromino.h"
#include "Block.h"
#include <list>

USING_NS_CC;

typedef void (CCObject::*SEL_ClearLine)(int numLine);
#define clearLine_selector(_SELECTOR) (SEL_ClearLine)(&_SELECTOR)

typedef void (CCObject::*SEL_NextBlock)(int*);
#define nextBlock_selector(_SELECTOR) (SEL_NextBlock)(&_SELECTOR)

typedef void (CCObject::*SEL_GameOver)();
#define gameOver_selector(_SELECTOR) (SEL_GameOver)(&_SELECTOR)

/**
 *  底板
 */
class BackgroundBoard : public CCNode,public CCTouchDelegate
{
public:
	///游戏开始,是重新开始的时候用,暂停后继续请用continueDrop
	void start();

	void pasueDrop();        ///<暂停游戏
	void continueDrop();     ///<继续游戏

	void curTetrominoMove(); ///<令当前的方块往下降落,是一个回调函数
	void setNextTetromino(); ///<设置新的方块,是一个回调函数

	
	void setClearLineListener(CCObject*,SEL_ClearLine);  ///<设置行消除的回调
	void setGameOverListener(CCObject*,SEL_GameOver);    ///<设置GameOver的回调

	/**
	 *  设置下一个方块编号改变的回调
	 *  用于提示玩家下一个方块是什么形状的
	 */
	void setNextBlockListener(CCObject*,SEL_NextBlock);   
	
	///设置下落一格的等待时间
	void setDropDelayTime(float dropDur)		 {m_dropDelayTime = dropDur;}

	bool isPause()								 {return m_isPause;}

	virtual bool init(float blockSize,char* fnBlockTex);
	virtual void onEnter();
    virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	static BackgroundBoard* create(float blockSize,char* fnBlockTex);
private:
	char* m_fnBlockTex;
	float m_dropDelayTime;
	bool  m_bAccAction;
	bool  m_bGameOver;
	bool  m_isPause;
	bool  m_bAccMove;
	int   m_blockSize;
	int   m_bgInfo[BACKGROUND_ROW];
	std::list<int> m_next3Blocks;
	CCPoint       m_touchPos;
	CCNode*       m_blockSprRow[BACKGROUND_ROW];
	Tetromino*    m_curTetromino;
//	CCNode*       m_targetBlock;
	CCObject*     m_clearLineListener;
	SEL_ClearLine m_clearLineCallback;
	CCObject*     m_gameOverListener;
	SEL_GameOver  m_gameOverCallback;
	CCObject*     m_nextBlockListener;
	SEL_NextBlock m_nextBlockCallback;
	CCParticleSystemQuad* m_parSys;

	int  clearLine();          ///<消除满方块的行
	bool addToBg();            ///<将当前的方块加到底板标记数组中区
	void addNewTetromino();    ///<增加新的方块
	void setTargetBlockPos();  ///<设置最后落点提示精灵的位置
	void gotoTargetPos();      ///<直接降落到最后落点
	void onGameOver();
};

inline void BackgroundBoard::setClearLineListener(CCObject* pObject,SEL_ClearLine callback)
{
	m_clearLineListener   = pObject;
	m_clearLineCallback  = callback;
}

inline void BackgroundBoard::setGameOverListener(CCObject* pObject,SEL_GameOver callback)
{
	m_gameOverListener  = pObject;
	m_gameOverCallback = callback;
}

inline void BackgroundBoard::setNextBlockListener(CCObject* pObject,SEL_NextBlock callback)
{
	m_nextBlockListener = pObject;
	m_nextBlockCallback = callback;
}
#endif