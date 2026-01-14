#pragma once
#include <vector>
#include <string>
#include <functional>
#include <iostream>

#define TEST(suite, name) \
    void test_##suite##_##name(); \
    namespace { \
        struct test_##suite##_##name##_reg : public TestRegistry::Registrar { \
            test_##suite##_##name##_reg() { \
                TestRegistry::instance().registerTest(#suite "." #name, test_##suite##_##name); \
            } \
        }; \
        static test_##suite##_##name##_reg test_##suite##_##name##_reg_instance; \
    } \
    void test_##suite##_##name()

#define ASSERT_EQ(expected, actual) \
    do { \
        auto&& exp = (expected); auto&& act = (actual); \
        if (!((exp) == (act))) { \
            throw TestFailure(#expected " == " #actual " failed: " \
                + std::to_string(exp) + " != " + std::to_string(act)); \
        } \
    } while(0)

#define ASSERT_TRUE(cond) \
    do { \
        if (!(cond)) { \
            throw TestFailure(#cond " failed"); \
        } \
    } while(0)

#define ASSERT_FALSE(cond) ASSERT_TRUE(!(cond))

#define EXPECT_EQ(expected, actual) \
    do { \
        auto&& exp = (expected); auto&& act = (actual); \
        if (!((exp) == (act))) { \
            std::cerr << "EXPECT_EQ failed: " << #expected << " (" \
                << exp << ") != " << #actual << " (" << act << ")\n"; \
        } \
    } while(0)

#define ASSERT_NO_THROW(code) do { \
    try { code;\
        throw _TestFailure("success"); \
     } catch (_TestFailure &t) { \
    } \
    catch (...) { \
        throw TestFailure(#code " throwed exception "); \
    } \
} while(0)

#define ASSERT_THROW(code) do { \
    try { code;\
        throw _TestFailure("success"); \
     } catch (_TestFailure &t) { \
        throw TestFailure(#code " didn't throwed any exception "); \
    } catch(...) {\
    \
    }\
} while(0)


class TestFailure : public std::runtime_error {
public:
    TestFailure(const std::string& msg) : std::runtime_error(msg) {}
};

class _TestFailure : public std::runtime_error {
public:
    _TestFailure(const std::string& msg) : std::runtime_error(msg) {}
};

class TestRegistry {
public:
    using TestFunc = std::function<void()>;
    
    struct Registrar {
        std::string name_;
        TestFunc func_;
        Registrar() = default;
        Registrar(const std::string& name, TestFunc func)
            : name_(name), func_(std::move(func)) {}
    };
    
    static TestRegistry& instance() {
        static TestRegistry reg;
        return reg;
    }
    
    void registerTest(const std::string& name, TestFunc func) {
        tests_.emplace_back(name, std::move(func));
    }
    
    std::vector<Registrar>& tests() { return tests_; }
    
private:
    TestRegistry() = default;
    std::vector<Registrar> tests_;
};

class TestRunner {
public:
    static int runAll() {
        auto& reg = TestRegistry::instance();
        std::cout << "Running " << reg.tests().size() << " tests...\n\n";
        
        size_t passed = 0, failed = 0;
        
        for (auto& test : reg.tests()) {
            try {
                std::cout << "Test: " << test.name_ << " ... ";
                test.func_();
                std::cout << "PASS\n";
                ++passed;
            } catch (const TestFailure& e) {
                std::cout << "FAIL\n";
                std::cout << "  " << e.what() << "\n";
                ++failed;
            } catch (...) {
                std::cout << "CRASH\n";
                ++failed;
            }
        }
        
        std::cout << "\nPASSED: " << passed 
                  << " FAILED: " << failed << "\n";
        
        return failed > 0 ? 1 : 0;
    }
    
    static int run(const std::string& filter) {
        auto& reg = TestRegistry::instance();
        std::cout << "Running tests matching '" << filter << "'...\n\n";
        
        size_t passed = 0, failed = 0;
        bool any_matched = false;
        
        for (auto& test : reg.tests()) {
            if (test.name_.find(filter) != std::string::npos) {
                any_matched = true;
                try {
                    std::cout << "Test: " << test.name_ << " ... ";
                    test.func_();
                    std::cout << "PASS" << std::endl;
                    ++passed;
                } catch (const TestFailure& e) {
                    std::cout << "FAIL" << std::endl;
                    std::cout << "  " << e.what() << std::endl;
                    ++failed;
                }
                catch (...) {
                    std::cout << "CRASH" << std::endl;
                    ++failed;
                    throw;
                }
            }
        }
        
        if (!any_matched) {
            std::cout << "No tests matched '" << filter << "'\n";
            return 1;
        }
        
        return failed > 0 ? 1 : 0;
    }
};


#define ENTRY_POINT() \
int main(int argc, char* argv[]) {\
    if (argc > 1) {\
        return TestRunner::run(argv[1]);\
    }\
    return TestRunner::runAll();\
}
