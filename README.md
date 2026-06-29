# Geometry Pro | Modern UI

A 2D geometry simulation application built in C++ using the Raylib library. This project showcases Advanced Object-Oriented Programming (OOP) principles, custom operator overloading, and a modern dark-themed graphical user interface (GUI) to manipulate geometric shapes in real-time.

---

## Features

* **Interactive Canvas:** Visual rendering of geometric primitives (Points and Line Segments) on a dynamic grid with smooth anti-aliased rendering and custom glow effects.
* **Real-time Control:** Dedicated sidebar for manual coordinate inputs and dynamic geometric transformations[cite: 3].
* **Live Property Calculations:** Instant feedback on mathematical properties like line segment length and midpoint coordinates[cite: 3].
* **Custom OOP Framework:** Built upon highly encapsulated `Point` and `LineSegment` classes featuring extensive operator overloading[cite: 1, 2, 4, 5].

---

## Deep Dive: Mathematical and OOP Logic

The core backend architecture demonstrates advanced C++ features:

### Advanced Operator Overloading
* `++` / `--` (Prefix & Postfix): Overloaded to shift points and whole line segments dynamically across the coordinate space[cite: 1, 4].
* `[]` (Subscript Operator): Accesses the start (`index 0`) or end (`index 1`) points of a line segment smoothly[cite: 1].
* `||` (Distance Operator): Overloaded as a non-member friend function between two `Point` objects to compute the Euclidean distance[cite: 4, 5]:
  $$\text{Distance} = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}$$
* `<<` / `>>` (Stream I/O): Integrated custom console input and formatted output formatting for all primitives[cite: 1, 4].

### Memory Management and Tracking
* **Deep Copying:** Explicit copy constructors and assignment operators (`operator=`) prevent shallow copy bugs by safely duplicating dynamic `Point` allocations within `LineSegment`[cite: 1, 2].
* **Static Lifetime Tracking:** A static counter inside the `Point` class tracks active object instances in memory at runtime[cite: 4, 5].

---

## UI Architecture (Powered by Raylib)

The frontend boasts a modern dark user experience featuring:
* **Sidebar Controls:** Fluid interactive text input fields tracking numerical filters and custom mouse interactions[cite: 3].
* **Custom Buttons:** Rendered using smooth rounded corner metrics (`DrawRectangleRounded`) built with responsive hover and click detection[cite: 3].
* **Hardware Accelerated Graphics:** Uses multi-sample anti-aliasing hints (`FLAG_MSAA_4X_HINT`) paired with automated scissor boundaries (`BeginScissorMode`) to isolate rendering regions safely[cite: 3].

---

## Getting Started

### Prerequisites
* A C++17 compatible compiler (e.g., GCC, MSVC, Clang)
* Raylib library installed on your system[cite: 3]

### Compilation Example (GCC)
```bash
g++ main.cpp Point.cpp LineSegment.cpp -o GeometryPro -lraylib -lopengl32 -lgdi32 -lwinmm