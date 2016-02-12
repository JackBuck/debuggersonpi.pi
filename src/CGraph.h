/*
 * CGraph.h
 *
 *  Created on: 13 Nov 2015
 *      Author: Jack Buckingham
 */

#ifndef SRC_CGRAPH_H_
#define SRC_CGRAPH_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>

/* ~~~ SIMPLE TYPES USED BY CGRAPH ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * CGraph_DistMatCheckResult defines values returnable by the function CGraph::CheckInput_DistMat(),
 * which checks the format of a supplied distance matrix.
 */
enum class CGraph_DistMatCheckResult { undefined, square, lowerTriangular, upperTriangular, badShape, invalidElements, tooLarge};

/* ~~~ CLASS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This is a class to represent the mathematical concept of a graph.
 * See https://en.wikipedia.org/wiki/Graph_theory
 * It has facility for an external numbering of the vertices.
 * The reader should beware that (excepting the private functions which convert between the two
 * numberings) all public functions use the external vertex numbering and have a corresponding
 * private version prefixed 'Internal' which uses the internal vertex numbering. All private
 * functions which need a vertex numbering will use the internal numbering and be prefixed
 * 'Internal'.
 *
 * Public Member Functions:
 *  - GetOrder         = A function to return the order of the graph.
 *  - ShortestDistance = A function to return the shortest distance and a shortest path between two
 *                       supplied vertices of the graph.
 *                       See comments in the source file for details of the inputs and outputs.
 *
 *                       [This function is public interface for InternalShortestDistance.
 *                       It converts the inputs and outputs between the internal vertex numbering
 *                       and the external numbering, using internalShortestDistance to do the work.]
 *
 * Private Member Functions:
 *  - InternalToExternal        = A function to relabel vertex labels from internal to external.
 *  - ExternalToInternal        = A function to relabel vertex labels from external to internal.
 *  - InternalDijkstra          = An implementation of Dijkstra's algorithm.
 *                                https://en.wikipedia.org/wiki/Dijkstra's_algorithm
 *                                Results are saved in the member variables beginning 'm_Dijkstra'.
 *  - InternalShortestDistance  = Calls InternalDijkstra if necessary (or just reads the relevant
 *                                member variables) to compute the shortest distance between two
 *                                supplied points.
 *  - CGraph_DistMatCheckResult = A function to check a distance matrix has the correct format, and
 *                                to return that format using the enum class
 *                                CGraph_DistMatCheckResult.
 *
 * Member Variables:
 *  Graph properties
 *  - m_DistanceMatrix  = A distance matrix for the graph. Use -1 to indicate an infinite distance.
 *  - m_AdjacencyMatrix = An adjacency matrix for the graph. This should be kept consistent with
 *                        distance matrix.
 *  - m_Order           = The order of the graph.
 *
 *  Vertex labelling
 *	 - m_ExternalToInternal = A map where the value corresponding to key i is the internal label of
 *	                          the vertex with external label i.
 *	 - m_InternalToExternal = A vector whose ith element is the external label of the vertex with
 *	                          internal label i.
 *
 *  Dijkstra results
 *  - m_DijkstraOutputroutes      = Contains all previous output routes found when calling Dijkstra.
 *                                  The ith entry corresponds to the ith call to Dijkstra and
 *                                  contains a vector specifying the tree of shortest routes found.
 *  - m_DijkstraShortestDistances = Contains all previous shortest distances found when calling
 *                                  Dijkstra. The ith entry corresponds to the ith call to Dijkstra
 *                                  and contains a vector specifying the shortest distances between
 *                                  the start vertex and all the other vertices.
 *  - m_DijkstraStartVertices     = A map allow lookup of which index in m_DijkstraOutputroutes and
 *                                  m_DijkstraShortestDistances correspond to a requested start
 *                                  vertex.
 *
 * Exceptions:
 *  - InputDistMat_BadShape           = Thrown when the distance matrix passed to the constructor
 *                                      has an unrecognised shape.
 *  - InputDistMat_InvalidElements    = Thrown when the distance matrix passed to the constructor
 *                                      has at least one unrecognised element.
 *  - InputDistMat_MatrixTooLarge     = Thrown when the distance matrix passed to the constructor
 *                                      has some row or column whose number of elements is too
 *                                      large.
 *  - InputVertexLabels_BadSize       = Thrown when the wrong number of vertex labels is passed to
 *                                      the constructor.
 *  - InputVertexLabels_RepeatedLabel = Thrown when the vertex labels is passed to the constructor
 *                                      contain a repeat.
 *  - ShortestDistance_InvalidVertex  = Thrown when ShortestDistance is called with in invalid start
 *                                      vertex.
 *  - InternalException               = Thrown with a string message when the code is internally
 *                                      broken.
 *
 */
