#include "Common.h"


// ---- ȫ�ֱ��� ---- //  
// ��������  
TThostFtdcBrokerIDType gBrokerID = "9999";                         // ģ�⾭���̴���  
TThostFtdcInvestorIDType gInvesterID = "13641868646";                         // Ͷ�����˻���  
TThostFtdcPasswordType gInvesterPassword = "centos123";                     // Ͷ��������  

                                                                            // �������  
CThostFtdcMdApi *g_pMdUserApi = nullptr;                           // ����ָ��  
char gMdFrontAddr[] = "tcp://180.168.146.187:10010";               // ģ������ǰ�õ�ַ  
char *g_pInstrumentID[] = { "TF1802", "zn1802", "rb1802", "CF802" }; // �����Լ�����б��С��ϡ���֣��������ѡһ��  
int instrumentNum = 4;                                             // �����Լ��������  

                                                                   // ���ײ���  
CThostFtdcTraderApi *g_pTradeUserApi = nullptr;                    // ����ָ��  
char gTradeFrontAddr[] = "tcp://180.168.146.187:10001";            // ģ�⽻��ǰ�õ�ַ  
TThostFtdcInstrumentIDType g_pTradeInstrumentID = "zn1705";         // �����׵ĺ�Լ����  
TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;       // ��������  
TThostFtdcPriceType gLimitPrice = 2818;                            // ���׼۸�
