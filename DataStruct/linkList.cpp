#include <cstddef>
#include <stdexcept>

template <typename Elem> class LinkList {
private:
  struct node {
    node *prev;
    Elem data;
    node *next;
  };
  node *head;
  node *tail;
  size_t _size;

public:
  LinkList() {
    head = new node;
    head->next = nullptr;
    head->prev = nullptr;
    tail = head;
    _size = 0;
  }

  LinkList(const LinkList &other) {
    head = new node;
    head->prev = nullptr;
    head->next = nullptr;
    _size = other._size;
    node *cur_other = other.head->next;
    node *cur_this = head;
    while (cur_other != nullptr) {
      node *n = new node;

      n->data = cur_other->data;

      n->prev = cur_this;
      n->next = nullptr;
      cur_this->next = n;
      cur_this = cur_this->next;
      cur_other = cur_other->next;
    }
    tail = cur_this;
  }

  void clear() {
    node *temp = nullptr;
    while (head != nullptr) {
      temp = head;
      head = head->next;
      delete temp;
    }
  }

  ~LinkList() { clear(); }

  LinkList &operator=(const LinkList &other) {
    if (this == &other)
      return;
    clear();
    head = new node;
    head->prev = nullptr;
    head->next = nullptr;
    _size = other._size;
    node *cur_other = other.head->next;
    node *cur_this = head;
    while (cur_other != nullptr) {
      node *n = new node;
      n->data = cur_other->data;
      n->prev = cur_this;
      n->next = nullptr;
      cur_this->next = n;
      cur_this = cur_this->next;
      cur_other = cur_other->next;
    }
    tail = cur_this;
    return *this;
  }

  size_t size() const { return _size; }
  bool empty() const { return _size == 0; }
  const Elem &front() const {
    if (empty())
      throw std::out_of_range("Linked List is Empty");
    return head->next->data;
  }
  const Elem &back() const {
    if (empty())
      throw std::out_of_range("Linked List is Empty");
    return tail->data;
  }

  void push_back(const Elem &data) {
    node *n = new node;
    n->data = data;
    n->next = nullptr;
    n->prev = tail;
    tail->next = n;
    tail = n;
    _size++;
  }

  void push_front(const Elem &data) {
    node *n = new node;
    n->data = data;
    n->prev = head;
    if (empty()) {
      n->next = nullptr;
      tail = n;
    } else {
      n->next = head->next;
      head->next->prev = n;
    }
    _size++;
    head->next = n;
  }

  void pop_back() {
    if (empty())
      throw std::out_of_range("Linked List is Empty");
    tail->prev->next = nullptr;
    node *temp = tail;
    tail = temp->prev;
    delete temp;
    _size--;
  }
  void pop_front() {
    if (empty())
      throw std::out_of_range("Linked List is Empty");
    node *temp = head->next;
    if (_size == 1) {
      head->next = nullptr;
      tail = head;
    } else {
      head->next = temp->next;
      temp->next->prev = head;
    }
    delete temp;
    _size--;
  }
  Elem &at(size_t idx) {
    if (idx > _size)
      throw std::out_of_range("No target location");
    if (idx == _size)
      return tail->data;
    node *cur = head->next;
    for (int i = 1; i < idx; i++)
      cur = cur->next;
    return cur->data;
  }
  const Elem &at(size_t idx) const {
    if (idx > _size)
      throw std::out_of_range("No target location");
    if (idx == _size)
      return tail->data;
    node *cur = head->next;
    for (int i = 1; i < idx; i++)
      cur = cur->next;
    return cur->data;
  }
  class iterator {
  private:
    node *current;

  public:
    iterator()
  };
};
