import numpy as np
import matplotlib.pyplot as plt

# Define the vertices of the original square (Figure a).
# Corners are given in order (clockwise or counterclockwise) for plotting.
square = np.array([(-1,  1),  # top-left corner
                   ( 1,  1),  # top-right corner
                   ( 1, -1),  # bottom-right corner
                   (-1, -1)]) # bottom-left corner

# Repeat the first point at the end to close the square shape when plotting
square_closed = np.vstack([square, square[0]])

# Calculate the transformation matrix A that maps the square to the parallelogram.
# We determine A by seeing how it maps the unit basis vectors:
#   A * (1,0) -> (3, 0)    (horizontal axis scaled by 3)
#   A * (0,1) -> (1.5, 3)  (vertical axis mapped to the slanted side vector)
A = np.array([[3.0, 1.5],
              [0.0, 3.0]])

# Apply the linear transformation A to each vertex of the square to get the parallelogram's vertices.
parallelogram = square_closed.dot(A.T)  # multiply each point (row vector) by A^T

# Plot the original square
plt.figure(figsize=(6, 6))
plt.plot(square_closed[:, 0], square_closed[:, 1], 'o-', color='blue', label='Original Square')
# Plot the transformed parallelogram
plt.plot(parallelogram[:, 0], parallelogram[:, 1], 'o-', color='red', label='Transformed Parallelogram')

# Add a grid for reference
plt.grid(True)
# Use equal scaling on both axes so the square isn't distorted (square looks like a square)
plt.gca().set_aspect('equal', adjustable='box')
# Set axis limits for a clear view of both shapes
plt.xlim(-5, 5)
plt.ylim(-4, 4)

# Label axes and add a title
plt.xlabel('X coordinate')
plt.ylabel('Y coordinate')
plt.title('Square (blue) transformed to Parallelogram (red)')

# Add a legend to identify the two shapes
plt.legend()

# Print out the transformation matrix A
print("Transformation matrix A that maps the square to the parallelogram:")
print(A)

# Display the plot
plt.show()
