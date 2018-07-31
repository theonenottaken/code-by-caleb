/*
 * ClusterMaker.h
 *
 *  Created on: Jan 25, 2018
 *      Author: cal
 */

#ifndef CLUSTERMAKER_H_
#define CLUSTERMAKER_H_

#include "Cluster.h"
#include "Data.h"
#include "definitions.h"

class ClusterMaker {
private:
	Data data;
	std::vector<Cluster> clusters;
	double distanceBetweenClusters(Cluster& c1, Cluster& c2);
	void joinClusters(int ind1, int ind2);
	std::vector<int> getClusterList();
public:
	ClusterMaker(Data& d);
	std::vector<int> makeClusters();
};

#endif /* CLUSTERMAKER_H_ */
