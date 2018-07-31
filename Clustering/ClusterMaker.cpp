/*
 * ClusterMaker.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: cal
 */

#include "ClusterMaker.h"

ClusterMaker::ClusterMaker(Data& d) : data(d) {
	std::vector<Point> pts = data.getPoints();
	for (unsigned int i = 0; i < pts.size(); i++) {
		Cluster c(pts[i]);
		clusters.push_back(c);
	}
}

std::vector<int> ClusterMaker::makeClusters() {
	unsigned int goalNum = data.getNumberOfClusters();
	std::vector<Point> pts = data.getPoints();
	int clust1 = 0; // index 0
	int clust2 = 1; // index 1
	while (clusters.size() > goalNum) {
		double distance = distanceBetweenClusters(clusters[0], clusters[1]);
		for (unsigned int i = 0; i < clusters.size(); i++) {
			for (unsigned int j = 0; j < clusters.size(); j++) {
				if (i != j) {
					double d = distanceBetweenClusters(clusters[i], clusters[j]);
					if (d < distance) {
						distance = d;
						clust1 = i;
						clust2 = j;
					}
				}
			}
		}
		joinClusters(clust1, clust2);
	}
	return getClusterList();
}

double ClusterMaker::distanceBetweenClusters(Cluster& c1, Cluster& c2) {
	int type = data.getType();
	std::vector<Point> pts1 = c1.getPoints();
	std::vector<Point> pts2 = c2.getPoints();
	double distance;
	if (type == SINGLE) {
		distance = pts1[0].distance(pts2[0]);
		for (unsigned int i = 0; i < pts1.size(); i++) {
			for (unsigned int j = 0; j < pts2.size(); j++) {
				double d = pts1[i].distance(pts2[j]);
				if (d < distance)
					distance = d;
			}
		}
	} else {
		double sum = 0;
		int size1 = pts1.size();
		int size2 = pts2.size();
		for (int i = 0; i < size1; i++) {
			for (int j = 0; j < size2; j++) {
				sum += pts1[i].distance(pts2[j]);
			}
		}
		distance = sum / (size1 * size2);
	}
	return distance;
}

void ClusterMaker::joinClusters(int ind1, int ind2) {
	std::vector<Point> c = clusters[ind2].getPoints();
	for (unsigned int i = 0; i < c.size(); i++) {
		clusters[ind1].addPoint(c[i]);
	}
	clusters.erase(clusters.begin() + ind2);
}

std::vector<int> ClusterMaker::getClusterList() {
	std::vector<int> nums;
	std::vector<Point> points = data.getPoints();
	for (unsigned int i = 0; i < points.size(); i++) {
		for (unsigned int j = 0; j < clusters.size(); j++) {
			if (clusters[j].containsPoint(points[i])) {
				nums.push_back(j + 1);
				break;
			}
		}
	}
	return nums;
}
