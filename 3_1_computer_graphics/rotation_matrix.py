import numpy as np
import matplotlib.pyplot as plt

# 1. 원본 정사각형(꼭짓점 좌표) 정의
#    각 행이 (x, y) 형태이며, 마지막 점은 처음 점과 같게 해서 닫힌 도형으로 표현
square = np.array([
    [-1, -1],
    [ 1, -1],
    [ 1,  1],
    [-1,  1],
    [-1, -1]  # 도형을 닫기 위해 시작점으로 돌아감
])

# 2. 회전 각도(라디안으로 변환) 및 회전 행렬 정의 (반시계방향 45도)
theta = np.radians(45)
cos_t = np.cos(theta)
sin_t = np.sin(theta)

R = np.array([
    [ cos_t, -sin_t],
    [ sin_t,  cos_t]
])

# 3. 회전 행렬을 이용해 각 점에 적용
#    각 점을 행벡터로 보고, (N x 2) · (2 x 2) = (N x 2) 형태로 곱해줌
square_rotated = square @ R

# 4. 결과 시각화
plt.figure(figsize=(6,6))
# 원본 도형
plt.plot(square[:,0], square[:,1], 'bo-', label='Original square')
# 회전된 도형
plt.plot(square_rotated[:,0], square_rotated[:,1], 'ro-', label='Rotated square (45°)')

# 보기 좋게 설정
plt.axhline(0, color='gray', linewidth=0.5)
plt.axvline(0, color='gray', linewidth=0.5)
plt.gca().set_aspect('equal', adjustable='box')
plt.legend()
plt.title("Square Rotation by 45° around the Origin")
plt.show()
