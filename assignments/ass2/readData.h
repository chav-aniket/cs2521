// Created by Aniket Chavan (z5265106) on 22/07/19
#ifndef READDATA_H
#define READDATA_H

#include <stdio.h>
#include <stdlib.h>

#include "collectionList.h"
#include "graphMatrix.h"

CollectionList getCollection();

Graph getGraph(CollectionList cList);

#endif