#ifndef __DATASTRUCT_H__
#define __DATASTRUCT_H__
#define SNPRINTF _snprintf_s

#include <map>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

typedef std::function<void(void* c, uint16_t length)> setMethod;
using namespace std;
using namespace std::placeholders;


///开仓
#define INNER_OFFSET_Open '0'
///平仓
#define INNER_OFFSET_Close '1'
///平今
#define INNER_OFFSET_CloseToday '3'
///平昨
#define INNER_OFFSET_CloseYesterday '4'

///买
#define INNER_DIRECTION_Buy '0'
///卖
#define INNER_DIRECTION_Sell '1'

int char2int(const char **ps);
const static uint16_t BrokerIDLen = 10;
const static uint16_t CancelTimeLen = 8;
const static uint16_t EventIDLen = 20;
const static uint16_t EventTypeLen = 14;
const static uint16_t ExchangeCodeLen = 8;
const static uint16_t FeeFormatLen = 14;
const static uint16_t FeeTypeLen = 14;
const static uint16_t InsertTimeLen = 8;
const static uint16_t InstrumentIDLen = 30;
const static uint16_t InterfaceModeLen = 9;
const static uint16_t InvestorIDLen = 12;
const static uint16_t LogTextLen = 4000;
const static uint16_t LogTimeLen = 40;
const static uint16_t LogTypeLen = 10;
const static uint16_t MqHostLen = 14;
const static uint16_t MqNameJetToServerLen = 30;
const static uint16_t MqNameServerToJetLen = 30;
const static uint16_t NameLen = 62;
const static uint16_t OrderSysIDLen = 20;
const static uint16_t ProductNameLen = 126;
const static uint16_t StatusMsgLen = 80;
const static uint16_t StrategyNameLen = 14;
const static uint16_t SymbolLen = 10;
const static uint16_t TradeIDLen = 20;
const static uint16_t TradeableTypeLen = 14;
const static uint16_t TraderNameLen = 62;
const static uint16_t TradingDayLen = 8;
const static uint16_t TypeLen = 10;
const static uint16_t UpdateTimeLen = 8;
const static uint16_t UserIDLen = 30;
const static uint16_t ValueDateLen = 8;
const static uint16_t ValueStringLen = 254;
const static uint16_t ValueTypeLen = 14;
const static uint16_t TitleNameLen = 60;


const static uint16_t EesSymbolLen = 8;
const static uint16_t InvestorIdRefLen = 12;
const static uint16_t AccountIDLen = 12;
const static uint16_t InstrumentNameLen = 30;

const static uint16_t CommentLen = 9;
const static uint16_t DateLen = 10;
const static uint16_t IndentificationLen = 14;
const static uint16_t SymLen = 9;
const static uint16_t DTimeLen = 19;
const static uint16_t DatesLen = 10;
const static uint16_t ExchangeIDLen = 8;

const static uint16_t OpenLen = 8;

const static uint16_t ParameterLen = 1023;
const static uint16_t PasswordLen = 19;
const static uint16_t Pri_contractLen = 14;
const static uint16_t Root_symLen = 9;
const static uint16_t Sec_contractLen = 14;
const static uint16_t StrategyClassLen = 19;
const static uint16_t ParamNameLen = 62;
const static uint16_t ParamValueStringLen = 62;
const static uint16_t TradingPeriodTypeLen = 9;
const static uint16_t FUN_INSTRUTMENT = 1;
const static uint16_t FUN_ORDER_INSERT = 2;
const static uint16_t FUN_ORDER_ACTION = 3;
const static uint16_t FUN_QRY_INVESTORPOS = 4;
const static uint16_t FUN_TRADING_ACCOUT = 5;
const static uint16_t FUN_QRY_ORDER = 6;
const static uint16_t FUN_QRY_TRADE = 7;

const static uint16_t TID_InstrumentTradingPeriod = 1;
const static uint16_t TID_SymbolInfo = 2;
const static uint16_t TID_SymbolTradingFee = 3;
const static uint16_t TID_TradeableInstrument = 4;
const static uint16_t TID_Strategy = 5;
const static uint16_t TID_StrategySymbol = 6;
const static uint16_t TID_StrategyParam = 7;
const static uint16_t TID_StrategyInstrumentPNLDaily = 8;
const static uint16_t TID_StrategyInstrumentPNLSettlementDaily = 9;
const static uint16_t TID_TimeBinner = 10;
const static uint16_t TID_OrderFills = 11;
const static uint16_t TID_Order = 12;
const static uint16_t TID_TimeOut = 13;
const static uint16_t TID_SymbolTradingPeriod = 14;
const static uint16_t TID_JetConfig = 15;
const static uint16_t TID_UpdateStrategyParams = 16;
const static uint16_t TID_StrategySwitch = 17;
const static uint16_t TID_JetStrategy = 18;
const static uint16_t TID_EndTimeBinner = 19;
const static uint16_t TID_WriteStrategyInstrumentPNLDaily = 101;
const static uint16_t TID_WriteTimeBinner = 102;
const static uint16_t TID_WriteOrder = 104;
const static uint16_t TID_WriteLog = 105;
const static uint16_t TID_WriteHeartBeat = 106;
const static uint16_t TID_WriteStrategySwitch = 107;
const static uint16_t TID_WriteMdLastPrice = 108;
const static uint16_t TID_WriteUpdateStrategyParams = 109;
const static uint16_t TID_Init = 998;
const static uint16_t TID_InitFinished = 999;

