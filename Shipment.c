#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "Shipment.h"

void read()
{
	double size, weight;
	int scanned, len, row, col, i;
	char point[4], c;
	struct Point destination;
	int loop = 1;
	int check;
	struct Shipment shipment = { 0 };
	init();
	printf("=================\n");
	printf("Seneca Deliveries\n");
	printf("=================\n");

	do {
	    size = weight = 0.0;
		row = col = scanned = len = 0;
		destination.row = destination.col = -1;
		printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
		scanned = scanf("%lf %lf %s", &weight, &size, point);
		len = strlen(point);

		//checks if user input for point is "x"
		if (!strcmp(point, "x"))
		{
			destination.row = 'x';
			destination.col = 0;
		}

		else
		{
			//Checks if user followed correct format (3 inputs separated by space)
			if (scanned != 3)
			{
				printf("Invalid input. Follow this example: 1 1 1A\n");
				while (getchar() != '\n') {}
				continue;
			}
			//breaks down string "point" to col and row variables
			for (i = 0; i < len; i++)
			{
				c = point[i];
				if (c >= '0' && c <= '9')
				{
					row = row * 10 + (c - '0');
				}
				else if (c >= 'A' && c <= 'Z')
				{
					col = col * 26 + (c - 'A');
				}
			}
			//Assigns the broken down row and col into the Point struct
			destination.row = --row;
			destination.col = col;
		}

		//Uses validate function
		check = validate(size, weight, destination);

		//If valid, creates a shipment struct and passes it to AssignTruck
		if (check == 1)
		{
			shipment.weight = weight;
			shipment.vol = size;
			shipment.destination.row = destination.row;
			shipment.destination.col = destination.col;
			AssignTruck(shipment);
		}

		//If user input is detected to be '0 0 x' then exits loop
		else if (check == 0)
			loop = 0;

	} while (loop);
}

int validate(double size, double weight, struct Point destination)
{
	struct Map map = populateMap();
	struct Map* testMap = &map;
	int check = 1;
	int min = 0; int max = 26;
	if (weight == 0 && size == 0 && destination.row == 'x')
	{
		printf("Thank you for shipping with Seneca!\n");
		check = 0;
	}
	else if (destination.row == NULL || destination.col == NULL || destination.row > max || destination.col > max)
		destination.row = destination.col = -1;

	if (check != 0)
	{
		if (weight > 1000 || weight < 1)
		{
			check = -2;
			printf("Invalid weight (must be 1-1000 Kg.)\n");
		}
		else if (size != S_SIZE && size != M_SIZE && size != L_SIZE)
		{
			check = -1;
			printf("Invalid size\n");
		}  
/*BUG 1*/	//Edit: Meet, update below condition to match destination
		else if ((destination.row < min || destination.row > max) || (destination.col < min || destination.row > max))
		{
			check = -3;
			printf("Invalid destination\n");
		}  //Add: Meet, Add below condition to double validate the destination within map
		else if (testMap->squares[(int)destination.row][(int)destination.col] == 0)
		{
			check = -3;
			printf("Invalid destination\n");
		}
	}
	return check;
}

int AssignTruck(struct Shipment s)
{
	int size = 0;
	int result = -1;
	struct Route routes[MAX_ROUTES] = { 0 };
	struct Route blueRoute = getBlueRoute();
	struct Route greenRoute = getGreenRoute();
	struct Route yellowRoute = getYellowRoute();
	trucks[0].route = &blueRoute;
	trucks[1].route = &greenRoute;
	trucks[2].route = &yellowRoute;
	double blueScore, greenScore, yellowScore;
	blueScore = calculateUtilizationScore(trucks[0].cargoWeight, trucks[0].cargoVol);
	greenScore = calculateUtilizationScore(trucks[1].cargoWeight, trucks[1].cargoVol);
	yellowScore = calculateUtilizationScore(trucks[2].cargoWeight, trucks[2].cargoVol);

	if ((blueScore + calculateUtilizationScore(s.weight, s.vol) > 0.0) &&
		(trucks[0].cargoWeight + s.weight <= MAX_WEIGHT) && (trucks[0].cargoVol + s.vol <= MAX_VOLUME))
		getAllTruckPaths(s, trucks[0], baseMap, &routes, &size);

	if ((greenScore + calculateUtilizationScore(s.weight, s.vol) > 0.0) &&
		(trucks[1].cargoWeight + s.weight <= MAX_WEIGHT) && (trucks[1].cargoVol + s.vol <= MAX_VOLUME))
		getAllTruckPaths(s, trucks[1], baseMap, &routes, &size);

	if ((yellowScore + calculateUtilizationScore(s.weight, s.vol) > 0.0) &&
		(trucks[2].cargoWeight + s.weight <= MAX_WEIGHT) && (trucks[2].cargoVol + s.vol <= MAX_VOLUME))
		getAllTruckPaths(s, trucks[2], baseMap, &routes, &size);

	int bestRoute = getBestRoute(routes, size, s);
	printRoute(routes[bestRoute], s);

	if (routes[bestRoute].routeSymbol == 2)
	{
		trucks[0].cargoVol += s.vol;
		trucks[0].cargoWeight += s.weight;
		result = 2;
	}
	else if (routes[bestRoute].routeSymbol == 4)
	{
		trucks[1].cargoVol += s.vol;
		trucks[1].cargoWeight += s.weight;
		result = 4;
	}
	else if (routes[bestRoute].routeSymbol == 8)
	{
		trucks[2].cargoVol += s.vol;
		trucks[2].cargoWeight += s.weight;
		result = 8;
	}
	return result;
}


