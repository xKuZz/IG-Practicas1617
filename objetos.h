//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include <random>
#include <cmath>
#include <ctime>
#include "file_ply_stl.h"

using namespace std;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);
void    vertice_en(unsigned pos, float x, float y, float z);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);

// Modificación
void    draw_caras_colores_distintos();
void    inicializar_colores();

void    cara_en(unsigned pos, int x, int y, int z);

vector<_vertex3i> caras;
vector<_vertex3f> color;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
    // Modificación
    _cubo(float tam, int desp_x, int desp_y, int desp_z);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase para objetos ply
//*************************************************************************

class _objeto_ply: public _triangulos3D {
public:
    _objeto_ply();

int parametros(char* archivo);
};

//*************************************************************************
// clase para objetos por revolución
//*************************************************************************

class _rotacion: public _triangulos3D {
public:
    _rotacion();
    void parametros(const vector<_vertex3f>& perfil1, int num1);

vector<_vertex3f> perfil;
int num;

};





