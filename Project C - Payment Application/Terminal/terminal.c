#include"terminal.h"
#include"stdio.h"
#include"time.h"


/*EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    termData->transactionDate[0] = tm.tm_mday/10;
    termData->transactionDate[1] = tm.tm_mday%10;
    termData->transactionDate[2] = '/';
    termData->transactionDate[5] = '/';
    if(tm.tm_mon>9)
    {termData->transactionDate[3] = tm.tm_mon/10;
     termData->transactionDate[4] = tm.tm_mon%10;
    }
    else 
    {termData->transactionDate[3] = '0';
    termData->transactionDate[4] = tm.tm_mon;
    }
    termData->transactionDate[6] = tm.tm_year/1000;
    termData->transactionDate[7] = (tm.tm_year%1000)/100;
    termData->transactionDate[8] = (tm.tm_year&100)/10;
    termData->transactionDate[9] = (tm.tm_year%10);
    return OK;
}*/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
 printf("Enter Card Transaction Date on the format DD/MM/YYYY:");
    fgets(termData->transactionDate,sizeof(termData->transactionDate),stdin);
    int strln = strlen(termData->transactionDate);
    if (strln > 10 || strln <10 || termData->transactionDate  == '\0' )
    {
        return WRONG_DATE;
    }
    else return K;
}



EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
    if (cardData.cardExpirationDate[3] >= termData.transactionDate[8])
    {
        if (cardData.cardExpirationDate[4] > termData.transactionDate[9])
        {
          return K; 
        }
    }
else if (cardData.cardExpirationDate[3] >= termData.transactionDate[8])
{
    if (cardData.cardExpirationDate[4]== termData.transactionDate[9])
    {
        if (cardData.cardExpirationDate[0]>= termData.transactionDate[3])
        {
            if (cardData.cardExpirationDate[1]>= termData.transactionDate[4])
            {
                return K;
            }
        }
    }
}
else return EXPIRED_CARD;

}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    printf("Enter Transaction Amount:");
    scanf_s("%f",&termData->transAmount);
    
    if (termData->transAmount<= 0)
    {
        return INVALID_AMOUNT;
    }
    else return K;


}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){

 if (termData->transAmount> termData->maxTransAmount)
    {
        return EXCEED_MAX_AMOUNT;
    }
    else return K;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
    printf("Set Max Transaction Amount:");
    uint32_t a ;
    scanf_s("%d",&a);
    termData->maxTransAmount=a;

if (termData->maxTransAmount<= 0)
    {
        return INVALID_MAX_AMOUNT;
    }
    else return K;

}
