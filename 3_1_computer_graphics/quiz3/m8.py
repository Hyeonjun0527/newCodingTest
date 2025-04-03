import numpy as np
import matplotlib.pyplot as plt

# 원본 삼각형의 꼭짓점 좌표 설정
orig_points = np.array([[0, 0],    # A (원점)
                        [3, 0],    # B (x축 위 점)
                        [0, 3]])   # C (y축 위 점)

# 변환 행렬 정의
R = np.array([[0, -1],   # 90도 반시계 회전 행렬
              [1,  0]])
S = np.array([[1,   0],   # y축 방향 1.5배 확대 행렬
              [0, 1.5]])

# 1단계: 회전 변환 적용 (오른쪽 행렬 R 먼저 적용)
rot_points = orig_points.dot(R.T)   # 각 점에 R 적용 (orig_points가 Nx2 행렬이므로 R의 전치를 곱함)

# 2단계: 스케일 변환 적용 (왼쪽 행렬 S를 나중에 적용)
trans_points = rot_points.dot(S.T)  # R 적용 결과에 S 적용

# 그래프 그리기 설정
fig, axs = plt.subplots(1, 2, figsize=(8, 4))  # 1행 2열의 subplot

# (a) 원본 삼각형 그리기
x0 = [orig_points[0,0], orig_points[1,0], orig_points[2,0], orig_points[0,0]]  # 닫힌 삼각형을 그리기 위한 x 좌표열
y0 = [orig_points[0,1], orig_points[1,1], orig_points[2,1], orig_points[0,1]]  # 닫힌 삼각형을 그리기 위한 y 좌표열
axs[0].plot(x0, y0, color='blue')                  # 삼각형 변들을 파란색 선으로 그림
axs[0].scatter(0, 0, color='black', zorder=5)      # 원점에 검은 점 표시
axs[0].set_xlim(-5, 5); axs[0].set_ylim(-5, 5)     # 축 범위 설정
axs[0].set_aspect('equal', 'box')                  # 축 비율 1:1 (왜곡 없이)
axs[0].grid(True)
axs[0].set_title("(a) 원래 삼각형")

# (b) 변환된 삼각형 그리기
x1 = [trans_points[0,0], trans_points[1,0], trans_points[2,0], trans_points[0,0]]
y1 = [trans_points[0,1], trans_points[1,1], trans_points[2,1], trans_points[0,1]]
axs[1].plot(x1, y1, color='blue')
axs[1].scatter(0, 0, color='black', zorder=5)
axs[1].set_xlim(-5, 5); axs[1].set_ylim(-5, 5)
axs[1].set_aspect('equal', 'box')
axs[1].grid(True)
axs[1].set_title("(b) 변환된 삼각형")

plt.show()
