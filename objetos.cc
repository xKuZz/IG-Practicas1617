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
        glColor3f(color[i].x, color[i].y, color[i].z);
        glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
    }

    glEnd();

}

void _triangulos3D::inicializar_colores()
{
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

_objeto_ply::_objeto_ply()
{

}

void _objeto_ply::parametros(char *archivo)
{
    _file_ply p;
    vector<float> ver_ply;
    vector<int>   car_ply;

    p.open(archivo);          // Abrimos el archivo con el lector proporcionado
    p.read(ver_ply, car_ply); // Al leerlo obtenemos un vector con puntos de vértices y otra con números para las caras

    for (auto i = 0u; i < ver_ply.size(); i+=3) // Cada 3 puntos forman un vértice que creamos y añadimos al vector de vértices
        vertices.emplace_back(ver_ply[i], ver_ply[i+1], ver_ply[i+2]);

    for (auto i = 0u; i < car_ply.size(); i+=3) // Cada 3 números se forma una cara que añadios al vector de caras
        caras.emplace_back(car_ply[i], car_ply[i+1], car_ply[i+2]);

    p.close();
    inicializar_colores();
}
_rotacion::_rotacion()
{

}

void _rotacion::parametros(const vector<_vertex3f>& perfil1, unsigned num1)
{

    perfil = perfil1;
    n_rotaciones = num1;

   // TRATAMIENTO DE LOS VÉRTICES (Aplicamos la cuenta de la matriz para la rotación sobre el eje Y)
   for (auto i = 0u; i < n_rotaciones; ++i)
       for (auto& vertex: perfil)
           vertices.emplace_back(vertex.x*cos(2.0*M_PI*i/ (1.0*n_rotaciones) )+
                                 vertex.z*sin(2.0*M_PI*i/ (1.0*n_rotaciones) ),

                                 vertex.y,

                                 vertex.x*sin(2.0*M_PI*i/ (1.0*n_rotaciones) ) +
                                 vertex.z*cos(2.0*M_PI*i/ (1.0*n_rotaciones) ) );

// TRATAMIENTO DE LAS CARAS

   // Lambdas auxiliares (pa que se entienda mejor)
   // Devuelve el vértice anterior
    auto anterior = [](int actual) {
       return actual - 1;
    };
   // Devuelve la posición en el vector de vértices de el vértice actual en el siguiente perfil
    auto sig_perfil = [this] (int actual) {
       return actual + perfil.size();
    };


    for (auto n_perfil = 0u; n_perfil < n_rotaciones -1; ++n_perfil)
        for (auto n_vertice = 1u; n_vertice < perfil.size(); ++n_vertice) {
            auto   actual       = n_perfil*perfil.size() + n_vertice;
            caras.emplace_back(actual, anterior(actual), sig_perfil(anterior(actual)));
            caras.emplace_back(actual, sig_perfil(anterior(actual)), sig_perfil(actual));
        }

    for (auto n_vertice = 1u; n_vertice < perfil.size(); ++ n_vertice) {
        auto actual = (n_rotaciones-1)*perfil.size() + n_vertice;
        auto sig_perfil = n_vertice;

        caras.emplace_back(actual, anterior(actual), anterior(sig_perfil));
        caras.emplace_back(actual, anterior(sig_perfil), sig_perfil);
    }

    // Proyectar sobre el eje Y supone dejar a 0 X, Z
    auto proyeccion_y = [](const _vertex3f& v) {
        return _vertex3f(0, v.y, 0);
    };

    // TAPA INFERIOR
        vertices.emplace_back(proyeccion_y(vertices.front()));

    for (auto n_perfil = 0u; n_perfil < n_rotaciones - 1; ++n_perfil) {
        auto centro_tapa = vertices.size()-1;
        auto actual      = n_perfil * perfil.size();
        caras.emplace_back(centro_tapa, sig_perfil(actual), actual);
    }

    // El último triángulo a mano
    caras.emplace_back(vertices.size()-1, 0, (n_rotaciones-1)* perfil.size());


// TAPA SUPERIOR
    vertices.emplace_back(proyeccion_y( vertices[ perfil.size() - 1 ]) );

    for (auto n_perfil = 0u; n_perfil < n_rotaciones - 1; ++ n_perfil) {
        auto centro_tapa = vertices.size()-1;
        auto actual      = n_perfil * perfil.size() + (perfil.size()-1);
        caras.emplace_back(centro_tapa, actual, sig_perfil(actual));
    }

    caras.emplace_back(vertices.size()-1, perfil.size()-1, n_rotaciones* perfil.size() - 1);
    inicializar_colores();
}
