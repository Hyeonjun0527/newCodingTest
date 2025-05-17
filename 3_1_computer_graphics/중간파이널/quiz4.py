import glfw
from OpenGL.GL import *

# ── 유틸 -------------------------------------------------
def draw_line(length):
    """x축 양의 방향으로 길이 `length`인 선분을 그림"""
    glBegin(GL_LINES)
    glVertex2d(0, 0)
    glVertex2d(length, 0)
    glEnd()

# ── 인형(팔) --------------------------------------------
def figure():
    lengths = [0.8, 0.8, 0.8]     # 스케일 ↑
    thetas  = [30., 40., -20.]

    glPushMatrix()               # 전체 인형용 스택
    for l, t in zip(lengths, thetas):
        glRotatef(t, 0, 0, 1)     # 관절 회전
        draw_line(l)              # 뼈대 그리기
        glTranslatef(l, 0, 0)     # 다음 관절 기준점
    glPopMatrix()

# ── 렌더 루프 -------------------------------------------
def render():
    glClear(GL_COLOR_BUFFER_BIT)
    glLoadIdentity()

    glTranslatef(0, -1, 0)        # 화면 중앙 아래로 살짝 내림
    figure()

# ── 진입점 ----------------------------------------------
def main():
    if not glfw.init():
        return
    win = glfw.create_window(480, 720, "Hierarchical Figure", None, None)
    if not win:
        glfw.terminate(); return
    glfw.make_context_current(win)

    # 투영(작은 범위로 축소)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(-2, 2, -3, 5, -1, 1)

    # 배경 흰색, 선 굵기·색상 설정
    glClearColor(1, 1, 1, 1)
    glLineWidth(2)
    glColor3f(0, 0, 0)

    glMatrixMode(GL_MODELVIEW)

    # 메인 루프
    while not glfw.window_should_close(win):
        glfw.poll_events()
        render()
        glfw.swap_buffers(win)

    glfw.terminate()

if __name__ == "__main__":
    main()
