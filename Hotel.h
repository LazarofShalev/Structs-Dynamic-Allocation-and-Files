#ifndef __Hotel_H
#define __Hotel_H

#include "Room.h"

struct Hotel
{
	int floorNumbers;
	int roomNumbers;
	room **roomsMatrix;

}typedef hotel;

void initializeNewHotel(hotel *newHotel)
{
	newHotel->roomsMatrix = (room**)calloc(newHotel->floorNumbers, sizeof(room*));

	if (!newHotel->roomsMatrix) 
	{
		printf("ERROR! Not enough memory!\n");
		exit(1);
	}

	for (int i = 0; i < newHotel->floorNumbers; i++) 
	{
		newHotel->roomsMatrix[i] = (room*)calloc(newHotel->roomNumbers, sizeof(room));
	}
}

void showHotelStatus(hotel *hotelToShow) 
{
	for (int i = 0; i < hotelToShow->floorNumbers; i++) 
	{
		printf("\n");

		for (int j = 0; j < hotelToShow->roomNumbers; j++) 
		{
			if (hotelToShow->roomsMatrix[i][j].isTaken == 0) 
			{
				printf("Room %d is not taken", (i + 1) * 100 + j);
				printf("\n");
			}
			else 
			{
				printf("Room %d is taken\n", (i + 1) * 100 + j);
				printf("The number of customers registered for the room is: %d\n", hotelToShow->roomsMatrix[i][j].guestsRegistered);
				printf("The number of customers registered for Breakfast is: %d\n", hotelToShow->roomsMatrix[i][j].guestRegisteredForBreakfast);
				printf("\n");
			}
		}
		printf("\n");
	}
}

#endif