struct QueueNode
{
  int Tid;
  void *Data;
};


//class CtpTraderSpi;
//class CtpMdSpi;
class ApiInfoDetail
{
public:
  ApiInfoDetail()
  {
    tradingId = 0;
    memset(userId_, 0, sizeof(userId_));
    memset(investorId_, 0, sizeof(investorId_));
    memset(brokerId_, 0, sizeof(brokerId_));
    memset(passwd_, 0, sizeof(passwd_));
    memset(onOff_, 0, sizeof(onOff_));
    memset(onOffMd_, 0, sizeof(onOffMd_));
    memset(frontTdAddr_, 0, sizeof(frontTdAddr_));
    memset(frontMdAddr_, 0, sizeof(frontMdAddr_));
    frontId_ = 0;
    sessionId_ = 0;
    type_ = '0';
    orderRef_ = 0;
    pMdApi_ = nullptr;
    pTdApi_ = nullptr;
    pTdSpi_ = nullptr;
    mdInit = false;
    tdInit = false;
  }

  int  tradingId;
  char userId_[InvestorIDLen + 1];
  char investorId_[InvestorIDLen + 1];
  char brokerId_[10 + 1];
  char passwd_[40 + 1];
  char onOff_[10 + 1];
  char onOffMd_[10 + 1];
  bool mdInit;
  bool tdInit;
  char frontTdAddr_[30 + 1];
  char frontMdAddr_[30 + 1];
  int frontId_;
  int sessionId_;
  char type_;
  volatile int orderRef_; //会修改
  void* pMdApi_;
  void* pTdApi_;
  void *pTdSpi_;
  void *pMdSpi_;
};

class UserDetail
{
public:
  UserDetail()
  {
    apiType_ = 0;
    memset(userId_, 0, sizeof(userId_));
    memset(userPasswd_, 0, sizeof(userPasswd_));
    memset(investorId_, 0, sizeof(investorId_));
  }
  ~UserDetail()
  {
    investMap_.clear();
  }

  int apiType_;
  char userId_[UserIDLen + 1];
  char userPasswd_[40 + 1];
  char investorId_[InvestorIDLen + 1];
  std::unordered_map<string, string> investMap_; //investor
};

typedef std::shared_ptr<UserDetail> UserDetailPtr;
class UserInfo
{
public:
  UserInfo() { ; }
  ~UserInfo()
  {
    userInfoMap_.clear();
  }

  typedef std::unordered_map<string, UserDetailPtr> UserInfoMap; //userid + userDetailMap
  UserInfoMap userInfoMap_;
  UserDetailPtr getUserDetail(string userid);
};

typedef std::shared_ptr<ApiInfoDetail> ApiDetailPtr;
class GateWayApiInfo
{
public:
  GateWayApiInfo() { ; }
  ~GateWayApiInfo()
  {
    apiInfoMap_.clear();
  }

  typedef std::unordered_map<string, ApiDetailPtr> ApiInfoMap;
  ApiDetailPtr getApiDetail(string investorId);
  ApiDetailPtr getApiDetailByType(int type);
  ApiInfoMap apiInfoMap_;
};

class Entry {
public:
  Entry() { ; }
  uint8_t  apitype_;
  uint16_t msgtype_;
  uint32_t userref_;
  uint32_t rtnSeqNo_;
  uint8_t  *memPtr_;
  uint32_t startPos_;
  uint16_t length_;
  char     userId_[UserIDLen + 1];
};

struct InnerMarketData
{
  ///交易日
  char TradingDay[TradingDayLen + 1];
  char InstrumentID[InstrumentIDLen + 1];
  char  ExchangeID[ExchangeIDLen + 1];
  double LastPrice;
  ///上次结算价
  double PreSettlementPrice;
  ///昨收盘
  double PreClosePrice;
  ///昨持仓量
  double PreOpenInterest;
  double OpenPrice;
  ///最高价
  double HighestPrice;
  ///最低价
  double LowestPrice;
  int Volume;
  ///成交金额
  double Turnover;
  ///持仓量
  double OpenInterest;
  ///涨停板价
  double UpperLimitPrice;
  ///跌停板价
  double LowerLimitPrice;
  double BidPrice1;
  int BidVolume1;
  double AskPrice1;
  int AskVolume1;
  double BidPrice2;
  int BidVolume2;
  double AskPrice2;
  int AskVolume2;
  double BidPrice3;
  int BidVolume3;
  double AskPrice3;
  int AskVolume3;
  double BidPrice4;
  int BidVolume4;
  double AskPrice4;
  int AskVolume4;
  double BidPrice5;
  int BidVolume5;
  double AskPrice5;
  int AskVolume5;
  double AveragePrice;
  char UpdateTime[UpdateTimeLen + 1];
  int UpdateMillisec;
};

