#include "CtpMdSpi.h"

#include <iostream>
#include <fstream>
#include "Common.h"
#include "DataStruct.h"
using namespace std;

void CtpMdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField * pForQuoteRsp)
{
}

CtpMdSpi::CtpMdSpi()
{
}


CtpMdSpi::~CtpMdSpi()
{
}

void CtpMdSpi::OnFrontConnected()
{
  cout << "ǰ�����ӳɹ�" << endl;
  RequestLogin();
}

void CtpMdSpi::RequestLogin()
{
  // ��ʼ��¼  
  CThostFtdcReqUserLoginField loginReq;
  memset(&loginReq, 0, sizeof(loginReq));
  strcpy_s(loginReq.BrokerID, gBrokerID);
  strcpy_s(loginReq.UserID, gInvesterID);
  strcpy_s(loginReq.Password, gInvesterPassword);
  static int requestID = 0; // ������  
  int rt = g_pMdUserApi->ReqUserLogin(&loginReq, requestID);
  if (!rt)
    std::cout << ">>>>>>���͵�¼����ɹ�" << std::endl;
  else
    std::cerr << "--->>>���͵�¼����ʧ��" << std::endl;
}

void CtpMdSpi::OnFrontDisconnected(int nReason)
{
  cout << "ǰ�����ӶϿ�" << endl;
}

void CtpMdSpi::OnHeartBeatWarning(int nTimeLapse)
{

}

void CtpMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
  bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
  if (!bResult)
  {
    std::cout << "=====�˻���¼�ɹ�=====" << std::endl;
    std::cout << "ϵͳ���ƣ� " << pRspUserLogin->SystemName << std::endl;
    std::cout << "�����գ� " << pRspUserLogin->TradingDay << std::endl;
    std::cout << "��¼ʱ�䣺 " << pRspUserLogin->LoginTime << std::endl;
    std::cout << "�����̣� " << pRspUserLogin->BrokerID << std::endl;
    std::cout << "�ʻ����� " << pRspUserLogin->UserID << std::endl;
    // ��ʼ��������  
    int rt = g_pMdUserApi->SubscribeMarketData(g_pInstrumentID, instrumentNum);
    if (!rt)
      std::cout << ">>>>>>���Ͷ�����������ɹ�" << std::endl;
    else
      std::cerr << "--->>>���Ͷ�����������ʧ��" << std::endl;
  }
  else
    std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

void CtpMdSpi::OnRspUserLogout(CThostFtdcUserLogoutField * pUserLogout, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

// ��������Ӧ��  
void CtpMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
  bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
  if (!bResult)
  {
    std::cout << "=====��������ɹ�=====" << std::endl;
    std::cout << "��Լ���룺 " << pSpecificInstrument->InstrumentID << std::endl;
    // �����Ҫ�����ļ��������ݿ⣬�����ﴴ����ͷ,��ͬ�ĺ�Լ�����洢  
    char filePath[100] = { '\0' };
    sprintf_s(filePath, "%s_market_data.csv", pSpecificInstrument->InstrumentID);
    std::ofstream outFile;
    outFile.open(filePath, std::ios::out); // �¿��ļ�  
    outFile << "��Լ����" << ","
      << "����ʱ��" << ","
      << "���¼�" << ","
      << "�ɽ���" << ","
      << "���һ" << ","
      << "����һ" << ","
      << "����һ" << ","
      << "����һ" << ","
      << "�ֲ���" << ","
      << "������"
      << std::endl;
    outFile.close();
  }
  else
    std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

void CtpMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{

}

void CtpMdSpi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void CtpMdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void CtpMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField * pDepthMarketData)
{
  InnerMarketData field_ = InnerMarketData();
  MarketDataToInField<CThostFtdcDepthMarketDataField>(pDepthMarketData, field_);

  // ��ӡ���飬�ֶν϶࣬��ȡ����  
  std::cout << "=====����������=====" << std::endl;
  std::cout << "�����գ� " << pDepthMarketData->TradingDay << std::endl;
  std::cout << "���������룺 " << pDepthMarketData->ExchangeID << std::endl;
  std::cout << "��Լ���룺 " << pDepthMarketData->InstrumentID << std::endl;
  std::cout << "��Լ�ڽ������Ĵ��룺 " << pDepthMarketData->ExchangeInstID << std::endl;
  std::cout << "���¼ۣ� " << pDepthMarketData->LastPrice << std::endl;
  std::cout << "������ " << pDepthMarketData->Volume << std::endl;
  // ���ֻ��ȡĳһ����Լ���飬������tick�ش����ļ������ݿ�  
  char filePath[100] = { '\0' };
  sprintf_s(filePath, "%s_market_data.csv", pDepthMarketData->InstrumentID);
  std::ofstream outFile;
  outFile.open(filePath, std::ios::app); // �ļ�׷��д��   
  outFile << pDepthMarketData->InstrumentID << ","
    << pDepthMarketData->UpdateTime << "." << pDepthMarketData->UpdateMillisec << ","
    << pDepthMarketData->LastPrice << ","
    << pDepthMarketData->Volume << ","
    << pDepthMarketData->BidPrice1 << ","
    << pDepthMarketData->BidVolume1 << ","
    << pDepthMarketData->AskPrice1 << ","
    << pDepthMarketData->AskVolume1 << ","
    << pDepthMarketData->OpenInterest << ","
    << pDepthMarketData->Turnover << std::endl;
  outFile.close();

  // ȡ����������  
  //int rt = g_pMdUserApi->UnSubscribeMarketData(g_pInstrumentID, instrumentNum);  
  //if (!rt)  
  //  std::cout << ">>>>>>����ȡ��������������ɹ�" << std::endl;  
  //else  
  //  std::cerr << "--->>>����ȡ��������������ʧ��" << std::endl;  
}
