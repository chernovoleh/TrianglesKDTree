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
	std::shared_ptr<Node> mp_root;
};

struct TriangleKDTree::Node
{
	std::shared_ptr<Node> mp_left;
	std::shared_ptr<Node> mp_right;
	BBox m_box;
	std::vector<const Triangle *> m_triangles;
};