struct InnerRspMessage
{
  int32_t ErrorID_;
  char ErrorMsg_[StatusMsgLen + 1];
};


struct InnerRtnTrade
{
  char  InvestorID[InvestorIDLen + 1];
  char InstrumentID[InstrumentIDLen + 1];
  char  ExchangeID[ExchangeIDLen + 1];
  char  TradeID[TradeIDLen + 1];
  int   Direction;
  char  OrderSysID[OrderSysIDLen + 1];
  char  OffsetFlag;
  char  HedgeFlag;
  double  Price;
  int   Volume;
  char  TradeTime[UpdateTimeLen + 1];
};

struct InnerInstructment
{
  char InstrumentID[InstrumentIDLen + 1];
  ///交易所代码
  char ExchangeID[ExchangeIDLen + 1];
  ///合约名称
  char InstrumentName[InstrumentNameLen + 1];
  ///合约在交易所的代码
  char ExchangeInstID[InstrumentIDLen + 1];
  ///产品代码
  char ProductID[InstrumentIDLen + 1];
  ///产品类型
  char ProductClass;
  ///交割年份
  int DeliveryYear;
  ///交割月
  int DeliveryMonth;
  int VolumeMultiple;
  ///最小变动价位
  double PriceTick;
};

struct InnerTradingAccount
{
  ///经纪公司代码
  char BrokerID[BrokerIDLen + 1];
  ///投资者帐号
  char AccountID[AccountIDLen + 1];
  double PreBalance;
  double PreMargin;
  double CurrMargin;
  double Commission;
  ///平仓盈亏
  double CloseProfit;
  ///持仓盈亏
  double PositionProfit;
  ///期货结算准备金
  double Balance;
  ///可用资金
  double Available;
};

struct InnerDeferDeliveryQuot
{
  char         InstrumentID[InstrumentIDLen + 1];          //合约号
  int          AskVolume;              //申卖量
  int          BidVolume;              //申买量
  int          MidAskVolume;           //中立仓申卖量
  int          MidBidVolume;           //中立仓申买量
};

struct InnerInvestorPosition
{
  char   InstrumentID[InstrumentIDLen + 1];   //合约号
  char   PosiDirection;                       //持仓方向
  int   HedgeFlag;                            //投机套保标志   
  int   Position;                             //今日持仓
  int   YdPosition;                           //昨持仓
  int   PositionDate;
};

const static uint16_t TradingAccountType = 15;
const static uint16_t InstrumentType = 16;
const static uint16_t InstrumentEndType = 17;
const static uint16_t MdRspUserLoginType = 18;
const static uint16_t InnerMarketDataType = 19;
const static uint16_t RspOrderRejectType = 20;
const static uint16_t CancelOrderRejectType = 21;

const static uint16_t RspErrorType = 22;
const static uint16_t RtnOrderType = 23;
const static uint16_t RtnTradeType = 24;
const static uint16_t RtnTradeVolumeType = 35;
const static uint16_t SettlementInfoConfirmType = 25;
const static uint16_t ErrRtnOrderActionType = 26;
const static uint16_t RspInvestorPositionType = 27;
const static uint16_t RspQryOrderType = 28;
const static uint16_t RspOrderActionType = 29;
const static uint16_t RspQryTradeType = 30;
const static uint16_t DeferDeliveryQuotType = 31;
const static uint8_t  HeartBeatType = 32;
const static uint16_t RtnRejectType = 33;

const static char InterfaceCtp = '1';
const static char Interfacefeishu = '2';
const static char InterfaceEes = '3';
const static char InterfacefeishuMd = '4';
const static char Interfacefeishu41 = '5';
const static char InterfacefeishuMd41 = '6';
const static char InterfaceCtpMDRecord = '7';
const static char InterfaceQdp = '8';
const static char InterfaceKcbp = '9';
const static uint16_t BUFFER_SIZE = 1024;
#define BufferSIZE 33554432

#pragma pack(push, 1)
#pragma pack(pop)

template<typename T>
void InstrumentToInField(const T &source, InnerInstructment &inst)
{
  unsigned int len = strlen(source.InstrumentID);
  memcpy(inst.InstrumentID, source.InstrumentID, (len < InstrumentIDLen ? len : InstrumentIDLen));
  len = strlen(source.ExchangeID);
  memcpy(inst.ExchangeID, source.ExchangeID, (len < ExchangeIDLen ? len : ExchangeIDLen));
  len = strlen(source.InstrumentName);
  memcpy(inst.InstrumentName, source.InstrumentName, (len < InstrumentNameLen ? len : InstrumentNameLen));
  len = strlen(source.ExchangeInstID);
  memcpy(inst.ExchangeInstID, source.ExchangeInstID, (len < ExchangeIDLen ? len : ExchangeIDLen));
  len = strlen(source.ProductID);
  memcpy(inst.ProductID, source.ProductID, (len < InstrumentIDLen ? len : InstrumentIDLen));

  inst.ProductClass = source.ProductClass;
  inst.DeliveryYear = source.DeliveryYear;
  inst.DeliveryMonth = source.DeliveryMonth;
  inst.VolumeMultiple = source.VolumeMultiple;
  inst.PriceTick = source.PriceTick;
}

