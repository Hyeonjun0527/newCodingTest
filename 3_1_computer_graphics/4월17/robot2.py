# pip install glfw PyOpenGL
import glfw
from OpenGL.GL import *

# ---------- 링크 파라미터 ----------
L0, L1, L2 = 2.0, 1.6, 1.2

BASE_W, H    = 2.0, 0.4          # 베이스 가로·세로
x,  y      = 1.0,2.0
th1, th2, th3 = 70,-40, 30 # deg

# ── 원점 마커 ────────────────────────────────
def draw_pivot(size=30,color=0):
    glPointSize(size)
    glBegin(GL_POINTS)
    glColor3f(color,color*0.3,color*0.7)          # 검은 점
    glVertex2f(0,0)
    glEnd()


# ① 링크는 +X 로만 그린다 → 직사각형 함수는 그대로
def link(L, H=0.25):
    h = H*0.5
    glBegin(GL_QUADS)
    glVertex2f(0,-h); glVertex2f(L,-h)
    glVertex2f(L, h); glVertex2f(0, h)
    glEnd()

def base_X(W, H):
    h = H * 0.5
    glBegin(GL_QUADS)
    glVertex2f(-W*0.5, -h); glVertex2f( W*0.5, -h)
    glVertex2f( W*0.5,  h); glVertex2f(-W*0.5,  h)
    glEnd()

# ② 'Link n' :  R(θn) ➜ T(Ln,0)  ➜ draw
def render():
    glClear(GL_COLOR_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

    # 월드 원점
    draw_pivot()

    # (0) 베이스 중심 ---------------------------------
    glTranslatef(x, y, 0)
    draw_pivot()                                # ▶ after T(x,y)
    glColor3f(.3,.3,.3); base_X(BASE_W, H)

    # (1) 링크 0 -------------------------------------
    glRotatef(th1, 0,0,1)
    draw_pivot(15,0.5)                                # ▶ after R(θ1)
    glColor3f(1,0,0); link(L0)

    glTranslatef(L0, 0, 0)
    draw_pivot()                                # ▶ after T(L0,0)

    # (2) 링크 1 -------------------------------------
    glRotatef(th2, 0,0,1)
    draw_pivot(15,0.5)                                # ▶ after R(θ2)
    glColor3f(0,1,0); link(L1)

    glTranslatef(L1, 0, 0)
    draw_pivot()                                # ▶ after T(L1,0)

    # (3) 링크 2 -------------------------------------
    glRotatef(th3, 0,0,1)
    draw_pivot(15,0.5)                                # ▶ after R(θ3)
    glColor3f(0,0,1); link(L2)



# ---------- GLFW 셋업 ----------
def main():
    if not glfw.init():
        return
    # 호환 프로필 요청(= glBegin 사용 OK)
    glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 2)
    glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 1)
    glfw.window_hint(glfw.OPENGL_PROFILE, glfw.OPENGL_ANY_PROFILE)

    win = glfw.create_window(640,640, "2‑D Lamp (최소)", None, None)
    if not win: glfw.terminate(); return
    glfw.make_context_current(win)

    # 2‑D 정투영
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(-6, 6, -6, 6, -1, 1)

    glClearColor(1,1,1,1)         # 흰 배경
    while not glfw.window_should_close(win):
        render()
        glfw.swap_buffers(win)
        glfw.poll_events()
    glfw.terminate()

if __name__ == "__main__":
    main()
