![Bonus 2/5 Completed](https://img.shields.io/badge/Bonus-%202%2F5%20Completed-yellow)

<h1 align="center">
	🕹️ cub3d
</h1>

<p align="center">
	<b><i>A basic 3D raycasting game engine in C, following the 42 project guidelines</i></b><br>
</p>

<h3 align="center">
	<a href="#-about-the-project">About</a>
	<span> · </span>
	<a href="#️-usage">Usage</a>
	<span> · </span>
	<a href="#-what-i-learned">What I Learned</a>
</h3>

---

## 💡 About the project

> _As a team project, Cub3D is a fundamental graphics project at 42 Wolfsburg, where the goal is to build a simple 3D game engine using raycasting techniques (similar to Wolfenstein 3D) in the C programming language. The project involves rendering a 2D map as a 3D environment, managing textures, player movement, and collision detection. It encourages a deep understanding of math for computer graphics, low-level programming, and practical problem-solving, while also fostering teamwork, communication, and collaborative development skills._

#### 🚀 Bonus
- [x] 2 out of 5 bonus features implemented (wall collision and minimap)

For more detailed information, check the [**subject of this project**](https://github.com/jonona912/42_cub3d/blob/main/cub3d_subject.pdf).

## 🛠️ Usage

### Requirements

Cub3D is written in C and requires the **`gcc` compiler**, the **MiniLibX graphics library**, and standard **C libraries** to build and run.

### Instructions

**1. Compile cub3d**

In the project directory, run:

```shell
$ make
```

**2. Run cub3d**

After compilation, launch cub3d with:

```shell
$ ./cub3d <map_file.cub>
```

**3. Playing cub3d**

- Move around the 3D world using the keyboard (WASD/arrows), and look around with the mouse (if supported).
- Explore the map, avoid walls, and enjoy the retro 3D rendering.
- Bonus features such as a minimap available.

## 📚 What I Learned

- Teamwork and efficient communication throughout a complex project
- Math for raycasting and 3D projection (trigonometry, vectors)
- Graphics programming with MiniLibX (drawing pixels, textures)
- Map parsing and validation
- Real-time game loop and event handling
- Player movement and collision detection
- Texture loading and rendering
- Implementing and debugging advanced features (minimap, animated sprites, doors, etc.)
- Robust memory management and debugging in C
