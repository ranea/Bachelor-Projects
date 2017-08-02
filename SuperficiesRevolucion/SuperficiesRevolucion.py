#!/usr/bin/env python

# Superficies de revolucion

import OpenGL
OpenGL.ERROR_ON_COPY = True
from OpenGL.GL import *
from OpenGL.GLU import gluOrtho2D
from OpenGL.GLUT import *
import sys, time
from sympy.core.sympify import sympify
from sympy import *
from OpenGL.constants import GLfloat
from OpenGL.GL.ARB.multisample import GL_MULTISAMPLE_ARB
import math
vec4 = GLfloat_4

tStart = t0 = time.time()
frames = 0
vertices = []
triangulos = []
normales_vertices = []
normales_triangulos = []
colores_vertices = []
colores_triangulos = []

camara_angulo_x = +10
camara_angulo_y = -45

ventana_pos_x  = 50
ventana_pos_y  = 50
ventana_tam_x  = 1024
ventana_tam_y  = 800

frustum_factor_escala = 1.0
frustum_dis_del = 0.1
frustum_dis_tra = 10.0
frustum_ancho = 0.5 * frustum_dis_del

frustum_factor_escala = 1.0

modoPunto = False
modoAlambre = False
modoSolido = False
modoSolidoColoreado = True
modoNormalesVertices = False

strings_ayuda = ["Teclas:"," 1 - Modo puntos"," 2 - Modo alambre",
    " 3 - Modo solido"," 4 - Modo solido coloreado"," 5 - Activar/Desactivar normales"]



def fijarProyeccion():
    ratioYX = float(ventana_tam_y) / float(ventana_tam_x)

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()

    glFrustum(-frustum_ancho, +frustum_ancho, -frustum_ancho*ratioYX, +frustum_ancho*ratioYX, +frustum_dis_del, +frustum_dis_tra)

    glTranslatef( 0.0,0.0,-0.5*(frustum_dis_del+frustum_dis_tra))

    glScalef( frustum_factor_escala, frustum_factor_escala,  frustum_factor_escala )

def fijarViewportProyeccion():
    glViewport( 0, 0, ventana_tam_x, ventana_tam_y )
    fijarProyeccion()

def fijarCamara():

    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

    glRotatef(camara_angulo_x,1,0,0)
    glRotatef(camara_angulo_y,0,1,0)

def dibujarEjes():

    long_ejes = 30.0

    # establecer modo de dibujo a lineas (podría estar en puntos)
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    # Ancho de línea
    glLineWidth( 1.5 );
    # dibujar tres segmentos
    glBegin(GL_LINES)

    # eje X, color rojo
    glColor3f( 1.0, 0.0, 0.0 )
    glVertex3f( -long_ejes, 0.0, 0.0 )
    glVertex3f( +long_ejes, 0.0, 0.0 )
    # eje Y, color verde
    glColor3f( 0.0, 1.0, 0.0 )
    glVertex3f( 0.0, -long_ejes, 0.0 )
    glVertex3f( 0.0, +long_ejes, 0.0 )
    # eje Z, color azul
    glColor3f( 0.0, 0.0, 1.0 )
    glVertex3f( 0.0, 0.0, -long_ejes )
    glVertex3f( 0.0, 0.0, +long_ejes )

    glEnd()

