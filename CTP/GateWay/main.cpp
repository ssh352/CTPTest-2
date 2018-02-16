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

    cout << "��ʼ������..." << endl;
    g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();   // ��������ʵ��  
    CThostFtdcMdSpi *pMdUserSpi = new CtpMdSpi;       // ��������ص�ʵ��  
    g_pMdUserApi->RegisterSpi(pMdUserSpi);               // ע���¼���  
    g_pMdUserApi->RegisterFront(gMdFrontAddr);           // ��������ǰ�õ�ַ  
    g_pMdUserApi->Init();                                // �������� 

                                                         // ��ʼ�������߳�  
    cout << "��ʼ������..." << endl;
    g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(); // ��������ʵ��  
                                                                  //CThostFtdcTraderSpi *pTradeSpi = new CustomTradeSpi;  
    CtpTradeSpi *pTradeSpi = new CtpTradeSpi;               // �������׻ص�ʵ��  
    g_pTradeUserApi->RegisterSpi(pTradeSpi);                      // ע���¼���  
    g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);    // ���Ĺ�����  
    g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);   // ����˽����  
    g_pTradeUserApi->RegisterFront(gTradeFrontAddr);              // ���ý���ǰ�õ�ַ  
    g_pTradeUserApi->Init();                                      // ��������  

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