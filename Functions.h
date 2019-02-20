#ifndef __Functions_H
#define __Functions_H

#include "Hotel.h"
#include "Room.h"
#include "Customer.h"
#include "Reservation.h"

int checkTheRoomNumberReliability(hotel *theHotel, int roomNumToCheck)
{
	for (int i = 0; i < theHotel->floorNumbers; i++)
	{
		int tempFloor = theHotel->floorNumbers;
		int digitCounter = 0;
		int multiple = 10;

		while (1 < tempFloor)
		{
			tempFloor /= 10;
			++digitCounter;
		}

		for (int i = 0; i < digitCounter; i++)
		{
			multiple *= 10;;
		}

		if ((i + 1) * multiple <= roomNumToCheck && roomNumToCheck < ((i + 1) * multiple) + theHotel->roomNumbers)
		{
			return 1;
		}
	}
	return 0;
}

int checkTheCreditCardNumberReliability(double long creditCardNumber, int creditCardExpirationMonth, int creditCardExpirationYear)
{
	int digitCounter = 0;

	while (1 < creditCardNumber)
	{
		creditCardNumber /= 10;
		++digitCounter;
	}

	if (digitCounter == 12 && (1 <= creditCardExpirationMonth && creditCardExpirationMonth <= 12) && (2010 <= creditCardExpirationYear && creditCardExpirationYear <= 2020))
	{
		printf("\nCredit Card information is Correct");
		return 1;
	}
	else
	{
		printf("\nCredit Card information is not correct\nThe credit Card length need to be 12 digits\nExpiration Month between 1-12\nExpiration Year between 2010-2020\n\n");
		return 0;
	}

}

void printSpecificRoomDetails(hotel *theHotel, int roomNumber)
{
	int floor;
	int room;

	floor = (roomNumber / 100) - 1;
	room = (roomNumber - ((floor + 1) * 100));

	if (theHotel->roomsMatrix[floor][room].isTaken == 1)
	{
		printf("\nThe room is taken.\n");
		printf("Customers Registered for the room are: %d\n", theHotel->roomsMatrix[floor][room].guestsRegistered);
		printf("Customers Registered For Breakfast: %d\n\n", theHotel->roomsMatrix[floor][room].guestRegisteredForBreakfast);
	}
	else
	{
		printf("\nThe Room is Not taken.\nthere are no current customers staying in the room\n\n");
	}
}

void convertTheFirstLetter(customer **customerArray, int const *customerArrayCounter)
{
	int firstLetterAscii;

	for (int i = 0; i < *customerArrayCounter - 1; i++)
	{
		firstLetterAscii = (*customerArray)[i].customerName[0];
		(*customerArray)[i].customerName[0] = firstLetterAscii - 32;
	}
}

void returnAllWithSubstr(char *customerName, customer **customerArray, int const *customerArrayCounter, customer **subStringCustomerArray, int *subStringCustomerArrayCounter)
{
	int j = 0;
	for (int i = 0; i < *customerArrayCounter - 1; i++)
	{
		if (strstr((*customerArray)[i].customerName, customerName))
		{
			(*subStringCustomerArray)[j] = (*customerArray)[i];
			*subStringCustomerArrayCounter += 1;
			*subStringCustomerArray = (customer*)realloc(*subStringCustomerArray, (*subStringCustomerArrayCounter)*sizeof(customer));
			j++;
		}
	}
}

#endif


