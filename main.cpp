#include "comparison-operator-mixin.h"
#include <iostream>

struct TestClass : public bb::ComparisonOperatorMixin<TestClass> {
public:
    int id{0};

    bool operator<(const TestClass& rhs) const noexcept {
        return this->id < rhs.id;
    }
};

int main() {
    TestClass testClass1;
    testClass1.id = 100;
    TestClass testClass2;
    testClass2.id = 1000;

    std::cout << std::boolalpha << testClass2.operator<(testClass1) << "\n";
    std::cout << testClass2.operator==(testClass1) << "\n";
    std::cout << testClass2.operator!=(testClass1) << "\n";
    std::cout << testClass2.operator>(testClass1) << "\n";
    std::cout << testClass2.operator>=(testClass1) << "\n";
    std::cout << testClass2.operator<=(testClass1) << "\n";
    return 0;
}