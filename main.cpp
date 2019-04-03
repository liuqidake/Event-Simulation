
#include "EventSimulator.h"

int main(int argc, char* argv[]) {
      assert(argc ==4);
      EventSimulation eventSimulation = EventSimulation(std::stod(argv[1]), std::stod(argv[2]), std::stoi(argv[3]));
      eventSimulation.eventSimulation();
}