### [依赖注入(Dependency Injection)](#)
> **介绍**：是一种软件设计模式，也是实现控制反转的其中一种技术。這种模式能让一个物件接收它所依赖的其他物件。**依赖** 是指接收方所需的对象。**注入** 是指将 **依赖** 传递给接收方的过程。
**此模式确保了任何想要使用给定服务的物件不需要知道如何建立這些服务**。
----

### [1. 基本概念](#)
**依赖注入** 这种技术手段实现功能模块对其依赖组件的**控制反转**,将 **依赖组件** 的配置和使用分离开。

**组件和服务:** 
* 组件是一种独立的、可重用的软件模块，它封装了某一特定功能或一组相关功能。
* 服务是一种独立的功能单元，它通过网络或其他通信机制向其他系统或组件提供特定的功能。

> 服务的一个常见实现形式是微服务架构，在这种架构中，应用被拆分为多个小的、独立部署的服务，每个服务实现特定的业务功能。

组件和服务的区别
* 组件通常是在 **同一个应用内部运行** 的（如 jar 文件、dll 或者源码导入），而服务 **通常是在不同的网络节点上独立部署和运行** 的（如 WebService、消息系统、RPC 或者 Socket）。
* 组件之间的通信通常是通过函数调用或消息传递，而服务之间的通信则通常是通过网络请求（如HTTP）进行的。
* 服务的独立性更强，可以独立部署和扩展，而组件通常依赖于宿主应用的运行环境。

依赖注入的形式主要有三种，分别将它们叫做
* 构造注入（ Constructor Injection）
* 函数/方法/属性注入（ Setter Injection）
* 接口注入（ Interface Injection）

```cpp
class UserController{
private:
    MysqlConnectionService service; //数据库服务

    UserController(){
        service = MysqlConnectionService("127.0.0.1",3306, "root", "123456", "test");
    }
};
// 使用构造注入
class UserController{
private:
    MysqlConnectionService service; //数据库服务

    UserController(MysqlConnectionService _service){
        service = _service;
    }
};
```
#### 1.1 控制反转简析
控制反转IoC(Inversion of Control)是说创建对象的控制权进行转移 **(获得依赖对象的方式反转了)** ，以前创建对象的主动权和创建时机是由自己把控的，而现在这种权力转移到第三方，比如转移交给了IoC容器，它就是一个专门用来创建对象的工厂...。

> 控制反转（创建对象实例的控制权反转），说的是一个类A要调用另一个类B，本来应该在类A里面创建B的实例的，控制权在A手里。现在用了Spring了，有了IOC，控制权就不在A手里了，而是交到Spring的IOC容器了，A要用到B，那Spring就把B分给A了。

IoC的一个重点是在系统运行中，动态的向某个对象提供它所需要的其他对象。这一点是通过DI（Dependency Injection，依赖注入）来实现的。

### [2. C++ 实现 IoC分析](#)
首先给出一个例子，如下所示，可以看到有一个接口类、一个具体实现类和一个客户端类，客户端类依赖于IService接口类。

**构造注入**
```cpp
// 具体实现类
class Service{
public:
    void serve() override {
        std::cout << "Service is serving" << std::endl;
    }
};

//函数方法注入
class Client {
    std::shared_ptr<Service> service;
public:
    Client(std::shared_ptr<Service> service) : service(service) {}
    void doSomething() {
        service->serve();
    }
};
```

**方法/函数注入**
```cpp
// 具体实现类
class Service{
public:
    void serve() override {
        std::cout << "Service is serving" << std::endl;
    }
};
//函数方法注入
class Client {
public:
    void doSomething(std::shared_ptr<Service> service) {
        service->serve();
    }
};
```
**接口注入**: 通过接口或抽象类定义依赖对象，由外部实现并注入到组件中。
```cpp
// 接口类
class IService {
public:
    virtual void serve() = 0;
    virtual ~IService() = default;
};

// 具体实现类
class Service : public IService {
public:
    void serve() override {
        std::cout << "Service is serving" << std::endl;
    }
};

// 依赖于IService的客户端类
class Client {
    std::shared_ptr<IService> service;
public:
    Client(std::shared_ptr<IService> service) : service(service) {}
    void doSomething() {
        service->serve();
    }
};
```
#### 2.1 依赖注入模式的角色
虽然依赖注入并不属于传统的设计模式，但我们仍然可以将其划分为以下几个角色：
* **依赖抽象(Abstraction of Dependency)** :这是一个抽象接口或抽象基类，它定义了一个组件所依赖的功能。高层模块和低层模块都依赖于这个抽象，而不是相互依赖。
* **依赖实现(Implementation of Dependency)** :这是实现依赖抽象的具体类。通常，一个依赖抽象可能有多个依赖实现，它们提供了不同的功能。
* **依赖消费者(Consumer of Dependency)** :这是依赖于依赖抽象的类，它通过依赖抽象与依赖实现进行交互。依赖消费者通常在运行时接收所依赖的具体实现，而不是在编译时直接依赖具体实现。这样做有助于降低耦合度，提高代码的可维护性和可测试性。
* **依赖注入器(Dependency Injector)** :这是负责创建和管理依赖实现的对象，以及将依赖实现注入到依赖消费者中的组件。依赖注入器可以是手动编写的代码，也可以是使用依赖注入容器（如 Spring、Google Guice）实现的自动化机制。
   
依赖注入的过程大致如下：
1. 定义依赖抽象，以及针对不同场景的依赖实现。
2. 在依赖消费者中引用依赖抽象，并通过构造函数、setter方法或接口注入的方式接收具体的依赖实现。
3. 使用依赖注入器将合适的依赖实现注入到依赖消费者中。
   
通过这样的设计，您可以在不修改依赖消费者的前提下，灵活地调整依赖实现，从而提高代码的可维护性和可测试性。

#### 2.2 场景需求
存在**Notification**类，该类需要依赖一个**SendMessageService**类，SendMessageService类有**EmailService**和**SMSService**两个实现类，Notification类需要根据不同的场景选择不同的SendMessageService类。

```cpp
class SendMessageService {
public:
    virtual ~SendMessageService() = default;
    virtual void sendMessage(const std::string& message, const std::string& recipient) = 0;
};

class EmailService : public SendMessageService {
public:
    void sendMessage(const std::string& message, const std::string& recipient) override {
        // 实现发送电子邮件的逻辑
        std::cout << "Sending email: " << message << " to " << recipient << std::endl;
    }
};
class SMSService : public SendMessageService {
public:
    void sendMessage(const std::string& message, const std::string& recipient) override {
        // 实现发送短信的逻辑
        std::cout << "Sending SMS: " << message << " to " << recipient << std::endl;
    }
};


class Notification {
public:
    explicit Notification(std::shared_ptr<SendMessageService> messageService) : messageService_(std::move(messageService)) {

    }
    
    void notify(const std::string& message, const std::string& recipient) {
        messageService_->sendMessage(message, recipient);
    }
private:
    std::shared_ptr<SendMessageService> messageService_;
};
```
#### 2.3 Boost.DI 库



### 参考资料
* [Spring实现IOC（控制反转）的三种方式 CSDN](https://blog.csdn.net/zhaoraolin/article/details/78941062)
* [深入浅出依赖注入](https://segmentfault.com/a/1190000014803412)
* [C++设计模式之 依赖注入模式探索](https://developer.aliyun.com/article/1463842)