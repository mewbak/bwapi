#pragma once
#include <unordered_set>
#include <set>

namespace BWAPI
{
  template <class T, class HashT>
  using SetContainerUnderlyingT = std::unordered_set < T, HashT >;

  /// This container is used to wrap convenience functions for BWAPI and be used as a bridge with
  /// a built-in set type.
  ///
  /// @tparam T
  ///     Type that this set contains.
  /// @tparam HashT
  ///     Hash type. Defaults to integral hashing for BWAPI usage.
  template <class T, class HashT = std::hash<int>>
  class SetContainer : public SetContainerUnderlyingT < T, HashT >
  {
  public:
    SetContainer() : SetContainerUnderlyingT<T, HashT>() {}
    SetContainer(SetContainer const &other) : SetContainerUnderlyingT<T, HashT>(other) {}
    SetContainer(SetContainer &&other) : SetContainerUnderlyingT<T, HashT>(std::forward<SetContainer>(other)) {}
    SetContainer(std::initializer_list<T> ilist) : SetContainerUnderlyingT<T, HashT>(ilist) {}
    
    template <class IterT>
    SetContainer(IterT _begin, IterT _end) : SetContainerUnderlyingT<T, HashT>(_begin, _end) {}
    
    /// Iterates the set and erases each element x where pred(x) returns true.
    ///
    /// @param pred
    ///     Predicate for removing elements.
    template<class Pred>
    void erase_if(const Pred& pred) {
      auto it = begin();
      while (it != end()) {
        if (pred(*it)) it = erase(it);
        else ++it;
      }
    };

    /// Checks if this set contains a specific value.
    ///
    /// @param value
    ///     Value to search for.
    bool contains(T const &value) const
    {
      return count(value) != 0;
    }
  };

}