# Farthest_to_Nearest

Vehicle Routing Problem (VRP) is an optimization problem in logistics aimed at determining the most efficient routes for a fleet of vehicles to deliver goods to various destinations, considering both travel distance and vehicle capacity. The goal is to minimize the total distance or cost of travel while meeting the demand at each destination and adhering to vehicle capacity constraints.

In finding an initial solution for the VRP, two commonly used methods are:

Random Method: This method involves connecting nodes (destinations) randomly, while considering the maximum capacity of vehicles and the demand at each node. Although straightforward, this approach often exhibits weaknesses in consistency, resulting in varying solutions with each execution, and tends to be less effective in route optimization.

Nearest Neighbor (NN) Method: This method connects nodes based on the nearest distance from the previous node, while also considering vehicle capacity and node demand. Nodes that are farthest from the central depot are usually addressed later. While more structured than the random method, NN often overlooks the critical role of distant nodes in achieving a more optimal route.

FTN Method (Farther Nodes First) has been developed to address the shortcomings of the random and NN methods. FTN prioritizes distant nodes, geographical boundaries, and node insertion from both ends to create better cycles. This method effectively integrates distant nodes, considers geographical limits, and designs routes with cycling formation, resulting in superior performance compared to the random and NN methods.

Testing on 15 case studies has shown that the FTN method delivers the best performance, particularly for cases with more than 100 nodes. FTN significantly outperforms other methods in forming better initial solutions by taking into account distance, geographical boundaries, and route cycling, thereby optimizing distribution routes more effectively.
