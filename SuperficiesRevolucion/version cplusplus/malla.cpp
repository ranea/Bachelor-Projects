#include "malla.hpp"
#include <assert.h>
#include <cmath>
#include <iostream>
#include <cstdlib>

MallaTVT::MallaTVT(std::vector<float> vertices_ply, std::vector<int> caras_ply )
{
   pintar_modo_ajedrez = false;
   pintar_normal_caras = false;
   pintar_normal_vertices = false;
   modo = GL_POINT;
   modo_visualizacion = PUNTO;
   color_principal = Tupla3f(0,0,0);               // negro
   color_alternativo = Tupla3f(0.5,0.5,0.5);       // gris
   color_normal_tri = Tupla3f(0.75,0,0.75);        // magenta
   color_normal_ver = Tupla3f(0.75,0.75,0);        // amarillo

   ver = std::vector<Tupla3f>(vertices_ply.size()/3);
   tri = std::vector<Tupla3i>(caras_ply.size()/3);

   for (unsigned int i = 0; i < num_ver(); ++i) {
      ver[i] = Tupla3f(
            vertices_ply[3*i],
            vertices_ply[3*i+1],
            vertices_ply[3*i+2]
      );
   }

   for (unsigned int i = 0; i < num_tri(); ++i) {
      tri[i] = Tupla3i(
            caras_ply[3*i],
            caras_ply[3*i+1],
            caras_ply[3*i+2]
      );
   }

   creaTriangulosParesImpares();
   creaNormales();
   creaColoresSegunNormales();
}

unsigned int MallaTVT::num_ver(){
   return ver.size();
}

unsigned int MallaTVT::num_tri(){
   return tri.size();
}

unsigned int MallaTVT::num_tri_pares(){
   return num_tri()/2;
}

unsigned int MallaTVT::num_tri_impares(){
   return num_tri() - num_tri_pares();
}

GLenum MallaTVT::getModo(){
   return modo;
}

bool MallaTVT::getAjedrez(){
   return pintar_modo_ajedrez;
}

void MallaTVT::CambiarVisualizacion(ModoVisualizacion nuevo_modo_visualizacion)
{
   modo_visualizacion = nuevo_modo_visualizacion;
}

void MallaTVT::CambiarModo(GLenum nuevo_modo){
   modo = nuevo_modo;
}

void MallaTVT::setModoAjedrez(bool pintar_modo_ajedrez){
   this->pintar_modo_ajedrez = pintar_modo_ajedrez;
}

void MallaTVT::setVisualizarNormalCaras(bool pintar_normal_caras){
   this->pintar_normal_caras = pintar_normal_caras;
}

void MallaTVT::setVisualizarNormalVertices(bool pintar_normal_vertices){
   this->pintar_normal_vertices = pintar_normal_vertices;
}

void MallaTVT::creaTriangulosParesImpares()
{
   tri_impares_pares = std::vector<Tupla3i>(num_tri());

   unsigned int i,j;
   j = 0;

   // triangulos impares
   for (i=0; i < num_tri(); i+=2){
      tri_impares_pares[j] = tri[i];
      j++;
   }

   // triangulos pares
   for (i=1; i < num_tri(); i+=2){
      tri_impares_pares[j] = tri[i];
      j++;
   }
}

void MallaTVT::creaNormales(){
   nor_tri = std::vector<Tupla3f>(num_tri());

   /* Dado un triangulo de vertices A,B,C
    * definimos la normal del triangulo como AB*BC
    * donde AB,BC son los correspondientes vectores
    */
   for (unsigned int i = 0; i < num_tri(); ++i) {
      Tupla3f A = ver[tri[i][0]];
      Tupla3f B = ver[tri[i][1]];
      Tupla3f C = ver[tri[i][2]];

      nor_tri[i] = (B-A)*(C-B);
      nor_tri[i] = nor_tri[i].normalized();
   }

   nor_ver = std::vector<Tupla3f>(num_ver(),Tupla3f(0,0,0));

   /*
    * El vector normal a un vertice es el promedio normalizado
    * de los vectores normales de las caras que comparten
    * dicho vertice
    */
   for (unsigned int i = 0; i < num_tri(); ++i) {
      nor_ver[tri[i][0]] = nor_ver[tri[i][0]] + nor_tri[i];
      nor_ver[tri[i][1]] = nor_ver[tri[i][1]] + nor_tri[i];
      nor_ver[tri[i][2]] = nor_ver[tri[i][2]] + nor_tri[i];
   }
   for (unsigned int j = 0; j < num_ver(); ++j) {
      nor_ver[j] = nor_ver[j].normalized();
   }
}