class CGraph
{
public:
	// === Constructors and Destructors =============================================================
	explicit CGraph(const std::vector<std::vector<double> >& distanceMatrix, const std::vector<int>& vertexLabels);

	// === Public Functions =========================================================================
	// Access functions
	unsigned int GetOrder() const {return m_Order;}

	// Dijkstra functions
	double ShortestDistance(const int& startVertex, const int& endVertex, std::vector<int>& outputRoute);
	double ShortestDistance(const int& startVertex, const int& endVertex, const bool& preferStartVertex, std::vector<int>& outputRoute);

	// === Exceptions ===============================================================================
	// TODO Derive these exceptions from a standard exception so they can be caught by generic exception handlers?
	struct InputDistMat_BadShape
	{
		std::vector<std::vector<double> > mm_DistanceMatrix;
		InputDistMat_BadShape(std::vector<std::vector<double> > distanceMatrix)
				: mm_DistanceMatrix { distanceMatrix }
		{
		}
	};
	struct InputDistMat_InvalidElements
	{
		std::vector<std::vector<double> > mm_DistanceMatrix;
		InputDistMat_InvalidElements(std::vector<std::vector<double> > distanceMatrix)
				: mm_DistanceMatrix { distanceMatrix }
		{
		}
	};
	struct InputDistMat_MatrixTooLarge
	{
		long unsigned int mm_requestedSize;
		unsigned int mm_largestPermittedSize;
		InputDistMat_MatrixTooLarge(long unsigned int requestedSize, unsigned int largestPermittedSize)
				: mm_requestedSize {requestedSize}, mm_largestPermittedSize {largestPermittedSize}
		{
		}
	};
	struct InputVertexLabels_BadSize
	{
		long unsigned int mm_vertexLabelsSize;
		InputVertexLabels_BadSize(long unsigned int vertexLabelsSize)
				: mm_vertexLabelsSize { vertexLabelsSize }
		{
		}
	};
	struct InputVertexLabels_RepeatedLabel
	{
		std::vector<int> mm_vertexLabels;
		InputVertexLabels_RepeatedLabel(std::vector<int> vertexLabels)
				: mm_vertexLabels { vertexLabels }
		{
		}
	};
	struct ShortestDistance_InvalidVertex
	{
		// The mm_startVertex and mm_endVertex here use the external labelling
		int mm_startVertex;
		int mm_endVertex;
		ShortestDistance_InvalidVertex(int startVertex, int endVertex)
				: mm_startVertex { startVertex }, mm_endVertex { endVertex }
		{
		}
	};
	struct InternalException
	{
		std::string mm_message;
		InternalException(std::string message)
				: mm_message { message }
		{
			std::cout << message << std::endl;
		}
	};

private:
	// === Private Functions ========================================================================
	// External look-up functions
	int InternalToExternal(const unsigned int) const;
	void InternalToExternal(const std::vector<unsigned int>&, std::vector<int>&) const;
	unsigned int ExternalToInternal(const int) const;
	void ExternalToInternal(const std::vector<int>&, std::vector<unsigned int>&) const;

	// Dijkstra functions
	void InternalShortestDistance(const unsigned int& startVertex, const unsigned int& endVertex, const bool& preferStartVertex, double& shortestDistance, std::vector<unsigned int>& outputRoute);
	unsigned int InternalDijkstra(const unsigned int& startVertex);

	// Helper functions
	CGraph_DistMatCheckResult CheckInput_DistMat(const std::vector<std::vector<double> >& distanceMatrix) const;

	// === Member Variables =========================================================================
	// Graph properties
	std::vector<std::vector<double> > m_DistanceMatrix;
	std::vector<std::vector<bool> > m_AdjacencyMatrix;
	unsigned int m_Order;

	// External vertex numbering look-up table
	std::map<int, unsigned int> m_ExternalToInternal;
	std::vector<int> m_InternalToExternal;

	// Saved Dijkstra output
	std::vector<std::vector<unsigned int> > m_DijkstraOutputRoutes;
	std::vector<std::vector<double> > m_DijkstraShortestDistances;
	std::map<unsigned int, unsigned int> m_DijkstraStartVertices;
};

#endif // SRC_CGRAPH_H_

