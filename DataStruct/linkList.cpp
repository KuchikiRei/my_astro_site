#include <cstddef>
#include <stdexcept>


<typename Elem>
class LinkList{
    private:
        struct node{
            node* prev;
            Elem data;
            node* next;
        };
        node* head;
        node* tail;
        size_t _size;

    public:
        LinkList(){
            head = new node;
            head -> next = nullptr;
            head -> prev = nullptr;
            
            tail = head;
            _size = 0;
        }

        LinkList(const LinkList &other){
            head = new node;
            head -> prev = nullptr;
            head -> next = nullptr;
            _size = other._size;
            node* cur_other = other.head -> next;
            node* cur_this = head;
            while(cur_other != nullptr){
                node * n = new node;
                
                n -> data = cur_other -> data;

                n -> prev = cur_this;
                n -> next = nullptr;
                cur_this -> next = n;
                cur_this = cur_this -> next;
                cur_other = cur_other -> next;
            }
            tail = cur_this;
        }
        ~LinkList(){
            node* temp = nullptr;
            while(head != nullptr){
                temp = head;
                head = head -> next;
                delete temp;
            }
        }
        
        LinkList& operator=(const LinkList &other){
            if(this == &other) return;
            ~LinkList();
            head = new node;
            head -> prev = nullptr;
            head -> next = nullptr;
            _size = other._size;
            node* cur_other = other.head -> next;
            node* cur_this = head;
            while(cur_other != nullptr){
                node* n = new node;
                n -> data = cur_other -> data;
                n -> prev = cur_this;
                n -> next = nullptr;
                cur_this -> next = n;
                cur_this = cur_this -> next;
                cur_other = cur_other -> next;
            }
            tail = cur_this;
            return *this;
        }

        size_t size() const {return _size;}
        bool empty() const {return _size == 0;}
        const Elem& front() const {
            if(empty())
                throw std::out_of_range("Linked List is Empty");
            return head -> next -> data;
        }
        const Elem& back() const {
            if(empty())
                throw std::out_of_range("Linked List is Empty");
            return tail -> data;
        }
};