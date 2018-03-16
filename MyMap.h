//
//  MyMap.h
//  Project 4
//
//  Created by Ishan Sharma on 3/8/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#ifndef MyMap_h
#define MyMap_h

#include <string>
#include "provided.h"

using namespace std;
// MyMap.h

// Skeleton for the MyMap class template.  You must implement the first six
// member functions.

template<typename KeyType, typename ValueType>
struct Node {
    Node(KeyType key, ValueType val, Node *left, Node *right){
        m_key=key;
        m_val=val;
        m_leftChild=left;
        m_rightChild=right;
    }
    
    KeyType m_key;
    ValueType m_val;
    Node* m_leftChild;
    Node* m_rightChild;
};


template<typename KeyType, typename ValueType>
class MyMap
{
public:
    MyMap(){
        m_head=NULL;
        m_size=0;
    }
    
    ~MyMap(){
        clear();
    }
    
    void clear(){
        if (m_head == nullptr)
            return;
        Node<KeyType, ValueType> * t = m_head;
        m_Clear(t);
        
    }
    
    int size() const{
        return m_size;
    }
    
    void associate(const KeyType& key, const ValueType& value){
        if (m_head==NULL){
            m_head=new Node<KeyType, ValueType>(key, value, NULL, NULL);
            m_size++;
            return;
        }
        
        Node<KeyType, ValueType>* cur = m_head;
        
        for (;;){
            if ((cur->m_key)==key){
                cur->m_val=value;
                return;
            }
        
            
            if ((cur->m_key) < key){
                if (cur->m_leftChild == NULL){
                    cur->m_leftChild=new Node<KeyType, ValueType>(key, value, NULL, NULL);
                    m_size++;
                    return;
                }
                else{
                    cur=cur->m_leftChild;
                }
            }
            
            else if ((cur->m_key)>key){
                if (cur->m_rightChild == NULL){
                    cur->m_rightChild=new Node<KeyType, ValueType>(key, value, NULL, NULL);
                    m_size++;
                    return;
                }
                else{
                    cur=cur->m_rightChild;
                }
            }

            
        }
        
    }
    
    // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const{
        if(m_head==NULL){
            return NULL;
        }
        
        Node<KeyType, ValueType>* cur = m_head;
        const ValueType* retVal= m_Find(key, cur);
        return retVal;
    }
    
    
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyMap*>(this)->find(key));
    }
    
    // C++11 syntax for preventing copying and assignment
    MyMap(const MyMap&) = delete;
    MyMap& operator=(const MyMap&) = delete;
    
private:
    
    Node<KeyType, ValueType>* m_head;
    int m_size;
   
    void m_Clear(Node<KeyType, ValueType> * node){
        if (node== NULL){
            return;
        }
        m_Clear(node->m_leftChild);
        m_Clear(node->m_rightChild);
        delete node;
    }
    
    
    const ValueType* m_Find(const KeyType& key, Node<KeyType, ValueType>* ptr) const {
        while(ptr!= NULL){
            if (ptr->m_key==key)
                return &(ptr->m_val);
            else if (key < ptr->m_key){
                return m_Find(key, ptr->m_leftChild);
            }
            else if (key > ptr->m_key){
                return m_Find(key, ptr->m_rightChild);
            }
        }
        return NULL;
    }
};


#endif /* MyMap_h */
