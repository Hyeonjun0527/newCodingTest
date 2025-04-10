import numpy as np
import matplotlib.pyplot as plt

# 원래 정사각형의 꼭짓점 (0,0을 중심으로 변 길이가 2이므로)
# 순서대로 연결하고 시작점으로 돌아와야 정사각형이 완성됨
square = np.array([
    [-1, -1],
    [ 1, -1],
    [ 1,  1],
    [-1,  1],
    [-1, -1]  # 시작점으로 복귀
])

# 45도 회전 행렬
rotation_matrix = np.array([
    [np.sqrt(2)/2, -np.sqrt(2)/2],
    [np.sqrt(2)/2,  np.sqrt(2)/2]
])

# 각 꼭짓점에 회전행렬 적용 (행 벡터 기준으로 계산)
rotated_square = square.dot(rotation_matrix.T)

# 결과를 시각화
plt.figure(figsize=(6, 6))
plt.plot(square[:, 0], square[:, 1], 'b-', label='원래 정사각형')
plt.plot(rotated_square[:, 0], rotated_square[:, 1], 'r-', label='45° 회전 후')

# 중심점 표시
plt.scatter(0, 0, color='k', marker='o', label='중심 (0,0)')

plt.title("정사각형의 45° 회전")
plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.grid(True)
plt.axis('equal')
plt.show()
