#include"server.h"
static uint32_t transnum = 0;
ST_accountsDB_t accountsdata[255]={0};
accountsdata[0]={16500.60,1669267546321479};
accountsdata[1]={266652.5,3651432179456213};
accountsdata[2]={1200000000,2564179613475621};
accountsdata[3]={1275,4596321765423165};
accountsdata[4]={132432,7821463975231469};
accountsdata[5]={33692,5796321856201426};
accountsdata[6]={562420,2013659970325135};
accountsdata[7]={2690.5,1306523005941023};
accountsdata[8]={77430,2003546930214376};
accountsdata[9]={45420,3302469765012346};
int account_num=10;

ST_transaction_t transactions[255]={0};



EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
  
   uint32_t i;
   for (i = 0; i < account_num; i++)
   {
    if (accountsdata[i].primaryAccountNumber== transData->cardHolderData.primaryAccountNumber)
    {
        break;
    }
   }
   
    accountsdata[i].balance -= transData->terminalData.transAmount;
    return APPROVED;
    
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
    uint8_t acc_flag=0;
   uint32_t i;
   for (i = 0; i < account_num; i++)
   {
    if (accountsdata[i].primaryAccountNumber== cardData->primaryAccountNumber)
    {
        acc_flag=1;
    }
   }
   if(acc_flag==0) return DECLINED_STOLEN_CARD;
   else return OK;


}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    uint8_t acc_flag=0;
   uint32_t i;
   for (i = 0; i < account_num; i++)
   {
    if (accountsdata[i].balance> termData->transAmount)
    {
        acc_flag=1;
    }
   }
   if(acc_flag==0) return LOW_BALANCE;
   else return OK;

}
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    transactions[transnum].cardHolderData=transData->cardHolderData;
    transactions[transnum].terminalData=transData->terminalData;
    transactions[transnum].transactionSequenceNumber=transnum;
    transData->transactionSequenceNumber=transnum;
    transactions[transnum].transState=transData->transState;

    

    if (transactions[transnum].cardHolderData.primaryAccountNumber>0)
    {
        transnum++;
        return OK;
    }
    else return SAVING_FAILED;
}
