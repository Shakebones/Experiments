LDFLAGS_COMMON = -framework Accelerate -framework GLUT -framework OpenGL -L/usr/local/lib/x86_64 -L/opt/local/lib -lstdc++ -lpng -lz -ljpeg -fopenmp -msse2
CFLAGS_COMMON = -c -Wall -I../../src/integrators -I../../src/linearalgebra -I../../src/geometry -I../../src/util -I../../src/glvu -DDO_PNG_OUT=0 -I./ -I/opt/local/include -I../../ -I../../src/Eigen/ -O3 -DNO_FFT -fopenmp -msse2

#LDFLAGS_COMMON = -framework Accelerate -framework GLUT -framework OpenGL ${GLVUFLAGS} -L/usr/local/lib/x86_64 -L/opt/local/lib -lstdc++ -lpng -lz -ljpeg -fopenmp -msse2 -fprofile-arcs -ftest-coverage
#CFLAGS_COMMON = -c -Wall -I../../src/integrators -I../../src/linearalgebra -I../../src/geometry -I../../src/util -I../../src/glvu -DDO_PNG_OUT=0 -I${GLVU_INCLUDE} -I./ -I/opt/local/include -I../../ -I../../src/Eigen/ -O1 -DNO_FFT -fopenmp -msse2 -fprofile-arcs -ftest-coverage
