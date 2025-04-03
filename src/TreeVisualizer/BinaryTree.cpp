#include "BinaryTree.hpp"

#include <stack>
#include "../Logger/Logger.hpp"

bool BinaryTree::Node::isLeaf()const{
    return not left and not right;
}

//TODO: Make the destructor of both Node and Binarytree iterative.
//For now, unique_pointers delete eachother in a recursive chain

Visualizer::Visualizer(const BinaryTree& tree){
    reconstructFrom(tree);
}

void Visualizer::reconstructFrom(const BinaryTree& tree){
    Logger::log() << Logger::Indent::ENTER << "reconstruct visualization tree";
    this->root.release(); // get rid of current tree

    if(not tree.root){
        Logger::log() << "Tree is empty" << Logger::Indent::LEAVE;
        return;
    }

    std::stack<std::unique_ptr<BinaryTree::Node>*> destinations;
    std::stack<BinaryTree::Node*> toCopy;
    toCopy.push(tree.root.get());
    destinations.push(&(this->root));
    while(not toCopy.empty()){
        BinaryTree::Node* current = toCopy.top();
        toCopy.pop();
        std::unique_ptr<BinaryTree::Node> *destination = destinations.top();
        destinations.pop();

        destination->reset(static_cast<BinaryTree::Node*>(new Visualizer::Node{current->toString()}));

        if(current->left){
            toCopy.push(current->left.get());
            destinations.push(&(*destination)->left);
        }
        if(current->right){
            toCopy.push(current->right.get());
            destinations.push(&(*destination)->right);
        }
    }
    Logger::log()<< "Visualization tree completed" << Logger::Indent::LEAVE;
}

void Visualizer::update(const BinaryTree& tree){
    Logger::log() << Logger::Indent::ENTER << "Start to update visualization";
    reconstructFrom(tree);
    Logger::log() << Logger::Indent::LEAVE;
}

std::string Visualizer::Node::toString()const{
    return text;
}

int Visualizer::Node::radius(Visualizer *owner){
    if(cachedRadius < 0)
        cachedRadius = owner->getTextWidth(text);
    return cachedRadius;
}

int Visualizer::Node::width(Visualizer *owner){
    if(cachedWidth < 0){
        if(isLeaf())
            cachedWidth = 2*(this->radius(owner));
        else
            cachedWidth =  static_cast<Visualizer::Node*>(left.get())->width(owner)
                        + owner->getMargin()
                        + static_cast<Visualizer::Node*>(right.get())->width(owner);
    }
    return cachedWidth;
}

int Visualizer::getTopDistance(){
    if(not root)
        return 0;
    return dynamic_cast<Visualizer::Node*>(root.get())->radius(this);
}

int Visualizer::getLeftDistance(){
    if(not root)
        return 0;
    if(not root->left)
        return getWidth() / 2;
    return dynamic_cast<Visualizer::Node*>(root->left.get())->width(this);
}

int Visualizer::getRightDistance(){
    if(not root)
        return 0;
    if(not root->right)
        return getWidth() / 2;
    return dynamic_cast<Visualizer::Node*>(root->right.get())->width(this);
}

int Visualizer::getWidth(){
    if(not root)
        return 0;
    return dynamic_cast<Visualizer::Node*>(root.get())->width(this);
}

void Visualizer::draw(int x, int y){
    if(not root)
        return;
    using Coords = std::pair<int,int>;
    std::stack<std::pair<Visualizer::Node*,Coords>> toDraw;
    toDraw.push({dynamic_cast<Visualizer::Node*>(root.get()),{x,y}});
    while(not toDraw.empty()){
        auto[node,coords] = toDraw.top();
        toDraw.pop();
        x = coords.first;
        y = coords.second;

        if(node->isLeaf()){
            drawNode(x, y, 0.75 * node->radius(this), node->text);
            continue;
        }
        //left
        Visualizer::Node* l = dynamic_cast<Visualizer::Node*>(node->left.get());
        int lx;
        if(l->isLeaf())
            lx = x - (l->width(this) + margin) / 2;
        else
            lx = x - margin/2 - dynamic_cast<Visualizer::Node*>(l->right.get())->width(this);

        //right
        Node* r = dynamic_cast<Visualizer::Node*>(node->right.get());
        int rx;
        if(r->isLeaf())
            rx = x + (r->width(this) + margin) / 2;
        else
            rx = x + margin/2 + dynamic_cast<Visualizer::Node*>(r->left.get())->width(this);

        int cy = y + std::max(l->radius(this),r->radius(this)) + margin + node->radius(this);

        drawLine(x,y,rx,cy);
        drawLine(x,y,lx,cy);

        drawNode(x, y, node->radius(this), node->text);

        if(node->left)toDraw.push({l,{lx,cy}});
        if(node->right)toDraw.push({r,{rx,cy}});
    }
}

Visualizer::Subject& Visualizer::Subject::operator=(BinaryTree* tree){
    Logger::log() << Logger::Indent::ENTER << "Start to change observed tree";
    this->tree.reset(tree);
    Logger::log() << "Tree changed";
    // alert all listeners
    for(Visualizer* listener : listeners)
        listener->update(*this->tree);
    Logger::log() << "Alerted listeners" << Logger::Indent::LEAVE;
    return *this;
}

void Visualizer::Subject::onAssign(Visualizer *visualizer){
    listeners.insert(visualizer);
}