class Order
{
public:
  Order()
  {
    memset(this, 0, sizeof(Order));
  }
  int StrategyID;
  char BrokerID[BrokerIDLen + 1];
  char InvestorID[InvestorIDLen + 1];
  char InstrumentID[InstrumentIDLen + 1];
  int OrderMsgType;
  int OrderRef;
  char UserID[UserIDLen + 1];
  char Direction;
  char Offset;
  double LimitPrice;
  int Volume;
  int VolumeFilled;
  int VolumeRemained;
  int VolumeTotalOriginal;
  char TradingDay[TradingDayLen + 1];
  char OrderSysID[OrderSysIDLen + 1];
  char OrderStatus;
  int OrderType;
  double Price;
  char TradeID[TradeIDLen + 1];
  int OrdRejReason;
  char InsertTime[InsertTimeLen + 1];
  char UpdateTime[UpdateTimeLen + 1];
  char CancelTime[CancelTimeLen + 1];
  int FrontID;
  int SessionID;
  char StatusMsg[StatusMsgLen + 1];
  char ExchangeCode[ExchangeCodeLen + 1];
  double Fee;
  char CounterType;
  long long CounterSysID;
  int CancelAttempts;
  long long TimeStamp;

  void setStrategyID(void *value, uint16_t length = 0) {
    StrategyID = *static_cast<int*>(value);
  }
  void setBrokerID(void *value, uint16_t length = 0) {
    memcpy(BrokerID, static_cast<char*>(value), length < BrokerIDLen ? length : BrokerIDLen);
  }
  void setInvestorID(void *value, uint16_t length = 0) {
    memcpy(InvestorID, static_cast<char*>(value), length < InvestorIDLen ? length : InvestorIDLen);
  }
  void setInstrumentID(void *value, uint16_t length = 0) {
    memcpy(InstrumentID, static_cast<char*>(value), length < InstrumentIDLen ? length : InstrumentIDLen);
  }
  void setOrderMsgType(void *value, uint16_t length = 0) {
    OrderMsgType = *static_cast<int*>(value);
  }
  void setOrderRef(void *value, uint16_t length = 0) {
    OrderRef = *static_cast<int*>(value);
  }
  void setUserID(void *value, uint16_t length = 0) {
    memcpy(UserID, static_cast<char*>(value), length < UserIDLen ? length : UserIDLen);
  }
  void setDirection(void *value, uint16_t length = 0) {
    Direction = *static_cast<char*>(value);
  }
  void setOffset(void *value, uint16_t length = 0) {
    Offset = *static_cast<char*>(value);
  }
  void setLimitPrice(void *value, uint16_t length = 0) {
    LimitPrice = *static_cast<double*>(value);
  }
  void setVolume(void *value, uint16_t length = 0) {
    Volume = *static_cast<int*>(value);
  }
  void setVolumeFilled(void *value, uint16_t length = 0) {
    VolumeFilled = *static_cast<int*>(value);
  }
  void setVolumeRemained(void *value, uint16_t length = 0) {
    VolumeRemained = *static_cast<int*>(value);
  }
  void setVolumeTotalOriginal(void *value, uint16_t length = 0) {
    VolumeTotalOriginal = *static_cast<int*>(value);
  }
  void setTradingDay(void *value, uint16_t length = 0) {
    memcpy(TradingDay, static_cast<char*>(value), length < TradingDayLen ? length : TradingDayLen);
  }
  void setOrderSysID(void *value, uint16_t length = 0) {
    memcpy(OrderSysID, static_cast<char*>(value), length < OrderSysIDLen ? length : OrderSysIDLen);
  }
  void setOrderStatus(void *value, uint16_t length = 0) {
    OrderStatus = *static_cast<char*>(value);
  }
  void setOrderType(void *value, uint16_t length = 0) {
    OrderType = *static_cast<int*>(value);
  }
  void setPrice(void *value, uint16_t length = 0) {
    Price = *static_cast<double*>(value);
  }
  void setTradeID(void *value, uint16_t length = 0) {
    memcpy(TradeID, static_cast<char*>(value), length < TradeIDLen ? length : TradeIDLen);
  }
  void setOrdRejReason(void *value, uint16_t length = 0) {
    OrdRejReason = *static_cast<int*>(value);
  }
  void setInsertTime(void *value, uint16_t length = 0) {
    memcpy(InsertTime, static_cast<char*>(value), length < InsertTimeLen ? length : InsertTimeLen);
  }
  void setUpdateTime(void *value, uint16_t length = 0) {
    memcpy(UpdateTime, static_cast<char*>(value), length < UpdateTimeLen ? length : UpdateTimeLen);
  }
  void setCancelTime(void *value, uint16_t length = 0) {
    memcpy(CancelTime, static_cast<char*>(value), length < CancelTimeLen ? length : CancelTimeLen);
  }
  void setFrontID(void *value, uint16_t length = 0) {
    FrontID = *static_cast<int*>(value);
  }
  void setSessionID(void *value, uint16_t length = 0) {
    SessionID = *static_cast<int*>(value);
  }
  void setStatusMsg(void *value, uint16_t length = 0) {
    memcpy(StatusMsg, static_cast<char*>(value), length < StatusMsgLen ? length : StatusMsgLen);
  }
  void setExchangeCode(void *value, uint16_t length = 0) {
    memcpy(ExchangeCode, static_cast<char*>(value), length < ExchangeCodeLen ? length : ExchangeCodeLen);
  }
  void setFee(void *value, uint16_t length = 0) {
    Fee = *static_cast<double*>(value);
  }
  void setCounterType(void *value, uint16_t length = 0) {
    CounterType = *static_cast<char*>(value);
  }
  void setCounterSysID(void *value, uint16_t length = 0) {
    CounterSysID = *static_cast<long long *>(value);
  }
  void setCancelAttempts(void *value, uint16_t length = 0) {
    CancelAttempts = *static_cast<int*>(value);
  }
  void setTimeStamp(void *value, uint16_t length = 0) {
    TimeStamp = *static_cast<long long *>(value);
  }
  string toString()
  {
    char buffer[2048];
    SNPRINTF(buffer, sizeof buffer, "StrategyID=[%d]BrokerID=[%s]InvestorID=[%s]InstrumentID=[%s]OrderMsgType=[%d]OrderRef=[%d]UserID=[%s]Direction=[%c]Offset=[%c]LimitPrice=[%f]Volume=[%d]VolumeFilled=[%d]VolumeRemained=[%d]VolumeTotalOriginal=[%d]TradingDay=[%s]OrderSysID=[%s]OrderStatus=[%c]OrderType=[%d]Price=[%f]TradeID=[%s]OrdRejReason=[%d]InsertTime=[%s]UpdateTime=[%s]CancelTime=[%s]FrontID=[%d]SessionID=[%d]StatusMsg=[%s]ExchangeCode=[%s]Fee=[%f]CounterType=[%c]CounterSysID=[%I64d]CancelAttempts=[%d]TimeStamp=[%I64d]",
      StrategyID, BrokerID, InvestorID, InstrumentID, OrderMsgType, OrderRef, UserID, Direction, Offset, LimitPrice, Volume, VolumeFilled, VolumeRemained, VolumeTotalOriginal, TradingDay, OrderSysID, OrderStatus, OrderType, Price, TradeID, OrdRejReason, InsertTime, UpdateTime, CancelTime, FrontID, SessionID, StatusMsg, ExchangeCode, Fee, CounterType, CounterSysID, CancelAttempts, TimeStamp);
    return buffer;
  }

