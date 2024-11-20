#pragma once
#ifndef MILESTONE3_H
#define MILESTONE3_H

#include <stdio.h>
#include "NewDataStructures.h" 

// Function Prototypes
/**
 * Determines the best truck for the shipment.
 * @return Index of the best truck, or -1 if no truck can deliver the package.
 */
int findTruckForShipment(Truck trucks[], int numTrucks, Package package, Map map);

/**
 * Calculates the shortest path to the destination using the A* algorithm.
 * @return The number of steps in the path, or -1 if no path is found.
 */
int calculateShortestPath(Map map, Point start, Point end, Point path[], int maxPathLength);

/**
 * Validates the package's weight and volume.
 * @return 1 if the package is valid, 0 otherwise.
 */
int validatePackage(Package package);

/**
 * Prints the results of the shipment, including the truck assigned and the route taken.
 */
void printShipmentDetails(const Truck* truck, const Package* package, double distance);

/**
 * Updates the truck's state after delivering a package.
 */
void updateTruckState(Truck* truck, Package package);

#endif 

