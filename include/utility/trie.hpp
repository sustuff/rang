#ifndef RANG_INCLUDE_UTILITY_TRIE_HPP_
#define RANG_INCLUDE_UTILITY_TRIE_HPP_

#include <QHash>

template <typename Element, typename Value>
class Trie {
  public:
    struct Node {
        Node* visit_or_create(const Element& el) {
          auto& node = m_next[el];
          if (node == nullptr) {
            node = new Node;
          }
          return node;
        }
        Node* visit_or_create(Element&& el) {
          auto& node = m_next[el];
          if (node == nullptr) {
            node = new Node;
          }
          return node;
        }

        Node* visit_or_nullptr(const Element& el) {
          if (auto it = m_next.find(el); it != m_next.end()) {
            return *it;
          }
          return nullptr;
        }

        Value& value() {
          return m_value.value();
        }

        bool hasValue() {
          return m_value.has_value();
        }

        template <typename... Args>
        void emplace(Args&&... args) {
          m_value.emplace(std::forward<Args>(args)...);
        }

      private:
        QHash<Element, Node*> m_next;
        std::optional<Value> m_value;
    };

    template <typename InputIterator>
    void addSequence(InputIterator begin, InputIterator end, const Value& value) {
      Node* node = head();
      for (auto it = begin; it != end; ++it) {
        node = node->visit_or_create(*it);
      }
      node->emplace(value);
    }

    Node* head() {
      return &m_head;
    }

  private:
    Node m_head;
};

#endif  // RANG_INCLUDE_UTILITY_TRIE_HPP_
