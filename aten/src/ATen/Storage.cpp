#include <ATen/Storage.h>
#include <ATen/Context.h>
#include <iostream>

namespace at {

Storage::Storage(at::ScalarType scalar_type, size_t size, Allocator* allocator)
    : storage_impl_(new StorageImpl(
          scalar_type,
          size,
          allocator,
          /* resizable */ false)) {}

Storage::Storage(
    at::ScalarType scalar_type,
    at::DataPtr data_ptr,
    size_t size,
    const std::function<void(void*)>& deleter)
    : storage_impl_(new StorageImpl(
          scalar_type,
          size,
          std::move(data_ptr),
          /* allocator */ nullptr,
          /* resizable */ false)) {}

Storage::~Storage() {
  if (!storage_impl_) {
    return;
  }
  storage_impl_->release();
}

} // namespace at
