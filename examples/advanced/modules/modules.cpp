#include "modules.hpp"

namespace UnsafeUDF {
void (*make_udf)(Model &) = nullptr; // Define the pointers
void (*init_udf)(impl &, int) = nullptr;
void (*delete_udf)(impl **) = nullptr;
} // namespace UnsafeUDF

Model::Model() { UnsafeUDF::make_udf(*this); }

void Model::init(int a) {
  if (pimpl != nullptr) {
    return UnsafeUDF::init_udf(*pimpl, a);
  }
}
Model::~Model() {
  if (pimpl != nullptr) {
    UnsafeUDF::delete_udf(&pimpl);
  }
}
