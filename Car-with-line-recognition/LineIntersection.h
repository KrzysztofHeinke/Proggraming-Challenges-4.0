#pragma once
#include <opencv2/opencv.hpp>
#include <utility>
struct Coordinates
{
	int x;
	int y;
};
struct Function_Equation
{
	double a;
	double b;
};
class LineIntersection
{
	// TODO
	// change to private
public:
	cv::Vec4i *source;
	cv::Vec4i *target;
	std::pair<double, double> intersection;
	Coordinates source_line_begin;
	Coordinates source_line_end;
	Function_Equation source_equation;
	Coordinates target_line_begin;
	Coordinates target_line_end;
	Function_Equation target_equation;
	int distance;

public:
	void lesser_or_major(double& a, double& b);
	bool is_intersection();
	int distance_measure();
	std::pair<int,int> find_intersection();
	LineIntersection(cv::Vec4i *source_line, cv::Vec4i *target_line);
};

