#include"server.h"
#include"stdio.h"
#include"string.h"

static uint32_t transnum = 0;
ST_accountsDB_t accountsdata[255] = { {16500.60,"1669267546321479"}, {266652.5,"36514321794562135"}, {12000,"25641795613475621"} ,{1275,"45963217565423165"}, \
{132432,"78214563975231469"}, {33692,"57963218562051426"} ,{562420,"20136599703525135"} ,{77430, "20035469302154376"} ,{45420, "33024697650512346"},{9000, "123654498523251469"}};

int account_num=10;
int account_id = 0;
ST_transaction_t transactions[255]={0};



EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
  
   uint32_t i;
   
    accountsdata[account_id].balance -= transData->terminalData.transAmount;

    return APPROVED;
    
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
    account_id = 0;
   uint8_t acc_flag=0;
   uint16_t i;
for ( i = 0; i < account_num; i++)
   {
       for (uint16_t j = 0; j < 20; j++)
       {
           if (accountsdata[i].primaryAccountNumber[j] == '\0')
           {
               break;
           }
           if (accountsdata[i].primaryAccountNumber[j] == cardData->primaryAccountNumber[j])
           {

               acc_flag = 1;
               

           }
           else
           {
               acc_flag = 0;
               goto checkflag;
               
           }
           
        }
   checkflag:
       if (acc_flag==1)
       {
           break;
       }
   }
   account_id = i;
   if(acc_flag==0) return DECLINED_STOLEN_CARD;
   else return OK;


}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
   uint8_t acc_flag=0;
   

   if (accountsdata[account_id].balance > termData->transAmount)
   {
       acc_flag = 1;
   }
   

   if(acc_flag==0) return LOW_BALANCE;
   else return OK;

}
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    printf("Your Current Balance is :%.2f\n", accountsdata[account_id].balance);
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
