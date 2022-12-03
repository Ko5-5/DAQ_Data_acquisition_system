#include "structs/daq_manager.h"

DAQManager* DAQManager::pInstance{nullptr};
std::mutex DAQManager::pMutex;

DAQManager* DAQManager::GetInstance() {
  std::lock_guard<std::mutex> lock(pMutex);
  if (pInstance == nullptr) {
    pInstance = new DAQManager();
  }
  return pInstance;
}
