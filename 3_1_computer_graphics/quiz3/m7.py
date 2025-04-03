import numpy as np
import matplotlib.pyplot as plt

# 원래 삼각형의 꼭지점 좌표
original = np.array([[0, 0], [3, 0], [0, 3]], dtype=float)

# 변환 행렬 정의
R = np.array([[1, 0], [0, -1]], dtype=float)   # x축 대칭 (반사) 행렬
S = np.array([[1.5, 0], [0, 1]], dtype=float)  # x방향 1.5배 확대 (스케일) 행렬

# 순서: 오른쪽 행렬 R을 먼저 적용한 후 S 적용
reflected = original.dot(R)         # R 적용 (반사 변환)
transformed = reflected.dot(S)      # S 적용 (스케일 변환)

# 원래 삼각형과 변환 삼각형의 x, y좌표 (폐곡선을 위해 첫 점을 끝에 추가)
orig_x = list(original[:, 0]) + [original[0, 0]]
orig_y = list(original[:, 1]) + [original[0, 1]]
trans_x = list(transformed[:, 0]) + [transformed[0, 0]]
trans_y = list(transformed[:, 1]) + [transformed[0, 1]]

# 그래프 그리기
plt.figure(figsize=(6, 6))
plt.plot(orig_x, orig_y, 'o-', color='blue', label='Original triangle')    # 원래 삼각형 (파랑)
plt.plot(trans_x, trans_y, 'o-', color='red', label='Transformed triangle')# 변환 삼각형 (빨강)

# 축 비율을 동일하게 하고 대칭적으로 범위 설정
plt.gca().set_aspect('equal', adjustable='box')  # 축 비율 1:1
plt.xlim(-5, 5)
plt.ylim(-5, 5)

# 격자, 축, 범례 표시
plt.axhline(0, color='black', linewidth=0.5)   # x축 표시선
plt.axvline(0, color='black', linewidth=0.5)   # y축 표시선
plt.grid(True)
plt.legend()

plt.show()
