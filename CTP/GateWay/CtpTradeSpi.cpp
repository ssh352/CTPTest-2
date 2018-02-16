#include "CtpTradeSpi.h"
#include <iostream>
#include "common.h"


CtpTradeSpi::CtpTradeSpi()
{
}


CtpTradeSpi::~CtpTradeSpi()
{
}

void CtpTradeSpi::reqOrderInsert(TThostFtdcInstrumentIDType instrumentID, TThostFtdcPriceType price, TThostFtdcVolumeType volume, TThostFtdcDirectionType direction)
{
  CThostFtdcInputOrderField orderInsertReq;
  memset(&orderInsertReq, 0, sizeof(orderInsertReq));
  ///经纪公司代码  
  strcpy_s(orderInsertReq.BrokerID, gBrokerID);
  ///投资者代码  
  strcpy_s(orderInsertReq.InvestorID, gInvesterID);
  ///合约代码  
  strcpy_s(orderInsertReq.InstrumentID, instrumentID);
  ///报单引用  
  strcpy_s(orderInsertReq.OrderRef, order_ref);
  ///报单价格条件: 限价  
  orderInsertReq.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
  ///买卖方向:   
  orderInsertReq.Direction = direction;
  ///组合开平标志: 开仓  
  orderInsertReq.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
  ///组合投机套保标志  
  orderInsertReq.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
  ///价格  
  orderInsertReq.LimitPrice = price;
  ///数量：1  
  orderInsertReq.VolumeTotalOriginal = volume;
  ///有效期类型: 当日有效  
  orderInsertReq.TimeCondition = THOST_FTDC_TC_GFD;
  ///成交量类型: 任何数量  
  orderInsertReq.VolumeCondition = THOST_FTDC_VC_AV;
  ///最小成交量: 1  
  orderInsertReq.MinVolume = 1;
  ///触发条件: 立即  
  orderInsertReq.ContingentCondition = THOST_FTDC_CC_Immediately;
  ///强平原因: 非强平  
  orderInsertReq.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
  ///自动挂起标志: 否  
  orderInsertReq.IsAutoSuspend = 0;
  ///用户强评标志: 否  
  orderInsertReq.UserForceClose = 0;

  static int requestID = 0; // 请求编号  
  int rt = g_pTradeUserApi->ReqOrderInsert(&orderInsertReq, ++requestID);
  if (!rt)
    std::cout << ">>>>>>发送报单录入请求成功" << std::endl;
  else
    std::cerr << "--->>>发送报单录入请求失败" << std::endl;
}

void CtpTradeSpi::reqUserLogin()
{

}

void CtpTradeSpi::reqUserLogout()
{
}

void CtpTradeSpi::reqSettlementInfoConfirm()
{
}

void CtpTradeSpi::reqQueryInstrument()
{
}

void CtpTradeSpi::reqQueryTradingAccount()
{
}

void CtpTradeSpi::reqQueryInvestorPosition()
{
}

void CtpTradeSpi::reqOrderInsert()
{
}

void CtpTradeSpi::reqOrderAction(CThostFtdcOrderField * pOrder)
{
  static bool orderActionSentFlag = false; // 是否发送了报单  
  if (orderActionSentFlag)
    return;

  CThostFtdcInputOrderActionField orderActionReq;
  memset(&orderActionReq, 0, sizeof(orderActionReq));
  ///经纪公司代码  
  strcpy_s(orderActionReq.BrokerID, pOrder->BrokerID);
  ///投资者代码  
  strcpy_s(orderActionReq.InvestorID, pOrder->InvestorID);
  ///报单操作引用  
  //  TThostFtdcOrderActionRefType    OrderActionRef;  
  ///报单引用  
  strcpy_s(orderActionReq.OrderRef, pOrder->OrderRef);
  ///请求编号  
  //  TThostFtdcRequestIDType RequestID;  
  ///前置编号  
  orderActionReq.FrontID = trade_front_id;
  ///会话编号  
  orderActionReq.SessionID = session_id;
  ///交易所代码  
  //  TThostFtdcExchangeIDType    ExchangeID;  
  ///报单编号  
  //  TThostFtdcOrderSysIDType    OrderSysID;  
  ///操作标志  
  orderActionReq.ActionFlag = THOST_FTDC_AF_Delete;
  ///价格  
  //  TThostFtdcPriceType LimitPrice;  
  ///数量变化  
  //  TThostFtdcVolumeType    VolumeChange;  
  ///用户代码  
  //  TThostFtdcUserIDType    UserID;  
  ///合约代码  
  strcpy_s(orderActionReq.InstrumentID, pOrder->InstrumentID);
  static int requestID = 0; // 请求编号  
  int rt = g_pTradeUserApi->ReqOrderAction(&orderActionReq, ++requestID);
  if (!rt)
    std::cout << ">>>>>>发送报单操作请求成功" << std::endl;
  else
    std::cerr << "--->>>发送报单操作请求失败" << std::endl;
  orderActionSentFlag = true;
}

bool CtpTradeSpi::isErrorRspInfo(CThostFtdcRspInfoField * pRspInfo)
{
  return false;
}

bool CtpTradeSpi::isMyOrder(CThostFtdcOrderField * pOrder)
{
  return false;
}

bool CtpTradeSpi::isTradingOrder(CThostFtdcOrderField * pOrder)
{
  return false;
}

void CtpTradeSpi::OnFrontConnected()
{
}

