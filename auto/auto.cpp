#include <iostream>
#include <vector>
#include <iterator>


/**
 * auto x = foo: 复制一个变量给 x
 * auto &x = foo: 获取 foo 的引用, 以便修改 foo的状态
 * auto const &x = foo: 获取foo 的引用,且只读
 * @return
 */
int main()
{
    std::vector<std::string> v = {"abc", "cba", "jkl"};

    // 不使用 auto遍历 vector
    std::vector<std::string>::iterator _it;
    for (_it = v.begin(); _it != v.end(); _it++) {
        std::cout << *_it << std::endl;
    }

    // 使用auto
    for (auto it = v.begin(); it != v.end(); it++) {
        std::cout << *it << std::endl;
    }
    // 使用 for-each + auto
    // 若 auto 后带上&,则意味着auto变量本身可能会被修改状态
    for (auto &it : v) {
        std::cout << it << std::endl;
    }
}