void MallaTVT::creaColoresSegunNormales(){
   col_ver = std::vector<Tupla3f>(num_ver());
   for (unsigned int i = 0; i < col_ver.size(); ++i){
      col_ver[i] = nor_ver[i].abs();
   }

   col_tri = std::vector<Tupla3f>(num_tri());
   for (unsigned int i = 0; i < col_tri.size(); ++i){
      col_tri[i] = nor_tri[i].abs();
   }
}

void MallaTVT::Revoluciona(unsigned int N)
{
   // Vemos si estan los vertices con coordenada X=0
   if(ver[num_ver()-1][0] != 0)
         ver.insert(ver.end(),Tupla3f(0,ver[num_ver()-1][1],ver[num_ver()-1][2]));
   if(ver[0][0] != 0)
      ver.insert(ver.begin(),Tupla3f(0,ver[0][1],ver[0][2]));

   // Creamos los vertices (sin repetir los vertices con X=0)
   std::vector<Tupla3f> copia_perfil(ver.begin()+1,ver.end()-1);
   unsigned int num_ver_copia_perfil = num_ver()-2;
   float angulo = 2*M_PI/(N);
   Matriz4x4f rotY = Matriz4x4f::RotacionEjeY(angulo);

   for (unsigned int perfil_i = 1; perfil_i < N; ++perfil_i) {    // perfil_N = perfil_0
      for (unsigned int j = 0; j < num_ver_copia_perfil; ++j) {
         Tupla4f c_p4f = Tupla4f(copia_perfil[j]);
         copia_perfil[j] = Tupla3f(rotY*c_p4f);
      }

      ver.insert(ver.end(), copia_perfil.begin(), copia_perfil.end());
   }

   // Creamos los caras longitudinales (hay tantas como perfiles)
   for (unsigned int perfil_i = 0; perfil_i < N; ++perfil_i)
   {
      // Si hay k-vertices en un perfil (sin considerar los de X=0)
      // formaran k-1 caras con los del perfil siguiente
      for (unsigned int j = 0; j < num_ver_copia_perfil-1; ++j)
      {
         unsigned int primer_ver_perfil_i;
         unsigned int primer_ver_sig_perfil;

         /*
          * Si estoy en el perfil1, solo tengo que saltarme un vertice
          * (el primero con X = 0)
          * Si estoy en otro perfil, tengo que saltarme dos vertices
          * (el primer y el ultimo del perfil original con X=0)
          */
         if(perfil_i==0)
            primer_ver_perfil_i = 1;
         else
            primer_ver_perfil_i = 2 + num_ver_copia_perfil * perfil_i;
         if(perfil_i==N-1)
            primer_ver_sig_perfil = 1;    // el N-perfil es el primer perfil
         else
            primer_ver_sig_perfil = 2 + num_ver_copia_perfil * (perfil_i+1);

         // Formo el triangulo con dos vertices en el perfil_i y uno en el perfil_i+1
         tri.push_back(Tupla3i(
               primer_ver_perfil_i    + j,
               primer_ver_sig_perfil  + j,
               primer_ver_perfil_i    + j+1

         ));

         // Formo el triangulo con dos vertices en el perfil_i+1 y uno en el perfil_i
         tri.push_back(Tupla3i(
               primer_ver_perfil_i    + j+1,
               primer_ver_sig_perfil  + j,
               primer_ver_sig_perfil  + j+1
         ));
      }
   }

   /*
   // Creamos la tapa inferior del solido (lo recorro igual que el anterior)
   for (unsigned int perfil_i = 0; perfil_i < N; ++perfil_i)
   {
      unsigned int primer_ver_perfil_i;
      unsigned int primer_ver_sig_perfil;

      if(perfil_i==0)
         primer_ver_perfil_i = 1;
      else
         primer_ver_perfil_i = 2 + num_ver_copia_perfil * perfil_i;
      if(perfil_i==N-1)
         primer_ver_sig_perfil = 1;
      else
         primer_ver_sig_perfil = 2 + num_ver_copia_perfil * (perfil_i+1);

      tri.push_back(Tupla3i(
            primer_ver_perfil_i    + 0,
            0,                            // primer vertice del perfil original con X=0
            primer_ver_sig_perfil  + 0
      ));
   }

   // Creamos la tapa superior del solido (lo recorro igual que el anterior)
   for (unsigned int perfil_i = 0; perfil_i < N; ++perfil_i)
   {
      unsigned int primer_ver_perfil_i;
      unsigned int primer_ver_sig_perfil;

      if(perfil_i==0)
         primer_ver_perfil_i = 1;
      else
         primer_ver_perfil_i = 2 + num_ver_copia_perfil * perfil_i;
      if(perfil_i==N-1)
         primer_ver_sig_perfil = 1;    // el N-perfil es el primer perfil
      else
         primer_ver_sig_perfil = 2 + num_ver_copia_perfil * (perfil_i+1);

      /*
       * Si num_copia_perfil = k, tenemos
       *    perfil1 = [x,copia_perfil_1,...,copia_perfil_k,x']
       *    perfil2 = [copia_perfil_1,...,copia_perfil_k]
       *//*
      tri.push_back(Tupla3i(
            primer_ver_perfil_i     + num_ver_copia_perfil-1,
            primer_ver_sig_perfil   + num_ver_copia_perfil-1,
            num_ver_copia_perfil + 1     // ultimo vertice del perfil original con X=0

      ));
   }*/

   // Actualizamos la malla
   creaTriangulosParesImpares();
   creaNormales();
   creaColoresSegunNormales();
}

