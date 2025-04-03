#pragma once

#include <gtkmm.h>
#include <iostream>

#include "../TreeVisualizer/BinaryTree.hpp"

#include "../Logger/Logger.hpp"

class GtkmmTreeVisualizer : public Visualizer, public Gtk::DrawingArea{
	Glib::RefPtr<Gtk::StyleContext> style_context = get_style_context();
	const Cairo::RefPtr<Cairo::Context>* cairo_ctx;

public:
	GtkmmTreeVisualizer():Visualizer(){
    	set_draw_func(sigc::mem_fun(*this, &GtkmmTreeVisualizer::on_draw));
    }

  	void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height){
		cairo_ctx = &cr;
    	style_context->render_background(cr, 0, 0, width, height);

    	double scale = width/std::max((double)getWidth(),1.);
    	scale = std::min(scale,1.);
    	Logger::log() << "Draw with scale :" << scale;

    	double displacement = (getLeftDistance() - getRightDistance()) / (double)getWidth() + 1;

    	cr->scale(scale,scale);

    	draw(displacement * width / 2 / scale, getTopDistance());
  	}

  	void drawNode(int x, int y, int r, const std::string& text) override{

		Pango::FontDescription font;

  		font.set_family("Monospace");
  		font.set_weight(Pango::Weight::BOLD);

  		// https://gnome.pages.gitlab.gnome.org/pangomm/classPango_1_1Layout.html
  		auto layout = create_pango_layout(text);

  		layout->set_font_description(font);

  		int text_width;
  		int text_height;

  		//get the text dimensions (it updates the variables -- by reference)
  		layout->get_pixel_size(text_width, text_height);

  		// draw circle representing the node
  		(*cairo_ctx)->arc(x, y, r, 0, 2 * M_PI);
  		(*cairo_ctx)->set_source_rgb(1.,1.,1.);
  		(*cairo_ctx)->fill();

  		// Position the text in the middle
  		(*cairo_ctx)->move_to(x-text_width/2,y-text_height/2);

  		(*cairo_ctx)->set_source_rgb(0.,0.,0.);
  		layout->show_in_cairo_context(*cairo_ctx);
	}

    void drawLine(int fromX, int fromY, int toX, int toY) override{
    	(*cairo_ctx)->set_source_rgb(1.,1.,1.);
		(*cairo_ctx)->move_to(fromX,fromY);
		(*cairo_ctx)->line_to(toX,toY);
		(*cairo_ctx)->stroke();
    }

    [[nodiscard]]int getTextWidth(const std::string& text) override{
    	Pango::FontDescription font;

  		font.set_family("Monospace");
  		font.set_weight(Pango::Weight::BOLD);

  		auto layout = create_pango_layout(text);

  		layout->set_font_description(font);

  		int text_width;
  		int text_height;

  		//get the text dimensions (it updates the variables -- by reference)
  		layout->get_pixel_size(text_width, text_height);
  		return text_width;
    }

    void update(const BinaryTree& tree)override{
    	Logger::log() << Logger::Indent::ENTER <<"Visualizer update start";
    	Logger::log() << "Reconstruct tree";
    	reconstructFrom(tree);
    	Logger::log() << "Request redraw";
    	queue_draw();
    	Logger::log() << Logger::Indent::LEAVE;
	}
};