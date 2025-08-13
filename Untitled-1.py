# %%
import numpy as np
import matplotlib.pyplot as plt
import pickle

# %%
rng = np.random.default_rng(15461)

# %%
R = 3
n_points = 2000
points = rng.normal(0, 1, (n_points, 3))
points /= np.linalg.norm(points, axis=1)[:, None]
points *= R

# %%
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')

ax.scatter(points[:, 0], points[:, 1], points[:, 2], alpha=0.6)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('3D Scatterplot of Points')

# Set aspect ratio equal
ax.set_box_aspect([1, 1, 1])  # Equal aspect ratio along all axes

with open('figures/random_normal.pkl', 'wb') as f:
	pickle.dump(fig, f)

plt.show()

# %%

n_theta = 50
n_phi = 50
theta = np.linspace(0, np.pi, n_theta)
phi = np.linspace(0, 2*np.pi, n_phi)
theta, phi = np.meshgrid(theta, phi)

x = np.vstack(((np.sin(theta)*np.cos(phi)).flatten(), (np.sin(theta)*np.sin(phi)).flatten(), np.cos(theta).flatten())).T

print(x.shape)

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')

ax.scatter(x[:, 0], x[:, 1], x[:, 2], alpha=0.6)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('3D Scatterplot of Points')

# Set aspect ratio equal
ax.set_box_aspect([1, 1, 1])  # Equal aspect ratio along all axes

with open('figures/grid_uniform.pkl', 'wb') as f:
	pickle.dump(fig, f)

plt.show()

# %%

theta = np.acos(1 - 2*np.linspace(0, 1, n_theta))
phi = np.linspace(0, 2*np.pi, n_phi)
theta, phi = np.meshgrid(theta, phi)

x = np.vstack(((np.sin(theta)*np.cos(phi)).flatten(), (np.sin(theta)*np.sin(phi)).flatten(), np.cos(theta).flatten())).T

print(x.shape)

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')

ax.scatter(x[:, 0], x[:, 1], x[:, 2], alpha=0.6)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('3D Scatterplot of Points')

# Set aspect ratio equal
ax.set_box_aspect([1, 1, 1])  # Equal aspect ratio along all axes

with open('figures/grid_sine.pkl', 'wb') as f:
	pickle.dump(fig, f)

plt.show()

# %%

theta = np.acos(1 - 2*rng.random(n_points))
phi = 2*np.pi * rng.random(n_points)

x = np.vstack(((np.sin(theta)*np.cos(phi)).flatten(), (np.sin(theta)*np.sin(phi)).flatten(), np.cos(theta).flatten())).T

print(x.shape)
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')

ax.scatter(x[:, 0], x[:, 1], x[:, 2], alpha=0.6)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('3D Scatterplot of Points')

# Set aspect ratio equal
ax.set_box_aspect([1, 1, 1])  # Equal aspect ratio along all axes

with open('figures/random_sine.pkl', 'wb') as f:
	pickle.dump(fig, f)

plt.show()