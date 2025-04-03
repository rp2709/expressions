application_sources = [
	'VisualExpressions.hpp',
	'VisualExpressions.cpp',
	'GtkmmTreeVisualizer.hpp',
]

application_deps = [
	dependency('gtkmm-4.0'),
]

libVisualExpressions = static_library(	'visual_expressions',application_sources,
										dependencies : application_deps,
										link_with : [lib_operators,lib_visualize,libExpressions,libLogger],
									 )	