#ifndef __Customer_H
#define __Customer_H

struct Customer
{
	char *customerName;
	int systemID;
	double long creditCardNumber;
	int creditCardExpirationMonth;
	int creditCardExpirationYear;

}typedef customer;

int addCustomer(customer **customerArray, int *customerArrayCounter)
{
	double long creditCardNumber;
	int creditCardExpirationMonth;
	int creditCardExpirationYear;

	int needToBeAdded = 1;
	int guestIdAlreadyinTheSystemToReturn;
	int stringLetterCounter = 0;
	int okToProccedWithCreditCardNumber = 0;

	char name[50];
	do
	{
		flushall();
		printf("Please enter the customer name: ");
		gets(name);
	} while (name[0] == 0);

	for (int i = 0; i < 50; i++)
	{
		if (name[i] == 0)
		{
			break;
		}
		stringLetterCounter++;
	}

	char* customerName = (char*)calloc(stringLetterCounter + 1, sizeof(char));

	for (int i = 0; i < stringLetterCounter; i++)
	{
		customerName[i] = name[i];
	}

	do
	{
		printf("please enter the Card Number (12 Digits): ");
		scanf("%Lf", &creditCardNumber);
		printf("please enter the Expiration Month (1-12): ");
		scanf("%d", &creditCardExpirationMonth);
		printf("please enter the Expiration Year (2010-2020): ");
		scanf("%d", &creditCardExpirationYear);
		okToProccedWithCreditCardNumber = checkTheCreditCardNumberReliability(creditCardNumber, creditCardExpirationMonth, creditCardExpirationYear);
	} while (okToProccedWithCreditCardNumber == 0);

	printf("\n");

	if (1 < *customerArrayCounter) 
	{
		for (int i = 0; i < *customerArrayCounter - 1; i++)
		{
			if ((strcmp((*customerArray)[i].customerName, customerName) == 0) && (*customerArray)[i].creditCardNumber == creditCardNumber)
			{
				needToBeAdded = 0;
				guestIdAlreadyinTheSystemToReturn = i;
			}
		}
	}

	if (needToBeAdded == 1) 
	{
		(*customerArray)[*customerArrayCounter - 1].systemID = *customerArrayCounter;
		(*customerArray)[*customerArrayCounter - 1].customerName = customerName;
		(*customerArray)[*customerArrayCounter - 1].creditCardNumber = creditCardNumber;
		(*customerArray)[*customerArrayCounter - 1].creditCardExpirationMonth = creditCardExpirationMonth;
		(*customerArray)[*customerArrayCounter - 1].creditCardExpirationYear = creditCardExpirationYear;
		*customerArrayCounter += 1;

		*customerArray = (customer*)realloc(*customerArray, (*customerArrayCounter)*sizeof(customer));

		printf("Customer added successfully!\n\n");
		return -1;
	}
	return guestIdAlreadyinTheSystemToReturn;
}

#endif
