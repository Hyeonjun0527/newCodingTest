import numpy as np
import matplotlib.pyplot as plt

# 1) 원본 삼각형 정의: (x,y) 좌표
triangle = np.array([
    [-2,  0],   # 예시 꼭짓점 1
    [-1,  2],   # 예시 꼭짓점 2
    [ 1,  1],   # 예시 꼭짓점 3
    [-2,  0]    # 닫기용 (첫 점과 동일)
])

# 2) 회전 행렬 (90° 반시계)
R_90 = np.array([
    [ 0, -1],
    [ 1,  0]
])

# 3) 변환 적용
#   (N x 2) · (2 x 2) => (N x 2)
triangle_rotated = triangle @ R_90

# 4) 시각화
plt.figure(figsize=(6,6))

# 원본 삼각형
plt.plot(triangle[:,0], triangle[:,1], 'bo-', label='Original triangle')

# 회전된 삼각형
plt.plot(triangle_rotated[:,0], triangle_rotated[:,1], 'ro-', label='Rotated triangle (90° CCW)')

# 좌표축 보조선
plt.axhline(0, color='gray', linewidth=0.5)
plt.axvline(0, color='gray', linewidth=0.5)

# 축 비율 동일하게 (찌그러지지 않도록)
plt.gca().set_aspect('equal', adjustable='box')
plt.legend()
plt.title("Triangle Rotation by 90° around the Origin")
plt.show()
