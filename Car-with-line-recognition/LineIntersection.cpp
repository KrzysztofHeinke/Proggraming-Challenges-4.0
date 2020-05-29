#include "LineIntersection.h"
#include <opencv2/opencv.hpp>
#include <utility>

bool LineIntersection::is_intersection()
{
	if (static_cast<int>(source_equation.a) == static_cast<int>(target_equation.a))
	{
		return false;
	}
	double result_x = (source_equation.b - target_equation.b) / (source_equation.a - target_equation.a);
	double result_y = (-1) * ((target_equation.a * result_x) - target_equation.b);
	intersection = std::make_pair(result_x,result_y);

	double lesser_point_x1 = source_line_begin.x;
	double major_point_x1 = source_line_end.x;
	lesser_or_major(lesser_point_x1, major_point_x1);
	double lesser_point_x2 = target_line_begin.x;
	double major_point_x2 = target_line_end.x;
	lesser_or_major(lesser_point_x2, major_point_x2);

	
	if (result_x > lesser_point_x1 && result_x < major_point_x1 && result_x > lesser_point_x2 && result_x < major_point_x2)
	{
		return true;
	}
	return false;
}

void LineIntersection::lesser_or_major(double& a, double& b)
{
	double tmp_var;
	if ( a > b )
	{
		tmp_var = a;
		a = b;
		b = tmp_var;
	}
}
int LineIntersection::distance_measure()
{
	return 0;
}

void find_function(const float x1,const float y1, const float x2, const float y2, Function_Equation &equation)
{
	equation.a = (y1 - y2) / (x1 - x2);
	equation.b = (-1) * ((x2 * equation.a) - y2);
}
std::pair<int, int> LineIntersection::find_intersection()
{

	return std::pair<int, int>();
}

LineIntersection::LineIntersection(cv::Vec4i *source_line, cv::Vec4i *target_line) 
{
	source = source_line;
	target = target_line;
	source_line_begin.x = source[0][0];
	source_line_begin.y = source[0][1];
	source_line_end.x = source[0][2];
	source_line_end.y = source[0][3];
	find_function(source_line_begin.x, source_line_begin.y, source_line_end.x, source_line_end.y, source_equation);

	target_line_begin.x = target[0][0];
	target_line_begin.y = target[0][1];
	target_line_end.x = target[0][2];
	target_line_end.y = target[0][3];
	find_function(target_line_begin.x, target_line_begin.y, target_line_end.x, target_line_end.y, target_equation);
}