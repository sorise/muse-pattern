### [CRTP 奇异递归模板模式](#)

**介绍**：CRTP(**C**uriously **R**ecurring **T**emplate **P**attern)，是一种实现静态多态的C++模板编程技巧。其基本做法是将派生类作为模板参数传递给它自己的基类。

----

1. 基类是一个模板类
2. 派生类继承该基类时，将派生类自身作为模板参数传递给基类
3. 基类方法可以通过模板继承的方式来访问继承类的成员

但CRTP是通过模板的方式，由子类继承父类，但父类的模板参数又是子类的一种奇怪的方式。

```cpp
// CRTP idioms
template <typename Derived>
class Base {
// 可以使用模板参数Derived访问派生类中的成员
};

class Derived : public Base<Derived> {
// ...
};

template<typename T>
class DerivedTemplate : public Base<DerivedTemplate<T>> {
// ...
```

在上面的代码中，基类Base是一个模板类，派生类Derived继承自基类，继承时派生类把自己作为模板参数传递给了基类。



这个技术应用主要也是在模板的元编程中的实现的，在c++中，好多的技术都是为了元编程服务的，另外就是在一些需要实现编译期（静态）多态的情况下使用。在C++11中的std::enable_shared_from_this就是这个技术的一个实际应用的例子。



### 1. 静态多态

父类指针、引用可以不通过虚函数就访问到子类的方法，看上去和普通的继承没啥区别，但是最大的区别在于**不再运行时才绑定**。

```cpp
template <class T>
class Base
{
public:
    void Display()
    {
        static_cast<T*>(this)->Data();
    }

    static void Call()
    {
        T::Call();
    }
};

class Derived : public Base<Derived>
{
public:
    void Data() { std::cout << "Derived function :Data()" << std::endl; };
    static void Call() { std::cout << "Derived function :Call()" << std::endl; };
};

int main()
{
    Derived d;
    Base<Derived> * base_ptr = &d;
    base_ptr->Display();
    base_ptr->Call();
};
```



### 2. 类似于智能指针的使用

类似于引用计数的功能！

```cpp
template <typename T>
struct refcounter
{
    static int ref_ ;
    static int release_ ;

    refcounter()
    {
        ++ref_;
        ++release_;
    }

    refcounter(const refcounter&)
    {
        ++ref_;
        ++release_;
    }
protected:
    ~refcounter()
    {
        --release_;
    }
};
template <typename T> int refcounter<T>::ref_(0);
template <typename T> int refcounter<T>::release_(0);

class A : refcounter<A>
{
public:
    void GetCounter()
    {
        std::cout << "cur ref is:"<< ref_ << "  "<< release_ << std::endl;
    }
};

class B : refcounter<B>
{
public:
    void GetCounter()
    {
        std::cout << "cur ref is:" << ref_ << "  " << release_ << std::endl;
    }
};
void TestRef()
{
    A a;
    B b;
    A a1(a);

    a1.GetCounter();
    b.GetCounter();
}
int main()
{
    TestRef();
    return 0;
}

```



### 3. 如Kotlin等的链式编程

一般来说在c++里很少出现这种链式的代码。这里通过CRTP实现了一种多态的链式式编程。

```cpp
template <typename ConcretePrinter>
class Printer
{
public:
    Printer(std::ostream& pstream) : stream_(pstream) {}

    template <typename T>
    ConcretePrinter& print(T&& t)
    {
        stream_ << t;
        return static_cast<ConcretePrinter&>(*this);
    }

    template <typename T>
    ConcretePrinter& println(T&& t)
    {
        stream_ << t << std::endl;
        return static_cast<ConcretePrinter&>(*this);
    }
private:
    std::ostream& stream_;
};
enum  Color
{
red,blue,green
};
class CoutPrinter : public Printer<CoutPrinter>
{
public:
    CoutPrinter() : Printer(std::cout) {}

    CoutPrinter& SetConsoleColor(Color c)
    {
        return *this;
    }
};
void TestChain()
{
    CoutPrinter().print("Hello ").SetConsoleColor(Color::red).println("Printer!");
}

int main()
{
    TestChain();
    return 0;
}
```



#### 4. 多态拷贝构造（Polymorphic copy construction）

```cpp
class AbstractShape {
public:
    virtual ~AbstractShape() = default;
    virtual std::unique_ptr<AbstractShape> clone() const = 0;
    //virtual void Show() = 0;
};

// This CRTP class implements clone() for Derived
template <typename Derived>
class Shape : public AbstractShape {
public:
    std::unique_ptr<AbstractShape> clone() const override {
        return std::make_unique<Derived>(static_cast<Derived const&>(*this));
    }

protected:
    // We make clear Shape class needs to be inherited
    Shape() = default;
    Shape(const Shape&) = default;
    Shape(Shape&&) = default;
};

// Every derived class inherits from CRTP class instead of abstract class

class Square : public Shape<Square> 
{
public:
    void Show() override{ std::cout << "is Square!" << std::endl; }
};
class Circle : public Shape<Circle> 
{
public:
    void Show() override{ std::cout << "is Circle!" << std::endl; }
};

void TestClone()
{
    std::unique_ptr<Square> ptrS = std::make_unique<Square>();
    std::unique_ptr<Circle> ptrC = std::make_unique<Circle>();
    auto p = ptrS->clone();
    std::unique_ptr<AbstractShape> pc = ptrC->clone();
    //p->Show();
    //pc->Show();
}

int main()
{
    TestClone();
    return 0;
}
```