def dibujarObjetos():
    if modoPunto == True:
        glColor3f(0.0,0.0,0.0)
        
        glBegin(GL_POINTS)
        for v in vertices:
            glVertex3f(v[0],v[1],v[2])
        glEnd()
    elif modoAlambre == True:
        glColor3f(0.0,0.0,0.0)
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE)
        glBegin( GL_TRIANGLES )
        for tri in triangulos:
            for j in range(3):
                v = vertices[tri[j]]
                glVertex3f(v[0],v[1],v[2])
        glEnd()
    elif modoSolido == True:
        glColor3f(0.5,0.5,0.5)
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL)
        glBegin( GL_TRIANGLES )
        for tri in triangulos:
            for j in range(3):
                v = vertices[tri[j]]
                glVertex3f(v[0],v[1],v[2])
        glEnd()
    elif modoSolidoColoreado == True:
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL)
        glBegin( GL_TRIANGLES )
        for tri in triangulos:
            for j in range(3):
                v = vertices[tri[j]]

                c1 = colores_vertices[tri[j]][0]
                c2 = colores_vertices[tri[j]][1]
                c3 = colores_vertices[tri[j]][2]
                glColor3f(c1,c2,c3)

                glVertex3f(v[0],v[1],v[2])
        glEnd()
    '''
    elif modoSolidoColoreadoCaras == True:
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL)
        glBegin( GL_TRIANGLES )
        i = 0
        for tri in triangulos:
            c1 = colores_triangulos[i][0]
            c2 = colores_triangulos[i][1]
            c3 = colores_triangulos[i][2]
            glColor3f(c1,c2,c3)
            i+=1
            for j in range(3):
                v = vertices[tri[j]]
                glVertex3f(v[0],v[1],v[2])
        glEnd()
    '''

    if modoNormalesVertices == True:
        glColor3f(0.0,0.0,0.0)
        glBegin( GL_LINES )
        for i in range(len(vertices)):
            v = vertices[i]
            n = normales_vertices[i]

            glVertex3f(v[0],v[1],v[2])
            glVertex3f(v[0]+n[0]*0.25,v[1]+n[1]*0.25,v[2]+n[2]*0.25)

        glEnd()
        

def ayuda():
    glMatrixMode(GL_PROJECTION)
    glPushMatrix()
    glLoadIdentity()
    gluOrtho2D(0.0, ventana_tam_x, 0.0, ventana_tam_y)
    glMatrixMode(GL_MODELVIEW)
    glPushMatrix()
    glLoadIdentity()
    glColor3f(1.0, 0.0, 0.0)

    num_lineas = 0
    for s in strings_ayuda:
        glWindowPos2i(10, ventana_tam_y - 15*(num_lineas + 1))
        for c in s:
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ord(c));
        num_lineas += 1

    glMatrixMode(GL_MODELVIEW)
    glPopMatrix()
    glMatrixMode(GL_PROJECTION)
    glPopMatrix()


# Función de dibujado
def dibujar():
    rotationRate = (time.time() - tStart) * 1.05
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

    fijarViewportProyeccion()
    fijarCamara()

    dibujarEjes()

    dibujarObjetos()

    ayuda()

    glutSwapBuffers()

def resetearEstados():
    global modoPunto,modoAlambre,modoSolido,modoSolidoColoreado

    modoPunto = False
    modoAlambre = False
    modoSolido = False
    modoSolidoColoreado = False

# Teclas normales: para cambiar escala y velocidad
def teclaNormal(k, x, y):
    global frustum_factor_escala, vertice_actual, velocidad, camara_angulo_x, camara_angulo_y, dibujoEvoluta
    global modoPunto,modoAlambre,modoSolido,modoSolidoColoreado,modoSolidoColoreado,modoNormalesVertices

    if k == b'+':
        frustum_factor_escala *= 1.05
    elif k == b'-':
        frustum_factor_escala /= 1.05
    elif k == b'1':
        resetearEstados()
        modoPunto = True
    elif k == b'2':
        resetearEstados()
        modoAlambre = True
    elif k == b'3':
        resetearEstados()
        modoSolido = True
    elif k == b'4':
        resetearEstados()
        modoSolidoColoreado = True
    elif k == b'5':
        modoNormalesVertices = not modoNormalesVertices
    elif k == b'r':
        camara_angulo_x = camara_angulo_y = 0.0
    elif k == b'q' or k == b'Q' or ord(k) == 27: # Escape
        sys.exit(0)
    else:
        return
    glutPostRedisplay()

