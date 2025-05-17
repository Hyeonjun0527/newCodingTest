import numpy as np
import matplotlib.pyplot as plt


square = np.array([[-2, -2, 1],
                   [-2,  2, 1],
                   [ 2,  2, 1],
                   [ 2, -2, 1]]).T

triangle = np.array([[0, 0, 1],
                     [0, 3, 1],
                     [3, 0, 1]]).T

fig, ax = plt.subplots(1,1,figsize=(9.0,8.0),sharex=True)

ax.set_xlim(-5, 5)
ax.set_ylim(-5, 5)

plt.grid(visible=True, axis='both')
plt.xticks(ticks=range(-5, 6), fontsize=20)
plt.yticks(ticks=range(-5, 6), fontsize=20)
ax.tick_params(which='both', grid_color='k', grid_alpha=0.5)
plt.scatter(0, 0, c='k')


def draw_rectangle(ractangle, c = 'b'):
    plt.plot(ractangle[0, [0, 1]], ractangle[1, [0, 1]], c=c)
    plt.plot(ractangle[0, [1, 2]], ractangle[1, [1, 2]], c=c)
    plt.plot(ractangle[0, [2, 3]], ractangle[1, [2, 3]], c=c)
    plt.plot(ractangle[0, [3, 0]], ractangle[1, [3, 0]], c=c)

def draw_triangle(triangle, c = 'b'):     
    plt.plot(triangle[0, [0, 1]], triangle[1, [0, 1]], c=c)
    plt.plot(triangle[0, [1, 2]], triangle[1, [1, 2]], c=c)
    plt.plot(triangle[0, [2, 0]], triangle[1, [2, 0]], c=c)
     

if __name__ == '__main__':

    r_deg = 30
    rotation = \
        [[np.cos(np.deg2rad(r_deg)), -np.sin(np.deg2rad(r_deg)), 0],
         [np.sin(np.deg2rad(r_deg)),  np.cos(np.deg2rad(r_deg)), 0],
         [0,                          0,                         1]]

    translation = \
        [[1, 0, 2],
         [0, 1, 2],
         [0, 0, 1]]

    scale = \
        [[1,   0, 0],
         [0, 1.5, 0],
         [0,   0, 1]]
    
    reflection = \
        [[ 1,  0, 0],
         [ 0, -1, 0],
         [ 0,  0, 1]]
    
    shear = \
        [[1, 1.5, 0], 
         [0,  1, 0], 
         [0,  0, 1]]

    scale = np.array(scale)
    rotation = np.array(rotation)
    translation = np.array(translation)
    shear = np.array(shear)
    reflection = np.array(reflection)

    # draw_triangle(triangle)
    # draw_triangle(rotation@triangle)
    draw_rectangle(square)
    draw_rectangle(shear@square)


    plt.show()


""" 

이 코드는 삼각형에 30도 회전과
 전단 변환을 적용한 후,
   그 결과를 2차원 플롯으로 보여주는 
   간단한 예제예요.

 """