  void initMethodMap(std::map<std::string, setMethod> &methodMap) {
    methodMap["StrategyID"] = std::bind(&Order::setStrategyID, this, _1, _2);
    methodMap["BrokerID"] = std::bind(&Order::setBrokerID, this, _1, _2);
    methodMap["InvestorID"] = std::bind(&Order::setInvestorID, this, _1, _2);
    methodMap["InstrumentID"] = std::bind(&Order::setInstrumentID, this, _1, _2);
    methodMap["OrderMsgType"] = std::bind(&Order::setOrderMsgType, this, _1, _2);
    methodMap["OrderRef"] = std::bind(&Order::setOrderRef, this, _1, _2);
    methodMap["UserID"] = std::bind(&Order::setUserID, this, _1, _2);
    methodMap["Direction"] = std::bind(&Order::setDirection, this, _1, _2);
    methodMap["Offset"] = std::bind(&Order::setOffset, this, _1, _2);
    methodMap["LimitPrice"] = std::bind(&Order::setLimitPrice, this, _1, _2);
    methodMap["Volume"] = std::bind(&Order::setVolume, this, _1, _2);
    methodMap["VolumeFilled"] = std::bind(&Order::setVolumeFilled, this, _1, _2);
    methodMap["VolumeRemained"] = std::bind(&Order::setVolumeRemained, this, _1, _2);
    methodMap["VolumeTotalOriginal"] = std::bind(&Order::setVolumeTotalOriginal, this, _1, _2);
    methodMap["TradingDay"] = std::bind(&Order::setTradingDay, this, _1, _2);
    methodMap["OrderSysID"] = std::bind(&Order::setOrderSysID, this, _1, _2);
    methodMap["OrderStatus"] = std::bind(&Order::setOrderStatus, this, _1, _2);
    methodMap["OrderType"] = std::bind(&Order::setOrderType, this, _1, _2);
    methodMap["Price"] = std::bind(&Order::setPrice, this, _1, _2);
    methodMap["TradeID"] = std::bind(&Order::setTradeID, this, _1, _2);
    methodMap["OrdRejReason"] = std::bind(&Order::setOrdRejReason, this, _1, _2);
    methodMap["InsertTime"] = std::bind(&Order::setInsertTime, this, _1, _2);
    methodMap["UpdateTime"] = std::bind(&Order::setUpdateTime, this, _1, _2);
    methodMap["CancelTime"] = std::bind(&Order::setCancelTime, this, _1, _2);
    methodMap["FrontID"] = std::bind(&Order::setFrontID, this, _1, _2);
    methodMap["SessionID"] = std::bind(&Order::setSessionID, this, _1, _2);
    methodMap["StatusMsg"] = std::bind(&Order::setStatusMsg, this, _1, _2);
    methodMap["ExchangeCode"] = std::bind(&Order::setExchangeCode, this, _1, _2);
    methodMap["Fee"] = std::bind(&Order::setFee, this, _1, _2);
    methodMap["CounterType"] = std::bind(&Order::setCounterType, this, _1, _2);
    methodMap["CounterSysID"] = std::bind(&Order::setCounterSysID, this, _1, _2);
    methodMap["CancelAttempts"] = std::bind(&Order::setCancelAttempts, this, _1, _2);
    methodMap["TimeStamp"] = std::bind(&Order::setTimeStamp, this, _1, _2);
  }

