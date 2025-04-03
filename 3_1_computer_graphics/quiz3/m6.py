import numpy as np
import matplotlib.pyplot as plt

# 원래 정사각형의 꼭짓점 좌표 (중심 원점, 변의 길이 4)
original_vertices = np.array([[ 2,  2],
                               [-2,  2],
                               [-2, -2],
                               [ 2, -2]])

# x축 방향 반전 행렬과 30° 회전 행렬 정의
reflection_matrix = np.array([[-1, 0],
                               [ 0, 1]])  # x좌표 부호 반전 (y축 대칭)
theta = np.pi / 6  # 30도의 라디안 값 (π/6)
rotation_matrix = np.array([[np.cos(theta), -np.sin(theta)],
                             [np.sin(theta),  np.cos(theta)]])

# 행렬 곱으로 결합된 변환 행렬 계산 (회전 ∘ 반전)
transformation_matrix = rotation_matrix.dot(reflection_matrix)

# 변환 행렬을 원본 꼭짓점들에 적용하여 새로운 좌표 계산
transformed_vertices = (transformation_matrix.dot(original_vertices.T)).T

# 결과 좌표 출력
print("Transformed vertices:")
for v in transformed_vertices:
    print(v)

# 원본과 변환된 정사각형을 시각적으로 비교
# 정사각형을 그리기 위해 처음 꼭짓점을 끝에 한 번 더 추가하여 폐곡선 구성
original_closed = np.vstack([original_vertices, original_vertices[0]])
transformed_closed = np.vstack([transformed_vertices, transformed_vertices[0]])

plt.figure(figsize=(6,6))
plt.plot(original_closed[:,0], original_closed[:,1], 'k--', label='Original square')
plt.plot(transformed_closed[:,0], transformed_closed[:,1], 'r-', label='Transformed square')
plt.gca().set_aspect('equal', 'box')   # 축 비율 1:1로 설정 (왜곡 방지)
plt.axhline(0, color='gray', linewidth=0.5)  # x축 표시선
plt.axvline(0, color='gray', linewidth=0.5)  # y축 표시선
plt.legend()
plt.show()
