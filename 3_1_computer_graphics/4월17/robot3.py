import glfw
from OpenGL.GL import *
from OpenGL.GLUT import glutInit, glutBitmapCharacter, GLUT_BITMAP_HELVETICA_18
import sys

glutInit(sys.argv)  

# ── 기본 비율 ─────────────────────────────────────
TORSO_W, TORSO_H = 4.0, 4.0
HEAD_W,  HEAD_H  = 1.4, 1.4
UP_ARM_W, UP_ARM_H = 0.8, 2.0   # 수평(가로)으로 붙일 upper‑arm
LO_ARM_W, LO_ARM_H = 0.4, 0.8   # 수직(세로)로 내려올 lower‑arm
UP_LEG_W, UP_LEG_H = 0.8, 1.0
LO_LEG_W, LO_LEG_H = 0.4, 2.0
LINE_COLOR = (0, 0, 0)

# ── 원점 마커 + 호출‑카운터 내장 ──────────────────
def draw_pivot(x=1,y=1,size=30,color=0):
    """
    호출될 때마다 1,2,3… 자동 번호가 찍히는 마커.
    프레임 시작 전에 draw_pivot.counter = 1 로 리셋!
    """
    if not hasattr(draw_pivot, "counter"):
        draw_pivot.counter = 1          # 최초 실행 시만 설정

    idx = draw_pivot.counter            # 이번 번호
    draw_pivot.counter += 1             # 다음 준비

    # 점
    glPointSize(size)
    glBegin(GL_POINTS)
    glColor3f(color,color,color)
    glVertex2f(0, 0)
    glEnd()

    # 숫자 (점에서 살짝 오른쪽·위)
    glColor3f(0, 0, 0)
    glRasterPos2f(x/3,y/3)
    for ch in str(idx):
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ord(ch))

# ── 사각형: (0,0) = pivot, +Y 방향으로 높이 h ───────
def rect(w, h):
    glColor3f(*LINE_COLOR)
    glBegin(GL_LINE_LOOP)
    glVertex2f(-w * 0.5, 0)    # 좌하
    glVertex2f( w * 0.5, 0)    # 우하
    glVertex2f( w * 0.5, h)    # 우상
    glVertex2f(-w * 0.5, h)    # 좌상
    glEnd()

# ── 관절 각도(시계방향 +) --------------------------------
θ_lua =  15   # left upper‑arm (수평에서 위로 +)
θ_lla = -90   # left lower‑arm  (upper 기준 아래로)
θ_rua = -15   # right upper‑arm
θ_rla = -90   # right lower‑arm

θ_lul =   5   # left upper‑leg (몸통에서 앞/뒤로)
θ_lll =  -5   # left lower‑leg
θ_rul = -5    # right upper‑leg
θ_rll =   5   # right lower‑leg

# ── 인형 그리기 ------------------------------------------
def figure():
    glPushMatrix()

    draw_pivot(1,1)
    # 0) TORSO (pivot = 좌하)
    rect(TORSO_W, TORSO_H)

    # 1) HEAD (torso 위 중앙)
    glPushMatrix()
    draw_pivot(2,1,15,0.5)
    glTranslatef(0, TORSO_H, 0)
    draw_pivot(1,1)
    rect(HEAD_W, HEAD_H)
    glPopMatrix()
    draw_pivot(3,1,15,0.5)

    # # 2) LEFT ARM (upper: 수평, lower: 수직)
    glPushMatrix()
    glTranslatef(-TORSO_W * 0.5-0.4, TORSO_H * 0.75-1.25, 0)
    draw_pivot(1,1,15,0.5)
    # glRotatef(θ_lua - 90, 0, 0, 1)  # -90 해서 수평 기준 맞춤
    rect(UP_ARM_W, UP_ARM_H)        # 가로폭 = 길이, 세로 = 두께
    # glTranslatef(UP_ARM_H,0, 0)    # 팔꿈치로 이동
    # # glRotatef(θ_lla, 0, 0, 1)
    rect(LO_ARM_W, -LO_ARM_H)        # 아래로
    glPopMatrix()

    # # # 3) RIGHT ARM
    glPushMatrix()
    glTranslatef(TORSO_W * 0.5+0.4, TORSO_H * 0.75-1.25, 0)
    draw_pivot(1,1,15,0.5)
    # glRotatef(θ_rua + 90, 0, 0, 1)  # +90 오른쪽으로 수평
    rect(UP_ARM_W, UP_ARM_H)
    # glTranslatef(UP_ARM_H, 0, 0)
    # glRotatef(θ_rla, 0, 0, 1)
    rect(LO_ARM_W, -LO_ARM_H)
    glPopMatrix()
    draw_pivot(4,1,15,0.5)

    # # # 4) LEFT LEG (pivot = 몸통 아래 모서리)
    glPushMatrix()
    glTranslatef(-TORSO_W * 0.25, 0, 0)    # 왼쪽 골반
    # glRotatef(θ_lul, 0, 0, 1)
    rect(UP_LEG_W, -UP_LEG_H)
    glTranslatef(0, -UP_LEG_H, 0)
    # glRotatef(θ_lll, 0, 0, 1)
    rect(LO_LEG_W, -LO_LEG_H)
    glPopMatrix()

    # # # 5) RIGHT LEG
    glPushMatrix()
    glTranslatef(TORSO_W * 0.25, 0, 0)
    # glRotatef(θ_rul, 0, 0, 1)
    rect(UP_LEG_W, -UP_LEG_H)
    glTranslatef(0, -UP_LEG_H, 0)
    # glRotatef(θ_rll, 0, 0, 1)
    rect(LO_LEG_W, -LO_LEG_H)
    glPopMatrix()

    glPopMatrix()

# ── OpenGL/GLFW 기본 루프 ------------------------------
def render():
    glClear(GL_COLOR_BUFFER_BIT)
    glLoadIdentity()
    draw_pivot.counter = 1      # ←← 여기! 프레임마다 1로 리셋
    glTranslatef(0, -1, 0)
    figure()

def main():
    if not glfw.init():
        return
    glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 2)
    glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 1)
    glfw.window_hint(glfw.OPENGL_PROFILE, glfw.OPENGL_ANY_PROFILE)
    win = glfw.create_window(480, 720, "Hierarchical Figure - Exact", None, None)
    if not win:
        glfw.terminate(); return
    glfw.make_context_current(win)

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity(); glOrtho(-6, 6, -6, 10, -1, 1)
    glClearColor(1, 1, 1, 1)
    glMatrixMode(GL_MODELVIEW)

    while not glfw.window_should_close(win):
        glfw.poll_events()
        render()
        glfw.swap_buffers(win)
    glfw.terminate()

if __name__ == "__main__":
    main()
