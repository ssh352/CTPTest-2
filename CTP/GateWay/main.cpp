#include <iostream>
#include "thread"
#include "Common.h"
#include "CtpMdSpi.h"
#include "CtpTradeSpi.h"
#include "iniFile.h"
#include "CSimpleLogger.h"
#include "RabbitMq.h"

using namespace std;
class RabbitMq;
int main() {
  try
  {
    extern TThostFtdcBrokerIDType gBrokerID;
    CSimpleLogger::Init("../gateway.log");
    CSimpleLogger::WriteLog(INFO, "GateWay start()");
    cout << "Read config.ini" << endl;
    IniFile ini("config.ini");
    ini.setSection("Common");
    cout << "[" << ini.getSection() << "]" << endl;

    string brokerID = ini.readStr("BrokerID", "");
    cout << "BrokerID" << "=" << brokerID << endl;
    string investerID = ini.readStr("InvesterID", "");
    cout << "InvesterID" << "=" << investerID << endl;
    string investerPassword = ini.readStr("InvesterPassword", "");
    string mdFrontAddr = ini.readStr("MdFrontAddr", "");
    cout << "MdFrontAddr" << "=" << mdFrontAddr << endl;
    string tradeFrontAddr = ini.readStr("TradeFrontAddr", "");
    cout << "TradeFrontAddr" << "=" << tradeFrontAddr << endl;

    string mqAddr = ini.readStr("MqAddr", "");
    cout << "MqAddr" << "=" << mqAddr << endl;
    int mqPort = ini.readInt("MqPort", 0);
    cout << "MqPort" << "=" << mqPort << endl;
    string mqUser = ini.readStr("MqUser", "");
    cout << "MqUser" << "=" << mqUser << endl;
    string mqPassword = ini.readStr("MqPassword", "");
    cout << "MqPassword" << "=" << mqPassword << endl;
    string queue1Name = ini.readStr("Queue1Name", "");
    cout << "Queue1Name" << "=" << queue1Name << endl;
    string queue2Name = ini.readStr("queue2Name", "");
    cout << "Queue2Name" << "=" << mqPassword << endl;

    cout << "初始化行情..." << endl;
    g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();   // 创建行情实例  
    CThostFtdcMdSpi *pMdUserSpi = new CtpMdSpi;       // 创建行情回调实例  
    g_pMdUserApi->RegisterSpi(pMdUserSpi);               // 注册事件类  
    g_pMdUserApi->RegisterFront(gMdFrontAddr);           // 设置行情前置地址  
    g_pMdUserApi->Init();                                // 连接运行 

                                                         // 初始化交易线程  
    cout << "初始化交易..." << endl;
    g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(); // 创建交易实例  
                                                                  //CThostFtdcTraderSpi *pTradeSpi = new CustomTradeSpi;  
    CtpTradeSpi *pTradeSpi = new CtpTradeSpi;               // 创建交易回调实例  
    g_pTradeUserApi->RegisterSpi(pTradeSpi);                      // 注册事件类  
    g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);    // 订阅公共流  
    g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);   // 订阅私有流  
    g_pTradeUserApi->RegisterFront(gTradeFrontAddr);              // 设置交易前置地址  
    g_pTradeUserApi->Init();                                      // 连接运行  

    spsc_queue<string>* send1Queue = new spsc_queue<string>();
    spsc_queue<string>* send2Queue = new spsc_queue<string>();
    //g_pRabbitMq = std::make_unique<RabbitMq>(RabbitMq(mqAddr, mqPort, mqUser, mqPassword, queue1Name, queue2Name, send1Queue, send2Queue));
    RabbitMq g_pRabbitMq(mqAddr, mqPort, mqUser, mqPassword, queue1Name, queue2Name, send1Queue, send2Queue);
    g_pRabbitMq.init();
    //while (1) {
    //  g_pRabbitMq.sendMsg1("\n message content\n");
    //}
    g_pRabbitMq.run();
    //std::thread mqThread(std::bind(&RabbitMq::run, &g_pRabbitMq));


    g_pMdUserApi->Join();
    delete pMdUserSpi;
    g_pMdUserApi->Release();

    g_pTradeUserApi->Join();
    delete pTradeSpi;
    g_pTradeUserApi->Release();

  }
  catch (const std::exception& ex)
  {
    ex.what();
  }


  getchar();
  return 0;
}