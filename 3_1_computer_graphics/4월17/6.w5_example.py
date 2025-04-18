from OpenGL.GLUT import *
from OpenGL.GL import *
import colorsys


def draw_line(length, color):
    glBegin(GL_LINES)
    glColor3d(color[0], color[1], color[2])
    glVertex3f(0.0, 0.0, 0.0)
    glVertex3f(length, 0.0, 0.0)
    glEnd()

def draw_box(points, color):
    glBegin(GL_LINE_LOOP)
    glColor3d(color[0], color[1], color[2])
    for p in points:
        glVertex3f(p[0], p[1], 0.0)
    glEnd()


def torso():
    draw_box([
        [-2., -2.],
        [-2., 2.],
        [2., 2.],
        [2., -2.]
    ], 
    color=colorsys.hsv_to_rgb(1/6, 1, 1))

def head():
        draw_box([
        [-2/3, -2/3],
        [-2/3,  2/3],
        [ 2/3,  2/3],
        [ 2/3, -2/3]
    ], 
    color=colorsys.hsv_to_rgb(2/6, 1, 1))

def upper_arm():
    draw_box([
        [0., -1/2],
        [0.,  1/2],
        [2.,  1/2],
        [2., -1/2]
    ], 
    color=colorsys.hsv_to_rgb(3/6, 1, 1))

def lower_arm():
    draw_box([
        [0., -1/3],
        [0.,  1/3],
        [1,  1/3],
        [1, -1/3]
    ], 
    color=colorsys.hsv_to_rgb(4/6, 1, 1))

def upper_leg():
    draw_box([
        [-3/5., -3  ],
        [-3/5.,  0. ],
        [ 3/5.,  0. ],
        [ 3/5., -3  ]
    ], 
    color=colorsys.hsv_to_rgb(5/6, 1, 1))


def lower_leg():
    draw_box([
        [-1/2., -2  ],
        [-1/2.,  0. ],
        [ 1/2.,  0. ],
        [ 1/2., -2  ]
    ], 
    color=colorsys.hsv_to_rgb(6/6, 1, 1))


def draw():
    glClearColor(0., 0., 0., 0.)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glColor3f(1., 1., 1.)
    glPushMatrix()
    glOrtho(-8.0, 8.0, -8.0, 8.0, -1.0, 1.0)
    glLineWidth(4.)

    glTranslatef(0.0, 3.0, 0.0)
    torso()

    # head
    glPushMatrix()
    glTranslatef(0.0, 2.0+2/3, 0.0)
    head()
    glPopMatrix()

    # left arm
    glPushMatrix()
    glTranslatef(2.5, 1.0, 0.0)
    glRotatef(-90.0, 0.0, 0.0, 1.0)
    upper_arm()
    glTranslatef(2.0, 0.0, 0.0)
    lower_arm()
    glPopMatrix()

    # right arm
    glPushMatrix()
    glTranslatef(-2.5, 1.0, 0.0)
    glRotatef(270.0, 0.0, 0.0, 1.0)
    upper_arm()
    glTranslatef(2.0, 0.0, 0.0)
    lower_arm()
    glPopMatrix()

    # left leg
    glPushMatrix()
    glTranslatef(1.0, -2.0, 0.0)
    upper_leg()
    glTranslatef(0.0, -3.0, 0.0)
    lower_leg()
    glPopMatrix()

    # Right leg
    glPushMatrix()
    glTranslatef(-1.0, -2.0, 0.0)
    upper_leg()
    glTranslatef(0.0, -3.0, 0.0)
    lower_leg()
    glPopMatrix()

    glPopMatrix()
    glFlush()

glutInit()
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
glutInitWindowSize(500, 500)
glutInitWindowPosition(100, 100)
glutCreateWindow(b"My Simple forward kinematics Program")
glutDisplayFunc(draw)
glutMainLoop()
