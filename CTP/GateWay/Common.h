#ifndef  __COMMON_H__
#define  __COMMON_H__

#include <string>
#include <unordered_map>
#include <memory>
#include  "ThostFtdcMdApi.h"
#include  "ThostFtdcTraderApi.h"
#include "RabbitMq.h"
class RabbitMq;

extern int g_i; // �˴�������,����,��ȫ�ֱ���ǰ��һ�� g_ �Ǻ�ϰ��.

                // ---- ȫ�ֱ��� ---- //  
                // ��������  
extern TThostFtdcBrokerIDType gBrokerID;                         // ģ�⾭���̴���  
extern TThostFtdcInvestorIDType gInvesterID;                         // Ͷ�����˻���  
extern TThostFtdcPasswordType gInvesterPassword;                     // Ͷ��������  

                                                                     // �������  
extern CThostFtdcMdApi *g_pMdUserApi;                           // ����ָ��  
extern char gMdFrontAddr[];               // ģ������ǰ�õ�ַ  
extern char *g_pInstrumentID[]; // �����Լ�����б��С��ϡ���֣��������ѡһ��  
extern int instrumentNum;                                             // �����Լ��������  

                                                                      // ���ײ���  
extern CThostFtdcTraderApi *g_pTradeUserApi;                    // ����ָ��  
extern char gTradeFrontAddr[];            // ģ�⽻��ǰ�õ�ַ  
extern TThostFtdcInstrumentIDType g_pTradeInstrumentID;         // �����׵ĺ�Լ����  
extern TThostFtdcDirectionType gTradeDirection;       // ��������  
extern TThostFtdcPriceType gLimitPrice;                            // ���׼۸�


#endif // ! __COMMON_H__



