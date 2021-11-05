import time
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib import cm
import pandas as pd
import numpy as np
from celluloid import Camera
import os.path
plt.style.use("seaborn")

def rosenbrock(x1: np.double, x2: np.double):
    return np.double(100 * (x2 - x1**2)**2 + (x1 -1)**2)

def drop_wave(x1: np.double, x2: np.double):
    return np.double(- (1 + np.cos(12*np.sqrt(x1**2 + x2**2))) / (0.5 * (x1**2 + x2**2) + 2))

def levy_n13(x1: np.double, x2: np.double):
    return np.double(np.sin(3*np.pi*x1)**2 + (x1-1)**2 * (1 + (np.sin(3*np.pi*x2)**2)) + (x2-1)**2 * (1 + (np.sin(2*np.pi*x2)**2)))

def ackley_function(x1: np.double, x2: np.double):
    a=np.double(20)
    b=np.double(0.2)
    c=np.double(2*np.pi)
    return np.double(-a*np.exp(-b*np.sqrt(1/2*(x1**2 + x2**2))) - np.exp(1/2*(np.cos(x1) + np.cos(x2))) + 1 + np.exp(1))

with open("data/swarm_summary.csv") as txtfile:
    SWARM_SUMMARY = pd.read_csv("data/swarm_summary.csv")

POPULATION_SIZE = SWARM_SUMMARY["population_size"].tolist()[0]
FUNCTION_NAME = SWARM_SUMMARY["function_name"].tolist()[0].replace(" ","_").lower()
X_SPAWN = SWARM_SUMMARY["x_spawn"].tolist()[0]
V_MAX = SWARM_SUMMARY["v_max"].tolist()[0]
ITERATIONS = SWARM_SUMMARY["iterations"].tolist()[0]

v_func = None

if FUNCTION_NAME.count("rosenbrock"):
    v_func = np.vectorize(rosenbrock)
if FUNCTION_NAME.count("drop_wave"):
    v_func = np.vectorize(drop_wave)
if FUNCTION_NAME.count("levy_n13"):
    v_func = np.vectorize(levy_n13)
if FUNCTION_NAME.count("ackley_function"):
    v_func = np.vectorize(ackley_function)

MIN_COST_HISTORY = pd.read_csv("data/swarm_min_cost_history.csv").iloc[:,0].to_numpy()

PARTICLE_POSITIONS = []
for i in range(POPULATION_SIZE):
    PARTICLE_POSITIONS.append(pd.read_csv(f"data/positions/history_{i}.csv").to_numpy())


x = np.linspace(0, MIN_COST_HISTORY.size-1, MIN_COST_HISTORY.size)
y = MIN_COST_HISTORY

fig = plt.figure(figsize=(14, 6))

ax1 = fig.add_subplot(1, 2, 1)
ax1.set_title(f"population_size = {POPULATION_SIZE}, v_max = [{V_MAX}, {V_MAX}], x_spawn $\in$ [-{X_SPAWN}, {X_SPAWN}]")
ax1.set_xlim(0, MIN_COST_HISTORY.size)
ax1.set_xlabel(f"Iterations")
# ax1.set_ylim(-2,2)
ax1.set_ylabel(f"Min. Cost of Swarm")

ax2 = fig.add_subplot(1, 2, 2)
ax2.set_title(f"Particles of Swarm searching for minimum")
ax2.set_xlim(-X_SPAWN, X_SPAWN)
ax2.set_xlabel("x1")
ax2.set_ylim(-X_SPAWN, X_SPAWN)
ax2.set_ylabel("x2")

x, y = np.meshgrid(np.linspace(-X_SPAWN, X_SPAWN, 1000), np.linspace(-X_SPAWN, X_SPAWN, 1000))
z = v_func(x,y)
camera = Camera(fig)

for i in range(MIN_COST_HISTORY.size):
    for j in range(i):
        ax1.plot(np.linspace(0, j-1, j), MIN_COST_HISTORY[:j], color="black")

    ax2.contourf(x, y, z, cmap=cm.winter)

    for particle_pos in PARTICLE_POSITIONS:
        ax2.scatter(particle_pos[i][0], particle_pos[i][1], color="black", marker="x")   
        if i>=2:
            x_vel = [particle_pos[i][0], particle_pos[i-1][0], particle_pos[i-2][0]]
            y_vel = [particle_pos[i][1], particle_pos[i-1][1], particle_pos[i-2][1]]
            ax2.plot(x_vel, y_vel, color="grey") 
    camera.snap()

animation = camera.animate()
animation.save(f"data/pso_animation/{FUNCTION_NAME}_p{POPULATION_SIZE}_i{ITERATIONS}_v{V_MAX}_x{X_SPAWN}.mp4", dpi=300, fps=5, writer="ffmpeg")

del fig, ax1, ax2

if not os.path.isfile(f"surface/{FUNCTION_NAME}_x{X_SPAWN}.png"):
    FUNCTION_NAME = SWARM_SUMMARY["function_name"].tolist()[0]
    x, y = np.meshgrid(np.linspace(-X_SPAWN, X_SPAWN, 1000), np.linspace(-X_SPAWN, X_SPAWN, 1000))
    z = v_func(x,y)

    fig = plt.figure()
    ax = fig.add_subplot(1,1,1, projection="3d")
    ax.plot_surface(x, y, z, cmap=cm.winter)
    ax.set_title(f"Surface of Problem Function: {FUNCTION_NAME}")
    ax.set_xlabel("x1")
    ax.set_ylabel("x2")
    FUNCTION_NAME = FUNCTION_NAME.lower().replace(" ", "_")
    fig.savefig(f"data/surface/{FUNCTION_NAME}_x{X_SPAWN}.png", dpi=300)