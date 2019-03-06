/// 可并堆
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;	///
typedef __gnu_pbds::priority_queue <int, greater<int>, pairing_heap_tag> Heap;	///
erase(iterator);	/// 根据迭代器删除元素
modify(iterator, val);	/// 根据迭代器修改值
join(other);	/// 使用之后另一个会被清空
/// 其他同STL

/// 可持久化平衡树
#include <ext/rope>
using namespace __gnu_cxx;	///
/// 下标从0开始，不可以cin，可以cout
/// 由于rope的底层实现，insert，erase，get都是logn的
reverse是O(n)的，所以构造两个rope来做
push_back(x);	///    在末尾添加x
insert(pos,x);	///   在pos插入x
erase(pos,x);	///    从pos开始删除x个
replace(pos,x);	///  从pos开始换成x
substr(pos,x);	///   提取pos开始x个
at(x)/[x];	///   访问第x个元素
rope<int>*his[maxn], his[i]=new rope<char>(*his[i-1]);	/// 可持久化数组
