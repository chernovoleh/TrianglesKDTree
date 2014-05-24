#pragma once

#include "TriangleKDTreeApi.h"

#include "Types.h"

#include <vector>
#include <memory>

class TRIANGLEKDTREE_API TriangleKDTree
{
public:
	TriangleKDTree(const std::vector<const Triangle *> & i_triangles);

	std::vector<const Triangle *> GetPickedTriangles(const Line & i_line) const;


private:
	struct Node;
	void _BuildTree(const std::vector<const Triangle *> &i_triangles, std::shared_ptr<Node> i_node) const;
	std::vector<const Triangle *> _TraceTree(const Line & i_line, std::shared_ptr<Node> i_node) const;
	std::shared_ptr<Node> mp_root;
};

struct TriangleKDTree::Node
{
	std::shared_ptr<Node> mp_left;
	std::shared_ptr<Node> mp_right;
	BBox m_box;
	std::vector<const Triangle *> m_triangles;
};