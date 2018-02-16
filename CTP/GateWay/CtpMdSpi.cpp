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
  cout << "前置连接成功" << endl;
  RequestLogin();
}

void CtpMdSpi::RequestLogin()
{
  // 开始登录  
  CThostFtdcReqUserLoginField loginReq;
  memset(&loginReq, 0, sizeof(loginReq));
  strcpy_s(loginReq.BrokerID, gBrokerID);
  strcpy_s(loginReq.UserID, gInvesterID);
  strcpy_s(loginReq.Password, gInvesterPassword);
  static int requestID = 0; // 请求编号  
  int rt = g_pMdUserApi->ReqUserLogin(&loginReq, requestID);
  if (!rt)
    std::cout << ">>>>>>发送登录请求成功" << std::endl;
  else
    std::cerr << "--->>>发送登录请求失败" << std::endl;
}

void CtpMdSpi::OnFrontDisconnected(int nReason)
{
  cout << "前置连接断开" << endl;
}

void CtpMdSpi::OnHeartBeatWarning(int nTimeLapse)
{

}

void CtpMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
  bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
  if (!bResult)
  {
    std::cout << "=====账户登录成功=====" << std::endl;
    std::cout << "系统名称： " << pRspUserLogin->SystemName << std::endl;
    std::cout << "交易日： " << pRspUserLogin->TradingDay << std::endl;
    std::cout << "登录时间： " << pRspUserLogin->LoginTime << std::endl;
    std::cout << "经纪商： " << pRspUserLogin->BrokerID << std::endl;
    std::cout << "帐户名： " << pRspUserLogin->UserID << std::endl;
    // 开始订阅行情  
    int rt = g_pMdUserApi->SubscribeMarketData(g_pInstrumentID, instrumentNum);
    if (!rt)
      std::cout << ">>>>>>发送订阅行情请求成功" << std::endl;
    else
      std::cerr << "--->>>发送订阅行情请求失败" << std::endl;
  }
  else
    std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

void CtpMdSpi::OnRspUserLogout(CThostFtdcUserLogoutField * pUserLogout, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

// 订阅行情应答  
void CtpMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
  bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
  if (!bResult)
  {
    std::cout << "=====订阅行情成功=====" << std::endl;
    std::cout << "合约代码： " << pSpecificInstrument->InstrumentID << std::endl;
    // 如果需要存入文件或者数据库，在这里创建表头,不同的合约单独存储  
    char filePath[100] = { '\0' };
    sprintf_s(filePath, "%s_market_data.csv", pSpecificInstrument->InstrumentID);
    std::ofstream outFile;
    outFile.open(filePath, std::ios::out); // 新开文件  
    outFile << "合约代码" << ","
      << "更新时间" << ","
      << "最新价" << ","
      << "成交量" << ","
      << "买价一" << ","
      << "买量一" << ","
      << "卖价一" << ","
      << "卖量一" << ","
      << "持仓量" << ","
      << "换手率"
      << std::endl;
    outFile.close();
  }
  else
    std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
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

  // 打印行情，字段较多，截取部分  
  std::cout << "=====获得深度行情=====" << std::endl;
  std::cout << "交易日： " << pDepthMarketData->TradingDay << std::endl;
  std::cout << "交易所代码： " << pDepthMarketData->ExchangeID << std::endl;
  std::cout << "合约代码： " << pDepthMarketData->InstrumentID << std::endl;
  std::cout << "合约在交易所的代码： " << pDepthMarketData->ExchangeInstID << std::endl;
  std::cout << "最新价： " << pDepthMarketData->LastPrice << std::endl;
  std::cout << "数量： " << pDepthMarketData->Volume << std::endl;
  // 如果只获取某一个合约行情，可以逐tick地存入文件或数据库  
  char filePath[100] = { '\0' };
  sprintf_s(filePath, "%s_market_data.csv", pDepthMarketData->InstrumentID);
  std::ofstream outFile;
  outFile.open(filePath, std::ios::app); // 文件追加写入   
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

  // 取消订阅行情  
  //int rt = g_pMdUserApi->UnSubscribeMarketData(g_pInstrumentID, instrumentNum);  
  //if (!rt)  
  //  std::cout << ">>>>>>发送取消订阅行情请求成功" << std::endl;  
  //else  
  //  std::cerr << "--->>>发送取消订阅行情请求失败" << std::endl;  
}