void MallaTVT::Barrido(unsigned int N)
{
    /*
     * Suponemos que el perfil inicial esta en el plano Y
     */

    /*
     * Vemos si el primer vertice tiene coordenada X=0,Z=0,
     * si no, lo añadimos (para poder crear la tapa inferior)
     */
    if(ver[0][0] != 0 || ver[0][2] != 0)
      ver.insert(ver.begin(),Tupla3f(0,ver[0][1],0));

    // Creamos copias del perfil (sin tomar el primer vertice)
    std::vector<Tupla3f> copia_perfil(ver.begin()+1,ver.end());
    unsigned int num_ver_copia_perfil = num_ver()-1;

    float dy = 0.1;
    Matriz4x4f trasY = Matriz4x4f::Traslacion(0,dy,0);

    for (unsigned int perfil_i = 1; perfil_i < N; ++perfil_i) {
       for (unsigned int j = 0; j < num_ver_copia_perfil; ++j) {
          Tupla4f c_p4f = Tupla4f(copia_perfil[j]);
          copia_perfil[j] = Tupla3f(trasY*c_p4f);
       }

       ver.insert(ver.end(), copia_perfil.begin(), copia_perfil.end());
    }

    // Añadimos al final un vertice para crear la tapa superior
    ver.insert(ver.end(),Tupla3f(0,ver[ver.size()-1][1],0));

    // Creamos los caras longitudinales (hay una menos que perfiles)
    for (unsigned int perfil_i = 0; perfil_i < N-1; ++perfil_i)
    {
       // Si hay k-vertices en un perfil (sin considerar el de Y=0)
       // formaran k-1 caras con los del perfil siguiente
       for (unsigned int j = 0; j < num_ver_copia_perfil; ++j)
       {
          unsigned int primer_ver_perfil_i;
          unsigned int primer_ver_sig_perfil;

          primer_ver_perfil_i = 1 + num_ver_copia_perfil * perfil_i;
          primer_ver_sig_perfil = primer_ver_perfil_i + num_ver_copia_perfil;

          /*
           * Tengo que tener cuidado si estamos en el ultimo vertice de perfil
           * (tiene que engancharse con el primer vertice)
           */

          // Formo el triangulo con dos vertices en el perfil_i y uno en el perfil_i+1
          tri.push_back(Tupla3i(
                primer_ver_perfil_i    + j,
                primer_ver_perfil_i    + (j+1)%num_ver_copia_perfil,
                primer_ver_sig_perfil  + j

          ));

          // Formo el triangulo con dos vertices en el perfil_i+1 y uno en el perfil_i
          tri.push_back(Tupla3i(
                primer_ver_perfil_i    + (j+1)%num_ver_copia_perfil,
                primer_ver_sig_perfil  + (j+1)%num_ver_copia_perfil,
                primer_ver_sig_perfil  + j
          ));
       }
    }

    /*
     * Creamos la tapa inferior del solido
     * (empezamos desde el j=1, porque el j=0 es el
     * vertice que tiene la Y=0 )
     */
    for (unsigned int j = 1; j < num_ver_copia_perfil+1; ++j)
    {
       /*
        * Cuando lleguemos al ultimo vertice, no tenemos que ir al vertice_0.
        * (ya que este es el que tiene Y=0). Tenemos que irnos al vertice_1
        */

       unsigned int k;
       if( j+1 == num_ver_copia_perfil+1) k = 1;
       else                               k = j+1;

       tri.push_back(Tupla3i(
             j,
             0,                           // primer vertice del perfil original con Y=0
             k
       ));
    }

    // Creamos la tapa superior del solido
    for (unsigned int j = 0; j < num_ver_copia_perfil; ++j)
    {
       unsigned int k;
       if( j+1 == num_ver_copia_perfil)   k = 0;
       else                               k = j+1;

       unsigned primer_ver_perfil_i = 1 + num_ver_copia_perfil*(N-1);

       tri.push_back(Tupla3i(
             primer_ver_perfil_i + j,
             primer_ver_perfil_i + k,
             ver.size()-1                // ultimo vertice del ultimo perfil con Y=0
       ));
    }

    // Actualizamos la malla
    creaTriangulosParesImpares();
    creaNormales();
    creaColoresSegunNormales();
}

