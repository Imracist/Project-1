SimCity Simulation Project

Description
This project simulates city growth using a grid-based system. It handles residential, industrial, and commercial zones while managing pollution and analyzing specified areas.

Features

Reads configuration files for the simulation setup.
Simulates growth based on predefined rules for different zone types.
Allows user interaction to step through the simulation.
Outputs total populations and pollution levels after the simulation.

Files

main.cpp: The entry point for the simulation.
config.cpp and config.h: Handles configuration file parsing.
region.cpp and region.h: Manages the grid of cells representing the city.
simulation.cpp and simulation.h: Controls the simulation flow.

Requirements

A C++ compiler

Steps

Open a terminal and navigate to the project directory. 

Use the 'make' command to compile the program. Ensure you have a Makefile in the project directory.

It will generate 'simcity'

Run the program by typing ./simcity

When prompted, enter the configuration file name (e.g., config1.txt).

Follow the on-screen instructions to step through the simulation. You can press Enter to continue to the next step or q to quit the simulation.

Make sure your configuration file (config1.txt) follows this format:

region1.csv
20
1

Authors
Jade Klaichang - jadeklaichang@my.unt.edu