# Teclas especiales: para cambiar la cámara
def teclaEspecial(k, x, y):
    global camara_angulo_x, camara_angulo_y

    if k == GLUT_KEY_UP:
        camara_angulo_x += 5.0
    elif k == GLUT_KEY_DOWN:
        camara_angulo_x -= 5.0
    elif k == GLUT_KEY_LEFT:
        camara_angulo_y += 5.0
    elif k == GLUT_KEY_RIGHT:
        camara_angulo_y -= 5.0
    else:
        return
    glutPostRedisplay()

# Nuevo tamaño de ventana
def cambioTamanio(width, height):
    global ventana_tam_x,ventana_tam_y

    ventana_tam_x = width
    ventana_tam_y = height

    fijarViewportProyeccion()
    glutPostRedisplay()

origen = [-1,-1]
def pulsarRaton(boton,estado,x,y):
    da = 5.0
    redisp = False
    global frustum_factor_escala,origen,camara_angulo_x,camara_angulo_y

    if boton == GLUT_LEFT_BUTTON:
        if estado == GLUT_UP:
            origen = [-1,-1]
        else:
            origen = [x,y]
    elif boton == 3: # Rueda arriba aumenta el zoom
        frustum_factor_escala *= 1.05;
        redisp = True
    elif boton == 4: # Rueda abajo disminuye el zoom
        frustum_factor_escala /= 1.05;
        redisp = True
    elif boton == 5: # Llevar la rueda a la izquierda gira la cámara a la izquierda
        camara_angulo_y -= da
        redisp = True
    elif boton == 6: # Llevar la rueda a la derecha gira la cámara a la derecha
        camara_angulo_y += da
        redisp = True

    if redisp:
        glutPostRedisplay();

def moverRaton(x,y):
    global camara_angulo_x,camara_angulo_y, origen

    if origen[0] >= 0 and origen[1] >= 0:
        camara_angulo_x += (y - origen[1])*0.25;
        camara_angulo_y += (x - origen[0])*0.25;

        origen[0] = x;
        origen[1] = y;

        # Redibujar
        glutPostRedisplay();

def rotacionEjeY(v,angulo):
    c = math.cos(angulo)
    s = math.sin(angulo)

    x = v[0]
    y = v[1]
    z = v[2] 

    vertice_rotado = [c*x+s*z,y,c*z-s*x]

    return vertice_rotado

def sumaVectores(v1,v2):
    vector_suma = [v1[0]+v2[0],v1[1]+v2[1],v1[2]+v2[2]]

    return vector_suma

def restaVectores(v1,v2):
    vector_resta = [v1[0]-v2[0],v1[1]-v2[1],v1[2]-v2[2]]

    return vector_resta

def productoEscalar(v1,v2):
    x1 = v1[0]
    y1 = v1[1]
    z1 = v1[2]
    x2 = v2[0]
    y2 = v2[1]
    z2 = v2[2]

    producto_escalar = x1*x2 + y1*y2 + z1*z2

    return producto_escalar


def vectorNormalizado(v):
    longitud = v[0]**2 + v[1]**2 + v[2]**2
    norma = math.sqrt(longitud)

    vector_normalizado = [v[0]/norma,v[1]/norma,v[2]/norma]

    return vector_normalizado


def productoVectorial(v1,v2):
    x1 = v1[0]
    y1 = v1[1]
    z1 = v1[2]
    x2 = v2[0]
    y2 = v2[1]
    z2 = v2[2]

    vector_producto_vectorial = [y1*z2 - z1*y2,z1*x2 - x1*z2,x1*y2 - y1*x2]

    return vector_producto_vectorial

def creaNormales():
    for tri in triangulos:
        A = vertices[tri[0]]
        B = vertices[tri[1]]
        C = vertices[tri[2]]

        B_A = restaVectores(B,A)
        C_B = restaVectores(C,B)
        nor_tri = productoVectorial(B_A,C_B)
        
        normales_triangulos.append(vectorNormalizado(nor_tri))

    normales_vertices_aux = [[0,0,0] for v in vertices]
    
    for i in range(len(triangulos)):
        normales_vertices_aux[triangulos[i][0]] = sumaVectores(normales_vertices_aux[triangulos[i][0]],normales_triangulos[i])
        normales_vertices_aux[triangulos[i][1]] = sumaVectores(normales_vertices_aux[triangulos[i][1]],normales_triangulos[i])
        normales_vertices_aux[triangulos[i][2]] = sumaVectores(normales_vertices_aux[triangulos[i][2]],normales_triangulos[i])

    for v in normales_vertices_aux: 
        normales_vertices.append(vectorNormalizado(v))
    
