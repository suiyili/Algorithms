#include "suffix_trie.hpp"

#include <stack>

#include "trie/trie_node/stem_node/end_node/end_node.hpp"
#include "trie/trie_node/leaf_node/leaf_node.hpp"
#include "trie/trie_node/stem_node/middle_node/middle_node.hpp"

namespace pattern_match::trie {
suffix_trie::suffix_trie(std::string_view pattern)
    : pattern_(pattern), root_(build_trie(pattern)) {}
bool suffix_trie::contains(std::string_view target) {
  auto found = find_node(target);
  return found;
}
size_t suffix_trie::find(std::string_view target) {
  auto found = find_node(target);
  if (!found) return pattern_.size();

  auto tail_len = get_max_depth(found);
  return pattern_.size() - (target.size() + tail_len);  
}

size_t suffix_trie::get_max_depth(trie_node* root)
{
  std::stack<decltype(root)> tail;
  tail.push(root);
  size_t max_depth = 0U;
  do {
    auto top = tail.top();
    if (auto n = top->next_child(); n)
      tail.push(n);
    else {
      if(top->is_leaf())
        max_depth = std::max(max_depth, tail.size() - 1);
      tail.pop();
    }
  } while (!tail.empty());

  return max_depth;
}

trie_node* suffix_trie::find_node(std::string_view target) {
  trie_node* cur = root_.get();
  for (char c : target) {
    if (!(cur = cur->find(c))) break;
  }
  return cur;
}

size_t suffix_trie::counts(std::string_view target) {
  size_t occurs = 0U;
  trie_node* cur = root_.get();
  for (char c : target) {
    occurs = 0U;
    if (cur = cur->find(c))
      occurs = cur->count_children();
    else
      break;
  }
  return occurs;
}
std::pair<size_t, size_t> suffix_trie::get_longest_repeat()
{
  std::stack<trie_node*> topology;
  decltype(topology.size()) max_depth = 0U;
  //first is the span between the end of repeat section to the end of pattern.
  //second is the len of repeat string.
  auto longest_repeat = std::make_pair<size_t, size_t>(0U, 0U);
  //DSF search
  topology.push(root_.get());
  do{
    auto top = topology.top();
    auto current_depth = topology.size();
    //find the max depth path with 2 children.
    //set to 0 if go to sibling branch.
    if (current_depth < max_depth)
      max_depth = 0;
    else if (top->count_children() == 2U)
      max_depth = current_depth;

    //update the longest repeat record
    if(top->is_leaf()){
      if(longest_repeat.second < max_depth){
        longest_repeat.second = max_depth;
        if (longest_repeat.first < current_depth)
          longest_repeat.first = current_depth;
      }
    }

    if (auto child = top->next_child(); child)
      topology.push(child);
    else
      topology.pop();

  } while (!topology.empty());

  //get rid of the root count;
  --longest_repeat.first;
  --longest_repeat.second;
  //make first as the start
  longest_repeat.first = pattern_.size() - longest_repeat.first;

  return longest_repeat;
}
std::pair<size_t, size_t> suffix_trie::find_longest_match(std::string_view target)
{
  auto longest_match = std::make_pair<size_t, size_t>(0, 0);
  for(size_t i = 0; i < target.size(); ++i){
    auto sub_target = target.substr(i);
    if (sub_target.size() <= longest_match.second)
      break;
    trie_node* cur = root_.get();
    size_t len = 0;
    for (auto t : sub_target) {
      if (!(cur = cur->find(t)))
        break;
      ++len;
    }

    if(longest_match.second < len){
      longest_match.first = i;
      longest_match.second = len;
    }
    
  }
  
  return longest_match;
}
trie_node_ptr suffix_trie::build_trie(std::string_view pattern) {
  auto root = std::make_unique<middle_node>('\0');

  // start from end to begin
  // so, leaf can be replaced by end node.
  auto last = pattern.end() - 1;
  for (auto start = pattern.rbegin(); start != pattern.rend(); ++start) {
    trie_node* current = root.get();
    for (auto cur = start.base(); cur != pattern.end(); ++cur)
      current = add_child(*cur, cur == last, current);
  }

  return std::move(root);
}
trie_node* suffix_trie::add_child(char child, bool is_end, trie_node* parent) {
  if (auto n = parent->find(child)) {
    if (n->is_leaf())  // replace it
      return parent->insert(std::make_unique<end_node>(child));
    else
      return n;
  } else {
    trie_node_ptr tn;
    if (is_end)
      tn = std::make_unique<leaf_node>(child);
    else
      tn = std::make_unique<middle_node>(child);

    return parent->insert(std::move(tn));
  }
}

}  // namespace pattern_match::trie