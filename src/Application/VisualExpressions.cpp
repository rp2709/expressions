#include "VisualExpressions.hpp"

#include <sstream>
#include <limits>
#include "../Expressions/Expression.hpp"
#include "../Logger/Logger.hpp"

#include "../Expressions/Expression.hpp"
#include "../Operators/Addition.h"
#include "../Operators/Multiplication.h"
#include "../Operators/Substraction.h"
#include "../Operators/Power.h"
#include "../Operators/Division.h"

VisualExpressions::VisualExpressions()
{
        set_title("Expressions");
        set_default_size(500,500);

        // container
        container.set_margin(25);
        container.set_row_spacing(25);
        set_child(container);

        // Drawing area
        visualizer.set_hexpand(true);
        visualizer.set_halign(Gtk::Align::FILL);
        visualizer.set_vexpand(true);
        visualizer.set_valign(Gtk::Align::FILL);
        container.attach(visualizer,0,0);

        // Entry field
        expressionIO.signal_activate().connect(sigc::mem_fun(*this,&VisualExpressions::onExpressionEnter));
        expressionIO.set_placeholder_text("expression to evaluate");
        expressionIO.set_valign(Gtk::Align::END);
        container.attach(expressionIO,0,1);

        expressionContainer.onAssign(&visualizer);
        visualizer.setMargin(10);
}

void VisualExpressions::onExpressionEnter(){
    Logger::log() << Logger::Indent::ENTER << "Start on expression enter";
    std::stringstream exprStream(expressionIO.get_text());
    set_title(exprStream.str());

    std::stringstream result;
    try{
        Logger::log() << "Trying to construct expression tree";
        std::unique_ptr<Expression> exprTree(new Expression(exprStream));
        result << exprTree->evaluate();
        Logger::log() << "Expression created, giving tree to wrapper";
        expressionContainer = exprTree.release();
    }catch(const std::invalid_argument& error){
        result << error.what();
    }

    Logger::log() << "Resetting text";
    expressionIO.delete_selection();
    expressionIO.set_text(result.str());
    Logger::log() << Logger::Indent::LEAVE << "----------";
}
