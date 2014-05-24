#pragma once

#include <CGAL/Cartesian.h>
#include <CGAL/Point_3.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/Line_3.h>
#include <CGAL/Bbox_3.h>
#include <CGAL/Vector_3.h>
#include <CGAL/Plane_3.h>

typedef CGAL::Cartesian<double> Kernel;
typedef CGAL::Point_3<Kernel> Point;
typedef CGAL::Triangle_3<Kernel> Triangle;
typedef CGAL::Bbox_3 BBox;
typedef CGAL::Line_3<Kernel> Line;
typedef CGAL::Vector_3<Kernel> Vector;
typedef CGAL::Plane_3<Kernel> Plane;

