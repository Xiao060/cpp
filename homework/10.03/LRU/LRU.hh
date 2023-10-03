#include <csetjmp>
#include <iostream>
#include <unordered_map>

using std::unordered_map;
using std::cout;
using std::endl;

struct DNode {
    DNode* prev;
    DNode* next;
    int key;
    int value; 

    DNode() 
    : prev(this) 
    , next(this)
    , key(-1)
    , value(-1) { }

    DNode(int k, int v) 
    : prev(nullptr)
    , next(nullptr)
    , key(k)
    , value(v) { }
};


class LRUCache {
public:
    LRUCache(int capacity) 
    : _head(new DNode())
    , _size(0)
    , _capacity(capacity) { }
    

    int get(int key) {
        auto it = _map.find(key);

        // 不存在
        if (it == _map.end()) {
            return -1;
        }

        // 存在则被访问, 并更新链表
        DNode* tmp = it->second;

        // 先移除
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;

        // 再添加
        tmp->prev = _head;
        tmp->next = _head->next;
        _head->next->prev = tmp;
        _head->next = tmp;

        return it->second->value;
    }
    
    void put(int key, int value) {
        auto it = _map.find(key);

        // key 已存在
        if (it != _map.end()) {
            // 修改 DNode 节点的值
            // _map[key]->value = value;
            it->second->value = value;

            // 将 DNode 移动到 链表开头
            if (it->second != _head->next) {
                DNode* tmp = it->second;

                // 先移除
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;

                // 再添加
                tmp->prev = _head;
                tmp->next = _head->next;
                _head->next->prev = tmp;
                _head->next = tmp;
            }

            return ;
        }

        // key 不存在
        DNode* tmp = new DNode(key, value);
        _map[key] = tmp;


        // 将 tmp 节点 头插
        tmp->prev = _head;
        tmp->next = _head->next;
        _head->next->prev = tmp;
        _head->next = tmp;

        ++_size;

        // 关键字数量 超出 数量, 移除掉 最早访问的(队尾元素)
        if (_size > _capacity) {
            DNode* tmp = _head->prev;

            tmp->prev->next = _head;
            _head->prev = tmp->prev; 

            --_size;
            _map.erase(_map.find(tmp->key));
        }

    }

    void print() {
        DNode* tmp = _head->next;
        while (tmp != _head) {
            cout << "(" << tmp->key << ": " << tmp->value << ")" << "  ";
            tmp = tmp->next;
        }
        cout << endl;
    }
    
private:
    unordered_map<int, DNode*> _map;
    DNode* _head;
    int _size;
    int _capacity;
};


