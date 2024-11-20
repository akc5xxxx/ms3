#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "Shipment.h"

int main(void) {
	struct Map baseMap = populateMap();
	struct Route blueRoute = getBlueRoute();            //extract blue truck route
	struct Route greenRoute = getGreenRoute();          //extract green truck route
	struct Route yellowRoute = getYellowRoute();        //extract yellow truck route

	//combines all three routes to single map
	struct Map routeMap = addRoute(&baseMap, &blueRoute);
	routeMap = addRoute(&routeMap, &greenRoute);
	routeMap = addRoute(&routeMap, &yellowRoute);

	//To understand map legends
	printf("Map symbols:\n"
		"\"+\": common route | \".\": Green and Blue route | G: Green | Y: yellow | B: Blue\n\n");
	printMap(&routeMap, 1, 1);                //print complete map
	printf("\n\n");

	//initialize global variables to safe empty State
	init();

	//Take user input and process the shipment
	read();
	return 0;
}