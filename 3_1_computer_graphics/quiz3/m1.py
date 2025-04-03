import numpy as np
import matplotlib.pyplot as plt

# 1. 원래 정사각형의 두 방향 벡터 (v1, v2)
v1 = np.array([2, 0])
v2 = np.array([0, 2])

# 2. 변환된 평행사변형의 방향 벡터 추정값 (v1', v2')
v1_prime = np.array([2, 1])
v2_prime = np.array([-1, 2.5])

# 3. 변환 행렬 A 계산 (A * v1 = v1', A * v2 = v2')
B = np.column_stack((v1, v2))             # 원래 기준 벡터 행렬 [v1 v2]
B_prime = np.column_stack((v1_prime, v2_prime))  # 변환된 벡터 행렬 [v1' v2']
A = B_prime.dot(np.linalg.inv(B))         # A = B_prime * B^{-1}
print("변환 행렬 A:")
print(A)

# 4. 원래 정사각형의 꼭짓점 좌표들과 변환 후 좌표 계산
square_points = np.array([[ 2,  2],
                           [-2,  2],
                           [-2, -2],
                           [ 2, -2],
                           [ 2,  2]]).T   # 2x5 배열로 정사각형 꼭짓점 (마지막은 시작점 반복하여 도형 닫음)
transformed_points = A.dot(square_points)  # 행렬 A를 적용한 변환된 좌표들

# 원래 정사각형 (파란색)과 변환된 평행사변형 (빨간색) 그리기
plt.figure(figsize=(6,6))
plt.axhline(0, color='gray', linewidth=0.5)
plt.axvline(0, color='gray', linewidth=0.5)
plt.plot(square_points[0], square_points[1], 'b-o', label='Original Square')
plt.plot(transformed_points[0], transformed_points[1], 'r-o', label='Transformed Parallelogram')
plt.scatter(0, 0, color='black')  # 원점 표시

# 기준 벡터들과 변환된 벡터를 화살표로 표시
plt.arrow(0, 0, v1[0], v1[1], head_width=0.1, color='blue', length_includes_head=True)
plt.text(v1[0]*1.1, v1[1]*1.1, 'v1', color='blue')
plt.arrow(0, 0, v2[0], v2[1], head_width=0.1, color='blue', length_includes_head=True)
plt.text(v2[0]*1.1, v2[1]*1.1, 'v2', color='blue')
plt.arrow(0, 0, v1_prime[0], v1_prime[1], head_width=0.1, color='red', length_includes_head=True)
plt.text(v1_prime[0]*1.1, v1_prime[1]*1.1, "v1'", color='red')
plt.arrow(0, 0, v2_prime[0], v2_prime[1], head_width=0.1, color='red', length_includes_head=True)
plt.text(v2_prime[0]*1.1, v2_prime[1]*1.1, "v2'", color='red')

plt.axis('equal')
plt.legend(loc='upper left')
plt.title("Square (blue) and its linear transform (red)")
plt.show()
