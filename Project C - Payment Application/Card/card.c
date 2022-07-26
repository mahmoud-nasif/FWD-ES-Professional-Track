#include"stdio.h"
#include"../StdTypes.h"
#include"card.h"
#include<string.h>



EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{

    printf("Enter Card Holder Name:");
    fgets(cardData->cardHolderName,sizeof(cardData->cardHolderName),stdin);
    int strln = strlen(cardData->cardHolderName);
    if(strln > 24 || strln <20 || cardData->cardHolderName[0] == '\0') {

        return WRONG_NAME;
    }
    else return OK;

}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    printf("Enter Card Expiry Date on the format MM/YY:");
    fgets(cardData->cardExpirationDate,sizeof(cardData->cardExpirationDate), stdin);
    int strln = strlen(cardData->cardExpirationDate);
    if (strln > 5 || strln <5 || cardData->cardExpirationDate[0] == '\0' || cardData->cardExpirationDate[2] != '/' )
    {
        return WRONG_EXP_DATE;
    }
    else return OK;

}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    printf("Enter Card PAN:");
    fgets(cardData->primaryAccountNumber, sizeof(cardData->primaryAccountNumber), stdin);
    int strln = strlen(cardData->primaryAccountNumber);
    if (strln < 16 || strln >19 || cardData->primaryAccountNumber[0] == '\0')
    {
        return WRONG_PAN;
    }
    else return OK;
}