add_sources(vlelib Coordinator.cpp DynamicsComp.cpp Dynamics.cpp DynamicsDbg.cpp
  DynamicsWrapper.cpp Executive.cpp ExternalEvent.cpp 
  ExternalEventList.cpp InitEventList.cpp InternalEvent.cpp ModelFactory.cpp
  RootCoordinator.cpp Scheduler.cpp SimulatorMulti.cpp SimulatorAtomic.cpp Time.cpp View.cpp
  ViewEvent.cpp)

install(FILES AbstractDynamics.hpp Dynamics.hpp DynamicsComp.hpp DynamicsWrapper.hpp Executive.hpp
  ExternalEvent.hpp ExternalEventList.hpp InitEventList.hpp
  ObservationEvent.hpp Time.hpp DESTINATION ${VLE_INCLUDE_DIRS}/devs)

if (VLE_HAVE_UNITTESTFRAMEWORK)
  add_subdirectory(test)
endif ()
