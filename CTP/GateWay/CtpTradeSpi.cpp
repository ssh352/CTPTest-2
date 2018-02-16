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
  ///���͹�˾����  
  strcpy_s(orderInsertReq.BrokerID, gBrokerID);
  ///Ͷ���ߴ���  
  strcpy_s(orderInsertReq.InvestorID, gInvesterID);
  ///��Լ����  
  strcpy_s(orderInsertReq.InstrumentID, instrumentID);
  ///��������  
  strcpy_s(orderInsertReq.OrderRef, order_ref);
  ///�����۸�����: �޼�  
  orderInsertReq.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
  ///��������:   
  orderInsertReq.Direction = direction;
  ///��Ͽ�ƽ��־: ����  
  orderInsertReq.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
  ///���Ͷ���ױ���־  
  orderInsertReq.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
  ///�۸�  
  orderInsertReq.LimitPrice = price;
  ///������1  
  orderInsertReq.VolumeTotalOriginal = volume;
  ///��Ч������: ������Ч  
  orderInsertReq.TimeCondition = THOST_FTDC_TC_GFD;
  ///�ɽ�������: �κ�����  
  orderInsertReq.VolumeCondition = THOST_FTDC_VC_AV;
  ///��С�ɽ���: 1  
  orderInsertReq.MinVolume = 1;
  ///��������: ����  
  orderInsertReq.ContingentCondition = THOST_FTDC_CC_Immediately;
  ///ǿƽԭ��: ��ǿƽ  
  orderInsertReq.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
  ///�Զ������־: ��  
  orderInsertReq.IsAutoSuspend = 0;
  ///�û�ǿ����־: ��  
  orderInsertReq.UserForceClose = 0;

  static int requestID = 0; // ������  
  int rt = g_pTradeUserApi->ReqOrderInsert(&orderInsertReq, ++requestID);
  if (!rt)
    std::cout << ">>>>>>���ͱ���¼������ɹ�" << std::endl;
  else
    std::cerr << "--->>>���ͱ���¼������ʧ��" << std::endl;
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
  static bool orderActionSentFlag = false; // �Ƿ����˱���  
  if (orderActionSentFlag)
    return;

  CThostFtdcInputOrderActionField orderActionReq;
  memset(&orderActionReq, 0, sizeof(orderActionReq));
  ///���͹�˾����  
  strcpy_s(orderActionReq.BrokerID, pOrder->BrokerID);
  ///Ͷ���ߴ���  
  strcpy_s(orderActionReq.InvestorID, pOrder->InvestorID);
  ///������������  
  //  TThostFtdcOrderActionRefType    OrderActionRef;  
  ///��������  
  strcpy_s(orderActionReq.OrderRef, pOrder->OrderRef);
  ///������  
  //  TThostFtdcRequestIDType RequestID;  
  ///ǰ�ñ��  
  orderActionReq.FrontID = trade_front_id;
  ///�Ự���  
  orderActionReq.SessionID = session_id;
  ///����������  
  //  TThostFtdcExchangeIDType    ExchangeID;  
  ///�������  
  //  TThostFtdcOrderSysIDType    OrderSysID;  
  ///������־  
  orderActionReq.ActionFlag = THOST_FTDC_AF_Delete;
  ///�۸�  
  //  TThostFtdcPriceType LimitPrice;  
  ///�����仯  
  //  TThostFtdcVolumeType    VolumeChange;  
  ///�û�����  
  //  TThostFtdcUserIDType    UserID;  
  ///��Լ����  
  strcpy_s(orderActionReq.InstrumentID, pOrder->InstrumentID);
  static int requestID = 0; // ������  
  int rt = g_pTradeUserApi->ReqOrderAction(&orderActionReq, ++requestID);
  if (!rt)
    std::cout << ">>>>>>���ͱ�����������ɹ�" << std::endl;
  else
    std::cerr << "--->>>���ͱ�����������ʧ��" << std::endl;
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
    std::cout << "=====�˻���¼�ɹ�=====" << std::endl;
    loginFlag = true;
    std::cout << "ϵͳ���ƣ� " << pRspUserLogin->SystemName << std::endl;
    std::cout << "�����գ� " << pRspUserLogin->TradingDay << std::endl;
    std::cout << "��¼ʱ�䣺 " << pRspUserLogin->LoginTime << std::endl;
    std::cout << "�����̣� " << pRspUserLogin->BrokerID << std::endl;
    std::cout << "�ʻ����� " << pRspUserLogin->UserID << std::endl;

    // ����Ự����  
    trade_front_id = pRspUserLogin->FrontID;
    session_id = pRspUserLogin->SessionID;
    strcpy_s(order_ref, pRspUserLogin->MaxOrderRef);

    // Ͷ���߽�����ȷ��  
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
    std::cout << "=====Ͷ���߽�����ȷ�ϳɹ�=====" << std::endl;
    std::cout << "ȷ�����ڣ� " << pSettlementInfoConfirm->ConfirmDate << std::endl;
    std::cout << "ȷ��ʱ�䣺 " << pSettlementInfoConfirm->ConfirmTime << std::endl;
    // �����ѯ��Լ  
    reqQueryInstrument();
  }
}

