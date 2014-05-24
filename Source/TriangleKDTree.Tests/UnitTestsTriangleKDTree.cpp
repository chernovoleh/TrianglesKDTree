#include "stdafx.h"
#include <gtest/gtest.h>

#include <TriangleKDTree/TriangleKDTree.h>

TEST(TriangleKDTree, Build)
{
	std::vector<const Triangle *> triangles;
	TriangleKDTree tree(triangles);
}