  string toJson() const {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    rapidjson::Document outDoc;
    outDoc.SetObject();
    rapidjson::Document::AllocatorType& outAllocator = outDoc.GetAllocator();
    doc.AddMember("StrategyID", StrategyID, allocator);
    if (strlen(BrokerID) != 0) {
      int length = strlen(BrokerID) < BrokerIDLen ? strlen(BrokerID) : BrokerIDLen;
      doc.AddMember("BrokerID", rapidjson::Value().SetString(BrokerID, length), allocator);
    }
    if (strlen(InvestorID) != 0) {
      int length = strlen(InvestorID) < InvestorIDLen ? strlen(InvestorID) : InvestorIDLen;
      doc.AddMember("InvestorID", rapidjson::Value().SetString(InvestorID, length), allocator);
    }
    if (strlen(InstrumentID) != 0) {
      int length = strlen(InstrumentID) < InstrumentIDLen ? strlen(InstrumentID) : InstrumentIDLen;
      doc.AddMember("InstrumentID", rapidjson::Value().SetString(InstrumentID, length), allocator);
    }
    doc.AddMember("OrderMsgType", OrderMsgType, allocator);
    doc.AddMember("OrderRef", OrderRef, allocator);
    if (strlen(UserID) != 0) {
      int length = strlen(UserID) < UserIDLen ? strlen(UserID) : UserIDLen;
      doc.AddMember("UserID", rapidjson::Value().SetString(UserID, length), allocator);
    }
    doc.AddMember("Direction", rapidjson::Value().SetString(&Direction, 1), allocator);
    doc.AddMember("Offset", rapidjson::Value().SetString(&Offset, 1), allocator);
    if (!std::isnan(LimitPrice))
      doc.AddMember("LimitPrice", LimitPrice, allocator);
    doc.AddMember("Volume", Volume, allocator);
    doc.AddMember("VolumeFilled", VolumeFilled, allocator);
    doc.AddMember("VolumeRemained", VolumeRemained, allocator);
    doc.AddMember("VolumeTotalOriginal", VolumeTotalOriginal, allocator);
    if (strlen(TradingDay) != 0) {
      int length = strlen(TradingDay) < TradingDayLen ? strlen(TradingDay) : TradingDayLen;
      doc.AddMember("TradingDay", rapidjson::Value().SetString(TradingDay, length), allocator);
    }
    if (strlen(OrderSysID) != 0) {
      int length = strlen(OrderSysID) < OrderSysIDLen ? strlen(OrderSysID) : OrderSysIDLen;
      doc.AddMember("OrderSysID", rapidjson::Value().SetString(OrderSysID, length), allocator);
    }
    doc.AddMember("OrderStatus", rapidjson::Value().SetString(&OrderStatus, 1), allocator);
    doc.AddMember("OrderType", OrderType, allocator);
    if (!std::isnan(Price))
      doc.AddMember("Price", Price, allocator);
    if (strlen(TradeID) != 0) {
      int length = strlen(TradeID) < TradeIDLen ? strlen(TradeID) : TradeIDLen;
      doc.AddMember("TradeID", rapidjson::Value().SetString(TradeID, length), allocator);
    }
    doc.AddMember("OrdRejReason", OrdRejReason, allocator);
    if (strlen(InsertTime) != 0) {
      int length = strlen(InsertTime) < InsertTimeLen ? strlen(InsertTime) : InsertTimeLen;
      doc.AddMember("InsertTime", rapidjson::Value().SetString(InsertTime, length), allocator);
    }
    if (strlen(UpdateTime) != 0) {
      int length = strlen(UpdateTime) < UpdateTimeLen ? strlen(UpdateTime) : UpdateTimeLen;
      doc.AddMember("UpdateTime", rapidjson::Value().SetString(UpdateTime, length), allocator);
    }
    if (strlen(CancelTime) != 0) {
      int length = strlen(CancelTime) < CancelTimeLen ? strlen(CancelTime) : CancelTimeLen;
      doc.AddMember("CancelTime", rapidjson::Value().SetString(CancelTime, length), allocator);
    }
    doc.AddMember("FrontID", FrontID, allocator);
    doc.AddMember("SessionID", SessionID, allocator);
    if (strlen(StatusMsg) != 0) {
      int length = strlen(StatusMsg) < StatusMsgLen ? strlen(StatusMsg) : StatusMsgLen;
      doc.AddMember("StatusMsg", rapidjson::Value().SetString(StatusMsg, length), allocator);
    }
    if (strlen(ExchangeCode) != 0) {
      int length = strlen(ExchangeCode) < ExchangeCodeLen ? strlen(ExchangeCode) : ExchangeCodeLen;
      doc.AddMember("ExchangeCode", rapidjson::Value().SetString(ExchangeCode, length), allocator);
    }
    if (!std::isnan(Fee))
      doc.AddMember("Fee", Fee, allocator);
    doc.AddMember("CounterType", rapidjson::Value().SetString(&CounterType, 1), allocator);
    doc.AddMember("CounterSysID", CounterSysID, allocator);
    doc.AddMember("CancelAttempts", CancelAttempts, allocator);
    doc.AddMember("TimeStamp", TimeStamp, allocator);
    outDoc.AddMember("Title", rapidjson::Value().SetString("Order"), outAllocator);
    outDoc.AddMember("Content", doc, outAllocator);
    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    outDoc.Accept(writer);
    return strbuf.GetString();
  }
};


