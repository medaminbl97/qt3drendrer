# Qt3DRenderer

Qt3DRenderer is a desktop application built with Qt and C++ for rendering and visualizing 3D models. The application uses CPU-based rendering to display 3D objects, relying on mathematical principles from linear algebra and geometry.

## Mathematical Principles

- **Linear Algebra:** 3D transformations are performed using matrices and vectors.
- **Projection:** 3D coordinates are projected onto a 2D screen using orthographic projection techniques.
- **Geometry:** Models are represented as collections of vertices, edges, and faces, with calculations for normals and surface properties.
- **Lighting:** Basic lighting calculations use dot products and vector math to simulate light interaction with surfaces.

## Rendering

All rendering is performed on the CPU, without using GPU acceleration. The application computes transformations, projections, and rasterization in C++ code, making it suitable for understanding the fundamentals of 3D graphics.

![Alt text](image.png?raw=true "")

## Features

- Load and display 3D models (OBJ format supported)
- Interactive 3D view with rotation, zoom, and pan
- Multiple model types: Cube, cone, Plane, Polygon, etc.
- Tabbed interface for managing multiple models
- Dialogs for model selection

## Principles

- **Modularity:** The codebase is organized into separate classes for models, views, dialogs, and utilities, making it easy to extend and maintain.
- **User Experience:** The application focuses on providing an intuitive and responsive interface for 3D visualization.
- **Extensibility:** Support for adding new model types and features with minimal changes.

## Getting Started

1. Build the project using CMake and Qt.
2. Run the executable (`qt3drenderer.exe`).
3. Use the UI to load models and explore 3D rendering features.

## File Structure

- `src/` - Source code files
- `inc/` - Header files
- `icons/` - UI icons
- `build/` - Build output
- `cube.obj`, `cone.obj` - Sample 3D models

## Requirements

- Qt 5 or higher
- CMake
- C++ compiler

## License

This project is open source and available under the MIT License.