def vectorValorAbsoluto(v):
    vector_valor_absoluto = [abs(v[0]),abs(v[1]),abs(v[2])]

    return vector_valor_absoluto

def creaColoresSegunNormales():
    for v in normales_vertices:
        colores_vertices.append(vectorValorAbsoluto(v))

    for v in normales_triangulos:
        colores_triangulos.append(vectorValorAbsoluto(v))

def revoluciona(vueltas):
    for v in vertices:
        if v[0] <= 0:
            print("Error: debe verificarse f(t)>0")
            sys.exit(-1)

    copia_perfil = list(vertices)
    num_ver_copia_perfil = len(copia_perfil)
    angulo_inicial = 2*math.pi/(vueltas)
    angulo = angulo_inicial

    for i in range(vueltas-1):
        for v in copia_perfil:
            vertices.append(rotacionEjeY(v,angulo))
        angulo += angulo_inicial

    for perfil_i in range(vueltas):
        for j in range(num_ver_copia_perfil-1):

            primer_ver_perfil_i = num_ver_copia_perfil * perfil_i
             
            if perfil_i == vueltas-1:
                primer_ver_sig_perfil = 0
            else:
                primer_ver_sig_perfil = primer_ver_perfil_i + num_ver_copia_perfil 

            triangulos.append([primer_ver_perfil_i+j,primer_ver_sig_perfil+j,primer_ver_perfil_i+j+1])
            triangulos.append([primer_ver_perfil_i+j+1,primer_ver_sig_perfil+j,primer_ver_sig_perfil+j+1])

    creaNormales();
    creaColoresSegunNormales();



def inicializar(argumentos):
    if len(argumentos) < 6:
        print("Es necesario introducir 6 argumentos")
        print("Uso: python SuperficieRevolucion.py <f(t)> <g(t)> <número de puntos> <inicio> <fin>")
        sys.exit(-1)

    global vertices, x_t, y_t, z_t
    t = symbols('t')

    x_t         = sympify(argumentos[1])
    y_t         = sympify(argumentos[2])
    z_t         = sympify('0')
    num_puntos  = int(argumentos[3])
    inicio      = float(argumentos[4])
    final       = float(argumentos[5])
    vueltas     = 32

    longitud = final - inicio
    incremento = longitud / (num_puntos - 1)

    curva = Matrix([x_t,y_t,z_t])

    for indice_punto in range(num_puntos):
        t_var = inicio + indice_punto*incremento
        vertices.append([curva[0].subs(t,t_var),curva[1].subs(t,t_var),curva[2].subs(t,t_var)])

    revoluciona(vueltas)

    glEnable(GL_NORMALIZE)
    glEnable(GL_MULTISAMPLE_ARB);
    glClearColor( 1.0, 1.0, 1.0, 1.0 ) ;
    glColor3f(0.0,0.0,0.0)

def main(argumentos):
    glutInit(argumentos)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_ALPHA)

    glutInitWindowPosition(0, 0)
    glutInitWindowSize(ventana_tam_x, ventana_tam_y)
    glutCreateWindow("Superficie de revolucion")
    inicializar(argumentos)

    glEnable( GL_DEPTH_TEST )

    glutDisplayFunc(dibujar)
    glutReshapeFunc(cambioTamanio)
    glutKeyboardFunc(teclaNormal)
    glutSpecialFunc(teclaEspecial)
    glutMouseFunc(pulsarRaton)
    glutMotionFunc(moverRaton)

    glutMainLoop()

if __name__ == '__main__':
    main(sys.argv) 
