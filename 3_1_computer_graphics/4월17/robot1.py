# pip install glfw PyOpenGL
import glfw
from OpenGL.GL import *

# ── 파라미터 ───────────────────────────────────────
L0, L1, L2   = 2.0, 1.6, 1.2     # 링크 길이
BASE_W, H    = 2.0, 0.4          # 베이스 가로·세로
x, y         = -2.5, -3.0        # 베이스 중심 위치
# 교재 θ는 시계방향(+). glRotatef는 CCW(+) → 부호 뒤집어 사용
θ0, θ1, θ2 = 70,-40, 30 # deg

# ── 도형  (+Y 로 뻗는 링크,  +X 로 뻗는 베이스) ─────────
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

# ── 렌더링 ──────────────────────────────────────────
def render():
    glClear(GL_COLOR_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

    # (0) 베이스: 중심으로 이동하고 그대로 그림 (수평 유지)
    glTranslatef(x, y, 0)
    glColor3f(.3,.3,.3)
    base_X(BASE_W, H)

    #    베이스 위쪽 중앙 → C1 피벗으로 이동
    glTranslatef(0, H*0.5, 0)     # T(0, H/2)
    glRotatef(θ0, 0,0,1)          # 베이스 기울기 (CW = -)

    # (1) 링크 0
    glColor3f(1,0,0)
    link(L0)                    # 그리기
    glTranslatef(0, L0, 0)        # 끝점으로 이동
    glRotatef(θ1, 0,0,1)

    # (2) 링크 1
    glColor3f(0,1,0)
    link(L1)
    glTranslatef(0, L1, 0)
    glRotatef(θ2, 0,0,1)

    # (3) 링크 2
    glColor3f(0,0,1)
    link(L2)


# ── GLFW 셋업 ───────────────────────────────────────
def main():
    if not glfw.init():
        return
    glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 2)
    glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 1)
    glfw.window_hint(glfw.OPENGL_PROFILE, glfw.OPENGL_ANY_PROFILE)

    win = glfw.create_window(640, 640, "2‑D Lamp (교재 TR‑패턴)", None, None)
    if not win: glfw.terminate(); return
    glfw.make_context_current(win)

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(-6, 6, -6, 6, -1, 1)
    glClearColor(1,1,1,1)

    while not glfw.window_should_close(win):
        glfw.poll_events()
        render()
        glfw.swap_buffers(win)
    glfw.terminate()

if __name__ == "__main__":
    main()
