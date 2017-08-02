#!/usr/bin/env python

from easygui import *
import sys
import SuperficiesRevolucion

if __name__ == "__main__":
    corriendo = False
    while not corriendo:

        correcto = False
        valorCampos = []
        while not correcto:
            mensaje = "Introduce la curva que creará la superficie de revolución"
            mensaje += "\n(con f(t)>0 y (f(t),g(t)) regular de primer orden)"
            titulo = "Superficies de revolución"
            nombreCampos = ["f(t)","g(t)","Número de muestras","Inicio del intervalo","Final del intervalo"]
            valorCampos = multenterbox(mensaje,titulo,nombreCampos,valorCampos)

            if valorCampos is None:
                sys.exit(-1)
            elif all(valorCampos):
                correcto = True
            else:
                correcto = False
                msgbox("Te has dejado algún dato sin introducir")

        corriendo = True

        argumentos = ["./SuperficiesRevolucion"] + valorCampos
        SuperficiesRevolucion.main(argumentos)
