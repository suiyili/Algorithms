#include <functional>
#include <memory_resource>
#include <unordered_map>
#include <vector>

namespace graph::generic {

template <typename T> concept comparable = requires(T &t1, T &t2) {
  t1 <=> t2;
};

template <comparable T> class priority_queue final {
public:
  priority_queue() noexcept;
  void push(T *key) noexcept;
  T *pop() noexcept;
  void update(T *key) noexcept;

private:
  std::size_t append(T *key) noexcept;
  bool compare(std::size_t lhs, std::size_t rhs) noexcept;
  void exchange(std::size_t lhs, std::size_t rhs) noexcept;
  bool compare_exchange(std::size_t lhs, std::size_t rhs) noexcept;
  static std::size_t find_parent(std::size_t child) noexcept;
  static std::pair<std::size_t, std::size_t> get_children(std::size_t parent) noexcept;
  T* remove_top() noexcept;
  std::size_t find_top_child(std::size_t parent) noexcept;
  bool swim(std::size_t id) noexcept;
  bool sink(std::size_t id) noexcept;

  std::pmr::vector<T *> heap_;
  std::pmr::unordered_map<T *, std::size_t> indices_;
};

} // namespace graph::generic