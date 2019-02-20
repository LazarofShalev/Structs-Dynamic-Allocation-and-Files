#ifndef __Reservation_H
#define __Reservation_H

#include "Customer.h"
#include "Room.h"

struct Reservation 
{
	customer *customerRegistered;
	room *roomRegistered;
	int numOfGuestsRegistered;
	int numOfGuestRegisteredForBreakfast;
	int isCheckout; /**isCheckout when equals 0**/

}typedef reservation;

void checkIn(customer **customerArray, int *customerArrayCounter, hotel *theHotel, reservation **reservationArray, int *reservationArrayCounter)
{
	int userChoise;
	int tempGuestsRegistered;
	int tempGuestRegisteredForBreakfast;
	int proceedWithRegistration = 0;
	int guestIdToCheckIn;
	int guestIdAlreadyinTheSystem = 0;

	flushall();

	if (*customerArrayCounter == 1)
	{
		printf("\nThere are no hotel customers at these moment\n");
	}
	else
	{
		printf("\n---These are the current hotel customers---\n");
		for (int i = 0; i < *customerArrayCounter - 1; i++)
		{
			printf("\nCustomer Name: %s\n", (*customerArray)[i]);
			printf("SystemID: %d\n", (*customerArray)[i].systemID);
			printf("Credit Card Number: %0.0lf\n", (*customerArray)[i].creditCardNumber);
			printf("Credit Card Expiration Month: %d\n", (*customerArray)[i].creditCardExpirationMonth);
			printf("Credit Card Expiration Year: %d\n", (*customerArray)[i].creditCardExpirationYear);
			printf("\n");
		}
		printf("----------------------------------------------------------\n");
		printf("To choose a Customer already in the system please enter 1\n");
	}

	printf("To add a new customer please enter 0\n");

	do
	{
		printf("Please enter your choise: ");
		scanf("%d", &userChoise);

		if (userChoise == 1)
		{
			if (*customerArrayCounter == 1)
			{
				printf("There are no current customers\nPlease add a new customer by enter 0");
			}
			else
			{
				printf("Customer systemID: ");
				scanf("%d", &guestIdToCheckIn);

				guestIdToCheckIn--;
				proceedWithRegistration = 1;
			}
		}
		else if (userChoise == 0) 
		{
			guestIdToCheckIn = *customerArrayCounter - 1;

			guestIdAlreadyinTheSystem = addCustomer(customerArray, customerArrayCounter);

			if (guestIdAlreadyinTheSystem != -1)
			{
				printf("Customer already in the system.\nhis SystemID is: %d\n", guestIdAlreadyinTheSystem + 1);

				guestIdToCheckIn = guestIdAlreadyinTheSystem;
				proceedWithRegistration = 1;
			}
			else
			{
				proceedWithRegistration = 1;
			}
		}
	} while (proceedWithRegistration == 0);

	do
	{
		printf("how many Guests would you like to Register for the room?\nNote that a room can hold up to 4 Guests, including the customer you registered\n");
		printf("Please enter your choise: ");
		scanf("%d", &tempGuestsRegistered);
	} while (!(1 <= tempGuestsRegistered && tempGuestsRegistered <= 4));

	do
	{
		printf("\nhow many Guests would you like to Register For Breakfast?\nPlease note that non of the Guests have to be register for Breakfast, some of them, or all of them\n\n");
		printf("Please enter your choise: ");
		scanf("%d", &tempGuestRegisteredForBreakfast);
	} while (!(tempGuestRegisteredForBreakfast <= tempGuestsRegistered && tempGuestRegisteredForBreakfast <= 4));
	printf("\n");

	printf("Creating the new reservation...\n");

	printf("Looking for available room.....\n");
	for (int i = 0; i < theHotel->floorNumbers; i++)
	{
		for (int j = 0; j < theHotel->roomNumbers; j++)
		{
			if (theHotel->roomsMatrix[i][j].isTaken == 0)
			{
				printf("Available Room number %d found!\nAssigning the room to the new Reservation...\n\n", (i + 1) * 100 + j);

				(*reservationArray)[*reservationArrayCounter - 1].roomRegistered = &(theHotel->roomsMatrix[i][j]);
				(*reservationArray)[*reservationArrayCounter - 1].numOfGuestsRegistered = tempGuestsRegistered;
				(*reservationArray)[*reservationArrayCounter - 1].numOfGuestRegisteredForBreakfast = tempGuestRegisteredForBreakfast;
				(*reservationArray)[*reservationArrayCounter - 1].isCheckout = 1;

				theHotel->roomsMatrix[i][j].isTaken = 1;
				theHotel->roomsMatrix[i][j].guestsRegistered = tempGuestsRegistered;
				theHotel->roomsMatrix[i][j].guestRegisteredForBreakfast = tempGuestRegisteredForBreakfast;

				(*reservationArray)[*reservationArrayCounter - 1].customerRegistered = &*(*customerArray + guestIdToCheckIn);

				printf("Room Checked!\nHave a great day :)\n\n");
				*reservationArrayCounter += 1;
				*reservationArray = (customer*)realloc(*reservationArray, (*reservationArrayCounter)*sizeof(customer));
				i = theHotel->floorNumbers;
				j = theHotel->roomNumbers;
			}
		}
	}
}

void checkOut(int roomNumToCheckOut, hotel *theHotel, reservation **reservationArray, int const *reservationArrayCounter)
{
	int reservationArrayroomAddress;
	int hotelRoomAddress;

	int floor;
	int room;

	floor = (roomNumToCheckOut / 100) - 1;
	room = (roomNumToCheckOut - (100 * (floor + 1)));

	for (int i = 0; i < *reservationArrayCounter - 1; i++)
	{
		reservationArrayroomAddress = (*reservationArray)[i].roomRegistered;
		hotelRoomAddress = &(theHotel->roomsMatrix[floor][room]);

		if (reservationArrayroomAddress == hotelRoomAddress)
		{
			(*reservationArray)[i].isCheckout = 0;
		}
	}
	theHotel->roomsMatrix[floor][room].isTaken = 0;
	theHotel->roomsMatrix[floor][room].guestsRegistered = 0;
	theHotel->roomsMatrix[floor][room].guestRegisteredForBreakfast = 0;

	printf("\nRoom number %d checked Out.\nReservation Closed, Enjoy the rest of the day :)\n\n", roomNumToCheckOut);
}

#endif