float MallaTVT::dimension(){
   /*
    * Para calcular la dimension del menor cubo que encierra el objeto,
    * calculamos para cada coordenada el mayor y el menor valor,
    * y hacemos la resta.
    */
   double valores_maximos_componentes[3] = {ver[0][0],ver[0][1],ver[0][2]};
   double valores_minimos_componentes[3] = {ver[0][0],ver[0][1],ver[0][2]};

   for (unsigned int iv = 1; iv < num_ver(); ++iv)
   {
      for (int c = 0; c < 3; ++c)  {
         if(ver[iv][c] > valores_maximos_componentes[c])
            valores_maximos_componentes[c] = ver[iv][c];
         else if(ver[iv][c] < valores_minimos_componentes[c])
            valores_minimos_componentes[c] = ver[iv][c];
      }
   }

   double dimension[3];
   for (int c = 0; c < 3; ++c)
      dimension[c] = valores_maximos_componentes[c] - valores_minimos_componentes[c];

   return std::max(dimension[0],std::max(dimension[1],dimension[2]));
}


/*
 * Apartado de visualizacion de la malla
 */

void MallaTVT::Visualizar()
{
   switch (modo_visualizacion) {
      case PUNTO:
         CambiarModo(GL_POINT);
         VisualizarVertices();
         break;
      case ALAMBRE:
         CambiarModo(GL_LINE);
         Visualizar_VA();
         break;
      case SOLIDO:
         CambiarModo(GL_FILL);
         Visualizar_VA();
         break;
      case AJEDREZ:
         setModoAjedrez(true);
         CambiarModo(GL_FILL);
         Visualizar_VA();
         setModoAjedrez(false);
         break;
      case ATRIBUTO_CARAS:
         CambiarModo(GL_FILL);
         Visualizar_BE_AT();
         break;
      case ATRIBUTO_VERTICES:
         CambiarModo(GL_FILL);
         Visualizar_VA_AV();
         break;
      default:
         break;
   }

   if(pintar_normal_caras){
      VisualizarNormalesCaras();
   }
   if(pintar_normal_vertices){
      VisualizarNormalesVertices();
   }

}

void MallaTVT::VisualizarVertices()
{
   glColor3fv(color_principal.getPuntero());

   glEnableClientState( GL_VERTEX_ARRAY );
   glVertexPointer(3, GL_FLOAT, 0, ver[0].getPuntero());
   glDrawArrays( GL_POINTS, 0, num_ver() );

   /*glBegin(GL_POINTS);
   for (unsigned i = 0; i < num_ver(); i++){
      glVertex3fv( ver[i].getPuntero() );
   }
   glEnd();*/
}

void MallaTVT::VisualizarNormalesVertices(){
   glColor3fv(color_normal_ver.getPuntero());

   glBegin( GL_LINES );
   for (unsigned i = 0; i < num_ver(); i++){
      glVertex3fv(ver[i].getPuntero());
      glVertex3fv((ver[i]+(nor_ver[i])*dimension()*0.10).getPuntero());
   }
   glEnd();
}

void MallaTVT::VisualizarNormalesCaras(){
   glColor3fv(color_normal_tri.getPuntero());

   glBegin( GL_LINES );
   for (unsigned i = 0; i < num_tri(); i++)
   {
      // Vertices de la cara-i
      Tupla3f A = ver[tri[i][0]];
      Tupla3f B = ver[tri[i][1]];
      Tupla3f C = ver[tri[i][2]];

      Tupla3f baricentro = Tupla3f(
            (A[0]+B[0]+C[0])/3,
            (A[1]+B[1]+C[1])/3,
            (A[2]+B[2]+C[2])/3
      );

      glVertex3fv(baricentro.getPuntero());
      glVertex3fv((baricentro+(nor_tri[i])*dimension()*0.10).getPuntero());
   }
   glEnd();
}

