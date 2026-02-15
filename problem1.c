#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mode.h"
#include "nodesAndEdges.h"
#include "csvParse.h"

void printProblem1Details(int path[], int pathLen, int source, int target, 
                          double srcLat, double srcLon, double destLat, double destLon) {
    double Car_Rate = 20.0;
    double Total_Distance = 0.0;
    double Total_Cost = 0.0;

    printf("\nProblem No: 1\n");
    printf("Source: (%.6f, %.6f)\n", srcLon, srcLat);
    printf("Destination: (%.6f, %.6f)\n", destLon, destLat);
    printf("\n");

    if (fabs(nodes[source].lat - srcLat) > 1e-6 || fabs(nodes[source].lon - srcLon) > 1e-6) 
    {
        double walkDist = haversineDistance(srcLat, srcLon, 
                                           nodes[source].lat, nodes[source].lon);
        printf("Walk from Source (%.6f, %.6f) to (%.6f, %.6f), Distance: %.3f km, Cost: ৳0.00\n", 
               srcLon, srcLat, nodes[source].lon, nodes[source].lat, walkDist);
        Total_Distance += walkDist;
    }

    for (int i = pathLen - 1; i > 0; i--) {
        int from = path[i];
        int to = path[i - 1];                                 

        double distSeg = 0;
        for (int j = 0; j < numEdges; j++) 
        {
            if (edges[j].from == from && edges[j].to == to && edges[j].mode == MODE_CAR)       
            {
                distSeg = edges[j].distance;
                break;
            }
        }

        double costSeg = distSeg * Car_Rate;
        Total_Distance += distSeg;
        Total_Cost += costSeg;

        printf("Ride Car from (%.6f, %.6f) to (%.6f, %.6f), Distance: %.3f km, Cost: ৳%.2f\n",
               nodes[from].lon, nodes[from].lat,
               nodes[to].lon, nodes[to].lat,
               distSeg, costSeg);
    }

    if (fabs(nodes[target].lat - destLat) > 1e-6 || fabs(nodes[target].lon - destLon) > 1e-6) 
    {
        double walkDist = haversineDistance(nodes[target].lat, nodes[target].lon,               
                                           destLat, destLon);
        printf("Walk from (%.6f, %.6f) to Destination (%.6f, %.6f), Distance: %.3f km, Cost: ৳0.00\n",
               nodes[target].lon, nodes[target].lat, destLon, destLat, walkDist);

        Total_Distance += walkDist;
    }

    printf("\nTotal Distance: %.3f km\n", Total_Distance);
    printf("Total Cost: ৳%.2f\n", Total_Cost);
}

void runProblem1() {
    double srcLat, srcLon, destLat, destLon;

    printf("Enter source latitude and longitude: ");
    scanf("%lf %lf", &srcLat, &srcLon);

    printf("Enter destination latitude and longitude: ");
    scanf("%lf %lf", &destLat, &destLon);

    int source = findNearestNode(srcLat, srcLon);
    int target = findNearestNode(destLat, destLon);

    if (source == -1 || target == -1) {
        printf("Error: Could not find nodes\n");
        return;
    }

    printf("\nUsing nearest roadmap nodes:\n");
    printf("Source Node: %s (%.6f, %.6f)\n", nodes[source].name, nodes[source].lat, nodes[source].lon);
    printf("Target Node: %s (%.6f, %.6f)\n", nodes[target].name, nodes[target].lat, nodes[target].lon);

    for (int i = 0; i < numNodes; i++) 
    {
        dist[i] = INF;
        prev[i] = -1;            
        visited[i] = 0;
    }
    dist[source] = 0;

    for (int count = 0; count < numNodes; count++)            
    {
        int u = -1;
        double minDist = INF;

        for (int i = 0; i < numNodes; i++)
        {
            if (!visited[i] && dist[i] < minDist) 
            {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1 || u == target) break;

        visited[u] = 1;

        for (int i = 0; i < numEdges; i++) 
        {
            if (edges[i].from == u && edges[i].mode == MODE_CAR) 
            {
                int v = edges[i].to;
                double newDist = dist[u] + edges[i].distance;          

                if (newDist < dist[v]) 
                {
                    dist[v] = newDist;
                    prev[v] = u;
                }
            }
        }
    }

    
    int path[MAX_NODES];
    int pathLen = 0;

    for (int at = target; at != -1; at = prev[at]) 
    {
        path[pathLen++] = at;               
    }

    if (pathLen == 1 || dist[target] >= INF) {
        printf("No path found between the selected nodes.\n");
        return;
    }

    printf("\nShortest path found with distance: %.3f km\n\n", dist[target]);

    printProblem1Details(path, pathLen, source, target, srcLat, srcLon, destLat, destLon);

    exportPathToKML(path, pathLen, "route.kml");
}