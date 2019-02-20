

#include <stdio.h>
#include <conio.h>

#include "Hotel.h"
#include "Room.h"
#include "Customer.h"
#include "Reservation.h"
#include "Functions.h"

int main()
{
	hotel theHotel;

	customer *customerArray;
	customer *subStringCustomerArray;
	reservation *reservationArray;

	int userChoise;

	int customerArrayCounter = 1;
	int subStringCustomerArrayCounter = 1;
	int reservationArrayCounter = 1;

	int roomNumToCheckOut;
	int roomNumToPrint;
	int okToProcced;


	customerArray = (customer*)malloc(customerArrayCounter * sizeof(customer));
	if (!customerArray)
	{
		printf("ERROR! Not enough memory!\n");
		exit(1);
	}

	subStringCustomerArray = (customer*)malloc(subStringCustomerArrayCounter * sizeof(customer));
	if (!subStringCustomerArray)
	{
		printf("ERROR! Not enough memory!\n");
		exit(1);
	}

	reservationArray = (reservation*)malloc(reservationArrayCounter * sizeof(reservation));
	if (!reservationArray)
	{
		printf("ERROR! Not enough memory!\n");
		exit(1);
	}

	printf("Hello! and welcome to the hotel managment System!\n\n");

	do
	{
		printf("Please enter How many floors are in the hotel: ");
		scanf("%d", &theHotel.floorNumbers);
	} while (!(0 < theHotel.floorNumbers));

	do
	{
		printf("Please enter How many rooms are in the hotel: ");
		scanf("%d", &theHotel.roomNumbers);
	} while (!(0 < theHotel.roomNumbers));

	printf("\n");

	initializeNewHotel(&theHotel);

	do
	{
		flushall();
		printf("Press 1 to show the hotel rooms status\n");
		printf("Press 2 to add a new customer to the system\n");
		printf("Press 3 to register a CheckIn for a customer\n");
		printf("Press 4 to register a CheckOut for a customer\n");
		printf("Press 5 to print a specific room detailes\n");
		printf("Press 6 to convert all the customer's name first letter to a large letter\n");
		printf("Press 7 to receive All customers registerd to the hotel with a substr in thier name\n");
		printf("Press 0 to exit.\n");
		printf("\nPlease enter your choise: ");
		scanf("%d", &userChoise);

		switch (userChoise)
		{
		case 1:
			showHotelStatus(&theHotel);
			break;

		case 2:
			if (!(customerArrayCounter == (theHotel.floorNumbers * theHotel.roomNumbers + 1)))
			{
				addCustomer(&customerArray, &customerArrayCounter);
			}
			else
			{
				printf("The hotel is in full capacity");
			}
			break;

		case 3:
			if (!(customerArrayCounter == (theHotel.floorNumbers * theHotel.roomNumbers + 1)))
			{
				checkIn(&customerArray, &customerArrayCounter, &theHotel, &reservationArray, &reservationArrayCounter);
			}
			else
			{
				printf("The hotel is in full capacity");
			}
			break;

		case 4:
			if (1 < reservationArrayCounter)
			{
				printf("Please enter the room number to check out please: ");
				scanf("%d", &roomNumToCheckOut);

				okToProcced = checkTheRoomNumberReliability(&theHotel, roomNumToCheckOut);

				if (okToProcced == 1)
				{
					checkOut(roomNumToCheckOut, &theHotel, &reservationArray, &reservationArrayCounter);
					okToProcced = 0;
				}
				else
				{
					printf("No Such Room\n\n");
				}
			}
			else
			{
				printf("\nNo current reservations in the hotel\n\n");
			}
			break;

		case 5:
			if (1 < reservationArrayCounter)
			{
				printf("Please enter the room number that you would like to review: ");
				scanf("%d", &roomNumToPrint);

				okToProcced = checkTheRoomNumberReliability(&theHotel, roomNumToPrint);

				if (okToProcced == 1)
				{
					printSpecificRoomDetails(&theHotel, roomNumToPrint);
					okToProcced = 0;
				}
				else
				{
					printf("\nNo Such Room\n\n");
				}
			}
			else
			{
				printf("\nNo current reservations in the hotel\n\n");
			}
			break;

		case 6:
			if (1 < customerArrayCounter)
			{
				printf("Converting all the first letters...\n");
				convertTheFirstLetter(&customerArray, &customerArrayCounter);
				printf("Convertion Completed, all hotels customers first name letter converted to UpperCase Letter\n\n");
			}
			else
			{
				printf("\nThere are no hotel customers at this moment\n\n");
			}
			break;

		case 7:
			if (1 < customerArrayCounter)
			{
				int stringLetterCounter = 0;
				char name[50];

				do
				{
					flushall();
					printf("Please enter the sub string: ");
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

				returnAllWithSubstr(customerName, &customerArray, &customerArrayCounter, &subStringCustomerArray, &subStringCustomerArrayCounter);

				printf("Customers in the hotel with the sub string %s in their name are:\n\n", customerName);

				for (int i = 0; i < subStringCustomerArrayCounter - 1; i++)
				{
					printf("Customer Name: %s\n", subStringCustomerArray[i].customerName);
					printf("systemID: %d\n", subStringCustomerArray[i].systemID);
					printf("credit Card Number: %0.0lf\n", subStringCustomerArray[i].creditCardNumber);
					printf("Expiration Month: %d\n", subStringCustomerArray[i].creditCardExpirationMonth);
					printf("Expiration Year : %d\n\n", subStringCustomerArray[i].creditCardExpirationYear);
				}
				subStringCustomerArrayCounter = 0;
			}
			else
			{
				printf("\nThere are no hotel customers at this moment\n\n");
			}
			break;

		default:
			for (int i = 0; i < theHotel.floorNumbers; i++)
			{
				free(theHotel.roomsMatrix[i]);
			}

			for (int i = 0; i < customerArrayCounter - 1; i++){
				free(customerArray[i].customerName);
			}

			free(customerArray);
			free(subStringCustomerArray);
			free(reservationArray);

			printf("Thank you, have a great day.\n");

			break;
		}

	} while (userChoise != 0);

	system("pause");
}


