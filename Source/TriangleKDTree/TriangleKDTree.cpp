#include "StdAfx.h"
#include "TriangleKDTree.h"

#include <CGAL/intersections.h>

TriangleKDTree::TriangleKDTree(const std::vector<const Triangle *> & i_triangles)
{
	_BuildTree(i_triangles, mp_root);
}

void TriangleKDTree::_BuildTree(const std::vector<const Triangle *> &i_triangles, std::shared_ptr<Node> i_node) const
{
	i_node.reset(new Node());
	for(size_t tr_i = 0;tr_i < i_triangles.size();++tr_i)
		i_node->m_box += i_triangles[tr_i]->bbox();
	
	if(i_triangles.size() < 10)
	{
		i_node->m_triangles = i_triangles;
		return;
	}

	size_t max_dim_i = 0;
	double max_dim = 0.;
	for(size_t i = 0;i < 3;++i)
	{
		if(max_dim < i_node->m_box.max(i) - i_node->m_box.min(i))
		{
			max_dim = i_node->m_box.max(i) - i_node->m_box.min(i);
			max_dim_i = i;
		}
	}
		
	Point plane_point((i_node->m_box.max(1) - i_node->m_box.min(1)) / 2, (i_node->m_box.max(1) - i_node->m_box.min(1)) / 2, (i_node->m_box.max(2) - i_node->m_box.min(2)) / 2);
	Vector plane_vector(max_dim_i == 0 ? 1: 0, max_dim_i == 1 ? 1: 0, max_dim_i == 2 ? 1: 0);
	Plane plane(plane_point, plane_vector);

	std::vector<const Triangle *> triangles_left;
	for(size_t tr_i = 0;tr_i < i_triangles.size();++tr_i)
	{
		bool add = false;
		for(size_t i = 0;i < 3;++i)
			if(plane.has_on_positive_side(i_triangles[tr_i]->vertex(i)))
				add = true;
		if(add)
			triangles_left.push_back(i_triangles[tr_i]);
	}
		
	std::vector<const Triangle *> triangles_right;
	for(size_t tr_i = 0;tr_i < i_triangles.size();++tr_i)
	{
		bool add = false;
		for(size_t i = 0;i < 3;++i)
			if(plane.has_on_negative_side(i_triangles[tr_i]->vertex(i)))
				add = true;
		if(add)
			triangles_right.push_back(i_triangles[tr_i]);
	}
	_BuildTree(triangles_left, i_node->mp_left);
	_BuildTree(triangles_left, i_node->mp_right);
}

std::vector<const Triangle *> TriangleKDTree::GetPickedTriangles(const Line & i_line) const
{
	if(!mp_root)
		return std::vector<const Triangle *>();
	return _TraceTree(i_line, mp_root);
}

std::vector<const Triangle *> TriangleKDTree::_TraceTree(const Line & i_line, std::shared_ptr<Node> i_node) const
{
	if(!CGAL::do_intersect(i_line, i_node->m_box))
		return std::vector<const Triangle *>();

	std::vector<const Triangle *> result;
	if(i_node->mp_left)
	{
		std::vector<const Triangle *> res_1 = _TraceTree(i_line, i_node->mp_left);
		result.insert(result.end(), res_1.begin(), res_1.end());
	}
	if(i_node->mp_right)
	{
		std::vector<const Triangle *> res_1 = _TraceTree(i_line, i_node->mp_right);
		result.insert(result.end(), res_1.begin(), res_1.end());
	}	
	if(i_node->m_triangles.size() > 0)
	{
		for(size_t tr_i = 0;tr_i < i_node->m_triangles.size();++tr_i)
			if(CGAL::do_intersect(i_line, *i_node->m_triangles[tr_i]))
				result.push_back(i_node->m_triangles[tr_i]);
	}
	return result;
}