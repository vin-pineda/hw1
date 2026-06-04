#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

void ULListStr::push_back(const std::string& val)
{
  if (empty()) {
    Item* item = new Item();
    item->val[0] = val;
    item->last = 1;
    head_ = item;
    tail_ = item;
  }
  else if (tail_->last == ARRSIZE) {
    Item* item = new Item();
    item->val[0] = val;
    item->last = 1;
    item->prev = tail_;
    tail_->next = item;
    tail_ = item;
  }
  else {
    tail_->val[tail_->last] = val;
    tail_->last++;
  }
  size_++;
}

void ULListStr::push_front(const std::string& val)
{
  if (empty()) {
    Item* item = new Item();
    item->val[0] = val;
    item->first = 0;
    item->last = 1;
    head_ = item;
    tail_ = item;
  }
  else if (head_->first > 0) {
    head_->first--;
    head_->val[head_->first] = val;
  }
  else {
    Item* item = new Item();
    item->val[ARRSIZE - 1] = val;
    item->first = ARRSIZE - 1;
    item->last = ARRSIZE;
    item->next = head_;
    head_->prev = item;
    head_ = item;
  }
  size_++;
}

void ULListStr::pop_back()
{
  if (empty()) return;

  if (tail_->last - tail_->first == 1) {
    Item* old = tail_;
    tail_ = tail_->prev;
    if (tail_ == nullptr) {
      head_ = nullptr;
    } else {
      tail_->next = nullptr;
    }
    delete old;
  }
  else {
    tail_->last--;
  }

  size_--;
}

void ULListStr::pop_front()
{
  if (empty()) return;

  if (head_->last - head_->first == 1) {
    Item* old = head_;
    head_ = head_->next;
    if (head_ == nullptr) {
      tail_ = nullptr;
    } else {
      head_->prev = nullptr;
    }
    delete old;
  }
  else {
    head_->first++;
  }

  size_--;
}

std::string const & ULListStr::front() const
{
  if (empty()) {
    throw std::invalid_argument("empty list");
  }
  return head_->val[head_->first];
}

std::string const & ULListStr::back() const
{
  if (empty()) {
    throw std::invalid_argument("empty list");
  }
  return tail_->val[tail_->last - 1];
}

std::string* ULListStr::getValAtLoc(size_t loc, Item* cur, bool start) const
{
  if (start) {
    if (loc >= size_) return NULL;
    cur = head_;
  }

  if (cur == NULL) {
    return NULL;
  }

  size_t count = cur->last - cur->first;
  if (loc < count) {
    return &(cur->val[cur->first + loc]);
  }

  return getValAtLoc(loc - count, cur->next, false);
}


void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
