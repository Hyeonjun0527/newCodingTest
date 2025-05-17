from OpenGL.GL import *
from OpenGL.GLUT import *
import numpy as np
import sys

def init():
    glClearColor(0.0, 0.0, 0.0, 1.0)
    glEnable(GL_DEPTH_TEST)


def set_perspective(fov, aspect, z_near, z_far):
    f = 1.0 / np.tan(np.radians(fov) / 2.0)
    nf = 1.0 / (z_near - z_far)

    proj_matrix = np.eye(4, dtype=np.float32)
    proj_matrix[0, 0] = f / aspect
    proj_matrix[1, 1] = f
    proj_matrix[2, 2] = (z_far + z_near) * nf
    proj_matrix[2, 3] = 2 * z_far * z_near * nf
    proj_matrix[3, 2] = -1.0
    proj_matrix[0, 1] = 0.0
    proj_matrix[0, 2] = 0.0
    proj_matrix[0, 3] = 0.0
    proj_matrix[1, 0] = 0.0
    proj_matrix[1, 2] = 0.0
    proj_matrix[1, 3] = 0.0
    proj_matrix[3, 0] =  0.0
    proj_matrix[3, 1] =  0.0
    proj_matrix[3, 3] =  0.0
    
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glLoadMatrixf(proj_matrix.T) 

def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glTranslatef(0.0, 0.0, -5.0)

    glutWireCube(1.0)

    glutSwapBuffers()

def reshape(w, h):
    if h == 0:
        h = 1
    aspect = w / h
    glViewport(0, 0, w, h)
    set_perspective(60.0, aspect, 1.0, 100.0)

def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
    glutInitWindowSize(800, 600)
    glutCreateWindow(b"Custom Perspective Projection")
    init()
    glutDisplayFunc(display)
    glutReshapeFunc(reshape)
    glutMainLoop()

if __name__ == "__main__":
    main()
