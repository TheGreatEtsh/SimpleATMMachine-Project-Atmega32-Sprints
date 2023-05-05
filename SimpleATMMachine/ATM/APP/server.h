#ifndef SERVER_H
#define SERVER_H

//#include "..\Card\card.h"
//#include "..\Terminal\terminal.h"
#include "..\SERVICE\standard_Types.h"

#define DB_SIZE				10
#define MAX_TRANS_AMOUNT	5000
/**********************************************************************************************************************
  *  GLOBAL DATA TYPES AND STRUCTURES
  *********************************************************************************************************************/

typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, EXCEEDED_MAXIMUM_AMOUNT
}EN_transState_t;

typedef struct ST_cardData_t
{
	u8 primaryAcountNumber[20];
	u8 PIN[5];
}ST_cardData_t;

typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	f32 transactionAmount;
	EN_transState_t transState;
	u32 transactionSequenceNumber;
}ST_transaction_t;

typedef enum EN_serverError_t
{
	SERVER_OK, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT, EXCEEDED_MAX_AMOUNT
}EN_serverError_t;

typedef enum EN_accountState_t
{
	RUNNING,
	BLOCKED
}EN_accountState_t;

typedef struct ST_accountsDB_t
{
	f32 balance;
	EN_accountState_t state;
	u8 primaryAccountNumber[19];
}ST_accountsDB_t;



EN_transState_t		SERVER_recieveTransactionData(f32 *remainingBalance, f32 transAmount, ST_cardData_t *cardData);
EN_serverError_t	SERVER_isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t* accountRefrence);
EN_serverError_t	SERVER_isBlockedAccount(ST_accountsDB_t* accountRefrence);
EN_serverError_t	SERVER_isAmountAvailable(f32 f32_a_transactionAmount, ST_accountsDB_t* accountRefrence);
EN_serverError_t	SERVER_saveTransaction(ST_transaction_t* transData);
EN_serverError_t	SERVER_isBelowMaxAmount(f32 f32_a_transactionAmount);

#endif // !SERVER_H
