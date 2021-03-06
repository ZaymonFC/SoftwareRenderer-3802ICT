﻿#include "DecompositionService.h"
#include "GraphicsMath.h"


bool DecompositionService::ValidateTriangle(const std::vector<Point>& points, const Point& pOrigin, const Point& pPrev,
	const Point& pNext)
{
	if (GraphicsMath::Convex2D(pOrigin, pPrev, pNext) > 0)
	{
		for (const auto& point : points)
		{
			if (GraphicsMath::PointInTriangle(point, pOrigin, pNext, pPrev))
			{
				if (point == pOrigin || point == pNext || point == pPrev)
				{
					continue;
				}
				return false;
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}

std::vector<Face> DecompositionService::DecomposePolygon(std::vector<Point> points)
{
	auto faces = std::vector<Face>();

	unsigned int index = 0;

	while (points.size() > 2)
	{
		const auto pOrigin = points[index];
		const auto pNext = points.size() == index + 1 ? points.front() : points[index + 1];
		const auto pPrev = index == 0 ? points.back() : points[index - 1];

		if (ValidateTriangle(points, pOrigin, pPrev, pNext))
		{
			faces.emplace_back(pNext, pOrigin, pPrev);
			points.erase(points.begin() + index);
			index = 0;
		} 
		else
		{
			index = index += 1;
			if (index == points.size())
			{
				return std::vector<Face>();
			}
		}
	}

	return faces;
}
