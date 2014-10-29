cmake_minimum_required(VERSION 2.8)

project(NC_Assessment1)

set(sources
	"main.cpp"
	"Simulator.cpp"
	"Gillespie.cpp"
	"Reaction.cpp"
	"Simulation.cpp"
	"Simulations/Simulation1.cpp"
	"Simulations/Simulation2.cpp"
	"Simulations/Simulation3.cpp"
	)
	
set(headers
	"Simulator.h"
	"Algorithm.h"
	"Parameter.h"
	"Gillespie.h"
	"Reaction.h"
	"Simulation.h"
	"Simulations/Simulation1.h"
	"Simulations/Simulation2.h"
	"Simulations/Simulation3.h"
	)

include_directories("." "Simulations")

add_executable(${PROJECT_NAME} ${sources} ${headers})
