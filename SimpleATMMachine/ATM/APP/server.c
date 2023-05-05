#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include "server.h"
#include "stddef.h"
#include "stdio.h"
#include "string.h"

ST_accountsDB_t accountsDB[DB_SIZE] = { {2000.0,	RUNNING, "1111000011110000"},
										{100000.0,	BLOCKED, "0000111100001111"},
										{100.0,		RUNNING, "1111222211112222"},
										{2500.0,	RUNNING, "2222111122221111"},
										{30000.0,	RUNNING, "2222333322223333"} };



EN_serverError_t SERVER_isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	u8 PAN[19] = {0};
	u8 compare = 0, reference = 0, functionReturn = 0;

	strcpy(PAN, cardData->primaryAcountNumber);
	
	for (; reference < DB_SIZE; reference++)
	{
		compare = strcmp(PAN, accountsDB[reference].primaryAccountNumber);
		if (!compare)
		{
			strcpy(accountRefrence->primaryAccountNumber, accountsDB[reference].primaryAccountNumber);
			accountRefrence->balance = accountsDB[reference].balance;
			accountRefrence->state = accountsDB[reference].state;
			
			break;
		}
		
	}
	
	if (compare)
	{
		functionReturn = ACCOUNT_NOT_FOUND;
		//accountRefrence = NULL;
	}
	else
	{
		functionReturn = SERVER_OK;
		
	}

	return functionReturn;

}

EN_serverError_t SERVER_isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	u8 accountState = 0, functionReturn = 0;
	accountState = accountRefrence->state;
	if (accountState == RUNNING)
	{
		functionReturn = SERVER_OK;
	}
	else if (accountState == BLOCKED)
	{
		functionReturn = BLOCKED_ACCOUNT;
	}
	else
	{
		/*DO NOTHING*/
	}
	return functionReturn;
}


EN_serverError_t	SERVER_isAmountAvailable(f32 f32_a_transactionAmount, ST_accountsDB_t* accountRefrence)
{
	f32  balance = 0;
	u8 checkAmount = 0;
	
	balance = accountRefrence->balance;
	
	if (balance >= f32_a_transactionAmount)
	{
		checkAmount = SERVER_OK;
	}
	else
	{
		checkAmount = LOW_BALANCE;
	}

	return checkAmount;
}





EN_transState_t	SERVER_recieveTransactionData(f32 *remainingBalance, f32 transAmount, ST_cardData_t* cardData)
{
	
	u8  PAN[19];
	u8 accountValidity = 0, amountAvailability = 0, accountState = 0, functionReturn = 0, amountValidity = 0;
	ST_accountsDB_t accReference;

	strcpy(PAN,	cardData->primaryAcountNumber);


	accountValidity = SERVER_isValidAccount(cardData, &accReference);
	
	accountState = SERVER_isBlockedAccount(&accReference);

	amountAvailability = SERVER_isAmountAvailable(transAmount, &accReference);
	
	amountValidity	= SERVER_isBelowMaxAmount(transAmount);

	if (accountValidity == ACCOUNT_NOT_FOUND)
	{
		functionReturn = FRAUD_CARD;
	}
	else if (accountState == BLOCKED_ACCOUNT)
	{
		functionReturn = DECLINED_STOLEN_CARD;
	}
	else if (amountAvailability == LOW_BALANCE)
	{
		functionReturn = DECLINED_INSUFFECIENT_FUND;
	}
	else if (amountValidity == EXCEEDED_MAX_AMOUNT)
	{
		functionReturn = EXCEEDED_MAXIMUM_AMOUNT;
	}
	else
	{
		functionReturn = APPROVED;
		for (u8 index = 0; index < DB_SIZE; index++)
		{	 
			if (!strcmp(PAN, accountsDB[index].primaryAccountNumber))
			{
				accountsDB[index].balance -= transAmount;
				*remainingBalance = accountsDB[index].balance;
			}

		}
	}


	return functionReturn;
	
}

EN_serverError_t	SERVER_isBelowMaxAmount(f32 f32_a_transactionAmount)
{
	EN_serverError_t status ;
	
	if (f32_a_transactionAmount > MAX_TRANS_AMOUNT)
	{
		status= EXCEEDED_MAX_AMOUNT;

	}
	else
	{
		status= SERVER_OK;

	}
	return status;
}