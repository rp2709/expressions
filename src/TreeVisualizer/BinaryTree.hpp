#pragma once

#include <string>
#include <memory>
#include <set>

// Interface of a binary tree
class BinaryTree{
protected:
	struct Node{
		std::unique_ptr<Node> left = nullptr;
		std::unique_ptr<Node> right = nullptr;
		[[nodiscard]]bool isLeaf()const;
		[[nodiscard]]virtual std::string toString()const = 0;
		virtual ~Node() = default;
	};

public:
std::unique_ptr<Node> root = nullptr;
	virtual ~BinaryTree() = default;
};

// Interface of the binary tree iterator used by the visualizer
class Visualizer : public BinaryTree{
	struct Node : public BinaryTree::Node{
    	const std::string text;
    	int cachedWidth = -1;
    	int cachedRadius = -1;
    	Node(std::string text):text(std::move(text)){}
    	[[nodiscard]]int radius(Visualizer* owner);
    	[[nodiscard]]int width(Visualizer* owner);
    	std::string toString()const override;
    };

protected:
    unsigned margin = 0;
    unsigned fontSize = 1;

    virtual void drawNode(int x, int y, int r, const std::string& text) = 0;
    virtual void drawLine(int fromX, int fromY, int toX, int toY) = 0;
    [[nodiscard]]virtual int getTextWidth(const std::string& text) = 0;

    void reconstructFrom(const BinaryTree& tree);
    virtual void update(const BinaryTree& tree);
public:
    Visualizer(const BinaryTree& tree);
    Visualizer() = default;
    void draw(int x, int y);

	// They are getter and setters for margin and fontSize
	// The getters allow subclasses to enforce certain constraints by overriding them
    virtual void setMargin(unsigned value){margin = value;}
    [[nodiscard]]unsigned getMargin()const{return margin;}
    virtual void setFontSize(unsigned value){fontSize = value;}
    [[nodiscard]]unsigned getFontSize()const{return fontSize;}

    int getTopDistance();
    int getLeftDistance();
    int getRightDistance();
    int getWidth();

    class Subject{
    	std::unique_ptr<BinaryTree> tree = nullptr;
    	std::set<Visualizer*> listeners;
    public:
    	Subject() = default;
    	Subject& operator=(BinaryTree* tree);
    	void onAssign(Visualizer* visualizer);
    };
};