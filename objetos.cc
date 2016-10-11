#include "objetos.h"


// Constructor vacío
_puntos3D::_puntos3D() {}

// Dibujar los puntos 3D, Entrada colores y tamaño

void _puntos3D::draw_puntos(float r, float g, float b, int grosor) {
    glPointSize(grosor);
    glColor3f(r,g,b);
    glBegin(GL_POINTS);

    for (unsigned i = 0; i < vertices.size(); ++i)
        glVertex3fv((GLfloat*) &vertices[i]);

    glEnd();

}

void _puntos3D::vertice_en(unsigned pos, float x, float y, float z)
{
    vertices[pos].x = x;
    vertices[pos].y = y;
    vertices[pos].z = z;
}



_triangulos3D::_triangulos3D() {}

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(grosor);
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES);

    for (unsigned i = 0; i < caras.size(); ++i) {
        glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
    }

    glEnd();


}

void _triangulos3D::draw_solido(float r, float g, float b)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES);

    for (unsigned i = 0; i < caras.size(); ++i) {
        glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
    }

    glEnd();

}

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_TRIANGLES);

    for (unsigned i = 0; i < caras.size(); ++i) {
        if (i % 2 == 0)
            glColor3f(r1,g1,b1);
        else
            glColor3f(r2,g2,b2);
        glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
    }

    glEnd();
}

void _triangulos3D::draw_caras_colores_distintos()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);

    for (unsigned i = 0; i < caras.size(); ++i) {
        glColor3fv((GLfloat*) &color[i]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
    }

    glEnd();

}

void _triangulos3D::inicializar_colores()
{
    if (color.empty()) {
        color.resize(caras.size());

        for (unsigned i= 0; i < color.size(); ++i) {
          bool repetido = true;

          while (repetido) {
            repetido = false;
            float color1 = (float) rand() / (float) RAND_MAX;
            float color2 = (float) rand() / (float) RAND_MAX;
            float color3 = (float) rand() / (float) RAND_MAX;

            color[i].x  = color1;
            color[i].y  = color2;
            color[i].z  = color3;

            for (unsigned j = 0; j < i && !repetido; ++j)
                if (color[i] == color[j])
                    repetido = true;
          }
        }

    }

}

void _triangulos3D::cara_en(unsigned pos, int x, int y, int z)
{
    caras[pos]._0 = x;
    caras[pos]._1 = y;
    caras[pos]._2 = z;
}


_piramide::_piramide(float tam, float al)
{
    vertices.resize(5);
    vertice_en(0, -tam,  0,  tam);
    vertice_en(1,  tam,  0,  tam);
    vertice_en(2,  tam,  0, -tam);
    vertice_en(3, -tam,  0, -tam);
    vertice_en(4,    0, al,    0);


    caras.resize(6);
    cara_en(0,  0,1,4);
    cara_en(1,  1,2,4);
    cara_en(2,  2,3,4);
    cara_en(3,  3,0,4);
    cara_en(4,  3,0,2);
    cara_en(5,  2,1,0);

    inicializar_colores();
}

_cubo::_cubo(float tam)
{
   vertices.resize(8);

   vertice_en(0,  tam,     0,  tam);
   vertice_en(1,  tam, 2*tam,  tam);
   vertice_en(2, -tam, 2*tam,  tam);
   vertice_en(3, -tam,     0,  tam);

   vertice_en(4,  tam,     0, -tam);
   vertice_en(5,  tam, 2*tam, -tam);
   vertice_en(6, -tam, 2*tam, -tam);
   vertice_en(7, -tam,     0, -tam);

   caras.resize(12);

   // Frontal
   cara_en(0,  0,2,3);
   cara_en(1,  0,1,2);

   // Derecha
   cara_en(2,  0,4,1);
   cara_en(3,  4,5,1);

   // Trasera
   cara_en(4,  7,5,4);
   cara_en(5,  6,5,7);

   // Izquierda
   cara_en(6,  3,6,7);
   cara_en(7,  3,2,6);

   // Superior
   cara_en(8,  2,1,6);
   cara_en(9,  1,5,6);

   // Inferior
   cara_en(10, 3,7,4);
   cara_en(11, 0,3,4);

   inicializar_colores();





}

// Modificación: Cubo con desplazamiento
_cubo::_cubo(float tam, int desp_x, int desp_y, int desp_z)
{

    vertices.resize(8);

    vertice_en(0,  tam + desp_x,     0 + desp_y,  tam + desp_z);
    vertice_en(1,  tam + desp_x, 2*tam + desp_y,  tam + desp_z);
    vertice_en(2, -tam + desp_x, 2*tam + desp_y,  tam + desp_z);
    vertice_en(3, -tam + desp_x,     0 + desp_y,  tam + desp_z);

    vertice_en(4,  tam + desp_x,     0 + desp_y, -tam + desp_z);
    vertice_en(5,  tam + desp_x, 2*tam + desp_y, -tam + desp_z);
    vertice_en(6, -tam + desp_x, 2*tam + desp_y, -tam + desp_z);
    vertice_en(7, -tam + desp_x,     0 + desp_y, -tam + desp_z);

    caras.resize(12);

    // Frontal
    cara_en(0,  0,2,3);
    cara_en(1,  0,1,2);

    // Derecha
    cara_en(2,  0,4,1);
    cara_en(3,  4,5,1);

    // Trasera
    cara_en(4,  7,5,4);
    cara_en(5,  6,5,7);

    // Izquierda
    cara_en(6,  3,6,7);
    cara_en(7,  3,2,6);

    // Superior
    cara_en(8,  2,1,6);
    cara_en(9,  1,5,6);

    // Inferior
    cara_en(10, 3,7,4);
    cara_en(11, 0,3,4);

    inicializar_colores();



}
