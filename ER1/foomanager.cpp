#include "FooManager.h"

// Inicialización de la instancia estática
FooManager* FooManager::m_Inst = nullptr;

// Constructor
FooManager::FooManager() : SampleData(100) {}

// Destructor
FooManager::~FooManager() {}
