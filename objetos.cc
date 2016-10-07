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





}
