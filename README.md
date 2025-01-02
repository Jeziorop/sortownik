# Sorting Algorithms Visualization Project

## Overview

This project provides a dynamic and interactive way to understand and visualize the inner workings of popular sorting algorithms. Sorting algorithms are fundamental in computer science, and visualizations make it easier to grasp their behavior and efficiency.

## Demonstration

Watch the video below for a demonstration of how the visualization works:

<video controls width="720">
  <source src="demonstration.mp4" type="video/mp4">
  Your browser does not support the video tag. Please download the video to view it.
</video>

### Supported Algorithms

- Bubble Sort
- Insertion Sort
- Quick Sort
- Heap Sort
- Bogo Sort
- Merge Sort
- Comb Sort
- Shell Sort
- Dumb Sort

## How It Works

The visualization is built using C++ with the help of libraries such as:
- **SFML**: For graphical visualizations.
- **thread**: Every visualization is run on it's own thread.

The program takes a random data set as input and dynamically visualizes the sorting process, providing insights into number of swaps and comparisons.