float calculateUtilizationScore(double weight, double vol)
{

	float weightScore = 0, volumeScore = 0, score = 0;

	if (weight > 0)
		weightScore = (float)weight / MAX_WEIGHT;
	if (vol > 0)
		volumeScore = (float)vol / MAX_VOLUME;

	if (weight > 0 && vol > 0.0)
		score = weightScore / volumeScore;

	return score;
}

void init(void) {
	struct Map map = populateMap();
	baseMap = &map;

	struct Route blueRoute = getBlueRoute();
	struct Route greenRoute = getGreenRoute();
	struct Route yellowRoute = getYellowRoute();

	struct Route test;
	int i;
	for (i = 19; i <= 26; i++)
	{
		const struct Point start = { 9, i };
		const struct Point dest = { 7, 24 };
		const struct Shipment s = { 500, .5, dest };
		test = shortestPath(&map, start, dest);
		int result = containsDestination(&test, s);
		if (result == 1) printf("CONTAINS DESTINATION!\n");
	}
	struct Truck truck[3] = {
	{0, 0, &blueRoute},
	{0, 0, &greenRoute},
	{0, 0, &yellowRoute}
	};
	trucks[0].cargoVol = 0;
	trucks[0].cargoWeight = 0;
	trucks[1].cargoVol = 0;
	trucks[1].cargoWeight = 0;
	trucks[2].cargoVol = 0;
	trucks[2].cargoWeight = 0;
}

void printRoute(struct Route route, struct Shipment s)
{

	if (route.routeSymbol == 2)
	{
		printf("Ship on BLUE LINE, ");
	}
	else if (route.routeSymbol == 4)
	{
		printf("Ship on GREEN LINE, ");
	}
	else if (route.routeSymbol == 8)
	{
		printf("Ship on YELLOW LINE, ");
	}

	if (route.numPoints >= 1)
	{
		if (route.numPoints == 1)
		{
			printf("no diversion");
		}
		else {
			printf("divert: ");
			for (int i = 0; i < route.numPoints; i++)
			{
				// print last point - without "," at the end
				if (i == route.numPoints - 1)
				{
					printf("%d%c", route.points[i].row + 1, 'A' + route.points[i].col);

				}
				else {
					printf("%d%c, ", route.points[i].row + 1, 'A' + route.points[i].col);
				}
			}
			// if route does not contain the destination point, but goes to destination diagonally
			if (route.points[route.numPoints - 1].col != s.destination.col ||
				route.points[route.numPoints - 1].row != s.destination.row)
			{
				printf(", %d%c", s.destination.row + 1, 'A' + s.destination.col);
			}
		}
	}
	// if there are no trucks available
	else {
		printf("Ships tommorow");
	}
	printf("\n");
};

void getAllTruckPaths(struct Shipment s, struct Truck truck, const struct Map* map, struct Route routes[MAX_ROUTES], int* size)
{
	int j = 0;
	struct Map maps = populateMap();

	for (int i = 0; i < truck.route->numPoints; i++)
	{
		struct Route result = shortestPath(&maps, truck.route->points[i], s.destination);
		const struct Point resultDistance = result.points[result.numPoints - 1];

		// paths that reach the destination that have the previous point north, east, south, or west have destination in points array
		if (containsDestination(&result, s) == 1)
		{
			result.routeSymbol = truck.route->routeSymbol;
			routes[(*size)++] = result;
		}
		if (result.numPoints == 2)
		{
			for (int j = 0; j < truck.route->numPoints; j++)
			{
				if (result.points[0].row == truck.route->points[j].row &&
					result.points[0].col == truck.route->points[j].col)
				{
					result.points[0] = s.destination;
					result.numPoints = 1;
				}
			}
			result.routeSymbol = truck.route->routeSymbol;
			routes[(*size)++] = result;
		}

		// paths that reach the destination diagonally do not have the destination in points array
		else if (distance(&resultDistance, &s.destination) == 1 && containsDestination(&result, s) == 0)
		{
			result.routeSymbol = truck.route->routeSymbol;
			routes[(*size)++] = result;
		}
	};
};

int getBestRoute(struct Route routes[MAX_ROUTES], int s0, struct Shipment s)
{
	int res = 0;
	int i = 0;
/*BUG 2
	Edited by: Meet
	Changes: replace 1 with i.
*/
	for (i = 0; i < s0; i++)
	{
		if ((routes[i].numPoints < routes[res].numPoints))
		{
			res = i;
		}
	}
	return res;
};

int isBuilding(struct Route r, const struct Map* map)
{
	int building = 0;
	int i = 0;
	struct Map maps = populateMap();
	baseMap = &maps;

/*BUG 3
	Edited by:Meet
	Changes: Add flag condition and typecasting to avoid floating value in array.
*/
	while (i < r.numPoints && building == 0)
	{
		int routerow = r.points[i].row;
		int routecol = r.points[i].col;

		if (baseMap->squares[(int)r.points[i].row][(int)r.points[i].col] == 1)
		{
			building = 1;
		}

		i++;
	}
	return building;
}

int containsDestination(struct Route* route, struct Shipment shipment)
{
	int contains = 0;
	int i = 0;
	while (i < route->numPoints && contains == 0)
	{
		if (route->points[i].col == shipment.destination.col &&
			route->points[i].row == shipment.destination.row)
		{
			contains = 1;
		}
		i++;
	}
	return contains;
};