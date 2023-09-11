### [观察者模式](#)

**介绍**：观察者模式是一种行为型设计模式，它定义了一种一对多的依赖关系，当一个对象的状态发生改变时，其所有依赖者都会收到通知并自动更新。当对象间存在一对多关系时，则使用观察者模式（Observer Pattern）。比如，当一个对象被修改时，则会自动通知依赖它的对象。观察者模式属于行为型模式。

-----



### 1. 基本概念

* **主要解决：**一个对象状态改变给其他对象通知的问题，而且要考虑到易用和低耦合，保证高度的协作。
* **何时使用：**一个对象（目标对象）的状态发生改变，所有的依赖对象（观察者对象）都将得到通知，进行广播通知。
* **关键代码：**在抽象类里有一个列表存放观察者们





在观察者模式中，通常有两种类型的对象：主题（Subject）和观察者（Observer）。主题对象是被观察的对象，它维护了一个观察者列表，并提供注册、注销和通知等方法。观察者对象则用于接收主题对象的通知，并根据需要做出相应的响应。

以下是观察者模式的基本构成要素：

1. 主题（Subject）：具有注册、注销和通知观察者的接口。它维护了一个观察者列表，并在状态变化时通知观察者。
2. 具体主题（Concrete Subject）：实现主题接口，并维护自身的状态。在状态变化时，通知观察者更新。
3. 观察者（Observer）：定义了接收通知并进行响应的方法。通常包括一个或多个回调方法来处理主题对象的通知。
4. 具体观察者（Concrete Observer）：实现观察者接口，并根据需要定义自己的响应逻辑。每个具体观察者可以选择订阅一个或多个具体主题。

观察者模式的**优点**包括：

1. 解耦性：主题对象和观察者对象之间的关系是松散耦合的，它们可以独立地进行修改和扩展，而不会相互影响。
2. 可扩展性：可以方便地增加新的观察者对象或主题对象，而无需修改现有的代码。
3. 实时性：观察者可以实时地接收到主题对象发出的通知，及时进行更新。

观察者模式在很多场景中都有应用，包括事件驱动系统、GUI开发、消息队列等。它可以帮助实现组件之间的松耦合，提高系统的灵活性和可维护性。

#### 1.1 实现启蒙

以自己为例，我下班的时候会告诉孩子和他妈，我开车要往回走了

- 孩子妈收到消息后开始做饭
- 孩子收到消息后，就赶紧收起手机，怕挨揍



```cpp
#include <iostream>
class Son{
public:
    void DoSomething(){
        std::cout<<"爸爸回来了，赶紧去写作业"<<std::endl;
    }
};

class Wife{
public:
    void DoSomething(){
        std::cout<<"老公回来了，去做饭"<<std::endl;
    }
};

class Me{
public:
    void Gohome(){
        wife.DoSomething();
        son.DoSomething();
    }
private:
    Wife wife;
    Son son;
};

int main(){
    Me me;
    me.Gohome();
    return 0;
}
```

这样写的不足如下：

1. 如果关心我的人变多了，比如我又加了我老妈、老爸 ，这时候我们不得不去修改Me的类



### 2. 松耦合实现

**订阅(抽象)观察者**：

```cpp
//抽象观察者
class Observer {
public:
    virtual void response(bool light) = 0;
};
```

**抽象主题**：

* 具体注册方法
* 取消注册方法
* 通知方法

```cpp
//主题
class Subject {
public:
    //订阅
    virtual void registerObserver(Observer* observer) = 0;
    //取消订阅
    virtual void removeObserver(Observer* observer) = 0;
    //通知
    virtual void notifyObservers(bool light) = 0;
};
```

**具体观察者**

```cpp
class LED : public Observer {
public:
    explicit LED(Subject* subject) : _subject(subject) {
        _subject->registerObserver(this);
    }

    void response(bool light) override {
        if(light) {
            std::cout << "LED is on." << std::endl;
        } else {
            std::cout << "LED is off." << std::endl;
        }
    }
private:
    Subject* _subject;
};

class Buzzer : public Observer {
public:
    explicit Buzzer(Subject* subject) : _subject(subject) {
        _subject->registerObserver(this);
    }

    void response(bool light) override {
        if(light) {
            std::cout << "Buzzer is on." << std::endl;
        } else {
            std::cout << "Buzzer is off." << std::endl;
        }
    }
private:
    Subject* _subject;
};
```

**测试代码**：

```cpp
int main()
{
    LightSensor sensor;
    // 创建 Observers
    auto led = new LED(&sensor);
    auto buzzer = new Buzzer(&sensor);

    // 模拟光感传感器检测光线
    sensor.setLight(true);
    sensor.setLight(false);

    sensor.removeObserver(led);
    sensor.removeObserver(buzzer);

    delete led;
    delete buzzer;
};
```

