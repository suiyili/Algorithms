#include <functional>
#include <memory_resource>
#include <unordered_map>
#include <vector>

namespace graph::generic {

template <typename T> concept comparable = requires(T &t1, T &t2) {
  t1 <=> t2;
};

template <typename T> requires comparable<T> class priority_queue final {
public:
  priority_queue() noexcept;
  void push(const T *key) noexcept;
  const T *pop() noexcept;
  void update(const T *key) noexcept;

private:
  std::size_t append(const T *key);
  bool compare_exchange(std::size_t lhs, std::size_t rhs);
  static std::size_t find_parent(std::size_t child);
  void swim(std::size_t id);
  std::pmr::vector<const T *> heap_;
  std::pmr::unordered_map<const T *, std::size_t> indices_;
};

} // namespace graph::generic