import numpy as np
import matplotlib.pyplot as plt

# --- 기본 2D 변환 행렬 -----------------------------
def T(tx, ty):
    """평행이동 4×4 행렬"""
    M = np.eye(4)
    M[0, 3], M[1, 3] = tx, ty
    return M

def R(theta):
    """Z축 회전 4×4 행렬 (라디안)"""
    c, s = np.cos(theta), np.sin(theta)
    M = np.eye(4)
    M[:2, :2] = [[c, -s], [s, c]]
    return M

# --- forward‑kinematics --------------------------------
def lamp_fk(x, y, th0, th1, th2, th3, l0, l1, l2):
    """각 관절 각도·길이 → 각 프레임 원점 좌표 리스트"""
    frames = [np.eye(4)]                   # 월드 원점
    M = T(x, y) @ R(th0)                   # 베이스 전역 위치·자세
    frames.append(M.copy())

    # 링크 0
    M = M @ T(0, l0) @ R(th1)
    frames.append(M.copy())

    # 링크 1
    M = M @ T(l1, 0) @ R(th2)
    frames.append(M.copy())

    # 링크 2 (end‑effector)
    M = M @ T(l2, 0) @ R(th3)
    frames.append(M.copy())
    return frames

# --- 예제 파라미터 ------------------------------------
θ0, θ1, θ2, θ3 = np.deg2rad([20,  40, -30, 10])
l0, l1, l2      = 1.5, 2.0, 1.2
x,  y           =  2.0, 0.5

frames = lamp_fk(x, y, θ0, θ1, θ2, θ3, l0, l1, l2)

# --- 시각화 -------------------------------------------
plt.figure(figsize=(5,5))
for a, b in zip(frames[:-1], frames[1:]):
    P = a[:2, 3]          # 링크 시작점
    Q = b[:2, 3]          # 링크 끝점
    plt.plot([P[0], Q[0]], [P[1], Q[1]], marker='o')
plt.axis('equal'); plt.grid(True)
plt.xlabel('X'); plt.ylabel('Y'); plt.title('2‑D Lamp Pose')
plt.tight_layout(); plt.show()