void CtpTradeSpi::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
  if (!isErrorRspInfo(pRspInfo)) {
    std::cout << "=====账户登录成功=====" << std::endl;
    loginFlag = true;
    std::cout << "系统名称： " << pRspUserLogin->SystemName << std::endl;
    std::cout << "交易日： " << pRspUserLogin->TradingDay << std::endl;
    std::cout << "登录时间： " << pRspUserLogin->LoginTime << std::endl;
    std::cout << "经纪商： " << pRspUserLogin->BrokerID << std::endl;
    std::cout << "帐户名： " << pRspUserLogin->UserID << std::endl;

    // 保存会话参数  
    trade_front_id = pRspUserLogin->FrontID;
    session_id = pRspUserLogin->SessionID;
    strcpy_s(order_ref, pRspUserLogin->MaxOrderRef);

    // 投资者结算结果确认  
    reqSettlementInfoConfirm();
  }
}

void CtpTradeSpi::OnRspError(CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void CtpTradeSpi::OnFrontDisconnected(int nReason)
{
}

void CtpTradeSpi::OnHeartBeatWarning(int nTimeLapse)
{
}

void CtpTradeSpi::OnRspUserLogout(CThostFtdcUserLogoutField * pUserLogout, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void CtpTradeSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
  if (!isErrorRspInfo(pRspInfo))
  {
    std::cout << "=====投资者结算结果确认成功=====" << std::endl;
    std::cout << "确认日期： " << pSettlementInfoConfirm->ConfirmDate << std::endl;
    std::cout << "确认时间： " << pSettlementInfoConfirm->ConfirmTime << std::endl;
    // 请求查询合约  
    reqQueryInstrument();
  }
}

void CtpTradeSpi::OnRspQryInstrument(CThostFtdcInstrumentField * pInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
  if (!isErrorRspInfo(pRspInfo))
  {
    std::cout << "=====查询合约结果成功=====" << std::endl;
    std::cout << "交易所代码： " << pInstrument->ExchangeID << std::endl;
    std::cout << "合约代码： " << pInstrument->InstrumentID << std::endl;
    std::cout << "合约在交易所的代码： " << pInstrument->ExchangeInstID << std::endl;
    std::cout << "执行价： " << pInstrument->StrikePrice << std::endl;
    std::cout << "到期日： " << pInstrument->EndDelivDate << std::endl;
    std::cout << "当前交易状态： " << pInstrument->IsTrading << std::endl;
    // 请求查询投资者资金账户  
    reqQueryTradingAccount();
  }
}

void CtpTradeSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField * pTradingAccount, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
  if (!isErrorRspInfo(pRspInfo))
  {
    std::cout << "=====查询投资者资金账户成功=====" << std::endl;
    std::cout << "投资者账号： " << pTradingAccount->AccountID << std::endl;
    std::cout << "可用资金： " << pTradingAccount->Available << std::endl;
    std::cout << "可取资金： " << pTradingAccount->WithdrawQuota << std::endl;
    std::cout << "当前保证金: " << pTradingAccount->CurrMargin << std::endl;
    std::cout << "平仓盈亏： " << pTradingAccount->CloseProfit << std::endl;
    // 请求查询投资者持仓  
    reqQueryInvestorPosition();
  }
}

void CtpTradeSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField * pInvestorPosition, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
  if (!isErrorRspInfo(pRspInfo))
  {
    std::cout << "=====查询投资者持仓成功=====" << std::endl;
    if (pInvestorPosition)
    {
      std::cout << "合约代码： " << pInvestorPosition->InstrumentID << std::endl;
      std::cout << "开仓价格： " << pInvestorPosition->OpenAmount << std::endl;
      std::cout << "开仓量： " << pInvestorPosition->OpenVolume << std::endl;
      std::cout << "开仓方向： " << pInvestorPosition->PosiDirection << std::endl;
      std::cout << "占用保证金：" << pInvestorPosition->UseMargin << std::endl;
    }
    else
      std::cout << "----->该合约未持仓" << std::endl;

    // 报单录入请求（这里是一部接口，此处是按顺序执行）  
    /*if (loginFlag)
    reqOrderInsert();*/
    if (loginFlag)
      reqOrderInsert(g_pTradeInstrumentID, gLimitPrice, 1, gTradeDirection); // 自定义一笔交易  

                                                                             // 策略交易  
    std::cout << "=====开始进入策略交易=====" << std::endl;
    //while (loginFlag)
    //StrategyCheckAndTrade(g_pTradeInstrumentID, this);
  }
}

void CtpTradeSpi::OnRspOrderInsert(CThostFtdcInputOrderField * pInputOrder, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{

}

void CtpTradeSpi::OnRspOrderAction(CThostFtdcInputOrderActionField * pInputOrderAction, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void CtpTradeSpi::OnRtnOrder(CThostFtdcOrderField * pOrder)
{
  char str[10];
  sprintf_s(str, "%d", pOrder->OrderSubmitStatus);
  int orderState = atoi(str) - 48;    //报单状态0=已经提交，3=已经接受  

  std::cout << "=====收到报单应答=====" << std::endl;

  if (isMyOrder(pOrder))
  {
    if (isTradingOrder(pOrder))
    {
      std::cout << "--->>> 等待成交中！" << std::endl;
      //reqOrderAction(pOrder); // 这里可以撤单  
      //reqUserLogout(); // 登出测试  
    }
    else if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled)
      std::cout << "--->>> 撤单成功！" << std::endl;
  }
}


void CtpTradeSpi::OnRtnTrade(CThostFtdcTradeField * pTrade)
{
  std::cout << "=====报单成功成交=====" << std::endl;
  std::cout << "成交时间： " << pTrade->TradeTime << std::endl;
  std::cout << "合约代码： " << pTrade->InstrumentID << std::endl;
  std::cout << "成交价格： " << pTrade->Price << std::endl;
  std::cout << "成交量： " << pTrade->Volume << std::endl;
  std::cout << "开平仓方向： " << pTrade->Direction << std::endl;
}