void CtpTradeSpi::OnRspQryInstrument(CThostFtdcInstrumentField * pInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
  if (!isErrorRspInfo(pRspInfo))
  {
    std::cout << "=====��ѯ��Լ����ɹ�=====" << std::endl;
    std::cout << "���������룺 " << pInstrument->ExchangeID << std::endl;
    std::cout << "��Լ���룺 " << pInstrument->InstrumentID << std::endl;
    std::cout << "��Լ�ڽ������Ĵ��룺 " << pInstrument->ExchangeInstID << std::endl;
    std::cout << "ִ�мۣ� " << pInstrument->StrikePrice << std::endl;
    std::cout << "�����գ� " << pInstrument->EndDelivDate << std::endl;
    std::cout << "��ǰ����״̬�� " << pInstrument->IsTrading << std::endl;
    // �����ѯͶ�����ʽ��˻�  
    reqQueryTradingAccount();
  }
}

void CtpTradeSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField * pTradingAccount, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
  if (!isErrorRspInfo(pRspInfo))
  {
    std::cout << "=====��ѯͶ�����ʽ��˻��ɹ�=====" << std::endl;
    std::cout << "Ͷ�����˺ţ� " << pTradingAccount->AccountID << std::endl;
    std::cout << "�����ʽ� " << pTradingAccount->Available << std::endl;
    std::cout << "��ȡ�ʽ� " << pTradingAccount->WithdrawQuota << std::endl;
    std::cout << "��ǰ��֤��: " << pTradingAccount->CurrMargin << std::endl;
    std::cout << "ƽ��ӯ���� " << pTradingAccount->CloseProfit << std::endl;
    // �����ѯͶ���ֲ߳�  
    reqQueryInvestorPosition();
  }
}

void CtpTradeSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField * pInvestorPosition, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
  if (!isErrorRspInfo(pRspInfo))
  {
    std::cout << "=====��ѯͶ���ֲֳ߳ɹ�=====" << std::endl;
    if (pInvestorPosition)
    {
      std::cout << "��Լ���룺 " << pInvestorPosition->InstrumentID << std::endl;
      std::cout << "���ּ۸� " << pInvestorPosition->OpenAmount << std::endl;
      std::cout << "�������� " << pInvestorPosition->OpenVolume << std::endl;
      std::cout << "���ַ��� " << pInvestorPosition->PosiDirection << std::endl;
      std::cout << "ռ�ñ�֤��" << pInvestorPosition->UseMargin << std::endl;
    }
    else
      std::cout << "----->�ú�Լδ�ֲ�" << std::endl;

    // ����¼������������һ���ӿڣ��˴��ǰ�˳��ִ�У�  
    /*if (loginFlag)
    reqOrderInsert();*/
    if (loginFlag)
      reqOrderInsert(g_pTradeInstrumentID, gLimitPrice, 1, gTradeDirection); // �Զ���һ�ʽ���  

                                                                             // ���Խ���  
    std::cout << "=====��ʼ������Խ���=====" << std::endl;
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
  int orderState = atoi(str) - 48;    //����״̬0=�Ѿ��ύ��3=�Ѿ�����  

  std::cout << "=====�յ�����Ӧ��=====" << std::endl;

  if (isMyOrder(pOrder))
  {
    if (isTradingOrder(pOrder))
    {
      std::cout << "--->>> �ȴ��ɽ��У�" << std::endl;
      //reqOrderAction(pOrder); // ������Գ���  
      //reqUserLogout(); // �ǳ�����  
    }
    else if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled)
      std::cout << "--->>> �����ɹ���" << std::endl;
  }
}


void CtpTradeSpi::OnRtnTrade(CThostFtdcTradeField * pTrade)
{
  std::cout << "=====�����ɹ��ɽ�=====" << std::endl;
  std::cout << "�ɽ�ʱ�䣺 " << pTrade->TradeTime << std::endl;
  std::cout << "��Լ���룺 " << pTrade->InstrumentID << std::endl;
  std::cout << "�ɽ��۸� " << pTrade->Price << std::endl;
  std::cout << "�ɽ����� " << pTrade->Volume << std::endl;
  std::cout << "��ƽ�ַ��� " << pTrade->Direction << std::endl;
}