template<typename T>
void CommonOrderToInField(const T *source, Order &pOrder)
{
  unsigned int len = strlen(source->InvestorID);
  memcpy(pOrder.InvestorID, source->InvestorID, (len < InvestorIDLen ? len : InvestorIDLen));

  len = strlen(source->InstrumentID);
  memcpy(pOrder.InstrumentID, source->InstrumentID, (len < InstrumentIDLen ? len : InstrumentIDLen));

  len = strlen(source->OrderRef);
  pOrder.OrderRef = atoi(source->OrderRef);

  len = strlen(source->UserID);
  memcpy(pOrder.UserID, source->UserID, (len < UserIDLen ? len : UserIDLen));

  pOrder.LimitPrice = source->LimitPrice;

  len = strlen(source->ExchangeID);
  memcpy(pOrder.ExchangeID, source->ExchangeID, (len < ExchangeIDLen ? len : ExchangeIDLen));
}

template<typename T>
void RtnOrderToInField(const T *source, Order &pOrder)
{
  strcpy(pOrder.InvestorID, source->InvestorID);
  strcpy(pOrder.InstrumentID, source->InstrumentID);
  pOrder.OrderRef = atoi(source->OrderRef);
  memcpy(pOrder.UserID, source->UserID, UserIDLen);
  pOrder.Direction = source->Direction;
  pOrder.Offset = source->CombOffsetFlag[0];
  pOrder.LimitPrice = source->LimitPrice;
  pOrder.VolumeTotalOriginal = source->VolumeTotalOriginal;

  /*今成交数量*/
  pOrder.Volume = source->VolumeTraded;
  pOrder.VolumeRemained = source->VolumeTotal;
  memcpy(pOrder.TradingDay, source->TradingDay, TradingDayLen);
  strcpy(pOrder.OrderSysID, source->OrderSysID);
  memcpy(pOrder.InsertTime, source->InsertTime, UpdateTimeLen);
  memcpy(pOrder.UpdateTime, source->UpdateTime, UpdateTimeLen);
  memcpy(pOrder.CancelTime, source->CancelTime, UpdateTimeLen);
  pOrder.FrontID = source->FrontID;
  pOrder.SessionID = source->SessionID;
  memcpy(pOrder.StatusMsg, source->StatusMsg, StatusMsgLen);
  memcpy(pOrder.ExchangeCode, source->ExchangeID, ExchangeIDLen);
}
template<typename T>
void TradeToInField(const T *source, InnerRtnTrade &pTrade)
{
  unsigned int len = strlen(source->InvestorID);
  memcpy(pTrade.InvestorID, source->InvestorID, (len < InvestorIDLen ? len : InvestorIDLen));

  len = strlen(source->InstrumentID);
  memcpy(pTrade.InstrumentID, source->InstrumentID, (len < InstrumentIDLen ? len : InstrumentIDLen));

  len = strlen(source->ExchangeID);
  memcpy(pTrade.ExchangeID, source->ExchangeID, (len < ExchangeIDLen ? len : ExchangeIDLen));

  len = strlen(source->TradeID);
  memcpy(pTrade.TradeID, source->TradeID, (len < TradeIDLen ? len : TradeIDLen));

  pTrade.Direction = source->Direction;

  len = strlen(source->OrderSysID);
  memcpy(pTrade.OrderSysID, source->OrderSysID, (len < OrderSysIDLen ? len : OrderSysIDLen));

  pTrade.OffsetFlag = source->OffsetFlag;
  pTrade.HedgeFlag = source->HedgeFlag;
  pTrade.Price = source->Price;
  pTrade.Volume = source->Volume;

  len = strlen(source->TradeTime);
  memcpy(pTrade.TradeTime, source->TradeTime, (len < UpdateTimeLen ? len : UpdateTimeLen));
}