void MallaTVT::Visualizar_BE()
{
   glColor3fv(color_principal.getPuntero());
   glPolygonMode(GL_FRONT_AND_BACK,modo);

   glBegin( GL_TRIANGLES );
   for (unsigned i = 0; i < num_tri(); i++){
      if(pintar_modo_ajedrez){
         if(i%2==0)
            glColor3fv(color_principal.getPuntero());
         else
            glColor3fv(color_alternativo.getPuntero());
      }

      for (int j = 0; j < 3; ++j) {
         unsigned int iv = tri[i][j]; // iv = índice de vértice
         glVertex3fv(ver[iv].getPuntero());
      }
   }
   glEnd();
}

void MallaTVT::Visualizar_BE_AT()
{
   glColor3fv(color_principal.getPuntero());
   glPolygonMode(GL_FRONT_AND_BACK,modo);

   glBegin( GL_TRIANGLES );
   for (unsigned i = 0; i < num_tri(); i++){
      if(!col_tri.empty())
         glColor3fv( col_tri[i].getPuntero() );
      if(!nor_tri.empty())
         glNormal3fv( nor_tri[i].getPuntero() );

      for (int j = 0; j < 3; ++j) {
         unsigned int iv = tri[i][j]; // iv = índice de vértice
         glVertex3fv(ver[iv].getPuntero());
      }
   }
   glEnd();
}

void MallaTVT::Visualizar_BE_AV()
{
   glColor3fv(color_principal.getPuntero());
   glPolygonMode(GL_FRONT_AND_BACK,modo);

   glBegin( GL_TRIANGLES );
   for (unsigned i = 0; i < num_tri(); i++){
      for (int j = 0; j < 3; ++j) {
         unsigned int iv = tri[i][j]; // iv = índice de vértice

         if(!col_ver.empty())
            glColor3fv( col_ver[iv].getPuntero() );
         if(!nor_ver.empty())
            glNormal3fv( nor_ver[iv].getPuntero() );

         glVertex3fv(ver[iv].getPuntero());
      }
   }
   glEnd();
}

void MallaTVT::Visualizar_VA()
{
   glPolygonMode(GL_FRONT_AND_BACK,modo);
   glColor3fv(color_principal.getPuntero());

   glEnableClientState( GL_VERTEX_ARRAY );
   glVertexPointer(3, GL_FLOAT, 0, ver[0].getPuntero());

   if(pintar_modo_ajedrez){
      glDrawElements(GL_TRIANGLES, 3*num_tri_impares(), GL_UNSIGNED_INT, tri_impares_pares[0].getPuntero());

      glColor3fv(color_alternativo.getPuntero());
      glDrawElements(GL_TRIANGLES, 3*num_tri_pares(), GL_UNSIGNED_INT,tri_impares_pares[num_tri_impares()].getPuntero());
   }
   else{
      glDrawElements(GL_TRIANGLES, 3*num_tri(), GL_UNSIGNED_INT, tri[0].getPuntero());
   }

   glDisableClientState( GL_VERTEX_ARRAY );
}

void MallaTVT::Visualizar_VA_AV()
{
   glColor3fv(color_principal.getPuntero());
   glPolygonMode(GL_FRONT_AND_BACK,modo);

   if ( !nor_ver.empty() ) {
      glEnableClientState( GL_NORMAL_ARRAY );
      glNormalPointer( GL_FLOAT, 0, nor_ver[0].getPuntero());
   }
   if ( !col_ver.empty() ) {
      glEnableClientState( GL_COLOR_ARRAY );
      glColorPointer( 3, GL_FLOAT, 0, col_ver[0].getPuntero());
   }

   glEnableClientState( GL_VERTEX_ARRAY );
   glVertexPointer(3, GL_FLOAT, 0, ver[0].getPuntero() );
   glDrawElements(GL_TRIANGLES, 3*num_tri(), GL_UNSIGNED_INT, tri[0].getPuntero());

   glDisableClientState( GL_VERTEX_ARRAY );
   glDisableClientState( GL_NORMAL_ARRAY );
   glDisableClientState( GL_COLOR_ARRAY );
}