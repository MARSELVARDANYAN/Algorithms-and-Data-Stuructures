#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED
#include <memory>
#include <type_traits>
#include <iterator>
#include <utility>
#include <exception>
#include <initializer_list>
#include <algorithm>

namespace My {
    template <class T, class Alloc = std::allocator<T>> class deque {
    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename std::allocator_traits<Alloc>::size_type size_type;
        typedef typename std::allocator_traits<Alloc>::difference_type difference_type;
        typedef T &reference;
        typedef const T &const_reference;
        typedef typename std::allocator_traits<Alloc>::pointer pointer;
        typedef typename std::allocator_traits<Alloc>::const_pointer const_pointer;
        class iterator;
        class const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    private:
        typedef std::allocator_traits<Alloc> vatraits;
        Alloc va;
        pointer *ab, *cb, *ae, *ce; // allocated begin, constructed begin, etc.
    public:
        deque() : deque(Alloc()) {}
        explicit deque(const Alloc &alloc) : va(alloc), ab(new pointer[1]), cb(ab), ae(ab + 1), ce(cb) {}
        deque(size_type count, const_reference value, const Alloc &alloc = Alloc()) : va(alloc),
            ab(new pointer[count << 1]), cb(ab + (count >> 1)), ae(ab + (count << 1)), ce(cb + count) {
            std::for_each(cb, ce, [&](pointer &p){
                p = vatraits::allocate(va, 1);
                vatraits::construct(va, p, value);
            });
        }
        explicit deque(size_type count, const Alloc &alloc = Alloc()) : va(alloc),
            ab(new pointer[count << 1]), cb(ab + (count >> 1)), ae(ab + (count << 1)), ce(cb + count) {
            std::for_each(cb, ce, [&](pointer &p){
                p = vatraits::allocate(va, 1);
                vatraits::construct(va, p);
            });
        }
        template <class InputIt> deque(InputIt first,
            std::conditional_t<false, typename std::iterator_traits<InputIt>::value_type, InputIt> last,
            const Alloc &alloc = Alloc()) : deque(alloc) {
            while (first != last)
                push_back(*first++);
        }
        deque(const deque &other) : va(vatraits::select_on_container_copy_construction(other.va)),
            ab(new pointer[other.size() << 1]), cb(ab + (other.size() >> 1)), ae(ab + (other.size() << 1)), ce(cb + other.size()) {
            std::for_each(cb, ce, [&](pointer &p){
                p = vatraits::allocate(va, 1);
                vatraits::construct(va, p, other[&p - cb]);
            });
        }
        deque(const deque &other, const Alloc &alloc) : va(alloc), ab(new pointer[other.size() << 1]),
            cb(ab + (other.size() >> 1)), ae(ab + (other.size() << 1)), ce(cb + other.size()) {
            std::for_each(cb, ce, [&](pointer &p){
                p = vatraits::allocate(va, 1);
                vatraits::construct(va, p, other[&p - cb]);
            });
        }
        deque(deque &&other) : va(std::move(other.va)), ab(other.ab), cb(other.cb), ae(other.ae), ce(other.ce) {}
        deque(deque &&other, const Alloc &alloc) : va(alloc), ab(other.ab), cb(other.cb), ae(other.ae), ce(other.ce) {
            if (va != other.va) {
                ab = new pointer[other.size() << 1];
                cb = ab + (other.size() >> 1);
                ae = ab + (other.size() << 1);
                ce = cb + other.size();
                std::for_each(cb, ce, [&](pointer &p){
                    p = vatraits::allocate(va, 1);
                    vatraits::construct(va, p, std::move(other[&p - cb]));
                });
            }
        }
        deque(std::initializer_list<T> init, const Alloc &alloc = Alloc()) : va(alloc), ab(new pointer[init.size() << 1]),
            cb(ab + (init.size() >> 1)), ae(ab + (init.size() << 1)), ce(cb + init.size()) {
            std::for_each(cb, ce, [&](pointer &p){
                p = vatraits::allocate(va, 1);
                vatraits::construct(va, p, std::move(init.begin()[&p - cb]));
            });
        }
        ~deque() {
            clear();
            delete []ab;
        }
        deque &operator = (const deque &other) {
            if (this == &other)
                return *this;
            if (typename vatraits::propagate_on_container_copy_assignment() && va != other.va) {
                Alloc newva(other.va);
                if (other.size() <= size()) { // ---XXXXXX--- to ---YYYY-----
                    std::for_each(cb, cb + other.size(), [&](pointer &p){
                        vatraits::destroy(va, p);
                        vatraits::deallocate(va, p, 1);
                        p = vatraits::allocate(newva, 1);
                        vatraits::construct(newva, p, other[&p - cb]);
                    });
                    erase(cbegin() + other.size(), cend());
                    ce = cb + other.size();
                } else if (other.size() <= ce - ab) { // ---XXXXXX--- to -YYYYYYYY---
                    std::for_each(ce - other.size(), cb, [&](pointer &p){
                        p = vatraits::allocate(newva, 1);
                        vatraits::construct(newva, p, other[&p - (ce - other.size())]);
                    });
                    std::for_each(cb, ce, [&](pointer &p){
                        vatraits::destroy(va, p);
                        vatraits::deallocate(va, p, 1);
                        p = vatraits::allocate(newva, 1);
                        vatraits::construct(newva, p, other[&p - (ce - other.size())]);
                    });
                    cb = ce - other.size();
                } else if (other.size() <= ae - ab) { // ---XXXXXX--- to YYYYYYYYYY--
                    auto newE = [&](pointer &p){
                        p = vatraits::allocate(newva, 1);
                        vatraits::construct(newva, p, other[&p - ab]);
                    };
                    std::for_each(ab, cb, newE);
                    std::for_each(cb, ce, [&](pointer &p){
                        vatraits::destroy(va, p);
                        vatraits::deallocate(va, p, 1);
                        p = vatraits::allocate(newva, 1);
                        vatraits::construct(newva, p, other[&p - ab]);
                    });
                    std::for_each(ce, ab + other.size(), newE);
                    cb = ab;
                    ce = ab + other.size();
                } else { // reallocation
                    pointer *nab = new pointer[other.size() << 1], *ncb = nab + (other.size() >> 1);
                    std::for_each(ncb, ncb + size(), [&](pointer &p){
                        p = cb[&p - ncb];
                        *p = other[&p - ncb];
                    });
                    std::for_each(ncb + size(), ncb + other.size(), [&](pointer &p){
                        p = vatraits::allocate(newva, 1);
                        vatraits::construct(newva, p, other[&p - ncb]);
                    });
                    cb = ncb;
                    ce = ncb + other.size();
                    delete []ab;
                    ab = nab;
                    ae = nab + (size() << 1);
                }
                va = std::move(newva);
            } else {
                if (other.size() <= size()) {
                    std::copy(other.begin(), other.end(), begin());
                    erase(cbegin() + other.size(), cend());
                    ce = cb + other.size();
                } else if (other.size() <= ce - ab) {
                    std::for_each(ce - other.size(), cb, [&](pointer &p){
                        p = vatraits::allocate(va, 1);
                        vatraits::construct(va, p, other[&p - (ce - other.size())]);
                    });
                    std::copy(other.end() - size(), other.end(), begin());
                    cb = ce - other.size();
                } else if (other.size() <= ae - ab) {
                    auto newE = [&](pointer &p){
                        p = vatraits::allocate(va, 1);
                        vatraits::construct(va, p, other[&p - ab]);
                    };
                    std::for_each(ab, cb, newE);
                    std::copy(other.begin() + (cb - ab), other.begin() + (ce - ab), begin());
                    std::for_each(ce, ab + other.size(), newE);
                    cb = ab;
                    ce = ab + other.size();
                } else {
                    pointer *nab = new pointer[other.size() << 1], *ncb = nab + (other.size() >> 1);
                    std::for_each(ncb, ncb + size(), [&](pointer &p){
                        p = cb[&p - ncb];
                        *p = other[&p - ncb];
                    });
                    std::for_each(ncb + size(), ncb + other.size(), [&](pointer &p){
                        p = vatraits::allocate(va, 1);
                        vatraits::construct(va, p, other[&p - ncb]);
                    });
                    cb = ncb;
                    ce = ncb + other.size();
                    delete []ab;
                    ab = nab;
                    ae = nab + (size() << 1);
                }
            }
            return *this;
        }
        deque &operator = (deque &&other) noexcept(typename vatraits::is_always_equal()) {
            if (this == &other)
                return *this;
            if (va == other.va) {
                clear();
                delete []ab;
                ab = other.ab;
                ae = other.ae;
                cb = other.cb;
                ce = other.ce;
                other.ab = nullptr;
            } else if (typename vatraits::propagate_on_container_move_assignment()) {
                if (other.size() <= size()) {
                    std::for_each(cb, cb + other.size(), [&](pointer &p){
                        vatraits::destroy(va, p);
                        vatraits::deallocate(va, p, 1);
                        p = vatraits::allocate(other.va, 1);
                        vatraits::construct(other.va, p, std::move(other[&p - cb]));
                    });
                    erase(cbegin() + other.size(), cend());
                    ce = cb + other.size();
                } else if (other.size() <= ce - ab) {
                    std::for_each(ce - other.size(), cb, [&](pointer &p){
                        p = vatraits::allocate(other.va, 1);
                        vatraits::construct(other.va, p, std::move(other[&p - (ce - other.size())]));
                    });
                    std::for_each(cb, ce, [&](pointer &p){
                        vatraits::destroy(va, p);
                        vatraits::deallocate(va, p, 1);
                        p = vatraits::allocate(other.va, 1);
                        vatraits::construct(other.va, p, std::move(other[&p - (ce - other.size())]));
                    });
                    cb = ce - other.size();
                } else if (other.size() <= ae - ab) {
                    auto newE = [&](pointer &p){
                        p = vatraits::allocate(other.va, 1);
                        vatraits::construct(other.va, p, std::move(other[&p - ab]));
                    };
                    std::for_each(ab, cb, newE);
                    std::for_each(cb, ce, [&](pointer &p){
                        vatraits::destroy(va, p);
                        vatraits::deallocate(va, p, 1);
                        p = vatraits::allocate(other.va, 1);
                        vatraits::construct(other.va, p, std::move(other[&p - ab]));
                    });
                    std::for_each(ce, ab + other.size(), newE);
                    cb = ab;
                    ce = ab + other.size();
                } else {
                    pointer *nab = new pointer[other.size() << 1], *ncb = nab + (other.size() >> 1);
                    std::for_each(ncb, ncb + size(), [&](pointer &p){
                        p = cb[&p - ncb];
                        *p = std::move(other[&p - ncb]);
                    });
                    std::for_each(ncb + size(), ncb + other.size(), [&](pointer &p){
                        p = vatraits::allocate(other.va, 1);
                        vatraits::construct(other.va, p, std::move(other[&p - ncb]));
                    });
                    cb = ncb;
                    ce = ncb + other.size();
                    delete []ab;
                    ab = nab;
                    ae = nab + (size() << 1);
                }
                va = std::move(other.va);
            } else {
                if (other.size() <= size()) {
                    std::move(other.begin(), other.end(), begin());
                    erase(cbegin() + other.size(), cend());
                    ce = cb + other.size();
                } else if (other.size() <= ce - ab) {
                    std::for_each(ce - other.size(), cb, [&](pointer &p){
                        p = vatraits::allocate(va, 1);
                        vatraits::construct(va, p, std::move(other[&p - (ce - other.size())]));
                    });
                    std::move(other.end() - size(), other.end(), begin());
                    cb = ce - other.size();
                } else if (other.size() <= ae - ab) {
                    auto newE = [&](pointer &p){
                        p = vatraits::allocate(va, 1);
                        vatraits::construct(va, p, std::move(other[&p - ab]));
                    };
                    std::for_each(ab, cb, newE);
                    std::move(other.begin() + (cb - ab), other.begin() + (ce - ab), begin());
                    std::for_each(ce, ab + other.size(), newE);
                    cb = ab;
                    ce = ab + other.size();
                } else {
                    pointer *nab = new pointer[other.size() << 1], *ncb = nab + (other.size() >> 1);
                    std::for_each(ncb, ncb + size(), [&](pointer &p){
                        p = cb[&p - ncb];
                        *p = std::move(other[&p - ncb]);
                    });
                    std::for_each(ncb + size(), ncb + other.size(), [&](pointer &p){
                        p = vatraits::allocate(va, 1);
                        vatraits::construct(va, p, std::move(other[&p - ncb]));
                    });
                    cb = ncb;
                    ce = ncb + other.size();
                    delete []ab;
                    ab = nab;
                    ae = nab + (size() << 1);
                }
            }
            return *this;
        }
        deque &operator = (std::initializer_list<T> other) {
            if (other.size() <= size()) {
                std::move(other.begin(), other.end(), begin());
                erase(cbegin() + other.size(), cend());
                ce = cb + other.size();
            } else if (other.size() <= ce - ab) {
                std::for_each(ce - other.size(), cb, [&](pointer &p){
                    p = vatraits::allocate(va, 1);
                    vatraits::construct(va, p, std::move(other.begin()[&p - (ce - other.size())]));
                });
                std::move(other.end() - size(), other.end(), begin());
                cb = ce - other.size();
            } else if (other.size() <= ae - ab) {
                auto newE = [&](pointer &p){
                    p = vatraits::allocate(va, 1);
                    vatraits::construct(va, p, std::move(other.begin()[&p - ab]));
                };
                std::for_each(ab, cb, newE);
                std::move(other.begin() + (cb - ab), other.begin() + (ce - ab), begin());
                std::for_each(ce, ab + other.size(), newE);
                cb = ab;
                ce = ab + other.size();
            } else {
                pointer *nab = new pointer[other.size() << 1], *ncb = nab + (other.size() >> 1);
                std::for_each(ncb, ncb + size(), [&](pointer &p){
                    p = cb[&p - ncb];
                    *p = std::move(other.begin()[&p - ncb]);
                });
                std::for_each(ncb + size(), ncb + other.size(), [&](pointer &p){
                    p = vatraits::allocate(va, 1);
                    vatraits::construct(va, p, std::move(other.begin()[&p - ncb]));
                });
                cb = ncb;
                ce = ncb + other.size();
                delete []ab;
                ab = nab;
                ae = nab + (size() << 1);
            }
            return *this;
        }
        void assign(size_type count, const_reference value) {
            if (count <= size()) {
                std::fill_n(begin(), count, value);
                erase(cbegin() + count, cend());
                ce = cb + count;
            } else if (count <= ce - ab) {
                std::for_each(ce - count, cb, [&](pointer &p){
                    p = vatraits::allocate(va, 1);
                    vatraits::construct(va, p, value);
                });
                std::fill(begin(), end(), value);
                cb = ce - count;
            } else if (count <= ae - ab) {
                auto newE = [&](pointer &p){
                    p = vatraits::allocate(va, 1);
                    vatraits::construct(va, p, value);
                };
                std::for_each(ab, cb, newE);
                std::fill(begin(), end(), value);
                std::for_each(ce, ab + count, newE);
                cb = ab;
                ce = ab + count;
            } else {
                pointer *nab = new pointer[count << 1], *ncb = nab + (count >> 1);
                std::for_each(ncb, ncb + size(), [&](pointer &p){
                    p = cb[&p - ncb];
                    *p = value;
                });
                std::for_each(ncb + size(), ncb + count, [&](pointer &p){
                    p = vatraits::allocate(va, 1);
                    vatraits::construct(va, p, value);
                });
                cb = ncb;
                ce = ncb + count;
                delete []ab;
                ab = nab;
                ae = nab + (size() << 1);
            }
        }
        template <class InputIt> std::conditional_t<false, typename std::iterator_traits<InputIt>::value_type, void>
            assign(InputIt first, InputIt last) {
            clear();
            while (first != last)
                push_back(*first++);
        }
        void assign(std::initializer_list<T> other) {
            *this = other;
        }
        Alloc get_allocator() const {
            return va;
        }
        reference at(size_type pos) {
            return (pos < size()) ? *cb[pos] : throw std::out_of_range("Out of range from std::deque::at!");
        }
        const_reference at(size_type pos) const {
            return (pos < size()) ? *cb[pos] : throw std::out_of_range("Out of range from std::deque::at!");
        }
        reference operator [] (size_type pos) {
            return *cb[pos];
        }
        const_reference operator [] (size_type pos) const {
            return *cb[pos];
        }
        reference front() {
            return **cb;
        }
        const_reference front() const {
            return **cb;
        }
        reference back() {
            return *ce[-1];
        }
        const_reference back() const {
            return *ce[-1];
        }
        iterator begin() noexcept {
            return iterator(cb);
        }
        const_iterator begin() const noexcept {
            return const_iterator(cb);
        }
        const_iterator cbegin() const noexcept {
            return const_iterator(cb);
        }
        iterator end() noexcept {
            return iterator(ce);
        }
        const_iterator end() const noexcept {
            return const_iterator(ce);
        }
        const_iterator cend() const noexcept {
            return const_iterator(ce);
        }
        reverse_iterator rbegin() noexcept {
            return make_reverse_iterator(begin());
        }
        const_reverse_iterator rbegin() const noexcept {
            return make_reverse_iterator(begin());
        }
        const_reverse_iterator crbegin() const noexcept {
            return make_reverse_iterator(crbegin());
        }
        reverse_iterator rend() noexcept {
            return make_reverse_iterator(end());
        }
        const_reverse_iterator rend() const noexcept {
            return make_reverse_iterator(end());
        }
        const_reverse_iterator crend() const noexcept {
            return make_reverse_iterator(cend());
        }
        bool empty() const noexcept {
            return cb == ce;
        }
        size_type size() const noexcept {
            return ce - cb;
        }
        size_type max_size() const noexcept {
            return vatraits::max_size(va);
        }
        void shrink_to_fit() {
            pointer *nab = new pointer[size()];
            ce = ae = std::move(cb, ce, nab);
            delete []ab;
            cb = ab = nab;
        }
        void clear() noexcept {
            std::for_each(cb, ce, [&](pointer &p){
                vatraits::destroy(va, p);
                vatraits::deallocate(va, p, 1);
            });
            ce = cb;
        }
        iterator insert(const_iterator pos, const_reference value) {
            return emplace(pos, value);
        }
        iterator insert(const_iterator pos, T &&value) {
            return emplace(pos, std::move(value));
        }
        iterator insert(const_iterator pos, size_type count, const_reference value) {
            if (0 == count) return iterator(pos.refer);
            pointer *i;
            if (count <= cb - ab) { // ---XXXXXX--- to -XYYXXXXX---
                i = std::move(cb, pos.refer, cb - count);
                cb -= count;
            } else if (size() + count <= ae - ab) { // ---XXXXXX--- to XXYYYYXXXX--
                i = std::move(cb, pos.refer, ab);
                pointer *j = std::move_backward(pos.refer, ce, ab + (count + size()));
                ce = ab + (count + size());
                cb = ab;
            } else { // reallocation required
                pointer *nab = new pointer[size() + count << 1], *ncb = nab + (size() + count >> 1);
                i = std::move(cb, pos.refer, ncb);
                ce = std::move(pos.refer, ce, i + count);
                cb = ncb;
                delete []ab;
                ab = nab;
                ae = nab + (size() + count << 1);
            }
            std::for_each(i, i + count, [&](pointer &p){
                p = vatraits::allocate(va, 1);
                vatraits::construct(va, p, value);
            });
            return iterator(i);
        }
        template <class InputIt> std::conditional_t<false, typename std::iterator_traits<InputIt>::value_type, iterator>
            insert(const_iterator pos, InputIt first, InputIt last) {
            if (first == last) return pos;
            iterator result(pos.refer - 1);
            while (first != last)
                insert(pos, *first++);
            return result;
        }
        iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
            if (0 == ilist.size()) return iterator(pos.refer);
            pointer *i;
            if (ilist.size() <= cb - ab) {
                i = std::move(cb, pos.refer, cb - ilist.size());
                cb -= ilist.size();
            } else if (size() + ilist.size() <= ae - ab) {
                i = std::move(cb, pos.refer, ab);
                std::move_backward(pos.refer, ce, ab + (ilist.size() + size()));
                ce = ab + ilist.size() + size();
                cb = ab;
            } else {
                pointer *nab = new pointer[size() + ilist.size() << 1], *ncb = nab + (size() + ilist.size() >> 1);
                i = std::move(cb, pos.refer, ncb);
                ce = std::move(pos.refer, ce, i + ilist.size());
                cb = ncb;
                delete []ab;
                ab = nab;
                ae = nab + (size() + ilist.size() << 1);
            }
            pointer *j = i;
            for (auto &v : ilist) {
                *j = vatraits::allocate(va, 1);
                vatraits::construct(va, *j++, std::move(v));
            }
            return iterator(i);
        }
        template <class ...Args> iterator emplace(const_iterator pos, Args &&...args) {
            pointer *i;
            if ((pos.refer - cb <= ce - pos.refer || ce == ae) && ab < cb) {
                // more efficient to move elements before pos, or no space at back
                i = std::move(cb, pos.refer, cb - 1);
                --cb;
                *i = vatraits::allocate(va, 1);
                vatraits::construct(va, *i, std::forward<Args>(args)...);
            } else if ((pos.refer - cb > ce - pos.refer || ab == cb) && ce < ae) {
                // more efficient to move elements after pos, or no space at front
                i = std::move_backward(pos.refer, ce, ce + 1) - 1;
                ++ce;
                *i = vatraits::allocate(va, 1);
                vatraits::construct(va, *i, std::forward<Args>(args)...);
            } else { // reallocation required
                pointer *nab = new pointer[size() << 1], *ncb = nab + (size() >> 1);
                i = std::move(cb, pos.refer, ncb);
                *i = vatraits::allocate(va, 1);
                vatraits::construct(va, *i, std::forward<Args>(args)...);
                ce = std::move(pos.refer, ce, i + 1);
                    cb = ncb;
                delete []ab;
                ab = nab;
                ae = nab + (size() << 1);
            }
            return iterator(i);
        }
        void push_back(const_reference value) {
            insert(cend(), value);
        }
        void push_back(T &&value) {
            insert(cend(), std::move(value));
        }
        template <class ...Args> void emplace_back(Args &&...args) {
            emplace(cend(), std::forward<Args>(args)...);
        }
        void push_front(const_reference value) {
            insert(cbegin(), value);
        }
        void push_front(T &&value) {
            insert(cbegin(), std::move(value));
        }
        template <class ...Args> void emplace_front(Args &&...args) {
            emplace(cbegin(), std::forward<Args>(args)...);
        }
        iterator erase(const_iterator pos) {
            vatraits::destroy(va, *pos.refer);
            vatraits::deallocate(va, *pos.refer, 1);
            if (ce - pos.refer <= pos.refer - cb) // more efficient to move elements before pos
                std::move(pos.refer + 1, ce--, pos.refer);
            else // more efficient to move elements after pos
                std::move_backward(cb++, pos.refer, pos.refer + 1);
            return iterator(pos.refer);
        }
        iterator erase(const_iterator first, const_iterator last) {
            std::for_each(first.refer, last.refer, [&](pointer &p){
                vatraits::destroy(va, p);
                vatraits::deallocate(va, p, 1);
            });
            if (ce - last.refer <= first.refer - cb) {
                std::move(last.refer, ce, first.refer);
                ce -= last - first;
            } else {
                std::move_backward(cb, first.refer, last.refer);
                cb += last - first;
            }
            return iterator(first.refer);
        }
        void pop_back() {
            erase(cend() - 1);
        }
        void pop_front() {
            erase(cbegin());
        }
        void resize(size_type count) {
            auto newE = [&](pointer &p){
                p = vatraits::allocate(va, 1);
                vatraits::construct(va, p);
            };
            if (count <= size()) // ---XXXXXX--- to ---XXXX-----
                erase(cbegin() + count, cend());
            else if (count <= ae - cb) { // ---XXXXXX--- to ---XXXXXXYY-
                std::for_each(ce, cb + count, newE);
                ce = cb + count;
            } else if (count <= ae - ab) { // ---XXXXXX--- to XXXXXXYYYY--
                pointer *i = std::move(cb, ce, ab);
                std::for_each(i, ab + count, newE);
            } else { // reallocation
                pointer *nab = new pointer[count << 1], *ncb = nab + (count >> 1), *nce = ncb + count;
                std::for_each(ncb, nce, newE);
                cb = ncb;
                ce = nce;
            }
        }
        void resize(size_type count, const_reference value) {
            auto newE = [&](pointer &p){
                p = vatraits::allocate(va, 1);
                vatraits::construct(va, p, value);
            };
            if (count <= size())
                erase(cbegin() + count, cend());
            else if (count <= ae - cb) {
                std::for_each(ce, cb + count, newE);
                ce = cb + count;
            } else if (count <= ae - ab) {
                pointer *i = std::move(cb, ce, ab);
                std::for_each(i, ab + count, newE);
            } else {
                pointer *nab = new pointer[count << 1], *ncb = nab + (count >> 1);
                std::move(cb, ce, ncb);
                std::for_each(ncb + size(), ncb + count, newE);
                cb = ncb;
                ce = ncb + count;
            }
        }
        void swap(deque &other) noexcept(typename vatraits::is_always_equal()) {
            std::swap(ab, other.ab);
            std::swap(cb, other.cb);
            std::swap(ce, other.ce);
            std::swap(ae, other.ae);
            if (typename vatraits::propagate_on_container_swap())
                swap(va, other.va);
        }
    };
    
    template <class T, class Alloc> 
    class deque<T, Alloc>::iterator {
        friend deque<T, Alloc>;
    public:
        typedef typename deque<T, Alloc>::difference_type difference_type;
        typedef T value_type;
        typedef typename deque<T, Alloc>::pointer pointer;
        typedef T &reference;
        typedef std::random_access_iterator_tag iterator_category;
    protected:
        pointer *refer;
        iterator(pointer *r) : refer(r) {}
    public:
        iterator(const iterator &other) : refer(other.refer) {}
        iterator() : refer(nullptr) {}
        iterator &operator = (const iterator &other) {
            refer = other.refer;
            return *this;
        }
        // destructor : default
        reference operator * () const {
            return **refer;
        }
        pointer operator -> () const {
            return *refer;
        }
        reference operator [] (difference_type d) const {
            return *refer[d];
        }
        iterator &operator ++ () {
            ++refer;
            return *this;
        }
        iterator operator ++ (int) {
            iterator i(*this);
            ++*this;
            return i;
        }
        iterator &operator -- () {
            --refer;
            return *this;
        }
        iterator operator -- (int) {
            iterator i(*this);
            --*this;
            return i;
        }
        friend bool operator == (const iterator &a, const iterator &b) {
            return a.refer == b.refer;
        }
        friend bool operator != (const iterator &a, const iterator &b) {
            return a.refer != b.refer;
        }
        friend bool operator < (const iterator &a, const iterator &b) {
            return a.refer < b.refer;
        }
        friend bool operator > (const iterator &a, const iterator &b) {
            return a.refer > b.refer;
        }
        friend bool operator <= (const iterator &a, const iterator &b) {
            return a.refer <= b.refer;
        }
        friend bool operator >= (const iterator &a, const iterator &b) {
            return a.refer >= b.refer;
        }
        friend iterator operator + (const iterator &i, difference_type d) {
            return iterator(i.refer + d);
        }
        friend iterator operator + (difference_type d, const iterator &i) {
            return iterator(i.refer + d);
        }
        friend iterator operator - (const iterator &i, difference_type d) {
            return iterator(i.refer - d);
        }
        iterator &operator += (difference_type d) {
            refer += d;
            return *this;
        }
        iterator &operator -= (difference_type d) {
            refer -= d;
            return *this;
        }
        friend difference_type operator - (const iterator &a, const iterator &b) {
            return a.refer - b.refer;
        }
    };
    template <class T, class Alloc> 
    class deque<T, Alloc>::const_iterator {
        friend deque<T, Alloc>;
    public:
        typedef typename deque<std::add_const_t<T>, Alloc>::difference_type difference_type;
        typedef std::add_const_t<T> value_type;
        typedef typename deque<std::add_const_t<T>, Alloc>::pointer pointer;
        typedef std::add_const_t<T> &reference;
        typedef std::random_access_iterator_tag iterator_category;
    private:
        typename deque<T, Alloc>::pointer *refer;
        const_iterator(decltype(refer) r) : refer(r) {}
    public:
        const_iterator(const const_iterator &other) : refer(other.refer) {}
        const_iterator() : refer(nullptr) {}
        const_iterator &operator = (const const_iterator &other) {
            refer = other.refer;
            return *this;
        }
        // destructor : default
        reference operator * () const {
            return **refer;
        }
        pointer operator -> () const {
            return *refer;
        }
        reference operator [] (difference_type d) const {
            return *refer[d];
        }
        const_iterator &operator ++ () {
            ++refer;
            return *this;
        }
        const_iterator operator ++ (int) {
            const_iterator i(*this);
            ++*this;
            return i;
        }
        const_iterator &operator -- () {
            --refer;
            return *this;
        }
        const_iterator operator -- (int) {
            const_iterator i(*this);
            --*this;
            return i;
        }
        friend bool operator == (const const_iterator &a, const const_iterator &b) {
            return a.refer == b.refer;
        }
        friend bool operator != (const const_iterator &a, const const_iterator &b) {
            return a.refer != b.refer;
        }
        friend bool operator < (const const_iterator &a, const const_iterator &b) {
            return a.refer < b.refer;
        }
        friend bool operator > (const const_iterator &a, const const_iterator &b) {
            return a.refer > b.refer;
        }
        friend bool operator <= (const const_iterator &a, const const_iterator &b) {
            return a.refer <= b.refer;
        }
        friend bool operator >= (const const_iterator &a, const const_iterator &b) {
            return a.refer >= b.refer;
        }
        friend const_iterator operator + (const const_iterator &i, difference_type d) {
            return const_iterator(i.refer + d);
        }
        friend const_iterator operator + (difference_type d, const const_iterator &i) {
            return const_iterator(i.refer + d);
        }
        friend const_iterator operator - (const const_iterator &i, difference_type d) {
            return const_iterator(i.refer - d);
        }
        const_iterator &operator += (difference_type d) {
            refer += d;
            return *this;
        }
        const_iterator &operator -= (difference_type d) {
            refer -= d;
            return *this;
        }
        friend difference_type operator - (const const_iterator &a, const const_iterator &b) {
            return a.refer - b.refer;
        }
    };
    template <class T, class Alloc> bool operator == (const deque<T,Alloc> &lhs, const deque<T,Alloc> &rhs) {
        return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
    }
    template <class T, class Alloc> bool operator != (const deque<T,Alloc> &lhs, const deque<T,Alloc> &rhs) {
        return !(lhs == rhs);
    }
    template <class T, class Alloc> bool operator < (const deque<T,Alloc> &lhs, const deque<T,Alloc> &rhs) {
        return std::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
    }
    template <class T, class Alloc> bool operator > (const deque<T,Alloc> &lhs, const deque<T,Alloc> &rhs) {
        return rhs < lhs;
    }
    template <class T, class Alloc> bool operator <= (const deque<T,Alloc> &lhs, const deque<T,Alloc> &rhs) {
        return !(rhs < lhs);
    }
    template <class T, class Alloc> bool operator >= (const deque<T,Alloc> &lhs, const deque<T,Alloc> &rhs) {
        return !(lhs < rhs);
    }
    template <class T, class Alloc> void swap(deque<T, Alloc> &lhs, deque<T, Alloc> &rhs) noexcept(noexcept(lhs.swap(rhs))) {
        lhs.swap(rhs);
    }
}
#endif // DEQUE_H_INCLUDED