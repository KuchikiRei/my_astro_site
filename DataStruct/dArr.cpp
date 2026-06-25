#include <cstddef>
#include <stdexcept>

const size_t DEFAULT = 10;

template <typename Elem> class DynamicArray {
private:
  size_t _size;
  size_t _capacity;
  Elem *_data;

  void _expand() {
    size_t newCapacity = (_capacity == 0) ? 1 : _capacity * 2;
    Elem *data = new Elem[newCapacity];
    for (size_t i = 0; i < _size; i++) {
      data[i] = _data[i];
    }
    delete[] _data;
    _data = data;
    _capacity = newCapacity;
  }

public:
  // 构造函数
  DynamicArray() : _size(0), _capacity(DEFAULT), _data(new Elem[DEFAULT]) {}
  DynamicArray(size_t capacity)
      : _size(0), _capacity(capacity), _data(new Elem[capacity]) {}
  // 构造拷贝函数
  DynamicArray(const DynamicArray &other) {
    _size = other._size;
    _capacity = other._capacity;
    _data = new Elem[_capacity];
    for (size_t i = 0; i < _size; i++)
      _data[i] = other._data[i];
  }
  ~DynamicArray() { delete[] _data; }

  // 实现队尾元素的添加
  void push_back(Elem elem) {
    if (_size == _capacity)
      _expand();
    _data[_size] = elem;
    _size++;
  }

  // 实现队尾元素的删除
  void pop_back() {
    if (_size == 0)
      return;
    _size--;
  }

  // 使用 operator 关键字，重载 [] 符号，实现对输入下标的访问
  Elem &operator[](size_t idx) { return _data[idx]; }
  const Elem &operator[](size_t idx) const { return _data[idx]; }
  // 使用 operator 关键字，重载 = 符号，实现通过已有数组的复制操作
  DynamicArray &operator=(const DynamicArray &other) {
    if (this == &other)
      return *this;
    delete[] _data;
    _size = other._size;
    _capacity = other._capacity;
    _data = new Elem[_capacity];
    for (size_t i = 0; i < _size; i++)
      _data[i] = other._data[i];
    return *this;
  }

  // 传参引用 实现对输入下标合法性的判断
  Elem &at(size_t idx) {
    if (idx >= _size)
      // 当出现不合法的情况下，使用 throw 抛出异常，并终止当前函数的执行
      throw std::out_of_range("No that position!");
    return _data[idx];
  }
  const Elem &at(size_t idx) const {
    if (idx >= _size)
      throw std:: : out_of_range("No that position");
    return _data[idx];
  }

  // 返回当前元素个数
  // 使用 const 来修饰隐含的传递参数
  size_t size() const { return _size; }

  // 返回当前的最大容量
  size_t capacity() const { return _capacity; }

  // 返回当前数组是否为空
  bool empty() const { return (_size == 0) ? true : false; }

  // 输出一个元素
  Elem &front() {
    if (empty())
      throw std::out_of_range("DynamicArray is Empty");
    return _data[0];
  }
  // 适应 const
  const Elem &front() const {
    if (empty())
      throw std::out_of_range("DynamicArray is Empty");
    return _data[0];
  }

  // 输出一个元素
  Elem &back() {
    if (empty())
      throw std::out_of_range("DynamicArray is Empty");
    return _data[_size - 1];
  }
  const Elem &back() const {
    if (empty())
      throw std::out_of_range("DynamicArray is Empty");
    return _data[_size - 1];
  }

  // 清空 DynamicArray 操作
  void clear() { _size = 0; }

  // 在指定位置插入元素
  void insert(size_t pos, Elem val) {
    if (pos > _size)
      throw std::out_of_range("Illegal location");
    if (_size == _capacity)
      _expand();
    if (pos == _size) {
      push_back(val);
      return;
    }
    for (size_t i = _size++; i > pos; i--)
      _data[i] = _data[i - 1];
    _data[pos] = val;
  }

  // 在指定位置删除元素
  void erase(size_t pos) {
    if (pos >= _size)
      throw std::out_of_range("Illegal location");
    if (pos == _size - 1) {
      pop_back();
      return;
    }
    --_size;
    for (size_t i = pos; i < _size; i++)
      _data[i] = _data[i + 1];
  }
};
