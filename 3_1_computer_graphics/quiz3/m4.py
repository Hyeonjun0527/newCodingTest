import matplotlib.pyplot as plt

# 원본 삼각형과 변환 삼각형 좌표 배열 (다각형을 그리기 위해 첫 점을 끝에 추가)
orig_triangle = np.vstack([A, B, C, A])        # A->B->C->A로 닫힌 경로
trans_triangle = np.vstack([A_transformed, B_transformed, C_transformed, A_transformed])

plt.figure(figsize=(5, 5))
# 원본 삼각형 그리기 (파란색 점선)
plt.plot(orig_triangle[:,0], orig_triangle[:,1], 'bo--', label='원본 삼각형 (A-B-C)')
# 변환 삼각형 그리기 (빨간색 실선)
plt.plot(trans_triangle[:,0], trans_triangle[:,1], 'ro-', label="변환 삼각형 (A'-B'-C')")
# 각 꼭짓점에 점 표시
plt.scatter(orig_triangle[:-1,0], orig_triangle[:-1,1], color='blue')
plt.scatter(trans_triangle[:-1,0], trans_triangle[:-1,1], color='red')
# 꼭짓점 레이블 표시
plt.text(A[0]+0.1, A[1]-0.3, "A(0,0)", color='blue')
plt.text(B[0]+0.1, B[1]+0.1, "B(0,3)", color='blue')
plt.text(C[0]+0.1, C[1]-0.3, "C(3,0)", color='blue')
plt.text(A_transformed[0]-0.3, A_transformed[1]-0.8, "A'(0,0)", color='red')
plt.text(B_transformed[0]-0.8, B_transformed[1]+0.1, "B'(-3,1.5)", color='red')
plt.text(C_transformed[0]+0.1, C_transformed[1]+0.1, "C'(0,3)", color='red')
# 보조선 및 범례
plt.axhline(0, color='gray', linewidth=0.5)
plt.axvline(0, color='gray', linewidth=0.5)
plt.axis('equal')
plt.legend()
plt.title("Original vs. Transformed Triangle")
plt.show()
