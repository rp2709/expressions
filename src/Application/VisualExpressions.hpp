#pragma once

#include <gtkmm-4.0/gtkmm.h>
#include <iostream>

#include "GtkmmTreeVisualizer.hpp"

class VisualExpressions : public Gtk::Window{

	Gtk::Grid container;

	Gtk::Entry expressionIO;

	GtkmmTreeVisualizer visualizer;
	Visualizer::Subject expressionContainer;

public:
    VisualExpressions();

    void onExpressionEnter();
};
