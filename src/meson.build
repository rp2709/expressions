subdir('ArgParser')
subdir('Logger')
subdir('Operators')
subdir('TreeVisualizer')
subdir('Expressions')
subdir('Application')

executable('expressions', 'main.cpp',
  install: true,
  link_with : [lib_operators,lib_visualize,libExpressions,libVisualExpressions,libLogger,libArgParser],
  dependencies : application_deps,
)