#ifndef  __COMMON_H__
#define  __COMMON_H__

#include <string>
#include <unordered_map>
#include <memory>
#include  "ThostFtdcMdApi.h"
#include  "ThostFtdcTraderApi.h"
#include "RabbitMq.h"
class RabbitMq;

extern int g_i; // 此处是声明,另外,在全局变量前加一个 g_ 是好习惯.

                // ---- 全局变量 ---- //  
                // 公共参数  
extern TThostFtdcBrokerIDType gBrokerID;                         // 模拟经纪商代码  
extern TThostFtdcInvestorIDType gInvesterID;                         // 投资者账户名  
extern TThostFtdcPasswordType gInvesterPassword;                     // 投资者密码  

                                                                     // 行情参数  
extern CThostFtdcMdApi *g_pMdUserApi;                           // 行情指针  
extern char gMdFrontAddr[];               // 模拟行情前置地址  
extern char *g_pInstrumentID[]; // 行情合约代码列表，中、上、大、郑交易所各选一种  
extern int instrumentNum;                                             // 行情合约订阅数量  

                                                                      // 交易参数  
extern CThostFtdcTraderApi *g_pTradeUserApi;                    // 交易指针  
extern char gTradeFrontAddr[];            // 模拟交易前置地址  
extern TThostFtdcInstrumentIDType g_pTradeInstrumentID;         // 所交易的合约代码  
extern TThostFtdcDirectionType gTradeDirection;       // 买卖方向  
extern TThostFtdcPriceType gLimitPrice;                            // 交易价格


#endif // ! __COMMON_H__



