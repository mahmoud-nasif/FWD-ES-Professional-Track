
#include"app.h"



void appStart(void)
{

ST_cardData_t card;
EN_cardError_t card_error;
ST_terminalData_t terminal;
EN_terminalError_t terminal_error;
ST_transaction_t transaction;
EN_transState_t transaction_state;
EN_serverError_t server;

start:
printf("Insert Your Card\n");
CardNameError:

card_error= getCardHolderName(&card);
if(card_error = WRONG_NAME)
{
    printf("Wrong Entry, Please Try again");
    goto CardNameError;
}
CardExpiryDate:
card_error= getCardExpiryDate(&card);
if(card_error = WRONG_EXP_DATE)
{
    printf("Wrong Entry, Please Try again");
    goto CardExpiryDate;
}
CardPAN:
card_error= getCardPAN(&card);
if(card_error = WRONG_PAN)
{
    printf("Wrong Entry, Please Try again");
    goto CardPAN;
}
terminal_error = getTransactionDate(&terminal);

terminal_error = isCardExpired(card,terminal);
if(terminal_error = EXPIRED_CARD)
{
    printf("Declined Expired Card, Transaction Rejected");
    goto start;
}
InvalidAmount:
terminal_error = getTransactionAmount(&terminal);
if(terminal_error = INVALID_AMOUNT)
{
    printf("Invaild Amount, Please Try again");
    goto InvalidAmount;
}

terminal_error = isBelowMaxAmount(&terminal);
if(terminal_error = EXCEED_MAX_AMOUNT)
{
    printf("Exceed Max Amount, Transaction Rejected");
    goto start;
}



transaction.cardHolderData=card;
transaction.terminalData=terminal;



server = isValidAccount(&card);
if(server = DECLINED_STOLEN_CARD)
{
    printf("****Declined Stolen Card****");
    transaction.transState=DECLINED_STOLEN_CARD;
    server = saveTransaction(&transaction);
    if(server = SAVING_FAILED)
{
    printf("Saving Failed, Server Error!");
}
    goto start;
}


server = isAmountAvailable(&terminal);
if(server = LOW_BALANCE)
{
    printf("LOW BALANCE, Transaction Rejected");
    transaction.transState=DECLINED_INSUFFECIENT_FUND;
    server = saveTransaction(&transaction);
    if(server = SAVING_FAILED)
{
    printf("Saving Failed, Server Error!");
}
    goto start;
}

server = recieveTransactionData(&terminal);
if(server = APPROVED)
{
    printf("APPROVED Transaction!");
     transaction.transState=APPROVED;
    server = saveTransaction(&transaction);
    if(server = SAVING_FAILED)
{
    printf("Saving Failed, Server Error!");
}

    goto start;
}



}