template<typename T>
void InvestorPositionToInField(const T *source, InnerInvestorPosition &position)
{
  unsigned int len = strlen(source->InstrumentID);
  memcpy(position.InstrumentID, source->InstrumentID, (len < InstrumentIDLen ? len : InstrumentIDLen));
  position.PosiDirection = source->PosiDirection;
  position.HedgeFlag = source->HedgeFlag;
  position.PositionDate = source->PositionDate;
  position.Position = source->Position;
}

template<typename T>
void AccountToInField(const T *source, InnerTradingAccount &account)
{
  unsigned int len = strlen(source->BrokerID);
  memcpy(account.BrokerID, source->BrokerID, (len < BrokerIDLen ? len : BrokerIDLen));
  ///投资者帐号
  len = strlen(source->AccountID);
  memcpy(account.AccountID, source->AccountID, (len < AccountIDLen ? len : AccountIDLen));

  account.PreBalance = source->PreBalance;
  account.PreMargin = source->PreMargin;
  account.CurrMargin = source->CurrMargin;
  account.Commission = source->Commission;
  account.CloseProfit = source->CloseProfit;
  account.PositionProfit = source->PositionProfit;
  account.Balance = source->Balance;
  account.Available = source->Available;
}

template<typename T>
void MarketDataToInField(const T *source, InnerMarketData &field)
{
  memset(&field, 0, sizeof(InnerMarketData));
  unsigned int len = strlen(source->TradingDay);
  memcpy(field.TradingDay, source->TradingDay, (len < TradingDayLen ? len : TradingDayLen));

  len = strlen(source->InstrumentID);
  memcpy(field.InstrumentID, source->InstrumentID, (len < InstrumentIDLen ? len : InstrumentIDLen));

  len = strlen(source->ExchangeID);
  memcpy(field.ExchangeID, source->ExchangeID, (len < ExchangeIDLen ? len : ExchangeIDLen));
  field.LastPrice = source->LastPrice;
  ///上次结算价
  field.PreSettlementPrice = source->PreSettlementPrice;
  ///昨收盘
  field.PreClosePrice = source->PreClosePrice;
  ///昨持仓量
  field.PreOpenInterest = source->PreOpenInterest;
  field.OpenPrice = source->OpenPrice;
  ///最高价
  field.HighestPrice = source->HighestPrice;
  ///最低价
  field.LowestPrice = source->LowestPrice;
  field.Volume = source->Volume;
  ///成交金额
  field.Turnover = source->Turnover;
  ///持仓量
  field.OpenInterest = source->OpenInterest;
  ///涨停板价
  field.UpperLimitPrice = source->UpperLimitPrice;
  ///跌停板价
  field.LowerLimitPrice = source->LowerLimitPrice;
  field.BidPrice1 = source->BidPrice1;
  field.BidVolume1 = source->BidVolume1;
  field.AskPrice1 = source->AskPrice1;
  field.AskVolume1 = source->AskVolume1;
  field.BidPrice2 = source->BidPrice2;
  field.BidVolume2 = source->BidVolume2;
  field.AskPrice2 = source->AskPrice2;
  field.AskVolume2 = source->AskVolume2;
  field.BidPrice3 = source->BidPrice3;
  field.BidVolume3 = source->BidVolume3;
  field.AskPrice3 = source->AskPrice3;
  field.AskVolume3 = source->AskVolume3;
  field.BidPrice4 = source->BidPrice4;
  field.BidVolume4 = source->BidVolume4;
  field.AskPrice4 = source->AskPrice4;
  field.AskVolume4 = source->AskVolume4;
  field.BidPrice5 = source->BidPrice5;
  field.BidVolume5 = source->BidVolume5;
  field.AskPrice5 = source->AskPrice5;
  field.AskVolume5 = source->AskVolume5;
  //   field.AveragePrice = source->AveragePrice;
  len = strlen(source->UpdateTime);
  memcpy(field.UpdateTime, source->UpdateTime, (len < UpdateTimeLen ? len : UpdateTimeLen));
  field.UpdateMillisec = source->UpdateMillisec;
}

enum OrderStatus
{
  Partiallyfilled = 'P',
  Filled = 'F',
  New = 'A',//ACKED
  Canceled = 'X',
  PendingCancel = 'C',
  PendingNew = 'N',
  NewRejected = 'R',
  CancelRejected = 'L',
  Suspended = 'S'
};

//reqeust position account by investorid
struct QryInvestorInfoField
{
  char  InvestorID[InvestorIDLen + 1];
  char  BrokerID[BrokerIDLen + 1];
  char  ExchangeID[ExchangeIDLen + 1];
  char  InstrumentID[InstrumentIDLen + 1];
  char  OrderSysID[OrderSysIDLen + 1];
  QryInvestorInfoField()
  {
    memset(this, 0, sizeof(QryInvestorInfoField));
  }
};
#endif





