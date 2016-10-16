reset
set ylabel 'time(sec)'
set style fill solid
set title 'perfomance comparison'
set term png size 1024,512 enhanced font 'Verdana,11'
set output 'runtime.png'

plot [:][:0.08]'output.txt' using 2:xtic(1) with histogram title 'original', \
'' using ($0-0.15):($2+0.001):2 with labels title ' ', \
'' using 3:xtic(1) with histogram title 'small-struct'  , \
'' using ($0+0.01):($3+0.0015):3 with labels title ' ', \
'' using 4:xtic(1) with histogram title 'binary-search-tree', \
'' using ($0+0.17):($4+0.0015):4 with labels title ' ', \
'' using 5:xtic(1) with histogram title 'hash-table', \
'' using ($0+0.36):($5+0.001):5 with labels title ' ', \
