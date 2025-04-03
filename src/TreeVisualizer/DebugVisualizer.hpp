#pragma once

#include <iostream>

#include "BinaryTree.hpp"

class DebugVisualizer : public Visualizer{
public:
	DebugVisualizer(const BinaryTree& tree):Visualizer(tree){}
	DebugVisualizer():Visualizer(){}
	void drawNode(int x, int y, int r, const std::string& text)override{
		std::cout << "Draw node at (" << x << ',' << y
				  << ") with radius " << r
				  << " Content : " << text
				  << std::endl;
	}

    void drawLine(int fromX, int fromY, int toX, int toY)override{
    	std::cout << "Drew a line from (" << fromX << ',' << fromY
    			  << ") to (" << toX << ',' << toY << ")."
    			  << std::endl;
    }

    [[nodiscard]]int getTextWidth(const std::string& text)override{
    	return text.size() * 10;
    }

    void update(const BinaryTree& tree)override{
    	reconstructFrom(tree);
    	draw(0,0);
	}
};