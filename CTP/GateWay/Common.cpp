#include "Common.h"


// ---- 全局变量 ---- //  
// 公共参数  
TThostFtdcBrokerIDType gBrokerID = "9999";                         // 模拟经纪商代码  
TThostFtdcInvestorIDType gInvesterID = "13641868646";                         // 投资者账户名  
TThostFtdcPasswordType gInvesterPassword = "centos123";                     // 投资者密码  

                                                                            // 行情参数  
CThostFtdcMdApi *g_pMdUserApi = nullptr;                           // 行情指针  
char gMdFrontAddr[] = "tcp://180.168.146.187:10010";               // 模拟行情前置地址  
char *g_pInstrumentID[] = { "TF1802", "zn1802", "rb1802", "CF802" }; // 行情合约代码列表，中、上、大、郑交易所各选一种  
int instrumentNum = 4;                                             // 行情合约订阅数量  

                                                                   // 交易参数  
CThostFtdcTraderApi *g_pTradeUserApi = nullptr;                    // 交易指针  
char gTradeFrontAddr[] = "tcp://180.168.146.187:10001";            // 模拟交易前置地址  
TThostFtdcInstrumentIDType g_pTradeInstrumentID = "zn1705";         // 所交易的合约代码  
TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;       // 买卖方向  
TThostFtdcPriceType gLimitPrice = 2818;                            // 交易价格
